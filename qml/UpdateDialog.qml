import QtQuick
import Fang 1.0

Dialog {
    id: updateDialog;

    title: "Update";

    // The new version number to display
    property string newVersion: "";

    Image {
        source: "qrc:/qml/images/fang_logo_color.svg";

        // 20% margins, for a decent size.
        x: parent.width * 0.2;
        width: parent.width - (parent.width * 0.4);
        fillMode: Image.PreserveAspectCrop;

        sourceSize.width: width;
        sourceSize.height: height;
    }

    DialogText {
        text: "Update Available";
        horizontalAlignment: Text.AlignHCenter;
        fontPointSize: style.font.titleSize;
    }

    DialogText {
        text: "Latest Version: " + newVersion;
        horizontalAlignment: Text.AlignHCenter;
    }

    DialogText {
        text: "Current Version: " + fangVersion;
        horizontalAlignment: Text.AlignHCenter;
    }

    DialogText {
        text: "<a href='http://www.getfang.com'>Download from our website</a>";
        horizontalAlignment: Text.AlignHCenter;
    }

    DialogSpacer {}

    DialogGroup {
        width: parent.width;

        DialogButton {
            id: dismissButton;

            text: "Dismiss";
            onClicked: close();
        }
    }
}
