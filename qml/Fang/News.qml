import QtQuick 1.1
import QtWebKit 1.0
import Fang 1.0

Item {
    id: news
    
    Item {
        id: newsMargin
        
        anchors.fill: parent
        anchors.rightMargin: 16
        anchors.leftMargin: 12
        
        Flickable {
            id: newsFlickable
            
            width: parent.width
            anchors.fill: parent
            contentWidth: Math.max(parent.width, newsView.width)
            contentHeight: Math.max(parent.height, newsView.height)
            
            flickableDirection: Flickable.VerticalFlick
            
            // The "interactor" is what talks to the C++ layer.
            WebInteractor {
                id: webInteractor
                objectName: "webInteractor" // Do not change!! PENALTY OF DEATH AND ELECTROCUTION
                
                function onAdd(append, id, title, url, feedTitle, timestamp, content) {
                    //console.log("You want ana append?", id)
                    
                    newsView.evaluateJavaScript("appendNews('"
                                                + append + "', '"
                                                + id + "', '"
                                                + title + "', '"
                                                + url + "', '"
                                                + feedTitle + "', '"
                                                + timestamp + "', '"
                                                + content + "');");
                }
                
                function onClear() {
                    //console.log("Clear!")
                    newsView.evaluateJavaScript("clearNews();");
                }
                
                function onJumpTo(id) {
                    //console.log("jump!")
                    newsView.evaluateJavaScript("jumpTo('" + id + "');");
                }
                
                function onDrawBookmark(id) {
                    newsView.evaluateJavaScript("drawBookmark('" + id + "');");
                }
                
                // Hook up signals.
                Component.onCompleted: {
                    add.connect(onAdd);
                    clear.connect(onClear);
                    jumpTo.connect(onJumpTo);
                    drawBookmark.connect(onDrawBookmark);
                }
            }
            
            // Web view for our HTML-based RSS display.
            WebView {
                id: newsView
                
                // Enable the web inspector by setting this to true.  You'll have to write-klik
                // on the webview to use this handy-dandy feature.
                property bool devMode: true
                
                function updateCSS() {
                    newsView.evaluateJavaScript(
                                "clearBodyClasses(); " +
                                "addBodyClass('" + platform + "'); " +
                                "addBodyClass('FONT_" + fangSettings.fontSize + "'); " +
                                "addBodyClass('" + fangSettings.style + "');");
                }
                
                preferredWidth: parent.parent.width
                
                focus: true
                
                url: "/html/NewsPage.html"
                
                javaScriptWindowObjects: QtObject {
                    WebView.windowObjectName: "fang"
                    
                    function getScroll() {
                        return newsFlickable.contentY;
                    }
                    
                    function setScroll(y) {
                        newsFlickable.contentY = y;
                    }
                    
                    function getHeight() {
                        return newsFlickable.height;
                    }
                    
                    function loadNext() {
                        //console.log("next!")
                        webInteractor.loadNext();
                    }
                    
                    function loadPrevious() {
                        //console.log("prev!")
                        webInteractor.loadPrevious();
                    }
                }
                
                // Turn the inspek0r off and on.
                settings.developerExtrasEnabled: devMode
                MouseArea {
                    enabled: !newsView.devMode
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                }
                
                // Set style, and update when needed.
                onLoadFinished: updateCSS()
                Connections {
                    target: fangSettings
                    
                    onFontSizeChanged: newsView.updateCSS()
                    onStyleChanged: newsView.updateCSS()
                }
                
                MouseWheelArea {
                    id: wheelArea
                    
                    anchors.fill: parent
                    property double deltaY: 0
                    onWheel: {
                        deltaY = delta * 2; // Fudge factor!
                        wheelScrollAnimation.restart();
                    }
                    
                    NumberAnimation {
                        id: wheelScrollAnimation
                        
                        target: newsFlickable
                        properties: "contentY"
                        to: Math.max(0, Math.min(newsFlickable.contentY - wheelArea.deltaY,
                                                 newsFlickable.contentHeight - newsFlickable.height));
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
                }
            }
        }
    }
    
    ScrollBar {
        target: newsFlickable
    }
}
