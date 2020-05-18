#include "printerorder.h"

PrinterOrder::PrinterOrder()
{

}

QByteArray PrinterOrder::DEVINIT()
{
    static QByteArray devInit = QByteArrayLiteral("\x11\x00\x00\x00");

    return devInit;
}

QByteArray PrinterOrder::DEVINFO()
{
    static QByteArray devInfo = QByteArrayLiteral("\x00\x00\x00\x00");

    return devInfo;
}

QByteArray PrinterOrder::HEARTBEAT()
{
    static QByteArray heartBeat = QByteArrayLiteral("\xff\x00\x00\x00");

    return heartBeat;
}

QByteArray PrinterOrder::DEVSTATUS()
{
    static QByteArray devStatus = QByteArrayLiteral("\xf1\x00\x00\x00");

    return devStatus;
}

QByteArray PrinterOrder::GETDEVSTATUS()
{
    static QByteArray devStatus = QByteArrayLiteral("\x12\x00\x00\x00");

    return devStatus;
}

QByteArray PrinterOrder::RESULTINFO()
{
    static QByteArray resultInfo = QByteArrayLiteral("\x0f\x00\x00\x00");

    return resultInfo;
}

QByteArray PrinterOrder::PRNDATA()
{
    static QByteArray resultInfo = QByteArrayLiteral("\xf0\x00\x00\x00");

    return resultInfo;
}

QByteArray PrinterOrder::PRNINFO()
{
    static QByteArray prnInfo = QByteArrayLiteral("\x01\x00\x00\x00");

    return prnInfo;
}
