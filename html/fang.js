/**
  This is Fang's Javascript logic.  But I mean, you knew that.  DUH!
  */

// Appends (or prepends) a news item.
function appendNews(append, id, title, url, feedTitle, timestamp, content) {
    // Copy the model.
    var item = $( 'body>.newsContainer#model' ).clone();
    
    // I'm a model, you know what I mean...
    // (but not anymore!! HAHA!)
    item.attr( 'id', '' );
    
    // Assign data.
    item.attr( 'id', id );
    item.find( '.link' ).attr( 'href', url );
    item.find( '.link' ).html( title );
    item.find( '.content' ).html( content );
    item.find( '.siteTitle' ).html( feedTitle );
    item.find( '.date' ).html( timestamp );
    
    // console.log(item.html());
    // console.log("ID: ", id)//item.getAttribute('id' ));
    
    // Stick 'er in!
    // TODO: prepend
    item.insertAfter( 'body>.newsContainer:last-child' );
}

// Clears out all the news from the view.
function clearNews() {
    //console.log("Clearing news")
    
    // Iterate over all news container items.
    var newsItem = $( "body>.newsContainer" );
    for (var i = 0; i < newsItem.length; i++) {
        var current = newsItem[i];
        
        // If it's not our model, DELETE!
        if (current.getAttribute('id') !== 'model' )
            current.parentNode.removeChild( current );
    }
}

// Scrolls to the element with the given ID.
function jumpTo(id) {
    var elementId = '#' + id;
    var scrollTo = $( elementId ).offset().top;
    
//    console.log("jump to: ", elementId, "scrolling to: ", scrollTo);
//    console.log("element: ", $( elementId ).prop('tagName'));
    window.fang.setScroll( scrollTo );
}

// Draws a bookmark on the given news container ID.
function drawBookmark(id) {
    var elementId = '#' + id;
    console.log("Bookmark at ", elementId)
    $( elementId ).addClass('bookmarked');
}

// Removes all existing classes on the body element.
function clearBodyClasses() {
    $('body').removeClass();
}

// Adds a class to the body element.
function addBodyClass(p) {
    //console.log("adding class " + p);
    $('body').addClass(p);
}

// Main method
$(document).ready(function() {
    /**
     * distance: pixels from bottom that triggers callback.
     * interval is how often the check will run (in milliseconds; 250-1000 is reasonable).
     */
    function watchScrollPosition(bottomCallback, topCallback, bookmarkCallback, distance, interval) {
        var $document = $(document);
        
        var prevScrollTop = 0;
        
        var checkScrollPosition = function() {
            var scrollTop = window.fang.getScroll();
            
            // If the user hasn't scrolled, there's nothing to do.
            if (prevScrollTop === scrollTop)
                return;
            
            // Check top.
            var top = distance;
            if (scrollTop <= top) {
                topCallback();
            }
            
            // Check bottom (note: calculation MUST be done after topCallback()!!!!)
            var bottom = $document.height() - window.fang.getHeight() - distance;
            if (scrollTop >= bottom) {
                bottomCallback();
            }
            
            bookmarkCallback();
            
            prevScrollTop = scrollTop;
        };

        setInterval(checkScrollPosition, interval);
    }
    
    // Returns true if the element is above the scroll position, else false.
    function isAboveScroll(element) {
        return $(document).scrollTop() > element.offset().top + element.height();
    }
    
    // Sets the bookmark to the given element.
    function setBookmark(element) {
        console.log("Bookmarking next item")
        // Remove existing bookmark.
        var bookmarkedItem = $( "#bookmarked" );
        if (bookmarkedItem.length > 0) {
            bookmarkedItem.removeAttr('id');
        }
        
        // Set the new one.
        element.attr("id", "bookmarked");
    }
    
    // Adjust the bookmark if necessary.
    function checkBookmark() {
//        var bookmarkedItem = $( "#bookmarked" );
        
//        // Check if the bottom of the bookmarked item is above the scroll level.
//        // If not, bail now since the bookmark won't be changed.
//        if (!isAboveScroll(bookmarkedItem))
//            return;
        
//        //console.log("Bookmark is above scroll!  It may require changing:", bookmarkedItem.next().length);
        
//        // Go through all the next items.
//        var nextItem = bookmarkedItem.next();
//        while (true) {
//            if (nextItem.length < 1) {
//                console.log("We've bookmarked the final item, sir.");
                
//                break;
//            }
            
//            // Nothing more to do.
//            if (!isAboveScroll(nextItem))
//                break;
            
//            // Move the bookmark down one.
//            setBookmark(nextItem);
            
//            // Continue to next item.
//            nextItem = nextItem.next();
//        }
    }
    
    function loadNext() {
        //console.log("Load nxt");
        window.fang.loadNext();
    }
    
    function loadPrevious() {
        //console.log("load prev");
        window.fang.loadPrevious();
    }
    
    watchScrollPosition(loadNext, loadPrevious, checkBookmark, 250, 250);
    
    // Scroll down a bit.
    //$(document).scrollTop(300);
});
