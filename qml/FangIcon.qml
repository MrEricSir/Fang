import QtQuick

Image {
    id: fangIcon;
    
    // Hack to make SVGs render with anti-aliasing
    sourceSize.width: width;
    sourceSize.height: height;
    smooth: true; // Since this is used in animation
    asynchronous: true;
    
    // Set state to change graphic.
    state: "";
    
    states: [
        State { name: "ok" },
        State { name: "help" },
        State { name: "error" },
        State { name: "spinner" }
    ]
    
    source: {
        switch (fangIcon.state) {
        case "ok":
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_ok.svg" : "images/symbol_dark_ok.svg";
        case "help":
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_question.svg" : "images/symbol_dark_question.svg";
        case "error":
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_error.svg" : "images/symbol_dark_error.svg";
        case "spinner":
            return fangSettings.style === "LIGHT" ?
                        "images/symbol_reload.svg" : "images/symbol_dark_reload.svg";
        default:
            console.log("Unknown state of FangIcon: ", fangIcon.state);
        }
    }
    
    Style {
        id: style;
    }

    // Spinner animation.
    RotationAnimation {
        id: spinAnimation;

        running: state === "spinner";
        direction: RotationAnimation.Clockwise;
        loops: Animation.Infinite;

        target: fangIcon;
        from: 0;
        to: 360;
        duration: 750;

        onStopped: () => {
           target.rotation = 0;
       }
    }
}
