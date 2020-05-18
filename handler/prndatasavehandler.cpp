#include "printerorder.h"
#include "prndatasavehandler.h"
#include "util/toolutil.h"
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QDataStream>

PrnDataSaveHandler::PrnDataSaveHandler(QObject *parent) : AbsHandler(parent)
{

}

bool PrnDataSaveHandler::handle(DevClient &devClient, DeviceOrder &deviceOrder)
{
    if (deviceOrder.orderType().at(0) != PrinterOrder::PRNDATA().at(0))
    {
        return false;
    }

    QString curTempName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss:zzz") + ".prn";
    QString tempFilePath = QDir::tempPath() + "\\" + curTempName;

    QFile tempFile(tempFilePath);
    if (tempFile.open(QIODevice::WriteOnly))
    {
        QDataStream dataS(&tempFile);
        dataS.setVersion(QDataStream::Qt_5_12);
        dataS << deviceOrder.getContent();
        tempFile.flush();
        tempFile.close();
    }
    else
    {
        qDebug() << "open file failed";
        qDebug() << "tempFilePath is " << tempFilePath;
    }

    devClient.writeAndFlush(ToolUtil::getResultMsg("ok", mpVerify));

    return true;
}
