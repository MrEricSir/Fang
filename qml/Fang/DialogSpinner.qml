import QtQuick 2.0

Rectangle {
    id: dialogSpinner
    property string text: ""
    color: "transparent"
    
    height: dialogSpinnerText.paintedHeight
    
    Style {
        id: style
    }
    
    Spinner {
        id: spinnerImage
        
        width: parent.height
        height: parent.height
    }
    
    Text {
        id: dialogSpinnerText
        
        text: dialogSpinner.text
        
        x: spinnerImage.width + 10 // margin
        
        color: style.color.fadedText
        
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        renderType: Text.NativeRendering
        
        width: parent.width - x
    }
}

