import QtQuick

/**
  * This class exists to keep the basic button functionality, including colors, transitions,
  * and button click events in one place.
  *
  * Implementers can set the size, image, raduis, text, etc. any way they like.
  */
Rectangle {
    id: baseButton;
    
    property bool enabled: true;

    // Used for toggle buttons.
    property bool isToggleable: false;
    property bool toggled: false;
    
    // Implementers: define these based on Style object.
    property color buttonColor;
    property color hoverColor;
    property color pressedColor;
    property color disabledColor;
    property color toggledColor;
    property color borderColor;
    
    // Signaled on a click.
    signal clicked();
    
    // Fakes a click event.
    function click() {
        if (enabled) {
            if (isToggleable) {
                toggled = !toggled;
            }

            clicked();
        }
    }
    
    border.color: borderColor;
    border.width: 1;
    
    onEnabledChanged: {
        if (!enabled) {
            state = "disabled";
        } else {
            state = toggled ? "toggled" : "default";
        }
    }

    onToggledChanged: {
        if (toggled) {
            state = "toggled";
        }
    }
    
    Style {
        id: style;
    }
    
    state: "default";
    states: [
        State { name: "default" },
        State { name: "hover" },
        State { name: "pressed" },
        State { name: "disabled" },
        State { name: "toggled" }
    ]
    
    function getColorForState() {
        switch (state) {
        case "default":
            return buttonColor;
        case "hover":
            return hoverColor;
        case "pressed":
            return pressedColor;
        case "disabled":
            return disabledColor;
        case "toggled":
            return toggledColor;
        }
    }
    
    Component.onCompleted: {
        // Sets the load-time color.
        color = getColorForState();
    }
    
    Connections {
        target: fangSettings;
        
        // Reset color when style changes.
        function onStyleChanged() {
            color = getColorForState();
        }
    }

    transitions: [
        Transition {
            from: "*";
            to: "disabled";
            
            ColorAnimation {
                target: baseButton;
                properties: "color";
                to: getColorForState();
                duration: 100;
                easing.type: Easing.InOutQuad;
            }
            
            // Hack to ensure correct button color in color selector.
            onRunningChanged: {
                if (!running) {
                    color = getColorForState();
                }
                
            }
        },
        Transition {
            from: "*";
            to: "hover";
            
            ColorAnimation {
                target: baseButton;
                properties: "color";
                to: getColorForState();
                duration: 300;
                easing.type: Easing.InOutQuad;
            }
        },
        Transition {
            from: "*";
            to: "default";
            
            ColorAnimation {
                target: baseButton;
                properties: "color";
                to: getColorForState();
                duration: 300;
                easing.type: Easing.InOutQuad;
            }
        },
        Transition {
            from: "*";
            to: "pressed";
            
            ColorAnimation {
                target: baseButton;
                properties: "color";
                to: getColorForState();
                duration: 300;
                easing.type: Easing.InOutQuad;
            }
        }
    ]
    
    MouseArea {
        id: buttonMouseArea;
        
        anchors.fill: parent;
        
        onClicked: {
            if (baseButton.isToggleable) {
                baseButton.toggled = !baseButton.toggled;
            }

            baseButton.clicked();
        }
        hoverEnabled: platform !== "ANDROID"; // No hover on touch screens
        enabled: baseButton.enabled;
        
        onEntered: baseButton.state = "hover";
        onExited: baseButton.state = baseButton.toggled ? "toggled" : "default";
        onPressed: baseButton.state = "pressed";
        onEnabledChanged: {
            if (!baseButton.enabled) {
                baseButton.state = baseButton.toggled ? "toggled" : "disabled";
            }
        }
        
        // Prevent double click from issuing two presses
        onDoubleClicked: {}
    }
}
