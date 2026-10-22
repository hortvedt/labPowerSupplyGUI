import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    required property string text
    required property string value
    property int labelWidth
    property alias textLabel: textLabel
    property alias valueLabel: valueLabel

    Label {
        id: textLabel

        text: root.text
        Layout.preferredWidth: root.labelWidth ?? implicitWidth
    }

    Label {
        id: valueLabel

        text: root.value
        Layout.preferredWidth: root.labelWidth ?? implicitWidth
    }
}
