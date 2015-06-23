import QtQuick 2.4
import QtWebEngine 1.0

WebEngineView {
    id: newsView;

    ///// START API /////

    // Unused for WebEngine
    property bool isVisible: false;

    function close() {
        state = "closing";
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
