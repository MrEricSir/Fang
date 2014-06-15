import QtQuick 2.0
import Fang 1.0

// The dialog for adding a feed!
Dialog {
    id: addDialog
    
    title: "Add a Feed"
    
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
    
    DialogText {
        text: "What site would you like to add?"
    }
    
    TextEntry {
        id: textURL
        
        placeholderText: "Website or feed URL"
        
        onTextChanged: validationStatus.visible = false
        onAccepted: addButton.click()
        
        width: parent.width
        
        // Don't allow editing while we're checking the feed.
        readOnly: validator.validating
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
        enabled: textURL.text && !validator.validating && !validator.validationComplete
    }
    
    DialogButton {
        id: cancelButton
        
        text: "Cancel"
        onClicked: close()
        enabled: !validator.validationComplete
    }
    
    // Magic beans that validate & add feeds (see C++ layer.)
    FeedValidator {
        id: validator
        url: textURL.text
        
        property bool validationComplete: false
        
        onValidationComplete: {
            if (!result) {
                // Uh oh, an error.
                validationStatus.state = "error";
                validationStatus.text = errorString;
                validationStatus.visible = true;
            } else {
                // We validated!
                validationStatus.state = "ok";
                validationStatus.text = "Success!";
                validationStatus.visible = true;
                
                // Signal completion.
                validationComplete = true;
                
                // Add the feed!
                addFeed();
                
                // Go into final phase!
                dismiss();
            }
        }
    }
}
