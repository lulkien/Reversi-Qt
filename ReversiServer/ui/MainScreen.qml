import QtQuick 2.0
import Qt.labs.platform 1.1
import "components"

Item {
    id: root
    width: 480
    height: 640

    Button {
        id: btn_new_key
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 5
        }

        width: parent.width - 10
        backgroundColor: "#40BDFF"

        Text {
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
            color: "#2a2a2a"
            text: "Refresh key"
        }

        onClicked: {
            ReversiServer.generateNewKey()
        }
    }

    Frame {
        id: key_holder
        anchors {
            top: btn_new_key.bottom
            topMargin: 5
        }

        width: parent.width
        height: 50
        margins: [ 5 ]
        backgroundColor: "lightgray"
        borderRadius: 15

        Text {
            id: room_key
            property bool hidden: true
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 20
            color: "#3a3a3a"
            text: hidden ? "######" : ReversiServer.roomKey
            renderType: Text.NativeRendering
        }

        MouseArea {
            anchors.fill: parent
            onPressAndHold: {
                room_key.hidden = !room_key.hidden
            }

            onDoubleClicked: {
                ReversiServer.sendKeyToClipBoard()
            }
        }
    }

    Frame {
        id: player_holder
        anchors.top: key_holder.bottom
        width: parent.width
        height: 200
        margins: [ 5 ]
        backgroundColor: "lightgray"
        borderRadius: 15

        Item {
            id: player_1_info
            width: parent.width / 2
            height: parent.height

        }
    }
}
