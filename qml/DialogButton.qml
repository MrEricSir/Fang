import QtQuick
import QtQuick.Layouts

Button {
    id: dialogButton;

    property string text: "";
    property bool isPrimary: false;

    Layout.fillWidth: true;
    height: buttonText.paintedHeight + 18;

    radius: platform === "MAC" ? 6 * style.scale : style.defaultRadius;

    buttonColor: isPrimary ? style.color.dialogButtonPrimary : style.color.dialogButton;
    hoverColor: isPrimary ? style.color.dialogButtonPrimaryHover : style.color.dialogButtonHover;
    pressedColor: isPrimary ? style.color.dialogButtonPrimaryPressed : style.color.dialogButtonPressed;
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
        color: isPrimary && dialogButton.enabled
               ? style.color.dialogButtonPrimaryText
               : dialogButton.enabled
                 ? style.color.dialogButtonText
                 : style.color.dialogButtonTextDisabled;
    }
}
