#include "asyncdevclient.h"
#include "devclient.h"
#include <QEventLoop>

AsyncDevClient::AsyncDevClient(QString serverIP, quint16 serverPort) : mServerIP(serverIP), mServerPort(serverPort)
{

}

void AsyncDevClient::run()
{
            DevClient* devClient = new DevClient();
            devClient->initDevice(mServerIP, mServerPort);

            QEventLoop loop;
            QObject::connect(devClient, SIGNAL(finish()), &loop, SLOT(quit()));
            loop.exec();
}
