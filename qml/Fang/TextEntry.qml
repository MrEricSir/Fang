import QtQuick 2.0

// A text entry box.
Rectangle {
    id: textEntry
    
    // Font size.
    property int fontSize: 11
    
    // The grayed-out "hint" text.
    property string hint: ""
    
    // Set the editable text.
    function setEditText(myText) {
        edit.text = myText;
        
        // Set position to end.
        edit.cursorPosition = edit.text.length
    }
    
    // Ready-only.
    property string editText: edit.text
    
    // Signaled on every text change.
    signal textChanged(string text)
    
    // Signaled when user hits enter/return.
    signal enterKeyPressed()
    
    Style {
        id: style
    }
    
    color: style.color.textEntryBorder
    height: textEntryContainer.height + 12
    
    Rectangle {
        id: textEntryContainer
        
        color: style.color.textEntryBackground
        width: parent.width - 12
        height: textEntryContainerInnerMargin.height + 12
        
        anchors.centerIn: parent
        
        MouseArea {
            anchors.fill: parent
            onClicked: edit.forceActiveFocus()
        }
        
        Rectangle {
            id: textEntryContainerInnerMargin
            
            width: parent.width - 12
            height: Math.max(hintText.paintedHeight, edit.paintedHeight)
            
            color: parent.color
            
            anchors.centerIn: parent
            
            // The default "hint" text
            Text {
                id: hintText
                
                width: parent.width
                
                text: hint
                
                visible: edit.text == "" || !edit.activeFocus
                
                color: style.color.textEntryHint
                font.italic: true
                font.family: style.font.defaultFamily
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
                    if (edit.width < width)
                        edit.width = width;
                    
                    if (edit.text == "") {
                        contentX = 0;
                        //edit.width = width; // reset width to prevent it from being too narrow
                    } else if (contentX >= r.x)
                        contentX = r.x;
                    else if (contentX + width <= r.x + r.width)
                        contentX = r.x + r.width - width;
                }
                
                // Editable field
                TextEdit {
                    id: edit
                    
                    text: ""
                    
                    textFormat: TextEdit.PlainText
                    
                    color: style.color.textEntryText
                    font.family: style.font.defaultFamily
                    font.pointSize: textEntry.fontSize
                    focus: true
                    wrapMode: TextEdit.NoWrap
                    
                    //onActiveFocusChanged: console.log("Got focus")
                    
                    // Used with the above flickable.
                    onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                    
                    onTextChanged: {
                        console.log("on text changed!: ", text)
                        // 1337 HAX to prevent newlines in text field.
                        if (text.indexOf('\n') != -1 || text.indexOf('\r') != -1) {
                            text = text.replace("\n", "");
                            text = text.replace("\r", "");
                            enterKeyPressed();
                        }
                        
                        textEntry.textChanged(text);
                        flick.ensureVisible(cursorRectangle); // Used with above flickable.
                    }
                    
                    onVisibleChanged: {
                        if (visible)
                            forceActiveFocus();
                    }
                }
            }
        }
    }
}
