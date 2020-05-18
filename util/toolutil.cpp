#include "printerorder.h"
#include "toolutil.h"
#include <QCryptographicHash>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <chrono>
#include <random>
#include <sstream>

ToolUtil::ToolUtil()
{

}

int ToolUtil::toInt(std::string str)
{
    std::stringstream sin(str);

    if (!ToolUtil::isNum(str))
    {
        return -1;
    }

    double tmpD;
    sin >> tmpD;

    return static_cast<int>(tmpD);
}

bool ToolUtil::isNum(std::string str)
{
    std::stringstream sin(str);
    double d;
    char c;

    if (!(sin >> d))
    {
        return false;
    }
    else if (sin >> c)
    {
        return false;
    }

    return true;
}

int ToolUtil::genRangeInt(int min, int max)
{
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rand_generator(seed);
    std::uniform_int_distribution<int> dist(min, max);
    int range = dist(rand_generator);

    return range;
}

QByteArray ToolUtil::getResultMsg(QString result, IVerify* verifyTool)
{
    QByteArray resultArray;

    QJsonObject resultObj;
    resultObj.insert("result", result);

    QJsonDocument document;
    document.setObject(resultObj);

    QByteArray resultBytes = ToolUtil::strCodecTo(document.toJson(), "gb18030");

    resultArray.append(PrinterOrder::RESULTINFO());
    resultArray.append(ToolUtil::intToBytes(resultBytes.length()));
    resultArray.append((unsigned char)verifyTool->verifyType());
    resultArray.append(verifyTool->generateVerifyCode(resultBytes));
    resultArray.append(resultBytes);
    resultArray.append(0x24);

    return resultArray;
}

QString ToolUtil::str2Md5(QString &&str)
{
    return QString().append(QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5).toHex());
}

QString ToolUtil::bytes2Md5(QByteArray &byteArray)
{
    return QString().append(QCryptographicHash::hash(byteArray, QCryptographicHash::Md5).toHex());
}

QByteArray ToolUtil::strCodecTo(QString src, QString toCodec)
{
    QTextCodec* srcStrCodec = QTextCodec::codecForName("utf-8");
    QTextCodec* toStrCodec = QTextCodec::codecForName(toCodec.toLocal8Bit());

    return toStrCodec->fromUnicode(srcStrCodec->toUnicode(src.toUtf8()));
}

QByteArray ToolUtil::strCodecTo(QByteArray strBytes, QString fromCodec, QString toCodec)
{
    QTextCodec* srcStrCodec = QTextCodec::codecForName(fromCodec.toLocal8Bit());
    QTextCodec* toStrCodec = QTextCodec::codecForName(toCodec.toLocal8Bit());

    return toStrCodec->fromUnicode(srcStrCodec->toUnicode(strBytes));
}

QByteArray ToolUtil::intToBytes(int length)
{
    QByteArray intBytes;
    intBytes[0] = (length >> 24) & 0xff;
    intBytes[1] = (length >> 16) & 0xff;
    intBytes[2] = (length >> 8) & 0xff;
    intBytes[3] = (length >> 0) & 0xff;

    return intBytes;
}

int ToolUtil::bytesToInt(QByteArray data)
{
    return data.toHex().toInt(nullptr, 16);
}

QString ToolUtil::bytes2HexStr(QByteArray data)
{
    QString ret(data.toHex().toUpper());
        int len = ret.length()/2;
//        qDebug()<<len;
        for(int i=1;i<len;i++)
        {
//            qDebug()<<i;
            ret.insert(2*i+i-1," ");
        }

        return ret;
}

int ToolUtil::verifyTypeLength(VerifyType verifyType)
{
    switch (verifyType)
    {
    case VerifyType::MD5:
        return 16;

    case VerifyType::CRC8:
        return 1;

    case VerifyType::CRC16:
    case VerifyType::CRC16CCITT:
        return 2;

    case VerifyType::CRC32:
        return 4;


    default:
        return 0;
    }
}

quint16 ToolUtil::generalCRC16(quint16 wCRCin, quint16 wCPoly, quint16 wResultXOR, bool input_invert, bool ouput_invert, const char *puchMsg, int usDataLen)
{
    quint8 wChar = 0;
    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        if(input_invert)//输入值反转
        {
            quint8 temp_char = wChar;
            wChar=0;
            for(int i=0;i<8;++i)
            {
                if(temp_char&0x01)
                    wChar|=0x01<<(7-i);
                temp_char>>=1;
            }
        }
        wCRCin ^= (wChar << 8);
        for (int i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    if(ouput_invert)
    {
        quint16 temp_short = wCRCin;
        wCRCin=0;
        for(int i=0;i<16;++i)
        {
            if(temp_short&0x01)
                wCRCin|=0x01<<(15-i);
            temp_short>>=1;
        }
    }
    return (wCRCin^wResultXOR);
}
