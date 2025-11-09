/**
  This is Fang's Javascript logic.  But I mean, you knew that.  DUH!
  */

// Selects all news containers
let newsContainerSelector = 'body>#newsView>.newsContainer:not(#model)';

// This will be reset later.
let windowHeight = 50000;

// Current mode
let currentMode = "newsView";

// Set to true when there's no more news to load.
let atNewsEnd = false;

// Websocket
let wsUri = "ws://localhost:2842";
let websocket = null;
let websocketRestartTimerID = null;
const websocketRestartTimeoutMs = 250;

// Call this to connect to Fang's WebSocket.
function initWebSocket()
{
    try {
        if (typeof MozWebSocket == 'function') {
            WebSocket = MozWebSocket;
        }

        if ( websocket && websocket.readyState === 1 ) {
            websocket.close();
        }

        websocket = new WebSocket( wsUri );
        websocket.onopen = function (evt) {
            console.log("WebSocket: CONNECTED");

            // Let Fang know we're good n' ready!
            sendCommand("pageLoaded", "");
        };
        websocket.onclose = function (evt) {
            console.log("WebSocket: DISCONNECTED");

            // TODO: Add timer with backoff so we don't always try to reconnect ASAP.

            if (!websocketRestartTimerID) {
                websocketRestartTimerID = setTimeout(() => {
                    console.log("Reconnecting WebSocket...");
                    initWebSocket();
                    websocketRestartTimerID = null;
                }, websocketRestartTimeoutMs);
            } else {
                console.log("Already restarting WebSocket.")
            }
        };
        websocket.onmessage = function (evt) {
            //console.log( "WebSocket message received :", evt.data );
            processMessage(evt.data);
        };
        websocket.onerror = function (evt) {
            console.log('ERROR: ' + evt.data);
        };
    } catch (exception) {
        console.log('WebSocket ERROR: ' + exception);
    }
}

// Ends the WebSocket session.
function stopWebSocket() {
    if (websocket) {
        websocket.close();
        websocket = null;
    }
}

// Send a command to the server.
function sendCommand(command, data)
{
    websocket.send( command + ' ' + data );
}

// Fang sent us a message, horray!
function processMessage(message)
{
    let spaceIndex = message.indexOf( ' ' );
    if (spaceIndex < 0) {
        console.log("Error! Could not understand message: ", message);

        return;
    }

    let command = message.substring(0, spaceIndex);
    let data = message.substring(spaceIndex + 1);

    //console.log("Command:", '[' + command + ']')
    //console.log("Data:", '[' + data + ']')


    if ('load' === command) {
        loadNews(data);
        atNewsEnd = false;
    } else if ('loadEmpty' === command) {
        atNewsEnd = true;
    } else if ('drawBookmark' === command) {
        drawBookmark(data);
    } else if ('updatePin' === command) {
        setUpdatePin(data);
    } else if ('windowHeight' === command) {
        setWindowHeight(data);
    } else if ('updateCSS' === command) {
        updateCSS(JSON.parse(data));
    } else if ('jumpToBookmark' === command) {
        jumpToBookmark();
    } else if ('jumpNext' === command) {
        jumpNextPrev(true);
    } else if ('jumpPrevious' === command) {
        jumpNextPrev(false);
    } else if ('showNews' === command) {
       setMode('newsView');
    } else if ('showWelcome' === command) {
       setMode('welcome');
    } else if ('forceBottomCheck' === command) {
        // Forces a bottom check.  (Used when new news is added.)
        if (isAtBottom(distance)) {
            loadNext();
        }
    }
}


function loadNews(json)
{
    // Might consider an evil eval() alternative if needed.
    let newsObject = JSON.parse( json );
    //console.log("loadNews: ", newsObject);

    setWindowHeight(newsObject.windowHeight);

    if ('initial' === newsObject.mode) {
        // Redo the view.
        setMode('newsView');
        clearNews();
        updateCSS(newsObject.css);
    }

    // Append or prepend?
    let toAppend = 'prepend' !== newsObject.mode;

    // Add all our news!
    appendNews(toAppend, newsObject.firstNewsID, newsObject.news);

    // If we have a new bookmark, draw it and jump there.
    if (newsObject.bookmark) {
        drawBookmarkAndJumpTo(newsObject.bookmark);
    }

    sendCommand('loadComplete');
}


