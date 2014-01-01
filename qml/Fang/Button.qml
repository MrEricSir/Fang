import QtQuick 2.0

import QtQuick 2.0

/**
  * This class exists to keep the basic button functionality, including colors, transitions,
  * and button click events in one place.
  *
  * Implementers can set the size, image, raduis, text, etc. any way they like.
  */
Rectangle {
    id: baseButton
    
    property bool enabled: true
    
    // Implementers: define these based on Style object.
    property color buttonColor
    property color hoverColor
    property color pressedColor
    property color disabledColor
    property color borderColor
    
    // Signaled on a click.
    signal clicked()
    
    // Fakes a click event.
    function click() {
        if (enabled)
            clicked();
    }
    
    border.color: borderColor
    border.width: 1
    
    onEnabledChanged: state = (enabled ? "default" : "disabled")
    
    Style {
        id: style
    }
    
    states: [
        State { name: "default" },
        State { name: "hover" },
        State { name: "pressed" },
        State { name: "disabled" }
    ]
    
    // Initial color state: will be changed by transitions below.
    color: state === "disabled" ? disabledColor : buttonColor
    
    /*
    color: state === "disabled" ? disabledColor :
                                 state === "hover" ? hoverColor :
                                 state === "pressed" ? pressedColor :
                                                       buttonColor
    */
    
    transitions: [
        Transition {
            from: "*"
            to: "disabled"
            
            ColorAnimation {
                target: baseButton
                properties: "color"
                to: disabledColor
                duration: 100
                easing.type: Easing.InOutQuad
            }
        },
        Transition {
            from: "*"
            to: "hover"
            
            ColorAnimation {
                target: baseButton
                properties: "color"
                to: hoverColor
                duration: 300
                easing.type: Easing.InOutQuad
            }
        },
        Transition {
            from: "*"
            to: "default"
            
            ColorAnimation {
                target: baseButton
                properties: "color"
                to: buttonColor
                duration: 300
                easing.type: Easing.InOutQuad
            }
        },
        Transition {
            from: "*"
            to: "pressed"
            
            ColorAnimation {
                target: baseButton
                properties: "color"
                to: pressedColor
                duration: 300
                easing.type: Easing.InOutQuad
            }
        }
    ]
    
    MouseArea {
        id: buttonMouseArea
        
        anchors.fill: parent
        
        onClicked: baseButton.clicked()
        hoverEnabled: true
        enabled: baseButton.enabled
        
        onEntered: baseButton.state = "hover"
        onExited:  baseButton.state = "default"
        onPressed: baseButton.state = "pressed"
        onEnabledChanged: {
            if (!enabled)
                baseButton.state = "disabled";
        }
    }
}
