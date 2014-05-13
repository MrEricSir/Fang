import QtQuick 2.0

Rectangle {
    id: dialogStatus
    property string text: ""
    color: "transparent"
    
    width: parent.width
    height: dialogStatusText.paintedHeight
    
    // Set state to change graphic.
    state: "ok"
    
    states: [
        State { name: "ok" },
        State { name: "help" },
        State { name: "error" }
    ]
    
    function getImage(newState) {
        if (newState === "ok")
            return fangSettings.style === "LIGHT" ? "images/symbol_ok.svg" : "images/symbol_dark_ok.svg";
        else if (newState === "help")
            return fangSettings.style === "LIGHT" ? "images/symbol_question.svg" : "images/symbol_dark_question.svg";
        else if (newState === "error")
            return fangSettings.style === "LIGHT" ? "images/symbol_error.svg" : "images/symbol_dark_error.svg";
    }
    
    Style {
        id: style
    }
    
    Image {
        id: statusImage
        
        width: parent.height
        height: parent.height
        
        // Hack to make SVGs render with anti-aliasing
        sourceSize.width: width
        sourceSize.height: height
        asynchronous: true
        
        source: getImage(dialogStatus.state);
    }
    
    Text {
        id: dialogStatusText
        
        text: dialogStatus.text
        
        x: statusImage.width + 10 // margin
        
        font.pointSize: style.font.defaultSize
        font.family: style.font.defaultFamily
        color: style.color.dialogText
        
        width: parent.width - x
    }
}

