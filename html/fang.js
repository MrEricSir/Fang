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

// Converts one of Fang's internal IDs to an HTML news item id.
function idToHtmlId(id) {
    if (id == -1)
        return 'topBookmark';
    else
        return 'NewsItem_' + id;
}

function htmlIdToId(htmlID) {
    if (htmlID == 'topBookmark')
        return -1;
    else
        return htmlID.replace('NewsItem_', '');
}

// Intercept clix.
function delegateLink() {
    navigator.qt.postMessage( 'openLink ' + $(this).attr( 'href' ) );
    return false; // Don't propogate link.
};

// True if an operation is in progress.  Set to true by clearNews().
var isInProgress = false;

var currentOperation = "";

// We're either about to append, prepend, or do the initial load.
function inProgress(started, operation) {
    if (started) {
        currentOperation = operation;
    } else {
        currentOperation = "";
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

// Given a parent element, setup the bookmark forcer and pin handler.
function installMouseHandlers(parentElement) {
    // Setup manual bookmarks.
    $(parentElement).find( '.stripe' ).on( "click", function() { 
        var elementID = $(this).parent().parent().attr( 'id' );
        
        navigator.qt.postMessage( 'forceBookmark ' + htmlIdToId( elementID ) );
    } );

    // Setup the pin... pinner?
    $(parentElement).find( '.pin' ).on( "click", function() {
        var elementID = $(this).parent().parent().attr( 'id' );

        navigator.qt.postMessage( 'setPin ' + htmlIdToId( elementID ) );
    } );
}

// Appends (or prepends) a news item.
function appendNews(append, firstNewsID, jsonNews) {
    // Unescape newlines.  (This allows pre tags to work.)
    jsonNews = jsonNews.replace(/[\u0018]/g, "\n");
    
    // Unroll the JSON string into a Javascript object.
    var newsList = eval('(' + jsonNews + ')');
    //console.log("News list: ", newsList);
    
    // Remember where we are.
    var currentScroll = $(document).scrollTop();
    var addToScroll = 0;
    
    for (var i = 0; i < newsList.length; i++) {
        var newsItem = newsList[i];
        //console.log("news item:", newsItem);
        
        // Copy the model.
        var item = $( 'body>.newsContainer#model' ).clone();
        
        // I'm a model, you know what I mean...
        // (but not anymore!! HAHA!)
        item.attr( 'id', '' );
        
        // Assign data.
        item.attr( 'id', idToHtmlId(newsItem['id']) );
        item.find( '.link' ).attr( 'href', newsItem['url'] );
        item.find( '.link' ).html( newsItem['title'] );
        item.find( '.content' ).html( newsItem['content'] );
        item.find( '.siteTitle' ).html( newsItem['feedTitle'] );
        item.find( '.timestamp' ).html( newsItem['timestamp'] ); // Hidden timestamp (shh)
        item.find( '.date' ).html( formatDateSimply(newsItem['timestamp']) );

        // Set pin.
        if (newsItem['pinned']) {
            item.find( '.pin' ).addClass('pinned');
        }
        
        //console.log(item.html());
        //console.log("ID: ", id, "append: ", append)
        
        // Setup link delegator.
        item.find( 'a' ).on( "click", delegateLink );
        
        // Setup mouse handlers (bookmark forcer, pinner, etc.)
        installMouseHandlers(item);
        
        // Stick 'er in!
        if (append) {
            console.log("Append!")
            item.insertAfter('body>.newsContainer:last');
        } else {
            console.log("Prepend!")
            item.insertBefore( 'body>.newsContainer:first' );
            
            // Calculate the size and add it to our prepend scroll tally.
            //var verticalMargins = parseInt( item.css("marginBottom") ) + parseInt( item.css("marginTop") );
            addToScroll += item.height(); /* + verticalMargins; */
        }
    }
    
    // Check total number of excessive news items.
    var extraItems = $(newsContainerSelector).length - 60; //"Too many."
    if (extraItems > 0) {
        //console.log("Total items: ", $(newsContainerSelector).length, " extra items: ", extraItems)
        
        // Okay, we have too many damn items to display.  We need to remove a few.
        //
        // The assumption here is this will never be on the initial load; it will
        // always occur during a manual append or prepend.
        if (append) {
            var itemsOnTop = $('body>.newsContainer:lt(' + extraItems + '):not(#model)');
            console.log("# Items to remove on the top:", itemsOnTop.length)
            
            // We have to iterate over all the items to get an accurate height.
            var myItem = itemsOnTop;
            itemsOnTop.each(function( index ) {
                //console.log( index + ": " + this );
                addToScroll -= $(this).height();
            });
            
            removeMatchingItems(itemsOnTop);
            navigator.qt.postMessage( 'removeNewsTop ' + itemsOnTop.length );
        } else {
            var itemsOnBottom = $('body>.newsContainer:gt(-' + (extraItems + 1) + '):not(#model)');
            //console.log("# Items to remove on the bottom:", itemsOnBottom.length)
            removeMatchingItems(itemsOnBottom);
            navigator.qt.postMessage( 'removeNewsBottom ' + itemsOnBottom.length );
        }
    }
    
    console.log("first news id in this feed ", firstNewsID);
    
    var myTopBookmark = $('#' + idToHtmlId(-1) );
    var topBookmarkIsEnabled = myTopBookmark.css('display') !== 'none';
    if (firstNewsID === -1) {
        // No bookmark, so top bookmark should be visible.
        console.log("No bookmark  (or it's all news!)")
        if (!topBookmarkIsEnabled) {
            console.log("Enabling the TOP bookmark!");
            myTopBookmark.css('display', 'block');
            addToScroll += myTopBookmark.height();
        }
    } else {
        var firstIDInView = htmlIdToId( $(newsContainerSelector).attr('id') );
        console.log("First id in view", firstIDInView)
        
        if (!topBookmarkIsEnabled && (firstNewsID == firstIDInView)) {
            console.log("Enabling the TOP bookmark!");
            myTopBookmark.css('display', 'block');
            addToScroll += myTopBookmark.height();
        } else if (topBookmarkIsEnabled && (firstNewsID != firstIDInView)) {
            console.log("We can DISABLE the top bookmark now!");
            console.log("at my restaurant, I no give SHIT about top bookmark!!!!")
            addToScroll -= myTopBookmark.height();
            myTopBookmark.css('display', 'none');
        }
    }
    
    // Scroll back down if we added a bunch of old news at the top, or scroll up
    // if we removed items at the top.
    if ((!append && addToScroll > 10) ||
        (append && addToScroll < 10)) {
        var newScroll = currentScroll + addToScroll;
        if (newScroll < 0) {
            newScroll = 0;
        }
        
        console.log("addToScroll ", addToScroll, " new scroll: ", newScroll)
        $(document).scrollTop( newScroll );
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
    
    var elementId = '#' + idToHtmlId( id );
    var scrollTo = $( elementId ).offset().top;
    
    //console.log("jump to: ", elementId, "scrolling to: ", scrollTo);
    
    //navigator.qt.postMessage( 'scrollToPosition ' + scrollTo );
    $(document).scrollTop( scrollTo );
}

// Draws a bookmark on the given news container ID.
function drawBookmark(id) {
    console.log("draw bookmark: ", id)
    
    // Remove any existing bookmark(s).
    $( ".bookmarked" ).removeClass('bookmarked');
    
    // Add bookmark.
    var elementId = '#' + idToHtmlId(id);
    //console.log("adding bookmarked class to: ", elementId);
    $( elementId ).addClass('bookmarked');
    
    resizeBottomSpacer();
}


// Both draw the bookmark AND jump to it!  In ONE SHOT!!  WOW!
var bookmarkIdWeAreJumpingTo = -100;
function drawBookmarkAndJumpTo(id) {
    console.log("drawBookmarkAndJumpTo", id)
    bookmarkIdWeAreJumpingTo = id;
    drawBookmarkAndJumpToJumpingToId();
}

// Internal method for above function.
function drawBookmarkAndJumpToJumpingToId() {
    console.log("Draw and jumping to jump jump")
    if (isInProgress) {
        window.setTimeout(function() {
            drawBookmarkAndJumpToJumpingToId();
        }, 1);
        
        return;
    }
    
    //console.log("Jump out complete: ", bookmarkIdWeAreJumpingTo)
    
    // If there's a bookmark, jump to it!
    if (bookmarkIdWeAreJumpingTo !== -100) {
        // Draw our bookmark and jump to it!
        console.log("Draw bookmark & jump to: ", bookmarkIdWeAreJumpingTo)
        drawBookmark(bookmarkIdWeAreJumpingTo);
        jumpToBookmark();
        
        // Reset.
        bookmarkIdWeAreJumpingTo = -100;
    }
    
    // Tell NewsView that we're ready to ROCK and ROLL.
    navigator.qt.postMessage( 'drawBookmarkAndJumpToFinished' );
}

function jumpToBookmark() {
    //console.log("Jump to bookmark");
    
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
        var lastVeryBottom = 0;
        
        var checkScrollPosition = function() {
            var scrollTop =  $(document).scrollTop();
            
            // If the user hasn't scrolled, check bottom and bail.
            if (prevScrollTop === scrollTop) {
                
                // If we're at the bottom, always trigger the callback.
                var bottom = $document.height() - windowHeight - distance - $( '#bottom' ).height();
                if (scrollTop >= bottom) {
                    // Only proceed with the callback if it's been more than 5 seconds since we last
                    // hit bottom and hadn't scrolled.
                    var now =  Date.now();
                    if (now >= lastVeryBottom + 5000) {
                        //console.log("at bottom!")
                        lastVeryBottom = now;
                        bottomCallback();
                    }
                }
                
                return;
            }
            
            lastVeryBottom = 0; // Now that we've scrolled, clear this timer.
            
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
            console.log("SET BOOKMKAR! ", nextItem.attr('id'))
            navigator.qt.postMessage( 'setBookmark ' + htmlIdToId(nextItem.attr('id')) );
            
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
    
    // Setup the bookmark forcer on the top bookmark.
    installMouseHandlers('#topBookmark');
});
