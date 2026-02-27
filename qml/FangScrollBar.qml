import QtQuick
import QtQuick.Controls.Basic

/**
 * Custom-themed scrollbar, thin and transient to match most modern OSes.
 */
ScrollBar {
    id: fangScrollBar;

    policy: style.transientScrollbars ? ScrollBar.AsNeeded : ScrollBar.AlwaysOn;
    property color backgroundColor: "transparent";

    contentItem: Rectangle {
        implicitWidth: 6 * style.scale;
        implicitHeight: 100;
        radius: width / 2;
        color: style.color.scrollbar;
        opacity: (!style.transientScrollbars || fangScrollBar.active) ? 1.0 : 0;

        Behavior on opacity {
            NumberAnimation {
                duration: 200;
            }
        }
    }

    background: Rectangle {
        implicitWidth: 6 * style.scale;
        color: backgroundColor;
    }
}
