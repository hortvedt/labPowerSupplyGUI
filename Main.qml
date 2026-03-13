import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: ("Lab Power Supply GUI")

    menuBar: AppMenuBar{}
    header: AppTabBar{}

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: filler
    }

    Component {
        id: filler
        Label {
            text: "Hei"
        }
    }
}
