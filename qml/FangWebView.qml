import QtQuick
import QtWebView

WebView {
    id: newsView;

    ///// API /////

    function close() {
        state = "closing";
    }

    property bool isVisible: false;

    ///// END API /////

    // Visibility hack for native WebView
    x: parent.x;
    y: parent.y;
    width: isVisible ? parent.width : 0;
    height: isVisible ? parent.height : 0;

    // Settings (should not be changed at runtime)
    settings.javaScriptEnabled: true;
    settings.allowFileAccess: true;
    settings.localContentCanAccessFileUrls: true;

    // State
    state: "news";
    states: [
        // The typical news/help mode.
        State { name: "news" },

        // Let WebKit load a safe, empty page before shutdown.
        State { name: "closing" }
    ]

    onStateChanged: {
        console.log("newsView state changed:", state);
        switch (state) {
        case "news":
            newsView.url = "http://localhost:2844/html/index.html";

            break;

        case "closing":
            newsView.url = "http://localhost:2844/html/blank.html";

            break;

        default:
             // Shouldn't get here.
            console.error("newsView: Unhandled state:", state);
        }
    }
}
