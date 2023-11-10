import QtQuick 2.0
import QtGraphicalEffects 1.12
import "../javascript/func.js" as Func

Item {
    id: root
    property double radius: 15
    property string backgroundColor: "#eaeaea"
    property string hoveredColor: Func.darker(backgroundColor, 20)
    property string pressedColor: Func.brighter(backgroundColor, 20)

    width: 100
    height: 50

    signal clicked()
    signal pressed()
    signal released()

    QtObject {
        id: self
        property bool isHovered: false
        property bool isPressed: false
    }

    Rectangle {
        id: bg
        anchors.fill: parent
        radius: root.radius
        color: self.isPressed ? root.pressedColor
                              : self.isHovered ? root.hoveredColor
                                               : root.backgroundColor
    }
    DropShadow {
        anchors.fill: bg
        horizontalOffset: 4
        verticalOffset: 4
        radius: 5
        color: "#5f5f5f"
        source: bg
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: root.clicked()
        onEntered: self.isHovered = true
        onExited: self.isHovered = false

        onPressed: {
            self.isPressed = true
            root.pressed()
        }

        onReleased: {
            self.isPressed = false
            root.released()
        }
    }
}
