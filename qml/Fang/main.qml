import QtQuick 1.1

Rectangle {
    id: mainFrame
    
    // Treat as const
    property int sidebarWidth: 230

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
                ParallelAnimation {
                    // Move sidebar off screen
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
            },
            Transition {
                from: "closed"
                to: "open"
                
                ParallelAnimation {
                    // Move sidebar back on screen
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
        ]
        
        onCloseClicked: sidebar.state = "closed"
        
        onFeedSelected: news.reset()
        onFeedDoubleClicked: news.jumpToBookmark()
        onAddClicked: addFeed.open()
        onRemoveClicked: removeFeed.open()
        onEditClicked: editFeed.open()
    }
    
    
    News {
        id: news
        
        anchors.left: sidebar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        
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
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#ccc"
                imageURL: "images/arrows_right.png"
                
                width: sidebar.buttonSize
                height: sidebar.buttonSize
                
                opacity: 0
                enabled: sidebar.state == "closed"
                
                anchors.margins: 5
                
                onClicked: sidebar.state = "open"
            }
        }
    }
    
    AddDialog {
        id: addFeed
        
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        
        title: "Add a Feed"
    }
    
    RemoveDialog {
        id: removeFeed
        
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        
        title: "Remove a Feed"
        
        // This is how we can remove the feed, you see.
        listView: sidebar.listView
    }
    
    EditDialog {
        id: editFeed
        
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        
        title: "Edit a Feed"
        
        // This lets us access the current item.
        listView: sidebar.listView
    }
}
