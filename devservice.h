#ifndef DEVSERVICE_H
#define DEVSERVICE_H

#include <QObject>
#include <QString>
#include <QList>
#include "MyLog.h"

namespace onechchy
{
    class DevService : public QObject
    {
        Q_OBJECT
    public:
        explicit DevService(QObject *parent = nullptr);

        Q_INVOKABLE void initService(QString hostIp, quint16 hostPort, int numDev);
        Q_INVOKABLE void switchDevLog(QString devId);

    signals:
        void devConnect(QString devId);
        void devDisconnect(QString devId);
        void receiveLog(QString log);
    };
}

#endif // DEVSERVICE_H
