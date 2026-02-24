import QtQuick
import QtQuick.Window
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
    readonly property bool windowActive: Window.window ? Window.window.active : true;

    SystemPalette {
        id: sysPalette;
        colorGroup: SystemPalette.Active;
    }

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

    function getSizeMultiplier() {
        switch(fangSettings.fontSize) {
        case "SMALL": return 0.75;
        case "MEDIUM": return 1.0;
        case "LARGE": return 1.3334;
        }
    }
    
    QtObject {
        id: macFontStyle;

        readonly property font standard: {
            let f = nativeFont;
            f.pointSize = 13 * getSizeMultiplier();
            return f;
        }
        readonly property font standardBold: {
            let f = nativeFont;
            f.pointSize = 13 * getSizeMultiplier();
            f.weight = Font.Bold;
            return f;
        }
        readonly property font unreadCount: {
            let f = nativeFont;
            f.pointSize = 8 * getSizeMultiplier();
            return f;
        }
        readonly property font title: {
            let f = nativeFont;
            f.pointSize = 20 * getSizeMultiplier();
            return f;
        }
    }
    
    QtObject {
        id: winFontStyle;

        readonly property font standard: {
            let f = nativeFont;
            f.pointSize = 11 * getSizeMultiplier();
            return f;
        }
        readonly property font standardBold: {
            let f = nativeFont;
            f.pointSize = 11 * getSizeMultiplier();
            f.weight = Font.Bold;
            return f;
        }
        readonly property font unreadCount: {
            let f = nativeFont;
            f.pointSize = 8 * getSizeMultiplier();
            return f;
        }
        readonly property font title: {
            let f = nativeFont;
            f.pointSize = 20 * getSizeMultiplier();
            return f;
        }
    }

    QtObject {
        id: linuxFontStyle;

        readonly property font standard: {
            let f = nativeFont;
            f.pointSize = 11 * getSizeMultiplier();
            return f;
        }
        readonly property font standardBold: {
            let f = nativeFont;
            f.pointSize = 11 * getSizeMultiplier();
            f.weight = Font.Bold;
            return f;
        }
        readonly property font unreadCount: {
            let f = nativeFont;
            f.pointSize = 8 * getSizeMultiplier();
            return f;
        }
        readonly property font title: {
            let f = nativeFont;
            f.pointSize = 20 * getSizeMultiplier();
            return f;
        }
    }

    QtObject {
        id: androidFontStyle;

        readonly property font standard: {
            let f = nativeFont;
            f.pointSize = 16;
            return f;
        }
        readonly property font standardBold: {
            let f = nativeFont;
            f.pointSize = 16;
            f.weight = Font.Bold;
            return f;
        }
        readonly property font unreadCount: {
            let f = nativeFont;
            f.pointSize = 13;
            return f;
        }
        readonly property font title: {
            let f = nativeFont;
            f.pointSize = 30;
            return f;
        }
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
        
        property color sidebar: platform === "MAC" ? "#F0F0F0"
                              : platform === "WIN" ? "#F3F3F3"
                              : "#efefef";
        property color sidebarToolbar: "#535353";
        property color sidebarRightLine: "#ccc";
        property color sidebarSelected: windowActive
                              ? (platform === "WIN" ? "#C4C4C9" : "#D5D5DA")
                              : (platform === "WIN" ? "#D8D8DC" : "#E0E0E4");
        property color sidebarSelectedText: windowActive
                              ? (platform === "MAC" ? sysPalette.accent : "black")
                              : "#888";
        property color sidebarText: windowActive ? "black" : "#888";

        property color sidebarButton: "#777";
        property color sidebarButtonBorder: sidebarButton;
        property color sidebarButtonHover: "#aaa";
        property color sidebarButtonPressed: "white"

        property color badge: platform === "WIN" ? "#0078D4" : sysPalette.accent;
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

        property color sidebar: platform === "MAC" ? "#1E1E1E"
                              : platform === "WIN" ? "#202020"
                              : "black";
        property color sidebarToolbar: "#333";
        property color sidebarRightLine: "#666";
        property color sidebarSelected: windowActive
                              ? (platform === "WIN" ? "#555560" : "#3A3A3C")
                              : (platform === "WIN" ? "#404048" : "#2E2E30");
        property color sidebarSelectedText: windowActive
                              ? (platform === "MAC" ? sysPalette.accent : "white")
                              : "#777";
        property color sidebarText: windowActive ? "white" : "#777";

        property color sidebarButton: "#777";
        property color sidebarButtonBorder: sidebarButton;
        property color sidebarButtonHover: "#555";
        property color sidebarButtonPressed: "#333";

        property color badge: platform === "WIN" ? "#0078D4" : sysPalette.accent;
        property color badgeText: "white";
    }
}
