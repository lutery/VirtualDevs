#include "printerorder.h"
#include "prninfohandler.h"
#include "verify/iverify.h"
#include "util/toolutil.h"

#include <QJsonParseError>
#include <QJsonObject>

PrnInfoHandler::PrnInfoHandler(QObject *parent) : AbsHandler(parent)
{

}

bool PrnInfoHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    if (deviceOrder.orderType().at(0) != PrinterOrder::PRNINFO().at(0))
    {
        return false;
    }

    if (!mpVerify->verifyContent(deviceOrder.getVerifyCode(), deviceOrder.getContent()))
    {
        qDebug() << "prn信息校验失败";
        return true;
    }

    QJsonParseError json_error;
    QJsonDocument prnInfoDoc = QJsonDocument::fromJson(ToolUtil::strCodecTo(deviceOrder.getContent(), "gb18030", "utf-8"), &json_error);

    if (json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "prn info parse error";
        qDebug() << "json error is " << json_error.error;
        qDebug() << "device order is " << ToolUtil::bytes2HexStr(deviceOrder.combine());
        return true;
    }

    QJsonObject prnInfo = prnInfoDoc.object();
    qDebug() << "prn id is " << prnInfo["prnid"] << ", prn size is " << prnInfo["size"];

    devClient.writeAndFlush(ToolUtil::getResultMsg("ok", mpVerify));

    return true;
}
