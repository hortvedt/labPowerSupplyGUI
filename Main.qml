import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: ("Lab Power Supply GUI")

    menuBar: AppMenuBar{}
    header: AppTabBar{}
    // footer: AppToolBar{}

    StackLayout {
        id: stack
        anchors.fill: parent
        currentIndex: 0

        ConnectingTab {
        }
        StandardTab {
        }
        StandardTab {
        }
        StandardTab {
        }
    }

    Component {
        id: filler
        Label {
            text: "Hei"
        }
    }
}
