import QtQuick 2.4
import QtQuick.Controls 1.2

// Let them drag the sidebar if they want to!
SplitView {
    id: fangSplitView;

    orientation: Qt.Horizontal

    handleDelegate: Rectangle { visible: false; }
}
