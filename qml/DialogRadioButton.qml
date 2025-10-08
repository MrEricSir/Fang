import QtQuick

DialogToggleButton {
    id: dialogRadioButton;
    
    property RadioButtonGroup radioGroup;
    
    onToggledChanged: {
        enabled = !toggled; // disable to prevent un-clicking of toggled item
        if (toggled) {
            radioGroup.selected = dialogRadioButton;
        }
    }
    
    function setToggled() {
        if (radioGroup.selected != dialogRadioButton) {
            toggled = false;
        } else {
            toggled = true;
        }
    }
    
    Connections {
        target: radioGroup;
        function onSelectedChanged() {
            setToggled();
        }
    }
    
    Component.onCompleted: setToggled();
    onRadioGroupChanged: setToggled();
}
