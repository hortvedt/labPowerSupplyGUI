import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import labPowerSupplyGUI

RowLayout {
    Label {
        text: "Important information"
    }

    Label {
        text: SingletonClass.psuController.identification
    }

    Label {
        text: "Last error from serial connection: "
    }
}

