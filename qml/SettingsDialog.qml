import QtQuick
import Fang 1.0

// Settings dialog
Dialog {
    id: settingsDialog;
    
    title: "Settings";
    
    DialogGroup {
        title: "Theme";
        width: parent.width;

        radioGroup: RadioButtonGroup {
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
        
        DialogRadioButton {
            id: lightTheme;
            
            text: "Light";
            animateToDefault: false;
            onIsToggled: fangSettings.style = "LIGHT";
        }
        
        DialogRadioButton {
            id: darkTheme;
            
            text: "Dark";
            animateToDefault: false;
            onIsToggled: fangSettings.style = "DARK";
        }

        DialogRadioButton {
            id: defaultTheme;

            text: "System";
            animateToDefault: false;
            onIsToggled: fangSettings.style = "DEFAULT";
        }
    }
    
    DialogGroup {
        title: "Tray icon";
        width: parent.width;
        visible: platform === "WIN";

        radioGroup: RadioButtonGroup {
            selected: fangSettings.showTrayIcon ? trayIconEnabled : trayIconDisabled;
        }

        DialogRadioButton {
            id: trayIconEnabled;

            text: "Enabled";
            onIsToggled: fangSettings.showTrayIcon = true;
        }

        DialogRadioButton {
            id: trayIconDisabled;

            text: "Disabled";
            onIsToggled: fangSettings.showTrayIcon = false;
        }
    }

    DialogGroup {
        title: "Text size";
        width: parent.width;

        radioGroup: RadioButtonGroup {
            selected: fangSettings.fontSize === "SMALL" ? smallFontSize : fangSettings.fontSize === "LARGE"
                                                          ? largeFontSize : mediumFontSize;
        }

        DialogRadioButton {
            id: smallFontSize;
            
            text: "Small";
            onIsToggled: fangSettings.fontSize = "SMALL";
        }
        
        DialogRadioButton {
            id: mediumFontSize;
            
            text: "Medium";
            onIsToggled: fangSettings.fontSize = "MEDIUM";
        }
        
        DialogRadioButton {
            id: largeFontSize;

            text: "Large";
            onIsToggled: fangSettings.fontSize = "LARGE";
        }
    }

    DialogGroup {
        title: "Refresh news every";
        width: parent.width;

        radioGroup: RadioButtonGroup {
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

        DialogRadioButton {
            id: oneMinuteRefresh;

            text: "1 min";
            onIsToggled: fangSettings.refresh = "1MIN";
        }

        DialogRadioButton {
            id: tenMinuteRefresh;

            text: "10 min";
            onIsToggled: fangSettings.refresh = "10MIN";
        }

        DialogRadioButton {
            id: thirtyMinuteRefresh;

            text: "30 min";
            onIsToggled: fangSettings.refresh = "30MIN";
        }

        DialogRadioButton {
            id: hourRefresh;

            text: "1 hour";
            onIsToggled: fangSettings.refresh = "1HOUR";
        }
    }

    DialogGroup {
        title: "Remove read news after";
        width: parent.width;

        radioGroup: RadioButtonGroup {
            selected:
                fangSettings.cacheLength === "2WEEK" ? twoWeekCache :
                fangSettings.cacheLength === "3MONTH" ? threeMonthCache :
                fangSettings.cacheLength === "6MONTH" ? sixMonthCache : oneYearCache;
        }

        DialogRadioButton {
            id: twoWeekCache;

            text: "2 weeks";
            onIsToggled: fangSettings.cacheLength = "2WEEK";
        }

        DialogRadioButton {
            id: threeMonthCache;

            text: "3 months";
            onIsToggled: fangSettings.cacheLength = "3MONTH";
        }

        DialogRadioButton {
            id: sixMonthCache;

            text: "6 months";
            onIsToggled: fangSettings.cacheLength = "6MONTH";
        }

        DialogRadioButton {
            id: oneYearCache;

            text: "1 year";
            onIsToggled: fangSettings.cacheLength = "1YEAR";
        }
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
        title: "OPML feed list";
        width: parent.width;
        
        DialogButton {
            id: importOPML;
            
            text: "Import";
            onClicked: opml.importFile();
        }
        
        DialogButton {
            id: exportOPML;
            
            text: "Export";
            onClicked: opml.exportFile();
        }
    }
    
    DialogGroup {
        width: parent.width;

        DialogButton {
            id: aboutBox;
            text: "About";
            onClicked: {
                var aboutDialog = main.openDialog("AboutDialog.qml");
                aboutDialog.onDialogClosed.connect(settingsDialog.forceFocus);
            }
        }
    }
    
    DialogGroup {
        width: parent.width;

        DialogButton {
            id: closeButton;

            text: "Close";
            onClicked: close();
            enabled: !isClosing;
        }
    }
}
