#ifndef PRINTERORDER_H
#define PRINTERORDER_H

#include <QByteArray>

class PrinterOrder
{
private:
    PrinterOrder();

public:
    static QByteArray DEVINIT();
    static QByteArray DEVINFO();
//    static QByteArray PRNDATA();
//    static QByteArray PRNOK();
    static QByteArray HEARTBEAT();
    static QByteArray DEVSTATUS();
    static QByteArray GETDEVSTATUS();
    static QByteArray RESULTINFO();
    static QByteArray PRNDATA();
    static QByteArray PRNINFO();
};

#endif // PRINTERORDER_H
