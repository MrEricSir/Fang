import QtQuick 2.0

Rectangle {
    id: dialogText
    property string text: ""
    color: "transparent"
    
    width: parent.width
    height: dialogTextText.paintedHeight
    
    Style {
        id: style
    }
    
    Text {
        id: dialogTextText
        
        text: dialogText.text
        
        onLinkActivated: {
            fangSettings.openLink(link)
            console.log("You clicked  a link to: ", link)
        }
        
        wrapMode: Text.Wrap
        
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        color: style.color.dialogText
        
        width: parent.width
    }
}

