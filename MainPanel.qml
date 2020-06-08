import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import DevServiceQml 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property int devNum: 1
    property string hostIp: "serverprinter.com.cn"
    property int hostPort: 9100
    property bool isInit: false

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

    onVisibleChanged: {
        if (visible && !isInit){
            console.log("start init")

            devService.initService(hostIp, hostPort, devNum)
        }
    }

    Component.onCompleted: {
        console.log("devNum:", devNum, "hostIp:", hostIp, "hostPort:", hostPort)
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
