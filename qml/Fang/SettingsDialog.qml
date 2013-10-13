import QtQuick 1.1
import Fang 1.0

// Settings dialog
Dialog {
    id: settingsDialog
    
    title: "Settings"
    
    DialogText {
        text: "Theme"
        width: parent.width
    }
    
    RadioButtonGroup {
        id: themeRadioGroup
        
        selected: fangSettings.style == "DARK" ? darkTheme : lightTheme
        
        onSelectedChanged: {
            if (selected === darkTheme)
                fangSettings.style = "DARK";
            else
                fangSettings.style = "LIGHT";
        }
    }
    
    DialogButtonGroup {
        width: parent.width
        
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
