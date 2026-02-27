import QtQuick
import QtQuick.Window

Row {
    id: captionButtons;

    Style {
        id: style;
    }

    property bool isMaximized: Window.window
                               && Window.window.visibility === Window.Maximized;
    property bool isDark: fangSettings.currentStyle === "DARK";
    property color iconColor: isDark ? "#ffffff" : "#000000";

    height: winTitleBar
            ? (isMaximized ? winTitleBar.captionHeight : winTitleBar.titleBarHeight)
            : 0;

    // Minimize
    Rectangle {
        width: winTitleBar ? winTitleBar.buttonWidth : 0;
        height: captionButtons.height;
        color: minimizeMA.containsMouse
               ? (isDark ? Qt.rgba(1, 1, 1, 0.1) : Qt.rgba(0, 0, 0, 0.06))
               : "transparent";

        Text {
            anchors.centerIn: parent;
            font.family: "Segoe MDL2 Assets";
            font.pixelSize: 10;
            text: "\uE921";
            color: captionButtons.iconColor;
        }

        MouseArea {
            id: minimizeMA;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: Window.window.showMinimized();
        }
    }

    // Maximize / Restore
    Rectangle {
        width: winTitleBar ? winTitleBar.buttonWidth : 0;
        height: captionButtons.height;
        color: maximizeMA.containsMouse
               ? (isDark ? Qt.rgba(1, 1, 1, 0.1) : Qt.rgba(0, 0, 0, 0.06))
               : "transparent";

        Text {
            anchors.centerIn: parent;
            font.family: "Segoe MDL2 Assets";
            font.pixelSize: 10;
            text: captionButtons.isMaximized ? "\uE923" : "\uE922";
            color: captionButtons.iconColor;
        }

        MouseArea {
            id: maximizeMA;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: toggleMaximized();
        }
    }

    // Close
    Rectangle {
        width: winTitleBar ? winTitleBar.buttonWidth : 0;
        height: captionButtons.height;
        color: closeMA.containsMouse ? "#e81123" : "transparent";

        Text {
            anchors.centerIn: parent;
            font.family: "Segoe MDL2 Assets";
            font.pixelSize: 10;
            text: "\uE8BB";
            color: closeMA.containsMouse ? "#ffffff" : captionButtons.iconColor;
        }

        MouseArea {
            id: closeMA;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: Window.window.close();
        }
    }
}
