import QtQuick 2.0

Button {
    id: sidebarButton
    property url imageURL: ""
    property url imageHoverURL: ""
    property url imagePressedURL: ""
    
    property int imageMargin: 7
    
    radius: width * 0.5
    
    buttonColor: style.color.sidebarButton
    hoverColor: style.color.sidebarButtonHover
    pressedColor: style.color.sidebarButtonPressed
    borderColor: style.color.sidebarButtonBorder
    // We don't set a disabledColor because that hasn't been required (yet!)
    
    
    Image {
        source: sidebarButton.state === "hover" ? sidebarButton.imageHoverURL : 
                                    sidebarButton.state === "pressed" ?
                                        sidebarButton.imagePressedURL : sidebarButton.imageURL
        
        anchors.fill: parent
        anchors.margins: imageMargin
        fillMode: Image.PreserveAspectCrop
        asynchronous: true
        
        // Make SVGs render real good like.
        sourceSize.width: width
        sourceSize.height: height
    }
}
