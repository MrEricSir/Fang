import QtQuick 2.2
import Fang 1.0


// OPML import dialog
Dialog {
    id: opmlImportDialog;
    
    // Ready for the parent (SettingsDialog) to close NOW
    signal parentClose();

    // Set by SettingsDialog
    property OPMLInteractor interactor;
    
    // Read-only.
    property bool iAmOpen: false;
    property bool addOnClose: false;
    
    onDialogOpened: {
        iAmOpen = true;
        if (interactor === null)
            return;
        
        doStart();
    }
    
    onDialogClosed: {
        if (interactor && addOnClose)
            interactor.addSelected();
    }

    onInteractorChanged: {
        if (interactor && iAmOpen) {
            doStart();
        }
    }
    
    // We're ready to start the import!
    function doStart() {
        // Hook up signals.
        interactor.onImportInProgressChanged.connect(onImportFinished);
        interactor.onValidationInProgressChanged.connect(onValidationFinished);
        interactor.onIsAnyFeedSelectedChanged.connect(onAnyFeedSelectedChanged);
        
        // Start!
        interactor.importStart();
    }

    title: "Import Feed List";

    // Importing and parsing the OPML file is complete.
    function onImportFinished() {
        if (interactor.importInProgress)
            return;

        console.log("On import finished!");
        var importString = interactor.importError;

        if (importString === "") {
            validationStatus.text = "Checking " + importRepeater.count + " feeds...";
        } else {
            validationStatus.text = importString;
            validationStatus.state = "error";
        }
    }
    
    // Batch feed validation is complete.
    function onValidationFinished() {
        if (interactor.validationInProgress || interactor.importInProgress)
            return;
        
        validationStatus.text = "Complete";
        validationStatus.state = "ok";
        
        if (interactor.isAnyFeedSelected)
            addButton.visible = true;
    }
    
    // Only show add button when we have feeds selected.
    function onAnyFeedSelectedChanged() {
        if (interactor.validationInProgress || interactor.importInProgress)
            return;
        
        addButton.visible = interactor.isAnyFeedSelected;
    }
    
    DialogStatus {
        id: validationStatus;

        text: "Importing...";
        state: "spinner";

        width: parent.width;
    }

    DialogSpacer {
    }

    Column {
        width: parent.width;

        Repeater {
            id: importRepeater;

            model: importListModel; // Defined in FangApp

            delegate: Item {
                id: importDelegate;

                Style {
                    id: style;
                }

                width: parent.width;
                height: importDelegate.childrenRect.height;

                Column {
                    Item {
                        width: parent.width;
                        height: index === 0 ? 0 : 12;
                    }

                    Row {
                        Item {
                            id: checkbox;
                            
                            width: feedCheckBox.width * 1.32;
                            height: parent.height;
                            
                            CheckBox {
                                id: feedCheckBox;
                                
                                enabled: true;
                                
                                checked: isSelected;
                                
                                onUserChecked: {
                                    isSelected = checked;
                                }
                                
                                y: (parent.height - height) / 2; // center
                                
                                width: importTitle.height;
                                height: importTitle.height;
                            }
                        }
                        
                        Column {
                            id: infoCol;

                            Text {
                                id: importTitle;

                                text: title;

                                font.pointSize: style.font.defaultSize;
                                font.family: style.font.defaultFamily;
                                color: style.color.dialogText;

                                elide: Text.ElideRight;
                                renderType: Text.NativeRendering;
                            }

                            Text {
                                id: importURL;

                                text: url;

                                font.pointSize: style.font.defaultSize;
                                font.family: style.font.defaultFamily;
                                font.italic: true; // It's a-me! Mario!
                                color: style.color.fadedText;

                                elide: Text.ElideRight;
                                renderType: Text.NativeRendering;
                            }
                        }
                        
                        Item {
                            id: rowSpacer;
                            
                            width: importDelegate.width -
                                   (checkbox.width + spinnerContainer.width + infoCol.width);
                            height: parent.height;
                        }
                        
                        Item {
                            id: spinnerContainer;
                            
                            width: spinnerImage.width * 1.32;
                            height: parent.height;

                            FangIcon {
                                id: spinnerImage;
                                state: "spinners";

                                y: (parent.height - width) / 2; // center
                                width: importTitle.height;
                                
                                visible: isUpdating;
                            }
                        }
                    }
                }
            }
        }
    }
    
    DialogSpacer {
    }

    DialogButton {
        id: addButton

        text: "Add Selected"
        onClicked: {
            parentClose();
            addOnClose = true; // <-- this auto-adds the new feeds on close
            close();
        }

        enabled: true
        
        visible: false // at first
    }
    
    DialogButton {
        id: cancelButton

        text: "Cancel"
        onClicked: close()
        enabled: true
    }
}
