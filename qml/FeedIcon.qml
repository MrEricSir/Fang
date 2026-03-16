import QtQuick
import QtQuick.Effects

// Reusable feed favicon with rounded corners and RSS fallback.
Item {
    id: feedIcon;

    property url source;
    property real iconSize: 24;
    property bool showFallback: true;

    readonly property bool imageLoaded: feedImage.status === Image.Ready;

    Style {
        id: style;
    }

    width: iconSize * style.scale;
    height: iconSize * style.scale;

    // Mask shape for rounded icon corners.
    Rectangle {
        id: iconMask;

        anchors.fill: parent;
        radius: 5 * style.scale;
        layer.enabled: true;
        visible: false;
    }

    // Feed icon with rounded corners (iOS-style).
    Image {
        id: feedImage;

        source: feedIcon.source;
        visible: status === Image.Ready;

        anchors.fill: parent;
        fillMode: Image.PreserveAspectCrop;
        asynchronous: true;

        layer.enabled: true;
        layer.effect: MultiEffect {
            maskEnabled: true;
            maskSource: iconMask;
        }
    }

    // RSS symbol fallback, shown when no image loaded.
    Image {
        id: defaultFeedIcon;

        visible: feedIcon.showFallback && !feedImage.visible;

        source: fangSettings.currentStyle === "LIGHT"
                ? "images/symbol_rss.svg"
                : "images/symbol_dark_rss.svg";

        anchors.fill: parent;
        asynchronous: true;
    }
}
