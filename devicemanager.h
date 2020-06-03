#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QVector>

class AsyncDevClient;
class DevInit;

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

signals:
    void finish();
    void receiveLog(QString);

public slots:

private:
    int mDevCount;
    QString mServerIP;
    int mServerPort;
    QVector<AsyncDevClient*> mDevs;
    static DeviceManager* gpInstance;
};

#endif // DEVICEMANAGER_H
