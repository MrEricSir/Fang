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

    ///// END API /////

    state: "news";
    states: [
        // The typical news/help mode.
        State { name: "news" },

        // Let WebKit load a safe, empty page before shutdown.
        State { name: "closing" }
    ]

    onStateChanged: {
        console.log("webengine state changed:", state)
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

    // TODO: Test on Windows to see if this is still needed. [qt6]
    // onLoadingChanged: {
    //     //console.log("webengine loading changed:", loadRequest.status)
    //     // Windows hack to allow Fang to exit.
    //     // This bug seems to be a holdout from Qt's flirtation with WebKit.
    //     if (state == "closing" && loadRequest.status == WebEngineView.LoadSucceededStatus) {
    //         Qt.quit();
    //     }
    // }
}
