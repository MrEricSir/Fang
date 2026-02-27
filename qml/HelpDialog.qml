import QtQuick
import Fang 1.0

Dialog {
    id: helpDialog;

    title: "Welcome to Fang";

    DialogText {
        text: "Fang helps you stay up to date with your favorite news websites " +
              "and blogs.";
    }

    DialogText {
        text: "RSS and Atom news feeds are supported. For the latest information " +
              "please visit <a href='http://www.getfang.com'>www.GetFang.com</a>.";
    }

    DialogSpacer {}

    DialogText {
        text: "Add a feed";
        font: style.font.title;
    }

    DialogText {
        text: "Press the + button at the bottom of the sidebar to add a feed. " +
              "Enter the URL and press \"Continue.\" Once the feed is located, " +
              "edit the title if you like and press \"Add Feed.\"";
    }

    DialogText {
        text: "<b>Tip:</b> If Fang wasn't able to locate an RSS or Atom news feed, " +
              "don't give up! Try searching for the site's exact feed URL on the web.";
    }

    DialogSpacer {}

    DialogText {
        text: "Import from other news readers";
        font: style.font.title;
    }

    DialogText {
        text: "Most news readers (including this one) can export their feed list " +
              "to a file format called OPML. Check your current news reader for an " +
              "option to export an OPML file.";
    }

    DialogText {
        text: "Once you have an OPML file, press the gear button at the top of the " +
              "sidebar, then press the \"Import\" button under \"OPML feed list.\"";
    }

    DialogSpacer {}

    DialogText {
        text: "Reading a feed";
        font: style.font.title;
    }

    DialogText {
        text: "Select a feed in the sidebar and scroll down as you read. A bookmark " +
              "appears if you scroll back up. Double-click the feed in the sidebar to " +
              "jump back to the bookmark.";
    }

    DialogText {
        text: "<b>Tip:</b> Some news feeds only include a preview. Click the headline " +
              "to open the complete article in your default web browser.";
    }

    DialogSpacer {}

    DialogText {
        text: "Keyboard shortcuts";
        font: style.font.title;
    }

    // Keyboard shortcuts list.
    Column {
        width: parent.width;
        spacing: 6 * style.scale;

        ShortcutRow { keys: ["\u2191", "\u2193"]; description: "Scroll up or down"; }
        ShortcutRow { keys: ["\u2192", "\u2190"]; description: "Next or previous news item"; }
        ShortcutRow { keys: ["PgUp", "PgDn"]; description: "Scroll by one screen"; }
        ShortcutRow { keys: ["Home", "End"]; description: "Scroll to top or bottom"; }
        ShortcutRow {
            keys: platform === "MAC" ? ["\u2318R"] : ["Ctrl+R"];
            description: "Refresh current feed";
        }
        ShortcutRow {
            keys: platform === "MAC" ? ["\u2318Q"] : ["Ctrl+Q"];
            description: "Quit";
        }
    }

    DialogSpacer {}

    DialogText {
        text: "\u00A9 Copyright 2013-2026 Eric Gregory";
        textColor: style.color.fadedText;
        horizontalAlignment: Text.AlignHCenter;
    }

    DialogGroup {
        width: parent.width;

        DialogButton {
            text: "Close";
            onClicked: close();
        }
    }
}
