import QtQuick
import Fang 1.0

/**
  Style object, ala http://qt-project.org/wiki/QmlStyling
  */
Item {
    readonly property var font: getPlatformFont();
    readonly property var color: fangSettings.currentStyle === "LIGHT" ? colorSchemeLight : colorSchemeDark;
    readonly property double scale: (platform === "ANDROID") ? 1.5 : 1.0;
    readonly property alias colorSchemeLight: colorSchemeLight;
    readonly property alias colorSchemeDark: colorSchemeDark;
    readonly property double defaultRadius: 4 * scale;
    readonly property double defaultMarin: 5 * scale;


    function getPlatformFont() {
        switch(platform) {
        case "MAC": return macFontStyle;
        case "WIN": return winFontStyle;
//        case "IOS": return iosFontStyle;
        case "ANDROID": return androidFontStyle;
        case "LINUX": return linuxFontStyle;
//        case "UNIX": return unixFontStyle;
        }
    }
    
    QtObject {
        id: macFontStyle;
        
        // Default UI font.
        property int defaultSize: 13;
        property int titleSize: 20;
        property int unreadCountSize: 8;
        property string defaultFamily: ""; // System default
    }
    
    QtObject {
        id: winFontStyle;
        
        // Default UI font.
        //property int defaultSize: 11;
        //property int titleSize: 20;
        //property int unreadCountSize: 8;
        //property string defaultFamily: QFontDatabase.systemFont(QFontDatabase.GeneralFont).family; //""//"Segoe UI";
        //property font standard: Qt.font({ pointSize: 11 })//QFontDatabase.systemFont(QFontDatabase.GeneralFont)
        //property font standard: nativeFont;
        readonly property font standard: {
            let f = nativeFont;
            f.pointSize = 11;
            return f;
        }
        readonly property font standardBold: {
            let f = nativeFont;
            f.pointSize = 11;
            f.weight = Font.Bold;
            return f;
        }
        readonly property font unreadCount: {
            let f = nativeFont;
            f.pointSize = 8;
            return f;
        }
        readonly property font title: {
            let f = nativeFont;
            f.pointSize = 20;
            return f;
        }
    }

    QtObject {
        id: linuxFontStyle;

        // Default UI font.
        property int defaultSize: 11;
        property int titleSize: 20;
        property int unreadCountSize: 8;
        property string defaultFamily: "Geneva";
    }

    QtObject {
        id: androidFontStyle;

        // Default UI font.
        property int defaultSize: 16;
        property int titleSize: 30;
        property int unreadCountSize: 13;
        property string defaultFamily: "Roboto";
    }

    QtObject {
        id: colorSchemeLight;
        
        property color scrollbar: "#999";
        
        property color background: "white";
        property color blockerBackground: "black";
        
        property color dialogBackground: "white";
        property color dialogText: "black";
        
        property color fadedText: "#999";
        
        property color dialogButton: "#eee";
        property color dialogButtonHover: "#d7d7d7";
        property color dialogButtonText: "black";
        property color dialogButtonTextDisabled: "#999";
        property color dialogButtonPressed: Qt.darker(colorSchemeLight.dialogButtonHover, 1.5);
        property color dialogButtonDisabled: "#ffffff"; // Update in SettingsDialog manually!
        property color dialogButtonBorder: "transparent";
        
        property color textEntryBackground: "white";
        property color textEntryText: "black";
        property color textEntryBorder: dialogButton;
        property color textEntryHint: sidebarRightLine;
        
        property color sidebar: "#efefef";
        property color sidebarToolbar: "#535353";
        property color sidebarRightLine: "#ccc";
        property color sidebarSelected: "white";
        property color sidebarSelectedText: "black";
        
        property color sidebarButton: "#777";
        property color sidebarButtonBorder: sidebarButton;
        property color sidebarButtonHover: "#aaa";
        property color sidebarButtonPressed: "white"
        
        property color badge: sidebarButton;
        property color badgeText: "white";
    }
    
    QtObject {
        id: colorSchemeDark;
        
        property color scrollbar: "#ddd";
        
        property color background: "black";
        property color blockerBackground: "#999";
        
        property color dialogBackground: "black";
        property color dialogText: "white";
        
        property color fadedText: "#999";
        
        property color dialogButton: "#555";
        property color dialogButtonHover: "#454545";
        property color dialogButtonText: "white";
        property color dialogButtonTextDisabled: "#666";
        property color dialogButtonPressed: Qt.lighter(colorSchemeDark.dialogButtonHover, 1.5);
        property color dialogButtonDisabled: Qt.darker(colorSchemeDark.dialogButton, 1.5);
        property color dialogButtonBorder: "transparent"
        
        property color textEntryBackground: "black";
        property color textEntryText: "white";
        property color textEntryBorder: dialogButton;
        property color textEntryHint: sidebarRightLine;

        property color sidebar: "black";
        property color sidebarToolbar: "#333";
        property color sidebarRightLine: "#666";
        property color sidebarSelected: "#444";
        property color sidebarSelectedText: "white";
        
        property color sidebarButton: "#777";
        property color sidebarButtonBorder: sidebarButton;
        property color sidebarButtonHover: "#555";
        property color sidebarButtonPressed: "#333";
        
        property color badge: sidebarButton;
        property color badgeText: "black";
    }
}
