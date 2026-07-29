pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

import labPowerSupplyGUI

Item {

    ColumnLayout {

        // StatusLamp {
        //     id: lamp
        //     text: "My text"
        //     state: false
        // }

        StatusLamp {
            id: lamp2
            text: "Connected"
            state: SingletonClass.connectionController.connectedToPsu
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: lamp2.state = !lamp2.state
    }
}
