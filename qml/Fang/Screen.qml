import QtQuick 2.0

/**
 * Represents all top-level screens (main frame, dialogs, etc.)
 */
Rectangle {
    id: screen
    
    // Index of this screen (used for z transitions)
    property double index: 0
    
    function fadeOut() {
        state = "out"
    }
    
    function fadeIn() {
        state = "in"
    }
    
    color: style.color.background
    width: parent.width
    height: parent.height
    z: index
    
    states: [
        State { name: "in" },
        State { name: "out" }
    ]
    
    // Default state is faded in
    state: "in"
    
    onStateChanged: {
        console.log("For  change state: " + state)
    }
    
    Item {
        id: placeholderScreen
        
        anchors.fill: parent
    }
    
    Rectangle {
        id: blocker
        
        anchors.fill: parent
        color: "transparent"
        
        z: screen.z + 1
    }
    
    transitions: [
        Transition {
            from: "in"
            to: "out"
            SequentialAnimation {
                // Fade out
                ColorAnimation {
                    id: fadeOut
                    
                    target: blocker
                    properties: "color"
                    from: "transparent"
                    to: "black"
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        },
        Transition {
            from: "out"
            to: "in"
           
            SequentialAnimation {
                // Show the dialog.
                ColorAnimation {
                    id: fadeIn
                    
                    target: blocker
                    properties: "color"
                    to: "transparent"
                    from: "black"
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        }
    ]
}
