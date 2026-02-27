import QtQuick

/**
  * Toolbar for the top and bottom of the sidebar.
  * Child items will appear inside "content."
  */
Rectangle {
    id: sidebarToolbar;

    Style {
        id: style;
    }

    // Set to true for top toolbar (separator on bottom edge),
    // false for bottom toolbar (separator on top edge).
    property bool separatorOnBottom: true;

    // Extra top padding (e.g. for macOS traffic lights under transparent title bar).
    property int topInset: 0;

    // Enable a background drag area covering the full toolbar (including inset).
    // Buttons in contentItem are on top and receive clicks first.
    property bool draggable: false;
    signal dragStarted();
    signal dragDoubleClicked();

    // Child items go here.
    default property alias content: contentItem.data;

    height: 48 * style.scale + topInset;
    color: style.color.sidebarToolbar;
    z: 10;

    // Window drag area.
    MouseArea {
        anchors.fill: parent;
        visible: sidebarToolbar.draggable;

        onPressed: (mouse) => {
            sidebarToolbar.dragStarted();
        }

        onDoubleClicked: {
            sidebarToolbar.dragDoubleClicked();
        }
    }

    // Separator line.
    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: separatorOnBottom ? parent.bottom : undefined;
        anchors.top: separatorOnBottom ? undefined : parent.top;
        height: 1;
        color: style.color.sidebarRightLine;
        z: 1;
    }

    Item {
        id: contentItem;
        anchors.fill: parent;
        anchors.topMargin: 5 * style.scale + topInset;
        anchors.leftMargin: 5 * style.scale;
        anchors.rightMargin: 5 * style.scale;
        anchors.bottomMargin: 5 * style.scale;
    }
}
