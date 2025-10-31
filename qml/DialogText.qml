import QtQuick

Rectangle {
    id: dialogText;
    property string text: "";
    property color textColor: style.color.dialogText;
    color: "transparent";
    
    property alias horizontalAlignment: dialogTextText.horizontalAlignment;
    property alias fontPointSize: dialogTextText.font.pointSize;
    
    width: parent.width;
    height: dialogTextText.paintedHeight;
    
    Style {
        id: style;
    }
    
    Text {
        id: dialogTextText;
        
        text: dialogText.text;
        
        font.pointSize: style.font.defaultSize;
        font.family: style.font.defaultFamily;
        color: dialogText.textColor;
        wrapMode: Text.WordWrap;
        renderType: style.textRendering;
        
        // In case you want teh linkx0rz
        onLinkActivated: Qt.openUrlExternally(link);
        
        width: parent.width;
    }
}

