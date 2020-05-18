#ifndef CRC16CCITT_H
#define CRC16CCITT_H

#include "iverify.h"

class CRC16CCITT : public IVerify
{
    Q_OBJECT
public:
    explicit CRC16CCITT(QObject *parent = nullptr);


    // IVerify interface
public:
    bool verifyContent(QByteArray verifyCode, QByteArray verifyContent);
    QByteArray generateVerifyCode(QByteArray content);
    VerifyType verifyType();

private:
    QByteArray crc16ccitt(QByteArray content);
};

#endif // CRC16CCITT_H
