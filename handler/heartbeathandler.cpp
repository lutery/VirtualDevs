#include "heartbeathandler.h"
#include "printerorder.h"

HeartBeatHandler::HeartBeatHandler(QObject *parent) : AbsHandler(parent)
{

}

bool HeartBeatHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    if (deviceOrder.orderType().at(0) != PrinterOrder::HEARTBEAT().at(0))
    {
        return 0;
    }

    qDebug() << "receive server send heart beat";

    return true;
}
