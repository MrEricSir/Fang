import QtQuick 1.1

Item {
    id: feedTitleDelegate
    height: 35
    
    signal doubleClicked()
    
    // Read-only
    property bool isAllNews: index == 0
    
    Row {
        id: row1
        
        Item {
            width: sidebarFeedList.width
            height: feedTitleDelegate.height
            
            
            Rectangle {
                id: rowBackground
                
                color: index == feedListView.currentIndex ? 
                           "white" : "transparent";
                
                anchors.fill: parent
                anchors.topMargin: 5
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                
                Item {
                    id: feedIconCol
                    
                    width: isAllNews ? 0 : 40 // no icon for all news
                    visible: !isAllNews
                    
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    
                    anchors.leftMargin: 10
                    
                    Image {
                        id: feedIcon
                        
                        source: imageURL
                        visible: !isUpdating
                        
                        onStatusChanged: {
                            // Show the default for errors.
                            if (status == Image.Error || imageURL == "")
                                source = "images/symbol_rss.svg";
                        }
                        
                        anchors.verticalCenter: parent.verticalCenter
                        
                        smooth: true
                        width: 23
                        height: 23
                        
                        sourceSize.width: width
                        sourceSize.height: height
                    }
                    
                    Spinner {
                        id: feedBusySpinner
                        
                        visible: isUpdating
                        
                        anchors.verticalCenter: parent.verticalCenter
                        
                        width: 23
                        height: 23
                    }
                }
                
                Item {
                    id: feedTitleCol
                    
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: feedIconCol.right
                    anchors.right: feedCountCol.left
                    
                    anchors.rightMargin: 4
                    anchors.bottomMargin: 5
                    anchors.topMargin: 5
                    
                    Text {
                        id: feedTitle
                        
                        text: title
                        
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        font.pointSize: 11
                        font.family: "Tahoma"
                        elide: Text.ElideRight
                    }
                }
                
                Item {
                    id: feedCountCol
                    
                    states: [
                        State { name: "allread" },
                        State { name: "unread" }
                    ]
                    
                    state: unreadCount > 0 ? "unread" : "allread"
                    opacity: unreadCount == 0 ? 0.0 : 1.0 // initial opacity
                    visible: true
                    
                    transitions: [
                        Transition {
                            from: "unread"
                            to: "allread"
                            NumberAnimation {
                                target: feedCountCol
                                properties: "opacity"
                                from: 1.0
                                to: 0.0
                                duration: 500
                                easing.type: Easing.InOutQuad
                            }
                        },
                        
                        Transition {
                            from: "allread"
                            to: "unread"
                            NumberAnimation {
                                target: feedCountCol
                                properties: "opacity"
                                from: 0.0
                                to: 1.0
                                duration: 500
                                easing.type: Easing.InOutQuad
                            }
                        }
                    ]
                    
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 14
                    
                    width: childrenRect.width
                    height: parent.height
                    
                    Rectangle {
                        color: "#bbb"
                        
                        width: unreadCountText.paintedWidth + 6
                        height: unreadCountText.paintedHeight + 4
                        anchors.verticalCenter: parent.verticalCenter
                        radius: 4
                        
                        Text {
                            id: unreadCountText
                            
                            text: unreadCount
                            
                            anchors.right: parent.right
                            anchors.rightMargin: 3
                            anchors.topMargin: 3
                            anchors.verticalCenter: parent.verticalCenter
                            font.pointSize: 8
                            font.family: "Tahoma"
                            elide: Text.ElideRight
                            color: "white"
                        }
                    }
                }
                
                MouseArea {
                    id: feedItemMouseArea
                    anchors.fill: parent
                    onClicked: feedListView.currentIndex = index
                    
                    onDoubleClicked: {
                        if (feedListView.currentIndex == index)
                            feedTitleDelegate.doubleClicked()
                    }
                
                }
            }
        }
        spacing: 10
    }
}
