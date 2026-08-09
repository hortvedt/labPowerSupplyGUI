pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls

// This visual was AI created and corrected by a human (me)

Rectangle {
    id: root

    property bool active: false
    property color activeColor: "#00ff00"
    property color inactiveColor: "#330000"
    property color glowColor: activeColor
    property int size: 20
    property real intensity: 1.0
    property real glowScale: 1.5  // How much larger the glow is compared to the main circle

    // Optional click handler
    signal clicked

    // Calculate total dimensions including glow
    implicitWidth: size * glowScale
    implicitHeight: size * glowScale
    radius: (size / 2) * glowScale  // Maintain proportional radius
    color: "transparent"  // Make root transparent so only the glow and main circle are visible

    // The main circle (centered within the expanded bounds)
    Rectangle {
        id: mainCircle

        anchors.centerIn: parent
        width: root.size
        height: root.size
        radius: width / 2
        color: root.active ? root.activeColor : root.inactiveColor

        // Color transition animation
        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }

        // Pulse animation for active state (optional)
        SequentialAnimation on opacity {
            id: pulseAnimation

            running: root.active && root.intensity > 0.5
            loops: Animation.Infinite

            NumberAnimation {
                to: 0.7
                duration: 500
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                to: 1.0
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }

        // Inner highlight (lens effect)
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            opacity: 0.8

            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: root.active ? Qt.lighter(root.activeColor, 1.5) : Qt.lighter(root.inactiveColor, 1.2)
                }

                GradientStop {
                    position: 0.7
                    color: root.active ? root.activeColor : root.inactiveColor
                }

                GradientStop {
                    position: 1.0
                    color: root.active ? Qt.darker(root.activeColor, 1.3) : Qt.darker(root.inactiveColor, 1.1)
                }
            }
        }

        // Specular highlight
        Rectangle {
            x: parent.width * 0.2
            y: parent.height * 0.15
            width: parent.width * 0.4
            height: parent.height * 0.25
            radius: width / 2
            color: "white"
            opacity: root.active ? 0.6 * root.intensity : 0.2
            rotation: 45
        }

        // Tooltip
        ToolTip {
            id: tooltip

            text: root.active ? "Active" : "Inactive"
            visible: mouse.containsMouse
            delay: 500
        }

        MouseArea {
            id: mouse

            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: root.clicked()
        }
    }

    // Outer glow effect - now properly contained within the expanded bounds
    Rectangle {
        id: glow

        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: width / 2
        color: root.active ? root.activeColor : "transparent"
        opacity: root.active ? 0.3 * root.intensity : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }
}
