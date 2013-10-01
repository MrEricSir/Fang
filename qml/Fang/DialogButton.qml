import QtQuick 1.1

// Implementers: specify width!
Rectangle {
    id: dialogButton
    
    property color buttonColor: "#eee"
    property color hoverColor: "#d7d7d7"
    property string text: ""
    
    color: buttonColor
    
    // Signaled on a click.
    signal clicked()
    
    // Fakes a click event.
    function click() {
        if (enabled)
            clicked();
    }
    
    height: buttonText.paintedHeight + 18
    
    onEnabledChanged: {
        buttonText.color = enabled ? "black" : "#999"
    }
    
    Style {
        id: style
    }
    
    Text {
        id: buttonText
        
        text: dialogButton.text
        
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        width: parent.width - 12
        
        anchors.centerIn: parent
        font.pointSize: style.defaultFontSize
        font.family: style.defaultFontFamily
        color: style.defaultFontColor
    }
    
    MouseArea {
        id: buttonMouseArea
        
        anchors.fill: parent
        
        onClicked: dialogButton.clicked()
        hoverEnabled: true
        enabled: dialogButton.enabled
        
        onEntered: dialogButton.color = hoverColor
        onExited:  dialogButton.color = buttonColor
        onPressed: dialogButton.color = Qt.darker(hoverColor, 1.5)
        onEnabledChanged: dialogButton.color = enabled ? buttonColor : Qt.lighter(buttonColor, 1.05)
    }
}
