/*
        ScrollBar component for QML Flickable
        
        Copyright (c) 2010 Gregory Schlomoff - gregory.schlomoff@gmail.com
        
        This code is released under the MIT license
        
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:
        
        The above copyright notice and this permission notice shall be included in
        all copies or substantial portions of the Software.
        
        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
        THE SOFTWARE.
*/

import QtQuick 2.0

/*

  Based on the work of Gregory Schlomoff (see license above)

Example:

Flickable {
   id: exampleFlicker
}

// Place outside flickable.
ScrollBar {
   target: exampleFlicker
}
*/
Item {
    id: scrollBar
    
    // The flickable component to scroll.
    property variant target
    
    // Scrolls to a given position in the document.  Will "clip" the value if it's out of bounds.
    function scrollTo( value ) {
        var newY = ( value /  ( target.contentHeight - target.height ) ) * slider.maxScrollbarY;
        scrollToScrollbarPosition( newY );
    }
    
    // Sets the scrollbar to the given value.
    function scrollToScrollbarPosition( newY ) {
        slider.y = Math.max(0, Math.min(newY, track.height - slider.height))
        slider.slideToY();
    }
    
    property real scrollPercentage: 0.15
    
    
    /**
      * Functions for scrolling.
      */
    
    function pageDown() {
        //console.log("Page down");
        scrollTo( target.contentY + target.height );
        
    }

    function pageUp() {
        //console.log("Page up");
        scrollTo( target.contentY - target.height );
    }

    function scrollUp() {
        //console.log("Scroll up");
        scrollTo( target.contentY - ( (target.height) * scrollPercentage ) );
    }

    function scrollDown() {
        //console.log("Scroll down");
        scrollTo( target.contentY + ( (target.height) * scrollPercentage ) );
    }

    function scrollHome() {
        console.log("Scroll home");
        scrollTo( 0 );
    }

    function scrollEnd() {
        console.log("Scroll end");
        scrollTo( target.contentHeight );
    }
    
    // The target's new contentY value
    // NOTE: This should normally only be set by the scrollTo() function.
    property int newContentY: 0
    
    states: [
        State { name: "active" },
        State { name: "inactive" }
    ]
    
    state: "inactive"
    
    transitions: [
        Transition {
            from: "active"
            to: "inactive"
            // Fade out
            NumberAnimation {
                id: fadeOut
                
                target: slider
                properties: "opacity"
                to: 0
                duration: 600
                easing.type: Easing.InOutQuad
            }
        },
        Transition {
            from: "inactive"
            to: "active"
            
            // Fade in
            NumberAnimation {
                id: fadeIn
                
                target: slider
                properties: "opacity"
                to: 1.0
                duration: 200
                easing.type: Easing.InOutQuad
            }
            
        }
    ]
    
    // Only show scrollbar when there's something to scroll.
    visible: target.contentHeight > height
    
    width: 12
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    
    function showScrollbar() {
        state = "active";
        inactiveTimer.restart();
    }
    
    // Reset scroll timer when the content is flicked.
    Connections {
        target: scrollBar.target
        onContentYChanged: showScrollbar()
    }
    
    // Go inactive after a short period.
    Timer {
        id: inactiveTimer
        
        repeat: false
        interval: 500
        onTriggered: scrollBar.state = "inactive"
    }
    
    Item {
        anchors.fill: parent
        
        Timer {
            property int scrollAmount
            
            id: timer
            repeat: true
            interval: 20
            onTriggered: {
                target.contentY = Math.max(
                            0, Math.min(
                                target.contentY + scrollAmount,
                                target.contentHeight - target.height));
            }
        }
        
        MouseArea {
            anchors.fill: parent
            enabled: scrollBar.state == "inactive"
            hoverEnabled: true
            
            // If the mouse is entered or moves, start scroll timer again.
            onEntered: showScrollbar()
            onPositionChanged: showScrollbar()
        }
        
        Item {
            id: track
            anchors.fill: parent
            anchors.rightMargin: 5;
            
            Rectangle {
                id: slider
                
                color: style.color.scrollbar
                width: parent.width
                radius: 5
                anchors.left: parent.left
                opacity: 0
                
                height: Math.max(Math.min(target.height / target.contentHeight * track.height, track.height), 75)
                
                // Max Y value of scroll bar.
                property int maxScrollbarY: track.height - height
                
                // Base y value is total scroll area scalled to scroll bar size.
                property int baseY: (target.contentY / (target.contentHeight - target.height)) * 
                                    maxScrollbarY
                
                // Force y to be between 0 and max height
                function setY() {
                    if (sliderMouseArea.drag.active || scrollAnimation.running)
                        return;
                    
                    y = Math.max(0, Math.min(baseY, maxScrollbarY));
                }
                
                onBaseYChanged: setY();
                onMaxScrollbarYChanged: setY();
                
                function slideToY() {
                    var newScroll = (slider.y / slider.maxScrollbarY) * (target.contentHeight - target.height);
                    
                    // Ensure it's within bounds.
                    newContentY = Math.max(0, Math.min(newScroll, target.contentHeight - target.height))
                    scrollAnimation.restart();
                }
                
                MouseArea {
                    id: sliderMouseArea
                    
                    anchors.fill: parent
                    
                    drag.target: parent
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: track.height - parent.height
                    
                    enabled: scrollBar.state == "active" || fadeOut.running || fadeIn.running
                    
                    onPositionChanged: {
                        if (pressedButtons == Qt.LeftButton) {
                            // Convert slider position to page position.
                            slider.slideToY();
                        }
                        
                        inactiveTimer.restart()
                    }
                    
                    // Scoot the view back it to bounds if we overshot.
                    onReleased: target.returnToBounds();
                }
            }
        }
    }
    
    NumberAnimation {
        id: scrollAnimation
        
        target: scrollBar.target
        properties: "contentY"
        to: newContentY // TODO: move this out of mouse area
        duration: 450
        easing.type: Easing.OutQuad
    }
}