function setUpdatePin(json)
{
    let pinObject = JSON.parse( json );
    updatePin(pinObject.id, pinObject.pinned);
}

function updateCSS(bodyClassList)
{
    // Clear the current styles.
    clearBodyClasses();

    // Add 'em!
    for (let i = 0; i < bodyClassList.length; i++) {
        addBodyClass(bodyClassList[i]);
    }
}

function setMode(mode)
{
    if (mode === currentMode) {
        return;
    }

    console.log("Switching mode to: ", mode);
    currentMode = mode;

    // Switch out the HTML
    if ('newsView' == currentMode) {
        $('#welcome').hide();
        $('#newsView').show();
        jumpToBookmark();
    } else if ('welcome' == currentMode) {
        $('#newsView').hide();
        $('#welcome').show();
        $(document).scrollTop(0); // Scroll back up

        sendCommand('loadComplete'); // Send a load complete
    }
}


// Returns true if we're at the bottom of the document.
// "distance" is the fudge factor: bottom will be triggered if it's y position is
// within distance from bottm
function isAtBottom(distance) {
    let bottom = $(document).height() - windowHeight - distance;
    let ret = $(document).scrollTop() >= bottom;
    //console.log("Is at bottom? bottom y: ", bottom, " scrollTop: ", $(document).scrollTop(), " ret: ", ret)
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
    if (id === -1) {
        return 'topBookmark';
    } else {
        return 'NewsItem_' + id;
    }
}

function htmlIdToId(htmlID) {
    if (htmlID === 'topBookmark') {
        return -1;
    } else {
        return htmlID.replace('NewsItem_', '');
    }
}

// Intercept clix.
function delegateLink() {
    sendCommand( 'openLink', $(this).attr('href')) ;
    return false; // Don't propogate link.
};

// Given a parent element, setup the bookmark forcer and pin handler.
function installMouseHandlers(parentElement) {
    // Setup manual bookmarks.
    $(parentElement).find( '.stripe' ).on( "click", function() { 
        let elementID = $(this).parent().parent().attr( 'id' );

        sendCommand( 'forceBookmark', htmlIdToId(elementID) );
    } );

    // Setup the pin... pinner?  Pinteresting.
    $(parentElement).find( '.pin' ).on( "click", function() {
        let element = $(this).parent().parent();
        let isPinned = element.find( '.pin' ).hasClass( 'pinned' );

        sendCommand('setPin', htmlIdToId( element.attr( 'id' ) ) + ' ' + (+!isPinned)); // Unary + operator converts to number :)
    } );
}

