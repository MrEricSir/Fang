import QtQuick

Row {
    id: dialogButtonGroup;
    
    // Read-only: set the width of each child button to this
    readonly property int buttonWidth: (width - (spacing * (children.length - 1))) / children.length;
    
    spacing: 10;
}
