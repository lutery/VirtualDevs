#include "md5verify.h"
#include <QCryptographicHash>

MD5Verify::MD5Verify(QObject *parent):IVerify (parent)
{

}

bool MD5Verify::verifyContent(QByteArray verifyCode, QByteArray verifyContent)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(verifyContent);

    QByteArray contentMD5 = md5.result();

    return verifyCode == contentMD5;
}

QByteArray MD5Verify::generateVerifyCode(QByteArray content)
{
    if (content.length() <= 0)
    {
        return QByteArray().append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00)
                .append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00)
                .append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00)
                .append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00).append((unsigned char)0x00);
    }

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(content);

    return md5.result();
}

VerifyType MD5Verify::verifyType()
{
    return VerifyType::MD5;
}
