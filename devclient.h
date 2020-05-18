#ifndef DEVCLIENT_H
#define DEVCLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QMutex>

class QTcpSocket;
class AbsHandler;

class DevClient : public QObject
{
    Q_OBJECT
public:
    explicit DevClient(QObject *parent = nullptr);
    virtual ~DevClient() override;
    void initDevice(QString serverIP, quint16 serverPort);

    QString devID() const;

signals:
    void finish();

public slots:
    void readData();
    void netError(QAbstractSocket::SocketError socketError);
    void connected();
    void disconnected();
    void hasWritten(qint64 bytes);
    void writeAndFlush(QByteArray& data);
    void writeAndFlush(QByteArray&& data);

private:
    QString mServerIP;
    quint16 mServerPort;
    AbsHandler* mpHandler;
    QTcpSocket* mpClient;
    QByteArray mClientBuff;
    QMutex mBuffLock;
    QString mDevID;
};

#endif // DEVCLIENT_H
