import QtQuick 1.1

Item {
    id: button
    
    property color color: "gray"
    property color hoverColor: "blue"
    property url imageURL: ""
    property int imageMargin: 0
    
    signal clicked()
    
    Rectangle {
        id: buttonContainer
        
        color: button.color
        anchors.fill: parent
        
        Image {
            source: imageURL
            
            anchors.fill: parent
            anchors.margins: imageMargin
            fillMode: Image.PreserveAspectCrop
            
            MouseArea {
                id: buttonMouseArea
                
                anchors.fill: parent
                
                onClicked: button.clicked()
                hoverEnabled: true
                enabled: button.enabled
                
                onEntered: buttonContainer.color = hoverColor
                onExited:  buttonContainer.color = button.color
                onPressed: buttonContainer.color = Qt.darker(hoverColor, 1.5)
            }
        }
    }
}
