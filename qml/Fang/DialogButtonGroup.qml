import QtQuick 1.1

Row {
    id: dialogButtonGroup
    
    // Read-only: set the width of each child button to this
    property int buttonWidth: width / children.length - spacing / children.length
    
    spacing: 10
}