// Appends (or prepends) a news item.
function appendNews(append, firstNewsID, newsList) {
    // Unescape newlines.  (This allows pre tags to work.)
    //jsonNews = jsonNews.replace(/[\u0018]/g, "\n");
    
    // Unroll the JSON string into a Javascript object.
    //let newsList = eval('(' + jsonNews + ')');
    //console.log("News list: ", newsList);
    
    // Remember where we are.
    let currentScroll = $(document).scrollTop();
    let addToScroll = 0;
    
    for (let i = 0; i < newsList.length; i++) {
        let newsItem = newsList[i];
        //console.log("news item:", newsItem);
        
        // Copy the model.
        let item = $( 'body>#newsView>.newsContainer#model' ).clone();
        
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
            item.insertAfter('body>#newsView>.newsContainer:last');
        } else {
            console.log("Prepend!")
            item.insertBefore( 'body>#newsView>.newsContainer:first' );
            
            // Calculate the size and add it to our prepend scroll tally.
            //let verticalMargins = parseInt( item.css("marginBottom") ) + parseInt( item.css("marginTop") );
            addToScroll += item.height(); /* + verticalMargins; */
        }
    }
    
    // Check total number of excessive news items.
    let extraItems = $(newsContainerSelector).length - 60; //"Too many."
    if (extraItems > 0) {
        //console.log("Total items: ", $(newsContainerSelector).length, " extra items: ", extraItems)
        
        // Okay, we have too many damn items to display.  We need to remove a few.
        //
        // The assumption here is this will never be on the initial load; it will
        // always occur during a manual append or prepend.
        if (append) {
            let itemsOnTop = $('body>#newsView>.newsContainer:lt(' + extraItems + '):not(#model)');
            console.log("# Items to remove on the top:", itemsOnTop.length)
            
            // We have to iterate over all the items to get an accurate height.
            let myItem = itemsOnTop;
            itemsOnTop.each(function( index ) {
                //console.log( index + ": " + this );
                addToScroll -= $(this).height();
            });
            
            removeMatchingItems(itemsOnTop);
            sendCommand( 'removeNewsTop', itemsOnTop.length );
        } else {
            let itemsOnBottom = $('body>#newsView>.newsContainer:gt(-' + (extraItems + 1) + '):not(#model)');
            //console.log("# Items to remove on the bottom:", itemsOnBottom.length)
            removeMatchingItems(itemsOnBottom);
            sendCommand( 'removeNewsBottom', itemsOnBottom.length );
        }
    }
    
    console.log("first news id in this feed ", firstNewsID);
    
    let myTopBookmark = $('#' + idToHtmlId(-1) );
    let topBookmarkIsEnabled = myTopBookmark.css('display') !== 'none';
    if (firstNewsID === -1) {
        // No bookmark, so top bookmark should be visible.
        console.log("No bookmark  (or it's all news!)")
        if (!topBookmarkIsEnabled) {
            console.log("Enabling the TOP bookmark!");
            myTopBookmark.css('display', 'block');
            addToScroll += myTopBookmark.height();
        }
    } else {
        let firstIDInView = htmlIdToId( $(newsContainerSelector).attr('id') );
        console.log("First id in view", firstIDInView)
        
        if (!topBookmarkIsEnabled && (firstNewsID === firstIDInView)) {
            console.log("Enabling the TOP bookmark!");
            myTopBookmark.css('display', 'block');
            addToScroll += myTopBookmark.height();
        } else if (topBookmarkIsEnabled && (firstNewsID !== firstIDInView)) {
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
        let newScroll = currentScroll + addToScroll;
        if (newScroll < 0) {
            newScroll = 0;
        }
        
        console.log("addToScroll ", addToScroll, " new scroll: ", newScroll)
        $(document).scrollTop( newScroll );
    }
}

function removeMatchingItems(item) {
    // Iterate over all items that match.
    for ( let i = 0; i < item.length; i++ ) {
        let current = item[i];
        
        // DELETE!
        current.parentNode.removeChild( current );
    }
}

// Clears out all the news from the view.
function clearNews() {
    removeMatchingItems( $(newsContainerSelector) );

    $(document).scrollTop( 0 );
}

// Returns the last news container.
function getLastNewsContainer() {
    return $(newsContainerSelector).last();
}

// Scrolls to the element with the given ID.
function jumpTo(id) {
    //console.log("Jump to: ", id)
    
    let elementId = '#' + idToHtmlId( id );
    let scrollTo = $( elementId ).offset().top;
    
    //console.log("jump to: ", elementId, "scrolling to: ", scrollTo);

    $(document).scrollTop( scrollTo );
}

// Draws a bookmark on the given news container ID.
function drawBookmark(id) {
    //console.log("draw bookmark: ", id)
    
    // Remove any existing bookmark(s).
    $( ".bookmarked" ).removeClass('bookmarked');
    
    // Add bookmark.
    let elementId = '#' + idToHtmlId(id);
    //console.log("adding bookmarked class to: ", elementId);
    $( elementId ).addClass('bookmarked');
}


// Both draw the bookmark AND jump to it!  In ONE SHOT!!  WOW!
let bookmarkIdWeAreJumpingTo = -100;
function drawBookmarkAndJumpTo(id) {
    console.log("drawBookmarkAndJumpTo", id)
//    bookmarkIdWeAreJumpingTo = id;
//    drawBookmarkAndJumpToJumpingToId();

    drawBookmark(id);
    jumpToBookmark();
}


function jumpToBookmark() {
    console.log("Jump to bookmark");
    
    // If there's a bookmark, this will jump to it.
    let element = $( ".bookmarked > .bookmark" );
    if (!element || element.length === 0) {
        console.log("No bookmark found, jumping to top")
        $(document).scrollTop( 0 );
        return;
    }

    // Check if last element is the bookmark.
    let lastIsBookmark = getLastNewsContainer().hasClass("bookmarked");
    let scrollTo = element.offset().top - 10;
    
    //console.log("Scroll to: ", scrollTo, " window height: ", windowHeight, " document h: ", $(document).height());
    
    // Set max jump.
    if (scrollTo > $(document).height() - windowHeight) {
        scrollTo = $(document).height() - windowHeight;

        // Rewind slightly if the last item isn't bookmarked (so the user can scroll to it.)
        if (!lastIsBookmark) {
            let bookmark = getLastNewsContainer().find('.bookmark');
            if (bookmark.length) {
                scrollTo -= bookmark.height();
            }
        }
    }
    
    $(document).scrollTop( scrollTo );
}

