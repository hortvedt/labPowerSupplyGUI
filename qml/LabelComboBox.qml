import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import labPowerSupplyGUI

RowLayout {
    id: root

    required property ComboBoxModel model
    property string text: ""
    property int labelWidth: label.implicitWidth
    property int boxWidth: comboBox.implicitWidth

    Label {
        id: label

        text: root.text
        Layout.preferredWidth: root.labelWidth
    }

    ComboBox {
        id: comboBox
        model: root.model
        textRole: "TextRole"
        Layout.preferredWidth: root.boxWidth
    }

}

