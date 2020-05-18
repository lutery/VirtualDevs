#include "unknownorderhandler.h"
#include "util/toolutil.h"

UnknownOrderHandler::UnknownOrderHandler(QObject *parent):AbsHandler (parent)
{

}

UnknownOrderHandler::~UnknownOrderHandler()
{

}

bool UnknownOrderHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    qDebug() << "##############receive unknown data from server start##############";
    qDebug() << ToolUtil::bytes2HexStr(deviceOrder.combine());
    qDebug() << "##############receive unknown data from server end##############";
}
