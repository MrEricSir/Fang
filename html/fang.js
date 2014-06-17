/**
  This is Fang's Javascript logic.  But I mean, you knew that.  DUH!
  */

var newsContainerSelector = 'body>.newsContainer:not(#model)';

// Large default to prevent accidental bookmarks.
var defaultWindowHeight = 50000;

// Height of window.  We can't use $(window).height() because Qt embeds WebView in a flickable.
var windowHeight = defaultWindowHeight;

// When the window is resized, jump to bookmark after a short delay.
$(window).resize(function() {
    if(this.resizeTO) clearTimeout(this.resizeTO);
        this.resizeTO = window.setTimeout(function() {
            //console.log("RESIZE");
            jumpToBookmark();
    }, 50);
    
});

// Intercept clix.
function delegateLink() {
    navigator.qt.postMessage( 'openLink ' + $(this).attr( 'href' ) );
    return false; // Don't propogate link.
};

// Collects the size of each prepended item to use for scrolling up.
var prependScroll = 0;

// True if an operation is in progress.  Set to true by clearNews().
var isInProgress = false;

// We're either about to append, prepend, or do the initial load.
function inProgress(started, operation) {
    if (started)
        prependScroll = 0;
    
    if (!started && operation === "prepend" && prependScroll > 10) {
        $(document).scrollTop( prependScroll );
        //console.log("Prepend: scroll to: ", prependScroll);
    }
    
    // Let the stop go through both processes so we can ensure the view has moved.
    if (!started) {
        window.setTimeout(function() {
            navigator.qt.postMessage( 'stopProgress' );
        }, 50);
    }
}

// Used above.
function stopInProgress() {
    isInProgress = false;
}

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
    item.find( '.timestamp' ).html( timestamp ); // Hidden timestamp (shh)
    item.find( '.date' ).html( formatDateSimply(timestamp) );
    
    //console.log(item.html());
    //console.log("ID: ", id, "append: ", append)
    
    // Setup link delegator.
    item.find( 'a' ).on( "click", delegateLink );
    
    // Stick 'er in!
    if (append) {
        console.log("Append!")
        item.insertAfter('body>.newsContainer:last');
    } else {
        console.log("Prepend!")
        item.insertBefore( 'body>.newsContainer:first' );
        
        // Calculate the size and add it to our prepend scroll tally.
        var verticalMargins = parseInt( item.css("marginBottom") ) + parseInt( item.css("marginTop") );
        prependScroll += verticalMargins + item.height();
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
    isInProgress = true;
    removeMatchingItems( $(newsContainerSelector) );
}

// Returns the last news container.
function getLastNewsContainer() {
    return $(newsContainerSelector).last();
}

// Resizes the bottom spacer to allow the last item to be bookmarked.
function resizeBottomSpacer() {
    // Grab the last (non model) news item.
    var lastItem = getLastNewsContainer();
    //console.log("Reszie bottom spacer. last item: ", lastItem)
    
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
    
    //console.log("Bottom spacer is now: ", numPix)
    $( '#bottom' ).height( numPix + 'px' );
}

