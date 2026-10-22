import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import labPowerSupplyGUI

Item {
    id: root

    property int labelWidth: 100
    property int boxWidth: 200

    RowLayout {
        spacing: 50

        ColumnLayout {
            StatusLamp {
                text: "Charging"
                state: SingletonClass.bcController.chargingOn
            }

            // RowLayout {
            //     Label {
            //         text: "Battery voltage"
            //         Layout.preferredWidth: root.labelWidth
            //     }

            //     Label {
            //         text: SingletonClass.bcController.batteryVoltage
            //         Layout.preferredWidth: root.labelWidth
            //     }
            // }

            // LabelTextValue {
            //     text: "Charging voltage"
            //     value: SingletonClass.bcController.voltage
            //     labelWidth: root.labelWidth
            // }
        }
    }
}
