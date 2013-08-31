import QtQuick 1.1

// Feed list sidebar
Item {
    id: sidebar
    
    signal addClicked()
    signal removeClicked()
    signal editClicked()
    signal closeClicked()
    signal feedSelected()
    signal feedDoubleClicked()
    
    // Read-only properties.
    property int buttonSize: 30
    property variant listView: feedListView
    
    Item {
        id: sidebarFeedList
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: sidebarControls.top
        
        Rectangle {
            id: rectangle2
            color: "#e5e5e5"
            anchors.fill: parent
            
            Rectangle {
                id: sidebarRightLine
                color: "#ccc"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: 1
            }
            
            ListView {
                id: feedListView
                anchors.fill: parent
                
                // Only move if there's a need.
                interactive: height < childrenRect.height
                
                delegate: FeedTitleDelegate {
                    id: titleDelegate
                    
                    // This sets the selected item in the C++ layer.
                    ListView.onIsCurrentItemChanged: {
                        if (ListView.isCurrentItem) {
                            feedListView.model.selected = self
                            sidebar.feedSelected();
                        }
                    }
                    
                    onDoubleClicked: {
                        feedDoubleClicked();
                    }
                }
                
                model: feedListModel
            }
            
            ScrollBar {
                id: feedListViewScroll
                target: feedListView
            }
        }
    }
    
    // Mini-toolbar under the sidebar.
    Rectangle {
        id: sidebarControls
        height: 40
        
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#535353"
        
        Item {
            id: toolbar
            anchors.fill: parent
            anchors.margins: 5
            
            // Adds a feed.
            SidebarButton {
                id: addButton
                
                x: 0
                
                width: buttonSize
                height: buttonSize
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#2a2"
                imageURL: "images/plus.png"
                
                onClicked: addClicked()
            }
            
            // Edits a feed.
            SidebarButton {
                id: editButton
                
                x: buttonSize + 10
                
                width: buttonSize
                height: buttonSize
                
                visible: feedListView.currentIndex > 0
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#27a"
                imageURL: "images/symbol_pencil.svg"
                
                onClicked: editClicked()
            }
            
            // Removes a feed.
            SidebarButton {
                id: removeButton
                
                x: buttonSize * 2 + 20
                
                width: buttonSize
                height: buttonSize
                
                visible: feedListView.currentIndex > 0
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#a22"
                imageURL: "images/minus.png"
                
                onClicked: removeClicked()
            }
            
            // Closes the sidebar.
            SidebarButton {
                id: closeButton
                
                x: toolbar.width - buttonSize
                
                width: buttonSize
                height: buttonSize
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#ccc"
                imageURL: "images/arrows_left.png"
                
                onClicked: closeClicked()
            }
        }
    }
}
