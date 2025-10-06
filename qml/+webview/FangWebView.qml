import QtQuick
import QtWebView

WebView {
    id: newsView;

    ///// START API /////

    // Set this to show/hide the native WebView window
    property bool isVisible: false;

    function close() {
        // Only used for WebEngine, so do nothin'
    }

    ///// END API /////

    visible: isVisible;

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
