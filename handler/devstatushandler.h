#ifndef DEVSTATUSHANDLER_H
#define DEVSTATUSHANDLER_H

#include "abshandler.h"

class DevStatusHandler : public AbsHandler
{
public:
    explicit DevStatusHandler(QObject *parent = nullptr);
    virtual ~DevStatusHandler();

    // AbsHandler interface
protected:
    bool handle(DevClient &devClient, DeviceOrder &deviceOrder);
};

#endif // DEVSTATUSHANDLER_H
