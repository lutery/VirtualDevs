#ifndef UNKNOWNORDERHANDLER_H
#define UNKNOWNORDERHANDLER_H

#include "abshandler.h"

class UnknownOrderHandler : public AbsHandler
{
public:
    UnknownOrderHandler(QObject* parent = nullptr);
    virtual ~UnknownOrderHandler();

private:
    virtual bool handle(DevClient& devClient, DeviceOrder& deviceOrder);
};

#endif // UNKNOWNORDERHANDLER_H
