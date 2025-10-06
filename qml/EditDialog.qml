import QtQuick
import Fang 1.0

// Edit a feed.
Dialog {
    id: editDialog;
    
    title: "Edit a Feed";

    onDialogOpened: {
        feedTitle.forceActiveFocus();
        feedTitle.text = listView.model.selected.getTitle();
        feedURL.text = listView.model.selected.getURL();
    }

    DialogStatus {
        id: validationStatus;
        
        state: "help";
        text: "Edit a feed";
    }
    
    TextEntry {
        id: feedTitle;
        
        placeholderText: "Feed title";
        
        onAccepted: saveEditButton.click();
        width: parent.width;
    }

    DialogText {
        id: feedURL;
        textColor: style.color.fadedText;

        width: parent.width;
    }
    
    DialogButton {
        id: saveEditButton;
        
        text: "Save";
        onClicked: {
            // Save the new title.
            listView.model.selected.setTitle(feedTitle.text);
            
            // Dismiss the dialog.
            dismiss();
        }
        enabled: !isClosing && feedTitle.text.trim() !== "";
        
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
