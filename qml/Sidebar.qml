import QtQuick 2.0

// Feed list sidebar
Item {
    id: sidebar;
    
    signal settingsClicked();
    signal addClicked();
    signal removeClicked();
    signal editClicked();
    signal closeClicked();
    signal feedSelected();
    signal feedDoubleClicked();
    signal helpClicked();
    signal orderChanged();
    
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
            
            Image {
                id: fangLogo
                
                source: "images/fang_logo.svg"
                
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                height: 25
                asynchronous: true
                
                // Hack to make SVGs render with anti-aliasing
                sourceSize.width: width
                sourceSize.height: height
            }
            
            // HALP
            SidebarButton {
                id: helpButton;
                
                anchors.right: settingsButton.left;
                anchors.rightMargin: 10;
                
                width: buttonSize;
                height: buttonSize;
                
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_help.svg" :
                                                           "images/symbol_help.svg";
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_help.svg" :
                                                                "images/symbol_dark_help.svg";
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_help.svg" :
                                                                  "images/symbol_help.svg";
                
                onClicked: helpClicked();
            }
            
            // Fang settings.
            SidebarButton {
                id: settingsButton
                
                anchors.right: parent.right
                
                width: buttonSize
                height: buttonSize
                
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_gear.svg" :
                                                           "images/symbol_gear.svg";
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_gear.svg" :
                                                                "images/symbol_dark_gear.svg";
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_gear.svg" :
                                                                  "images/symbol_gear.svg";
                
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
            
            FangScrollView {
                anchors.fill: parent
                
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
                                console.log("Item selected: ", feedListView.currentIndex)
                                feedListView.model.selectedIndex = feedListView.currentIndex
                                sidebar.feedSelected();
                            }
                        }
                        
                        onJumpToBookmark: {
                            sidebar.feedDoubleClicked();
                        }
                        
                        onOrderChanged: {
                            sidebar.orderChanged();
                        }
                    }
                    
                    model: feedListModel
                    
                    Connections {
                        target: feedListModel
                        
                        // This allows C++ to set the selected item.
                        onSelectedIndexChanged: {
                            if (selectedIndex !== feedListView.currentIndex)
                                feedListView.currentIndex = selectedIndex;
                        }
                    }
                    
                    displaced: Transition {
                        NumberAnimation { properties: "x,y"; duration: 50 }
                    }
                }
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
                
                imageURL: fangSettings.style === "LIGHT" ? "images/plus_dark.png" : "images/plus.png"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/plus.png" : "images/plus_dark.png"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/plus.png" : "images/plus_dark.png"
                
                onClicked: addClicked()
            }
            
            // Edits a feed.
            SidebarButton {
                id: editButton
                
                x: buttonSize + 10
                
                width: buttonSize
                height: buttonSize
                
                visible: feedListView.currentIndex > 0
                
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_pencil.svg"
                                                         : "images/symbol_pencil.svg"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_pencil.svg"
                                                              : "images/symbol_dark_pencil.svg"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_pencil.svg"
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
                
                imageURL: fangSettings.style === "LIGHT" ? "images/minus_dark.png"
                                                         : "images/minus.png"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/minus.png"
                                                              : "images/minus_dark.png"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/minus.png"
                                                                : "images/minus_dark.png"
                
                onClicked: removeClicked()
            }
            
            // Closes the sidebar.
            SidebarButton {
                id: closeButton
                
                x: toolbar.width - buttonSize
                
                width: buttonSize
                height: buttonSize
                
                imageURL: fangSettings.style === "LIGHT" ? "images/arrows_left_dark.png"
                                                         : "images/arrows_left.png"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/arrows_left.png"
                                                              : "images/arrows_left_dark.png"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/arrows_left.png"
                                                                : "images/arrows_left_dark.png"
                
                onClicked: closeClicked()
            }
        }
    }
}
