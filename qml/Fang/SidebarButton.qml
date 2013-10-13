import QtQuick 1.1

Item {
    id: sidebarButton
    
    property color color: style.color.sidebarButton
    property color hoverColor: style.color.sidebarButtonHover
    property color pressedColor: style.color.sidebarButtonPressed
    
    property url imageURL: ""
    property int imageMargin: 0
    
    signal clicked()
    
    Rectangle {
        id: buttonContainer
        
        anchors.fill: parent
        
        states: [
            State { name: "default" },
            State { name: "hover" },
            State { name: "pressed" }
        ]
        
        color: state === "hover" ? sidebarButton.hoverColor : state === "pressed" ?
                                      sidebarButton.pressedColor : sidebarButton.color
        
        Image {
            source: imageURL
            
            anchors.fill: parent
            anchors.margins: imageMargin
            fillMode: Image.PreserveAspectCrop
            
            // Make SVGs render real good like.
            sourceSize.width: width
            sourceSize.height: height
            
            MouseArea {
                id: buttonMouseArea
                
                anchors.fill: parent
                
                onClicked: sidebarButton.clicked()
                hoverEnabled: true
                enabled: sidebarButton.enabled
                
                onEntered: buttonContainer.state = "hover"
                onExited:  buttonContainer.state = "default"
                onPressed: buttonContainer.state = "pressed"
            }
        }
    }
}
