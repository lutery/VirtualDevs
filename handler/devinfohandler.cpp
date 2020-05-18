#include "devinfohandler.h"
#include "util/toolutil.h"
#include "printerorder.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "verify/iverify.h"

DevInfoHandler::DevInfoHandler(QObject *parent):AbsHandler (parent)
{

}

DevInfoHandler::~DevInfoHandler()
{

}

bool DevInfoHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    if (deviceOrder.orderType().at(0) != 0x10)
    {
        return false;
    }

    qDebug() << "返回设备信息给服务器";
    qDebug() << "dev id is " << devClient.devID();

    QString devId = devClient.devID();

    QJsonObject devInfoJson;
    devInfoJson.insert("deviceid", devId);

    QJsonDocument document;
    document.setObject(devInfoJson);
    QByteArray devBytes = ToolUtil::strCodecTo(document.toJson(), "gb18030");


    QByteArray byteBuf;
    byteBuf.append(PrinterOrder::DEVINFO());
    byteBuf.append(ToolUtil::intToBytes(devBytes.length()));
    byteBuf.append((unsigned char)mpVerify->verifyType());
    byteBuf.append(mpVerify->generateVerifyCode(devBytes));
    byteBuf.append(devBytes);
    byteBuf.append(0x24);

    devClient.writeAndFlush(byteBuf);

    return true;
}
