import QtQuick 2.4
import QtWebEngine 1.0
//import QtWebView 1.0
import Fang 1.0

Item {
    id: news

    // Read-only: The number of special feeds in the feed list
    property alias specialFeedCount: qmlNewsInteractor.specialFeedCount;

    // Read-only: Whether bookmarks are enabled for this feed.
    property bool bookmarksEnabled: true;

    // Read-only: Whether the news view is loading stuff.
    property alias isInProgress: qmlNewsInteractor.loadInProgress;
    
    // Used by main for double clicking on feed titles.
    function jumpToBookmark() {
        qmlNewsInteractor.jumpToBookmark();
    }
    
    function orderChanged() {
        qmlNewsInteractor.orderChanged();
    }
    
    function refreshFeed() {
        qmlNewsInteractor.refreshCurrentFeed();
    }
    
    // Switch to news.
    function showNews() {
        qmlNewsInteractor.showNews();
    }
    
    // Switch to the welcome/help screen.
    function showWelcome() {
        qmlNewsInteractor.showWelcome();
    }
    
    // This is a workaround for a bug on Winows; see the comment
    // in main.qml where this is called for more information.
    function close() {
        newsView.state = "closing";
    }
    
    // Don't propagate key events while dialogs are up.
    property bool newsFocus: true;
    
    Item {
        id: newsMargin;
        
        anchors.fill: parent;
        
        onHeightChanged: qmlNewsInteractor.windowHeight = height;
        
        // The "interactor" is what talks to the C++ layer.
        // See QMLNewsInteractor.h and .cpp
        QMLNewsInteractor {
            id: qmlNewsInteractor;
            objectName: "QMLNewsInteractor"; // Do not change!! PENALTY OF DEATH AND ELECTROCUTION
        }
        
            
        WebEngineView {
//            WebView {
            id: newsView;

            // Start visible
            visible: true;
            anchors.fill: parent;

            // Stops scrolling while we're loading or a dialog is displayed.
            enabled: !qmlNewsInteractor.loadInProgress && newsFocus;

            state: "news";
            states: [
                // The typical news/help mode.
                State { name: "news" },

                // Let WebKit load a safe, empty page before shutdown.
                State { name: "closing" }
            ]

            onStateChanged: {
                switch (state) {
                case "news":
                    newsView.url = "qrc:///html/index.html";

                    break;

                case "closing":
                    newsView.url = "qrc:///html/blank.html";

                    break;

                default:
                     // Shouldn't get here.
                    console.error("You didn't handle state: ", state)
                }
            }

            onLoadingChanged: {
                // Windows hack to allow Fang to exit.
                // This bug seems to be a holdout from Qt's flirtation with WebKit.
                if (state == "closing" && loadRequest.status == WebEngineView.LoadSucceededStatus) {
                    Qt.quit();
                }
            }
        }

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Left:
                qmlNewsInteractor.jumpPrevious();

                break;
            case Qt.Key_Right:
                qmlNewsInteractor.jumpNext();

                break;
            case Qt.Key_F5:
                qmlNewsInteractor.refreshCurrentFeed();

                break;
            case Qt.Key_R:
                if (event.modifiers & Qt.ControlModifier) {
                    qmlNewsInteractor.refreshCurrentFeed();
                }

                break;
            case Qt.Key_Q:
                if (event.modifiers & Qt.ControlModifier) {
                    Qt.quit();
                }

                break;
            }
        }
    }
}
