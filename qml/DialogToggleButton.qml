import QtQuick 2.4

DialogButton {
    id: dialogToggleButton
    
    // Read/write
    property bool toggled: false
    
    onClicked: {
        toggled = !toggled
    }
    
    // Manually set state if we entered toggled mode.
    onToggledChanged: {
        if (toggled)
            state = "disabled";
    }
}
