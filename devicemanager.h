#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QMap>

class AsyncDevClient;
class DevInit;
class DevClient;

class DeviceManager : public QObject
{
    Q_OBJECT
protected:
    explicit DeviceManager(QObject *parent = nullptr);
    explicit DeviceManager(DevInit& devInit, QObject* parent = nullptr);

public:
    static DeviceManager* getInstance(DevInit& devInit);
    static DeviceManager* getInstance();
    ~DeviceManager();

    void switchDev(QString devId);
    QString requestDevLog(QString devId);

signals:
    void finish();
    void receiveLog(QString);
    void sdevConnect(QString devId);
    void sdevDisconnect(QString devId);

public slots:
    void devConnect(QString devId);
    void devDisconnect(QString devId);

private:
    int mDevCount;
    QString mServerIP;
    int mServerPort;
    AsyncDevClient* mpCurDev = nullptr;
    QMap<QString, AsyncDevClient*> mDevs;
    static DeviceManager* gpInstance;
};

#endif // DEVICEMANAGER_H
