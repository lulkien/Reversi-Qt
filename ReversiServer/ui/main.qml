import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 480
    height: 640
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    visible: true
    title: qsTr("Reversi Server")

    MainScreen {
        id: mainscreen
    }
}
