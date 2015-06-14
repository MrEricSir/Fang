import QtQuick 2.4
import Fang 1.0

// Psst hey kid, you wanna remove a feed?
Dialog {
    id: removeDialog
    
    title: "Remove a Feed"
    
    property var listView;
    
    DialogStatus {
        id: validationStatus
        
        state: "help"
        text: "Are you sure you want to delete this feed?"
    }
    
    DialogButton {
        id: removeButton
        
        text: "Remove Feed"
        onClicked: {
            // Remove the selected item.
            //console.log("current index ", listView.model.selected)
            validator.removeFeed(listView.model.selected);
            
            // Dismiss the dialog.
            dismiss();
        }
        enabled: !isClosing
        
        // Yes this is cheating, but so what?
        FeedValidator {
            id: validator
        }
    }
    
    onDialogClosed: {
        validator.destroy();
    }
    
    DialogButton {
        id: cancelButton
        
        text: "Cancel"
        onClicked: close()
        enabled: !isClosing
    }
}
