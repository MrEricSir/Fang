import QtQuick

/**
 * A single keyboard shortcut row: key caps on the left, description on the right.
 */
Item {
    id: shortcutRow;

    property var keys: []
    property string description: ""

    width: parent.width;
    height: Math.max(keyCaps.height, descriptionText.paintedHeight);

    Style {
        id: style;
    }

    KeyboardShortcut {
        id: keyCaps;
        keys: shortcutRow.keys;
        anchors.verticalCenter: parent.verticalCenter;
    }

    Text {
        id: descriptionText;
        text: shortcutRow.description;
        font: style.font.standard;
        color: style.color.dialogText;
        wrapMode: Text.WordWrap;
        anchors.left: keyCaps.right;
        anchors.leftMargin: 12 * style.scale;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
    }
}
