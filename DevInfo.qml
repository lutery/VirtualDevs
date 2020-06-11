import QtQuick 2.0
import QtQuick.Controls 2.12
import DevServiceQml 1.0

Rectangle {

    signal switchDev(string devid)

//    ScrollView {
//            id: scroll
////            anchors.centerIn: parent
//            anchors.fill: parent
////            width: 200; height: 24 // 初始高度就是一行
//            background: Rectangle {
//                anchors.fill: parent
//                border.color: "gray"
//                radius: 5
//            }

//            TextArea {
//                id: logTxt
//                property int preContentHeight: 0
//                text: "日志窗口"
//                wrapMode: TextArea.Wrap
//                selectByMouse: true
//                onContentHeightChanged: {
//                    //每一行为高度为14， 当输入大于3行的时候自动滚动
//                    if(contentHeight > 14 && contentHeight < 56) {
//                        if(contentHeight != preContentHeight) {
//                            preContentHeight = contentHeight;
//                            scroll.height += 14;
//                        }
//                    }
//                }
//            }
//        }

//    ScrollView{
//        id: scroll
//        anchors.fill: parent

        Text {
            id: logTxt

            anchors.fill: parent

            wrapMode: Text.Wrap
            text: "日志窗口"
        }
//    }

    onSwitchDev: {
        // 这里调用c++接口 请求切换设备
        // 这里使用与c++层进行信号连接接收新设备的日志信息
        DevService.switchDevLog(devid)
    }

    Connections {
        target: DevService
        onReceiveLog: {
           console.log("log: " + log)
           logTxt.text = logTxt.text + "\n\n" + log
        }
    }
}
