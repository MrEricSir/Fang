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

    // Read-only: Tells you if the news view is busy.
    readonly property alias isInProgress: news.isInProgress;

    // Treat as const
    property int minimumSidebarWidth: (platform === "ANDROID") ? 260 : 230;
    property int minimumNewsWidth: 400;
    
    // Style object.
    Style {
        id: style;
    }
    
    visible: true
    
    FangSettings {
        id: fangSettings;
        objectName: "fangSettings"; // Don't change this!
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
        // Remove the entry.
        openDialogs.splice(openDialogs.indexOf(dialog), 1);
        delete dialog;
        
        // If it was the last one, give focus back to news
        if (openDialogs.length === 0) {
            news.newsFocus = true;
        }
    }

    // Open the splash screen.
    Component.onCompleted: {
        openDialog("SplashScreenDialog.qml");
    }

    // Seen in transitions.
    color: style.color.blockerBackground;

    // Prevent closing when system tray icon is active.
    onClosing: (event) => {
        if (fangSettings.showTrayIcon && platform === "WIN") {
            event.accepted = false;
            hide();
        }
    }

    SystemTrayIcon {
        visible: fangSettings.showTrayIcon; // Defaults to true for non-Windows platforms.
        icon.source: "qrc:/qml/images/full_icon.png";

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
                text: qsTr("Quit");
                onTriggered: Qt.quit();
            }
        }
    }

    /**
     * Operator: mainFrame turn on.
     *
     * Captain: It's you!!
     * CATS: How are you gentlemen!!
     * CATS: All your base are belong to us.
     * CATS: You are on the way to destruction.
     * Captain: What you say!!
     * CATS: You have no chance to survive make your time.
     * CATS: Ha ha ha ha ....
     */
    FangScreen {
        id: mainFrame;

        // WebView visibility hack
        onFadeInComplete: {
            news.isVisible = true;
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
                onHelpClicked: news.showWelcome();
                onRefreshFeedClicked: (feed) => { news.refreshFeed(feed); }
                onRefreshCurrentFeedClicked: news.refreshCurrentFeed();
                onMarkAllAsUnreadClicked: (feed) => { news.markAllAsUnread(feed); }
                onMarkAllAsReadClicked: (feed) => { news.markAllAsRead(feed); }

                onSettingsClicked: openDialog("SettingsDialog.qml");
                onAddClicked: openDialog("AddDialog.qml");
                onRemoveClicked: openDialog("RemoveDialog.qml", listView.model.selected);
                onEditClicked: openDialog("EditDialog.qml", listView.model.selected);
            }

            News {
                id: news;

                SplitView.fillWidth: true
                SplitView.fillHeight: true;
                SplitView.minimumWidth: minimumNewsWidth;

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

                        imageURL: fangSettings.style === "LIGHT" ? "images/arrows_right_dark.png"
                                                                 : "images/arrows_right.png";
                        imageHoverURL: fangSettings.style === "LIGHT" ? "images/arrows_right.png"
                                                                      : "images/arrows_right_dark.png";
                        imagePressedURL: fangSettings.style === "LIGHT" ? "images/arrows_right.png"
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
