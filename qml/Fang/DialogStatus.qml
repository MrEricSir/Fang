import QtQuick 1.1

Rectangle {
    id: dialogStatus
    property string text: ""
    color: "transparent"
    
    height: dialogStatusText.paintedHeight
    
    // Set state to change grpahic.
    state: "ok"
    
    states: [
        State { name: "ok" },
        State { name: "help" },
        State { name: "error" }
    ]
    
    function getImage(newState) {
        if (newState === "ok")
            return "images/symbol_ok.svg";
        else if (newState === "help")
            return "images/symbol_question.svg";
        else if (newState === "error")
            return "images/symbol_error.svg";
    }
    
    Image {
        id: statusImage
        
        width: parent.height
        height: parent.height
        
        // Hack to make SVGs render with anti-aliasing
        sourceSize.width: width
        sourceSize.height: height
        smooth: true
        
        source: getImage(dialogStatus.state);
    }
    
    Text {
        id: dialogStatusText
        
        text: dialogStatus.text
        
        x: statusImage.width + 10 // margin
        
        color: "black"
        
        font.pointSize: 12
        font.family: "Tahoma"
        
        width: parent.width - x
    }
}

