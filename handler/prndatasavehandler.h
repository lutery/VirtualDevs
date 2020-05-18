#ifndef PRNDATASAVEHANDLER_H
#define PRNDATASAVEHANDLER_H

#include "abshandler.h"

class PrnDataSaveHandler : public AbsHandler
{
    Q_OBJECT
public:
    explicit PrnDataSaveHandler(QObject *parent = nullptr);


    // AbsHandler interface
protected:
    bool handle(DevClient &devClient, DeviceOrder &deviceOrder);
};

#endif // PRNDATASAVEHANDLER_H
