/**
  This is Fang's Javascript logic.  But I mean, you knew that.  DUH!
  */

// Main method
$(document).ready(function() {
    /**
     * distance: pixels from bottom that triggers callback.
     * interval is how often the check will run (in milliseconds; 250-1000 is reasonable).
     */
    function watchScrollPosition(bottomCallback, topCallback, bookmarkCallback, distance, interval) {
        var $window = $(window),
            $document = $(document);
        
        var prevScrollTop = $window.scrollTop();
        
        var checkScrollPosition = function() {
            console.log("Well hello")
            // If the user hasn't scrolled, there's nothing to do.
            if (prevScrollTop == $window.scrollTop())
                return;
            
            // Check top.
            var top = distance;
            if ($window.scrollTop() <= top) {
                topCallback();
            }

            // Check bottom (note: calculation MUST be done after topCallback()!!!!)
            var bottom = $document.height() - $window.height() - distance;
            if ($window.scrollTop() >= bottom) {
                bottomCallback();
            }
            
            bookmarkCallback();
            
            prevScrollTop = $window.scrollTop();
        };

        setInterval(checkScrollPosition, interval);
    }
    
    function atTop() {
        console.log("You're at the top!")
        // Prepend.  Must do these one at a time.
        var totalHeight = $(document).scrollTop();
        for (var i = 0; i < 3; i++) {
            var newItem = $( "<div class='newsContainer'></div>" );
            newItem.insertBefore( "body>.newsContainer:first-child" );
            
            var verticalMargins = parseInt( newItem.css("marginBottom") ) + parseInt( newItem.css("marginTop") );
            totalHeight += verticalMargins + newItem.height();
        }
        
        // Reset scroll position so it looks like we haven't moved.
        // This isn't *quite* right...
        $(document).scrollTop( totalHeight );
    }
    
    function atBottom() {
        console.log("You've hit bottom.");
        
        // Add a new batch.
        
        //
        // TODO: figure out how to signal to request for more
        //
        
        $( "<div class='newsContainer'></div><div class='newsContainer'></div><div class='newsContainer'></div>" ).insertAfter( "body>.newsContainer:last-child" );
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
        var bookmarkedItem = $( "#bookmarked" );
        
        // Check if the bottom of the bookmarked item is above the scroll level.
        // If not, bail now since the bookmark won't be changed.
        if (!isAboveScroll(bookmarkedItem))
            return;
        
        //console.log("Bookmark is above scroll!  It may require changing:", bookmarkedItem.next().length);
        
        // Go through all the next items.
        var nextItem = bookmarkedItem.next();
        while (true) {
            if (nextItem.length < 1) {
                console.log("We've bookmarked the final item, sir.");
                
                break;
            }
            
            // Nothing more to do.
            if (!isAboveScroll(nextItem))
                break;
            
            // Move the bookmark down one.
            setBookmark(nextItem);
            
            // Continue to next item.
            nextItem = nextItem.next();
        }
    } 
    
    watchScrollPosition(atBottom, atTop, checkBookmark, 250, 250);
    
    // Scroll down a bit.
    $(document).scrollTop(300);
});
