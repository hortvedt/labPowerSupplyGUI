pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    required property string text
    required property bool state

    spacing: 10

    Label {
        text: root.text
    }

    LedIndicator {
        active: root.state
        Layout.preferredWidth: implicitWidth
        Layout.preferredHeight: implicitHeight
    }
}
