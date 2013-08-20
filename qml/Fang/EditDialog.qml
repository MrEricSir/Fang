import QtQuick 1.1
import Fang 1.0

// Edit a feed.
Dialog {
    id: editDialog
    
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
                text: "Edit a feed"
                
                width: parent.width
            }
            
            TextEntry {
                id: feedTitle
                
                hint: "Feed title"
                
                onEnterPressed: saveButton.click()
                
                width: parent.width
            }
            
            DialogButton {
                id: saveButton
                
                text: "Save"
                onClicked: {
                    // TODO actually save.
                    
                    // Dismiss the dialog.
                    dismissTimer.restart();
                }
                enabled: !dismissTimer.running && feedTitle.editText !== ""
                
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
                enabled: !dismissTimer.running
                
                width: parent.width
            }
        
        }
        
        // Timer so we give the user a glimpse of our "success" message before closing
        // the dialog.
        Timer {
            id: dismissTimer
            
            interval: 700
            running: false
            repeat: false
            
            onTriggered: removeDialog.close()
        }
    }
}
