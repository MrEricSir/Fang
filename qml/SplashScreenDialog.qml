import QtQuick 2.4
import Fang 1.0

Dialog {
    id: splashScreenDialog;

    title: "";

    openAtStart: true

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
            id: splashCompleteTimer
            interval: 700
            running: false
            repeat: false

            onTriggered: close()
        }

        Component.onCompleted: {

            splashFadeIn.start();
            splashCompleteTimer.restart();
        }
    }
}
