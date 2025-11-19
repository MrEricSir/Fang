import QtQuick

DialogGroup {
    id: dialogButtonGroup;

    // Set to the corresponding radio button group.
    property RadioButtonGroup radioGroup;

    function update() {
         if (!radioGroup) {
             throw new Error("No radioGroup defined");
         }

        for (let i in children) {
            let button = children[i];
            const isSelected = button === radioGroup.selected;

            if (isSelected) {
                button.enabled = false;
                button.toggled = true;
            } else {
                button.toggled = false;
                button.enabled = true;
            }
        }
    }

    Connections {
        target: radioGroup;
        function onSelectedChanged() {
            update();
        }
    }

    Component.onCompleted: update();
    onRadioGroupChanged: update();
}
