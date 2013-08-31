import QtQuick 1.1
import Fang 1.0

Item {
    id: news
    
    // Call this when a feed changes to reset the view.
    function reset() {
        // Reload and scroll to top.
        //newsView.reload.trigger();
        //newsFlickable.contentY = 0; // TODO: zoom to q position of bookmark
    }
    
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
    
    // WebView can't handle sizes changes well, so we'll hack around it.
    property int oldWidth: 0
    onWidthChanged: {
        if (oldWidth <= 0) {
            oldWidth = width;
            return;
        }
        
        reloadTimer.restart();
        oldWidth = width;
    }
    property int oldHeight: 0
    onHeightChanged: {
        if (oldHeight <= 0) {
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
