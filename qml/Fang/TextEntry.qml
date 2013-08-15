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
    
    // Signaled on every text change.
    signal editTextChanged(string text)
    
    // Signaled when user hits enter/return.
    signal enterPressed()
    
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
            
            // Allow text to scroll.
            // Based on: http://qt-project.org/wiki/Flickable_Wrapped_TextEdit
            // Also note the onCursorRectangleChanged() signal in the editable field.
            Flickable {
                id: flick
                
                width: parent.width - 5
                height: edit.height
                
                clip: true
                flickableDirection: Flickable.VerticalFlick
                
                contentWidth: edit.width
                contentHeight: edit.height
                
                function ensureVisible(r) {
                    if (contentX >= r.x)
                        contentX = r.x;
                    else if (contentX + width <= r.x + r.width)
                        contentX = r.x + r.width - width;
                }
                
                // Editable field
                TextEdit {
                    id: edit
                    
                    text: ""
                    
                    textFormat: TextEdit.PlainText
                    
                    color: "black"
                    font.family: "Tahoma"
                    font.pointSize: textEntry.fontSize
                    focus: true
                    wrapMode: TextEdit.NoWrap
                    
                    // Used with the above flickable.
                    onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                    
                    onTextChanged: {
                        // 1337 HAX to prevent newlines in text field.
                        if (text.indexOf('\n') != -1 || text.indexOf('\r') != -1) {
                            text = text.replace("\n", "");
                            text = text.replace("\r", "");
                            enterPressed();
                        }
                        
                        editTextChanged(text);
                    }
                }
            }
        }
    }
}
