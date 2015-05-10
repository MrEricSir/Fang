import QtQuick 2.4

Row {
    id: dialogButtonGroup
    
    // Read-only: set the width of each child button to this
    property int buttonWidth: (width - (spacing * (children.length - 1))) / children.length
    
    spacing: 10
}
