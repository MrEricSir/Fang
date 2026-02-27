import QtQuick
import QtQuick.Effects

/**
 * Represents all top-level screens (main frame, dialogs, etc.)
 */
Rectangle {
    id: screen;

    // Children go into the content wrapper (underneath the blocker).
    default property alias content: contentWrapper.data;

    // Index of this screen (used for z transitions)
    property double index: 0;

    // Special handling for the splash screen dialog.
    property bool isSplashScreen: false;

    // Blur amount (0.0 = none, 1.0 = max). Animated by transitions.
    property real blurAmount: 0;

    // When the fade-in is done.
    signal fadeInComplete();

    // Fades the screen out, man.
    function fadeOut() {
        state = "out";
    }

    // Whoa fade back in!
    function fadeIn() {
        state = "in";
    }

    color: style.color.background;
    width: parent.width;
    height: parent.height;
    z: index;

    states: [
        State { name: "in"; },
        State { name: "out"; }
    ]

    // Default state is faded out for splash screen.
    state: isSplashScreen ? "out" : "in";

    Item {
        id: contentWrapper;

        anchors.fill: parent;

        layer.enabled: screen.blurAmount > 0;
        layer.effect: MultiEffect {
            blurEnabled: true
            blur: screen.blurAmount
            blurMax: 48
        }
    }

    // Dim overlay, drawn on top of (blurred) content.
    Rectangle {
        id: blocker;

        anchors.fill: parent;
        color: "transparent";

        z: screen.z + 1;
    }

    transitions: [
        Transition {
            from: "in";
            to: "out";
            ParallelAnimation {
                ColorAnimation {
                    id: fadeOut;

                    target: blocker;
                    properties: "color";
                    from: "transparent";
                    to: style.color.blockerBackground;
                    duration: 300;
                    easing.type: Easing.InOutQuad;
                }
                NumberAnimation {
                    target: screen;
                    property: "blurAmount";
                    from: 0;
                    to: 0.4;
                    duration: 300;
                    easing.type: Easing.OutSine;
                }
            }
        },
        Transition {
            from: "out";
            to: "in";

            onRunningChanged: {
                if (!running) {
                    screen.fadeInComplete();
                }
            }

            ParallelAnimation {
                ColorAnimation {
                    id: fadeIn;

                    target: blocker;
                    properties: "color";
                    to: "transparent";
                    from: style.color.blockerBackground;
                    duration: 300;
                    easing.type: Easing.InOutQuad;
                }
                NumberAnimation {
                    target: screen;
                    property: "blurAmount";
                    from: 0.4;
                    to: 0;
                    duration: 300;
                    easing.type: Easing.InSine;
                }
            }
        }
    ]

    Style {
        id: style;
    }
}
