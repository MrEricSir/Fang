import QtQuick
import RearrangeableTreeView

RearrangeableDelegate {
    id: feedTitleDelegate;

    Style {
        id: style;
    }

    signal jumpToBookmark();
    signal searchRequested(string query);
    signal searchCleared();

    onClicked: (mouse) => {
        if (mouse.button === Qt.LeftButton) {
            if (isFolder && opener.width > 0 && mouse.x < titleDelegate.x + opener.width) {
               toggleFolder();
            } else if (!isSearchFeed) {
               // Don't change selection for search feed - let the input handle clicks
               feedListView.currentIndex = index;
            }
        }
    }

    onDoubleClicked: (mouse) => {
        // Don't trigger jump to bookmark for search feed
        if (feedListView.currentIndex == index && !isSearchFeed) {
            feedTitleDelegate.jumpToBookmark();
        }
    }

    dragEnabled: !isSpecialFeed && !isSearchFeed;

    // Search feed needs to receive mouse events for text input
    acceptMouseEvents: !isSearchFeed;

    // Folders are always visible, but their children are not.
    visible: isFolder ? true : (parentFolder == -1 || folderOpen ? true : false);
    height: visible ? (35 * style.scale) : 0;

    folderIndent: height;

    // Folder opener icon
    Item {
        id: opener;

        visible: isFolder;
        width: isFolder ? feedTitleDelegate.height : 0;
        height: feedTitleDelegate.height;
        z: 10;

        Image {
            id: openerIcon;

            source: fangSettings.currentStyle === "LIGHT" ? "images/opener.png" : "images/opener_dark.png";
            x: 10;
            y: 10;

            width: sourceSize.width;
            height: sourceSize.height;

            fillMode: Image.PreserveAspectCrop;
            asynchronous: true;

            states: [
                State { name: "open"; },
                State { name: "closed"; }
            ]

            state: folderOpen ? "open" : "closed";

            Component.onCompleted: {
                if (!folderOpen) {
                    rotation = -90;
                }
            }

            transitions: [
                Transition {
                    from: "*";
                    to: "closed";
                    RotationAnimation {
                        running: false;
                        direction: RotationAnimation.Counterclockwise;
                        target: openerIcon;
                        to: -90;
                        duration: 250;
                        property: "rotation";
                    }
                },
                Transition {
                    from: "*";
                    to: "open";
                    RotationAnimation {
                        running: false;
                        direction: RotationAnimation.Clockwise;
                        target: openerIcon;
                        to: 0;
                        duration: 250;
                        property: "rotation";
                    }
                }
            ]
        }
    }

    Row {
        id: row1;
         anchors.left: opener.right;
        
        Item {
            width: {
                if (isFolder) {
                    return sidebarFeedList.width - height;
                } else if (parentFolder > -1) {
                    return sidebarFeedList.width - folderIndent;
                } else {
                    return sidebarFeedList.width;
                }
            }
            height: feedTitleDelegate.height;
            
            Rectangle {
                id: rowBackground;
                
                color: index == feedListView.currentIndex ? 
                           style.color.sidebarSelected : "transparent";

                anchors.fill: parent;
                anchors.topMargin: style.defaultMarin;
                anchors.leftMargin: 0;
                anchors.rightMargin: 0;
                
                Item {
                    id: feedIconCol
                    
                    // No icon for all news or folders.
                    width: isSpecialFeed || isFolder ? 0 : (35 * style.scale);
                    visible: !(isSpecialFeed || isFolder);
                    
                    anchors.left: parent.left;
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    anchors.leftMargin: 10 * style.scale;

                    Item {
                        id: feedIconContainer;

                        anchors.verticalCenter: parent.verticalCenter;

                        width: 24 * style.scale;
                        height: 24 * style.scale;

                        opacity: 1;

                        Image {
                            id: feedIcon;

                            source: imageURL;

                            // Only display when there is something loaded.
                            visible: status === Image.Ready;

                            anchors.fill: parent;
                            asynchronous: true;
                        }

                        Image {
                            id: defaultFeedIcon;

                            visible: !feedIcon.visible;

                            source: (fangSettings.currentStyle === "LIGHT" ? "images/symbol_rss.svg"
                                                            : "images/symbol_dark_rss.svg");

                            anchors.fill: parent;
                            asynchronous: true;
                        }

                        Image {
                            id: errorIcon;

                            visible: errorFlag;

                            source: (fangSettings.currentStyle === "LIGHT" ? "images/symbol_warning.svg"
                                                                           : "images/symbol_dark_warning.svg");
                            width: parent.width * 0.75;
                            height: width;
                            anchors.right: parent.right;
                            anchors.bottom: parent.bottom
                            anchors.margins: -parent.width * 0.25;
                        }

                        property bool updating: isUpdating;
                        onUpdatingChanged: {
                            if (updating) {
                                iconFadeOut.restart();
                            } else {
                                iconFadeIn.restart();
                            }
                        }

                        OpacityAnimator {
                            id: iconFadeIn;

                            target: feedIconContainer;
                            from: 0;
                            to: 1;
                            duration: 300;
                            easing.type: Easing.InQuad;
                        }

                        OpacityAnimator {
                            id: iconFadeOut;

                            target: feedIconContainer;
                            from: 1;
                            to: 0;
                            duration: 300;
                            easing.type: Easing.OutQuad;
                        }
                    }
                    
                    FangIcon {
                        id: feedBusySpinner;
                        
                        state: "spinner";
                        visible: true;
                        opacity: 0;
                        
                        anchors.verticalCenter: parent.verticalCenter;
                        
                        width: 23 * style.scale;
                        height: 23 * style.scale;

                        property bool updating: isUpdating;
                        onUpdatingChanged: {
                            if (updating) {
                                spinnerFadeIn.restart();
                            } else {
                                spinnerFadeOut.restart();
                            }
                        }

                        OpacityAnimator {
                            id: spinnerFadeIn;

                            target: feedBusySpinner;
                            from: 0;
                            to: 1;
                            duration: 300;
                            easing.type: Easing.InQuad;
                        }

                        OpacityAnimator {
                            id: spinnerFadeOut;

                            target: feedBusySpinner;
                            from: 1;
                            to: 0;
                            duration: 300;
                            easing.type: Easing.OutQuad;
                        }
                    }
                }
                
                Item {
                    id: feedTitleCol;

                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    anchors.left: feedIconCol.right;
                    anchors.right: feedCountCol.left;

                    anchors.rightMargin: 4 * style.scale;
                    anchors.bottomMargin: style.defaultMargin;
                    anchors.topMargin: style.defaultMargin;
                    anchors.leftMargin: 0;

                    // Feed title.
                    Text {
                        id: feedTitle;

                        visible: !isSearchFeed;
                        text: title;

                        width: parent.width;
                        anchors.verticalCenter: parent.verticalCenter;

                        font: unreadCount > 0 ?
                                  style.font.standardBold : style.font.standard;
                        color: style.color.sidebarSelectedText;

                        elide: Text.ElideRight;
                    }

                    // Search box.
                    Row {
                        id: searchInputRow;
                        visible: isSearchFeed;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: parent.left;
                        anchors.right: parent.right;
                        spacing: 4 * style.scale;

                        // Search icon
                        Image {
                            id: searchIcon;
                            source: fangSettings.currentStyle === "LIGHT"
                                    ? "images/symbol_search.svg"
                                    : "images/symbol_dark_search.svg";
                            width: 16 * style.scale;
                            height: 16 * style.scale;
                            anchors.verticalCenter: parent.verticalCenter;
                            sourceSize.width: width;
                            sourceSize.height: height;
                        }

                        // Search text input.
                        Rectangle {
                            id: searchInputBg;
                            width: parent.width - searchIcon.width - parent.spacing;
                            height: 24 * style.scale;
                            anchors.verticalCenter: parent.verticalCenter;
                            color: style.color.textEntryBackground;
                            border.color: style.color.textEntryBorder;
                            border.width: 2 * style.scale;
                            radius: style.defaultRadius;

                            TextInput {
                                id: searchInput;
                                anchors.fill: parent;
                                anchors.margins: 4 * style.scale;
                                verticalAlignment: TextInput.AlignVCenter;
                                font: style.font.standard;
                                color: style.color.textEntryText;
                                selectByMouse: true;
                                clip: true;

                                // Placeholder text
                                Text {
                                    anchors.fill: parent;
                                    verticalAlignment: Text.AlignVCenter;
                                    text: "Search news...";
                                    color: style.color.textEntryHint;
                                    font: style.font.standard;
                                    visible: !searchInput.text && !searchInput.activeFocus;
                                }

                                // Focus when search feed becomes selected
                                Component.onCompleted: {
                                    if (isSearchFeed && feedListView.currentIndex === index) {
                                        forceActiveFocus();
                                    }
                                }

                                // Watch for when this item becomes selected
                                Connections {
                                    target: feedListView;
                                    function onCurrentIndexChanged() {
                                        if (isSearchFeed && feedListView.currentIndex === index) {
                                            searchInput.forceActiveFocus();
                                        }
                                    }
                                }

                                Keys.onReturnPressed: {
                                    if (text.trim() !== "") {
                                        feedTitleDelegate.searchRequested(text.trim());
                                    }
                                }

                                Keys.onEnterPressed: {
                                    if (text.trim() !== "") {
                                        feedTitleDelegate.searchRequested(text.trim());
                                    }
                                }

                                Keys.onEscapePressed: {
                                    text = "";
                                    feedTitleDelegate.searchCleared();
                                }
                            }
                        }
                    }

                }
                
                Item {
                    id: feedCountCol;

                    // Hide for search feed
                    visible: !isSearchFeed;

                    states: [
                        State { name: "allread"; },
                        State { name: "unread"; }
                    ]

                    state: unreadCount > 0 ? "unread" : "allread";

                    Component.onCompleted: {
                        // Set initial opacity.
                        opacity = unreadCount == 0 ? 0.0 : 1.0;
                    }

                    transitions: [
                        Transition {
                            from: "unread";
                            to: "allread";
                            NumberAnimation {
                                target: feedCountCol;
                                properties: "opacity";
                                from: 1.0;
                                to: 0.0;
                                duration: 500;
                                easing.type: Easing.InOutQuad;
                            }
                        },

                        Transition {
                            from: "allread";
                            to: "unread";
                            NumberAnimation {
                                target: feedCountCol;
                                properties: "opacity";
                                from: 0.0;
                                to: 1.0;
                                duration: 500;
                                easing.type: Easing.InOutQuad;
                            }
                        }
                    ]

                    anchors.right: parent.right;
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    anchors.rightMargin: 7 + scrollView.effectiveScrollBarWidth;
                    Behavior on anchors.rightMargin { PropertyAnimation {
                            easing.type: Easing.InOutQuad;
                            duration: 250;
                        }
                    }

                    width: childrenRect.width;
                    height: parent.height;

                    Rectangle {
                        color: style.color.badge;

                        width: unreadCountText.paintedWidth + 6;
                        height: unreadCountText.paintedHeight + 4;
                        anchors.verticalCenter: parent.verticalCenter;
                        radius: style.defaultRadius;

                        Text {
                            id: unreadCountText;

                            text: unreadCount;

                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter;
                            font: style.font.unreadCount;
                            elide: Text.ElideRight;
                            color: style.color.badgeText;
                        }
                    }
                }

                // Search clear button.
                Item {
                    id: searchClearCol;

                    visible: isSearchFeed && searchInput.text !== "";

                    anchors.right: parent.right;
                    // anchors.top: parent.top;
                    // anchors.bottom: parent.bottom;
                    anchors.verticalCenter: parent.verticalCenter;
                    //anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.rightMargin: 7 + scrollView.effectiveScrollBarWidth;

                    width: 20 * style.scale;
                    height: parent.height;

                    Rectangle {
                        id: clearSearchButton;
                        width: 20 * style.scale;
                        height: 20 * style.scale;
                        anchors.verticalCenter: parent.verticalCenter;
                        color: "transparent";

                        Image {
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.right: parent.right;
                            width: 12 * style.scale;
                            height: 12 * style.scale;
                            source: fangSettings.currentStyle === "LIGHT"
                                    ? "images/symbol_close.svg"
                                    : "images/symbol_dark_close.svg";
                            sourceSize.width: width;
                            sourceSize.height: height;

                            MouseArea {
                                anchors.fill: parent;
                                onClicked: {
                                    searchInput.text = "";
                                    searchInput.forceActiveFocus();
                                }
                            }
                        }

                    }
                }
            }
        }

        spacing: 10 * style.scale;
    }
}
