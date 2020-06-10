import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import DevServiceQml 1.0

Rectangle {

    id: mainPanel

    ColumnLayout{
        anchors.fill: parent

        ListView {
            id: virtualList

            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: devsDelegate
            model: devsModel
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
        }

        RowLayout {
            Button {
                id: delBtn

                text: "-"

                Layout.alignment: Qt.AlignLeft
            }

            Button {
                id: addBtn

                text: "+"

                Layout.alignment: Qt.AlignRight

                onClicked: {

                }
            }
        }
    }

    Component{
        id: devsDelegate
        Item {
            width: parent.width
            height: 16

            Column {
                Text { text: '<b>devid:</b> ' + devid }
            }

            MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log(index)
                        virtualList.currentIndex = index
                    }
            }
        }
    }

    ListModel {
        id: devsModel
    }

    Connections{
        target: DevService
        onDevConnect: {
            console.log(devId + " connect");
            devsModel.append({"devid":devId})
        }
    }

    Connections{
        target: DevService
        onDevDisConnect: {
            console.log(devId + " disconnect");
            devsModel.remove({"devid":devId})
        }
    }
}
