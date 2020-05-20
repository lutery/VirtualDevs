#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QTextStream>
#include <QString>

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>

#include <istream>
#include <sstream>

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

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

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
