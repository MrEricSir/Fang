import QtQuick 1.1

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
        
        font.pointSize: style.defaultFontSize
        font.family: style.defaultFontFamily
        color: style.defaultFontColor
        
        width: parent.width
    }
}

