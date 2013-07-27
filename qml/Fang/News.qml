import QtQuick 1.1
import Fang 1.0

Item {
    id: news
    
    property variant reload: newsView.reload
    
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
            
            FangWebView {
                id: newsView
                objectName: "newsView" // MUST NOT CHANGE (used in C++)
                
                preferredWidth: parent.parent.width
                
                focus: true
                
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                }
                
                MouseWheelArea {
                    id: wheelArea
                    
                    anchors.fill: parent
                    property double deltaY: 0
                    onWheel: {
                        deltaY = delta * 1.5; // Fudge factor!
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
    
    // WebView can't handle sizes changes well, so we'll hack around it.
    property int oldWidth: 0
    onWidthChanged: {
        if (oldWidth == 0) {
            oldWidth = width;
            return;
        }
        
        reloadTimer.restart();
        oldWidth = width;
    }
    property int oldHeight: 0
    onHeightChanged: {
        if (oldHeight == 0) {
            oldHeight = height;
            return;
        }
        
        reloadTimer.restart();
        oldHeight = height;
    }
    
    // Timer for reloading when the size changes.
    Timer {
        id: reloadTimer
        interval: 50
        running: false
        repeat: false
        
        // Force a refresh.
        onTriggered: newsView.reload.trigger();
    }
    
    ScrollBar {
        target: newsFlickable
    }
}
