import QtQuick 2.0
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
        
        selected: fangSettings.style === "DARK" ? darkTheme : lightTheme
        
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
            
            text: "Light"
            enabled: true
            
            width: parent.buttonWidth
            
            onClicked: {
                transitions[0].animations[0].stop();
            }
        }
        
        DialogRadioButton {
            id: darkTheme
            radioGroup: themeRadioGroup
            
            text: "Dark"
            enabled: true
            
            width: parent.buttonWidth
            
            onClicked: {
                transitions[0].animations[0].stop();
            }
        }
    }
    
    DialogText {
        text: "Text size"
        width: parent.width
    }
    
    RadioButtonGroup {
        id: fontSizeRadioGroup
        
        selected: fangSettings.fontSize === "SMALL" ? smallFontSize : fangSettings.fontSize === "LARGE" 
                                                                  ? largeFontSize : mediumFontSize
        
        onSelectedChanged: {
            if (selected === smallFontSize)
                fangSettings.fontSize = "SMALL";
            else if (selected === mediumFontSize)
                fangSettings.fontSize = "MEDIUM";
            else
                fangSettings.fontSize = "LARGE";
        }
    }
    
    DialogButtonGroup {
        width: parent.width
        
        DialogRadioButton {
            id: smallFontSize
            radioGroup: fontSizeRadioGroup
            
            text: "Small"
            enabled: true
            
            width: parent.buttonWidth
        }
        
        DialogRadioButton {
            id: mediumFontSize
            radioGroup: fontSizeRadioGroup
            
            text: "Medium"
            enabled: true
            
            width: parent.buttonWidth
        }
        
        DialogRadioButton {
            id: largeFontSize
            radioGroup: fontSizeRadioGroup
            
            text: "Large"
            enabled: true
            
            width: parent.buttonWidth
        }
    }
    
    // Spacer
    DialogText {
        text: ""
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