// Updates the pin status on newsID
function updatePin(newsID, pin) {
    //console.log("Update pin: ", newsID, " set to: ", pin);

    let element = $('#' + idToHtmlId( newsID ));
    if (!element.length) {
        return; // Not found.
    }

    if (pin) {
        element.find( '.pin' ).addClass('pinned');
    } else {
        element.find( '.pin' ).removeClass('pinned');
    }
}

// UTILITY: Returns true if the element is a real news item,
//          rather than a model or chrome component.
function isNewsContainer(element) {
    let ret = element.hasClass('newsContainer') && element.attr('id') !== 'model';
    //console.log("Is news container: ", element, " :: ", ret)
    return ret;
}

// Returns the next news item in our little list.
function nextNewsContainer(element) {
    //console.log("nextNewsContainer for: ", element)

    // Loop until we find another valid news container.
    let item = element;
    while (item.length) {
        item = item.next();
        //console.log("Examining item: ", item.attr('id'))
        if (isNewsContainer(item)) {
            //console.log("nextNewsC took this: ", element.attr('id'), " and spat out this: ", item)
            return item;
        }
    }
    
    return null; // :(
}

// Or how about the previous one, why not?
function prevNewsContainer(element) {
    //console.log("prevNewsContainer for: ", element)
    
    // Loop backwards until we find another valid news container.
    let item = element;
    while (item.length) {
        item = item.prev();
        //console.log("Examining item: ", item.attr('id'))
        if (isNewsContainer(item)) {
            //console.log("prevNewsC took this: ", element.attr('id'), " and spat out this: ", item)
            return item;
        }
    }
    
    return null; // :(
}

// UTILITY: Returns true if the element is above the scroll position, else false.
function isAboveScroll(element) {
    //console.log("Is above scroll: ", element)

    // We don't want to include the bookmark space this calculation.
    let bookmarkHeight = 0;
    let bookmark = element.find('.bookmark');
    if (bookmark.length) {
        bookmarkHeight = bookmark.height() + 15; // for consistent results
    }

    //console.log("Bookmark Height: ", bookmarkHeight);

    let allHeight = element.offset().top + element.height() - bookmarkHeight;
    let ret = $(window).scrollTop() >= allHeight;
    
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
    let item = $(newsContainerSelector);

    while (item !== null && item.length) {
        if (!isAboveScroll(item))
            return item;
        
        item = nextNewsContainer(item);
    }
    
    // Just return the last item, then?
    return getLastNewsContainer();
}

