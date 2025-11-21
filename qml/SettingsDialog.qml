import QtQuick
import Fang 1.0

// Settings dialog
Dialog {
    id: settingsDialog;
    
    title: "Settings";
    
    DialogText {
        text: "Theme";
    }
    
    RadioButtonGroup {
        id: themeRadioGroup;
        selected: {
            switch (fangSettings.style) {
            case "LIGHT":
                return lightTheme;
            case "DARK":
                return darkTheme;
            default:
                return defaultTheme;
            }
        }
    }
    
    DialogButtonGroup {
        radioGroup: themeRadioGroup;
        width: parent.width;
        
        DialogRadioButton {
            id: lightTheme;
            
            text: "Light";
            animateToDefault: false;
            width: parent.buttonWidth;
            onIsToggled: fangSettings.style = "LIGHT";
        }
        
        DialogRadioButton {
            id: darkTheme;
            
            text: "Dark";
            animateToDefault: false;
            width: parent.buttonWidth;
            onIsToggled: fangSettings.style = "DARK";
        }

        DialogRadioButton {
            id: defaultTheme;

            text: "System";
            animateToDefault: false;
            width: parent.buttonWidth;
            onIsToggled: fangSettings.style = "DEFAULT";
        }
    }
    
    DialogText {
        text: "Tray icon";
        visible: platform === "WIN";
    }
    
    RadioButtonGroup {
        id: trayRadioGroup;
        selected: fangSettings.showTrayIcon ? trayIconEnabled : trayIconDisabled;
    }
    
    DialogButtonGroup {
        radioGroup: trayRadioGroup;
        width: parent.width;
        visible: platform === "WIN";

        DialogRadioButton {
            id: trayIconEnabled;

            text: "Enabled";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.showTrayIcon = true;
        }

        DialogRadioButton {
            id: trayIconDisabled;

            text: "Disabled";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.showTrayIcon = false;
        }
    }

    DialogText {
        text: "Text size";
    }

    RadioButtonGroup {
        id: fontSizeRadioGroup;
        selected: fangSettings.fontSize === "SMALL" ? smallFontSize : fangSettings.fontSize === "LARGE"
                                                                  ? largeFontSize : mediumFontSize;
    }

    DialogButtonGroup {
        radioGroup: fontSizeRadioGroup;
        width: parent.width;
        
        DialogRadioButton {
            id: smallFontSize;
            
            text: "Small";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.fontSize = "SMALL";
        }
        
        DialogRadioButton {
            id: mediumFontSize;
            
            text: "Medium";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.fontSize = "MEDIUM";
        }
        
        DialogRadioButton {
            id: largeFontSize;

            text: "Large";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.fontSize = "LARGE";
        }
    }

    DialogText {
        text: "Refresh news every";
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
    }

    DialogButtonGroup {
        radioGroup: refreshRadioGroup;
        width: parent.width;

        DialogRadioButton {
            id: oneMinuteRefresh;

            text: "1 min";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.refresh = "1MIN";
        }

        DialogRadioButton {
            id: tenMinuteRefresh;

            text: "10 min";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.refresh = "10MIN";
        }

        DialogRadioButton {
            id: thirtyMinuteRefresh;

            text: "30 min";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.refresh = "30MIN";
        }

        DialogRadioButton {
            id: hourRefresh;

            text: "1 hour";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.refresh = "1HOUR";
        }
    }

    DialogText {
        text: "Remove read news after";
    }

    RadioButtonGroup {
        id: cacheLengthRadioGroup;
        selected:
            fangSettings.cacheLength === "2WEEK" ? twoWeekCache :
            fangSettings.cacheLength === "3MONTH" ? threeMonthCache :
            fangSettings.cacheLength === "6MONTH" ? sixMonthCache : oneYearCache;
    }

    DialogButtonGroup {
        radioGroup: cacheLengthRadioGroup;
        width: parent.width;

        DialogRadioButton {
            id: twoWeekCache;

            text: "2 weeks";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.cacheLength = "2WEEK";
        }

        DialogRadioButton {
            id: threeMonthCache;

            text: "3 months";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.cacheLength = "3MONTH";
        }

        DialogRadioButton {
            id: sixMonthCache;

            text: "6 months";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.cacheLength = "6MONTH";
        }

        DialogRadioButton {
            id: oneYearCache;

            text: "1 year";
            width: parent.buttonWidth;
            onIsToggled: fangSettings.cacheLength = "1YEAR";
        }
    }
    
    DialogText {
        text: "OPML feed list";
    }
    
    onDialogClosed: {
        // Manual memory management.
        opml.destroy();
    }
    
    OPMLInteractor {
        id: opml;
        
        onImportReady: {
            var importDialog = main.openDialog("OPMLImportDialog.qml");
            importDialog.interactor = opml;
            importDialog.onParentClose.connect(close);
        }
        
        onImportInProgressChanged: {
            console.log("Import in progress? ", importInProgress);
        }
    }
    
    DialogGroup {
        width: parent.width;
        
        DialogButton {
            id: importOPML;
            
            text: "Import";
            width: parent.buttonWidth;
            onClicked: opml.importFile();
        }
        
        DialogButton {
            id: exportOPML;
            
            text: "Export";
            width: parent.buttonWidth;
            onClicked: opml.exportFile();
        }
    }
    
    DialogSpacer {}
    
    DialogButton {
        id: aboutBox;
        text: "About";
        onClicked: {
            var aboutDialog = main.openDialog("AboutDialog.qml");
            aboutDialog.onDialogClosed.connect(settingsDialog.forceFocus);
        }
    }
    
    DialogSpacer {}
    
    DialogButton {
        id: closeButton;
        
        text: "Close";
        onClicked: close();
        enabled: !isClosing;
    }
}
