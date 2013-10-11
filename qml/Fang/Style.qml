import QtQuick 1.1

/**
  Style object, ala http://qt-project.org/wiki/QmlStyling
  */
Item {
    property variant font: getPlatformFont()
    
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
        property color defaultColor: "black"
        property string defaultFamily: "Lucida Grande"
    }
    
    QtObject {
        id: winFontStyle
        
        // Default UI font.
        property int defaultSize: 11
        property color defaultColor: "black"
        property string defaultFamily: "Tahoma"
    }
}
