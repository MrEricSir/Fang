import QtQuick 1.1

Item {
    id: news
    
    ListView {
        id: newsListView
        
        anchors.fill: parent
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        spacing: 20
        
        delegate: NewsItemDelegate {
            id: newsItem
        }
        
        model: sidebar.newsList
        
        
            
            /*ListModel {
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
        } */
    }
}
