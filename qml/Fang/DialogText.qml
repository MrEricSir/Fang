import QtQuick 2.0

Rectangle {
    id: dialogText
    property string text: ""
    color: "transparent"
    
    property alias horizontalAlignment: dialogTextText.horizontalAlignment
    property alias fontPointSize: dialogTextText.font.pointSize
    
    width: parent.width
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
        wrapMode: Text.WordWrap
        
        width: parent.width
    }
}

