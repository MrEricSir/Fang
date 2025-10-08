import QtQuick
import Fang 1.0

// Settings dialog
Dialog {
    id: settingsDialog
    
    title: "Settings"
    
    DialogText {
        text: "Theme"
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

    DialogText {
        text: "Refresh news every"
    }

    RadioButtonGroup {
        id: refreshRadioGroup;

        selected: {
            switch (fangSettings.refresh) {
                case "1MIN":
                    return oneMinuteRefresh;
                case "10MIN":
                    return tenMinuteRefresh;
                case "30MIN":
                    return thirtyMinuteRefresh;
                case "1HOUR":
                    return hourRefresh;
            }

            return "10MIN"; // Default (shouldn't get here)
        }

        onSelectedChanged: {
            if (selected === oneMinuteRefresh)
                fangSettings.refresh = "1MIN";
            else if (selected === tenMinuteRefresh)
                fangSettings.refresh = "10MIN";
            else if (selected === thirtyMinuteRefresh)
                fangSettings.refresh = "30MIN";
            else
                fangSettings.refresh = "1HOUR";
        }
    }

    DialogButtonGroup {
        width: parent.width;

        DialogRadioButton {
            id: oneMinuteRefresh;
            radioGroup: refreshRadioGroup;

            text: "1 min";
            enabled: true;

            width: parent.buttonWidth;
        }

        DialogRadioButton {
            id: tenMinuteRefresh;
            radioGroup: refreshRadioGroup;

            text: "10 min";
            enabled: true;

            width: parent.buttonWidth;
        }

        DialogRadioButton {
            id: thirtyMinuteRefresh;
            radioGroup: refreshRadioGroup;

            text: "30 min";
            enabled: true;

            width: parent.buttonWidth;
        }

        DialogRadioButton {
            id: hourRefresh;
            radioGroup: refreshRadioGroup;

            text: "1 hour";
            enabled: true;

            width: parent.buttonWidth;
        }
    }

    DialogText {
        text: "Remove read news after"
    }

    RadioButtonGroup {
        id: cacheLengthRadioGroup;

        selected:
            fangSettings.cacheLength === "2WEEK" ? twoWeekCache :
            fangSettings.cacheLength === "3MONTH" ? threeMonthCache :
            fangSettings.cacheLength === "6MONTH" ? sixMonthCache : oneYearCache;

        onSelectedChanged: {
            if (selected === twoWeekCache)
                fangSettings.cacheLength = "2WEEK";
            else if (selected === threeMonthCache)
                fangSettings.cacheLength = "3MONTH";
            else if (selected === threeMonthCache)
                fangSettings.cacheLength = "6MONTH";
            else
                fangSettings.cacheLength = "1YEAR";
        }
    }

    DialogButtonGroup {
        width: parent.width;

        DialogRadioButton {
            id: twoWeekCache;
            radioGroup: cacheLengthRadioGroup;

            text: "2 weeks";
            enabled: true;

            width: parent.buttonWidth;
        }

        DialogRadioButton {
            id: threeMonthCache;
            radioGroup: cacheLengthRadioGroup;

            text: "3 months";
            enabled: true;

            width: parent.buttonWidth;
        }

        DialogRadioButton {
            id: sixMonthCache;
            radioGroup: cacheLengthRadioGroup;

            text: "6 months";
            enabled: true;

            width: parent.buttonWidth;
        }

        DialogRadioButton {
            id: oneYearCache;
            radioGroup: cacheLengthRadioGroup;

            text: "1 year";
            enabled: true;

            width: parent.buttonWidth;
        }
    }
    
    DialogText {
        text: "OPML feed list"
    }
    
    onDialogClosed: {
        // Manual memory management.
        opml.destroy();

    }
    
    OPMLInteractor {
        id: opml
        
        onImportReady: {
            var importDialog = main.openDialog("OPMLImportDialog.qml");
            importDialog.interactor = opml;
            importDialog.onParentClose.connect(close);
        }
        
        onImportInProgressChanged: {
            console.log("Import in progress? ", importInProgress)
        }
    }
    
    DialogButtonGroup {
        width: parent.width
        
        DialogButton {
            id: importOPML
            
            text: "Import"
            enabled: true
            
            onClicked: opml.importFile()
            
            width: parent.buttonWidth
        }
        
        DialogButton {
            id: exportOPML
            
            text: "Export"
            enabled: true
            
            onClicked: opml.exportFile()
            
            width: parent.buttonWidth
        }
    }
    
    DialogSpacer {}
    
    DialogButton {
        id: aboutBox
        text: "About"
        onClicked: {
            var aboutDialog = main.openDialog("AboutDialog.qml");
            aboutDialog.onDialogClosed.connect(settingsDialog.forceFocus);
        }
    }
    
    DialogSpacer {}
    
    DialogButton {
        id: closeButton
        
        text: "Close"
        onClicked: close()
        enabled: !isClosing
    }
}
