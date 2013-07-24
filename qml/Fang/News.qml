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
    }
    
    ScrollBar {
        target: newsListView
    }
}
