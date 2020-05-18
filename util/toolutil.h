#ifndef TOOLUTIL_H
#define TOOLUTIL_H

#include <QString>
#include <QByteArray>
#include <string>
#include "verify/iverify.h"

class ToolUtil
{
private:
    ToolUtil();

public:
    static int toInt(std::string str);
    static bool isNum(std::string str);
    static int genRangeInt(int min, int max);
    static QByteArray getResultMsg(QString result, IVerify* verifyTool);
    static QString str2Md5(QString&& str);
    static QString bytes2Md5(QByteArray& byteArray);
    static QByteArray strCodecTo(QString src, QString toCodec);
    static QByteArray strCodecTo(QByteArray strBytes, QString fromCodec, QString toCodec);
    static QByteArray intToBytes(int length);
    static int bytesToInt(QByteArray data);
    static QString bytes2HexStr(QByteArray data);
    static int verifyTypeLength(VerifyType verifyType);
    static quint16 generalCRC16(quint16 wCRCin,quint16 wCPoly,quint16 wResultXOR,bool input_invert,bool ouput_invert,const char *puchMsg, int usDataLen);
};

#endif // TOOLUTIL_H
