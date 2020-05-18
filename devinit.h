#ifndef DEVINIT_H
#define DEVINIT_H

#include <QObject>
#include <iostream>

class DevInit : public QObject
{
    Q_OBJECT
public:
    explicit DevInit(QObject *parent = nullptr);

    friend std::ostream &operator<<(std::ostream& out, DevInit& devInit);

    int devCount() const;

    int serverPort() const;

    QString serverIP() const;

signals:

public slots:
    void initParam();

private:
    int mDevCount = 100;
    int mServerPort = 9100;
    QString mServerIP = "startprinter.com.cn";
//    QString mServerIP = "localhost";
};

#endif // DEVINIT_H
