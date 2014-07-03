import QtQuick 2.2

ListViewDragDelegate {
    id: feedTitleDelegate;
    height: 35;
    
    Style {
        id: style;
    }
    
    signal jumpToBookmark()
    
    // Read-only
    property bool isAllNews: index == 0;
    
    onClicked: feedListView.currentIndex = index;
    
    onDoubleClicked: {
        if (feedListView.currentIndex == index)
            feedTitleDelegate.jumpToBookmark();
    }
    
    Row {
        id: row1;
        
        Item {
            width: sidebarFeedList.width;
            height: feedTitleDelegate.height;
            
            
            Rectangle {
                id: rowBackground;
                
                color: index == feedListView.currentIndex ? 
                           style.color.sidebarSelected : "transparent";
                
                anchors.fill: parent;
                anchors.topMargin: 5;
                anchors.leftMargin: 0;
                anchors.rightMargin: 0;
                
                Item {
                    id: feedIconCol
                    
                    width: isAllNews ? 0 : 35; // no icon for all news
                    visible: !isAllNews
                    
                    anchors.left: parent.left;
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    
                    anchors.leftMargin: 10;
                    
                    Image {
                        id: feedIcon;
                        
                        source: imageURL;
                        visible: !isUpdating;
                        
                        onStatusChanged: {
                            // Show the default for errors.
                            if (status == Image.Error || imageURL == "")
                                source = fangSettings.style === "LIGHT" ? "images/symbol_rss.svg"
                                                                        : "images/symbol_dark_rss.svg";
                        }
                        
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        width: 24;
                        height: 24;
                        
                        sourceSize.width: width;
                        sourceSize.height: height;
                        asynchronous: true;
                    }
                    
                    FangIcon {
                        id: feedBusySpinner;
                        
                        state: "spinner";
                        visible: isUpdating;
                        
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        width: 23;
                        height: 23;
                    }
                }
                
                Item {
                    id: feedTitleCol;
                    
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    anchors.left: feedIconCol.right;
                    anchors.right: feedCountCol.left;
                    
                    anchors.rightMargin: 4;
                    anchors.bottomMargin: 5;
                    anchors.topMargin: 5;
                    anchors.leftMargin: 0;
                    
                    Text {
                        id: feedTitle;
                        
                        text: title;
                        
                        width: parent.width;
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        font.pointSize: style.font.defaultSize;
                        font.family: style.font.defaultFamily;
                        color: style.color.sidebarSelectedText;
                        renderType: Text.NativeRendering;
                        
                        elide: Text.ElideRight;
                    }
                }
                
                Item {
                    id: feedCountCol;
                    
                    states: [
                        State { name: "allread"; },
                        State { name: "unread"; }
                    ]
                    
                    state: unreadCount > 0 ? "unread" : "allread";
                    opacity: unreadCount == 0 ? 0.0 : 1.0 // initial opacity;
                    visible: true;
                    
                    transitions: [
                        Transition {
                            from: "unread";
                            to: "allread";
                            NumberAnimation {
                                target: feedCountCol;
                                properties: "opacity";
                                from: 1.0;
                                to: 0.0;
                                duration: 500;
                                easing.type: Easing.InOutQuad;
                            }
                        },
                        
                        Transition {
                            from: "allread";
                            to: "unread";
                            NumberAnimation {
                                target: feedCountCol;
                                properties: "opacity";
                                from: 0.0;
                                to: 1.0;
                                duration: 500;
                                easing.type: Easing.InOutQuad;
                            }
                        }
                    ]
                    
                    anchors.right: parent.right;
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    anchors.rightMargin: 7;
                    
                    width: childrenRect.width;
                    height: parent.height;
                    
                    Rectangle {
                        color: style.color.badge;
                        
                        width: unreadCountText.paintedWidth + 6;
                        height: unreadCountText.paintedHeight + 4;
                        anchors.verticalCenter: parent.verticalCenter;
                        radius: 4;
                        
                        Text {
                            id: unreadCountText;
                            
                            text: unreadCount;
                            
                            anchors.right: parent.right;
                            anchors.rightMargin: 3;
                            anchors.topMargin: 3;
                            anchors.verticalCenter: parent.verticalCenter;
                            font.pointSize: 8;
                            font.family: style.font.defaultFamily;
                            elide: Text.ElideRight;
                            color: style.color.badgeText;
                            renderType: Text.NativeRendering;
                        }
                    }
                }
            }
        }
        
        spacing: 10;
    }
}
