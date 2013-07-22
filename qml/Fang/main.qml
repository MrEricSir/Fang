import QtQuick 1.1

Rectangle {
    id: mainFrame
    width: 800
    height: 600

    Item {
        id: sidebarColumn
        x: 0
        y: 0
        width: 229
        height: 600
        
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
                    }
                    model: ListModel {
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
            }
            }
        }
        
        Rectangle {
            id: sidebarControls
            height: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            color: "#535353"
        }

    }
    
    Item {
        id: newsColumn
        x: 229
        y: 0
        width: 571
        height: 600
        
        ListView {
            id: newsListView
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            spacing: 20
            
            delegate: NewsItemDelegate {
                id: newsItem
            }
            
            model: ListModel {
                ListElement {
                    title: "Doctor Beat"
                    author: "Miami sound Machine"
                    description: "Doctor, i've got this feelin' deep inside of me, deep inside of me
I just can't control my feet when i hear the beat, when i hear the beat
Hey doctor, could you give me somethin' to ease the pain
'cause if you don't help me soon gonna lose my brain "
                    timestamp: 3
                    url: "http://www.beat.com"
                    siteTitle: "Beat.com"
                }
                ListElement {
                    title: "Japan upper house vote to set ruling bloc's power"
                    author: "USA Today"
                    description: "Copyright 2013 The Associated Press. All rights reserved. This material may not be published, broadcast, rewritten or redistributed."
                    timestamp: 234
                    url: "http://www.usatoday.com/story/news/world/2013/07/20/japan-election-abe-economy/2570723/"
                    siteTitle: "USA Today"
                }
            }
        }
    }

}
