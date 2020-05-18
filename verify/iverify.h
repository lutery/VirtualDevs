#ifndef IVERIFY_H
#define IVERIFY_H

#include <QObject>
#include <QByteArray>

enum class VerifyType
{
    MD5 = 0x01,
    CRC8 = 0x02,
    CRC16 = 0x03,
    CRC32 = 0x04,
    CRC16CCITT = 0x05
};

class IVerify : public QObject
{
    Q_OBJECT
protected:
    explicit IVerify(QObject *parent = nullptr);
    virtual ~IVerify(){}

public:
    virtual bool verifyContent(QByteArray verifyCode, QByteArray verifyContent) = 0;
    virtual QByteArray generateVerifyCode(QByteArray content) = 0;
    virtual VerifyType verifyType() = 0;
};

#endif // IVERIFY_H
