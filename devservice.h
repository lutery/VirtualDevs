#ifndef DEVSERVICE_H
#define DEVSERVICE_H

#include <QObject>
#include <QString>
#include "MyLog.h"

namespace onechchy
{
    class DevService : public QObject
    {
        Q_OBJECT
    public:
        explicit DevService(QObject *parent = nullptr);

        Q_INVOKABLE void initService(QString hostIp, quint16 hostPort, int numDev);

    signals:

    };
}

#endif // DEVSERVICE_H
