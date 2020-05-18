#ifndef MD5VERIFY_H
#define MD5VERIFY_H

#include "iverify.h"

class MD5Verify : public IVerify
{
     Q_OBJECT

public:
    MD5Verify(QObject* parent = nullptr);
    virtual ~MD5Verify(){}



    // IVerify interface
public:
    bool verifyContent(QByteArray verifyCode, QByteArray verifyContent);
    QByteArray generateVerifyCode(QByteArray content);
    VerifyType verifyType();
};

#endif // MD5VERIFY_H