// Jumps to the next or previous item on the screen.
function jumpNextPrev(jumpNext) {
    let current = getFirstVisible();
    
    //console.log("JNP: first visible: ", current)
    //console.log("Is above scroll: ", isAboveScroll(current))
    
    if (!current.length) {
        return;
    }
    
    // Either go to the next item, or jump back up to the current one.
    let jumpTo = current;
    if (jumpNext) {
        jumpTo = nextNewsContainer(jumpTo);
        //console.log("Next news container: ", jumpTo);
        if (jumpTo === null) {
            // We didn't find a last news item, so jump to the last bookmark instead.
            jumpTo = current.find(".bookmark > .stripe");
            //console.log("Jumping to last bookmark: ", jumpTo);
        }
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
    
    if (jumpTo === null || !jumpTo.length) {
        console.log("No valid jumpTo item! Bail!");
        return;
    }

    $(document).scrollTop( jumpTo.offset().top );
}

// Called by QML to tell us the height of the window.
function setWindowHeight(height) {
    console.log("height is now: ", height)
    windowHeight = height;
}

// Main method
$(document).ready(function() {
    // Start our WebSocket client
    initWebSocket();

    ////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * distance: pixels from bottom that triggers callback.
     * interval is how often the check will run (in milliseconds; 250-1000 is reasonable).
     */
    function watchScrollPosition(bottomCallback, topCallback, bookmarkCallback, distance, interval) {
        let $document = $(document);
        
        let prevScrollTop = 0;
        let lastVeryBottom = 0;
        
        let checkScrollPosition = function() {
            if (currentMode != 'newsView') {
                return;
            }

            let scrollTop =  $(document).scrollTop();
            
            // If the user hasn't scrolled, check bottom and bail.
            if (prevScrollTop === scrollTop) {
                // Trigger callback if we're at the bottom.
                if (isAtBottom(distance)) {
                    // Only proceed with the callback if it's been more than 5 seconds since we last
                    // hit bottom and hadn't scrolled.
                    let now =  Date.now();
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
            let top = distance;
            if (scrollTop <= top) {
                console.log("Top callback")
                topCallback();
            }
            
            // Check bottom (note: calculation MUST be done after topCallback()!!!!)
            if (isAtBottom(distance)) {
                bottomCallback();
            }
            
            bookmarkCallback();
            
            prevScrollTop = scrollTop;
        };

        setInterval(checkScrollPosition, interval);
    }
    
    // Adjust the bookmark if necessary.
    function checkBookmark() {
        // console.log("check bookmark")
        bookmarkAll = false; // If true, bookmark every single item.

        if ($(newsContainerSelector).length === 0) {
            console.log("checkBookmark: NO NEWS CONTAINERS to deal with, no need to set bookmark")
            
            return;
        }


        // If there's nothing more to load and we've scrolled alllll the way down, bookmark the last item.
        if (atNewsEnd && isAtBottom(25)) {
            //console.log("checkBookmark: At bottom, bookmark all");
            bookmarkAll = true;
        }
        
        // Start at the current bookmark.
        let bookmarkedItem = $( 'body>.bookmarked' );
        //console.log("Current bookmark: ", bookmarkedItem)
        
        // Check if the current bookmark is valid.
        if (!bookmarkAll && bookmarkedItem.length && !isAboveScroll(bookmarkedItem)) {
            // console.log("checkBookmark Currently bookmarked item is not above scroll.  Goodbye!", bookmarkedItem.attr('id'));
            
            return;
        }
        
        // If there's a bookmark, get the next item.  Otherwise, get the first news container.
        let nextItem = bookmarkedItem.length ? nextNewsContainer(bookmarkedItem) : $(newsContainerSelector);

        //console.log("Bookmark is above scroll! ", bookmarkedItem);
        //console.log("Next available news item is: ", nextItem);
        
        while (nextItem !== null && nextItem.length >= 1) {
            // Nothing more to do.
            if (!isAboveScroll(nextItem) && !bookmarkAll) {
                // console.log("checkBookmark: item not above scroll:", nextItem.attr('id'))
                
                break;
            }
            
            // Move the bookmark down one.
            // console.log("checkBookmark: set bookmark to ", nextItem.attr('id'))
            sendCommand( 'setBookmark', htmlIdToId(nextItem.attr('id')) );
            
            // Continue to next item.
            nextItem = nextNewsContainer(nextItem);
        }
    }
    
    function loadNext() {
        //console.log("loadNext")
        sendCommand( 'loadNext', '' );
    }
    
    function loadPrevious() {
        //console.log("loadPrevious")
        sendCommand( 'loadPrevious', '' );
    }
    
    
    /**
     * Timestamp update timer.
     */
    function updateTimestamps(interval) {
        let $document = $(document);
        
        // Grab each timestamp, then re-call formatDateSimply() on it.
        let updateTimestampsCallback = function() {
            let item = $(newsContainerSelector);
            while (item.length) {
                //console.log("Examining item: ", item.attr('id'))
                if (isNewsContainer(item)) {
                    // Hidden timestamp!  (Shh.)
                    let timestamp = item.find( '.timestamp' ).html();
                    item.find( '.date' ).html( formatDateSimply(timestamp) );
                }
                item = item.next();
            }
        };

        setInterval(updateTimestampsCallback, interval);
    }
    
    /**
     * Initial setup.
     */
    
    // Poll for scroll position every 250 ms.
    watchScrollPosition(loadNext, loadPrevious, checkBookmark, 250, 250);
    
    // Update timestamps every 10 seconds.
    updateTimestamps(10000);
    
    // Setup the bookmark forcer on the top bookmark.
    installMouseHandlers('#topBookmark');

    // Setup link delegator on all non-news items.
    $(document).find( 'a' ).on( "click", delegateLink );
});
