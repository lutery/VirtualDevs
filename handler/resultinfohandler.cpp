#include "printerorder.h"
#include "resultinfohandler.h"
#include "util/toolutil.h"
#include <QJsonObject>
#include <QJsonParseError>

ResultInfoHandler::ResultInfoHandler(QObject *parent) : AbsHandler(parent)
{

}

ResultInfoHandler::~ResultInfoHandler()
{

}

bool ResultInfoHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    if (deviceOrder.orderType().at(0) != PrinterOrder::RESULTINFO().at(0))
    {
        return false;
    }

    if (!mpVerify->verifyContent(deviceOrder.getVerifyCode(), deviceOrder.getContent()))
    {
        qDebug() << "结果内容校验不通过";
        qDebug() << ToolUtil::bytes2HexStr(deviceOrder.combine());
        return true;
    }

    QJsonParseError json_error;
    QJsonDocument resultInfoDoc = QJsonDocument::fromJson(ToolUtil::strCodecTo(deviceOrder.getContent(), "gb18030", "utf-8"), &json_error);

    if (json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "result info parse error";
        qDebug() << "json error is " << json_error.error;
        return true;
    }

    QJsonObject resultInfoObj = resultInfoDoc.object();
    qDebug() << "result is " << resultInfoObj["result"];

    return true;
}
