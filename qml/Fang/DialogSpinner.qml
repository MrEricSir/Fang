import QtQuick 1.1

Rectangle {
    id: dialogSpinner
    property string text: ""
    color: "transparent"
    
    height: dialogSpinnerText.paintedHeight
    
    Image {
        id: spinnerImage
        
        width: parent.height
        height: parent.height
        
        // Hack to make SVGs render with anti-aliasing
        sourceSize.width: width
        sourceSize.height: height
        smooth: true
        
        source: "images/symbol_reload.svg"
        
        onVisibleChanged: {
            if (visible)
                spinAnimation.restart();
            else
                spinAnimation.stop();
        }
        
        RotationAnimation  {
            id: spinAnimation
            
            running: true
            direction: RotationAnimation.Clockwise
            loops: Animation.Infinite
            
            target: spinnerImage
            from: 0
            to: 360
            duration: 750
            
            // Hack to supress warning message.
            property: "rotation"
        }
        
        
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

