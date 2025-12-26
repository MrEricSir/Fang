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
//     url: {
//         switch(platform) {
//             case "ANDROID":
//                 return "file:///android_asset/index_android.html";
//             default:
//                 return "qrc:///html/index.html";

//             // TODO
// //          case "MAC": return "";
// //          case "IOS": return "";
//         }

//         // So far no native WebView platforms can load QRC.  Maybe someday?
//         //return "UnrecognizedPlatformError";
//     }

    settings.javaScriptEnabled: true;
    settings.allowFileAccess: true;
    settings.localContentCanAccessFileUrls: true;

    //url: "file:///Users/eric/Development/Fang/html/index.html"
    //url: "https://www.google.com/"
    url: "http://localhost:2844/html/index.html";

    onLoadingChanged: function(loadRequest) {
        console.log('>>>>>>>>>>>>>> onLoadingChanged')
        console.log(loadRequest.status)
        return true
    }

    // Component.onCompleted: {

    //     //const resource = "qrc:///html/index.html";

    //     //newsView.loadHtml("<html><body color=\"#ff0000\"></body></html>");
    //     //const resource = "https://www.google.com"

    //     //const resource = "file:///Users/eric/Development/Fang/html/index.html"

    //     const resource = 'http://localhost:2844/html/index.html';

    //     var xhr = new XMLHttpRequest;
    //     xhr.open('GET', resource);
    //     xhr.onreadystatechange = function() {
    //         if (xhr.readyState === XMLHttpRequest.DONE) {
    //             var response = xhr.responseText;
    //             //console.log("got response text:", response)
    //             newsView.loadHtml(response)//, "http://localhost");
    //         }
    //     };
    //     xhr.send();
    // }
}
