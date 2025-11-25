import QtQuick
import QtQuick.Layouts

Item {
    id: dialogGroup;

    // Set to the corresponding radio button group.
    property RadioButtonGroup radioGroup;

    // Set this to the title, if any.
    property alias title: text.text;

    // This allows children to be positioned within the element.
    default property alias contents: placeholder.children;

    height: placeholder.height + text.height + placeholder.anchors.topMargin * 2;

    Connections {
        target: radioGroup;
        function onSelectedChanged() {
            placeholder.update();
        }
    }
    onRadioGroupChanged: placeholder.update();

    DialogText {
        id: text;
        anchors.left: parent.left;
        anchors.right: parent.right;
    }

    // Child components will be placed here.
    RowLayout {
        id: placeholder;
        spacing: 10;
        uniformCellSizes: true;
        anchors.topMargin: spacing;
        anchors.top: text.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;

        function update() {
            if (!radioGroup) {
                //throw new Error("No radioGroup defined");
                return;
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

        Component.onCompleted: update();
    }
}
