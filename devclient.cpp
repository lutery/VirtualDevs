#include "devclient.h"
#include <QTcpSocket>
#include <QDebug>
#include <QUuid>
#include "util/toolutil.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "printerorder.h"
#include <QByteArray>
#include <QTimer>
#include "handler/devinfohandler.h"
#include "handler/devstatushandler.h"
#include "handler/heartbeathandler.h"
#include "handler/prndatasavehandler.h"
#include "handler/prninfohandler.h"
#include "handler/resultinfohandler.h"
#include "handler/unknownorderhandler.h"
#include "MyLog.h"
#include "verify/crc16ccitt.h"

DevClient::DevClient(QObject *parent) : QObject(parent), mpClient(nullptr)
{
    mpClient = new QTcpSocket(this);

    connect(mpClient, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(mpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(netError(QAbstractSocket::SocketError)));
    connect(mpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(mpClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(hasWritten(qint64)));
    connect(this, &DevClient::rTimeOut, this, &DevClient::readTimeOut);

    DevInfoHandler* infoHandler = new DevInfoHandler();
    DevStatusHandler* devStatusHandler = new DevStatusHandler();
    ResultInfoHandler* resultInfoHandler = new ResultInfoHandler();
    HeartBeatHandler* heartBeatHandler = new HeartBeatHandler();
    PrnDataSaveHandler* prnDataSavaHandler = new PrnDataSaveHandler();
    PrnInfoHandler* prnInfoHandler = new PrnInfoHandler();
    UnknownOrderHandler* unknownHandler = new UnknownOrderHandler();

    mpHandler = infoHandler;
    infoHandler->setNext(devStatusHandler);
    devStatusHandler->setNext(resultInfoHandler);
    resultInfoHandler->setNext(heartBeatHandler);
    heartBeatHandler->setNext(prnDataSavaHandler);
    prnDataSavaHandler->setNext(prnInfoHandler);
    prnInfoHandler->setNext(unknownHandler);

    mpMyLog = new MyLog();

    mDevID = ToolUtil::str2Md5(QUuid::createUuid().toString());
}

DevClient::~DevClient()
{
    if (mpMyLog != nullptr)
    {
        delete mpMyLog;
    }
}

void DevClient::initDevice(QString serverIP, quint16 serverPort)
{
    mServerIP = serverIP;
    mServerPort = serverPort;

    mpClient->connectToHost(serverIP, serverPort);

    qDebug() << "DevId " << mDevID << " born";
    LOGIM("DevId", mDevID.toStdString(), "born");
    emit receiveLog(mpMyLog->addLogs({"DevId", mDevID, "born"}));

    if (mReadTimer != nullptr)
    {
        mReadTimer->stop();
    }

    mReadTimer = new QTimer(this);
    mReadTimer->setSingleShot(false);
    mReadTimer->start(3000);
    connect(mReadTimer, &QTimer::timeout, [&](){
        emit this->rTimeOut();
    });
}

void DevClient::readData()
{
    qDebug() << "DevId " << mDevID << "receive dara";
    LOGIM("DevId", mDevID.toStdString(), "receive data");
    emit receiveLog(mpMyLog->addLogs({"DevId", mDevID, "receive data"}));

    if (mpClient->bytesAvailable() <= 0)
    {
        return;
    }

    QByteArray readBuff = mpClient->readAll();

//    qDebug() << "readBuff is " << ToolUtil::bytes2HexStr(readBuff);
    LOGIM("readBuff is", ToolUtil::bytes2HexStr(readBuff).toStdString());
    emit receiveLog(mpMyLog->addLogs({"readBuff is", ToolUtil::bytes2HexStr(readBuff)}));

    mBuffLock.lock();
    mClientBuff.append(readBuff);
    mBuffLock.unlock();

    int lenthOfCheck = 1;
    int lengthOfContent = 4;
    int lengthOfOrder = 4;
    char endByte = 0x24;

    int headerLength = lenthOfCheck + lengthOfOrder + lengthOfContent;
    if (mClientBuff.length() <= headerLength)
    {
        return;
    }

    char verifyByte = mClientBuff.at(8);
    int lengthOfVerifyType = ToolUtil::verifyTypeLength(VerifyType(verifyByte));

    if (mClientBuff.length() <= (lengthOfVerifyType + headerLength))
    {
        return;
    }

    QByteArray lengthOfJson;
    lengthOfJson[0] = mClientBuff[4];
    lengthOfJson[1] = mClientBuff[5];
    lengthOfJson[2] = mClientBuff[6];
    lengthOfJson[3] = mClientBuff[7];

    int jsonLength = ToolUtil::bytesToInt(lengthOfJson);

    qDebug() << "jsonLength is " << jsonLength;
//    qDebug() << "lengthOfJson is " << ToolUtil::bytes2HexStr(lengthOfJson);
//    qDebug() << "mClientBuff[3] " << ToolUtil::bytes2HexStr(mClientBuff.left(8).right(4));
    LOGIM("jsonLength is", QString::number(jsonLength).toStdString());
    emit receiveLog(mpMyLog->addLogs({"jsonLength is", QString::number(jsonLength)}));

    if (mClientBuff.length() <= (jsonLength + lengthOfVerifyType + headerLength))
    {
        return;
    }

    int endIndex = jsonLength + lengthOfVerifyType + headerLength;
    if (endByte != mClientBuff[endIndex])
    {
        qDebug() << "严重错误，尾部标识错误";
        LOGI("严重错误，尾部标识错误");
        emit receiveLog(mpMyLog->addLogs({"严重错误，尾部标识错误"}));
        qDebug() << "endIndex is " << endIndex << " and " << ToolUtil::bytes2HexStr(mClientBuff);
        LOGIM("endIndex is", QString::number(endIndex).toStdString(), "and", ToolUtil::bytes2HexStr(mClientBuff).toStdString());
        emit receiveLog(mpMyLog->addLogs({"endIndex is", QString::number(endIndex), "and", ToolUtil::bytes2HexStr(mClientBuff)}));
        return;
    }

//    qDebug() << "mClientBuff is " << ToolUtil::bytes2HexStr(mClientBuff);
//    qDebug() << "mClientBuff.mid((lengthOfOrder + lengthOfContent + lenthOfCheck), lengthOfVerifyType) is " << ToolUtil::bytes2HexStr(mClientBuff.mid((lengthOfOrder + lengthOfContent + lenthOfCheck), lengthOfVerifyType));
//    qDebug() << "lengthOfOrder is " << lengthOfOrder;
//    qDebug() << "lengthOfContent is " << lengthOfContent;
//    qDebug() << "lenthOfCheck is " << lenthOfCheck;
//    qDebug() << "lengthOfVerifyType is " << lengthOfVerifyType;
//    qDebug() << "jsonLength is " << jsonLength;
//    qDebug() << "endIndex is " << endIndex;

    DeviceOrder deviceOrder;
    deviceOrder.setOrderType(mClientBuff.mid(0, lengthOfOrder));
    deviceOrder.setMlengthBytes(mClientBuff.mid(lengthOfOrder, lengthOfContent));
    deviceOrder.setVerifyType(mClientBuff.mid((lengthOfOrder + lengthOfContent), lenthOfCheck));
    deviceOrder.setVerifyCode(mClientBuff.mid((lengthOfOrder + lengthOfContent + lenthOfCheck), lengthOfVerifyType));
    deviceOrder.setContent(mClientBuff.mid((lengthOfOrder + lengthOfContent + lenthOfCheck + lengthOfVerifyType), jsonLength));
    deviceOrder.setEnd(mClientBuff.mid(endIndex));

    mClientBuff = mClientBuff.right(mClientBuff.length() - (lengthOfOrder + lengthOfContent + lenthOfCheck + lengthOfVerifyType + jsonLength + 1));

    mpHandler->ReadDataHandler(*this, deviceOrder);
}

void DevClient::netError(QAbstractSocket::SocketError socketError)
{

}

void DevClient::connected()
{
    qDebug() << "与服务器连接成功";
    LOGI("与服务器连接成功");
    emit receiveLog(mpMyLog->addLogs({"与服务器连接成功"}));
    emit devconnect(this->mDevID);

//    QByteArray initArray;
//    initArray.append(PrinterOrder::DEVINIT());
//    initArray.append(QByteArrayLiteral("\x00\x00\x00\x00"));
//    initArray.append(QByteArrayLiteral("\x03\x00\x00"));
//    initArray.append(QByteArrayLiteral("\x24"));

    qDebug() << "返回设备信息给服务器";
    qDebug() << "dev id is " << this->devID();

    QJsonObject devInfoJson;
    devInfoJson.insert("deviceid", this->devID());
    devInfoJson.insert("driver", "zpl");
    devInfoJson.insert("page", "100X180");
    devInfoJson.insert("resolution", "203X203");
    devInfoJson.insert("packageSize", 4096);

    QJsonDocument document;
    document.setObject(devInfoJson);
    QByteArray devBytes = ToolUtil::strCodecTo(document.toJson(), "gb18030");


    QByteArray byteBuf;
    byteBuf.append(PrinterOrder::DEVINFO());
    byteBuf.append(ToolUtil::intToBytes(devBytes.length()));
    byteBuf.append((unsigned char)CRC16CCITT().verifyType());
    byteBuf.append(CRC16CCITT().generateVerifyCode(devBytes));
    byteBuf.append(devBytes);
    byteBuf.append(0x24);

    mpClient->write(byteBuf);
}

void DevClient::disconnected()
{
    qDebug() << "与服务器断开连接";
    LOGI("与服务器断开连接");
    emit receiveLog(mpMyLog->addLogs({"与服务器断开连接"}));
    emit devdisconnect(this->mDevID);
}

void DevClient::hasWritten(qint64 bytes)
{
//    qDebug() << "has writer bytes count is " << bytes;
    LOGIM("has writer bytes count is", QString::number(bytes).toStdString());
    emit receiveLog(mpMyLog->addLogs({"has writer bytes count is", QString::number(bytes)}));
}

void DevClient::writeAndFlush(QByteArray &data)
{
    mpClient->write(data);
    mpClient->flush();
}

void DevClient::writeAndFlush(QByteArray &&data)
{
    mpClient->write(data);
    mpClient->flush();
}

void DevClient::readTimeOut()
{
    qDebug() << "devid: " << devID() << " read Time Out";
    IVerify* pVerify = new CRC16CCITT();
    mpClient->write(ToolUtil::getHeartMsg(pVerify));
    delete pVerify;
}

QString DevClient::devID() const
{
    return mDevID;
}

QString DevClient::logs() const
{
    return mpMyLog->logs();
}
