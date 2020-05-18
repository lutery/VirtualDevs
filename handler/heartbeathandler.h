#ifndef HEARTBEATHANDLER_H
#define HEARTBEATHANDLER_H

#include "abshandler.h"

class HeartBeatHandler : public AbsHandler
{
    Q_OBJECT
public:
    explicit HeartBeatHandler(QObject *parent = nullptr);


    // AbsHandler interface
protected:
    bool handle(DevClient &devClient, DeviceOrder &deviceOrder);
};

#endif // HEARTBEATHANDLER_H
