import QtQuick

Rectangle {
    id: dialogText;
    property string text: "";
    property color textColor: style.color.dialogText;
    color: "transparent";
    
    property alias horizontalAlignment: dialogTextText.horizontalAlignment;
    property alias font: dialogTextText.font;
    
    width: parent.width;
    height: dialogTextText.paintedHeight;
    
    Style {
        id: style;
    }
    
    Text {
        id: dialogTextText;
        
        text: dialogText.text;
        
        font: style.font.standard;
        color: dialogText.textColor;
        wrapMode: Text.WordWrap;
        
        // In case you want teh linkx0rz
        onLinkActivated: Qt.openUrlExternally(link);
        
        width: parent.width;
    }
}

