import QtQuick
import QtQuick.Controls as Controls
import QtQuick.Layouts
import Fang 1.0

Dialog {
    id: searchDialog;
    title: "Search";

    Style {
        id: style;
    }

    // Initial state: Set this before opening the dialog.
    property string initialQuery: "";
    property string initialScopeType: "global";
    property int initialScopeId: -1;

    onDialogOpened: {
        buildFeedModel();

        if (initialQuery !== "") {
            searchInput.text = initialQuery;
        }

        // Selects the corresponding feed.
        selectFeedByScope(initialScopeType, initialScopeId);

        searchInput.forceActiveFocus();
    }

    // Populate feedModel.
    function buildFeedModel() {
        feedModel.clear();

        // All News appears first.
        feedModel.append({ text: "All News", scopeType: "global", scopeId: -1 });

        // Add regular feeds (no pinned feed, folders, etc.)
        for (let i = 0; i < feedListModel.count; i++) {
            const isSpecial = feedListModel.dataByField(i, "isSpecialFeed");
            const isFolder = feedListModel.dataByField(i, "isFolder");
            const isSearch = feedListModel.dataByField(i, "isSearchFeed");

            if (isSpecial || isFolder || isSearch) {
                continue;
            }

            const title = feedListModel.dataByField(i, "title");
            const uid = feedListModel.dataByField(i, "uid");

            feedModel.append({ text: title, scopeType: "feed", scopeId: uid });
        }
    }

    // Select the ComboBox entry.
    function selectFeedByScope(scopeType, scopeId) {
        if (scopeType === "global") {
            feedCombo.currentIndex = 0;
            return;
        }

        for (let i = 0; i < feedModel.count; i++) {
            if (feedModel.get(i).scopeId === scopeId) {
                feedCombo.currentIndex = i;
                return;
            }
        }

        // Fallback to All News.
        feedCombo.currentIndex = 0;
    }

    function doSearch() {
        const query = searchInput.text.trim();
        if (query === "") {
            return;
        }

        const index = feedCombo.currentIndex;
        const entry = feedModel.get(index);
        const scopeType = entry.scopeType;
        const scopeId = entry.scopeId;
        const feedTitle = entry.text;

        close();
        news.performSearch(query, scopeType, scopeId);
        main.addSearchHistory(query, scopeType, scopeId, feedTitle);
    }


    // Feed selector.
    DialogText {
        text: "Search for";
    }

    // Search input with history dropdown.
    Item {
        id: searchInputContainer;

        // Feed model for the ComboBox.
        // Created on open to account for changes in added/removed feeds.
        ListModel {
            id: feedModel;
        }
        width: parent.width;
        height: searchInput.height;

        TextEntry {
            id: searchInput;
            width: parent.width;
            rightPadding: historyDropdownButton.visible ? historyDropdownButton.width + 10 * style.scale : 6 * style.scale;
            placeholderText: "Search news";
            onAccepted: doSearch();
        }

        // Dropdown arrow — only visible when there's history.
        Text {
            id: historyDropdownButton;
            visible: main.searchHistory.length > 0;
            anchors.right: searchInput.right;
            anchors.rightMargin: 6 * style.scale;
            anchors.verticalCenter: searchInput.verticalCenter;
            text: "\u25BC";
            font: style.font.standard;
            color: style.color.fadedText;

            MouseArea {
                anchors.fill: parent;
                anchors.margins: -4;
                cursorShape: Qt.PointingHandCursor;
                onClicked: {
                    if (historyPopup.justClosed) {
                        return;
                    }
                    historyPopup.visible ? historyPopup.close() : historyPopup.open();
                }
            }
        }

        Controls.Popup {
            id: historyPopup;
            popupType: Controls.Popup.Window;

            // Workaround for race between close and history popup.
            property bool justClosed: false;
            onClosed: {
                justClosed = true;
                ustClosedTimer.restart();
            }
            Timer {
                id: justClosedTimer;
                interval: 200;
                onTriggered: historyPopup.justClosed = false;
            }
            parent: searchInputContainer;
            y: searchInputContainer.height;
            width: searchInputContainer.width;
            padding: 4;

            // Pass through so the repeater has access to these properties.
            readonly property font itemFont: style.font.standard;
            readonly property color itemTextColor: style.color.dialogText;
            readonly property color itemFeedColor: style.color.fadedText;
            readonly property color itemHoverColor: style.color.dialogButtonHover;
            readonly property color bgColor: style.color.dialogBackground;
            readonly property color borderColor: style.color.textEntryBorder;
            readonly property double itemRadius: (platform === "MAC") ? 6 * style.scale : style.defaultRadius;
            readonly property double itemMargin: 6 * style.scale;
            readonly property double itemPadding: 10 * style.scale;

            contentItem: Column {
                Repeater {
                    model: main.searchHistory;

                    Rectangle {
                        width: historyPopup.width - 2 * historyPopup.padding;
                        height: historyRow.implicitHeight + historyPopup.itemPadding;
                        color: historyItemMouse.containsMouse ? historyPopup.itemHoverColor : "transparent";
                        radius: historyPopup.itemRadius;

                        RowLayout {
                            id: historyRow;
                            anchors.left: parent.left;
                            anchors.right: parent.right;
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.leftMargin: historyPopup.itemMargin;
                            anchors.rightMargin: historyPopup.itemMargin;
                            spacing: historyPopup.itemMargin;

                            Text {
                                Layout.fillWidth: true;
                                text: modelData.query;
                                font: historyPopup.itemFont;
                                color: historyPopup.itemTextColor;
                                elide: Text.ElideRight;
                            }

                            Text {
                                text: modelData.feedTitle;
                                font: historyPopup.itemFont;
                                color: historyPopup.itemFeedColor;
                            }
                        }

                        MouseArea {
                            id: historyItemMouse;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            cursorShape: Qt.PointingHandCursor;
                            onClicked: {
                                searchInput.text = modelData.query;
                                selectFeedByScope(modelData.scopeType, modelData.scopeId);
                                historyPopup.close();
                            }
                        }
                    }
                }
            }

            background: Rectangle {
                color: historyPopup.bgColor;
                border.color: historyPopup.borderColor;
                border.width: 1;
                radius: historyPopup.itemRadius;
            }
        }
    }

    // Feed selector.
    DialogText {
        text: "In Feed";
    }

    Controls.ComboBox {
        id: feedCombo;
        width: parent.width;
        model: feedModel;
        textRole: "text";
    }

    DialogGroup {
        width: parent.width;

        DialogButton {
            text: "Cancel";
            onClicked: close();
        }

        DialogButton {
            isPrimary: true;
            text: "Search";
            enabled: searchInput.text.trim() !== "";
            onClicked: doSearch();
        }
    }
}
