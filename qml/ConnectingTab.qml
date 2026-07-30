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
            RowLayout {
                Label {
                    Layout.preferredWidth: root.labelWidth
                    text: "Port"
                }

                TextField {
                    Layout.preferredWidth: root.boxWidth
                    placeholderText: "Enter port ( /dev/ttyUSB0 )"
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: root.labelWidth
                    text: "Baudrate"
                }

                SpinBox {
                    id: baudrateBox

                    Layout.preferredWidth: root.boxWidth
                    from: 1
                    to: 921600
                    stepSize: 100
                    value: 9600

                    // onValueChanged: baudrate = value

                    contentItem: Text {
                        text: baudrateBox.value
                        horizontalAlignment: Text.AlignLeft
                        color: parent.palette.text
                    }
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: root.labelWidth
                    text: "Timeout"
                }

                SpinBox { // Use simpleTimeout
                    id: timeoutBox

                    Layout.preferredWidth: root.boxWidth
                    from: 0
                    to: 1000
                    stepSize: 50
                    value: 0

                    contentItem: Text {
                        text: timeoutBox.value
                        horizontalAlignment: Text.AlignLeft
                        color: parent.palette.text
                    }
                }
            }

            LabelComboBox {
                labelWidth: root.labelWidth
                boxWidth: root.boxWidth
                text: "Byte size"
                model: SingletonClass.connectionController.bytesizeCombo
            }

            LabelComboBox {
                labelWidth: root.labelWidth
                boxWidth: root.boxWidth
                text: "Parity"
                model: SingletonClass.connectionController.parityCombo
            }

            LabelComboBox {
                labelWidth: root.labelWidth
                boxWidth: root.boxWidth
                text: "Stop bits"
                model: SingletonClass.connectionController.stopbitsCombo
            }

            LabelComboBox {
                labelWidth: root.labelWidth
                boxWidth: root.boxWidth
                text: "Flow control"
                model: SingletonClass.connectionController.flowcontrolCombo
            }
        }

        Button {
            text: "Connect"

            onClicked: {
                console.log("Clicked")
            }
        }
    }
}
