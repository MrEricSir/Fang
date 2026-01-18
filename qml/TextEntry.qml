import QtQuick
import QtQuick.Controls.Basic

// A text entry box.
TextField {
    id: textEntry;

    Style {
        id: style;
    }

    color: style.color.textEntryText;

    font {
        family: style.font.defaultFamily;
        pointSize: style.font.defaultSize;
    }

    placeholderTextColor: style.color.textEntryHint;

    background: Rectangle {
        color: style.color.textEntryBackground;
        border.color: style.color.textEntryBorder;
        border.width: 1 * style.scale;
    }

    topPadding: 6  * style.scale;
    bottomPadding: topPadding;
}
