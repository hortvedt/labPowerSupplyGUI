pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import labPowerSupplyGUI

// Idea: Do like the physical device and have some memory or programmable settings. E.g. 5V 1A, 12V 5A and 3.3V 0.1A.

Item {
    id: root

    property int labelWidth: 150
    property int valueWidth: 200

    ColumnLayout {
        RowLayout {
            StatusLamp {
                text: "Output on"
                state: SingletonClass.psuController.outputOn
            }

            Button {
                text: "Toggle output"
                enabled: true

                onClicked: {
                    console.log("Turning", setCurrent.value ? "on" : "off")
                    SingletonClass.psuController.setOutput(!SingletonClass.psuController.outputOn)
                }
            }
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
                text: "Maximum voltage"
            }

            Label {
                Layout.preferredWidth: root.labelWidth
                text: SingletonClass.psuController.valueSetVoltage
            }

            SpinBox {
                id: setVoltage

                Layout.preferredWidth: root.valueWidth
                from: 0
                to: 30
                stepSize: 1
                value: 0
                editable: true

                contentItem: Text {
                    text: setVoltage.value
                    horizontalAlignment: Text.AlignLeft
                    color: parent.palette.text
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
                text: "Maximum current"
            }

            Label {
                Layout.preferredWidth: root.labelWidth
                text: SingletonClass.psuController.valueSetCurrent
            }

            SpinBox {
                id: setCurrent

                Layout.preferredWidth: root.valueWidth
                from: 0
                to: 5
                stepSize: 1
                value: 0
                editable: true

                contentItem: Text {
                    text: setCurrent.value
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

    // MouseArea {
    //     anchors.fill: parent
    //     onClicked: lamp2.state = !lamp2.state
    // }
}
