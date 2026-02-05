/**
  * Fang: Feed on news.
  *
  * This script is used to update the browser view with news feed data provided by a web server
  * and a websocket that live in the C++ layer.
  */

// Config option fetched from Fang.
let config = null;

// Selects all news containers
let newsContainerSelector = 'body>#newsView>.newsContainer:not(#model)';

// Current mode
let currentMode = "newsView";

// Websocket
let websocket = null;
let websocketRestartTimerID = null;
const websocketRestartTimeoutMs = 250;

// Prefetch data for loading an update
let prefetchPromise = null;
let prefetchedData = null;
let isPrefetching = false;
const PREFETCH_THRESHOLD = 0.7; // Start prefetch at 70% scroll

// Concurrent load request guard (prevent duplicate NewsItems.)
let isLoadingNews = false;

/**
  * Establishes a websocket connection to the backend.
  */
function initWebSocket()
{
    try {
        if (typeof MozWebSocket == 'function') {
            WebSocket = MozWebSocket;
        }

        if ( websocket && websocket.readyState === 1 ) {
            websocket.close();
        }

        websocket = new WebSocket(`ws://localhost:${config.webSocketPort}`);
        websocket.onopen = function (evt) {
            console.log("WebSocket: CONNECTED");
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
            processMessage(evt.data);
        };
        websocket.onerror = function (evt) {
            console.log('ERROR: ' + evt.data);
        };
    } catch (exception) {
        console.log('WebSocket ERROR: ' + exception);
    }
}

/**
 * Ends the WebSocket session.
 */
function stopWebSocket() {
    if (websocket) {
        websocket.close();
        websocket = null;
    }
}

/**
  * Send a command to the websocket server.
  */
function sendCommand(command, data)
{
    websocket.send( command + ' ' + data );
}

/**
  * Processes a message from the websocket server.
  */
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

    if ('feedChanged' === command) {
        requestNews('initial');
    } else if ('drawBookmark' === command) {
        drawBookmark(data);
    } else if ('jumpToBookmark' === command) {
        jumpToBookmark();
    } else if ('jumpNext' === command) {
        jumpNextPrev(true);
    } else if ('jumpPrevious' === command) {
        jumpNextPrev(false);
    } else if ('styleChanged' === command) {
        updateCSS();
    } else if ('showNews' === command) {
       setMode('newsView');
    } else if ('showWelcome' === command) {
       setMode('welcome');
    }
}

/**
  * Performs a GET request to the backend.
  * URL will be of the path /api/{method}/{params}
  *
  * Returns a Promise that will resolve to a Response.
  */
function apiGetRequest(method, params)
{
    let url = '/api/' + method;
    if (params) {
        url += '/' + params;
    }

    return fetch(url);
}

/**
  * Performs a POST request to the backend.
  * URL will be of the path /api/{method}
  * Post body will be the object
  *
  * Returns a Promise that will resolve to a Response.
  */
function apiPostRequest(method, object)
{
    let url = '/api/' + method;

    return fetch(url, {
                     method: "POST",
                     body: JSON.stringify(object)
                 });
}

/**
  * Loads news items from the backend and displays them.
  * Mode can be "initial", "prepend", or "append"
  */
function requestNews(mode)
{
    console.log("requestNews:", mode);

    // Clear prefetch on initial or prepend (feed change or scroll up)
    if (mode === 'initial' || mode === 'prepend') {
        clearPrefetch();
    }

    apiGetRequest('load', mode)
    .then((response) => response.json())
    .then((data) => {
              console.log("load news data:", data);
              if (data.showWelcome === true) {
                  setMode('welcome');
              } else {
                  setMode('newsView');

                  if ('initial' === data.mode) {
                      // Redo the view.

                      clearNews();
                  }

                  // Append or prepend?
                  let toAppend = 'prepend' !== data.mode;

                  // Add all our news!
                  appendNews(toAppend, data.firstNewsID, data.news);

                  // If we have a new bookmark, draw it and jump there.
                  if (data.bookmark) {
                      drawBookmark(data.bookmark);
                      jumpToBookmark();
                  }
              }
          })
    .finally(() => {
        isLoadingNews = false;
    });
}

