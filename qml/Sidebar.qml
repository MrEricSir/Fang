import QtQuick 2.4
import Fang 1.0

// Feed list sidebar
Item {
    id: sidebar;
    
    signal settingsClicked();
    signal addClicked();
    signal removeClicked();
    signal editClicked();
    signal refreshClicked();
    signal closeClicked();
    signal feedSelected();
    signal feedClicked();
    signal feedDoubleClicked();
    signal helpClicked();
    signal orderChanged();

    // Set this to the number of special feeds at the top so I can treat them with
    // the care and respect that they deserve.
    property int specialFeedCount: 0;
    
    // Read-only properties.
    property int buttonSize: 30 * style.scale;
    property variant listView: feedListView
    property bool feedsExist:  feedListModel.count > 1; // (There's always 1 item -- all news.)

    // This is called by RearrangableDelegate when the user creates a new folder.  It
    // expects the folder's database ID to be returned.
    function insertFolder(firstItemIndex) {
        return validator.insertFolder(firstItemIndex);
    }

    FeedValidator {
        id: validator
    }
    
    Rectangle {
        id: sidebarTopControls
        height: 40 * style.scale
        
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: style.color.sidebarToolbar
        z: 10 // higher than list
        
        Item {
            id: toolbarTop
            anchors.fill: parent
            anchors.margins: 5 * style.scale
            
            Image {
                id: fangLogo
                
                source: "images/fang_logo.svg"
                
                anchors.top: parent.top
                anchors.topMargin: 5 * style.scale
                anchors.left: parent.left
                anchors.leftMargin: 5 * style.scale
                height: 25 * style.scale
                asynchronous: true
                
                // Hack to make SVGs render with anti-aliasing
                sourceSize.width: width
                sourceSize.height: height
            }
            
            // HALP
            SidebarButton {
                id: helpButton;
                
                anchors.right: settingsButton.left;
                anchors.rightMargin: 10  * style.scale;
                
                width: buttonSize;
                height: buttonSize;
                
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_help.svg" :
                                                           "images/symbol_dark_help.svg";
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_help.svg" :
                                                                "images/symbol_help.svg";
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_help.svg" :
                                                                  "images/symbol_dark_help.svg";
                
                onClicked: {
                    helpClicked();
                }
            }
            
            // Fang settings.
            SidebarButton {
                id: settingsButton
                
                anchors.right: parent.right
                
                width: buttonSize
                height: buttonSize
                
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_gear.svg" :
                                                           "images/symbol_dark_gear.svg";
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_gear.svg" :
                                                                "images/symbol_gear.svg";
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_gear.svg" :
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
                width: 1 * style.scale
            }
            
            FangScrollView {
                anchors.fill: parent
                
                ListView {
                    id: feedListView
                    anchors.fill: parent

                    // Don't show this unless there's something in the list.
                    visible: feedsExist;
                    
                    // Only scroll if there's a need.
                    interactive: height < childrenRect.height
                    
                    delegate: FeedTitleDelegate {
                        id: titleDelegate
                        
                        // This sets the selected item in the C++ layer.
                        ListView.onIsCurrentItemChanged: {
                            if (ListView.isCurrentItem) {
                                //console.log("Item selected: ", feedListView.currentIndex)
                                sidebar.feedSelected();
                                feedListView.model.selectedIndex = feedListView.currentIndex
                            }
                        }

                        // Special feeds won't let themselves get dragged around.
                        numStationary: sidebar.specialFeedCount;
                        
                        onClicked: {
                            sidebar.feedClicked();
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
        height: 40 * style.scale
        
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: style.color.sidebarToolbar
        
        Item {
            id: toolbar
            anchors.fill: parent
            anchors.margins: 5 * style.scale
            
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
                
                x: buttonSize + (10 * style.scale)
                
                width: buttonSize
                height: buttonSize
                visible: !feedListView.model.selected.isSpecialFeed();
                
                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_pencil.svg"
                                                         : "images/symbol_dark_pencil.svg"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_pencil.svg"
                                                              : "images/symbol_pencil.svg"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_pencil.svg"
                                                                : "images/symbol_pencil.svg"
                
                onClicked: editClicked()
            }
            
            // Removes a feed.
            SidebarButton {
                id: removeButton
                
                x: buttonSize * 2 + (20 * style.scale)
                
                width: buttonSize
                height: buttonSize
                
                visible: !feedListView.model.selected.isSpecialFeed();
                
                imageURL: fangSettings.style === "LIGHT" ? "images/minus_dark.png"
                                                         : "images/minus.png"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/minus.png"
                                                              : "images/minus_dark.png"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/minus.png"
                                                                : "images/minus_dark.png"
                
                onClicked: removeClicked();
            }

            SidebarButton {
                id: refreshButton;

                x: toolbar.width - buttonSize;

                width: buttonSize;
                height: buttonSize;

                visible: feedsExist;

                imageURL: fangSettings.style === "LIGHT" ? "images/symbol_reload.svg"
                                                         : "images/symbol_dark_reload.svg"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_reload.svg"
                                                              : "images/symbol_reload.svg"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/symbol_dark_reload.svg"
                                                                : "images/symbol_reload.svg"

                onClicked: refreshClicked();
            }
            
            // Closes the sidebar.
            //
            // FEATURE REMOVED (for now?)
            // We can't have an Open button on iOS because we can't lay content on top of the Safari
            // browser

            /*
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
            */
        }
    }
}
