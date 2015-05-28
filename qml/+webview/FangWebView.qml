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

    // The URL is going to be platform-specific.  For now, it's Android-only.
    url: {
        switch(platform) {
            case "ANDROID": return "file:///android_asset/index_android.html";

            // TODO
//          case "MAC": return "";
//          case "IOS": return "iosFontStyle"";
        }

        // So far no native WebView platforms can load QRC.  Maybe someday?
        return "UnrecognizedPlatformError";
    }

    // No overlapping windows in WebView: this is a workaround.
    width: isVisible ? parent.width : 0;
    height: isVisible ? parent.height : 0;
    visible: isVisible;
}
