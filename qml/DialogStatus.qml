import QtQuick 2.4

Rectangle {
    id: dialogStatus
    property string text: ""
    color: "transparent"
    
    width: parent.width
    height: dialogStatusText.paintedHeight
    
    Style {
        id: style
    }
    
    FangIcon {
        id: statusImage;
        
        state: dialogStatus.state;
        width: parent.height;
        height: parent.height;
    }
    
    Text {
        id: dialogStatusText
        
        text: dialogStatus.text
        
        x: statusImage.width + 10 // margin
        
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        color: style.color.dialogText
        renderType: style.textRendering;
        
        width: parent.width - x
    }
}

