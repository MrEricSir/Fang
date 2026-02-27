import QtQuick

// Separator line between dialog sections.
Item {
    id: dialogSpacer;

    width: parent.width;
    height: 1;

    Rectangle {
        width: parent.width;
        height: 1;
        color: style.color.dialogButtonBorder;
    }

    Style {
        id: style;
    }
}
