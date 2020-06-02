import QtQuick 2.0

Rectangle {

    signal switchDev(string devid)

    Text {
        id: logTxt

        anchors.fill: parent

        text: "日志窗口"
    }

    onSwitchDev: {
        // 这里调用c++接口 请求切换设备
        // 这里使用与c++层进行信号连接接收新设备的日志信息
    }

}
