import QtQuick
import Fang 1.0

// Psst hey kid, you wanna remove a feed?
Dialog {
    id: removeDialog;
    
    title: "Remove a Feed";
    
    property var feed;
    
    DialogStatus {
        id: validationStatus;
        
        state: "help";
        text: "Are you sure you want to remove this feed?";
    }
    
    DialogButton {
        id: removeButton;
        
        text: "Remove Feed";
        onClicked: {
            // Remove a specific feed.
            //console.log("Feed to remove: ", feed)
            validator.removeFeed(feed);
            
            // Dismiss the dialog.
            dismiss();
        }
        enabled: !isClosing;
        
        // Yes this is cheating, but so what?
        FeedValidator {
            id: validator;
        }
    }
    
    onDialogClosed: {
        validator.destroy();
    }
    
    DialogButton {
        id: cancelButton;
        
        text: "Cancel";
        onClicked: close();
        enabled: !isClosing;
    }
}
