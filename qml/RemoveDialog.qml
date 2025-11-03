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
            newsFeedInteractor.removeFeed(feed);
            
            // Dismiss the dialog.
            dismiss();
        }
        enabled: !isClosing;
        
        // The "interactor" is what talks to the C++ layer.
        NewsFeedInteractor {
            id: newsFeedInteractor;
        }
    }
    
    DialogButton {
        id: cancelButton;
        
        text: "Cancel";
        onClicked: close();
        enabled: !isClosing;
    }
}
