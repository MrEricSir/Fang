import QtQuick 1.1

Item {
    id: feedTitleDelegate
    height: 40
    Row {
        id: row1
        Rectangle {
            id: rowBackground
            
            color: index == feedListView.currentIndex ? 
                       "#d7d7d7" : "transparent";
            
            width: sidebarFeedList.width
            height: feedTitleDelegate.height
            
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
                    
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 11
                    font.family: "Tahoma"
                }
            }
            
            Item {
                id: feedIconCol
                width: 40
                
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                
                anchors.leftMargin: 10
                
                Image {
                    id: feedIcon
                    source: image || ""
                    anchors.verticalCenter: parent.verticalCenter
                    width: 30
                    height: 30
                }
            }
            
            MouseArea {
                id: feedItemMouseArea
                anchors.fill: parent
                onClicked: feedListView.currentIndex = index
            }
        }
        spacing: 10
    }
}
