import QtQuick 2.0
import Fang 1.0

Rectangle {
    id: mainFrame
    
    // Treat as const
    property int sidebarWidth: 230
    
    // Style object.
    Style {
        id: style
    }
    
    FangSettings {
        id: fangSettings
        objectName: "fangSettings" // Don't change this!
    }
    
    color: style.color.background
    
    // Read-only: List of all open dialogs
    property var openDialogs: []
    
    // Creates and opens a dialog.
    function openDialog(dialogName) {
        var component = Qt.createComponent(dialogName);
        var dialog = component.createObject(
                    mainFrame, {"x": 0, "y": 0, "listView": sidebar.listView});
        
        if (dialog === null) {
            // Error Handling
            console.log("Error creating dialog: " + dialogName);
        }
        
        // Pop 'er open!
        openDialogs.push(dialog);
        news.newsFocus = false;
        dialog.onDialogClosed.connect(onDialogClosed);
        dialog.open();
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
    
    // The feed list sidebar.
    Sidebar {
        id: sidebar
        
        width: sidebarWidth
        x: 0
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        state: "open"
        
        states: [
            State { name: "open" },
            State { name: "closed" }
        ]
        
        transitions: [
            Transition {
                from: "open"
                to: "closed"
                SequentialAnimation {
                    // Move sidebar off screen
                    ParallelAnimation {
                        NumberAnimation {
                            target: sidebar
                            properties: "x"
                            to: -sidebarWidth
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                        
                        NumberAnimation {
                            target: openSidebarButton
                            properties: "opacity"
                            from: 0.0
                            to: 1.0
                            duration: 500
                            easing.type: Easing.InOutQuad
                        }
                    }
                }
            },
            Transition {
                from: "closed"
                to: "open"
                
                SequentialAnimation {
                    // Move sidebar back on screen
                    ParallelAnimation {
                        NumberAnimation {
                            target: sidebar
                            properties: "x"
                            to: 0
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                        
                        NumberAnimation {
                            target: openSidebarButton
                            properties: "opacity"
                            from: 1.0
                            to: 0.0
                            duration: 500
                            easing.type: Easing.InOutQuad
                        }
                    }
                }
            }
        ]
        
        onCloseClicked: sidebar.state = "closed"
        
        onFeedDoubleClicked: news.jumpToBookmark()
        onOrderChanged: news.orderChanged()
        
        onSettingsClicked: openDialog("SettingsDialog.qml");
        onAddClicked: openDialog("AddDialog.qml");
        onRemoveClicked: openDialog("RemoveDialog.qml");
        onEditClicked: openDialog("EditDialog.qml");
    }
    
    News {
        id: news
        
        anchors.left: sidebar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        
        newsFocus: true // set by dialog system
        
        Item {
            id: openButtonContainer
            
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            
            height: sidebar.buttonSize
            width: sidebar.buttonSize
            
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            
            // Button to re-open sidebar
            SidebarButton {
                id: openSidebarButton
                
                imageURL: fangSettings.style === "LIGHT" ? "images/arrows_right_dark.png"
                                                         : "images/arrows_right.png"
                imageHoverURL: fangSettings.style === "LIGHT" ? "images/arrows_right.png"
                                                              : "images/arrows_right_dark.png"
                imagePressedURL: fangSettings.style === "LIGHT" ? "images/arrows_right.png"
                                                                : "images/arrows_right_dark.png"
                
                width: sidebar.buttonSize
                height: sidebar.buttonSize
                
                opacity: 0
                enabled: sidebar.state == "closed"
                
                anchors.margins: 5
                
                onClicked: sidebar.state = "open"
            }
        }
    }
}
