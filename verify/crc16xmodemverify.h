#ifndef CRC16XMODEMVERIFY_H
#define CRC16XMODEMVERIFY_H

#include "iverify.h"

class CRC16XModemVerify : public IVerify
{
    Q_OBJECT
public:
    explicit CRC16XModemVerify(QObject *parent = nullptr);

    // IVerify interface
public:
    bool verifyContent(QByteArray verifyCode, QByteArray verifyContent);
    QByteArray generateVerifyCode(QByteArray content);
    VerifyType verifyType();

private:
    QByteArray CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen);
};

#endif // CRC16XMODEMVERIFY_H
