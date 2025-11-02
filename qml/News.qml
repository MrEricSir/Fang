import QtQuick
import Fang 1.0

Item {
    id: news

    // Read-only: The number of special feeds in the feed list
    property alias specialFeedCount: qmlNewsInteractor.specialFeedCount;

    // Read-only: Whether bookmarks are enabled for this feed.
    property bool bookmarksEnabled: true;

    // Read-only: Whether the news view is loading stuff.
    property alias isInProgress: qmlNewsInteractor.loadInProgress;

    // Set this if you want the news to be visible (native WebView only)
    property alias isVisible: newsView.isVisible;
    
    // Used by main for double clicking on feed titles.
    function jumpToBookmark() {
        qmlNewsInteractor.jumpToBookmark();
    }
    
    function orderChanged() {
        qmlNewsInteractor.orderChanged();
    }
    
    function refreshCurrentFeed() {
        qmlNewsInteractor.refreshCurrentFeed();
    }

    function refreshFeed(feed) {
        qmlNewsInteractor.refreshFeed(feed);
    }

    function markAllAsRead(feed) {
        qmlNewsInteractor.markAllAsRead(feed);
    }

    function markAllAsUnread(feed) {
        qmlNewsInteractor.markAllAsUnread(feed);
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
        newsView.close();
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
        
        // Our web page!
        FangWebView {
            id: newsView;

            anchors.fill: parent;

            // Stops scrolling while we're loading or a dialog is displayed.
            enabled: !qmlNewsInteractor.loadInProgress && newsFocus;
        }

        Keys.onPressed: (event)=> {
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
