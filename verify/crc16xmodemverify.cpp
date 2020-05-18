#include "crc16xmodemverify.h"

CRC16XModemVerify::CRC16XModemVerify(QObject *parent) : IVerify(parent)
{

}

bool CRC16XModemVerify::verifyContent(QByteArray verifyCode, QByteArray verifyContent)
{
    return verifyCode == this->CRC16_XMODEM((unsigned char*)verifyContent.data(), verifyContent.length());
}

QByteArray CRC16XModemVerify::generateVerifyCode(QByteArray content)
{
    return this->CRC16_XMODEM((unsigned char*)content.data(), content.length());
}

VerifyType CRC16XModemVerify::verifyType()
{
    return VerifyType::CRC16;
}

QByteArray CRC16XModemVerify::CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen)
{
    unsigned short wCRCin = 0x0000;
    unsigned short wCPoly = 0x1021;
    unsigned char wChar = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        wCRCin ^= (wChar << 8);
        for (int i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }

    QByteArray arrayCRC;
    arrayCRC[0] = (wCRCin >> 8) & 0xff;
    arrayCRC[1] = (wCRCin >> 0) & 0xff;

    return arrayCRC;
}
