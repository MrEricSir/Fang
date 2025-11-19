import QtQuick

DialogButton {
    id: dialogRadioButton;

    // Fired only when the button is toggled, but not un-toggled.
    signal isToggled;

    // Read-only.
    isToggleable: true;
    
    onToggledChanged: {
        if (toggled) {
            isToggled();
        }
    }
}
