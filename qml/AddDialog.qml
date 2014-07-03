import QtQuick 2.0
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
    
    onStateChanged: console.log("State is now: ", state)
    
    DialogText {
        text: "What site would you like to add?";
    }
    
    TextEntry {
        id: textURL;
        
        placeholderText: "Website or feed URL";
        
        onTextChanged: validationStatus.visible = false;
        onAccepted: continueButton.click();
        
        width: parent.width;
        
        // Don't allow editing while we're checking the feed.
        readOnly: addDialog.state === "validating" || addDialog.state === "add"
    }
    
    TextEntry {
        id: textSiteTitle;
        
        placeholderText: "Feed name";
        
        onAccepted: addButton.click();
        
        visible: addDialog.state === "add"
        
        width: parent.width;
    }
    
    DialogStatus {
        id: validationStatus;
        
        text: "";
        visible: false;
        
        width: parent.width;
    }
    
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
        
        text: "Add Feed";
        onClicked: {
            // Set the title.
            validator.siteTitle = textSiteTitle.text;
            textSiteTitle.readOnly = true;
            
            // Add the feed and dismiss.
            validator.addFeed();
            addDialog.dismiss();
        }
        visible: addDialog.state === "add";
        enabled: textSiteTitle.text; 
    }
    
    DialogButton {
        id: cancelButton;
        
        text: "Cancel";
        onClicked: close();
    }
    
    onDialogClosed: {
        validator.destroy();
    }
    
    // Magic beans that validate & add feeds (see C++ layer.)
    FeedValidator {
        id: validator;
        url: textURL.text;
        
        property bool validationComplete: false;
        
        onValidationComplete: {
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
                
                textSiteTitle.text = validator.siteTitle;
                
                // Signal completion.
                validationComplete = true;
                
                addDialog.state = "add";
            }
        }
    }
}
