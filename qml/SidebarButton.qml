import QtQuick

Button {
    id: sidebarButton;

    // Define images here.
    property url lightImageURL: "";
    property url darkImageURL: "";

    // lightImageURL = dark-colored icon (for light backgrounds)
    // darkImageURL = light-colored icon (for dark backgrounds)
    property url imageURL: fangSettings.currentStyle === "LIGHT" ? lightImageURL : darkImageURL;
    property url imageHoverURL: fangSettings.currentStyle === "LIGHT" ? lightImageURL : darkImageURL;
    property url imagePressedURL: fangSettings.currentStyle === "LIGHT" ? lightImageURL : darkImageURL;
    
    property int imageMargin: 7 * style.scale;
    
    radius: width / 2;
    
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
