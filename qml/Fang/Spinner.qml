import QtQuick 2.0

Image {
    id: spinner
    
    // Hack to make SVGs render with anti-aliasing
    sourceSize.width: width
    sourceSize.height: height
    smooth: true
    
    source: fangSettings.style === "LIGHT" ? "images/symbol_reload.svg" : "images/symbol_dark_reload.svg"
    
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
        
        target: spinner
        from: 0
        to: 360
        duration: 750
        
        // Hack to supress warning message.
        property: "rotation"
    }
}
