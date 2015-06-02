import QtQuick 2.4
import QtWebView 1.0

WebView {
    id: newsView;

    ///// START API /////

    // Set this to show/hide the native WebView window
    property bool isVisible: false;

    function close() {
        // Only used for WebEngine, so do nothin'
    }

    ///// END API /////

    // Android hack: Zero-out dimensions until we've gotten past the startup screen.  Otherwise
    // we'll get a big ugly rectangle.
    property bool firstIsVisible: false;
    width: firstIsVisible ? parent.width : 0;
    height: firstIsVisible ? parent.height : 0;
    visible: isVisible;

     // No overlapping windows in WebView: this is a workaround.
    onIsVisibleChanged: {
        parent.visible = isVisible;
        if (isVisible) {
            firstIsVisible = true;
        }
    }

    // The URL is going to be platform-specific.  For now, it's Android-only.
    url: {
        switch(platform) {
            case "ANDROID": return "file:///android_asset/index_android.html";

            // TODO
//          case "MAC": return "";
//          case "IOS": return "";
        }

        // So far no native WebView platforms can load QRC.  Maybe someday?
        return "UnrecognizedPlatformError";
    }
}
