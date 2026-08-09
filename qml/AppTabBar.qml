import QtQuick
import QtQuick.Controls

import labPowerSupplyGUI

TabBar {
    TabButton {
        text: "Connect"
        enabled: true
        checked: SingletonClass.applicationController.tab === ApplicationController.Tab.Connect

        onClicked: {
            SingletonClass.applicationController.tab = ApplicationController.Tab.Connect
        }
    }

    TabButton {
        text: "Standard"
        // enabled: SingletonClass.connectionController.connectedToPsu
        checked: SingletonClass.applicationController.tab === ApplicationController.Tab.Standard

        onClicked: {
            SingletonClass.applicationController.tab = ApplicationController.Tab.Standard
        }
    }

    TabButton {
        text: "CSV"
        // enabled: SingletonClass.connectionController.connectedToPsu
        checked: SingletonClass.applicationController.tab === ApplicationController.Tab.CSV

        onClicked: {
            SingletonClass.applicationController.tab = ApplicationController.Tab.CSV
        }
    }

    TabButton {
        text: "Battery charger"
        enabled: SingletonClass.connectionController.connectedToPsu
        checked: SingletonClass.applicationController.tab === ApplicationController.Tab.BatteryCharger

        onClicked: {
            SingletonClass.applicationController.tab = ApplicationController.Tab.BatteryCharger
        }
    }

    TabButton {
        text: "Free serial"
        enabled: SingletonClass.connectionController.connectedToSerial
        checked: SingletonClass.applicationController.tab === ApplicationController.Tab.FreeSerial

        onClicked: {
            SingletonClass.applicationController.tab = ApplicationController.Tab.FreeSerial
        }
    }
}
