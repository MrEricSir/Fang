import QtQuick 2.0

Image {
    id: fangIcon;
    
    // Hack to make SVGs render with anti-aliasing
    sourceSize.width: width;
    sourceSize.height: height;
    smooth: true; // Since this is used in animation
    asynchronous: true;
    
    // Set state to change graphic.
    state: "ok";
    
    states: [
        State { name: "ok" },
        State { name: "help" },
        State { name: "error" },
        State { name: "spinner" }
    ]
    
    source: getImage(state);
    
    function getImage(newState) {
        if (newState === "ok")
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_ok.svg" : "images/symbol_dark_ok.svg";
        else if (newState === "help")
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_question.svg" : "images/symbol_dark_question.svg";
        else if (newState === "error")
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_error.svg" : "images/symbol_dark_error.svg";
        else if (newState === "spinner")
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_reload.svg" : "images/symbol_dark_reload.svg";
        else
            console.log("Unknown state if FangIcon: ", newState);
    }
    
    Style {
        id: style;
    }
    
    onStateChanged: {
        if (state === "spinner") {
            spinAnimation.restart();
        } else {
            spinAnimation.stop();
            fangIcon.rotation = 0;
        }
    }
    
    RotationAnimation  {
        id: spinAnimation;
        
        running: false;
        direction: RotationAnimation.Clockwise;
        loops: Animation.Infinite;
        
        target: fangIcon;
        from: 0;
        to: 360;
        duration: 750;
        
        // Hack to supress warning message.
        property: "rotation";
    }
}
