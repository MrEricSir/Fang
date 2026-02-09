import QtQuick
import Fang 1.0

Dialog {
    id: aboutDialog;
    
    title: "About";
    
    Image {
        source: "qrc:/qml/images/fang_logo_color.svg";
        
        // 20% margins, for a decent size.
        x: parent.width * 0.2;
        width: parent.width - (parent.width * 0.4);
        fillMode: Image.PreserveAspectCrop;
        
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
        text: "<a href='http://www.getfang.com'>Visit our website</a>";
        horizontalAlignment: Text.AlignHCenter;
    }
    
    DialogSpacer {}
    
    DialogText {
        text: "Credits:\n\n" +
              "Software & design\n" +
              "Eric Gregory\n\n" +
              "Logo\n" +
              "Studyou Design";
        
        horizontalAlignment: Text.AlignHCenter;
    }
    
    DialogSpacer {}
    
    DialogText {
        text: "Copyright 2013-2026 Eric Gregory.  All rights reserved.\n\n" +
              "Made in San Francisco, California.";
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
