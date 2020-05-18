#ifndef DEVINFOHANDLER_H
#define DEVINFOHANDLER_H

#include "abshandler.h"

class DevInfoHandler : public AbsHandler
{
public:
    DevInfoHandler(QObject* parent = nullptr);
    virtual ~DevInfoHandler();

private:
     virtual bool handle(DevClient& devClient, DeviceOrder& deviceOrder);
};

#endif // DEVINFOHANDLER_H
