import QtQuick 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0

Dialog {
    id: dropboxConnectDialog
    
    title: "Sync feeds with Dropbox"
    wideDialog: true
    
    DialogText {
        text: "Do you use Fang on more than one computer? Keep them all in sync using your Dropbox account."
    }
    
    function authorized(code) {
        //console.log("Got me an auth code: ", code);
        dropboxManager.login(code);
        
        // TODO: show state of auth, deal with handshake errors, offline, etc.
        close();
    }
    
    // Read-only.
    // 
    // These represent special and allowed URLs.
    property string initialURL: "https://www.dropbox.com/1/oauth2/authorize?client_id=" + dropboxManager.getClientCode() + "&response_type=code"
    property string authURL: "https://www.dropbox.com/1/oauth2/authorize_submit"
    property string loginPrefix: "https://www.dropbox.com/login"
    property string authPrefix: "https://www.dropbox.com/1/oauth2"
    
    DialogButton {
        id: cancelButton
        
        text: "Cancel"
        onClicked: close()
        enabled: true
    }
        
    WebView {
        id: myView
        
        Connections {
            target: dropboxManager
            
            onConnectedStateChanged: {
                if (dropboxManager.connectedState == "logout") {
                    // Make the browser visible and load 'er up!
                    myView.visible = true;
                    myView.url = initialURL;
                }
            }
        }
        
        width: parent.width
        height: parent.width // TODO: Should this change based on text size?
        
        visible: false
        
        experimental.preferences.developerExtrasEnabled: true
        experimental.preferences.navigatorQtObjectEnabled: true
        
        // Resize a bit more intelligently.
        experimental.preferredMinimumContentsWidth: 300
        
        function doAuthCheck() {
            // Check if token is present.
            myView.experimental.evaluateJavaScript(
                        "var elements = document.getElementsByClassName('auth-code'); " +
                        "console.log('num elements: ', elements.length); " +
                        "var code = 'authCheck'; " +
                        "if (elements.length >= 1) { " +
                        "   code += ' ' + elements[0].innerHTML; " +
                        "} " +
                        "navigator.qt.postMessage( code ); "
                        );
        }
        
        experimental.onMessageReceived: {
            console.log("get msg from javascript:", message.data)
            var commandArray = message.data.split(" ");
            var cmd = commandArray[0];
            
            if (cmd !== "authCheck")
                return;
            
            visible = false;
            
            // If we got a second token, it's the auth key.
            if (commandArray.length == 2) {
                authorized(commandArray[1]);
            } else {
                dropboxConnectDialog.close();
            }
            
        }
        
        onLoadingChanged: {
            console.log();
            console.log("Loading changed: ", loadRequest.status, loadRequest.url)
            var strUrl = "" + loadRequest.url;
            
            if (loadRequest.status === WebView.LoadFailedStatus) {
                // If the page didn't load, just do a close.
                // TODO: add an error message
                visible = false;
                dropboxConnectDialog.close();
            } else if (loadRequest.status === WebView.LoadSucceededStatus) {
                // A page loaded. What to do?!
                console.log("Load request: ", loadRequest)
                if (strUrl === initialURL) {
                    return; // Just roll with it!
                } else if (strUrl === authURL) {
                    doAuthCheck();
                } else if (strUrl.indexOf(loginPrefix) == 0) {
                    // Let login requests pass through.
                } else {
                    // Got an unexpected URL!
                    // TODO: add an error message
                    console.log("Unexpected URL: ", loadRequest.url)
                    visible = false;
                    dropboxConnectDialog.close();
                }
            }
        }
    }
}
