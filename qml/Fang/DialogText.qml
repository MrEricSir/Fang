import QtQuick 2.0

Rectangle {
    id: dialogText
    property string text: ""
    color: "transparent"
    
    height: dialogTextText.paintedHeight
    
    Style {
        id: style
    }
    
    Text {
        id: dialogTextText
        
        text: dialogText.text
        
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        color: style.color.dialogText
        
        width: parent.width
    }
}

