import QtQuick 1.1
import Fang 1.0

/**
  Style object, ala http://qt-project.org/wiki/QmlStyling
  */
Item {
    property variant font: getPlatformFont()
    property variant color: fangSettings.style === "LIGHT" ? colorSchemeLight : colorSchemeDark;
    
    function getPlatformFont() {
        switch(platform) {
        case "MAC": return macFontStyle;
        case "WIN": return winFontStyle;
//        case "IOS": return iosFontStyle;
//        case "ANDROID": return androidFontStyle;
//        case "LINUX": return linuxFontStyle;
//        case "UNIX": return unixFontStyle;
        }
    }
    
    QtObject {
        id: macFontStyle
        
        // Default UI font.
        property int defaultSize: 13
        property string defaultFamily: "Lucida Grande"
    }
    
    QtObject {
        id: winFontStyle
        
        // Default UI font.
        property int defaultSize: 11
        property string defaultFamily: "Segoe UI"
    }
    
    QtObject {
        id: colorSchemeLight
        
        property color scrollbar: "#999"
        
        property color background: "white"
        
        property color dialogBackground: "white"
        property color dialogText: "black"
        
        property color dialogButton: "#eee"
        property color dialogButtonHover: "#d7d7d7"
        property color dialogButtonText: "black"
        property color dialogButtonTextDisabled: "#999"
        property color dialogButtonPressed: Qt.darker(colorSchemeLight.dialogButtonHover, 1.5)
        property color dialogButtonDisabled: Qt.lighter(colorSchemeLight.dialogButton, 1.5)
        
        property color textEntryBackground: "white"
        property color textEntryText: "black"
        property color textEntryBorder: dialogButton
        property color textEntryHint: sidebarRightLine
        
        property color sidebar: "#e5e5e5"
        property color sidebarToolbar: "#535353"
        property color sidebarRightLine: "#ccc"
        property color sidebarSelected: "white"
        property color sidebarSelectedText: "black"
        
        property color sidebarButton: "#777"
        property color sidebarButtonHover: "#ccc"
        property color sidebarButtonPressed: Qt.darker(colorSchemeLight.sidebarButtonHover, 1.5)
        
        property color badge: "#bbb"
        property color badgeText: "white"
    }
    
    QtObject {
        id: colorSchemeDark
        
        property color scrollbar: "#ddd"
        
        property color background: "black"
        
        property color dialogBackground: "black"
        property color dialogText: "white"
        
        property color dialogButton: "#555"
        property color dialogButtonHover: "#454545"
        property color dialogButtonText: "white"
        property color dialogButtonTextDisabled: "#666"
        property color dialogButtonPressed: Qt.lighter(colorSchemeDark.dialogButtonHover, 1.5)
        property color dialogButtonDisabled: Qt.darker(colorSchemeDark.dialogButton, 1.5)
        
        property color textEntryBackground: "black"
        property color textEntryText: "white"
        property color textEntryBorder: dialogButton
        property color textEntryHint: sidebarRightLine
        
        property color sidebar: "#444"
        property color sidebarToolbar: "#888"
        property color sidebarRightLine: "#666"
        property color sidebarSelected: "black"
        property color sidebarSelectedText: "white"
        
        property color sidebarButton: "white"
        property color sidebarButtonHover: "#ccc"
        property color sidebarButtonPressed: Qt.lighter(colorSchemeDark.sidebarButtonHover, 1.5)
        
        property color badge: "#aaa"
        property color badgeText: "black"
    }
}
