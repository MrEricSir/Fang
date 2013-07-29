import QtQuick 1.1

// A text entry box.
Rectangle {
    id: textEntry
    
    // Font size.
    property int fontSize: 11
    
    // The grayed-out "hint" text.
    property string hint: ""
    
    function setEditText(editText) {
        edit.text = editText;
    }
    
    function getEditText() {
        return edit.text;
    }
    
    signal editTextChanged(string text)
    
    color: "#eee"
    height: textEntryContainer.height + 12
    
    Rectangle {
        id: textEntryContainer
        
        color: "white"
        width: parent.width - 12
        height: textEntryContainerInnerMargin.height + 12
        
        anchors.centerIn: parent
        
        Rectangle {
            id: textEntryContainerInnerMargin
            
            width: parent.width - 12
            height: Math.max(hintText.paintedHeight, edit.paintedHeight)
            
            anchors.centerIn: parent
            
            // The default "hint" text
            Text {
                id: hintText
                
                width: parent.width
                
                text: hint
                
                visible: edit.text == "" && !edit.activeFocus
                
                color: "#ccc"
                font.italic: true
                font.family: "Tahoma"
                font.pointSize: textEntry.fontSize
            }
            
            // Editable field
            TextEdit {
                id: edit
                
                width: parent.width
                
                text: ""
                
                textFormat: TextEdit.PlainText
                
                color: "black"
                font.family: "Tahoma"
                font.pointSize: textEntry.fontSize
                
                onTextChanged: {
                    // 1337 HAX to prevent newlines in text field.
                    if (text.indexOf('\n') != -1 || text.indexOf('\r') != -1) {
                        text = text.replace("\n", "");
                        text = text.replace("\r", "");
                    }
                    
                    editTextChanged(text);
                }
            }
        }
    }
}
