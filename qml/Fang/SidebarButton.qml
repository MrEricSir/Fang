import QtQuick 2.0

Item {
    id: sidebarButton
    
    property color color: style.color.sidebarButton
    property color borderColor: style.color.sidebarButtonBorder
    property color hoverColor: style.color.sidebarButtonHover
    property color pressedColor: style.color.sidebarButtonPressed
    
    property url imageURL: ""
    property url imageHoverURL: ""
    property url imagePressedURL: ""
    
    property int imageMargin: 7
    
    signal clicked()
    
    Rectangle {
        id: buttonContainer
        
        anchors.fill: parent
        
        radius: width * 0.5
        
        states: [
            State { name: "default" },
            State { name: "hover" },
            State { name: "pressed" }
        ]
        
        color: state === "hover" ? sidebarButton.hoverColor : state === "pressed" ?
                                      sidebarButton.pressedColor : sidebarButton.color
        
        border.color: sidebarButton.borderColor
        border.width: 1
        
        Image {
            source: buttonContainer.state === "hover" ? sidebarButton.imageHoverURL : 
                                                        buttonContainer.state === "pressed" ?
                                                            sidebarButton.imagePressedURL : sidebarButton.imageURL
            
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
