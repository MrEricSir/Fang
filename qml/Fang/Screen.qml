import QtQuick 2.0

/**
 * Represents all top-level screens (main frame, dialogs, etc.)
 */
Rectangle {
    id: screen
    
    // Index of this screen (used for z transitions)
    property double index: 0
    
    // Fades the screen out, man.
    function fadeOut() {
        state = "out"
    }
    
    // Whoa fade back in!
    function fadeIn() {
        state = "in"
    }
    
    color: style.color.background
    width: parent.width
    height: parent.height
    z: index
    
    transform: Scale {
        id: scaleTransform
        property real scale: 1.0
        
        xScale: scale
        yScale: scale
        origin.x: parent.width / 2
        origin.y: parent.height / 2
    }
    
    states: [
        State { name: "in" },
        State { name: "out" }
    ]
    
    // Default state is faded in
    state: "in"
    
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
            ParallelAnimation {
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
                PropertyAnimation {
                    target: scaleTransform
                    properties: "scale"
                    from: 1.0
                    to: 0.8
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        },
        Transition {
            from: "out"
            to: "in"
           
            ParallelAnimation {
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
                
                PropertyAnimation {
                    target: scaleTransform
                    properties: "scale"
                    to: 1.0
                    from: 0.8
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        }
    ]
}
