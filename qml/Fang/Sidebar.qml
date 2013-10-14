import QtQuick 1.1

// Feed list sidebar
Item {
    id: sidebar
    
    signal settingsClicked()
    signal addClicked()
    signal removeClicked()
    signal editClicked()
    signal closeClicked()
    signal feedSelected()
    signal feedDoubleClicked()
    
    // Read-only properties.
    property int buttonSize: 30
    property variant listView: feedListView
    
    Rectangle {
        id: sidebarTopControls
        height: 40
        
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: style.color.sidebarToolbar
        z: 10 // higher than list
        
        Item {
            id: toolbarTop
            anchors.fill: parent
            anchors.margins: 5
            
            // Fang settings.
            SidebarButton {
                id: settingsButton
                
                anchors.right: parent.right
                
                width: buttonSize
                height: buttonSize
                
                imageMargin: 5
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_gear.svg" :
                                                           "images/symbol_dark_gear.svg";
                
                onClicked: settingsClicked()
            }
        }
    }
    
    Item {
        id: sidebarFeedList
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: sidebarTopControls.bottom
        anchors.bottom: sidebarControls.top
        
        Rectangle {
            id: rectangle2
            color: style.color.sidebar
            anchors.fill: parent
            
            Rectangle {
                id: sidebarRightLine
                color: style.color.sidebarRightLine
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
        color: style.color.sidebarToolbar
        
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
                hoverColor: "#2a2"
                imageURL: fangSettings.style === "LIGHT" ? "images/plus.png" : "images/plus_dark.png"
                
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
                hoverColor: "#27a"
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_pencil.svg"
                                                         : "images/symbol_dark_pencil.svg"
                
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
                hoverColor: "#a22"
                imageURL: fangSettings.style === "LIGHT" ? "images/minus.png"
                                                         : "images/minus_dark.png"
                
                onClicked: removeClicked()
            }
            
            // Closes the sidebar.
            SidebarButton {
                id: closeButton
                
                x: toolbar.width - buttonSize
                
                width: buttonSize
                height: buttonSize
                
                imageMargin: 5
                imageURL: fangSettings.style === "LIGHT" ? "images/arrows_left.png"
                                                         : "images/arrows_left_dark.png"
                                                           
                
                onClicked: closeClicked()
            }
        }
    }
}
