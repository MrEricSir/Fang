/**
  Fang's CSS logic!  Requires teh jQuery.
  */

// Removes all existing classes on the body element.
function clearBodyClasses() {
    $('body').removeClass();
}

// Adds a class to the body element.
function addBodyClass(p) {
    //console.log("adding class " + p);
    $('body').addClass(p);
}

// Sets the accent color.
function applyAccentColor(hex) {
    if (!hex) {
        return;
    }

    var body = document.body;
    body.style.setProperty('--accent', hex);

    // Compute a hover variant (20% lighter, clamped).
    var r = parseInt(hex.substring(1, 3), 16);
    var g = parseInt(hex.substring(3, 5), 16);
    var b = parseInt(hex.substring(5, 7), 16);

    r = Math.min(255, r + 40);
    g = Math.min(255, g + 40);
    b = Math.min(255, b + 40);

    var hover = '#' +
        r.toString(16).padStart(2, '0') +
        g.toString(16).padStart(2, '0') +
        b.toString(16).padStart(2, '0');

    body.style.setProperty('--accent-hover', hover);

    // Lighter variant for dark theme links (blend toward white).
    r = parseInt(hex.substring(1, 3), 16);
    g = parseInt(hex.substring(3, 5), 16);
    b = parseInt(hex.substring(5, 7), 16);

    r = Math.round(r + (255 - r) * 0.45);
    g = Math.round(g + (255 - g) * 0.45);
    b = Math.round(b + (255 - b) * 0.45);

    var light = '#' +
        r.toString(16).padStart(2, '0') +
        g.toString(16).padStart(2, '0') +
        b.toString(16).padStart(2, '0');

    body.style.setProperty('--accent-light', light);
}

// Sets the system font.
function applySystemFont(fontFamily) {
    if (!fontFamily) {
        return;
    }

    document.body.style.setProperty('--system-font', '"' + fontFamily + '", sans-serif');
}

// Sets the scrollbar color (used on Windows/Linux via ::-webkit-scrollbar CSS).
function applyScrollbarColor(hex) {
    if (!hex) {
        return;
    }

    document.body.style.setProperty('--scrollbar-color', hex);
}
