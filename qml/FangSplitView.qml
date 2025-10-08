import QtQuick
import QtQuick.Controls

// Let them drag the sidebar if they want to!
SplitView {
    id: fangSplitView;

    orientation: Qt.Horizontal;

    // Relevant fields from the parent's handle, with a transparent color.
    handle: Rectangle {
        implicitWidth: fangSplitView.orientation === Qt.Horizontal ? 6 : fangSplitView.width;
        implicitHeight: fangSplitView.orientation === Qt.Horizontal ? fangSplitView.height : 6;
        color: "transparent";
    }
}
