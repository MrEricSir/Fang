import QtQuick
import QtQuick.Effects
import RearrangeableTreeView

RearrangeableDelegate {
    id: feedTitleDelegate;

    Style {
        id: style;
    }

    signal jumpToBookmark();

    onClicked: (mouse) => {
        if (mouse.button === Qt.LeftButton) {
            if (isFolder && opener.width > 0 && mouse.x < titleDelegate.x + opener.width) {
               toggleFolder();
            } else {
               feedListView.currentIndex = index;
            }
        }
    }

    onDoubleClicked: (mouse) => {
        if (feedListView.currentIndex == index) {
            feedTitleDelegate.jumpToBookmark();
        }
    }

    dragEnabled: !isSpecialFeed;

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
                    return feedTitleDelegate.width - height;
                } else if (parentFolder > -1) {
                    return feedTitleDelegate.width - folderIndent;
                } else {
                    return feedTitleDelegate.width;
                }
            }
            height: feedTitleDelegate.height;

            Rectangle {
                id: rowBackground;

                color: index == feedListView.currentIndex ?
                           style.color.sidebarSelected : "transparent";
                radius: style.defaultRadius;

                anchors.fill: parent;
                anchors.topMargin: style.defaultMarin;
                anchors.leftMargin: style.defaultMarin;
                anchors.rightMargin: style.defaultMarin + (rectangle2.contentOverflows ? sidebarScrollBar.width : 0);
                Behavior on anchors.rightMargin {
                    PropertyAnimation {
                        easing.type: Easing.InOutQuad;
                        duration: 250;
                    }
                }

                Item {
                    id: feedIconCol

                    // No icon for all news or folders, but search feed gets the search icon.
                    width: (isSpecialFeed && !isSearchFeed) || isFolder ? 0 : (35 * style.scale);
                    visible: !((isSpecialFeed && !isSearchFeed) || isFolder);

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

                        // Mask shape for rounded icon corners.
                        Rectangle {
                            id: iconMask;
                            anchors.fill: parent;
                            radius: 5 * style.scale;
                            layer.enabled: true;
                            //visible: false;
                            color: style.color.sidebar;
                        }

                        // Feed icon with rounded corners (iOS-style).
                        Image {
                            id: feedIcon;

                            source: imageURL;
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

                        Image {
                            id: defaultFeedIcon;

                            visible: !feedIcon.visible;

                            source: isSearchFeed
                                    ? (fangSettings.currentStyle === "LIGHT" ? "images/symbol_search.svg"
                                                                             : "images/symbol_dark_search.svg")
                                    : (fangSettings.currentStyle === "LIGHT" ? "images/symbol_rss.svg"
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

                        text: title;

                        width: parent.width;
                        anchors.verticalCenter: parent.verticalCenter;

                        font: style.font.standard;
                        color: index == feedListView.currentIndex ?
                                   style.color.sidebarSelectedText : style.color.sidebarText;

                        elide: Text.ElideRight;
                    }

                }

                Item {
                    id: feedCountCol;

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
                    anchors.rightMargin: 7;

                    width: childrenRect.width;
                    height: parent.height;

                    Rectangle {
                        color: style.color.badge;

                        width: Math.max(unreadCountText.paintedWidth + 8, height);
                        height: unreadCountText.paintedHeight + 4;
                        anchors.verticalCenter: parent.verticalCenter;
                        radius: height / 2;

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
            }
        }

        spacing: 10 * style.scale;
    }
}
