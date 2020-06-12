#include "crc16ccitt.h"
#include "util/toolutil.h"

CRC16CCITT::CRC16CCITT(QObject *parent) : IVerify(parent)
{

}

bool CRC16CCITT::verifyContent(QByteArray verifyCode, QByteArray verifyContent)
{
    if (verifyCode.length() <= 0 || verifyContent.length() <= 0)
    {
        return false;
    }

    return verifyCode == this->crc16ccitt(verifyContent);
}

QByteArray CRC16CCITT::generateVerifyCode(QByteArray content)
{
    return this->crc16ccitt(content);
}

VerifyType CRC16CCITT::verifyType()
{
    return VerifyType::CRC16CCITT;
}

QByteArray CRC16CCITT::crc16ccitt(QByteArray content)
{
    if (content.length() <= 0)
    {
        return QByteArray().append((unsigned char)0x00).append((unsigned char)0x00);
    }

    quint16 verifyCode = ToolUtil::generalCRC16(0, 0x1021, 0, true, true, content.data(), content.length());

    QByteArray verifyCodeBuf;
    verifyCodeBuf[0] = (verifyCode >> 8) & 0xff;
    verifyCodeBuf[1] = (verifyCode >> 0) & 0xff;

    return verifyCodeBuf;
}
