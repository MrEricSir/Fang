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
    
    Row {
        spacing: 10
        width: parent.width
        property int buttonWidth: width / children.length - spacing / children.length
        
        DialogRadioButton {
            id: lightTheme
            radioGroup: themeRadioGroup
            
            text: "Light Theme"
            enabled: true
            
            width: parent.buttonWidth
        }
        
        DialogRadioButton {
            id: darkTheme
            radioGroup: themeRadioGroup
            
            text: "Dark Theme"
            enabled: true
            
            width: parent.buttonWidth
        }
    }
    
    DialogButton {
        id: closeButton
        
        text: "Close"
        onClicked: close()
        enabled: !isClosing
        
        width: parent.width
    }
}
