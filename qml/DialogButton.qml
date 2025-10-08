import QtQuick

Button {
    id: dialogButton
    
    property string text: ""
    
    width: parent.width
    height: buttonText.paintedHeight + 18
    
    buttonColor: style.color.dialogButton
    hoverColor: style.color.dialogButtonHover
    pressedColor: style.color.dialogButtonPressed
    disabledColor: style.color.dialogButtonDisabled
    borderColor: style.color.dialogButtonBorder
    
    Style {
        id: style
    }
    
    Text {
        id: buttonText
        
        text: dialogButton.text
        
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        width: parent.width - 12
        renderType: style.textRendering;
        
        anchors.centerIn: parent
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        color: style.color.dialogButtonText
    }
}
