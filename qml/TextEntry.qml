import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic as Basic

// A text entry box.
Basic.TextField {
    id: textEntry;

    Style {
        id: style;
    }

    color: style.color.textEntryText;
    font: style.font.standard;

    placeholderTextColor: style.color.textEntryHint;

    background: Rectangle {
        color: style.color.textEntryBackground;
        radius: platform === "MAC" ? 6 * style.scale : style.defaultRadius;
        border.color: textEntry.activeFocus
                      ? style.color.textEntryFocusBorder
                      : style.color.textEntryBorder;
        border.width: textEntry.activeFocus ? 2 * style.scale : 1 * style.scale;
    }

    topPadding: 6  * style.scale;
    bottomPadding: topPadding;

    ContextMenu.menu: Menu {
        id: contextMenu;
        popupType: Popup.Native;

        MenuItem {
            text: "Cut";
            enabled: textEntry.selectedText !== "" && !textEntry.readOnly;
            onTriggered: textEntry.cut();
        }
        MenuItem {
            text: "Copy";
            enabled: textEntry.selectedText !== "";
            onTriggered: textEntry.copy();
        }
        MenuItem {
            text: "Paste";
            enabled: textEntry.canPaste;
            onTriggered: textEntry.paste();
        }

        MenuSeparator { }

        MenuItem {
            text: "Select All"
            enabled: textEntry.length > 0
            onTriggered: textEntry.selectAll()
        }
    }
}
