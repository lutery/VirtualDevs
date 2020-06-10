import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import DevServiceQml 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    signal initDev

    property int devNum: 1
    property string hostIp: "startprinter.com.cn"
    property int hostPort: 9100

    RowLayout {
        anchors.fill: parent

        VirtualDevs {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DevInfo {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    onDevNumChanged: {
        console.log("dev number change " + devNum)
    }

    onInitDev: {
        console.log("start init")
        console.log("devNum:", devNum, "hostIp:", hostIp, "hostPort:", hostPort)
        devService.initService(hostIp, hostPort, devNum)
    }

    DevService{
        id: devService

        onDevConnect: {
            console.log(devId + " connect")
        }

        onDevDisconnect: {
            console.log(devId + " disconnect")
        }
    }
}
