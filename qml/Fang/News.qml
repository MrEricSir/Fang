import QtQuick 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0
import Fang 1.0

Item {
    id: news
    
    // Used by main for double clicking on feed titles.
    function jumpToBookmark() {
        webInteractor.jumpToBookmark();
    }
    
    Item {
        id: newsMargin
        
        anchors.fill: parent
        anchors.rightMargin: 16
        anchors.leftMargin: 12
        
        onHeightChanged: webInteractor.heightChanged(height);
        
        // The "interactor" is what talks to the C++ layer.
        WebInteractor {
            id: webInteractor
            objectName: "webInteractor" // Do not change!! PENALTY OF DEATH AND ELECTROCUTION
            
            function heightChanged(height) {
                newsView.experimental.evaluateJavaScript(
                            "setWindowHeight('" + height + "')"
                            );
            }
            
            onAdd: {
                newsView.experimental.evaluateJavaScript("appendNews("
                                                         + append + ", '"
                                                         + id + "', '"
                                                         + title + "', '"
                                                         + url + "', '"
                                                         + feedTitle + "', '"
                                                         + timestamp + "', '"
                                                         + content + "');");
            }
            
            onClear: {
                //console.log("Clear!")
                newsView.experimental.evaluateJavaScript("clearNews();");
                newsView.contentY = 0;
//                newsFlickable.contentY = 0; // reset scroll
            }
            
            onJumpTo: {
//                console.log("jump!")
                newsView.experimental.evaluateJavaScript("jumpTo('" + id + "');");
            }
            
            onDrawBookmark: {
                console.log("Draw bookmark: ", id)
                newsView.experimental.evaluateJavaScript("drawBookmark('" + id + "');");
            }
        }
        
        // Web view for our HTML-based RSS display.
        WebView {
            id: newsView
            
            // Enable the web inspector by setting this to true.  You'll have to open Chrome to: 
            // http://127.0.0.1:9999/webkit/inspector/inspector.html?page=1
            property bool devMode: true
            
            // Turn the inspek0r off and on.
            experimental.preferences.developerExtrasEnabled: devMode
            
            function updateCSS() {
                newsView.experimental.evaluateJavaScript(
                            "clearBodyClasses(); " +
                            "addBodyClass('" + platform + "'); " +
                            "addBodyClass('FONT_" + fangSettings.fontSize + "'); " +
                            "addBodyClass('" + fangSettings.style + "');");
            }
            
            anchors.fill: parent
            
            // Resize a bit more intelligently.
            experimental.preferredMinimumContentsWidth: 300
            
            focus: true
            
            url: "qrc:///html/NewsPage.html"
            
            
            experimental.preferences.navigatorQtObjectEnabled: true
            experimental.onMessageReceived: {
                //console.log("get msg from javascript:", message.data)
                if (message.data === "loadNext") {
                    webInteractor.loadNext();
                } else if (message.data === "loadPrevious") {
                    webInteractor.loadPrevious();
                } else if (message.data.substring(0, 11) === "setBookmark") {
                    var bookmarkArray = message.data.split(" ");
                    webInteractor.setBookmark(bookmarkArray[1]);
                }
                
            }
            
            // Set style, and update when needed.
            onLoadingChanged: {
                if (loadRequest.status === WebView.LoadSucceededStatus) {
                    webInteractor.pageLoaded();  // tell 'em the page is loaded now.
                    updateCSS(); // set our page's style
                    webInteractor.heightChanged(newsMargin.height); // update height (if not already updated)
                }
            }
            
            Connections {
                target: fangSettings
                
                onFontSizeChanged: newsView.updateCSS()
                onStyleChanged: newsView.updateCSS()
            }
        }
    }
    
    ScrollBar {
        target: newsView
    }
}
