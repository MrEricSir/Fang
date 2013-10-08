import QtQuick 1.1

/**
  Style object, ala http://qt-project.org/wiki/QmlStyling
  */
Item {
    Component {
        id: macStyle
            
        Item {
            // Default UI font.
            property int defaultFontSize: 13
            property color defaultFontColor: "black"
            property string defaultFontFamily: "Lucida Grande"
        }
    }
    
    Component {
        id: winStyle
            
        Item {
            // Default UI font.
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
            case "WIN": {
                console.log("Windows!");
                return winStyle;
            }
//            case "IOS": {
//            }
//            case "ANDROID": {
//            }
//            case "LINUX": {
//            }
//            case "UNIX": {
//            }
//            }
            }
        }
    }
}
