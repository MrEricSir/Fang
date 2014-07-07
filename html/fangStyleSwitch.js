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
