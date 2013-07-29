import QtQuick 1.1
import Fang 1.0

// The dialog for adding a feed!
Dialog {
    id: addDialog
    
    onStateChanged: {
        if (state == "open") {
            // Clear everything.
            reset();
        }
    }
    
    function reset() {
        textURL.setEditText("");
        validator.validationComplete = false;
        validationStatus.visible = false;
    }
    
    Item {
        id: container
        
        width: 400
        anchors.horizontalCenter: parent.horizontalCenter
        
        Column {
            width: parent.width
            spacing: 10
            
            DialogText {
                text: "What site would you like to add?"
                width: parent.width
            }
            
            TextEntry {
                id: textURL
                
                hint: "Website or feed URL"
                
                onEditTextChanged: validationStatus.visible = false
                
                width: parent.width
            }
            
            DialogSpinner {
                id: validationSpinner
                
                text: "Checking feed..."
                visible: validator.validating
                
                onVisibleChanged: {
                    // If we're spinning, kill status.
                    if (visible)
                        validationStatus.visible = false;
                }
                
                width: parent.width
            }
            
            DialogStatus {
                id: validationStatus
                
                text: ""
                visible: false
                
                width: parent.width
            }
            
            DialogButton {
                id: addButton
                
                text: "Add Feed"
                onClicked: validator.check()
                enabled: !validator.validating && !validator.validationComplete
                
                width: parent.width
            }
            
            DialogButton {
                id: cancelButton
                
                text: "Cancel"
                onClicked: close()
                enabled: !validator.validationComplete
                
                width: parent.width
            }
        
        }
    }
    
    FeedValidator {
        id: validator
        url: textURL.getEditText()
        
        property bool validationComplete: false
        
        onValidationComplete: {
            console.log("Validation complete for url:", url)
            console.log("Result? ", result)
            console.log("Error? ", errorString)
            console.log("Title? ", siteTitle)
            
            if (!result) {
                validationStatus.state = "error";
                validationStatus.text = errorString;
                validationStatus.visible = true;
            }
            
            if (result) {
                validationStatus.state = "ok";
                validationStatus.text = "Success!";
                validationStatus.visible = true;
                
                // Signal completion.
                validationComplete = true;
                
                // Go into final phase!
                dismissTimer.restart();
            }
        }
        
        // Timer so we give the user a glimpse of our "success" message before closing
        // the dialog.
        Timer {
            id: dismissTimer
            interval: 700
            running: false
            repeat: false
            
            onTriggered: addDialog.close()
        }
    }
}
