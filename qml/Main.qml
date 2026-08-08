import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import labPowerSupplyGUI

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: ("Lab Power Supply GUI")

    menuBar: AppMenuBar{}
    header: AppTabBar{}
    footer: StatusInformation{}

    StackLayout {
        id: stack
        anchors.fill: parent
        currentIndex: SingletonClass.applicationController.tab

        ConnectingTab {
        }
        StandardTab {
        }
        CsvTab {
        }
        BatteryChargerTab {
        }
        FreeSerialTab {
        }
    }
}
