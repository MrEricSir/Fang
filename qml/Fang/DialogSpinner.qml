import QtQuick 1.1

Rectangle {
    id: dialogSpinner
    property string text: ""
    color: "transparent"
    
    height: dialogSpinnerText.paintedHeight
    
    Spinner {
        id: spinnerImage
        
        width: parent.height
        height: parent.height
    }
    
    Text {
        id: dialogSpinnerText
        
        text: dialogSpinner.text
        
        x: spinnerImage.width + 10 // margin
        
        color: "#999"
        
        font.pointSize: 12
        font.family: "Tahoma"
        
        width: parent.width - x
    }
}

