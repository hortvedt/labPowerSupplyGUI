pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import labPowerSupplyGUI

Item {
    id: root

    property int labelWidth: 100
    property int valueWidth: 200

    ColumnLayout {
        StatusLamp {
            text: "Output on"
            state: SingletonClass.psuController.outputOn
        }

        RowLayout {
            Label {
                text: "Voltage"
                Layout.preferredWidth: root.labelWidth
            }

            Label {
                text: SingletonClass.psuController.voltage
                Layout.preferredWidth: root.labelWidth
            }

            StatusLamp {
                text: "Voltage limited"
                state: SingletonClass.psuController.outputOn
            }
        }

        RowLayout {
            Label {
                text: "Current"
                Layout.preferredWidth: root.labelWidth
            }

            Label {
                text: SingletonClass.psuController.current
                Layout.preferredWidth: root.labelWidth
            }

            StatusLamp {
                text: "Current limited"
                state: SingletonClass.psuController.currentLimited
            }
        }

        RowLayout {
            Label {
                Layout.preferredWidth: root.labelWidth
                text: "Set voltage"
            }

            SpinBox {
                id: setVoltage

                Layout.preferredWidth: root.valueWidth
                from: 0
                to: 30
                stepSize: 1
                value: 0

                contentItem: Text {
                    text: setVoltage.value
                    horizontalAlignment: Text.AlignLeft
                    // color: parent.palette.text
                }

                onValueModified: {
                    SingletonClass.psuController.setTempVoltage(value)
                }
            }

            Button {
                text: "Send new value"
                enabled: SingletonClass.psuController.tempDifferentFromSetVoltage

                onClicked: {
                    console.log("Setting voltage to", setVoltage.value)
                    SingletonClass.psuController.setVoltage(setVoltage.value)
                }
            }
        }

        RowLayout {
            Label {
                Layout.preferredWidth: root.labelWidth
                text: "Set current"
            }

            SpinBox {
                id: setCurrent

                Layout.preferredWidth: root.valueWidth
                from: 0
                to: 5
                stepSize: 1
                value: 0

                contentItem: Text {
                    text: setVoltage.value
                    horizontalAlignment: Text.AlignLeft
                    color: parent.palette.text
                }

                onValueModified: {
                    SingletonClass.psuController.setTempCurrent(value)
                }
            }

            Button {
                text: "Send new value"
                enabled: SingletonClass.psuController.tempDifferentFromSetCurrent

                onClicked: {
                    console.log("Setting voltage to", setCurrent.value)
                    SingletonClass.psuController.setCurrent(setCurrent.value)
                }
            }
        }
    }

    //     StatusLamp {
    //         id: lamp2
    //         text: "Connected"
    //         state: SingletonClass.connectionController.connectedToPsu
    //     }
    // }

    // MouseArea {
    //     anchors.fill: parent
    //     onClicked: lamp2.state = !lamp2.state
    // }
}
