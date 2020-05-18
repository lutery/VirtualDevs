#include "devinit.h"
#include <iostream>
#include <string>
#include "util/toolutil.h"

using namespace std;

DevInit::DevInit(QObject *parent) : QObject(parent)
{

}

ostream & operator<<(ostream &out, DevInit& devInit)
{
    out << "devNumbers is " << devInit.mDevCount << std::endl;
    out << "serverIp is " << devInit.mServerIP.toStdString() << std::endl;
    out << "serverPort is " << devInit.mServerPort << std::endl;

    return out;
}

void DevInit::initParam()
{
    cout << "please enter how number dev: ";

    std::string inputStr;
    char inputChar[1024];
    memset(inputChar, 0, 1024);
    getline(cin,inputStr);

    int devNumbers = ToolUtil::toInt(inputStr);
    if (devNumbers < 0 || devNumbers > 100)
    {
        cout << "enter an incorrect number, default devNumbers is 1";
        devNumbers = 1;
    }

    mDevCount = devNumbers;

    cout << endl << "please enter server ip(default serverprinter.com.cn):";

    std::string serverIP;
    getline(cin, serverIP);

    if (serverIP.length() > 5)
    {
        mServerIP = QString::fromStdString(serverIP);
    }

    cout << endl << "please enter server port(default port is 9100):";

    inputStr = "";

    getline(cin, inputStr);

    int serverPort = ToolUtil::toInt(inputStr);

    if (serverPort > 0)
    {
        mServerPort = serverPort;
    }
}

QString DevInit::serverIP() const
{
    return mServerIP;
}

int DevInit::serverPort() const
{
    return mServerPort;
}

int DevInit::devCount() const
{
    return mDevCount;
}
