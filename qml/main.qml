import QtQuick
import QtQuick.Window
import Fang 1.0
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import QtCore

// Can't use ApplicationWindow because it leaves spaces for an action bar (menu) on Android.
Window {
    id: main;

    width: windowSettings.width;
    height: windowSettings.height;

    // True once the page load has hit 100%
    property alias isWebPageLoaded: news.isWebPageLoaded;

    visibility: {
        if (platform == "ANDROID") {
            return Window.Maximized;
        }

        if (windowSettings.maximized) {
            return Window.Maximized;
        }

        // Default
        return Window.Windowed;
    }
    
    minimumWidth: Math.max(640, sidebar.width + minimumNewsWidth);
    minimumHeight: 450;

    // Treat as const
    property int minimumSidebarWidth: (platform === "ANDROID") ? 260 : 230;
    property int minimumNewsWidth: 400;

    // Toggles between maximized and normal window size.
    function toggleMaximized() {
        if (!isDesktop) {
            // Doesn't make sense on mobile.
            return;
        }

        if (visibility === Window.Maximized) {
            showNormal();
        } else {
            showMaximized();
        }
    }
    
    // Style object.
    Style {
        id: style;
    }

    visible: true;

    // Prevents all-white window from appearing on Windows.
    flags: platform === "WIN" ? Qt.Window | Qt.FramelessWindowHint : Qt.Window;

    // The "interactor" is what talks to the C++ layer.
    NewsFeedInteractor {
        id: newsFeedInteractor;
    }
    
    FangSettings {
        id: fangSettings;
        objectName: "fangSettings"; // Don't change this!
    }

    // Search history.
    // Contents of each item:
    // { query: "...", scopeType: "global"|"feed", scopeId: -1|feedId, feedTitle: "All News"|"Feed Name" }
    property var searchHistory: []

    function addSearchHistory(query, scopeType, scopeId, feedTitle) {
        // Remove any duplicate (same query + scopeType + scopeId).
        var history = searchHistory.filter(function(entry) {
            return !(entry.query === query && entry.scopeType === scopeType && entry.scopeId === scopeId);
        });
        // Prepend new entry.
        history.unshift({ query: query, scopeType: scopeType, scopeId: scopeId, feedTitle: feedTitle });
        // Cap at 10.
        if (history.length > 10) history.length = 10;
        searchHistory = history;
    }

    // Latest version, will be displayed after UI has settled.
    property string pendingUpdateVersion: "";

    // Check for update notifications.
    Connections {
        target: fangSettings;

        function onUpdateAvailable(newVersion) {
            console.log("Update available: " + newVersion);
            pendingUpdateVersion = newVersion;
            showPendingUpdateIfReady();
        }
    }

    // Displays the update dialog if there's a new version. Will only be shown
    // after the UI has started and settled.
    function showPendingUpdateIfReady() {
        if (pendingUpdateVersion !== "" && openDialogs.length === 0) {
            var dialog = openDialog("UpdateDialog.qml");
            if (dialog) {
                dialog.newVersion = pendingUpdateVersion;

                // Set this version as "seen."
                fangSettings.lastSeenVersion = pendingUpdateVersion;
                pendingUpdateVersion = "";
            }
        }
    }
    
    // Save window settings on close.
    Component.onDestruction: {
        windowSettings.save();
    }

    // Read-only.
    property bool wasMaximized: false;
    onVisibilityChanged: {
        if (main.visibility === Window.Maximized) {
            wasMaximized = true;
        } else if (main.visibility === Window.Windowed) {
            wasMaximized = false;
        }
    }
    
    // Saves window dimensions and whether or not we're maximized.
    Settings {
        id: windowSettings
        
        function save() {
            if (main.wasMaximized) {
                // We're MAXimized!
                windowSettings.maximized = true;
            } else {
                // We're windowed!
                windowSettings.maximized = false;
                windowSettings.width = main.width;
                windowSettings.height = main.height;
            }
        }
        
        category: "FangWindow"
        
        // Defaults
        property bool maximized: false;
        property int width: 900;
        property int height: 700;

        // Standard settings.
        property alias sidebarWidth: sidebar.width;
    }

    // Read-only: List of all open dialogs
    property var openDialogs: []
    
    // Creates and opens a dialog.  The dialog is returned in
    // case you wanna mess with it and shit.
    function openDialog(dialogName, feed=null) {
        console.log("openDialog(" + dialogName + ")")
        news.isVisible = false; // webview hack
        var component = Qt.createComponent(dialogName);
        var dialog = component.createObject(
                    main, {"x": 0, "y": 0, "feed": feed});
        
        if (dialog === null) {
            // Error Handling
            console.log("Error creating dialog: " + dialogName);
            console.log("createObject error: ", component.errorString());
            
            return null;
        }
        
        // Fade out current screen.
        if (openDialogs.length > 0) {
            // Current screen is dialog.
            openDialogs[openDialogs.length - 1].fadeOut();
        } else {
            // Current screen is mainFrame
            mainFrame.fadeOut();
        }
        
        // Pop 'er open!
        openDialogs.push(dialog);
        news.newsFocus = false;
        dialog.index = openDialogs.length
        dialog.onDialogClosed.connect(onDialogClosed);
        dialog.onDialogClosing.connect(onDialogClosing);
        dialog.open();
        
        return dialog;
    }
    
    // Called when a dialog is starting to close.
    function onDialogClosing(dialog) {
        // The previous screen will either be a dialog or the main frame.
        // Find it and fade it in!
        var i = openDialogs.indexOf(dialog) - 1;
        if (i >= 0) {
            openDialogs[i].fadeIn();
        } else {
            mainFrame.fadeIn();
        }
        
    }
    
    // Called when a dialog is closed.
    function onDialogClosed(dialog) {
        var wasSplashScreen = dialog.isSplashScreen;

        // Remove the entry.
        openDialogs.splice(openDialogs.indexOf(dialog), 1);
        delete dialog;

        // If it was the last one, give focus back to news
        if (openDialogs.length === 0) {
            news.newsFocus = true;
            news.grabFocus();

            // Show help dialog for new users after splash screen.
            if (wasSplashScreen && !sidebar.feedsExist) {
                openDialog("HelpDialog.qml");
            }
        }
    }

    // Open the splash screen.
    Component.onCompleted: {
        openDialog("SplashScreenDialog.qml");
    }

    // Windows title bar.
    Rectangle {
        id: winTitleBarArea;

        property bool isMaximized: main.visibility === Window.Maximized;

        x: sidebar.width;
        y: 0;
        width: parent.width - sidebar.width;
        height: (platform === "WIN" && winTitleBar)
                ? (isMaximized ? winTitleBar.captionHeight : winTitleBar.titleBarHeight)
                : 0;
        visible: platform === "WIN";
        color: style.color.background;
        z: 1000;

        // Drag to move window.
        MouseArea {
            anchors.fill: parent;
            anchors.rightMargin: (platform === "WIN" && winTitleBar) ? winTitleBar.buttonWidth * 3 : 0;
            onPressed: main.startSystemMove();
            onDoubleClicked: toggleMaximized();
        }

        // Caption buttons (minimize, maximize, close).
        Loader {
            active: platform === "WIN";
            anchors.top: parent.top;
            anchors.right: parent.right;
            source: "WinCaptionButtons.qml";
        }
    }

    // Window background behind all screens.
    color: "black";

    // Prevent closing when system tray icon is active.
    // Note: This is a valid property according to the docs; ignore the Qt Creator error message.
    onClosing: (event) => {
        if (fangSettings.showTrayIcon && platform === "WIN") {
            event.accepted = false;
            hide();
        }
    }

    SystemTrayIcon {
        property bool showBadge: newsFeedInteractor.allUnreadCount > 0;

        visible: fangSettings.showTrayIcon; // Defaults to true for Windows.
        icon.source: showBadge ? "qrc:/qml/images/system_tray_icon_badge.png" :
                                 "qrc:/qml/images/system_tray_icon.png";

        onActivated: (reason) => {
            if (reason === SystemTrayIcon.Context) {
                // Show context menu.
                contextMenu.open();
            } else {
                main.show();
                main.raise();
                main.requestActivate();
            }
        }

        menu: Menu {
            id: contextMenu;

            MenuItem {
                text: qsTr("Refresh news");
                onTriggered: news.refreshAllFeeds();
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Quit");
                onTriggered: Qt.quit();
            }
        }
    }

    // Keyboard shortcuts for Windows and Linux. See the MenuBar for MacOS implementation.
    Shortcut {
        sequences: [StandardKey.Quit]
        enabled: platform !== "MAC"
        onActivated: Qt.quit()
    }
    Shortcut {
        sequence: "Ctrl+Shift+F"
        enabled: platform !== "MAC"
        onActivated: openDialog("SearchDialog.qml")
    }
    Shortcut {
        sequence: "Ctrl+,"
        enabled: platform !== "MAC"
        onActivated: openDialog("SettingsDialog.qml")
    }
    Shortcut {
        sequence: "Ctrl+N"
        enabled: platform !== "MAC"
        onActivated: openDialog("AddDialog.qml")
    }
    Shortcut {
        sequence: "Ctrl+R"
        enabled: platform !== "MAC"
        onActivated: news.refreshCurrentFeed()
    }

    // MacOS menu bar; also handles keyboard shortcuts.
    MenuBar {
        // Main app menu
        Menu {
            title: qsTr("Fang")

            MenuItem {
                text: qsTr("About Fang")
                onTriggered: openDialog("AboutDialog.qml")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Settings...")
                shortcut: "Ctrl+,"
                onTriggered: openDialog("SettingsDialog.qml")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Quit Fang")
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("Edit")

            MenuItem {
                text: qsTr("Cut")
                shortcut: StandardKey.Cut
            }
            MenuItem {
                text: qsTr("Copy")
                shortcut: StandardKey.Copy
            }
            MenuItem {
                text: qsTr("Paste")
                shortcut: StandardKey.Paste
            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("Select All")
                shortcut: StandardKey.SelectAll
            }
        }

        Menu {
            title: qsTr("Feeds")

            MenuItem {
                text: qsTr("Search...")
                shortcut: "Ctrl+Shift+F"
                onTriggered: openDialog("SearchDialog.qml")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Add Feed...")
                shortcut: "Ctrl+N"
                onTriggered: openDialog("AddDialog.qml")
            }
            MenuItem {
                text: qsTr("Edit Feed...")
                enabled: sidebar.listView.model.selected
                         && !sidebar.listView.model.selected.isSpecialFeed()
                onTriggered: openDialog("EditDialog.qml", sidebar.listView.model.selected)
            }
            MenuItem {
                text: qsTr("Remove Feed...")
                enabled: sidebar.listView.model.selected
                         && !sidebar.listView.model.selected.isSpecialFeed()
                onTriggered: openDialog("RemoveDialog.qml", sidebar.listView.model.selected)
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Refresh")
                shortcut: "Ctrl+R"
                onTriggered: news.refreshCurrentFeed()
            }
        }

        Menu {
            title: qsTr("Help")

            MenuItem {
                text: qsTr("Fang Help")
                onTriggered: openDialog("HelpDialog.qml")
            }
        }
    }

    /**
     * Main component.
     */
    FangScreen {
        id: mainFrame;

        // WebView visibility hack
        onFadeInComplete: {
            news.isVisible = true;

            // Show pending update dialog after main view is fully visible
            showPendingUpdateIfReady();
        }

        // Splitter works differently on desktop vs. mobile.
        FangSplitView {
            id: mainView;

            anchors.fill: parent;
        
            // The feed list sidebar.
            Sidebar {
                id: sidebar;

                SplitView.minimumWidth: minimumSidebarWidth;
                SplitView.fillHeight: true;

                width: minimumSidebarWidth;
                state: "open";

                // Now isn't that special?
                specialFeedCount: news.specialFeedCount;

                states: [
                    State { name: "open"; },
                    State { name: "closed"; }
                ]

                // Currently disabled -- will need something like this for mobile, but
                // not realy needed for desktop
                // TODO
                /*
                transitions: [
                    Transition {
                        from: "open";
                        to: "closed";
                        SequentialAnimation {
                            // Move sidebar off screen
                            ParallelAnimation {
                                NumberAnimation {
                                    target: sidebar;
                                    properties: "x";
                                    to: -sidebarWidth;
                                    duration: 200;
                                    easing.type: Easing.InOutQuad;
                                }

                                NumberAnimation {
                                    target: openSidebarButton;
                                    properties: "opacity";
                                    from: 0.0;
                                    to: 1.0;
                                    duration: 500;
                                    easing.type: Easing.InOutQuad;
                                }
                            }
                        }
                    },
                    Transition {
                        from: "closed";
                        to: "open";

                        SequentialAnimation {
                            // Move sidebar back on screen
                            ParallelAnimation {
                                NumberAnimation {
                                    target: sidebar;
                                    properties: "x";
                                    to: 0;
                                    duration: 200;
                                    easing.type: Easing.InOutQuad;
                                }

                                NumberAnimation {
                                    target: openSidebarButton;
                                    properties: "opacity";
                                    from: 1.0;
                                    to: 0.0;
                                    duration: 500;
                                    easing.type: Easing.InOutQuad;
                                }
                            }
                        }
                    }
                ] */

                onCloseClicked: sidebar.state = "closed";

                onFeedClicked: news.showNews();
                onFeedDoubleClicked: news.jumpToBookmark();
                onOrderChanged: news.orderChanged();
                onHelpClicked: openDialog("HelpDialog.qml");
                onRefreshFeedClicked: (feed) => { news.refreshFeed(feed); }
                onRefreshCurrentFeedClicked: news.refreshCurrentFeed();
                onMarkAllAsUnreadClicked: (feed) => { news.markAllAsUnread(feed); }
                onMarkAllAsReadClicked: (feed) => { news.markAllAsRead(feed); }

                onSettingsClicked: openDialog("SettingsDialog.qml");
                onAddClicked: openDialog("AddDialog.qml");
                onRemoveClicked: openDialog("RemoveDialog.qml", listView.model.selected);
                onEditClicked: openDialog("EditDialog.qml", listView.model.selected);

                onSearchButtonClicked: openDialog("SearchDialog.qml");

                onMaximizeToggle: toggleMaximized();
            }

            News {
                id: news;

                SplitView.fillWidth: true
                SplitView.fillHeight: true;
                SplitView.minimumWidth: minimumNewsWidth;

                titleBarInset: winTitleBarArea.height;
                newsFocus: true // set by dialog system
/*
                Item {
                    id: openButtonContainer;

                    anchors.left: parent.left;
                    anchors.bottom: parent.bottom;

                    height: sidebar.buttonSize;
                    width: sidebar.buttonSize;

                    anchors.leftMargin: 5;
                    anchors.bottomMargin: 5;

                    //
                    // Disabled -- see Sidebar.qml to understand why.
                    //
                    // Button to re-open sidebar
                    SidebarButton {
                        id: openSidebarButton

                        imageURL: fangSettings.currentStyle === "LIGHT" ? "images/arrows_right_dark.png"
                                                                 : "images/arrows_right.png";
                        imageHoverURL: fangSettings.currentStyle === "LIGHT" ? "images/arrows_right.png"
                                                                      : "images/arrows_right_dark.png";
                        imagePressedURL: fangSettings.currentStyle === "LIGHT" ? "images/arrows_right.png"
                                                                        : "images/arrows_right_dark.png";

                        width: sidebar.buttonSize;
                        height: sidebar.buttonSize;

                        opacity: 0;
                        enabled: sidebar.state == "closed";

                        anchors.margins: 5;

                        onClicked: sidebar.state = "open";
                    }
                } */
            }
        }
    }
}
