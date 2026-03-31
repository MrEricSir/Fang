import QtQuick
import Fang 1.0

Dialog {
    id: updateDialog;

    title: "Update";

    // The new version number to display
    property string newVersion: "";

    Image {
        source: "qrc:/qml/images/fang_logo_color.svg";
        anchors.horizontalCenter: parent.horizontalCenter;
        width: parent.width * 0.6;
        fillMode: Image.PreserveAspectFit;
        sourceSize.width: width;
    }

    DialogText {
        text: "Update Available";
        horizontalAlignment: Text.AlignHCenter;
        font: style.font.title;
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

            text: "Close";
            onClicked: close();
        }
    }
}
