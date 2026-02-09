import QtQuick

Rectangle {
    id: dialogStatus
    property string text: "";
    color: "transparent";
    
    width: parent.width;
    height: dialogStatusText.paintedHeight;
    
    Style {
        id: style;
    }
    
    FangIcon {
        id: statusImage;
        
        state: dialogStatus.state;
        width: parent.height;
        height: parent.height;
    }
    
    Text {
        id: dialogStatusText;
        
        text: dialogStatus.text;
        
        x: statusImage.width + 10; // margin
        
        font: style.font.standard;
        color: style.color.dialogText;
        
        width: parent.width - x;
    }
}

