import QtQuick 1.1

Rectangle {
    id: dialogText
    property string text: ""
    color: "transparent"
    
    height: dialogTextText.paintedHeight
    
    Text {
        id: dialogTextText
        
        text: dialogText.text
        
        font.pointSize: 12
        font.family: "Tahoma"
        
        width: parent.width
    }
}

