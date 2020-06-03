#ifndef ASYNCDEVCLIENT_H
#define ASYNCDEVCLIENT_H

#include <QRunnable>
#include <QString>
#include <QObject>

class DevClient;

class AsyncDevClient : public QObject, public QRunnable
{
    Q_OBJECT
public:
    AsyncDevClient(QString serverIP, quint16 serverPort);
    virtual ~AsyncDevClient();

    QString devID() const;

signals:
    void receiveLog(QString);

protected:
    void run() override;

private:
    QString mServerIP;
    quint16 mServerPort;
    DevClient* mpDevClient = nullptr;
};

#endif // ASYNCDEVCLIENT_H
