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
                
                function onAdd(append, title, url, feedTitle, timestamp, content) {
                    console.log("You want ana append?")
                    //newsView.evaluateJavaScript("document.getElementsByTagName('body')[0].innerHTML = '" + html + "';");
                    //newsView.evaluateJavaScript("document.getElementsByTagName('body')[0].insertAdjacentHTML('beforeEnd', '" + html + "');");
                    //var html2 = "<br><br>YOYO<br>"
                    //newsView.evaluateJavaScript("document.body.insertAdjacentHTML('beforeEnd', '" + html + "');");
                    
               /*     newsView.evaluateJavaScript("appendNews('" 
                                                + "ts" + "', '"
                                                + "sfd" + "', '"
                                                + "" + "', '"
                                                + "feedTitle" + "', '"
                                                + "timestamp" + "', '"
                                                + "content" + "');"); */
                    
                  /*  newsView.evaluateJavaScript("appendNews('" 
                                                + append + "', '"
                                                + title + "', '"
                                                + url + "', '"
                                                + feedTitle + "', '"
                                                + timestamp + "', '"
                                                + content + "');");  */
                    
                    newsView.evaluateJavaScript("appendNews('" 
                                                + append + "', '"
                                                + title + "', '"
                                                + url + "', '"
                                                + feedTitle + "', '"
                                                + timestamp + "', '"
                                                + content + "');");
                }
                
                Component.onCompleted: {
                    add.connect(onAdd);
                }
            }
            
            // Web view for our HTML-based RSS display.
            WebView {
                id: newsView
                
                // Enable the web inspector by setting this to true.  You'll have to write-klik
                // on the webview to use this handy-dandy feature.
                property bool devMode: true
                
                preferredWidth: parent.parent.width
                
                focus: true
                
                url: "/html/NewsPage.html"
                
                javaScriptWindowObjects: QtObject {
                    WebView.windowObjectName: "fang"
                    
                    function loadNext() {
                        webInteractor.loadNext();
                    }
                    
                    function loadPrevious() {
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
                
                // Set platform.
                onLoadFinished: {
                    newsView.evaluateJavaScript("setPlatform('" + platform + "');");
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
