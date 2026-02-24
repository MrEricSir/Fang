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

    // Child items go here.
    default property alias content: contentItem.data;

    height: 48 * style.scale;
    color: style.color.sidebarToolbar;
    z: 10;

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
        anchors.margins: 5 * style.scale;
    }
}
