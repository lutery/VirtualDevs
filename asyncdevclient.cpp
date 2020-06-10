#include "asyncdevclient.h"
#include "devclient.h"
#include <QEventLoop>

AsyncDevClient::AsyncDevClient(QString serverIP, quint16 serverPort) : mServerIP(serverIP), mServerPort(serverPort)
{

}

AsyncDevClient::~AsyncDevClient()
{
    if (mpDevClient != nullptr)
    {
        delete mpDevClient;
    }
}

QString AsyncDevClient::devID() const
{
    if (mpDevClient != nullptr)
    {
        return mpDevClient->devID();
    }

    return "-1";
}

QString AsyncDevClient::logs() const
{

}

void AsyncDevClient::run()
{
//    while (true) {
//        qDebug() << "AsyncDevClient run";
//    }

            mpDevClient = new DevClient();
            mpDevClient->initDevice(mServerIP, mServerPort);

            QEventLoop loop;
            QObject::connect(mpDevClient, SIGNAL(receiveLog(QString)), this, SIGNAL(receiveLog(QString)));
            QObject::connect(mpDevClient, SIGNAL(finish()), &loop, SLOT(quit()));
            QObject::connect(mpDevClient, SIGNAL(devconnect(QString)), this, SIGNAL(devconnect(QString)));
            QObject::connect(mpDevClient, SIGNAL(devdisconnect(QString)), this, SIGNAL(devdisconnect(QString)));
            loop.exec();
}
