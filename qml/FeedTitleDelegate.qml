import QtQuick

RearrangeableDelegate {
    id: feedTitleDelegate;
    
    Style {
        id: style;
    }
    
    signal jumpToBookmark();
    
    onClicked: feedListView.currentIndex = index;
    
    onDoubleClicked: {
        if (feedListView.currentIndex == index)
            feedTitleDelegate.jumpToBookmark();
    }
    
    dragEnabled: !isSpecialFeed;

    qmlListModel: false;

    openerImage: "images/opener.png";
    openerOffsetX: 10;
    openerOffsetY: 10;

    // Folders are always visible, but their children are not.
    visible: isFolder ? true : (parentFolder == -1 || folderOpen ? true : false);
    height: visible ? 35 * style.scale : 0

    Row {
        id: row1;
        
        Item {
            width: sidebarFeedList.width - (isFolder || parentFolder > -1 ? height : 0);
            height: feedTitleDelegate.height;
            
            Rectangle {
                id: rowBackground;
                
                color: index == feedListView.currentIndex ? 
                           style.color.sidebarSelected : "transparent";
                
                anchors.fill: parent;
                anchors.topMargin: 5 * style.scale;
                anchors.leftMargin: 0;
                anchors.rightMargin: 0;
                
                Item {
                    id: feedIconCol
                    
                    // No icon for all news or folders.
                    width: isSpecialFeed || isFolder ? 0 : (35 * style.scale);
                    visible: !(isSpecialFeed || isFolder)
                    
                    anchors.left: parent.left;
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    
                    anchors.leftMargin: 10 * style.scale;
                    
                    Image {
                        id: feedIcon;
                        
                        source: imageURL;
                        
                        visible: !isUpdating && status === Image.Ready;
                        
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        width: 24 * style.scale;
                        height: 24 * style.scale;
                        
                        sourceSize.width: width;
                        sourceSize.height: height;
                        asynchronous: true;
                    }
                    
                    Image {
                        id: defaultFeedIcon;
                        
                        visible: !isUpdating && (feedIcon.status !== Image.Ready);
                        
                        source: (fangSettings.style === "LIGHT" ? "images/symbol_rss.svg"
                                                        : "images/symbol_dark_rss.svg");
                        
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        width: 24 * style.scale;
                        height: 24 * style.scale;
                        
                        sourceSize.width: width;
                        sourceSize.height: height;
                        asynchronous: true;
                    }
                    
                    FangIcon {
                        id: feedBusySpinner;
                        
                        state: "spinner";
                        visible: isUpdating;
                        
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        width: 23 * style.scale;
                        height: 23 * style.scale;
                    }
                }
                
                Item {
                    id: feedTitleCol;
                    
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    anchors.left: feedIconCol.right;
                    anchors.right: feedCountCol.left;
                    
                    anchors.rightMargin: 4 * style.scale;
                    anchors.bottomMargin: 5 * style.scale;
                    anchors.topMargin: 5 * style.scale;
                    anchors.leftMargin: 0;
                    
                    Text {
                        id: feedTitle;
                        
                        text: title;
                        
                        width: parent.width;
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        font.pointSize: style.font.defaultSize;
                        font.family: style.font.defaultFamily;
                        color: style.color.sidebarSelectedText;
                        renderType: style.textRendering;
                        
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
                    visible: !isFolder; // TODO: Add working unread count to folders.
                    
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
                            
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter;
                            font.pointSize: style.font.unreadCountSize;
                            font.family: style.font.defaultFamily;
                            elide: Text.ElideRight;
                            color: style.color.badgeText;
                            renderType: style.textRendering;
                        }
                    }
                }
            }
        }
        
        spacing: 10 * style.scale;
    }
}
