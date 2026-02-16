import QtQuick

Button {
    id: sidebarButton;

    // Define images here.
    property url lightImageURL: "";
    property url darkImageURL: "";

    property url imageURL: fangSettings.currentStyle === "LIGHT" ? darkImageURL : lightImageURL;
    property url imageHoverURL: fangSettings.currentStyle === "LIGHT" ? darkImageURL : lightImageURL;
    property url imagePressedURL:  fangSettings.currentStyle === "DARK" ? darkImageURL : lightImageURL;
    
    property int imageMargin: 5 * style.scale;
    
    radius: style.defaultRadius;
    
    buttonColor: style.color.sidebarButton;
    hoverColor: style.color.sidebarButtonHover;
    pressedColor: style.color.sidebarButtonPressed;
    borderColor: style.color.sidebarButtonBorder;
    toggledColor: style.color.sidebarButtonPressed;
    // We don't set a disabledColor because that hasn't been required (yet!)
    
    Image {
        source: sidebarButton.state === "hover" ? sidebarButton.imageHoverURL :
                                    sidebarButton.state === "pressed" ?
                                        sidebarButton.imagePressedURL : sidebarButton.imageURL;
        
        anchors.fill: parent;
        anchors.margins: imageMargin;
        fillMode: Image.PreserveAspectCrop;
        asynchronous: true;
    }
}
