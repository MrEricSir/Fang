import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

// A text entry box.
TextField {
    id: textEntry
    
    // Note: this extremely hacky height calculation relies on the fact
    // that the TextEdit is the second child of TextField.
    height: textEntry.children[2].paintedHeight + (12  * style.scale);
    
    style: TextFieldStyle {
        Style {
            id: style
        }
        
        textColor: style.color.textEntryText
        
        font {
            family: style.font.defaultFamily
            pointSize: style.font.defaultSize
        }
        
        placeholderTextColor: style.color.textEntryHint
        
        background: Rectangle {
            color: style.color.textEntryBackground
            border.color: style.color.textEntryBorder
            border.width: 1 * style.scale
            
        }
    }
}
