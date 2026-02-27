import QtQuick

/**
 * Displays one or more keyboard keys in a styled row.
 * Usage: KeyboardShortcut { keys: ["Ctrl", "R"] }
 */
Item {
    id: shortcutItem;

    property var keys: []
    property font keyLabelFont: style.font.standard;
    property color keyLabelColor: style.color.dialogText;

    width: keyRow.width;
    height: keyRow.height;

    Style {
        id: style;
    }

    Row {
        id: keyRow;

        spacing: style.defaultMarin;

        Repeater {
            model: shortcutItem.keys;

            Rectangle {
                color: style.color ? style.color.dialogButton : "transparent";
                border.color: style.color ? style.color.dialogButtonBorder : "transparent";
                border.width: 1;
                radius: style.defaultMarin;
                width: keyLabel.implicitWidth + 12 * style.scale;
                height: keyLabel.implicitHeight + 8 * style.scale;

                Text {
                    id: keyLabel;
                    text: modelData;
                    font: keyLabelFont;
                    color: keyLabelColor;
                    anchors.centerIn: parent;
                }
            }
        }
    }
}
