import QtQuick
import QtQuick.Controls

/**
 * Custom-themed scrollbar, thin and transient to match most modern OSes.
 */
ScrollBar {
    id: fangScrollBar;

    policy: style.transientScrollbars ? ScrollBar.AsNeeded : ScrollBar.AlwaysOn;

    contentItem: Rectangle {
        implicitWidth: 6 * style.scale;
        implicitHeight: 100;
        radius: width / 2;
        color: Qt.rgba(style.color.dialogText.r,
                       style.color.dialogText.g,
                       style.color.dialogText.b, 0.4);
        opacity: (!style.transientScrollbars || fangScrollBar.active) ? 1.0 : 0;

        Behavior on opacity {
            NumberAnimation {
                duration: 200;
            }
        }
    }

    background: Rectangle {
        implicitWidth: 6 * style.scale;
        color: "transparent";
    }
}
