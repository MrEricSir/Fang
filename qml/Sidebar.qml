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
    readonly property int buttonSize: 35 * style.scale;
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

    SidebarToolbar {
        id: sidebarTopControls;
        separatorOnBottom: true;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;

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

            source: fangSettings.currentStyle === "LIGHT"
                    ? "images/fang_logo_dark.svg" : "images/fang_logo.svg";

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 5 * style.scale;
            height: 28 * style.scale;
            asynchronous: true;

            // Hack to make SVGs render with anti-aliasing
            sourceSize.width: width;
            sourceSize.height: height;
        }

        // Search
        SidebarButton {
            id: searchButton;

            anchors.right: helpSettingsGroup.left;
            anchors.rightMargin: 10 * style.scale;
            anchors.verticalCenter: parent.verticalCenter;

            width: buttonSize;
            height: buttonSize;

            lightImageURL: "images/symbol_search.svg";
            darkImageURL: "images/symbol_dark_search.svg";

            // Show toggled icon if search is open.
            property bool isSearchActive: feedListView.model.selected && feedListView.model.selected.isSearchFeed();
            toggled: isSearchActive;

            onClicked: sidebar.toggleSearch();
        }

        // Help + Settings grouped in a pill.
        Rectangle {
            id: helpSettingsGroup;

            anchors.right: parent.right;
            anchors.rightMargin: 5 * style.scale;
            anchors.verticalCenter: parent.verticalCenter;

            width: buttonSize * 2 + helpSettingsDivider.width;
            height: buttonSize;
            radius: height / 2;
            color: "transparent";
            border.color: style.color.sidebarButtonBorder;
            border.width: 1;

            Row {
                anchors.fill: parent;

                SidebarButton {
                    id: helpButton;

                    width: buttonSize;
                    height: buttonSize;
                    radius: 0;
                    borderColor: "transparent";

                    lightImageURL: "images/symbol_help.svg";
                    darkImageURL: "images/symbol_dark_help.svg";

                    onClicked: helpClicked();
                }

                Rectangle {
                    id: helpSettingsDivider;
                    width: 1;
                    height: parent.height * 0.6;
                    anchors.verticalCenter: parent.verticalCenter;
                    color: style.color.sidebarButtonBorder;
                }

                SidebarButton {
                    id: settingsButton;

                    width: buttonSize;
                    height: buttonSize;
                    radius: 0;
                    borderColor: "transparent";

                    lightImageURL: "images/symbol_gear.svg";
                    darkImageURL: "images/symbol_dark_gear.svg";

                    onClicked: settingsClicked();
                }
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

                        ContextMenu.menu: isSpecialFeed ? specialFeedMenu : feedMenu;

                        Menu {
                            id: specialFeedMenu;
                            popupType: Popup.Native;

                            MenuItem {
                                text: "Refresh";
                                onTriggered: refreshFeedClicked(thisFeed);
                            }

                            MenuItem {
                                text: unreadCount !== 0 ? "Mark all as read" : "Mark all as unread";
                                onTriggered: unreadCount !== 0 ? markAllAsReadClicked(thisFeed) : markAllAsUnreadClicked(thisFeed);
                            }
                        }

                        Menu {
                            id: feedMenu;
                            popupType: Popup.Native;

                            MenuItem {
                                text: "Refresh";
                                onTriggered: refreshFeedClicked(thisFeed);
                            }

                            MenuItem {
                                text: unreadCount !== 0 ? "Mark all as read" : "Mark all as unread";
                                onTriggered: unreadCount !== 0 ? markAllAsReadClicked(thisFeed) : markAllAsUnreadClicked(thisFeed);
                            }

                            MenuItem {
                                text: "Edit";
                                onTriggered: openDialog("EditDialog.qml", thisFeed);
                            }

                            MenuItem {
                                text: "Remove";
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
    
    SidebarToolbar {
        id: sidebarControls;
        separatorOnBottom: false;

        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;

        // Add + Edit + Remove grouped in a pill.
        // When a special feed is selected, Edit/Remove hide and Add
        // becomes a standalone circle.
        Rectangle {
            id: feedActionsGroup;

            property bool showEditRemove: feedListView.model.selected
                                          && !feedListView.model.selected.isSpecialFeed();

            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.leftMargin: 10 * style.scale;

            height: buttonSize;
            radius: height / 2;
            color: "transparent";
            border.color: style.color.sidebarButtonBorder;
            border.width: 1;

            states: [
                State {
                    name: "expanded";
                    when: feedActionsGroup.showEditRemove;
                    PropertyChanges {
                        feedActionsGroup { width: buttonSize * 3 + 2 }
                        addEditDivider { width: 1; opacity: 1 }
                        editButton { width: buttonSize; opacity: 1 }
                        editRemoveDivider { width: 1; opacity: 1 }
                        removeButton { width: buttonSize; opacity: 1 }
                    }
                },
                State {
                    name: "collapsed";
                    when: !feedActionsGroup.showEditRemove;
                    PropertyChanges {
                        feedActionsGroup { width: buttonSize }
                        addEditDivider { width: 0; opacity: 0 }
                        editButton { width: 0; opacity: 0 }
                        editRemoveDivider { width: 0; opacity: 0 }
                        removeButton { width: 0; opacity: 0 }
                    }
                }
            ]

            transitions: Transition {
                NumberAnimation {
                    properties: "width,opacity";
                    duration: 250;
                    easing.type: Easing.InOutQuad;
                }
            }

            Row {
                anchors.fill: parent;

                SidebarButton {
                    id: addButton;

                    width: buttonSize;
                    height: buttonSize;
                    radius: 0;
                    borderColor: "transparent";

                    lightImageURL: "images/plus_dark.png";
                    darkImageURL: "images/plus.png";

                    onClicked: addClicked();
                }

                Rectangle {
                    id: addEditDivider;
                    height: parent.height * 0.6;
                    anchors.verticalCenter: parent.verticalCenter;
                    color: style.color.sidebarButtonBorder;
                }

                SidebarButton {
                    id: editButton;

                    height: buttonSize;
                    radius: 0;
                    borderColor: "transparent";
                    clip: true;

                    lightImageURL: "images/symbol_pencil.svg";
                    darkImageURL: "images/symbol_dark_pencil.svg";

                    onClicked: editClicked();
                }

                Rectangle {
                    id: editRemoveDivider;
                    height: parent.height * 0.6;
                    anchors.verticalCenter: parent.verticalCenter;
                    color: style.color.sidebarButtonBorder;
                }

                SidebarButton {
                    id: removeButton;

                    height: buttonSize;
                    radius: 0;
                    borderColor: "transparent";
                    clip: true;

                    lightImageURL: "images/minus_dark.png";
                    darkImageURL: "images/minus.png";

                    onClicked: removeClicked();
                }
            }
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
    }
}
