import QtQuick

// Provides a simple checkbox of any size with default colors.
Button {
    id: checkBox
    
    // The most important variable!
    property bool checked: false
    
    // When the check was initiated by a click.
    signal userChecked(bool checked)
    
    buttonColor: style.color.dialogBackground
    hoverColor: style.color.dialogButtonHover
    pressedColor: style.color.dialogButtonPressed
    //disabledColor // TODO
    borderColor: style.color.dialogText
    
    Item {
        x: parent.height / 8
        y: parent.height / 8
        
        width: parent.height - (parent.height / 4)
        height: parent.height - (parent.height / 4)
        
        Image {
            id: checkboxImage
            
            anchors.fill: parent
            
            // Hack to make SVGs render with anti-aliasing
            sourceSize.width: width
            sourceSize.height: height
            asynchronous: true
            
            visible: checkBox.checked
            
            source: fangSettings.currentStyle === "LIGHT" ? "images/symbol_ok.svg" : "images/symbol_dark_ok.svg";
        }
        
        MouseArea {
            
            anchors.fill: parent
            
            onClicked: {
                checkBox.checked = !checkBox.checked;
                userChecked(checkBox.checked);
            }
        }
    }
}
