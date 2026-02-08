import QtQuick
import QtQuick.Layouts

Button {
    id: dialogButton;
    
    property string text: "";

    Layout.fillWidth: true;
    height: buttonText.paintedHeight + 18;

    radius: style.defaultRadius;
    
    buttonColor: style.color.dialogButton;
    hoverColor: style.color.dialogButtonHover;
    pressedColor: style.color.dialogButtonPressed;
    disabledColor: style.color.dialogButtonDisabled;
    toggledColor: style.color.dialogButtonDisabled;
    borderColor: style.color.dialogButtonBorder;
    
    Style {
        id: style;
    }
    
    Text {
        id: buttonText;
        
        text: dialogButton.text;
        
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;
        width: parent.width - 12;
        
        anchors.centerIn: parent;
        font: style.font.standard
        color: style.color.dialogButtonText;
    }
}
