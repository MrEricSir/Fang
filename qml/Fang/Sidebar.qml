import QtQuick 1.1

Item {
    id: sidebar
    
    signal addClicked()
    signal removeClicked()
    signal closeClicked()
    
    // Currently selected news list
    property variant newsList: feedListView.currentItem.feedModel.newsList
    
    // Const property
    property int buttonSize: 30
    
    Item {
        id: sidebarFeedList
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: sidebarControls.top
        
        Rectangle {
            id: rectangle2
            color: "#eee"
            anchors.fill: parent
            
            ListView {
                id: feedListView
                anchors.fill: parent
                delegate: FeedTitleDelegate {
                    id: titleDelegate
                    
                    property variant feedModel: model // Hack to get current data
                }
                
                model: feedListModel
                    /*
                    ListModel {
                    ListElement {
                        title: "All News"
                        url: ""
                        lastUpdated: 123
                    }
                    
                    ListElement {
                        image: "http://www.mrericsir.com/blog/wp-content/themes/eric-cordobo-green-park-2/favicon.ico"
                        title: "MrEricSir.com"
                        url: "http://www.mrericsir.com"
                        lastUpdated: 123
                    }
                    
                    ListElement {
                        image: "http://static.arstechnica.net/favicon.ico"
                        title: "Ars Technica"
                        url: "blue"
                        lastUpdated: 123
                    }
                    
                    ListElement {
                        title: "SFist"
                        image: "http://www.sfist.com/favicon.ico"
                        url: "green"
                        lastUpdated: 123
                    }
                }
                */
            }
        }
    }
    
    Rectangle {
        id: sidebarControls
        height: 40
        
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#535353"
        
        Item {
            id: toolbar
            anchors.fill: parent
            anchors.margins: 5
            
            Button {
                id: addButton
                
                x: 0
                
                width: buttonSize
                height: buttonSize
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#2a2"
                imageURL: "images/plus.png"
                
                onClicked: addClicked()
            }
            
            Button {
                id: removeButton
                
                x: buttonSize + 10
                
                width: buttonSize
                height: buttonSize
                
                visible: feedListView.currentIndex != 0
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#a22"
                imageURL: "images/minus.png"
                
                onClicked: removeClicked()
            }
            
            // Button to close the 
            Button {
                id: closeButton
                
                x: toolbar.width - buttonSize
                
                width: buttonSize
                height: buttonSize
                
                imageMargin: 5
                color: "#777"
                hoverColor: "#ccc"
                imageURL: "images/arrows_left.png"
                
                onClicked: closeClicked()
            }
        }
        
    }
}
