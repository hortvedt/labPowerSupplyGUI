import QtQuick
import QtQuick.Controls

import labPowerSupplyGUI

TabBar{
        TabButton {
            text: "Connect"
            onClicked: {
                SingletonClass.applicationController.tab = ApplicationController.Tab.Connect
            }
        }

        TabButton {
            text: "Standard"
            onClicked: {
                SingletonClass.applicationController.tab = ApplicationController.Tab.Standard
            }
        }

        TabButton {
            text: "CSV"
            onClicked: {
                SingletonClass.applicationController.tab = ApplicationController.Tab.CSV
            }
        }

        TabButton {
            text: "Battery charger"
            onClicked: {
                SingletonClass.applicationController.tab = ApplicationController.Tab.BatteryCharger
            }
        }

        TabButton {
            text: "Free serial"
            onClicked: {
                SingletonClass.applicationController.tab = ApplicationController.Tab.FreeSerial
            }
        }
}
