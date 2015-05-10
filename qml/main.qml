import QtQuick 2.2
import QtQuick.Window 2.1
import Fang 1.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Qt.labs.settings 1.0

Window {
    id: main;
    
    width: windowSettings.width;
    height: windowSettings.height;
    visibility: windowSettings.maximized ?
                    Window.Maximized : Window.Windowed;
    
    minimumWidth: 640;
    minimumHeight: 450;
    
    // Treat as const
    property int sidebarWidth: 230;
    
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
    }
    
    // This is a hack to prevent Fang from hanging when closed on
    // Windows due to a bug in QtWebKit.
    // Ticket: https://github.com/MrEricSir/Fang/issues/93
    onClosing: {
        close.accepted = false;
        news.close();
    }

    // Read-only: List of all open dialogs
    property var openDialogs: []
    
    // Creates and opens a dialog.  The dialog is returned in
    // case you wanna mess with it and shit.
    function openDialog(dialogName) {
        var component = Qt.createComponent(dialogName);
        var dialog = component.createObject(
                    main, {"x": 0, "y": 0, "listView": sidebar.listView});
        
        if (dialog === null) {
            // Error Handling
            console.log("Error creating dialog: " + dialogName);
            
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
    
    color: "black"; // For transitions.

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

        //anchors.fill: parent;
        
        // The feed list sidebar.
        Sidebar {
            id: sidebar;
            
            width: sidebarWidth;
            x: 0;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            state: "open";

            // Now isn't that special?
            specialFeedCount: news.specialFeedCount;
            
            states: [
                State { name: "open"; },
                State { name: "closed"; }
            ]
            
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
            ]
            
            onCloseClicked: sidebar.state = "closed";
            
            onFeedClicked: news.showNews();
            onFeedDoubleClicked: news.jumpToBookmark();
            onOrderChanged: news.orderChanged();
            onHelpClicked: news.showWelcome();
            
            onSettingsClicked: openDialog("SettingsDialog.qml");
            onAddClicked: openDialog("AddDialog.qml");
            onRemoveClicked: openDialog("RemoveDialog.qml");
            onEditClicked: openDialog("EditDialog.qml");
        }
        
        News {
            id: news;
            
            anchors.left: sidebar.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;
            
            newsFocus: true // set by dialog system
            
            Item {
                id: openButtonContainer;
                
                anchors.left: parent.left;
                anchors.bottom: parent.bottom;
                
                height: sidebar.buttonSize;
                width: sidebar.buttonSize;
                
                anchors.leftMargin: 5;
                anchors.bottomMargin: 5;
                
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
            }
        }
    }
    
}
