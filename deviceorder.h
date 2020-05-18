#ifndef DEVICEORDER_H
#define DEVICEORDER_H

#include <QByteArray>

class DeviceOrder
{
public:
    DeviceOrder();

    QByteArray combine();

    QByteArray orderType() const;
    void setOrderType(const QByteArray &orderType);

    QByteArray getMlengthBytes() const;
    void setMlengthBytes(const QByteArray &value);

    QByteArray getVerifyType() const;
    void setVerifyType(const QByteArray &verifyType);

    QByteArray getVerifyCode() const;
    void setVerifyCode(const QByteArray &verifyCode);

    QByteArray getContent() const;
    void setContent(const QByteArray &content);

    QByteArray getEnd() const;
    void setEnd(const QByteArray &value);

private:
    QByteArray mOrderType;
    QByteArray mlengthBytes;
    QByteArray mVerifyType;
    QByteArray mVerifyCode;
    QByteArray mContent;
    QByteArray end;
};

#endif // DEVICEORDER_H
