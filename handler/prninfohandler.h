#ifndef PRNINFOHANDLER_H
#define PRNINFOHANDLER_H

#include "abshandler.h"

class PrnInfoHandler : public AbsHandler
{
    Q_OBJECT
public:
    explicit PrnInfoHandler(QObject *parent = nullptr);


    // AbsHandler interface
protected:
    bool handle(DevClient &devClient, DeviceOrder &deviceOrder);
};

#endif // PRNINFOHANDLER_H
