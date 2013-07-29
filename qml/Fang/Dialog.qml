import QtQuick 1.1

// Dialog container.
// Takes up the entire screen.
// Note: Mr. T. pitties the fool who uses this with anchors!  Specify x, y, width, height, please.
Rectangle {
    id: dialog
    
    // Dialog title text.
    property string title
    
    // This allows children to be positioned within the element.
    default property alias contents: placeholder.children
    
    color: "white"
    visible: false // Managed by state transitions
    state: "closed"
    
    states: [
        State { name: "open" },
        State { name: "closed" }
    ]
    
    function open() {
        state = "open";
    }
    
    function close() {
        state = "closed";
    }
    
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
            }
        }
    ]
    
    Text {
        id: dialogTitle
        
        text: dialog.title
        
        font.pointSize: 18
        font.family: "Tahoma"
        
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.leftMargin: 15
    }
    
    Item {
        id: placeholder
        
        anchors.top: dialogTitle.bottom
        anchors.topMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.right: parent.right
    }
}
