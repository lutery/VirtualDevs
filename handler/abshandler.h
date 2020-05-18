#ifndef ABSHANDLER_H
#define ABSHANDLER_H

#include <QObject>
#include "devclient.h"
#include "deviceorder.h"

class IVerify;

class AbsHandler : public QObject
{
    Q_OBJECT
public:
    explicit AbsHandler(QObject *parent = nullptr);
    virtual ~AbsHandler();

    virtual void ReadDataHandler(DevClient& devClient, DeviceOrder& deviceOrder) final;
    virtual void setNext(AbsHandler* pNext);

protected:
    virtual bool handle(DevClient& devClient, DeviceOrder& deviceOrder) = 0;

signals:

public slots:

protected:
    IVerify* mpVerify;
    AbsHandler* mpNext = nullptr;
};

#endif // ABSHANDLER_H
