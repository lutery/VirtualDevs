#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

#include "MyLog.h"
#include "devservice.h"
#include "devicemanager.h"
#include "devinit.h"

#include <iostream>
#include <istream>
#include <sstream>
#include <QThreadPool>

int main(int argc, char *argv[])
{
    QFile logConfig(":/properties/log4cplus.properties");
    if (logConfig.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&logConfig);
        QString configTxt = in.readAll();

        std::stringbuf configBuf(configTxt.toStdString());
        std::istream configStream(&configBuf);

        log4cplus::initialize();
        log4cplus::PropertyConfigurator pc(configStream);

        pc.configure();
    }

    LOG4CPLUS_INFO(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck")), LOG4CPLUS_TEXT("Hello, world! this is Log4cplus"));
    MyLog::I("hello this is MyLog");
    LOGI("hello this is Marco");
    LOGIM("hello", "this", "is", "Marco");

    LOGIM("max thread count", std::to_string(QThreadPool::globalInstance()->maxThreadCount()), "stack Size is", std::to_string(QThreadPool::globalInstance()->stackSize()));
    QThreadPool::globalInstance()->setMaxThreadCount(100);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<onechchy::DevService>("DevServiceQml", 1, 0, "DevService");
//    qmlRegisterSingletonType<onechchy::DevService>("DevServiceQml", 1, 0, "DevService", [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
//        Q_UNUSED(engine);
//        Q_UNUSED(scriptEngine);

//        onechchy::DevService* devService = new onechchy::DevService();

//        return devService;
//    });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
