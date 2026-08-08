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

                    onTextEdited: {
                        SingletonClass.connectionController.port = text
                    }
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

                    contentItem: Text {
                        text: baudrateBox.value
                        horizontalAlignment: Text.AlignLeft
                        // color: parent.palette.text
                    }

                    onValueModified: {
                        SingletonClass.connectionController.baudrate = value
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
                    value: 100

                    contentItem: Text {
                        text: timeoutBox.value
                        horizontalAlignment: Text.AlignLeft
                        // color: parent.palette.text
                    }

                    onValueModified: {
                        SingletonClass.connectionController.timeOutTime = value
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

        ColumnLayout {
            Button {
                text: "Connect to serial"
                enabled: true

                onClicked: {
                    console.log("Connecting serial")
                    SingletonClass.connectionController.connectToSerial()
                }
            }

            Button {
                text: "Connect to psu"
                enabled: SingletonClass.connectionController.connectedToSerial

                onClicked: {
                    console.log("Connecting psu")
                    SingletonClass.connectionController.connectToPsu()
                }
            }
        }
    }
}
