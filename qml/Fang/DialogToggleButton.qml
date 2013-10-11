import QtQuick 1.1

DialogButton {
    id: dialogToggleButton
    
    // Read/write
    property bool toggled: false
    
    // Read-only
    property color originalButtonColor: "#eee"
    property color toggledButtonColor: "#777"
    
    onClicked: {
        toggled = !toggled
    }
    
    onToggledChanged: {
        buttonColor = toggled ? toggledButtonColor : originalButtonColor
    }
}
