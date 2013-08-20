import QtQuick 1.1

Item {
    id: sidebarButton
    
    property color color: "gray"
    property color hoverColor: "blue"
    property url imageURL: ""
    property int imageMargin: 0
    
    signal clicked()
    
    Rectangle {
        id: buttonContainer
        
        color: sidebarButton.color
        anchors.fill: parent
        
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
                
                onEntered: buttonContainer.color = hoverColor
                onExited:  buttonContainer.color = sidebarButton.color
                onPressed: buttonContainer.color = Qt.darker(hoverColor, 1.5)
            }
        }
    }
}
