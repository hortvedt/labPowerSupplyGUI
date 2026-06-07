import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

MenuBar {
    Menu {
        title: "File"
        Action {
            text: "&Open CSV-file..."
            onTriggered: {
                fileDialog.open()
            }
        }
        MenuSeparator {}
        Action{
            text: "&Quit"
            onTriggered: {
                Qt.callLater( Qt.quit )
            }
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

    FileDialog {
        id: fileDialog

        title: "Please choose a file"
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        nameFilters: ["CSV files (*.csv)", "Text files (*.txt)", "All file (*)"]
        fileMode: FileDialog.OpenFile

        onAccepted: {
            // let fileUrl = selectedFile.toString()
            // let localPath = fileUrl.toString().replace(/^(file:\/{3})|(file:)/, "");

            console.log("Selected file path: ", selectedFile )
        }

        onRejected: {
            console.log("Dialog cancelled")
        }
    }
}
