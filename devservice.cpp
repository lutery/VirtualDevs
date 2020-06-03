#include "devservice.h"
#include "devicemanager.h"
#include "devinit.h"

#include <QThreadPool>

namespace onechchy
{
    DevService::DevService(QObject *parent) : QObject(parent)
    {

    }

    void DevService::initService(QString hostIp, quint16 hostPort, int numDev)
    {
        DevInit initParam;
        initParam.initParam(hostIp, hostPort, numDev);

        DeviceManager::getInstance(initParam);
    }
}
