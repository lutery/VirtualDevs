#include "devicemanager.h"
#include "devclient.h"
#include "asyncdevclient.h"
#include "devinit.h"
#include <QThreadPool>

DeviceManager* DeviceManager::gpInstance = nullptr;

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{

}

DeviceManager::DeviceManager(DevInit &devInit, QObject *parent):QObject (parent)
  ,mDevCount(devInit.devCount()),mServerIP(devInit.serverIP()),mServerPort(devInit.serverPort())
{
    qDebug() << "mDevCount is " << mDevCount;
    for (int i = 0; i < mDevCount; ++i)
    {
        AsyncDevClient* pDevClient = new AsyncDevClient(mServerIP, mServerPort);
        connect(pDevClient, SIGNAL(receiveLog(QString)), this, SIGNAL(receiveLog(QString)));
        mDevs.append(pDevClient);
        QThreadPool::globalInstance()->start(pDevClient);
//        DevClient* devClient = new DevClient(nullptr);
//        devClient->initDevice(mServerIP, mServerPort);

//        mDevs.append(devClient);
    }
}

DeviceManager *DeviceManager::getInstance(DevInit &devInit)
{
    if (DeviceManager::gpInstance == nullptr)
    {
        gpInstance = new DeviceManager(devInit);
    }

    return gpInstance;
}

DeviceManager *DeviceManager::getInstance()
{
    return gpInstance;
}

DeviceManager::~DeviceManager()
{
    qDebug() << "释放所有客户端";

    for (auto& pDevClient : mDevs)
    {
        delete pDevClient;
    }
}
