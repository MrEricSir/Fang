import QtQuick
import QtQuick.Controls
import Fang 1.0

// Dialog container.
// Regular dialogs display as a centered card over dimmed content.
// Splash screen dialogs use full-screen layout.
FangScreen {
    id: dialog;

    signal dialogOpened(); // Open has completed
    signal dialogClosed(var self);
    signal dialogClosing(var self);

    // Dialog title text.
    property string title;

    // [Optional] FeedItem object.
    property var feed;

    // This allows children to be positioned within the element.
    default property alias contents: placeholder.children;

    // Read only.
    property bool isClosing: dialogMainContainer.state === "closed" || dismissTimer.running;
    property bool isClosed: dialogMainContainer.state === "closed";
    property bool wasOpened: openAtStart ? true : false;

    // Only used for splash screen.
    property bool openAtStart: false;

    // Transparent background for card dialogs; solid for splash screen.
    color: isSplashScreen ? style.color.dialogBackground : "transparent";
    visible: openAtStart ? true : false // Managed by state transitions

    // Opens the dialog.
    function open() {
        wasOpened = true;
        dialogMainContainer.state = "open";
    }

    // Dismisses the dialog after a short delay.  Normally it's best to use this instead of close.
    function dismiss() {
        dismissTimer.restart();
    }

    // Immediately closes the dialog.
    function close() {
        if (dialogMainContainer.state === "open") {
            dialogClosing(dialog);
            Qt.inputMethod.hide(); // Ditch mobile keyboard
        }

        dialogMainContainer.state = "closed";
    }

    // Put focus back on this dialog.
    function forceFocus() {
        dialog.forceActiveFocus();
    }

    // Send closed signal
    onIsClosedChanged: {
        if (isClosed && wasOpened) {
            dialogClosed(dialog);
            Qt.inputMethod.hide();  // Ditch mobile keyboard
        }
    }

    Keys.onPressed: (event)=> {
        if ((event.key === Qt.Key_Escape || event.key === Qt.Key_Back) && !isSplashScreen) {
            close();
            event.accepted = true;
        }
    }

    Item {
        id: dialogMainContainer

        state: openAtStart ? "open" : "closed"

        states: [
            State { name: "open" },
            State { name: "closed" }
        ]

        anchors.fill: parent

        transitions: [
            // --- Close transition ---
            Transition {
                from: "open"
                to: "closed"
                SequentialAnimation {
                    ParallelAnimation {
                        // Card: fade out + slide down (regular dialogs only).
                        NumberAnimation {
                            target: dialogCard
                            property: "opacity"
                            to: 0
                            duration: isSplashScreen ? 0 : 200
                            easing.type: Easing.InQuad
                        }
                        NumberAnimation {
                            target: dialogCard
                            property: "anchors.verticalCenterOffset"
                            to: 20
                            duration: isSplashScreen ? 0 : 200
                            easing.type: Easing.InQuad
                        }

                        // Splash screen: fade out entire dialog to reveal blurred content.
                        NumberAnimation {
                            target: dialog
                            property: "opacity"
                            from: 1
                            to: isSplashScreen ? 0 : 1
                            duration: isSplashScreen ? 400 : 0
                            easing.type: Easing.InOutQuad
                        }
                    }

                    PropertyAction {
                        target: dialog
                        property: "visible"
                        value: false
                    }

                    // Reset opacity after hide (for splash screen).
                    PropertyAction {
                        target: dialog
                        property: "opacity"
                        value: 1
                    }
                }
            },

            // --- Open transition ---
            Transition {
                from: "closed"
                to: "open"

                SequentialAnimation {
                    PropertyAction {
                        target: dialog
                        property: "visible"
                        value: true
                    }

                    ParallelAnimation {
                        // Card: fade in + slide up.
                        NumberAnimation {
                            target: dialogCard
                            property: "opacity"
                            from: 0
                            to: 1
                            duration: isSplashScreen ? 0 : 250
                            easing.type: Easing.OutQuad
                        }
                        NumberAnimation {
                            target: dialogCard
                            property: "anchors.verticalCenterOffset"
                            from: 20
                            to: 0
                            duration: isSplashScreen ? 0 : 250
                            easing.type: Easing.OutQuad
                        }
                    }

                    ScriptAction {
                        script: {
                            forceFocus();
                            dialog.dialogOpened();
                        }
                    }
                }
            }
        ]

        // Background click area dismisses dialog when clicking outside pf ot/
        MouseArea {
            anchors.fill: parent

            // Capture scroll events and such from propagating to WebView.
            hoverEnabled: true
            preventStealing: true
            onWheel: {}

            onClicked: {
                if (!isSplashScreen) {
                    close();
                }
            }
        }

        // --- Dialog card ---
        // Centered modal card for regular dialogs; full-screen for splash screen.
        Rectangle {
            id: dialogCard

            // Splash screen: fill window. Regular dialog: centered card.
            width: isSplashScreen
                   ? parent.width
                   : Math.min(450 * style.scale, parent.width - 60 * style.scale)
            height: isSplashScreen
                    ? parent.height
                    : Math.min(
                        dialogTitle.height + dialogTitle.anchors.topMargin
                            + contentFlickable.anchors.topMargin + contentFlickable.contentHeight
                            + contentFlickable.anchors.bottomMargin,
                        parent.height - 60 * style.scale
                    )

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            radius: isSplashScreen ? 0 : (platform === "MAC" ? 12 * style.scale : 8 * style.scale)
            color: style.color.dialogBackground
            border.color: isSplashScreen ? "transparent" : style.color.dialogButtonBorder
            border.width: isSplashScreen ? 0 : 1
            clip: true

            // Absorb clicks within the card so they don't dismiss the dialog.
            MouseArea {
                anchors.fill: parent
            }

            Text {
                id: dialogTitle

                visible: !isSplashScreen
                text: dialog.title

                font: style.font.title;
                color: style.color.dialogText

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 20 * style.scale
                anchors.leftMargin: 15 * style.scale
                anchors.rightMargin: 15 * style.scale
            }

            // Separator line below title.
            Rectangle {
                id: titleSeparator

                visible: !isSplashScreen
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: dialogTitle.bottom
                anchors.topMargin: 7 * style.scale

                height: 1
                color: style.color.dialogButtonBorder
                opacity: 1
                z: 1
            }

            // Scrollable dialog contents.
            Flickable {
                id: contentFlickable

                anchors.top: isSplashScreen ? parent.top : dialogTitle.bottom
                anchors.topMargin: isSplashScreen ? 0 : 15 * style.scale
                anchors.bottom: parent.bottom
                anchors.bottomMargin: isSplashScreen ? 0 : 15 * style.scale
                anchors.left: parent.left
                anchors.leftMargin: isSplashScreen ? 0 : 15 * style.scale
                anchors.right: parent.right
                anchors.rightMargin: isSplashScreen ? 0 : 4 * style.scale

                contentWidth: width
                contentHeight: container.childrenRect.height
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                clip: true

                ScrollBar.vertical: FangScrollBar {
                    backgroundColor: style.color.dialogBackground;
                    visible: !isSplashScreen; // No scrollbar on the splash screen.
                }

                Item {
                    id: container

                    width: isSplashScreen
                           ? 400 * style.scale
                           : parent.width - 15 * style.scale
                    x: isSplashScreen ? (parent.width - width) / 2 : 0

                    // Children go here.
                    Column {
                        id: placeholder

                        width: parent.width
                        spacing: 8 * style.scale
                    }
                }
            }
        }

        // Timer so we give the user a glimpse of our message before closing
        // the dialog.
        Timer {
            id: dismissTimer
            interval: 700
            running: false
            repeat: false

            onTriggered: close()
        }

        Style {
            id: style
        }
    }
}
