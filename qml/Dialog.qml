import QtQuick 2.0
import Fang 1.0

// Dialog container.
// Takes up the entire screen.
// Note: Mr. T. pitties the fool who uses this with anchors!  Specify x, y, width, height, please.
FangScreen {
    id: dialog
    
    signal dialogOpened() // Open has completed
    signal dialogClosed(var self)
    signal dialogClosing(var self)
    
    // Dialog title text.
    property string title
    
    // This allows children to be positioned within the element.
    default property alias contents: placeholder.children
    
    // Read only.
    property bool isClosing: dialogMainContainer.state === "closed" || dismissTimer.running
    property bool isClosed: dialogMainContainer.state === "closed"
    property bool wasOpened: false
    
    color: style.color.dialogBackground
    visible: false // Managed by state transitions
    
    // Opens the dialog.
    function open() {
        wasOpened = true;
        dialogMainContainer.state = "open";
    }
    
    // Dismisses the dialog after a short delay.  Normally it's best to use this instead of close.
    function dismiss() {
        dismissTimer.restart();
    }
    
    // Immediately closes the dialog.
    function close() {
        if (dialogMainContainer.state === "open")
            dialogClosing(dialog)
        
        dialogMainContainer.state = "closed";
    }
    
    // Send closed signal
    onIsClosedChanged: {
        if (isClosed && wasOpened)
            dialogClosed(dialog)
    }
    
    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            close();
        }
    }
    
    Item {
        id: dialogMainContainer
        
        state: "closed"
        
        states: [
            State { name: "open" },
            State { name: "closed" }
        ]
        
        anchors.fill: parent
        
        transitions: [
            Transition {
                from: "open"
                to: "closed"
                SequentialAnimation {
                    // Move dialog off screen
                    NumberAnimation {
                        id: closeAnimation
                        
                        target: dialog
                        properties: "y"
                        from: 0
                        to: parent.height
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                    
                    // Make it invisible.
                    PropertyAction {
                        target: dialog
                        property: "visible"
                        value: "false"
                    }
                }
            },
            Transition {
                from: "closed"
                to: "open"
               
                SequentialAnimation {
                    // Show the dialog.
                    PropertyAction {
                        target: dialog
                        property: "visible"
                        value: "true"
                    }
                    
                     // Move dialog back on screen
                    NumberAnimation {
                        id: openAnimation
                        
                        target: dialog
                        properties: "y"
                        from: parent.height
                        to: 0
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                    
                    ScriptAction {
                        script: dialog.dialogOpened();
                    }
                }
            }
        ]
        
        Text {
            id: dialogTitle
            
            text: dialog.title
            
            font.pointSize: style.font.titleSize
            font.family: style.font.defaultFamily
            color: style.color.dialogText
            renderType: Text.NativeRendering
            
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 20
            anchors.leftMargin: 15
        }
        
        // Catch-alls to prevent clicks under this container.
        MouseArea {
            anchors.fill: parent
            
            // Capture scroll events and such from propagating to WebKit
            hoverEnabled: true
            preventStealing: true
            onWheel: {}
        }
        
        // Dialog contents
        Item {
            anchors.top: dialogTitle.bottom
            anchors.topMargin: 15
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: parent.right
            
            FangScrollView {
                anchors.fill: parent

                Flickable {
                    id: placeholderFlickable
                    anchors.fill: parent
                    
                    contentWidth: width
                    contentHeight: container.childrenRect.height
                    flickableDirection: Flickable.VerticalFlick
                    
                    Item {
                        id: container
                        
                        width: 400
                        anchors.horizontalCenter: parent.horizontalCenter
                        
                        // Children go here.
                        Column {
                            id: placeholder
                            
                            width: parent.width
                            spacing: 10
                        }
                    }
                }
            }
        }
        
        // Timer so we give the user a glimpse of our message before closing
        // the dialog.
        Timer {
            id: dismissTimer
            interval: 700
            running: false
            repeat: false
            
            onTriggered: close()
        }
        
        Style {
            id: style
        }
    }
}
