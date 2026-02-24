import QtQuick
import Fang 1.0

// Edit a feed.
Dialog {
    id: editDialog;
    
    title: "Edit a Feed";

    onDialogOpened: {
        feedTitle.forceActiveFocus();
        feedTitle.text = feed.getTitle();
        feedURL.text = feed.getURL();
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
    
    DialogGroup {
        width: parent.width;

        DialogButton {
            id: saveEditButton;

            isPrimary: true;
            text: "Save";
            onClicked: {
                // Save the new title.
                feed.setTitle(feedTitle.text);

                // Dismiss the dialog.
                dismiss();
            }
            enabled: !isClosing && feedTitle.text.trim() !== "";
        }

        DialogButton {
            id: cancelButton;

            text: "Cancel";
            onClicked: close();
            enabled: !isClosing;
        }
    }
}
