import QtQuick
import QtWebEngine

WebEngineView {
    id: newsView;

    ///// START API /////

    // Unused for WebEngine
    property bool isVisible: false;

    function close() {
        state = "closing";
    }

    // Search functions.
    // scope: "global" (default), "feed", or "folder"
    // scopeId: feed_id or folder_id when scope is "feed" or "folder"
    function performSearch(query, scope, scopeId) {
        var escapedQuery = query.replace(/\\/g, '\\\\').replace(/'/g, "\\'");
        var scopeArg = scope || 'global';
        var scopeIdArg = scopeId || -1;
        runJavaScript("performSearch('" + escapedQuery + "', '" + scopeArg + "', " + scopeIdArg + ")");
    }

    function clearSearch() {
        runJavaScript("clearSearch()");
    }

    ///// END API /////

    state: "news";
    states: [
        // The typical news/help mode.
        State { name: "news" },

        // Let WebKit load a safe, empty page before shutdown.
        State { name: "closing" }
    ]

    onStateChanged: {
        console.log("webengine state changed:", state);
        switch (state) {
        case "news":
            newsView.url = "http://localhost:" + localServerPort + "/html/index.html";

            break;

        case "closing":
            newsView.url = "http://localhost:" + localServerPort + "/html/blank.html";

            break;

        default:
             // Shouldn't get here.
            console.error("You didn't handle state: ", state)
        }
    }
}
