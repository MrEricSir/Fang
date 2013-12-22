import QtQuick 2.0

// Implementers: specify width!
Rectangle {
    id: dialogButton
    
    property string text: ""
    
    property bool enabled: true
    
    property color buttonColor: style.color.dialogButton
    property color hoverColor: style.color.dialogButtonHover
    property color pressedColor: style.color.dialogButtonPressed
    property color disabledColor: style.color.dialogButtonDisabled
    
    // Signaled on a click.
    signal clicked()
    
    // Fakes a click event.
    function click() {
        if (enabled)
            clicked();
    }
    
    height: buttonText.paintedHeight + 18
    
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
    
    color: state === "disabled" ? disabledColor :
                                 state === "hover" ? hoverColor :
                                 state === "pressed" ? pressedColor :
                                                       buttonColor
    
    Text {
        id: buttonText
        
        text: dialogButton.text
        
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        width: parent.width - 12
        
        anchors.centerIn: parent
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        color: style.color.dialogButtonText
    }
    
    MouseArea {
        id: buttonMouseArea
        
        anchors.fill: parent
        
        onClicked: dialogButton.clicked()
        hoverEnabled: true
        enabled: dialogButton.enabled
        
        onEntered: dialogButton.state = "hover"
        onExited:  dialogButton.state = "default"
        onPressed: dialogButton.state = "pressed"
        onEnabledChanged: {
            if (!enabled)
                dialogButton.state = "disabled";
        }
    }
}
