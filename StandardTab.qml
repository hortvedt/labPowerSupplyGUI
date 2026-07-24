pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

Item {

    ColumnLayout {

        StatusLamp {
            id: lamp
            text: "My text"
            state: false
        }

        StatusLamp {
            id: lamp2
            text: "Connected"
            state:
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: lamp.state = !lamp.state
    }
}
