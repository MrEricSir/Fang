import QtQuick
import QtQuick.Controls
import Fang 1.0

// Feed list sidebar
Item {
    id: sidebar;

    signal settingsClicked();
    signal addClicked();
    signal removeClicked();
    signal editClicked();
    signal refreshFeedClicked(var feed);
    signal markAllAsReadClicked(var feed);
    signal markAllAsUnreadClicked(var feed);
    signal refreshCurrentFeedClicked();
    signal closeClicked();
    signal feedSelected();
    signal feedClicked();
    signal feedDoubleClicked();
    signal helpClicked();
    signal orderChanged();
    signal maximizeToggle();
    signal searchButtonClicked();
    signal searchRequested(string query);
    signal searchCleared();

    // Set this to the number of special feeds at the top so I can treat them with
    // the care and respect that they deserve.
    property int specialFeedCount: 0;
    
    // Read-only properties.
    readonly property int buttonSize: 25 * style.scale;
    readonly property var listView: feedListView;
    readonly property bool feedsExist: feedListModel.count > 1; // (There's always 1 item -- all news.)

    // This is called by RearrangeableDelegate when the user creates a new folder.  It
    // expects the folder's database ID to be returned.
    function insertFolder(firstItemIndex) {
        return newsFeedInteractor.insertFolder(firstItemIndex);
    }

    // Toggles the search feed open/closed.
    function toggleSearch() {
        if (searchButton.isSearchActive) {
            // Close search: Close the special feed and switch to All News.
            newsFeedInteractor.closeSearchFeed();
            feedListView.currentIndex = 0;
        } else {
            // Open search: Add and select the special feed.
            newsFeedInteractor.showSearchFeed();
            Qt.callLater(function() {
                feedListView.currentIndex = sidebar.specialFeedCount - 1;
            });
        }
    }

    Rectangle {
        id: sidebarTopControls;
        height: 40 * style.scale;
        
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        color: style.color.sidebarToolbar;
        z: 10; // higher than list
        
        Item {
            id: toolbarTop;
            anchors.fill: parent;
            anchors.margins: 5 * style.scale;

            // Allow top of sidebar to drag window and maximize/restore size.
            MouseArea {
                anchors.fill: parent;

                onPressed: (mouse) => {
                    startSystemMove();
                }

                onDoubleClicked: {
                    maximizeToggle();
                }
            }
            
            Image {
                id: fangLogo;
                
                source: "images/fang_logo.svg";
                
                anchors.top: parent.top;
                anchors.topMargin: 5 * style.scale;
                anchors.left: parent.left;
                anchors.leftMargin: 5 * style.scale;
                height: 25 * style.scale;
                asynchronous: true;
                
                // Hack to make SVGs render with anti-aliasing
                sourceSize.width: width;
                sourceSize.height: height;
            }
            
            // Search
            SidebarButton {
                id: searchButton;

                anchors.right: helpButton.left;
                anchors.rightMargin: 15 * style.scale;
                anchors.verticalCenter: parent.verticalCenter;

                width: buttonSize;
                height: buttonSize;

                lightImageURL: "images/symbol_search.svg";
                darkImageURL: "images/symbol_dark_search.svg";

                // Show togled icon if search is open.
                property bool isSearchActive: feedListView.model.selected && feedListView.model.selected.isSearchFeed();
                toggled: isSearchActive;

                onClicked: sidebar.toggleSearch();
            }

            // HALP
            SidebarButton {
                id: helpButton;

                anchors.right: settingsButton.left;
                anchors.rightMargin: 15 * style.scale;
                anchors.verticalCenter: parent.verticalCenter;

                width: buttonSize;
                height: buttonSize;

                lightImageURL: "images/symbol_help.svg";
                darkImageURL: "images/symbol_dark_help.svg";

                onClicked: {
                    helpClicked();
                }
            }
            
            // Fang settings.
            SidebarButton {
                id: settingsButton;
                
                anchors.right: parent.right;
                anchors.rightMargin: 5 * style.scale;
                anchors.verticalCenter: parent.verticalCenter;
                
                width: buttonSize;
                height: buttonSize;
                
                lightImageURL: "images/symbol_gear.svg";
                darkImageURL: "images/symbol_dark_gear.svg";
                
                onClicked: settingsClicked();
            }
        }
    }
    
    Item {
        id: sidebarFeedList;
        anchors.right: parent.right;
        anchors.left: parent.left;
        anchors.top: sidebarTopControls.bottom;
        anchors.bottom: sidebarControls.top;
        
        Rectangle {
            id: rectangle2;
            color: style.color.sidebar;
            anchors.fill: parent;
            
            Rectangle {
                id: sidebarRightLine;
                color: style.color.sidebarRightLine;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.right: parent.right;
                width: 1 * style.scale;
            }
            
            // Covers the scrollbar briefly while the selection highlight
            // animates to make room, preventing visual overlap.
            Rectangle {
                id: scrollBarCover;
                anchors.right: sidebarRightLine.left;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                width: scrollView.effectiveScrollBarWidth;
                color: style.color.sidebar;
                visible: scrollBarCoverTimer.running;
                z: 10;
            }

            Timer {
                id: scrollBarCoverTimer;
                interval: 260;
            }

            Connections {
                target: scrollView;
                function onEffectiveScrollBarWidthChanged() {
                    if (scrollView.effectiveScrollBarWidth > 0) {
                        scrollBarCoverTimer.restart();
                    }
                }
            }

            FangScrollView {
                id: scrollView;
                anchors.fill: parent;
                
                ListView {
                    id: feedListView;
                    anchors.fill: parent;

                    // Don't show this unless there's something in the list.
                    visible: feedsExist;
                    
                    // Only scroll if there's a need.
                    interactive: height < childrenRect.height;
                    
                    delegate: FeedTitleDelegate {
                        id: titleDelegate;

                        // Represents this current feed when its index is valid (not being removed, etc.)
                        readonly property var thisFeed: index >= 0 ? feedListView.model.rowAs(index) : null;
                        
                        // This sets the selected item in the C++ layer.
                        ListView.onIsCurrentItemChanged: {
                            if (ListView.isCurrentItem) {
                                //console.log("Item selected: ", feedListView.currentIndex)
                                sidebar.feedSelected();
                                feedListView.model.selectedIndex = feedListView.currentIndex;
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

                        onSearchRequested: (query) => {
                            sidebar.searchRequested(query);
                        }

                        onSearchCleared: {
                            sidebar.searchCleared();
                        }

                        ContextMenu.menu: Menu {
                            id: contextMenu;

                            MenuItem {
                                text: "Refresh";
                                onTriggered: refreshFeedClicked(thisFeed);
                            }

                            MenuItem {
                                text: unreadCount !== 0 ? "Mark all as read" : "Mark all as unread";
                                visible: bookmarksEnabled;
                                height: visible ? implicitHeight : 0;
                                onTriggered: unreadCount !== 0 ? markAllAsReadClicked(thisFeed) : markAllAsUnreadClicked(thisFeed);
                            }

                            MenuItem {
                                text: "Edit";
                                visible: !isSpecialFeed;
                                height: visible ? implicitHeight : 0;
                                onTriggered: openDialog("EditDialog.qml", thisFeed);
                            }

                            MenuItem {
                                text: "Remove";
                                visible: !isSpecialFeed;
                                height: visible ? implicitHeight : 0;
                                onTriggered: openDialog("RemoveDialog.qml", thisFeed);
                            }
                        }
                    }
                    
                    model: feedListModel;
                    
                    Connections {
                        target: feedListModel;
                        
                        // This allows C++ to set the selected item.
                        function onSelectedIndexChanged(selectedIndex) {
                            console.log("selected index:", feedListModel.selectedIndex);
                            if (selectedIndex !== feedListView.currentIndex) {
                                feedListView.currentIndex = selectedIndex;
                            }
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
        id: sidebarControls;
        height: 40 * style.scale;
        
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        color: style.color.sidebarToolbar;
        
        Item {
            id: toolbar;
            anchors.fill: parent;
            
            // Adds a feed.
            SidebarButton {
                id: addButton;
                
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.leftMargin: 10 * style.scale;
                
                width: buttonSize;
                height: buttonSize;
                
                lightImageURL: "images/plus_dark.png";
                darkImageURL: "images/plus.png";
                
                onClicked: addClicked();
            }
            
            // Edits a feed.
            SidebarButton {
                id: editButton;
                
                anchors.right: removeButton.left;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.rightMargin: 15 * style.scale;
                
                width: buttonSize;
                height: buttonSize;
                visible: !feedListView.model.selected.isSpecialFeed();
                
                lightImageURL: "images/symbol_pencil.svg";
                darkImageURL: "images/symbol_dark_pencil.svg";
                
                onClicked: editClicked();
            }
            
            // Removes a feed.
            SidebarButton {
                id: removeButton;
                
                anchors.right: refreshButton.left;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.rightMargin: 15 * style.scale;
                
                width: buttonSize;
                height: buttonSize;
                
                visible: !feedListView.model.selected.isSpecialFeed();
                
                lightImageURL: "images/minus_dark.png";
                darkImageURL: "images/minus.png";
                
                onClicked: removeClicked();
            }

            SidebarButton {
                id: refreshButton;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.rightMargin: 10 * style.scale;

                width: buttonSize;
                height: buttonSize;

                visible: feedsExist;

                lightImageURL: "images/symbol_reload.svg";
                darkImageURL: "images/symbol_dark_reload.svg";

                onClicked: refreshCurrentFeedClicked();
            }
            
            // Closes the sidebar.
            //
            // FEATURE REMOVED (for now?)
            // We can't have an Open button on iOS because we can't lay content on top of the Safari
            // browser

            /*
            SidebarButton {
                id: closeButton;
                
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.rightMargin: 10 * style.scale;
                
                width: buttonSize
                height: buttonSize
                
                lightImageURL: "images/".svg";
                darkImageURL: "images/arrows_left_dark.svg";
                
                onClicked: closeClicked();
            }
            */
        }
    }
}
