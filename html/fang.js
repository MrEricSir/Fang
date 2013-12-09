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
    
    //console.log(item.html());
    console.log("ID: ", id, "append: ", append)
    
    // Stick 'er in!
    if (append) {
        //console.log("append!")
        item.insertAfter('body>.newsContainer:last-child');
    } else {
        //console.log("Prepend!")
        item.insertBefore( 'body>.newsContainer:first-child' );
        
        // Scroll down after prepend.
        var verticalMargins = parseInt( item.css("marginBottom") ) + parseInt( item.css("marginTop") );
        window.fang.addToScroll( verticalMargins + item.height() );
    }
}

function removeMatchingItems(item) {
    // Iterate over all items that match.
    for ( var i = 0; i < item.length; i++ ) {
        var current = item[i];
        
        // If it's not our model, DELETE!
        if ( current.getAttribute('id') !== 'model' )
            current.parentNode.removeChild( current );
    }
}

// Clears out all the news from the view.
function clearNews() {
    //console.log("Clearing news")
    
    removeMatchingItems( $('body>.newsContainer') );
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
    // If we have another bookmark, remove it.
    
    // Remove any existing bookmark(s).
    $( ".bookmarked" ).removeClass('bookmarked');
    
    // Add bookmark.
    var elementId = '#' + id;
    $( elementId ).addClass('bookmarked');
    
    //console.log("Bookmark drawn at ", elementId);
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
        return window.fang.getScroll() > element.offset().top + element.height();
    }
    
    // Adjust the bookmark if necessary.
    function checkBookmark() {
        // Start at the current bookmark.
        var bookmarkedItem = $( 'body>.bookmarked' );
        
        // No bookmark?  No problem, we'll look at the first news item instead.
        if (!bookmarkedItem.length)
            bookmarkedItem = $( 'body>.newsContainer' );
        
        // Oh bother.  I guess there's nothing to do.
        if (bookmarkedItem.length < 1) {
            // There's *always* at least one news container (i.e. the model)
            console.log("No bookmarks to deal with.  w00t!")
            
            return;
        }
        
        // Check if the bottom of the bookmarked item is above the scroll level.
        // If not, bail now since the bookmark won't be changed.
        if (!isAboveScroll(bookmarkedItem)) {
            console.log("not above scroll!")
            
            return;
        }
        
        //console.log("Bookmark is above scroll!  It may require changing:", bookmarkedItem.next().length);
        
        // Go through all the next items.
        var nextItem = bookmarkedItem.next();
        while (true) {
            if (nextItem.length < 1) {
                console.log("We've bookmarked the final item, sir.");
                
                break;
            }
            
            // Ignore the model, she's so stuck up.
            if (nextItem[0].getAttribute('id') === 'model') {
                nextItem = nextItem.next();
                
                continue;
            }
            
            // Nothing more to do.
            if (!isAboveScroll(nextItem)) {
                console.log("item not above scroll")
                
                break;
            }
            
            // Move the bookmark down one.
            //console.log("bookmark item: ", nextItem);
            window.fang.setBookmark( nextItem[0].getAttribute('id') );
            
            // Continue to next item.
            nextItem = nextItem.next();
        }
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
});
