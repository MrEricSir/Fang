/**
  This is Fang's Javascript logic.  But I mean, you knew that.  DUH!
  */

// Large default to prevent accidental bookmarks.
var defaultWindowHeight = 50000;

// Height of window.  We can't use $(window).height() because Qt embeds WebView in a flickable.
var windowHeight = defaultWindowHeight; 

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
    //console.log("ID: ", id, "append: ", append)
    
    // Stick 'er in!
    if (append) {
        console.log("append! ", id)
        item.insertAfter('body>.newsContainer:last');
    } else {
        console.log("Prepend!")
        item.insertBefore( 'body>.newsContainer:first' );
        
        // Scroll down after prepend.
        var verticalMargins = parseInt( item.css("marginBottom") ) + parseInt( item.css("marginTop") );
        $(document).scrollTop( $(document).scrollTop() + verticalMargins + item.height() );
    }
    
    resizeBottomSpacer();
}

function removeMatchingItems(item) {
    // Iterate over all items that match.
    for ( var i = 0; i < item.length; i++ ) {
        var current = item[i];
        
        // DELETE!
        current.parentNode.removeChild( current );
    }
}

// Clears out all the news from the view.
function clearNews() {
    removeMatchingItems( $('body>.newsContainer:not(#model)') );
}

function resizeBottomSpacer() {
    // Grab the last (non model) news item.
    var lastItem = $( 'body>.newsContainer' ).last();
    //console.log("last item: ", lastItem)
    
    // By default, bottom spacer is the window height.  This allows the user
    // to scroll the last item off the page, bookmarking it.
    var numPix = windowHeight;
    
    // If the final item is already bookmarked, collapse the bottom spacer a bit.
    if ( lastItem.hasClass( 'bookmarked' ) ) {
        
        var removePix = lastItem.height();
        if (removePix > numPix)
            removePix = numPix; // Don't exceed window height.
        
        numPix -= removePix;
    }
    
    $( '#bottom' ).height( numPix + 'px' );
}

// Scrolls to the element with the given ID.
function jumpTo(id) {
    // Append to event loop.
    window.setTimeout(jumpToInternal, 1, id);
}

function jumpToInternal(id) {
    console.log("Jump to: ", id)
    
    resizeBottomSpacer();
    
    var elementId = '#' + id;
    var scrollTo = $( elementId ).offset().top;
    
    console.log("jump to: ", elementId, "scrolling to: ", scrollTo);
    $(document).scrollTop( scrollTo );
}

// Draws a bookmark on the given news container ID.
function drawBookmark(id) {
    // Remove any existing bookmark(s).
    $( ".bookmarked" ).removeClass('bookmarked');
    
    // Add bookmark.
    var elementId = '#' + id;
    $( elementId ).addClass('bookmarked');
    
    resizeBottomSpacer();
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

function setWindowHeight(height) {
    console.log("height is now: ", height)
    windowHeight = height;
    
    resizeBottomSpacer();
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
            var scrollTop =  $(document).scrollTop();
            
            // If the user hasn't scrolled, check bottom and bail.
            if (prevScrollTop === scrollTop) {
                
                // If we're at the bottom, always trigger the callback.
                var bottom = $document.height() - windowHeight - distance - $( '#bottom' ).height();
                if (scrollTop >= bottom) {
                    //console.log("at bottom!")
                    bottomCallback();
                }
                
                return;
            }
            
            // Check top.
            var top = distance;
            if (scrollTop <= top) {
                topCallback();
            }
            
            // Check bottom (note: calculation MUST be done after topCallback()!!!!)
            var bottom = $document.height() - windowHeight - distance - $( '#bottom' ).height();
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
        //console.log("Is above scroll: ", element)
        if (element.attr('id') === 'model')
            element = element.next(); // Skip the model.
        
        //console.log("isAboveScroll: Scroll top: ", $(window).scrollTop(), " elem offset and height: ", element.offset().top + element.height())
        
        return $(window).scrollTop() >= element.offset().top + element.height() - 1;
    }
    
    // Adjust the bookmark if necessary.
    function checkBookmark() {
        // Start at the current bookmark.
        var bookmarkedItem = $( 'body>.bookmarked' );
        
        // No bookmark?  No problem, we'll look at the first news item instead.
        if (!bookmarkedItem.length) {
            bookmarkedItem = $( 'body>.newsContainer' );
            //console.log("No bookmark found: starting with: ", bookmarkedItem)
        }
        
        // Oh bother.  I guess there's nothing to do.
        if (bookmarkedItem.length < 1) {
            //console.log("No bookmarks to deal with.  w00t!")
            
            return;
        }
        
        // Check if the bottom of the bookmarked item is above the scroll level.
        // If not, bail now since the bookmark won't be changed.
        if (!isAboveScroll(bookmarkedItem)) {
            console.log("not above scroll!", bookmarkedItem.attr('id'))
            
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
            if (nextItem.attr('id') === 'model') {
                console.log("Skipping over model");
                nextItem = nextItem.next();
                
                continue;
            }
            
            // Nothing more to do.
            if (!isAboveScroll(nextItem)) {
                console.log("item not above scroll:", nextItem.attr('id'))
                
                break;
            }
            
            // Move the bookmark down one.
            //console.log("SET BOOKMKAR! ", nextItem.attr('id'))
            navigator.qt.postMessage( 'setBookmark ' + nextItem.attr('id') );
            
            // Continue to next item.
            nextItem = nextItem.next();
        }
    }
    
    function loadNext() {
        //console.log("loadNext")
        navigator.qt.postMessage( 'loadNext' );
    }
    
    function loadPrevious() {
        navigator.qt.postMessage( 'loadPrevious' );
    }
    
    watchScrollPosition(loadNext, loadPrevious, checkBookmark, 250, 250);
});
