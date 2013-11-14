/**
  This is Fang's Javascript logic.  But I mean, you knew that.  DUH!
  */

function appendNews(append, title, url, feedTitle, timestamp, content) {
    // Copy the model.
    var item = $( 'body>.newsContainer#model' ).clone();
    
    // I'm a model, you know what I mean...
    // (but not anymore!! HAHA!)
    item.attr( 'id', '' );
    
    // Assign data.
    item.find( '.link' ).attr( 'href', url );
    item.find( '.link' ).html( title );
    item.find( '.content' ).html( content );
    item.find( '.siteTitle' ).html( feedTitle );
    item.find( '.date' ).html( timestamp );
    
    // console.log(item.html());
    
    // Stick 'er in!
    // TODO: prepend
    item.insertAfter( 'body>.newsContainer:last-child' );
}

function clearBodyClasses() {
    $('body').removeClass();
}

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
    $(document).scrollTop(300);
});
