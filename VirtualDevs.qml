import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12

Rectangle {

    id: mainPanel

    ColumnLayout{
        anchors.fill: parent

        ListView {
            id: virtualList

            Layout.fillWidth: true
            Layout.fillHeight: true
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
            }
        }
    }

}
