import QtQuick 1.1
import Fang 1.0

Item {
    id: news
    
    // Forces the web view to be repainted (but not refresh!)
    function forceRefresh() {
        newsViewScrollReader.forceRefresh();
    }
    
    // Jump to the current bookmark.
    function jumpToBookmark() {
        newsViewScrollReader.jumpToBookmark();
    }
    
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
            contentHeight: Math.max(parent.height, newsView.height + bottomRect.height)
            
            flickableDirection: Flickable.VerticalFlick
            
            ScrollReader {
                id: newsViewScrollReader
                objectName: "newsViewScrollReader" // MUST NOT CHANGE (used in C++)
                
                // Grab the current contentY
                contentY: newsFlickable.contentY
                
                // Used for jumping the view to a position.
                onJumpYChanged: {
                    if (jumpY < 0)
                        return;
                    
                    newsFlickable.contentY = jumpY
                    jumpY = -1; // reset / acknowledge
                }
            }
            
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
            
            // Spacer to allow the final story to scroll all the way to the top of the window.
            Item {
                id: bottomRect
                
                // Height is set by the scroll utility.
                height: newsViewScrollReader.bottomSpacer
                
                anchors.top: newsView.bottom
                width: parent.width
            }
        }
    }
    
    ScrollBar {
        target: newsFlickable
    }
}
