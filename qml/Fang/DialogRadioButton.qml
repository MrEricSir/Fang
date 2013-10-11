import QtQuick 1.1

DialogToggleButton {
    id: dialogRadioButton
    
    property RadioButtonGroup radioGroup
    
    onToggledChanged: {
        enabled = !toggled // disable to prevent un-clicking of toggled item
        if (toggled)
            radioGroup.selected = dialogRadioButton
    }
    
    function setToggled() {
        if (radioGroup.selected != dialogRadioButton)
            toggled = false
    }
    
    Connections {
        target: radioGroup
        onSelectedChanged: setToggled();
    }
}
