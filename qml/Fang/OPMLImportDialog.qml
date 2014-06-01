import QtQuick 2.0
import Fang 1.0

// OPML import dialog

Dialog {
    id: opmlImportDialog
    
    // The settings dialog must set this after creating the dialog
    function setInteractor(interator) {
        opmlImportDialog.interactor = interactor;
        interactor.onImportFinished.connect(onImportFinished);
    }
    
    function onImportFinished() {
        console.log("On import finished!");
        var importString = interactor.importError;
        if (importString === "") {
            validationSpinner.visible = false;
            
            validationStatus.text = "Success!";
            validationStatus.state = "error";
            validationStatus.visible = true;
        } else {
            validationSpinner.visible = false;
            
            validationStatus.text = importString;
            validationStatus.state = "ok";
            validationStatus.visible = true;
        }
    }
    
    // Private!!  Use setInteractor() instead.
    property OPMLInteractor interactor
    
    title: "Import Feed List"
    
    DialogSpinner {
        id: validationSpinner
        
        text: "Verifying feed URLs, please wait..."
        //visible: validator.validating
        
        width: parent.width
    }
    
    DialogStatus {
        id: validationStatus
        
        text: ""
        visible: false
        
        width: parent.width
    }
    
    DialogButton {
        id: cancelButton
        
        text: "Cancel"
        onClicked: close()
        enabled: true
    }
}