/**
 * Clears prefetch state. Called when feed changes or on initial load.
 */
function clearPrefetch() {
    prefetchedData = null;
    prefetchPromise = null;
    isPrefetching = false;
    isLoadingNews = false;
}


/**
  * Requests updated CSS from the backend and applies it.
  * Note: This is required to sync the light/dark modes and font sizes.
  * Returns a Promise that resolves when CSS has been applied.
  */
function updateCSS()
{
    return apiGetRequest('css')
    .then((response) => response.json())
    .then((data) => {
              console.log("Update css:", data);
              // Clear the current styles.
              clearBodyClasses();

              // Add 'em!
              for (let i = 0; i < data.length; i++) {
                  addBodyClass(data[i]);
              }
          });
}

/**
  * Switches between the news and welcome modes.
  * Valid modes: 'newsView', 'welcome'
  */
function setMode(mode)
{
    if (mode === currentMode) {
        return;
    }

    console.log("setMode: ", mode);
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
    }
}


/**
  * Returns true if we're at the bottom of the document.
  * "distance" is the fudge factor: bottom will be triggered if it's y position is
  * within distance from bottm
  */
function isAtBottom(distance)
{
    let bottom = $(document).height() - window.innerHeight - distance;
    let ret = $(document).scrollTop() >= bottom;
    //console.log("Is at bottom? bottom y: ", bottom, " scrollTop: ", $(document).scrollTop(), " ret: ", ret)
    return ret;
}

/**
  * Converts one of Fang's database IDs to an HTML news item id string.
  */
function idToHtmlId(id)
{
    if (id === -1) {
        return 'topBookmark';
    } else {
        return 'NewsItem_' + id;
    }
}

/**
  * Converts an HTML id string for a news item to a database ID.
  */
function htmlIdToId(htmlID)
{
    if (htmlID === 'topBookmark') {
        return -1;
    } else {
        return htmlID.replace('NewsItem_', '');
    }
}

/**
  * Click handler for URLs.
  * Sends the link URL to the backend to decide what to do (open default browser, etc.)
  */
function handleLinkClick(event)
{
    const link = event.target.closest('a');
    if (!link) {
        // Not a link, allow it to it propagate.
        return true;
    }

    const url = link.getAttribute('href');
    if (url) {
        apiPostRequest('open_link', { 'url': url });
    }
    event.preventDefault();
    return false; // Don't propagate.
}

/**
  * Sets up event delegation for click handlers on the news view.
  * This replaces per-item event handlers with a single delegated handler.
  */
function initEventDelegation()
{
    const newsView = document.getElementById('newsView');
    if (!newsView) return;

    newsView.addEventListener('click', function(event) {
        const target = event.target;

        // Force bookmark if user clicks on it.
        // Use closest() since clicks may land on child elements (.stripe_left, etc.)
        if (target.closest('.stripe')) {
            const container = target.closest('.newsContainer, .newsItemStyle');
            if (container) {
                const elementID = htmlIdToId(container.id);
                console.log('Force bookmark clicked: ID=' + elementID + ' container=' + container.id);
                apiGetRequest('force_bookmark', elementID);
            } else {
                console.log('Force bookmark: No container found for target', target);
            }
            return;
        }

        // Pin/unpin click.
        if (target.classList.contains('pin')) {
            const container = target.closest('.newsContainer');
            if (container) {
                const isPinned = target.classList.contains('pinned');
                const elementID = htmlIdToId(container.id);

                let apiResponse = isPinned
                    ? apiGetRequest('unpin', elementID)
                    : apiGetRequest('pin', elementID);

                apiResponse.then((response) => response.json()).then((data) => {
                    console.log("update pin data:", data);
                    updatePin(data.newsID, data.pinned);
                });
            }
            return;
        }

        // Links (requires special handling)
        const link = target.closest('a');
        if (link) {
            handleLinkClick(event);
        }
    });

    // Also take care of links in welcome section and other areas
    document.addEventListener('click', function(event) {
        const link = event.target.closest('a');
        if (link && !link.closest('#newsView')) {
            handleLinkClick(event);
        }
    });
}

/**
  * Appends (or prepends) news item(s) to the DOM via DocumentFragment batches.
  */
