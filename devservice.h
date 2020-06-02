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

        Q_INVOKABLE void addDev(QString hostIp, quint16 hostPort);

    signals:

    };
}

#endif // DEVSERVICE_H
