import QtQuick 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0
import Fang 1.0

Item {
    id: news
    
    // Used by main for double clicking on feed titles.
    function jumpToBookmark() {
        //console.log("Jump to bmark");
        newsView.experimental.evaluateJavaScript("jumpToBookmark();");
    }
    
    function orderChanged() {
        webInteractor.orderChanged();
    }
    
    function refreshFeed() {
        webInteractor.refreshCurrentFeed();
    }
    
    // Sets focus on the news view when dialogs are closed.
    property alias newsFocus: newsScrollView.focus
    
    Item {
        id: newsMargin;
        
        anchors.fill: parent;
        
        onHeightChanged: webInteractor.heightChanged(height);
        
        // The "interactor" is what talks to the C++ layer.
        // See WebInteractor.h and .cpp
        WebInteractor {
            id: webInteractor;
            objectName: "webInteractor"; // Do not change!! PENALTY OF DEATH AND ELECTROCUTION
            
            function heightChanged(height) {
                newsView.experimental.evaluateJavaScript(
                            "setWindowHeight('" + height + "')"
                            );
            }
            
            onAddInProgress: {
                newsView.experimental.evaluateJavaScript("inProgress("
                                                         + started + ", '"
                                                         + operation + "');");
                if (started) {
                    newsView.isInProgress = true;
                }
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
            
            onNothingToAdd: {
                newsView.experimental.evaluateJavaScript("stopInProgress();");
            }
            
            onClear: {
                //console.log("Clear!");
                newsView.experimental.evaluateJavaScript("clearNews();");
                newsView.contentY = 0;  // reset scroll
                
                // Wipe the view clean; it will be set to visible again when ready.
                newsView.visible = false;
            }
            
            onJumpTo: {
                //console.log("jump to: ", id);
                newsView.experimental.evaluateJavaScript("jumpTo('" + id + "');");
            }
            
            onDrawBookmark: {
                //console.log("Draw bookmark: ", id);
                newsView.experimental.evaluateJavaScript("drawBookmark('" + id + "');");
            }
            
            onDrawBookmarkAndJumpTo: {
                //console.log("Draw bookmark and jump to: ", id);
                newsView.experimental.evaluateJavaScript("drawBookmarkAndJumpTo('" + id + "');");
            }
            
            onFontSizeChanged: {
                //console.log("Font size changed, alert!  Need to jump to bookmark!")
                newsView.updateCSS();
                newsView.experimental.evaluateJavaScript("jumpToBookmark();");
            }
            
            onStyleChanged: {
                //console.log("I was told to update the css?");
                newsView.updateCSS();
            }
        }
        
        // Web view for our HTML-based RSS display.
        FangScrollView {
            id: newsScrollView;
            
            anchors.fill: parent;
            
            WebView {
                id: newsView;
                
                // Enable the web inspector by setting this to true.  You'll have to open Chrome to: 
                // http://127.0.0.1:9999/webkit/inspector/inspector.html?page=1
                property bool devMode: true;
                
                // Read-only
                property bool isInProgress: false;
                
                // Start invisible
                visible: false;
                
                // Stops scrolling while we're loading.
                enabled: !isInProgress;
                
                // Turn the inspek0r off and on.
                experimental.preferences.developerExtrasEnabled: devMode;
                
                property bool firstRun: true;        // On first run, we need to wait for both.
                property bool cssUpdated: false;     // Check for this on first run.
                // Whether the bookmark has been jumped to
                property bool drawBookmarkAndJumpToFinished: false;
                
                // Checks if we should become visible or not.  (Internal)
                function checkReady() {
                    if (firstRun) {
                        if (drawBookmarkAndJumpToFinished && cssUpdated) {
                            visible = true;
                        }
                    } else {
                        if (drawBookmarkAndJumpToFinished)
                            visible = true;
                    }
                }
                
                focus: true;
                
                function updateCSS() {
                    newsView.experimental.evaluateJavaScript(
                                "clearBodyClasses(); " +
                                "addBodyClass('" + platform + "'); " +
                                "addBodyClass('FONT_" + fangSettings.fontSize + "'); " +
                                "addBodyClass('" + fangSettings.style + "');");
                    
                    cssUpdated = true;
                    checkReady();
                }
                
                // Jumpts to the next news item.
                function jumpNext() {
                    newsView.experimental.evaluateJavaScript("jumpNextPrev(true);");
                }
                
                // Jumps to the previous news item.
                function jumpPrevious() {
                    newsView.experimental.evaluateJavaScript("jumpNextPrev(false);");
                }
                
                // Leave margin for scroll bar.
                anchors.fill: parent;
                anchors.rightMargin: 16;
                anchors.leftMargin: 12;
                
                // Resize a bit more intelligently.
                experimental.preferredMinimumContentsWidth: 300;
                
                url: "qrc:///html/NewsPage.html"
                
                // Communication from WebKit layer to QML.
                experimental.preferences.navigatorQtObjectEnabled: true;
                experimental.onMessageReceived: {
                    //console.log("get msg from javascript:", message.data)
                    var commandArray = message.data.split(" ");
                    var cmd = commandArray[0];
                    
                    if (cmd === "loadNext") {
                        webInteractor.loadNext();
                    } else if (cmd === "loadPrevious") {
                        webInteractor.loadPrevious();
                    } else if (cmd === "setBookmark") {
                        webInteractor.setBookmark(commandArray[1]);
                    } else if (cmd === "openLink") {
                        webInteractor.openLink(commandArray[1]);
                    } else if (cmd === "stopProgress" ) {
                        newsView.experimental.evaluateJavaScript("stopInProgress();");
                        newsView.isInProgress = false;
                    } else if (cmd === "drawBookmarkAndJumpToFinished" ) {
                        // Check if it's time to become visible again.
                        //console.log("draw book jump to finished");
                        newsView.drawBookmarkAndJumpToFinished = true;
                        checkReady();
                    }
                    
                    // Not used in Qt 5.3
                    //                } else if (cmd === "scrollToPosition" ) {
                    //                    console.log("Scroll to position: ", commandArray[1]);
                    //                    newsScroll.scrollTo(commandArray[1]);
                }
                
                // Set style, and update when needed.
                onLoadingChanged: {
                    if (loadRequest.status === WebView.LoadSucceededStatus) {
                        webInteractor.pageLoaded();  // tell 'em the page is loaded now.
                        updateCSS(); // set our page's style
                        webInteractor.heightChanged(newsMargin.height); // update height (if not already updated)
                    }
                }
                
                Keys.onPressed: {
                    switch (event.key) {
                    case Qt.Key_Left:
                        newsView.jumpPrevious();
                        
                        break;
                    case Qt.Key_Right:
                        newsView.jumpNext();
                        
                        break;
                    case Qt.Key_F5:
                        news.refreshFeed();
                        
                        break;
                    case Qt.Key_R:
                        if (event.modifiers & Qt.ControlModifier)
                            news.refreshFeed();
                        
                        break;
                    }
                }
            }
        }
    }
}
