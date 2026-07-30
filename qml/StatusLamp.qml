pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    required property string text
    required property bool state

    RowLayout {
        spacing: 10

        Label {
            text: root.text
        }

        LedIndicator {
            active: root.state
        }
    }
}
