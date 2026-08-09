import QtQuick

Item {
    StatusLamp {
        text: "Output on"
        state: SingletonClass.psuController.outputOn
    }
}
