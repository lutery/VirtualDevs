import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import DevServiceQml 1.0

Window {
    id: mainPanel
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    signal initDev
    signal switchDev(string devid)

    property int devNum: 1
    property string hostIp: "startprinter.com.cn"
    property int hostPort: 9100

    RowLayout {
        anchors.fill: parent

        VirtualDevs {
            Layout.fillHeight: true
            Layout.fillWidth: true

            onDevSwitch: {
                mainPanel.switchDev(devid)
            }
        }

        DevInfo {
            id: devInfo
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    onSwitchDev: {
        devInfo.switchDev(devid)
    }

    onDevNumChanged: {
        console.log("dev number change " + devNum)
    }

    onInitDev: {
        console.log("start init")
        console.log("devNum:", devNum, "hostIp:", hostIp, "hostPort:", hostPort)
        DevService.initService(hostIp, hostPort, devNum)
    }

//    Connections {
//        target: DevService
//        onReceiveLog: {
//           console.log("log: " + log)
//        }
//    }

//    DevService{
//        id: devService

//        onDevConnect: {
//            console.log(devId + " connect")
//        }

//        onDevDisconnect: {
//            console.log(devId + " disconnect")
//        }

//        onReceiveLog: {
//            console.log("log: " + log)
//        }
//    }
}
