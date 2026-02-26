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
    readonly property double defaultRadius: (platform === "MAC " ? 4 : 2) * scale;
    readonly property double defaultMarin: 5 * scale;
    readonly property bool windowActive: Window.window ? Window.window.active : true;

    SystemPalette {
        id: sysPalette;
        colorGroup: windowActive ? SystemPalette.Active : SystemPalette.Inactive;
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
        property color blockerBackground: Qt.rgba(0, 0, 0, 0.3);
        
        property color dialogBackground: "white";
        property color dialogText: "black";
        
        property color fadedText: "#999";
        
        property color dialogButton: "#eee";
        property color dialogButtonHover: "#d7d7d7";
        property color dialogButtonText: "black";
        property color dialogButtonTextDisabled: "#999";
        property color dialogButtonPressed: Qt.darker(colorSchemeLight.dialogButtonHover, 1.5);
        property color dialogButtonDisabled: "#ffffff"; // Update in SettingsDialog manually!
        property color dialogButtonBorder: sysPalette.mid;
        property color dialogButtonPrimary: sysPalette.accent;
        property color dialogButtonPrimaryHover: Qt.darker(sysPalette.accent, 1.1);
        property color dialogButtonPrimaryPressed: Qt.darker(sysPalette.accent, 1.3);
        property color dialogButtonPrimaryText: "white";

        property color textEntryBackground: "white";
        property color textEntryText: "black";
        property color textEntryBorder: dialogButton;
        property color textEntryFocusBorder: sysPalette.accent;
        property color textEntryHint: sidebarRightLine;
        
        property color sidebar: sysPalette.window;
        property color sidebarToolbar: Qt.darker(sysPalette.window, 1.05);
        property color sidebarRightLine: "#ccc";
        property color sidebarSelected: {
            if (platform === "MAC" && !windowActive) return sysPalette.mid;
            if (platform === "WIN") return sysPalette.mid;
            return sysPalette.highlight;
        }
        property color sidebarSelectedText: {
            if (platform === "MAC" && !windowActive) return sysPalette.windowText;
            return sysPalette.highlightedText;
        }
        property color sidebarText: sysPalette.windowText;

        property color sidebarButton: "transparent";
        property color sidebarButtonBorder: Qt.rgba(0, 0, 0, 0.15);
        property color sidebarButtonHover: Qt.rgba(0, 0, 0, 0.06);
        property color sidebarButtonPressed: Qt.rgba(0, 0, 0, 0.12);

        property color badge: platform === "WIN" ? "#0078D4" : sysPalette.accent;
        property color badgeText: "white";
    }

    QtObject {
        id: colorSchemeDark;

        property color scrollbar: "#ddd";

        property color background: "black";
        property color blockerBackground: Qt.rgba(0, 0, 0, 0.4);

        property color dialogBackground: "black";
        property color dialogText: "white";

        property color fadedText: "#999";

        property color dialogButton: "#555";
        property color dialogButtonHover: "#454545";
        property color dialogButtonText: "white";
        property color dialogButtonTextDisabled: "#666";
        property color dialogButtonPressed: Qt.lighter(colorSchemeDark.dialogButtonHover, 1.5);
        property color dialogButtonDisabled: Qt.darker(colorSchemeDark.dialogButton, 1.5);
        property color dialogButtonBorder: sysPalette.placeholderText;
        property color dialogButtonPrimary: sysPalette.accent;
        property color dialogButtonPrimaryHover: Qt.lighter(sysPalette.accent, 1.15);
        property color dialogButtonPrimaryPressed: Qt.lighter(sysPalette.accent, 1.3);
        property color dialogButtonPrimaryText: "white";

        property color textEntryBackground: "black";
        property color textEntryText: "white";
        property color textEntryBorder: dialogButton;
        property color textEntryFocusBorder: sysPalette.accent;
        property color textEntryHint: sidebarRightLine;

        property color sidebar: sysPalette.window;
        property color sidebarToolbar: Qt.lighter(sysPalette.window, 1.1);
        property color sidebarRightLine: "#666";
        property color sidebarSelected: {
            if (platform === "MAC" && !windowActive) return sysPalette.mid;
            if (platform === "MAC") return Qt.lighter(sysPalette.light, 1.5);
            return sysPalette.highlight;
        }
        property color sidebarSelectedText: {
            if (platform === "MAC" && !windowActive) return sysPalette.windowText;
            if (platform === "MAC") return Qt.lighter(sysPalette.accent, 1.3);
            return sysPalette.highlight;
        }
        property color sidebarText: sysPalette.windowText;

        property color sidebarButton: "transparent";
        property color sidebarButtonBorder: Qt.rgba(1, 1, 1, 0.2);
        property color sidebarButtonHover: Qt.rgba(1, 1, 1, 0.06);
        property color sidebarButtonPressed: Qt.rgba(1, 1, 1, 0.12);

        property color badge: platform === "WIN" ? "#0078D4" : sysPalette.accent;
        property color badgeText: "white";
    }
}
