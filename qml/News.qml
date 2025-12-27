import QtQuick
import Fang 1.0

Item {
    id: news

    // Read-only: The number of special feeds in the feed list
    property alias specialFeedCount: newsFeedInteractor.specialFeedCount;

    // Read-only: Whether bookmarks are enabled for this feed.
    property bool bookmarksEnabled: true;

    // Set this if you want the news to be visible (native WebView only)
    property alias isVisible: newsView.isVisible;

    property bool isWebPageLoaded: newsView.loadProgress === 100;
    
    // Used by main for double clicking on feed titles.
    function jumpToBookmark() {
        newsFeedInteractor.jumpToBookmark();
    }
    
    function orderChanged() {
        newsFeedInteractor.orderChanged();
    }
    
    function refreshCurrentFeed() {
        newsFeedInteractor.refreshCurrentFeed();
    }

    function refreshFeed(feed) {
        newsFeedInteractor.refreshFeed(feed);
    }

    function refreshAllFeeds() {
        newsFeedInteractor.refreshAllFeeds();
    }

    function markAllAsRead(feed) {
        newsFeedInteractor.markAllAsRead(feed);
    }

    function markAllAsUnread(feed) {
        newsFeedInteractor.markAllAsUnread(feed);
    }
    
    // Switch to news.
    function showNews() {
        newsFeedInteractor.showNews();
    }
    
    // Switch to the welcome/help screen.
    function showWelcome() {
        newsFeedInteractor.showWelcome();
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
        
        // The "interactor" is what talks to the C++ layer.
        NewsFeedInteractor {
            id: newsFeedInteractor;
        }
        
        // Our web page!
        FangWebView {
            id: newsView;

            // Stops scrolling while we're loading or a dialog is displayed.
            enabled: newsFocus && news.isWebPageLoaded;
        }

        Keys.onPressed: (event)=> {
            switch (event.key) {
            case Qt.Key_Left:
                newsFeedInteractor.jumpPrevious();

                break;
            case Qt.Key_Right:
                newsFeedInteractor.jumpNext();

                break;
            case Qt.Key_F5:
                newsFeedInteractor.refreshCurrentFeed();

                break;
            case Qt.Key_R:
                if (event.modifiers & Qt.ControlModifier) {
                    newsFeedInteractor.refreshCurrentFeed();
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
