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

    // Set this to the number of special feeds at the top so I can treat them with
    // the care and respect that they deserve.
    property int specialFeedCount: 0;

    // Extra top padding for macOS transparent title bar (traffic lights).
    readonly property int titleBarInset: platform === "MAC" ? 38 * style.scale : 0;

    // Read-only properties.
    readonly property int buttonSize: 35 * style.scale;
    readonly property var listView: feedListView;
    readonly property bool feedsExist: feedListModel.count > 1; // (There's always 1 item -- all news.)

    // Guard to prevent clicks from passing "through" the context menu.
    property bool menuClickGuard: false;
    Timer {
        id: menuGuardTimer;
        interval: 200;
        onTriggered: sidebar.menuClickGuard = false;
    }



    // This is called by RearrangeableDelegate when the user creates a new folder.  It
    // expects the folder's database ID to be returned.
    function insertFolder(firstItemIndex) {
        return newsFeedInteractor.insertFolder(firstItemIndex);
    }

    SidebarToolbar {
        id: sidebarTopControls;
        separatorOnBottom: true;
        topInset: sidebar.titleBarInset;
        draggable: true;

        onDragStarted: startSystemMove();
        onDragDoubleClicked: maximizeToggle();

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;

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

            onClicked: sidebar.searchButtonClicked();
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
            
            // Whether the feed list overflows and needs a scrollbar.
            readonly property bool contentOverflows: feedListView.contentHeight > feedListView.height

            ListView {
                id: feedListView;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.left: parent.left;
                anchors.right: sidebarRightLine.left;
                clip: true;

                visible: feedsExist;
                interactive: contentHeight > height;

                ScrollBar.vertical: FangScrollBar {
                    id: sidebarScrollBar;
                    rightPadding: 4 * style.scale;
                }

                delegate: FeedTitleDelegate {
                    id: titleDelegate;

                    readonly property var thisFeed: index >= 0 ? feedListView.model.rowAs(index) : null;

                    ListView.onIsCurrentItemChanged: {
                        if (ListView.isCurrentItem) {
                            sidebar.feedSelected();
                            feedListView.model.selectedIndex = feedListView.currentIndex;
                        }
                    }

                    numStationary: sidebar.specialFeedCount;
                    acceptMouseEvents: !sidebar.menuClickGuard;

                    onClicked: {
                        sidebar.feedClicked();
                    }

                    onJumpToBookmark: {
                        sidebar.feedDoubleClicked();
                    }

                    onOrderChanged: {
                        sidebar.orderChanged();
                    }

                    ContextMenu.menu: {
                        if (isSearchFeed) return searchFeedMenu;
                        if (uid === -1) return null; // Pinned feed — no context menu
                        if (isSpecialFeed) return specialFeedMenu;
                        return feedMenu;
                    }

                    Menu {
                        id: searchFeedMenu;
                        popupType: Popup.Window;
                        onAboutToShow: sidebar.menuClickGuard = true;
                        onClosed: menuGuardTimer.restart();

                        MenuItem {
                            text: "Edit Search";
                            onTriggered: {
                                var dialog = openDialog("SearchDialog.qml");
                                dialog.initialQuery = newsFeedInteractor.getSearchQuery();
                            }
                        }

                        MenuItem {
                            text: "Close";
                            onTriggered: newsFeedInteractor.closeSearchFeed();
                        }
                    }

                    Menu {
                        id: specialFeedMenu;
                        popupType: Popup.Window;
                        onAboutToShow: sidebar.menuClickGuard = true;
                        onClosed: menuGuardTimer.restart();

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
                        popupType: Popup.Window;
                        onAboutToShow: sidebar.menuClickGuard = true;
                        onClosed: menuGuardTimer.restart();

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
