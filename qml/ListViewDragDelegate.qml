import QtQuick 2.0

/**
  * This is a draggable delegate for a ListView.
  *
  * Each element in the list model must have a string named "dropTarget" which is by default
  * set to "none".
  *
  * If you want a certain number of items at the top to not be draggable, set numUndraggable
  * to that number, okay?  Geez.
  */
Rectangle {
    id: dragDelegateBorder
    
    // Don't use a MouseArea!!  Instead, use these signals to find when the item is clicked.
    signal clicked()
    signal doubleClicked()
    
    // Subscribe to this signal to know when the list may have changed order.
    signal orderChanged()

    // Sets the number of undraggable items at the top of the list.
    property int numUndraggable: 0;
    
    // Drag border color and height.
    property color dragBorderColor: "black";
    property int dragBorderHeight: 1;
    property bool dragEnabled: true;
    
    // PRIVATE:
    
    // This allows children to be positioned within the element.
    default property alias contents: placeholder.children
    
    width: parent.width
    height: placeholder.childrenRect.height
    
    color: "transparent"
    
    Rectangle {
        id: topBorder
        
        color: dragBorderColor
        height: dragBorderHeight
        width: parent.width
        visible: dropTarget === "top"
        
        anchors.top: parent.top
    }
    
    // Draws d&d drop-target borders for a given index.
    // Valid positions are "top", "bottom", and "none"
    function drawDnDBorders(index, position) {
        dragDelegateBorder.ListView.view.model.setData(index, "dropTarget", position)
    }
    
    // Makes all the drag borders from a DND job go away.
    function removeDragBorders() {
        for (var i = 0; i < dragDelegateBorder.ListView.view.model.count; i++)
            drawDnDBorders(i, "none");
    }
    
    Item {
        id: placeholder
    }
    
    Rectangle {
        id: bottomBorder
        
        color: dragBorderColor
        height: dragBorderHeight
        width: parent.width
        visible: dropTarget === "bottom"
        
        anchors.bottom: parent.bottom
    }
    
    MouseArea {
        id: dragArea
        anchors.fill: parent
        property real positionStarted: 0
        property real positionEnded: 0
        property int positionsMoved: Math.floor((positionEnded - positionStarted) / dragDelegateBorder.height)
        
        // New index (uncapped)
        property int newPosition: index + positionsMoved
        
        // New index (within range)
        property int cappedNewPosition: Math.max(numUndraggable, Math.min(dragDelegateBorder.ListView.view.count - 1, newPosition));
        
        // Whether or not the rect is currently being held.
        property bool held: false
        
        drag.axis: Drag.YAxis
        
        onClicked: dragDelegateBorder.clicked()
        onDoubleClicked: dragDelegateBorder.doubleClicked()
        
        onPressAndHold: {
            if (!dragEnabled) {
                return;
            }
            
            dragDelegateBorder.z = 2
            positionStarted = dragDelegateBorder.y
            dragArea.drag.target = dragDelegateBorder
            dragDelegateBorder.opacity = 0.6
            dragDelegateBorder.ListView.view.interactive = false
            drag.maximumY = (dragDelegateBorder.ListView.view.height - dragDelegateBorder.height - 1 + dragDelegateBorder.ListView.view.contentY)
            drag.minimumY = 0
            
            held = true
        }
        
        onPositionChanged: {
            if (!held)
                return;
            
            positionEnded = dragDelegateBorder.y;
            
            // Draw the new drag borders.
            removeDragBorders();
            if (Math.abs(positionsMoved) > 0 && newPosition < dragDelegateBorder.ListView.view.count) {
                if (positionsMoved > 0)
                    drawDnDBorders(cappedNewPosition, "bottom");
                else
                    drawDnDBorders(cappedNewPosition, "top");
            }
            
            //console.log("pos moved: ", positionsMoved, " index: ", index, " newPosition: ", newPosition)
        }
        
        onReleased: {
            // Handle Press & Hold events
            if (held) {
                held = false;
                
                dragDelegateBorder.z = 1
                dragDelegateBorder.opacity = 1
                dragDelegateBorder.ListView.view.interactive = true
                dragArea.drag.target = null
                
                removeDragBorders();
                
                if (cappedNewPosition === index) {
                    // We didn't move; snap the rectangle back in place.
                    dragDelegateBorder.y = positionStarted
                } else {
                    // Do the move!
                    dragDelegateBorder.ListView.view.model.move(index, cappedNewPosition);
                }
                
                // We emit signal.  Main screen turn on.
                orderChanged();
                
                return;
            }
        }
    }
}
