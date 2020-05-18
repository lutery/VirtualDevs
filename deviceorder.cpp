#include "deviceorder.h"

DeviceOrder::DeviceOrder()
{

}

QByteArray DeviceOrder::combine()
{
    return QByteArray().append(orderType()).append(getMlengthBytes())
            .append(getVerifyType()).append(getVerifyCode())
            .append(getContent()).append(getEnd());
}

QByteArray DeviceOrder::orderType() const
{
    return mOrderType;
}

void DeviceOrder::setOrderType(const QByteArray &orderType)
{
    mOrderType = orderType;
}

QByteArray DeviceOrder::getMlengthBytes() const
{
    return mlengthBytes;
}

void DeviceOrder::setMlengthBytes(const QByteArray &value)
{
    mlengthBytes = value;
}

QByteArray DeviceOrder::getVerifyType() const
{
    return mVerifyType;
}

void DeviceOrder::setVerifyType(const QByteArray &verifyType)
{
    mVerifyType = verifyType;
}

QByteArray DeviceOrder::getVerifyCode() const
{
    return mVerifyCode;
}

void DeviceOrder::setVerifyCode(const QByteArray &verifyCode)
{
    mVerifyCode = verifyCode;
}

QByteArray DeviceOrder::getContent() const
{
    return mContent;
}

void DeviceOrder::setContent(const QByteArray &content)
{
    mContent = content;
}

QByteArray DeviceOrder::getEnd() const
{
    return end;
}

void DeviceOrder::setEnd(const QByteArray &value)
{
    end = value;
}
