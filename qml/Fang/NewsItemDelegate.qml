import QtQuick 1.1
import QtWebKit 1.0

Component {
    id: newsItemDelegate
    
    Column {
        id: newsCol
        
        width: parent.width
        spacing: 3
        
        // Headline container
        Column {
            id: headlineCol
            width: parent.width
            spacing: 5
            
            // Top-margin spacer
            Item {
                height: 5
                width: parent.width
            }
            
            // Headline
            Text {
                id: newsItemTitle
                
                text: title
                font.pointSize: 14
                font.family: "Tahoma"
            }
            
            // Line break
            Rectangle {
                id: lineBreakRect
                
                height: 1
                color: "#00000000"
                border.width: 1
                border.color: "#aaa"
                width: parent.width
            }
            
            // Site title and date
            Row {
                id: newsSubheadlineRow
                width: parent.width
                height: newsItemSiteTitle.paintedHeight
                
                Text {
                    id: newsItemSiteTitle
                    width: newsSubheadlineRow.width / 2
                    text: siteTitle
                    font.pointSize: 10
                    font.family: "Tahoma"
                }
                Text {
                    id: newsItemDate
                    
                    horizontalAlignment: Text.AlignRight
                    width: newsSubheadlineRow.width / 2
                    text: qsTr("May 4th 10:30 PM")
                    font.pointSize: 10
                    font.family: "Tahoma"
                }
            }
            
            
        }
        
        Item {
            id: newsItemContainer
            width: parent.width
            height: childrenRect.height
            
            WebView {
                id: webViewNews
                width: parent.width
                preferredWidth: parent.width
                     preferredHeight: 50
                
                html: description
                
                settings.standardFontFamily: "Tahoma"
                
                settings.javaEnabled: false
                settings.javascriptEnabled: false
                settings.pluginsEnabled: false
            }
        }
    }
    
   
}


