import QtQuick
import Fang 1.0

Dialog {
    id: aboutDialog;
    
    title: "About";
    
    Image {
        source: "qrc:/qml/images/fang_logo_color.svg";

        // 60% of parent width, centered.
        width: parent.width * 0.6;
        anchors.horizontalCenter: parent.horizontalCenter;
        fillMode: Image.PreserveAspectFit;

        // Make SVGs render real good like.
        sourceSize.width: width;
        sourceSize.height: height;
    }
    
    DialogText {
        text: "Feed on news";
        horizontalAlignment: Text.AlignHCenter;
        font: style.font.title;
    }

    DialogText {
        text: "Version " + fangVersion;
        horizontalAlignment: Text.AlignHCenter;
    }
    
    DialogText {
        text: "<a href='http://www.getfang.com'>Website</a> | " +
              "<a href='https://github.com/MrEricSir/Fang'>GitHub</a>";
        horizontalAlignment: Text.AlignHCenter;
    }

    DialogText {
        text: "Credits";
        horizontalAlignment: Text.AlignHCenter;
        font: style.font.title;
    }
    
    DialogText {
        text: "Software & design\n" +
              "Eric Gregory\n\n" +
              "Logo\n" +
              "Studyou Design\n\n" +
              "Made in San Francisco, California.";
        
        horizontalAlignment: Text.AlignHCenter;
    }
    
    DialogText {
        text: "\nCopyright 2013-2026 Eric Gregory";
        textColor: style.color.fadedText;
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
