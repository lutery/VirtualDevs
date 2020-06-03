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

void AsyncDevClient::run()
{
            mpDevClient = new DevClient();
            mpDevClient->initDevice(mServerIP, mServerPort);

            QEventLoop loop;
            QObject::connect(mpDevClient, SIGNAL(receiveLog(QString)), this, SIGNAL(receiveLog(QString)));
            QObject::connect(mpDevClient, SIGNAL(finish()), &loop, SLOT(quit()));
            loop.exec();
}
