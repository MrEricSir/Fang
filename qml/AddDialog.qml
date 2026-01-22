import QtQuick
import Fang 1.0

// The dialog for adding a feed!
Dialog {
    id: addDialog;
    
    title: "Add a Feed";
    
    onDialogOpened: {
        textURL.forceActiveFocus();
    }
    
    state: "start";
    states: [
        State { name: "start" },
        State { name: "validating" },
        State { name: "add" }
    ]
    
    //onStateChanged: console.log("State is now: ", state)
    
    DialogText {
        text: "What site would you like to add?";
    }
    
    TextEntry {
        id: textURL;
        
        placeholderText: "Website or feed URL";
        
        onTextChanged: validationStatus.visible = false;
        onAccepted: {
            if (continueButton.visible) {
                continueButton.click();
            } else if (addButton.visible) {
                addButton.clicked();
            } else
                console.warn("Accepted enter key but neither continue nor add button visible");
        }
        
        width: parent.width;
        
        // Don't allow editing while we're checking the feed.
        readOnly: addDialog.state === "validating" || addDialog.state === "add";
    }
    
    // Feed(s) discovered.
    Column {
        id: multipleFeedsColumn;

        visible: addDialog.state === "add";
        width: parent.width;
        spacing: 8;

        Repeater {
            model: validator.discoveredFeeds;

            Item {
                width: parent.width;
                height: 32;

                Row {
                    anchors.fill: parent;
                    spacing: 8;
                    // Required due to weird Repeater delegate scoping.
                    property var _validator: validator;

                    CheckBox {
                        width: height;
                        height: 32;
                        checked: modelData.selected;
                        visible: parent._validator.feedCount > 1;

                        onUserChecked: (checked) => {
                            parent._validator.setFeedSelected(modelData.index, checked);
                        }
                    }

                    TextEntry {
                        width: parent.width - parent.children[0].width - parent.spacing;
                        height: 32;
                        text: modelData.title;

                        onTextChanged: () => {
                            parent._validator.setFeedTitle(modelData.index, text);

                            // If set programatically, reset cursor to the left.
                            if (!focus) {
                                cursorPosition = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    DialogStatus {
        id: validationStatus;
        
        text: "";
        visible: false;
        state: "spinner";
        
        width: parent.width;
    }
    
    DialogGroup {
        width: parent.width;

        DialogButton {
            id: continueButton;

            text: "Continue";
            onClicked: {
                validator.check();
                addDialog.state = "validating";
                validationStatus.state = "spinner";
                validationStatus.text = "Checking feed...";
                validationStatus.visible = true;
            }
            visible: addDialog.state !== "add";
            enabled: textURL.text && addDialog.state !== "validating";
        }

        DialogButton {
            id: addButton;

            text: validator.feedCount > 1 ? "Add Selected Feeds" : "Add Feed";
            onClicked: {
                validator.addFeeds();
                addDialog.dismiss();
            }
            visible: addDialog.state === "add";
            enabled: validator.feedsToAddCount > 0;
        }
    }
    
    DialogGroup {
        width: parent.width;

        DialogButton {
            id: cancelButton;

            text: "Cancel";
            onClicked: close();
        }
    }

    onDialogClosed: {
        validator.destroy();
    }
    
    // Magic beans that validate & add feeds (see C++ layer.)
    FeedValidator {
        id: validator;
        url: textURL.text;
        
        property bool validationComplete: false;
        
        onValidationComplete: (result, errorString) => {
            if (!result) {
                // Uh oh, an error.
                validationStatus.state = "error";
                validationStatus.text = errorString;
                validationStatus.visible = true;
                
                // Main state.
                addDialog.state = "start";
            } else {
                // We validated!
                validationStatus.state = "ok";
                validationStatus.text = "Success!";
                validationStatus.visible = true;
                
                // Signal completion.
                validationComplete = true;
                
                addDialog.state = "add";
            }
        }
    }
}
