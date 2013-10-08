import QtQuick 1.1

/**
  Style object, ala http://qt-project.org/wiki/QmlStyling
  */
Item {
    // Default UI font.
    property int defaultFontSize: 11
    property color defaultFontColor: "black"
    property string defaultFontFamily: "Tahoma"
    
    Component {
        id: macStyle
            
        Item {
            property int defaultFontSize: 11
            property color defaultFontColor: "black"
            property string defaultFontFamily: "Tahoma"
        }
    }
    
    Component {
        id: winStyle
            
        Item {
            property int defaultFontSize: 11
            property color defaultFontColor: "black"
            property string defaultFontFamily: "Tahoma"
        }
    }
    
    Loader { 
        sourceComponent: {
            switch(platform) {
            case "MAC": {
                console.log("Mac!");
                return macStyle
            }
            break;
            case "WIN": {
                console.log("Windows!");
                return winStyle;
            }
            break;
//            case "IOS": {
//            }
//            break;
//            case "ANDROID": {
//            }
//            break;
//            case "LINUX": {
//            }
//            break;
//            case "UNIX": {
//            }
//            break;
//            }
            }
        }
    }
}
