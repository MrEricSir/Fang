import QtQuick 1.1
import QtWebKit 1.0
import Fang 1.0

Item {
    id: news
    
    Item {
        id: newsMargin
        
        anchors.fill: parent
        anchors.rightMargin: 16
        anchors.leftMargin: 12
        
        Flickable {
            id: newsFlickable
            
            width: parent.width
            anchors.fill: parent
            contentWidth: Math.max(parent.width, newsView.width)
            contentHeight: Math.max(parent.height, newsView.height)
            
            flickableDirection: Flickable.VerticalFlick
            
            // Web view for our HTML-based RSS display.
            WebView {
                id: newsView
                
                // Enable the web inspector by setting this to true.  You'll have to write-klik
                // on the webview to use this handy-dandy feature.
                property bool devMode: true
                
                preferredWidth: parent.parent.width
                
                focus: true
                
                url: "/html/NewsPage.html"
                
                // Turn the inspek0r off and on.
                settings.developerExtrasEnabled: devMode
                MouseArea {
                    enabled: !newsView.devMode
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                }
                
                MouseWheelArea {
                    id: wheelArea
                    
                    anchors.fill: parent
                    property double deltaY: 0
                    onWheel: {
                        deltaY = delta * 2; // Fudge factor!
                        wheelScrollAnimation.restart();
                    }
                    
                    NumberAnimation {
                        id: wheelScrollAnimation
                        
                        target: newsFlickable
                        properties: "contentY"
                        to: Math.max(0, Math.min(newsFlickable.contentY - wheelArea.deltaY,
                                                 newsFlickable.contentHeight - newsFlickable.height));
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
                }
            }
        }
    }
    
    ScrollBar {
        target: newsFlickable
    }
}
