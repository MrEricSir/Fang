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

import QtQuick 1.1

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
            focus: true
            
            enabled: scrollBar.state == "inactive"
            hoverEnabled: true
            
            // If the mouse is entered or moves, start scroll timer again.
            onEntered: showScrollbar()
            onMousePositionChanged: showScrollbar()
        }
        
        Item {
            id: track
            anchors.fill: parent
            anchors.rightMargin: 5;
            
            Rectangle {
                id: slider
                
                color: "#999"
                width: parent.width
                radius: 5
                anchors.left: parent.left
                opacity: 0
                
                height: 100
                
                property int maxScrollbarY: track.height - height
                
                // Base y value is total scroll area scalled to scroll bar size.
                property int baseY: (target.contentY / (target.contentHeight - target.height)) * 
                                    maxScrollbarY
                
                // Force y to be between 0 and max height
                y: sliderMouseArea.drag.active || scrollAnimation.running ? y : Math.max(0, Math.min(baseY, maxScrollbarY))
                
                MouseArea {
                    id: sliderMouseArea
                    
                    anchors.fill: parent
                    
                    // The target's new contentY value
                    property int newContentY: 0
                    
                    drag.target: parent
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: track.height - parent.height
                    
                    enabled: scrollBar.state == "active"
                    
                    onPositionChanged: {
                        if (pressedButtons == Qt.LeftButton) {
                            newContentY = (slider.y / slider.maxScrollbarY) * (target.contentHeight - target.height)
                            newContentY = Math.max(0, Math.min(newContentY, target.contentHeight-target.height))
                            scrollAnimation.restart();
                        }
                        
                        inactiveTimer.restart()
                    }
                    
                    // Scoot the view back it to bounds if we overshot.
                    onReleased: target.returnToBounds();
                    
                    NumberAnimation {
                        id: scrollAnimation
                        
                        target: scrollBar.target
                        properties: "contentY"
                        to: sliderMouseArea.newContentY
                        duration: 450
                        easing.type: Easing.OutQuad
                    }
                }
            }
        }
    }
}
