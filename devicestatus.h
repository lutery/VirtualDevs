#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QObject>
#include <QMetaEnum>

class DeviceStatus : public QObject
{
    Q_OBJECT
public:
    DeviceStatus(QObject* parnet = nullptr);

    enum StatusEnum
    {
        ShortOfPaper = 0x30,
        Ready = 0x18,
        Offline = 0xfe,
        Printing = 0x03
    };

    Q_ENUM(StatusEnum)

    static QMap<QByteArray, QString> shortOfPaper();
    static QMap<QByteArray, QString> ready();
    static QMap<QByteArray, QString> offline();
    static QMap<QByteArray, QString> printing();
};

#endif // DEVICESTATUS_H