function appendNews(append, firstNewsID, newsList)
{
    if (newsList.length === 0) {
        // Bail early if there's nothing new.
        return;
    }

    // Remember where we are.
    let currentScroll = $(document).scrollTop();
    let addToScroll = 0;

    // Get the model element and container
    const model = document.querySelector('body>#newsView>.newsContainer#model');
    const container = document.getElementById('newsView');
    if (!model || !container) {
        // Possibly called too early?
        return;
    }

    // Create a DocumentFragment to batch DOM insertions
    const fragment = document.createDocumentFragment();
    const items = [];
    let skippedDuplicates = 0;

    for (let i = 0; i < newsList.length; i++) {
        let newsItem = newsList[i];
        const itemHtmlId = idToHtmlId(newsItem['id']);

        // IMPORTANT!!!!1 Skip any NewsItems that are already in the DOM.
        if (document.getElementById(itemHtmlId)) {
            console.log("appendNews: Skipping duplicate item id=" + newsItem['id']);
            skippedDuplicates++;
            continue;
        }

        // Clone the model
        const item = model.cloneNode(true);
        item.id = itemHtmlId;

        // Assign data.
        const linkEl = item.querySelector('.link');
        if (linkEl) {
            linkEl.setAttribute('href', newsItem['url']);
            linkEl.innerHTML = newsItem['title'];
        }

        const contentEl = item.querySelector('.content');
        if (contentEl) {
            contentEl.innerHTML = newsItem['content'];
        }

        const siteTitleEl = item.querySelector('.siteTitle');
        if (siteTitleEl) {
            siteTitleEl.innerHTML = newsItem['feedTitle'];
        }

        const timestampEl = item.querySelector('.timestamp');
        if (timestampEl) {
            timestampEl.innerHTML = newsItem['timestamp'];
        }

        const dateEl = item.querySelector('.date');
        if (dateEl) {
            dateEl.innerHTML = formatDateSimply(newsItem['timestamp']);
        }

        // Set pin
        if (newsItem['pinned']) {
            const pinEl = item.querySelector('.pin');
            if (pinEl) {
                pinEl.classList.add('pinned');
            }
        }

        items.push(item);
        fragment.appendChild(item);
    }

    // Log if we skipped any duplicates
    if (skippedDuplicates > 0) {
        console.log("appendNews: Skipped " + skippedDuplicates + " duplicate items");
    }

    // Insert all items at once
    if (append) {
        console.log("Append! Adding " + items.length + " items");
        // Find the last news container and insert after it
        const lastContainer = container.querySelector('.newsContainer:last-of-type');
        if (lastContainer && lastContainer.nextSibling) {
            container.insertBefore(fragment, lastContainer.nextSibling);
        } else {
            container.appendChild(fragment);
        }
    } else {
        console.log("Prepend!");
        // Find the first news container and insert before it
        const firstContainer = container.querySelector('.newsContainer:not(#model)');
        if (firstContainer) {
            container.insertBefore(fragment, firstContainer);
        } else {
            container.appendChild(fragment);
        }

        // Calculate scroll adjustment for prepended items
        for (let i = 0; i < items.length; i++) {
            addToScroll += items[i].offsetHeight;
            console.log("adding to scroll:", items[i].offsetHeight);
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
            console.log("# Items to remove on the top:", itemsOnTop.length);

            // We have to iterate over all the items to get an accurate height.
            itemsOnTop.each(function( index ) {
                //console.log( index + ": " + this );
                addToScroll -= $(this).height();
            });

            itemsOnTop.remove();
            sendCommand( 'removeNewsTop', itemsOnTop.length );
        } else {
            let itemsOnBottom = $('body>#newsView>.newsContainer:gt(-' + (extraItems + 1) + '):not(#model)');
            console.log("# Items to remove on the bottom:", itemsOnBottom.length);
            itemsOnBottom.remove();
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

/**
  * Clears out all the news from the view.
  */
function clearNews()
{
    $(newsContainerSelector).remove();

    $(document).scrollTop( 0 );
}

/**
  * Returns the last news container in the DOM.
  */
function getLastNewsContainer()
{
    return $(newsContainerSelector).last();
}

/**
  * Scrolls to the news item in the DOM with the given database ID.
  */
function jumpTo(id)
{
    //console.log("Jump to: ", id)

    let elementId = '#' + idToHtmlId( id );
    let scrollTo = $( elementId ).offset().top;

    //console.log("jump to: ", elementId, "scrolling to: ", scrollTo);

    $(document).scrollTop( scrollTo );
}

/**
  * Updates the DOM with a bookmark on the given news database ID.
  */
function drawBookmark(id)
{
    //console.log("draw bookmark: ", id)

    // Remove any existing bookmark(s).
    $( ".bookmarked" ).removeClass('bookmarked');

    // Add bookmark.
    let elementId = '#' + idToHtmlId(id);
    //console.log("adding bookmarked class to: ", elementId);
    $( elementId ).addClass('bookmarked');
}

/**
  * Scrolss to the currently bookmarked item (if any.)
  */
function jumpToBookmark()
{
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

    //console.log("Scroll to: ", scrollTo, " window height: ", window.innerHeight, " document h: ", $(document).height());

    // Set max jump.
    if (scrollTo > $(document).height() - window.innerHeight) {
        scrollTo = $(document).height() - window.innerHeight;

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

/**
  * Updates the DOM's pin status on news ID.
  */
function updatePin(newsID, pinned)
{
    //console.log("Update pin: ", newsID, " set to: ", pinned);

    let element = $('#' + idToHtmlId( newsID ));
    if (!element.length) {
        return; // Not found.
    }

    if (pinned) {
        element.find( '.pin' ).addClass('pinned');
    } else {
        element.find( '.pin' ).removeClass('pinned');
    }
}

/**
  * Returns true if the element is a real news item, rather than a model, chrome component, etc.
  */
function isNewsContainer(element) {
    let ret = element.hasClass('newsContainer') && element.attr('id') !== 'model';
    //console.log("Is news container: ", element, " :: ", ret)
    return ret;
}

/**
  * Returns the next news item the DOM.
  */
function nextNewsContainer(element)
{
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

/**
  * Returns the previous news item the DOM.
  */
function prevNewsContainer(element)
{
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

/**
  * Returns true if the element is entirely above the scroll position, else false.
  */
function isAboveScroll(element)
{
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

/**
  * Just like isAboveScroll(), but this only checks the top of the specified element.
  */
function isTopAboveScroll(element)
{
    //console.log("Is top above scroll: ", element)
    //console.log("isTopAboveScroll: Scroll top: ", $(window).scrollTop(), " elem offset and height: ", element.offset().top + element.height())

    return $(window).scrollTop() >= element.offset().top + 10;
}

/**
  * Returns the first visible news item.
  */
function getFirstVisible()
{
    // Go through all the next items.
    let item = $(newsContainerSelector);

    while (item !== null && item.length) {
        if (!isAboveScroll(item)) {
            return item;
        }

        item = nextNewsContainer(item);
    }

    // Just return the last item, then?
    return getLastNewsContainer();
}

/**
  * Jumps our scroll position to the next or previous item.
  * If jumpNext is true, jump to next item, otherwise jump to the previous one.
  */
function jumpNextPrev(jumpNext)
{
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

/**
  * Sets up the loading spinner to appear during fetch API calls.
  */
function initLoadingSpinner() {
    const GRACE_PERIOD = 150;     // Ms to wait before displaying timer for short requests
    const MIN_DISPLAY_TIME = 800; // Minimium ms to display timer
    let activeFetches = 0;
    let loadingStartTime = 0;
    let showTimer = null;

    const showLoadingSpinner = () => {
        activeFetches++;

        if (activeFetches === 1 && !showTimer) {
            // Show timer after grace period.
            showTimer = setTimeout(() => {
                loadingStartTime = Date.now();
                $('#loading-indicator').fadeIn(200);
                showTimer = null; // Timer has finished.
            }, GRACE_PERIOD);
        }
    };

    const hideLoadingSpinner = () => {
        activeFetches--;

        if (activeFetches <= 0) {
            activeFetches = 0; // Guard against negative count.

            if (showTimer) {
                // We've already stopped showing the timer, so end here.
                clearTimeout(showTimer);
                showTimer = null;
            } else if (loadingStartTime > 0) {
                // Fade out spinner after delay.
                const currentTime = Date.now();
                const elapsedTime = currentTime - loadingStartTime;
                const remainingTime = Math.max(0, MIN_DISPLAY_TIME - elapsedTime);

                setTimeout(() => {
                    // Ignore timeout unless it's the final active fetch.
                    if (activeFetches === 0) {
                        $('#loading-indicator').fadeOut(400);
                    }
                }, remainingTime);
            }
        }
    };

    // Patch the native Fetch API
    const originalFetch = window.fetch;
    window.fetch = async (...args) => {
        // Only show spinner for news load requests.
        const url = (typeof args[0] === 'string') ? args[0] : args[0].url;
        const shouldShowSpinner = url.includes('/api/load/');

        // Show, then hide the loader.
        if (shouldShowSpinner) {
            showLoadingSpinner();
        }
        try {
            const response = await originalFetch(...args);
            return response;
        } catch (error) {
            // Still hide even if the request fails
            throw error;
        } finally {
            if (shouldShowSpinner) {
                hideLoadingSpinner();
            }
        }
    };
}

/**
  * Creates a debounced version of a function.
  */
function debounce(func, wait) {
    let timeout;
    return function executedFunction(...args) {
        const later = () => {
            clearTimeout(timeout);
            func(...args);
        };
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
    };
}

/**
  * Window resize handler.
  * When the window is resized, jumps to bookmark after a short delay.
  */
$(window).resize(debounce(function() {
    // console.log("RESIZE");
    jumpToBookmark();
}, 50));

/**
  * Main method.
  */
$(document).ready(function() {
    // Fetch our config.
    // IMPORTANT: This must be done before attempting to connect to the websocket.
    apiGetRequest("config")
    .then((response) => response.json())
    .then((data) => {
              config = data;

              // Start our WebSocket client.
              initWebSocket();
          });

    // Setup loading spinner (can happen immediately).
    initLoadingSpinner();

    // Setup event delegation (replaces per-item event handlers).
    initEventDelegation();

    // Wait for CSS to load before loading news to avoid visual flash/glitch.
    updateCSS()
    .then(() => {
        console.log("CSS loaded, now loading news...");

        // Remove the css-loading class and continue with news load.
        document.body.classList.remove('css-loading');
        requestNews('initial');
    })
    .catch((error) => {
        console.error("Failed to load CSS:", error);

        // Well... we tried our best! Attempt to soldier on without CSS.
        // Remove the css-loading class and continue with news load.
        document.body.classList.remove('css-loading');
        requestNews('initial');
    });

    ////////////////////////////////////////////////////////////////////////////////////////////

    // Scroll watcher state
    let prevScrollTop = 0;
    let lastVeryBottom = 0;
    let scrollTicking = false;
    const SCROLL_DISTANCE = 250;

    /**
     * Returns the current scroll position as a percentage (0.0 to 1.0).
     */
    function getScrollPercent() {
        const scrollTop = $(document).scrollTop();
        const docHeight = $(document).height();
        const winHeight = window.innerHeight;
        const scrollable = docHeight - winHeight;
        if (scrollable <= 0) return 1.0;
        return Math.min(1.0, scrollTop / scrollable);
    }

    /**
     * Starts prefetching the next batch of news if not already prefetching.
     */
    function startPrefetch() {
        if (isPrefetching || prefetchedData !== null) {
            return; // Already prefetching or have prefetched data
        }

        console.log("Prefetching next batch...");
        isPrefetching = true;

        prefetchPromise = apiGetRequest('load', 'append')
            .then((response) => response.json())
            .then((data) => {
                console.log("Prefetch complete, cached", data.news ? data.news.length : 0, "items");
                prefetchedData = data;
                isPrefetching = false;
                return data;
            })
            .catch((error) => {
                console.log("Prefetch failed:", error);
                isPrefetching = false;
                prefetchPromise = null;
            });
    }

    /**
     * Checks scroll position and triggers appropriate callbacks.
     * Called on scroll events with requestAnimationFrame for smooth performance.
     */
    function checkScrollPosition() {
        if (currentMode != 'newsView') {
            return;
        }

        const scrollTop = $(document).scrollTop();

        // If the user hasn't scrolled, check bottom and bail.
        if (prevScrollTop === scrollTop) {
            // Trigger callback if we're at the bottom.
            if (isAtBottom(SCROLL_DISTANCE)) {
                // Only proceed with the callback if it's been more than 5 seconds since we last
                // hit bottom and hadn't scrolled.
                const now = Date.now();
                if (now >= lastVeryBottom + 5000) {
                    //console.log("at bottom!")
                    lastVeryBottom = now;
                    loadNext();
                }
            }

            return;
        }

        lastVeryBottom = 0; // Now that we've scrolled, clear this timer.

        // Prefetch when user is 70% scrolled down
        const scrollPercent = getScrollPercent();
        if (scrollPercent >= PREFETCH_THRESHOLD && !prefetchedData && !isPrefetching) {
            startPrefetch();
        }

        // Check top.
        if (scrollTop <= SCROLL_DISTANCE) {
            console.log("Top callback")
            loadPrevious();
        }

        // Check bottom (note: calculation MUST be done after loadPrevious()!!!!)
        if (isAtBottom(SCROLL_DISTANCE)) {
            loadNext();
        }

        checkBookmark();

        prevScrollTop = scrollTop;
    }

    /**
     * Scroll event handler using requestAnimationFrame for smooth 60fps updates.
     */
    function onScroll() {
        if (!scrollTicking) {
            requestAnimationFrame(() => {
                checkScrollPosition();
                scrollTicking = false;
            });
            scrollTicking = true;
        }
    }

    // Adjust the bookmark if necessary.
    function checkBookmark() {
        // console.log("check bookmark")
        let bookmarkAll = false; // If true, bookmark every single item.

        if ($(newsContainerSelector).length === 0) {
            // console.log("checkBookmark: NO NEWS CONTAINERS to deal with, no need to set bookmark")

            return;
        }

        // If there's nothing more to load and we've scrolled alllll the way down, bookmark the last item.
        if (isAtBottom($(".bookmark").height())) {
            // console.log("checkBookmark: At bottom, bookmark all");
            bookmarkAll = true;
        }

        // Start at the current bookmark.
        let bookmarkedItem = $( '#newsView>.bookmarked' );
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

            // Move the bookmark.
            // console.log("checkBookmark: set bookmark to ", nextItem.attr('id'));
            apiGetRequest('set_bookmark', htmlIdToId(nextItem.attr('id')));

            // Continue to next item.
            nextItem = nextNewsContainer(nextItem);
        }
    }

    function loadNext() {
        // console.log("loadNext");

        // Prevent duplicate requests.
        if (isLoadingNews) {
            console.log("loadNext: Already loading, skipping");
            return;
        }

        // Use prefetched data if available
        if (prefetchedData !== null) {
            console.log("Using prefetched data");
            const data = prefetchedData;
            clearPrefetch();

            if (data.news && data.news.length > 0) {
                appendNews(true, data.firstNewsID, data.news);
            }
            return;
        }

        // If prefetch is in progress, wait for it instead of making a duplicate request
        if (isPrefetching && prefetchPromise) {
            console.log("Waiting for prefetch to complete...");
            prefetchPromise.then((data) => {
                clearPrefetch();
                if (data && data.news && data.news.length > 0) {
                    appendNews(true, data.firstNewsID, data.news);
                }
            });
            return;
        }

        // No prefetch available, make a regular request
        isLoadingNews = true;
        requestNews("append");
    }

    function loadPrevious() {
        // console.log("loadPrevious");

        // Prevent concurrent requests which can cause duplicates
        if (isLoadingNews) {
            console.log("loadPrevious: Already loading, skipping");
            return;
        }

        // Clear prefetch data when scrolling upward. This is because the prefetch data will
        // be for appending to the bottom.
        clearPrefetch();

        isLoadingNews = true;
        requestNews("prepend");
    }


    /**
     * Timestamp update timer.
     */
    function updateTimestamps(interval) {
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

    // Use passive scroll event listener instead of polling
    window.addEventListener('scroll', onScroll, { passive: true });

    // Also check periodically for edge cases (e.g., content loaded while at bottom)
    setInterval(checkScrollPosition, 1000);

    // Update timestamps every 10 seconds.
    updateTimestamps(10000);
});
