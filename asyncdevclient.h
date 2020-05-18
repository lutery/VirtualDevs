#ifndef ASYNCDEVCLIENT_H
#define ASYNCDEVCLIENT_H

#include <QRunnable>
#include <QString>

class AsyncDevClient : public QRunnable
{
public:
    AsyncDevClient(QString serverIP, quint16 serverPort);

protected:
    void run() override;

private:
    QString mServerIP;
    quint16 mServerPort;
};

#endif // ASYNCDEVCLIENT_H
