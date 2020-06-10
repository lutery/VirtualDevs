import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    id: configWin
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property var mainPanel

    ColumnLayout {
        RowLayout {
            Text {
                text: qsTr("请输入虚拟设备数量:")
            }

            TextEdit {
                id: numDev
                text: "1"
            }
        }

        RowLayout {
            Text {
                text: qsTr("请输入测试主机域名IP:")
            }

            TextEdit {
                id: serverIP
//                text: "startprinter.com.cn"
                text: "localhost"
            }
        }

        RowLayout {
            Text {
                text: qsTr("请输入测试主机端口:")
            }

            TextEdit {
                id: serverPort
                text: "9100"
            }
        }

        RowLayout{
            Button {
                text: "确定"
                onClicked: {
//                    configWin.hide()
                    var component = Qt.createComponent("MainPanel.qml")
                    mainPanel = component.createObject()
                    mainPanel.devNum = numDev.text
                    mainPanel.hostIp = serverIP.text
                    mainPanel.hostPort = serverPort.text
                    mainPanel.initDev()
                    mainPanel.show()
                    configWin.close()
                }
            }

            Button {
                text: "取消"
                onClicked: {
                    Qt.quit()
                }
            }
        }
    }

}
