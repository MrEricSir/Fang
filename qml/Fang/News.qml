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
        
        // The "interactor" is what talks to the C++ layer.
        WebInteractor {
            id: webInteractor
            objectName: "webInteractor" // Do not change!! PENALTY OF DEATH AND ELECTROCUTION
            
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
            /*
                javaScriptWindowObjects: QtObject {
                    WebView.windowObjectName: "fang"
                    
                    function getScroll() {
                        return newsFlickable.contentY;
                    }
                    
                    function setScroll(y) {
                        newsFlickable.contentY = y;
                    }
                    
                    function addToScroll(y) {
                        // Tell the mouse wheel to fuck off temporarily.
                        wheelArea.active = false;
                        
                        newsFlickable.contentY += y;
                        
                        wheelArea.active = true;
                    }
                    
                    function getHeight() {
                        return newsFlickable.height;
                    }
                    
                    function loadNext() {
                        //sconsole.log("next!")
                        webInteractor.loadNext();
                    }
                    
                    function loadPrevious() {
                        //console.log("prev!")
                        webInteractor.loadPrevious();
                    }
                    
                    function setBookmark(id) {
                        //console.log("qml bookmark: ", id)
                        webInteractor.setBookmark(id);
                    }
                }
                */
            
            // Set style, and update when needed.
            onLoadingChanged: {
                if (loadRequest.status === WebView.LoadSucceededStatus) {
                    webInteractor.pageLoaded();  // tell 'em the page is loaded now.
                    updateCSS();
                }
            }
            
            Connections {
                target: fangSettings
                
                onFontSizeChanged: newsView.updateCSS()
                onStyleChanged: newsView.updateCSS()
            }
            
//            MouseWheelArea {
//                id: wheelArea
                
//                // Disable this to stop the motion.
//                property bool active: true
                
//                onActiveChanged: {
//                    if (!active)
//                        wheelScrollAnimation.stop();
//                }
                
//                anchors.fill: parent
//                property double deltaY: 0
//                onWheel: {
//                    deltaY = delta * 2; // Fudge factor!
//                    wheelScrollAnimation.restart();
//                }
                
//                NumberAnimation {
//                    id: wheelScrollAnimation
                    
//                    target: newsFlickable
//                    properties: "contentY"
//                    to: Math.max(0, Math.min(newsFlickable.contentY - wheelArea.deltaY,
//                                             newsFlickable.contentHeight - newsFlickable.height));
//                    duration: 200
//                    easing.type: Easing.OutQuad
//                }
//            }
        }
    }
    
    ScrollBar {
        target: newsView
    }
}
