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
#include "handler/devinfohandler.h"
#include "handler/devstatushandler.h"
#include "handler/heartbeathandler.h"
#include "handler/prndatasavehandler.h"
#include "handler/prninfohandler.h"
#include "handler/resultinfohandler.h"
#include "handler/unknownorderhandler.h"
#include "MyLog.h"

DevClient::DevClient(QObject *parent) : QObject(parent), mpClient(nullptr)
{
    mpClient = new QTcpSocket(this);

    connect(mpClient, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(mpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(netError(QAbstractSocket::SocketError)));
    connect(mpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(mpClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(hasWritten(qint64)));

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

//    qDebug() << "DevId " << mDevID << " born";
    LOGIM("DevId", mDevID.toStdString(), "born");
    emit receiveLog(mpMyLog->addLogs({"DevId", mDevID, "born"}));
}

void DevClient::readData()
{
//    qDebug() << "DevId " << mDevID << "receive dara";
    LOGIM("DevId", mDevID.toStdString(), "receive data");
    emit receiveLog(mpMyLog->addLogs({"DevId", mDevID, "born"}));

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
//    qDebug() << "与服务器连接成功";
    LOGI("与服务器连接成功");
    emit receiveLog(mpMyLog->addLogs({"与服务器连接成功"}));
    emit devconnect(this->mDevID);

    QByteArray initArray;
    initArray.append(PrinterOrder::DEVINIT());
    initArray.append(QByteArrayLiteral("\x00\x00\x00\x00"));
    initArray.append(QByteArrayLiteral("\x03\x00\x00"));
    initArray.append(QByteArrayLiteral("\x24"));

    mpClient->write(initArray);
}

void DevClient::disconnected()
{
//    qDebug() << "与服务器断开连接";
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

QString DevClient::devID() const
{
    return mDevID;
}

QString DevClient::logs() const
{
    return mpMyLog->logs();
}
