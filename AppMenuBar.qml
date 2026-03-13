import QtQuick
import QtQuick.Controls

MenuBar {
    Menu {
        title: "File"
        Action {
            text: "&Load CSV-file..."
        }
        MenuSeparator {}
        Action{
            text: "&Quit"
            // onTriggered:
        }

    }

    Menu {
        title: "Edit"
    }

    Menu {
        title: "Help"

        Action {
            text: "&Keybindings"
        }

        Action {
            text: "&About"
        }
    }
}
