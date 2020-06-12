#ifndef DEVCLIENT_H
#define DEVCLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QMutex>

class QTcpSocket;
class AbsHandler;
class MyLog;
class QTimer;

class DevClient : public QObject
{
    Q_OBJECT
public:
    explicit DevClient(QObject *parent = nullptr);
    virtual ~DevClient() override;
    void initDevice(QString serverIP, quint16 serverPort);

    QString devID() const;
    QString logs() const;

signals:
    void finish();
    void receiveLog(QString);
    void devconnect(QString);
    void devdisconnect(QString);
    void rTimeOut();

public slots:
    void readData();
    void netError(QAbstractSocket::SocketError socketError);
    void connected();
    void disconnected();
    void hasWritten(qint64 bytes);
    void writeAndFlush(QByteArray& data);
    void writeAndFlush(QByteArray&& data);

protected:
    void readTimeOut();

private:
    QTimer* mReadTimer = nullptr;
    QString mServerIP;
    quint16 mServerPort;
    MyLog* mpMyLog = nullptr;
    AbsHandler* mpHandler;
    QTcpSocket* mpClient;
    QByteArray mClientBuff;
    QMutex mBuffLock;
    QString mDevID;
};

#endif // DEVCLIENT_H
