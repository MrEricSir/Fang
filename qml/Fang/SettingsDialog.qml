import QtQuick 1.1
import Fang 1.0

// Settings dialog
Dialog {
    id: settingsDialog
    
    DialogText {
        text: "Theme"
        width: parent.width
    }
    
    RadioButtonGroup {
        id: themeRadioGroup
    }
    
    DialogRadioButton {
        id: lightTheme
        radioGroup: themeRadioGroup
        
        text: "Light Theme"
        enabled: true
        
        width: parent.width
    }
    
    DialogRadioButton {
        id: darkTheme
        radioGroup: themeRadioGroup
        
        text: "Dark Theme"
        enabled: true
        
        width: parent.width
    }
    
    DialogButton {
        id: closeButton
        
        text: "Close"
        onClicked: close()
        enabled: !isClosing
        
        width: parent.width
    }
}
