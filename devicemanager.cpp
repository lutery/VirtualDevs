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
        // 只有切换到某个设备的时候，才进行信号的连接
//        connect(pDevClient, SIGNAL(receiveLog(QString)), this, SIGNAL(receiveLog(QString)));
        connect(pDevClient, SIGNAL(devconnect(QString)), this, SLOT(devConnect(QString)));
        connect(pDevClient, SIGNAL(devdisconnect(QString)), this, SLOT(devDisconnect(QString)));
        mDevs.insert(pDevClient->devID(), pDevClient);
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

void DeviceManager::switchDev(QString devId)
{
    if (mpCurDev != nullptr)
    {
        mpCurDev->disconnect();
        mpCurDev = nullptr;
    }

    mpCurDev = mDevs[devId];

    connect(mpCurDev, SIGNAL(receiveLog(QString)), this, SIGNAL(receiveLog(QString)));
}

QString DeviceManager::requestDevLog(QString devId)
{
    if (devId.length() <= 0)
    {
        mpCurDev->logs();
    }

    return mDevs[devId]->logs();
}

void DeviceManager::devConnect(QString devId)
{
    emit devConnect(devId);
}

void DeviceManager::devDisconnect(QString devId)
{
    emit devDisconnect(devId);
    mDevs.remove(devId);
}
