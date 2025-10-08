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
}
