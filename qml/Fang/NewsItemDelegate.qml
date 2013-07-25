import QtQuick 1.1
import QtWebKit 1.0

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
            width: parent.width
            wrapMode: Text.WordWrap
            
            // Makes the headline clickable
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    parent.color = "blue"
                    parent.font.underline = true
                }
                onExited: {
                    parent.color = "black"
                    parent.font.underline = false
                }
                
                onClicked: Qt.openUrlExternally(url)
            }
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
            
            spacing: 4
            
            Image {
                width: 20
                height: 20
                
                source: siteImageURL
                
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
            }
            
            Text {
                id: newsItemSiteTitle
                width: newsSubheadlineRow.width / 2 - 20
                
                text: siteTitle
                
                font.pointSize: 10
                font.family: "Tahoma"
                elide: Text.ElideRight
            }
            
            Text {
                id: newsItemDate
                
                horizontalAlignment: Text.AlignRight
                width: newsSubheadlineRow.width / 2 - 10
                text: ""//Qt.formatDateTime(timestamp)
                font.pointSize: 10
                font.family: "Tahoma"
                elide: Text.ElideRight
            }
        }
        
        
    }
    
    Item {
        id: newsItemContainer
        width: parent.width
        height: childrenRect.height
        
        WebView {
            id: webViewNews
            //width: parent.width
            preferredWidth: parent.width
            preferredHeight: 1
            
            html: description
            
            settings.standardFontFamily: "Tahoma"
            
            settings.javaEnabled: false
            settings.javascriptEnabled: true//false
            settings.localContentCanAccessRemoteUrls: false
            settings.pluginsEnabled: true //false
            
            focus: false
            
            // WebView can't handle sizes changes well, so we'll hack around it.
            property int oldWidth: 0
            onWidthChanged: {
                if (oldWidth == 0) {
                    oldWidth = width;
                    return;
                }
                
                reloadTimer.restart();
                oldWidth = width;
            }
            property int oldHeight: 0
            onHeightChanged: {
                if (oldHeight == 0) {
                    oldHeight = height;
                    return;
                }
                
                console.log("new height", height)
                reloadTimer.restart();
                oldHeight = height;
            }
            
            // Timer for reloading when the size changes.
            Timer {
                id: reloadTimer
                interval: 50
                running: false
                repeat: false
                
                // Hack to force a refresh.
                //onTriggered: webViewNews.html = webViewNews.html
            }
            
            onLoadFinished: {
                            evaluateJavaScript(' \
                                var els = document.getElementsByTagName("a"); \
                                for (var i in els){ \
                                    els[i].onclick = function(e){e.preventDefault(); qml.qmlCall(this.getAttribute("href")); return false;} \
                                } \
                            ')
                            enabled = true;
                            }
                        javaScriptWindowObjects: QtObject {
                            WebView.windowObjectName: "qml"
            
                            function qmlCall(url) {
                                console.log(url);
                                Qt.openUrlExternally(url)
                            }
                        }
                        
        }
    }
}
