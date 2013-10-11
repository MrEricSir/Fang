import QtQuick 1.1
import Fang 1.0

// Edit a feed.
Dialog {
    id: editDialog
    
    property variant listView
    
    onStateChanged: {
        if (state == "open") {
            reset();
        }
    }
    
    function reset() {
        feedTitle.setEditText(listView.model.selected.getTitle());
    }

    DialogStatus {
        id: validationStatus
        
        state: "help"
        text: "Edit a feed"
        
        width: parent.width
    }
    
    TextEntry {
        id: feedTitle
        
        hint: "Feed title"
        
        onEnterPressed: saveEditButton.click()
        width: parent.width
    }
    
    DialogButton {
        id: saveEditButton
        
        text: "Save"
        onClicked: {
            // Save the new title.
            listView.model.selected.setTitle(feedTitle.editText);
            
            // Dismiss the dialog.
            dismiss();
        }
        enabled: !isClosing && feedTitle.editText.trim() !== ""
        
        width: parent.width
        
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
        
        width: parent.width
    }
}
