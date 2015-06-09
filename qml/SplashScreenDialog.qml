import QtQuick 2.4
import Fang 1.0


// This is the dialog that's open when Fang starts.  Aside from showing off our snazzy logo, it
// also gives the sidebar and news view time to load.
Dialog {
    id: splashScreenDialog;

    title: "";

    isSplashScreen: true;
    openAtStart: true;

    Item {
        id: topSpacer

        width: parent.width;
        height: (splashScreenDialog.height / 2.0) - fangLogo.height;
    }

    Image {
        id: fangLogo;

        source: "qrc:/qml/images/fang_logo_color.svg";

        opacity: 0.0;

        // 20% margins, for a decent size.
        x: parent.width * 0.2;
        width: parent.width - (parent.width * 0.4);
        fillMode: Image.PreserveAspectCrop;

        // Make SVGs render real good like.
        sourceSize.width: width;
        sourceSize.height: height;

        NumberAnimation on opacity {
            id: splashFadeIn;
            from: 0.0;
            to: 1.0;
            duration: 350;
            easing.type: Easing.InOutQuad;
        }

        Timer {
            id: splashCompleteTimer;
            interval: 350;
            running: false;
            repeat: false;

            onTriggered: {
                // It will either be closed here if the load's already complete,
                // or in the Connections handler.
                if (!main.isInProgress) {  // don't leave this one in!
                    console.log("Wasn't in progress")
                    close();
                }
            }
        }

        Connections {
            target: main;
            onIsInProgressChanged: {
                // If we didn't close in the above timer, we're closing here.
                if (!splashScreenDialog.isClosed && !main.isInProgress && !splashCompleteTimer.running) {
                    close();
                }
            }
        }

        Component.onCompleted: {
            // Start here:
            splashFadeIn.start();
            splashCompleteTimer.restart();
        }
    }
}
