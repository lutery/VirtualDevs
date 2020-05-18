#ifndef RESULTINFOHANDLER_H
#define RESULTINFOHANDLER_H

#include "abshandler.h"

class ResultInfoHandler : public AbsHandler
{
    Q_OBJECT
public:
    explicit ResultInfoHandler(QObject *parent = nullptr);
    virtual ~ResultInfoHandler();


    // AbsHandler interface
protected:
    bool handle(DevClient &devClient, DeviceOrder &deviceOrder);
};

#endif // RESULTINFOHANDLER_H
