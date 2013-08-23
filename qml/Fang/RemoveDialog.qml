import QtQuick 1.1
import Fang 1.0

// Psst hey kid, you wanna remove a feed?
Dialog {
    id: removeDialog
    
    property variant listView
    
    Item {
        id: container
        
        width: 400
        anchors.horizontalCenter: parent.horizontalCenter
        
        Column {
            width: parent.width
            spacing: 10
            
            DialogStatus {
                id: validationStatus
                
                state: "help"
                text: "Are you sure you want to delete this feed?"
                
                width: parent.width
            }
            
            DialogButton {
                id: removeButton
                
                text: "Remove Feed"
                onClicked: {
                    // Remove the selected item.
                    //console.log("current index ", listView.currentIndex)
                    console.log("does this exist");
                    validator.removeFeed(listView.model.selected);
                    
                    // Dismiss the dialog.
                    dismiss();
                }
                enabled: !isClosing
                
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
    }
}