// Scrolls to the element with the given ID.
function jumpTo(id) {
    //console.log("Jump to: ", id)
    
    resizeBottomSpacer();
    
    var elementId = '#' + id;
    var scrollTo = $( elementId ).offset().top;
    
    //console.log("jump to: ", elementId, "scrolling to: ", scrollTo);
    
    //navigator.qt.postMessage( 'scrollToPosition ' + scrollTo );
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


// Both draw the bookmark AND jump to it!  In ONE SHOT!!  WOW!
var bookmarkIdWeAreJumpingTo = "";
function drawBookmarkAndJumpTo(id) {
    bookmarkIdWeAreJumpingTo = id;
    drawBookmarkAndJumpToJumpingToId();
}

// Internal method for above function.
function drawBookmarkAndJumpToJumpingToId() {
    //console.log("Draw and jumping to jump jump")
    if (isInProgress) {
        window.setTimeout(function() {
            drawBookmarkAndJumpToJumpingToId();
        }, 1);
        
        return;
    }
    
    //console.log("Jump out complete: ", bookmarkIdWeAreJumpingTo)
    
    // If there's a bookmark, jump to it!
    if (bookmarkIdWeAreJumpingTo !== '') {
        // Draw our bookmark and jump to it!
        drawBookmark(bookmarkIdWeAreJumpingTo);
        jumpToBookmark();
    }
    
    // Tell NewsView that we're ready to ROCK and ROLL.
    navigator.qt.postMessage( 'drawBookmarkAndJumpToFinished' );
}

function jumpToBookmark() {
    console.log("Jump to bookmark");
    
    resizeBottomSpacer();
    
    // If there's a bookmark, this will jump to it.
    var element = $( ".bookmarked > .bookmark" );
    if (!element || element.length === 0)
        return;
    
    var scrollTo = element.offset().top - 10;
    
    //console.log("Scroll to: ", scrollTo, " window height: ", windowHeight, " document h: ", $(document).height());
    
    // Set max jump. (It overshoots on first load.)
    if (scrollTo > $(document).height() - windowHeight)
        scrollTo = $(document).height() - windowHeight;
    
    $(document).scrollTop( scrollTo );
}

// UTILITY: Returns true if the element is a real news item,
//          rather than a model or chrome component.
function isNewsContainer(element) {
    var ret = element.hasClass('newsContainer') && element.attr('id') !== 'model';
    //console.log("Is news container: ", element, " :: ", ret)
    return ret;
}

// Returns the next news item in our little list.
function nextNewsContainer(element) {
    //console.log("nextNewsContainer for: ", element)

    // Loop until we find another valid news container.
    var item = element;
    while (item.length) {
        item = item.next();
        //console.log("Examining item: ", item.attr('id'))
        if (isNewsContainer(item)) {
            //console.log("nextNewsC took this: ", element.attr('id'), " and spat out this: ", item)
            return item;
        }
    }
    
    return; // :(
}

// Or how about the previous one, why not?
function prevNewsContainer(element) {
    //console.log("prevNewsContainer for: ", element)
    
    // Loop backwards until we find another valid news container.
    var item = element;
    while (item.length) {
        item = item.prev();
        //console.log("Examining item: ", item.attr('id'))
        if (isNewsContainer(item)) {
            //console.log("prevNewsC took this: ", element.attr('id'), " and spat out this: ", item)
            return item;
        }
    }
    
    return; // :(
}

// UTILITY: Returns true if the element is above the scroll position, else false.
function isAboveScroll(element) {
    //console.log("Is above scroll: ", element)
    
    // We don't want to include the bookmark space this calculation.
    var bookmarkHeight = 0;
    var bookmark = element.find('.bookmark');
    if (bookmark.length) {
        bookmarkHeight = bookmark.height();
    }
    
    //console.log("Bookmark Height: ", bookmarkHeight);
     
    var allHeight = element.offset().top + element.height() - bookmarkHeight;
    var ret = $(window).scrollTop() >= allHeight;
    
    //console.log("isAboveScroll: Scroll top: ", $(window).scrollTop(), " elem offset and height: ", allHeight, " ret: ", ret)
    return ret;
}

// UTILITY: Just like isAboveScroll(), but this only checks the top of the element.
function isTopAboveScroll(element) {
    //console.log("Is top above scroll: ", element)
    //console.log("isTopAboveScroll: Scroll top: ", $(window).scrollTop(), " elem offset and height: ", element.offset().top + element.height())
    
    return $(window).scrollTop() >= element.offset().top + 10;
}

// UTILITY: Returns the first visible news item.
function getFirstVisible() {
    // Go through all the next items.
    var item = $(newsContainerSelector);
    while (item.length) {
        if (!isAboveScroll(item))
            return item;
        
        item = nextNewsContainer(item);
    }
    
    console.log("GFV: it's LAST: ", item.last())
    
    // Just return the last item, then?
    return getLastNewsContainer();
}

// Jumps to the next or previous item on the screen.
function jumpNextPrev(jumpNext) {
    var current = getFirstVisible();
    
    //console.log("JNP: first visible: ", current)
    //console.log("Is above scroll: ", isAboveScroll(current))
    
    if (!current.length)
        return;
    
    // Either go to the next item, or jump back up to the current one.
    var jumpTo = current;
    if (jumpNext) {
        jumpTo = nextNewsContainer(jumpTo);
        //console.log("Next valid news container: ", jumpTo);
    } else {
        // Check if we're strattling the top.  If not, jump one back.
        if (!isTopAboveScroll(jumpTo)) {
            jumpTo = prevNewsContainer(jumpTo);
            //console.log("Prev not top above scroll: ", jumpTo);
        } else {
            //console.log("Jump to current: ", jumpTo);
        }
    }
    
    //console.log("Current is: ", current)
    //console.log("Jump to is: ", jumpTo)
    
    if (!jumpTo.length) {
        //console.log("No length! ABORT ABORT");
        return;
    }
    
    //navigator.qt.postMessage( 'scrollToPosition ' + jumpTo.offset().top );
    $(document).scrollTop( jumpTo.offset().top );
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


// Called by QML to tell us the height of the window.
function setWindowHeight(height) {
    //console.log("height is now: ", height)
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
            var bottomTwo = $document.height() - windowHeight - distance - $( '#bottom' ).height();
            if (scrollTop >= bottomTwo) {
                bottomCallback();
            }
            
            bookmarkCallback();
            
            prevScrollTop = scrollTop;
        };

        setInterval(checkScrollPosition, interval);
    }
    
    // Adjust the bookmark if necessary.
    function checkBookmark() {
        if (isInProgress)
            return; // Wait for news items to appear, dummy!
        
        if ($(newsContainerSelector).length === 0) {
            //console.log("NO NEWS CONTAINERS to deal with, no need to set bmkar")
            
            return;
        }
        
        // Start at the current bookmark.
        var bookmarkedItem = $( 'body>.bookmarked' );
        //console.log("Current bookmark: ", bookmarkedItem)
        
        // Check if the current bookmark is valid.
        if (bookmarkedItem.length && !isAboveScroll(bookmarkedItem)) {
            //console.log("Currently bookmarked item is not above scroll.  Goodbye!", bookmarkedItem.attr('id'));
            
            return;
        }
        
        // If there's a bookmark, get the next item.  Otherwise, get the first news container.
        var nextItem = bookmarkedItem.length ? nextNewsContainer(bookmarkedItem) : $(newsContainerSelector);
        
        //console.log("Bookmark is above scroll! ", bookmarkedItem);
        //console.log("Next available news item is: ", nextItem);
        
        while (nextItem.length >= 1) {
            // Nothing more to do.
            if (!isAboveScroll(nextItem)) {
                //console.log("item not above scroll:", nextItem.attr('id'))
                
                break;
            }
            
            // Move the bookmark down one.
            //console.log("SET BOOKMKAR! ", nextItem.attr('id'))
            navigator.qt.postMessage( 'setBookmark ' + nextItem.attr('id') );
            
            // Continue to next item.
            nextItem = nextNewsContainer(nextItem);
        }
    }
    
    function loadNext() {
        if (isInProgress)
            return;
        
        //console.log("loadNext")
        navigator.qt.postMessage( 'loadNext' );
    }
    
    function loadPrevious() {
        if (isInProgress)
            return;
        
        //console.log("load prev")
        navigator.qt.postMessage( 'loadPrevious' );
    }
    
    
    /**
     * Timestamp update timer.
     */
    function updateTimestamps(interval) {
        var $document = $(document);
        
        // Grab each timestamp, then re-call formatDateSimply() on it.
        var updateTimestampsCallback = function() {
            var item = $(newsContainerSelector);
            while (item.length) {
                //console.log("Examining item: ", item.attr('id'))
                if (isNewsContainer(item)) {
                    // Hidden timestamp!  (Shh.)
                    var timestamp = item.find( '.timestamp' ).html();
                    item.find( '.date' ).html( formatDateSimply(timestamp) );
                }
                item = item.next();
            }
        };

        setInterval(updateTimestampsCallback, interval);
    }
    
    /**
     * Touch off all the timers we just defined.
     */
    
    // Poll for scroll position every 250 ms.
    watchScrollPosition(loadNext, loadPrevious, checkBookmark, 250, 250);
    
    // Update timestamps every 10 seconds.
    updateTimestamps(10000);
});
