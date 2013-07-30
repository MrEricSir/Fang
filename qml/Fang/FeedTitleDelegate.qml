import QtQuick 1.1

Item {
    id: feedTitleDelegate
    height: 40
    
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
                           "#d7d7d7" : "transparent";
                
                anchors.fill: parent
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                
                Item {
                    id: feedTitleCol
                    
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: feedIconCol.right
                    
                    anchors.rightMargin: 10
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
                    id: feedIconCol
                    
                    width: isAllNews ? 0 : 40 // no icon for all news
                    visible: !isAllNews
                    
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    
                    anchors.leftMargin: 10
                    
                    Image {
                        id: feedIcon
                        source: imageURL != "" ? imageURL : "images/symbol_rss.svg"
                        anchors.verticalCenter: parent.verticalCenter
                        
                        smooth: true
                        width: 23
                        height: 23
                        
                        sourceSize.width: width
                        sourceSize.height: height
                    }
                }
                
                MouseArea {
                    id: feedItemMouseArea
                    anchors.fill: parent
                    onClicked: feedListView.currentIndex = index
                }
            }
        }
        spacing: 10
    }
}
