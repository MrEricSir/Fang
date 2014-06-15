import QtQuick 2.0
import Fang 1.0

// Edit a feed.
Dialog {
    id: editDialog
    
    title: "Edit a Feed"
    
    property variant listView
    
    onDialogOpened: {
        reset();
    }
    
    function reset() {
        feedTitle.text = listView.model.selected.getTitle();
    }

    DialogStatus {
        id: validationStatus
        
        state: "help"
        text: "Edit a feed"
    }
    
    TextEntry {
        id: feedTitle
        
        placeholderText: "Feed title"
        
        onAccepted: saveEditButton.click()
        width: parent.width
    }
    
    DialogButton {
        id: saveEditButton
        
        text: "Save"
        onClicked: {
            // Save the new title.
            listView.model.selected.setTitle(feedTitle.text);
            
            // Dismiss the dialog.
            dismiss();
        }
        enabled: !isClosing && feedTitle.text.trim() !== ""
        
        // Yes this is cheating, but so what?
        FeedValidator {
            id: validator
        }
    }
    
    DialogButton {
        id: cancelButton
        
        text: "Cancel"
        onClicked: close()
        enabled: !isClosing
    }
}
