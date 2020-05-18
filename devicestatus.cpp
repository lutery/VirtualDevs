#include "devicestatus.h"
#include <tuple>

DeviceStatus::DeviceStatus(QObject *parnet) : QObject (parnet)
{

}

QMap<QByteArray, QString> DeviceStatus::shortOfPaper()
{
    static QMap<QByteArray, QString> status({std::pair(QByteArrayLiteral("\x30"), "缺纸")});

    return status;
}

QMap<QByteArray, QString> DeviceStatus::ready()
{
    static QMap<QByteArray, QString> status({std::pair(QByteArrayLiteral("\x18"), "就绪")});

    return status;
}

QMap<QByteArray, QString> DeviceStatus::offline()
{
    static QMap<QByteArray, QString> status({std::pair(QByteArrayLiteral("\xfe"), "离线")});

    return status;
}

QMap<QByteArray, QString> DeviceStatus::printing()
{
    static QMap<QByteArray, QString> status({std::pair(QByteArrayLiteral("\x03"), "正在打印")});

    return status;
}
