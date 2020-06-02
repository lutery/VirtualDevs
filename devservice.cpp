#include "devservice.h"
#include "asyncdevclient.h"

#include <QThreadPool>

namespace onechchy
{
    DevService::DevService(QObject *parent) : QObject(parent)
    {

    }

    void DevService::addDev(QString hostIp, quint16 hostPort)
    {
        QThreadPool::globalInstance()->start(new AsyncDevClient(hostIp, hostPort));
    }
}
