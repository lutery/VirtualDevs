import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

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
}
