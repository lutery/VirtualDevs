#include "devstatushandler.h"
#include "printerorder.h"
#include "devicestatus.h"
#include "util/toolutil.h"
#include <random>
#include <QJsonDocument>
#include <QJsonObject>

DevStatusHandler::DevStatusHandler(QObject *parent) : AbsHandler(parent)
{

}

DevStatusHandler::~DevStatusHandler()
{

}

bool DevStatusHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    if (deviceOrder.orderType().at(0) != PrinterOrder::GETDEVSTATUS().at(0))
    {
        return false;
    }

    qDebug() << "服务器请求设备状态";

    std::default_random_engine random;
    QMetaEnum statusEnum = QMetaEnum::fromType<DeviceStatus::StatusEnum>();

    int status = statusEnum.keyToValue(statusEnum.key(ToolUtil::genRangeInt(0, statusEnum.keyCount())));

    qDebug() << "cur status is " << status;

    QJsonObject devStatusJson;
    devStatusJson.insert("status", status);

    QJsonDocument document;
    document.setObject(devStatusJson);
    QByteArray statusBytes = ToolUtil::strCodecTo(document.toJson(), "gb18030");

    QByteArray byteBuf;
    byteBuf.append(PrinterOrder::DEVSTATUS());
    byteBuf.append(ToolUtil::intToBytes(statusBytes.length()));
    byteBuf.append((unsigned char)mpVerify->verifyType());
    byteBuf.append(mpVerify->generateVerifyCode(statusBytes));
    byteBuf.append(statusBytes);
    byteBuf.append(0x24);

    devClient.writeAndFlush(byteBuf);

    return true;
}
