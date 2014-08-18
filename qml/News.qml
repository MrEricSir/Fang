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
    
    // Switch to news.
    function showNews() {
        newsView.state = "news";
    }
    
    // Switch to the welcome/help screen.
    function showWelcome() {
        newsView.state = "welcome";
    }
    
    // This is a workaround for a bug on Winows; see the comment
    // in main.qml where this is called for more information.
    function close() {
        newsView.state = "closing";
    }
    
    // Sets focus on the news view when dialogs are closed.
    property alias newsFocus: newsScrollView.focus;
    
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
                                                         + jsonNews + "');");
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
            
            focus: true;
            
            WebView {
                id: newsView;
                
                // Enable the web inspector by setting this to true.  You'll have to open Chrome to: 
                // http://127.0.0.1:9999/webkit/inspector/inspector.html?page=1
                property bool devMode: isDebugBuild;
                
                // Read-only
                property bool isInProgress: false;
                property real scaleFactor: (width >= experimental.preferredMinimumContentsWidth) ? 1.0 :
                    width / experimental.preferredMinimumContentsWidth;
                
                // Start invisible
                visible: false;
                
                // Stops scrolling while we're loading.
                enabled: !isInProgress;
                
                // Turn the inspek0r off and on.
                experimental.preferences.developerExtrasEnabled: devMode;
                
                state: (feedListModel.count > 1) ? "news" : "welcome";
                states: [
                    // Shows welcome screen.
                    State { name: "welcome" },
                    
                    // The typical news mode.
                    State { name: "news" },
                    
                    // Let WebKit load a safe, empty page before shutdown.
                    State { name: "closing" }
                ]
                
                Connections {
                    target: feedListModel;
                    onCountChanged: {
                        if (feedListModel.count > 1 && "welcome" === newsView.state) {
                            newsView.state = "news";
                        } else if (feedListModel.count <= 1 && "news" === newsView.state) {
                            newsView.state = "welcome";
                        }
                    }
                }
                
                onStateChanged: {
                    switch (state) {
                    case "welcome":
                        newsView.cssUpdated = false;
                        newsView.url = "qrc:///html/Welcome.html";
                        break;
                    
                    case "news":
                        newsView.cssUpdated = false;
                        newsView.firstRun = true;
                        newsView.url = "qrc:///html/NewsPage.html";
                        
                        break;
                    
                    case "closing":
                        newsView.url = "qrc:///html/Blank.html";
                        
                        break;
                    
                    default:
                         // Shouldn't get here.
                        console.error("You didn't handle state: ", state)
                    }
                }
                
                property bool firstRun: true;        // On first run, we need to wait for both.
                property bool cssUpdated: false;     // Check for this on first run.
                // Whether the bookmark has been jumped to
                property bool drawBookmarkAndJumpToFinished: false;
                
                // Checks if we should become visible or not.  (Internal)
                function checkReady() {
                    if (state === "welcome") {
                        // Welcome screen.
                        if (cssUpdated) {
                            visible = true;
                            isInProgress = false;
                        }
                    } else {
                        // We're showing the news!
                        if (firstRun) {
                            if (drawBookmarkAndJumpToFinished && cssUpdated) {
                                visible = true;
                                firstRun = false;
                            }
                        } else {
                            if (drawBookmarkAndJumpToFinished)
                                visible = true;
                        }
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
                
                // No plugins and such.
                experimental.preferences.pluginsEnabled: false;
                
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
                    } else if (cmd === "removeNewsTop") {
                        webInteractor.removeNews(true, commandArray[1]);
                    } else if (cmd === "removeNewsBottom") {
                        webInteractor.removeNews(false, commandArray[1]);
                    }
                    
                    
                    // Not used in Qt 5.3
                    //                } else if (cmd === "scrollToPosition" ) {
                    //                    console.log("Scroll to position: ", commandArray[1]);
                    //                    newsScroll.scrollTo(commandArray[1]);
                }
                
                // Set style, and update when needed.
                onLoadingChanged: {
                    if (loadRequest.status === WebView.LoadSucceededStatus) {
                        if (state === "closing") {
                            Qt.quit();
                            
                            return;
                        }
                        
                        webInteractor.pageLoaded();  // tell 'em the page is loaded now.
                        updateCSS(); // set our page's style
                        
                        // update height (if not already updated)
                        webInteractor.heightChanged(newsMargin.height);
                    } else if (loadRequest.status === WebView.LoadStartedStatus) {
                        visible = false;
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
                    case Qt.Key_Q:
                        if (event.modifiers & Qt.ControlModifier)
                            Qt.quit();
                        
                        break;
                    }
                }
            }
        }
    }
}
