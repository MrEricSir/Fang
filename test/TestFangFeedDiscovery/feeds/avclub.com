<!DOCTYPE html>
<html lang="en-US" itemscope itemtype="https://schema.org/WebPage">

<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="viewport-fit=cover, width=device-width, initial-scale=1.0, maximum-scale=2.0">

    <meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate">
    <meta http-equiv="Pragma" content="no-cache">
    <meta http-equiv="Expires" content="0">
  <link rel="alternate" type="application/rss+xml" title="AV Club href="https://www.avclub.com/rss.xml">
  
   <script> 
 function getCookie(name) {
  var match = document.cookie.match(new RegExp('(^| )' + name + '=([^;]+)'));
  if (match) return match[2];
}

 function isMemberOrEditor() {
    
     var memberCookie = getCookie('jmemberlevel');
        
        return (memberCookie=='2' || memberCookie=='3' || memberCookie=='administrator' || memberCookie=='editor' || memberCookie=='contributor') ;
}

var htlSuppress = false;
if (isMemberOrEditor() ){
    htlSuppress = true;
}
</script>
<script type='text/javascript'>
    (function() {
 
        var _sf_async_config = window._sf_async_config = (window._sf_async_config || {});
        _sf_async_config.uid = 67234 ; 
        _sf_async_config.domain = 'avclub.com'; 
        _sf_async_config.useCanonical = true;
        _sf_async_config.useCanonicalDomain = true;
        _sf_async_config.flickerControl = false;
        _sf_async_config.sections = 'homepage'; 
        _sf_async_config.authors = 'No Author'; //SET PAGE AUTHOR(S)
 
        function loadChartbeat() {
            var e = document.createElement('script');
            var n = document.getElementsByTagName('script')[0];
            e.type = 'text/javascript';
            e.async = true;
            e.src = '//static.chartbeat.com/js/chartbeat.js';
            n.parentNode.insertBefore(e, n);
        }
        loadChartbeat();
     })();
</script>     






    <link rel="icon" sizes="196x196" href="https://www.avclub.com/wp-content/themes/pastemagazine/img/mobile-icon-196.png">
    <link rel="icon" sizes="128x128" href="https://www.avclub.com/wp-content/themes/pastemagazine/img/mobile-icon-128.png">
    <link rel="apple-touch-icon" sizes="57x57" href="https://www.avclub.com/wp-content/themes/pastemagazine/img/mobile-icon-57.png">
    <link rel="apple-touch-icon" sizes="72x72" href="https://www.avclub.com/wp-content/themes/pastemagazine/img/mobile-icon-72.png">
    <link rel="apple-touch-icon" sizes="144x144" href="https://www.avclub.com/wp-content/themes/pastemagazine/img/mobile-icon-144.png">

    <link rel="shortcut icon" href="https://www.avclub.com/wp-content/themes/pastemagazine/img/favicon.ico" type="image/vnd.microsoft.icon">

    <link rel="stylesheet" type="text/css" href="https://htlbid.com/v3/avclub.com/htlbid.css" />
     <script src="https://htlbid.com/v3/avclub.com/htlbid.js"></script> <script>
    
    
    
    //googletag.cmd.push(detectAdLoad);
    function getCookie(name) {
  var match = document.cookie.match(new RegExp('(^| )' + name + '=([^;]+)'));
  if (match) return match[2];
}
function refreshSlotOnTimter(slotId, delay) {
 myCounter.incrementCountForSlotId(slotId);
 let myCnt = myCounter.getCountForSlotId(slotId);
   console.log('slotId: ' + slotId + ' Count: ' + myCnt); 
   if (myCnt<4 ) {
     setTimeout(function() {
       // console.log('Refresh Blank: ' + slotId )
          htlbid.refreshSlot(slotId);
        }, delay);
   } else {//console.log('Skip refresh()');
       
   }
}

class RefreshCounter {
    constructor() {
        this.arr = [];
    }
       
    increment() { this.count =  this.count +1; }
    getCountForSlotId(slotId) { 
        if (this.arr[slotId] ) { 
            return this.arr[slotId];
        
        } else {
            return 0;
            
        } 
        
    }
    resetAllCounts() {
           console.log('resetAllCounts()'); 
           this.arr = [];
   }
    incrementCountForSlotId(slotId) {
    if (this.arr[slotId] ) {
        this.arr[slotId] = this.arr[slotId] + 1;
        
    } else {
        this.arr[slotId] = 1;} 
        
    }
}
let myCounter = new RefreshCounter();

function detectAdLoad() {
 
    if(window.googletag && googletag.pubadsReady) {
        console.log("pubadsReady");
        googletag.cmd.push(detectAdLoad);
        googletag.pubads().addEventListener('slotRenderEnded', function(event) {
       const slotId = event.slot.getSlotElementId();
    
     
     
        const {isEmpty, slot} = event;
        myCounter.increment();
        
       
         

            
           
        });
    } else {
        // console.log("googletag not detected, defaulting");
        setTimeout(function() {
          
            console.log("pubads not detected");
            detectAdLoad() ;
        }, 300);
    }
}
    setupAds();

   // setInterval(refreshAds, 30000);
   function refreshAds() {
   myCounter.resetAllCounts();
   
       
       
  htlbid.refresh();
  
   } 
    function setupAds() {
     
        var memberCookie = getCookie('jmemberlevel');
      
        if (memberCookie!='2' && memberCookie!='3') {
      window.htlbid = window.htlbid || {};
      htlbid.cmd = htlbid.cmd || [];
  
      htlbid.cmd.push(function() {
        htlbid.setTargeting("is_testing","no");  
 htlbid.setTargeting("subscriber",isMemberOrEditor()? "true":"false");
htlbid.setTargeting("is_home", "yes"); 
htlbid.setTargeting("category", "homepage");  
htlbid.setTargeting("post_id", "/"); 
 htlbid.layout();
});
  } 
 }
</script>

    <script>
    var pm = {
        servers: {
            pastemagazine: "www.avclub.com",
            wolfgangs: "www.wolfgangs.com"
        },
        version: "0",
        page: {
            "type": "Landing",
            "mediaType": "Unknown",
            "articleType": "Unknown",
            "articleId": -1,
            "author": null,
            "services": "/pastemagazine.svc/pastemagazine/",
            "isMobile": false,
            "isIos": false,
            "videoEmbedPlayerId": 30540132,
            "testGroup": null,
            "adblocker": true
        }
    };
    </script>


    <meta property="fb:admins" content="679468950">
    <meta property="fb:admins" content="1185614656">
    <meta property="fb:app_id" content="127550380613969">
    <meta property="fb:pages" content="18512903240">

    <meta name="p:domain_verify" content="8f36922bc91ba221f10d82c407d8b6a9">

 

      <script>
    var googletag = googletag || {};
    googletag.cmd = googletag.cmd || [];
    </script>



    <meta name='robots' content='index, follow, max-image-preview:large, max-snippet:-1, max-video-preview:-1' />
	<style>img:is([sizes="auto" i], [sizes^="auto," i]) { contain-intrinsic-size: 3000px 1500px }</style>
	
	<!-- This site is optimized with the Yoast SEO Premium plugin v25.9 (Yoast SEO v25.9) - https://yoast.com/wordpress/plugins/seo/ -->
	<title>The A.V. Club — Pop culture obsessives writing for the pop culture obsessed.</title>
	<meta name="description" content="The A.V. Club digs deep into film, TV, music, games, books and more." />
	<link rel="canonical" href="https://www.avclub.com/" />
	<meta property="og:locale" content="en_US" />
	<meta property="og:type" content="website" />
	<meta property="og:title" content="Home" />
	<meta property="og:description" content="The A.V. Club digs deep into film, TV, music, games, books and more." />
	<meta property="og:url" content="https://www.avclub.com/" />
	<meta property="og:site_name" content="AV Club" />
	<meta property="article:publisher" content="https://www.facebook.com/theavclub" />
	<meta property="article:modified_time" content="2024-06-24T15:45:55+00:00" />
	<meta property="og:image" content="https://img.pastemagazine.com/wp-content/avuploads/2024/05/15050443/logo-1200x675-1.png" />
	<meta property="og:image:width" content="676" />
	<meta property="og:image:height" content="380" />
	<meta property="og:image:type" content="image/png" />
	<meta name="twitter:card" content="summary_large_image" />
	<meta name="twitter:site" content="@theavclub" />
	<script type="application/ld+json" class="yoast-schema-graph">{"@context":"https://schema.org","@graph":[{"@type":"WebPage","@id":"https://www.avclub.com/","url":"https://www.avclub.com/","name":"The A.V. Club — Pop culture obsessives writing for the pop culture obsessed.","isPartOf":{"@id":"https://www.avclub.com/#website"},"datePublished":"2022-04-19T10:34:01+00:00","dateModified":"2024-06-24T15:45:55+00:00","description":"The A.V. Club digs deep into film, TV, music, games, books and more.","breadcrumb":{"@id":"https://www.avclub.com/#breadcrumb"},"inLanguage":"en-US","potentialAction":[{"@type":"ReadAction","target":["https://www.avclub.com/"]}]},{"@type":"BreadcrumbList","@id":"https://www.avclub.com/#breadcrumb","itemListElement":[{"@type":"ListItem","position":1,"name":"Home"}]},{"@type":"WebSite","@id":"https://www.avclub.com/#website","url":"https://www.avclub.com/","name":"AV Club","description":"Pop culture obsessives writing for the pop culture obsessed.","potentialAction":[{"@type":"SearchAction","target":{"@type":"EntryPoint","urlTemplate":"https://www.avclub.com/?s={search_term_string}"},"query-input":{"@type":"PropertyValueSpecification","valueRequired":true,"valueName":"search_term_string"}}],"inLanguage":"en-US"}]}</script>
	<!-- / Yoast SEO Premium plugin. -->


		<!-- This site uses the Google Analytics by MonsterInsights plugin v9.9.1 - Using Analytics tracking - https://www.monsterinsights.com/ -->
							<script src="//www.googletagmanager.com/gtag/js?id=G-B6Y9GVDWSB"  data-cfasync="false" async async></script>
			<script data-cfasync="false" async>
				var mi_version = '9.9.1';
				var mi_track_user = true;
				var mi_no_track_reason = '';
								var MonsterInsightsDefaultLocations = {"page_location":"https:\/\/www.avclub.com\/"};
								if ( typeof MonsterInsightsPrivacyGuardFilter === 'function' ) {
					var MonsterInsightsLocations = (typeof MonsterInsightsExcludeQuery === 'object') ? MonsterInsightsPrivacyGuardFilter( MonsterInsightsExcludeQuery ) : MonsterInsightsPrivacyGuardFilter( MonsterInsightsDefaultLocations );
				} else {
					var MonsterInsightsLocations = (typeof MonsterInsightsExcludeQuery === 'object') ? MonsterInsightsExcludeQuery : MonsterInsightsDefaultLocations;
				}

								var disableStrs = [
										'ga-disable-G-B6Y9GVDWSB',
									];

				/* Function to detect opted out users */
				function __gtagTrackerIsOptedOut() {
					for (var index = 0; index < disableStrs.length; index++) {
						if (document.cookie.indexOf(disableStrs[index] + '=true') > -1) {
							return true;
						}
					}

					return false;
				}

				/* Disable tracking if the opt-out cookie exists. */
				if (__gtagTrackerIsOptedOut()) {
					for (var index = 0; index < disableStrs.length; index++) {
						window[disableStrs[index]] = true;
					}
				}

				/* Opt-out function */
				function __gtagTrackerOptout() {
					for (var index = 0; index < disableStrs.length; index++) {
						document.cookie = disableStrs[index] + '=true; expires=Thu, 31 Dec 2099 23:59:59 UTC; path=/';
						window[disableStrs[index]] = true;
					}
				}

				if ('undefined' === typeof gaOptout) {
					function gaOptout() {
						__gtagTrackerOptout();
					}
				}
								window.dataLayer = window.dataLayer || [];

				window.MonsterInsightsDualTracker = {
					helpers: {},
					trackers: {},
				};
				if (mi_track_user) {
					function __gtagDataLayer() {
						dataLayer.push(arguments);
					}

					function __gtagTracker(type, name, parameters) {
						if (!parameters) {
							parameters = {};
						}

						if (parameters.send_to) {
							__gtagDataLayer.apply(null, arguments);
							return;
						}

						if (type === 'event') {
														parameters.send_to = monsterinsights_frontend.v4_id;
							var hookName = name;
							if (typeof parameters['event_category'] !== 'undefined') {
								hookName = parameters['event_category'] + ':' + name;
							}

							if (typeof MonsterInsightsDualTracker.trackers[hookName] !== 'undefined') {
								MonsterInsightsDualTracker.trackers[hookName](parameters);
							} else {
								__gtagDataLayer('event', name, parameters);
							}
							
						} else {
							__gtagDataLayer.apply(null, arguments);
						}
					}

					__gtagTracker('js', new Date());
					__gtagTracker('set', {
						'developer_id.dZGIzZG': true,
											});
					if ( MonsterInsightsLocations.page_location ) {
						__gtagTracker('set', MonsterInsightsLocations);
					}
										__gtagTracker('config', 'G-B6Y9GVDWSB', {"forceSSL":"true","link_attribution":"true"} );
										window.gtag = __gtagTracker;										(function () {
						/* https://developers.google.com/analytics/devguides/collection/analyticsjs/ */
						/* ga and __gaTracker compatibility shim. */
						var noopfn = function () {
							return null;
						};
						var newtracker = function () {
							return new Tracker();
						};
						var Tracker = function () {
							return null;
						};
						var p = Tracker.prototype;
						p.get = noopfn;
						p.set = noopfn;
						p.send = function () {
							var args = Array.prototype.slice.call(arguments);
							args.unshift('send');
							__gaTracker.apply(null, args);
						};
						var __gaTracker = function () {
							var len = arguments.length;
							if (len === 0) {
								return;
							}
							var f = arguments[len - 1];
							if (typeof f !== 'object' || f === null || typeof f.hitCallback !== 'function') {
								if ('send' === arguments[0]) {
									var hitConverted, hitObject = false, action;
									if ('event' === arguments[1]) {
										if ('undefined' !== typeof arguments[3]) {
											hitObject = {
												'eventAction': arguments[3],
												'eventCategory': arguments[2],
												'eventLabel': arguments[4],
												'value': arguments[5] ? arguments[5] : 1,
											}
										}
									}
									if ('pageview' === arguments[1]) {
										if ('undefined' !== typeof arguments[2]) {
											hitObject = {
												'eventAction': 'page_view',
												'page_path': arguments[2],
											}
										}
									}
									if (typeof arguments[2] === 'object') {
										hitObject = arguments[2];
									}
									if (typeof arguments[5] === 'object') {
										Object.assign(hitObject, arguments[5]);
									}
									if ('undefined' !== typeof arguments[1].hitType) {
										hitObject = arguments[1];
										if ('pageview' === hitObject.hitType) {
											hitObject.eventAction = 'page_view';
										}
									}
									if (hitObject) {
										action = 'timing' === arguments[1].hitType ? 'timing_complete' : hitObject.eventAction;
										hitConverted = mapArgs(hitObject);
										__gtagTracker('event', action, hitConverted);
									}
								}
								return;
							}

							function mapArgs(args) {
								var arg, hit = {};
								var gaMap = {
									'eventCategory': 'event_category',
									'eventAction': 'event_action',
									'eventLabel': 'event_label',
									'eventValue': 'event_value',
									'nonInteraction': 'non_interaction',
									'timingCategory': 'event_category',
									'timingVar': 'name',
									'timingValue': 'value',
									'timingLabel': 'event_label',
									'page': 'page_path',
									'location': 'page_location',
									'title': 'page_title',
									'referrer' : 'page_referrer',
								};
								for (arg in args) {
																		if (!(!args.hasOwnProperty(arg) || !gaMap.hasOwnProperty(arg))) {
										hit[gaMap[arg]] = args[arg];
									} else {
										hit[arg] = args[arg];
									}
								}
								return hit;
							}

							try {
								f.hitCallback();
							} catch (ex) {
							}
						};
						__gaTracker.create = newtracker;
						__gaTracker.getByName = newtracker;
						__gaTracker.getAll = function () {
							return [];
						};
						__gaTracker.remove = noopfn;
						__gaTracker.loaded = true;
						window['__gaTracker'] = __gaTracker;
					})();
									} else {
										console.log("");
					(function () {
						function __gtagTracker() {
							return null;
						}

						window['__gtagTracker'] = __gtagTracker;
						window['gtag'] = __gtagTracker;
					})();
									}
			</script>
			
							<!-- / Google Analytics by MonsterInsights -->
		<style id='classic-theme-styles-inline-css' type='text/css'>
/*! This file is auto-generated */
.wp-block-button__link{color:#fff;background-color:#32373c;border-radius:9999px;box-shadow:none;text-decoration:none;padding:calc(.667em + 2px) calc(1.333em + 2px);font-size:1.125em}.wp-block-file__button{background:#32373c;color:#fff;text-decoration:none}
</style>
<style id='global-styles-inline-css' type='text/css'>
:root{--wp--preset--aspect-ratio--square: 1;--wp--preset--aspect-ratio--4-3: 4/3;--wp--preset--aspect-ratio--3-4: 3/4;--wp--preset--aspect-ratio--3-2: 3/2;--wp--preset--aspect-ratio--2-3: 2/3;--wp--preset--aspect-ratio--16-9: 16/9;--wp--preset--aspect-ratio--9-16: 9/16;--wp--preset--color--black: #000000;--wp--preset--color--cyan-bluish-gray: #abb8c3;--wp--preset--color--white: #ffffff;--wp--preset--color--pale-pink: #f78da7;--wp--preset--color--vivid-red: #cf2e2e;--wp--preset--color--luminous-vivid-orange: #ff6900;--wp--preset--color--luminous-vivid-amber: #fcb900;--wp--preset--color--light-green-cyan: #7bdcb5;--wp--preset--color--vivid-green-cyan: #00d084;--wp--preset--color--pale-cyan-blue: #8ed1fc;--wp--preset--color--vivid-cyan-blue: #0693e3;--wp--preset--color--vivid-purple: #9b51e0;--wp--preset--gradient--vivid-cyan-blue-to-vivid-purple: linear-gradient(135deg,rgba(6,147,227,1) 0%,rgb(155,81,224) 100%);--wp--preset--gradient--light-green-cyan-to-vivid-green-cyan: linear-gradient(135deg,rgb(122,220,180) 0%,rgb(0,208,130) 100%);--wp--preset--gradient--luminous-vivid-amber-to-luminous-vivid-orange: linear-gradient(135deg,rgba(252,185,0,1) 0%,rgba(255,105,0,1) 100%);--wp--preset--gradient--luminous-vivid-orange-to-vivid-red: linear-gradient(135deg,rgba(255,105,0,1) 0%,rgb(207,46,46) 100%);--wp--preset--gradient--very-light-gray-to-cyan-bluish-gray: linear-gradient(135deg,rgb(238,238,238) 0%,rgb(169,184,195) 100%);--wp--preset--gradient--cool-to-warm-spectrum: linear-gradient(135deg,rgb(74,234,220) 0%,rgb(151,120,209) 20%,rgb(207,42,186) 40%,rgb(238,44,130) 60%,rgb(251,105,98) 80%,rgb(254,248,76) 100%);--wp--preset--gradient--blush-light-purple: linear-gradient(135deg,rgb(255,206,236) 0%,rgb(152,150,240) 100%);--wp--preset--gradient--blush-bordeaux: linear-gradient(135deg,rgb(254,205,165) 0%,rgb(254,45,45) 50%,rgb(107,0,62) 100%);--wp--preset--gradient--luminous-dusk: linear-gradient(135deg,rgb(255,203,112) 0%,rgb(199,81,192) 50%,rgb(65,88,208) 100%);--wp--preset--gradient--pale-ocean: linear-gradient(135deg,rgb(255,245,203) 0%,rgb(182,227,212) 50%,rgb(51,167,181) 100%);--wp--preset--gradient--electric-grass: linear-gradient(135deg,rgb(202,248,128) 0%,rgb(113,206,126) 100%);--wp--preset--gradient--midnight: linear-gradient(135deg,rgb(2,3,129) 0%,rgb(40,116,252) 100%);--wp--preset--font-size--small: 13px;--wp--preset--font-size--medium: 20px;--wp--preset--font-size--large: 36px;--wp--preset--font-size--x-large: 42px;--wp--preset--spacing--20: 0.44rem;--wp--preset--spacing--30: 0.67rem;--wp--preset--spacing--40: 1rem;--wp--preset--spacing--50: 1.5rem;--wp--preset--spacing--60: 2.25rem;--wp--preset--spacing--70: 3.38rem;--wp--preset--spacing--80: 5.06rem;--wp--preset--shadow--natural: 6px 6px 9px rgba(0, 0, 0, 0.2);--wp--preset--shadow--deep: 12px 12px 50px rgba(0, 0, 0, 0.4);--wp--preset--shadow--sharp: 6px 6px 0px rgba(0, 0, 0, 0.2);--wp--preset--shadow--outlined: 6px 6px 0px -3px rgba(255, 255, 255, 1), 6px 6px rgba(0, 0, 0, 1);--wp--preset--shadow--crisp: 6px 6px 0px rgba(0, 0, 0, 1);}:where(.is-layout-flex){gap: 0.5em;}:where(.is-layout-grid){gap: 0.5em;}body .is-layout-flex{display: flex;}.is-layout-flex{flex-wrap: wrap;align-items: center;}.is-layout-flex > :is(*, div){margin: 0;}body .is-layout-grid{display: grid;}.is-layout-grid > :is(*, div){margin: 0;}:where(.wp-block-columns.is-layout-flex){gap: 2em;}:where(.wp-block-columns.is-layout-grid){gap: 2em;}:where(.wp-block-post-template.is-layout-flex){gap: 1.25em;}:where(.wp-block-post-template.is-layout-grid){gap: 1.25em;}.has-black-color{color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-color{color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-color{color: var(--wp--preset--color--white) !important;}.has-pale-pink-color{color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-color{color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-color{color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-color{color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-color{color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-color{color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-color{color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-color{color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-color{color: var(--wp--preset--color--vivid-purple) !important;}.has-black-background-color{background-color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-background-color{background-color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-background-color{background-color: var(--wp--preset--color--white) !important;}.has-pale-pink-background-color{background-color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-background-color{background-color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-background-color{background-color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-background-color{background-color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-background-color{background-color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-background-color{background-color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-background-color{background-color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-background-color{background-color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-background-color{background-color: var(--wp--preset--color--vivid-purple) !important;}.has-black-border-color{border-color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-border-color{border-color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-border-color{border-color: var(--wp--preset--color--white) !important;}.has-pale-pink-border-color{border-color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-border-color{border-color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-border-color{border-color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-border-color{border-color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-border-color{border-color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-border-color{border-color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-border-color{border-color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-border-color{border-color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-border-color{border-color: var(--wp--preset--color--vivid-purple) !important;}.has-vivid-cyan-blue-to-vivid-purple-gradient-background{background: var(--wp--preset--gradient--vivid-cyan-blue-to-vivid-purple) !important;}.has-light-green-cyan-to-vivid-green-cyan-gradient-background{background: var(--wp--preset--gradient--light-green-cyan-to-vivid-green-cyan) !important;}.has-luminous-vivid-amber-to-luminous-vivid-orange-gradient-background{background: var(--wp--preset--gradient--luminous-vivid-amber-to-luminous-vivid-orange) !important;}.has-luminous-vivid-orange-to-vivid-red-gradient-background{background: var(--wp--preset--gradient--luminous-vivid-orange-to-vivid-red) !important;}.has-very-light-gray-to-cyan-bluish-gray-gradient-background{background: var(--wp--preset--gradient--very-light-gray-to-cyan-bluish-gray) !important;}.has-cool-to-warm-spectrum-gradient-background{background: var(--wp--preset--gradient--cool-to-warm-spectrum) !important;}.has-blush-light-purple-gradient-background{background: var(--wp--preset--gradient--blush-light-purple) !important;}.has-blush-bordeaux-gradient-background{background: var(--wp--preset--gradient--blush-bordeaux) !important;}.has-luminous-dusk-gradient-background{background: var(--wp--preset--gradient--luminous-dusk) !important;}.has-pale-ocean-gradient-background{background: var(--wp--preset--gradient--pale-ocean) !important;}.has-electric-grass-gradient-background{background: var(--wp--preset--gradient--electric-grass) !important;}.has-midnight-gradient-background{background: var(--wp--preset--gradient--midnight) !important;}.has-small-font-size{font-size: var(--wp--preset--font-size--small) !important;}.has-medium-font-size{font-size: var(--wp--preset--font-size--medium) !important;}.has-large-font-size{font-size: var(--wp--preset--font-size--large) !important;}.has-x-large-font-size{font-size: var(--wp--preset--font-size--x-large) !important;}
:where(.wp-block-post-template.is-layout-flex){gap: 1.25em;}:where(.wp-block-post-template.is-layout-grid){gap: 1.25em;}
:where(.wp-block-columns.is-layout-flex){gap: 2em;}:where(.wp-block-columns.is-layout-grid){gap: 2em;}
:root :where(.wp-block-pullquote){font-size: 1.5em;line-height: 1.6;}
</style>
<link rel='stylesheet' id='pastemagazine-old_inline-style-css' href='https://www.avclub.com/wp-content/themes/pastemagazine/css/inline-39.2022.10209.11821.css?ver=0.57443200%201761284289' type='text/css' media='all' />
<link rel='stylesheet' id='pastemagazine-old_stylesheet-style-css' href='https://www.avclub.com/wp-content/themes/pastemagazine/css/stylesheet-39.2022.10209.11821.css?ver=0.57446300%201761284289' type='text/css' media='all' />
<link rel='stylesheet' id='pastemagazine-theme-style-css' href='https://www.avclub.com/wp-content/themes/pastemagazine/style.css?ver=0.57448700%201761284289' type='text/css' media='all' />
<script type="text/javascript" defer src="https://www.avclub.com/wp-content/plugins/google-analytics-premium/assets/js/frontend-gtag.min.js?ver=9.9.1" id="monsterinsights-frontend-script-js" async="async" data-wp-strategy="async"></script>
<script data-cfasync="false" async id='monsterinsights-frontend-script-js-extra'>/* <![CDATA[ */
var monsterinsights_frontend = {"js_events_tracking":"true","download_extensions":"doc,pdf,ppt,zip,xls,docx,pptx,xlsx","inbound_paths":"[]","home_url":"https:\/\/www.avclub.com","hash_tracking":"false","v4_id":"G-B6Y9GVDWSB"};/* ]]> */
</script>
<script type="text/javascript" src="https://www.avclub.com/wp-includes/js/jquery/jquery.min.js?ver=3.7.1" id="jquery-core-js"></script>
<script type="text/javascript" defer src="https://www.avclub.com/wp-content/themes/pastemagazine/js/jquery.sticky.js?ver=68fb10c18c42f" id="sticky-js"></script>
<script type="text/javascript" defer src="https://www.avclub.com/wp-content/themes/pastemagazine/js/pm_custom.js?ver=68fb10c18c441" id="pm-custom-js"></script>
<noscript><style>.lazyload[data-src]{display:none !important;}</style></noscript><style>.lazyload{background-image:none !important;}.lazyload:before{background-image:none !important;}</style><link rel="icon" href="https://img.pastemagazine.com/wp-content/avuploads/2024/06/14160401/logo-dark-outline-512x512-1.jpg" sizes="32x32" />
<link rel="icon" href="https://img.pastemagazine.com/wp-content/avuploads/2024/06/14160401/logo-dark-outline-512x512-1.jpg" sizes="192x192" />
<link rel="apple-touch-icon" href="https://img.pastemagazine.com/wp-content/avuploads/2024/06/14160401/logo-dark-outline-512x512-1.jpg" />
<meta name="msapplication-TileImage" content="https://img.pastemagazine.com/wp-content/avuploads/2024/06/14160401/logo-dark-outline-512x512-1.jpg" />

 
<!-- LiveConnectTag for advertisers -->
 <!-- <script type="text/javascript" src="//b-code.liadm.com/b-00aw.min.js" async="true" charset="utf-8"></script>

<script type="text/javascript">
window.liQ = window.liQ || [];
window.liQ.push({ "event": "convsersion"});
</script>


<script>!function(n){if(!window.cnx){window.cnx={},window.cnx.cmd=[];var t=n.createElement('iframe');t.src='javascript:false'; t.display='none',t.onload=function(){var n=t.contentWindow.document,c=n.createElement('script');c.src='//cd.connatix.com/connatix.player.js?cid=f05e5dfa-afb4-420d-a94f-13c7f4af05fb&pid=0a5a5d4b-02a8-43c5-b6cb-d47c44cae4bb',c.setAttribute('async','1'),c.setAttribute('type','text/javascript'),n.body.appendChild(c)},n.head.appendChild(t)}}(document);</script>
-->
</head>

<body class="home wp-singular page-template-default page page-id-2 wp-embed-responsive wp-theme-pastemagazine">

    <a href="#content" class="skip-link screen-reader-text">Skip to the content</a>
    <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-N6NTJSWR" height="0" width="0"
            style="display:none;visibility:hidden"></iframe></noscript>

    <div class="htlad-top_leaderboard" id="top_leaderboard"></div>

    
<div class="expanded site-navigation" id="site_navigation" data-pagetype="Landing">
	<div class="htlad-above_logo" id="above_logo"></div>
    <div class="grid-container">
        <header id="master-header" class="grid-y landing top-bar">
             <div id="site-bar"><ul><li><a href="https://www.pastemagazine.com">Paste</a></li> | <li><a href="https://www.avclub.com">A.V. Club</a></li>  | <li><a href="https://www.jezebel.com">Jezebel</a></li> | <li><a href="https://www.splinter.com">Splinter</a></li> | <li><a href="https://www.endlessmode.com">Endless Mode</a></li></ul></div> 
            <div class="top-bar-container grid-x">
                <div class="top-bar-right hide-for-large cell">
                    <a href="#" class="menu" aria-label="Section Menu" data-toggle="small-navigation-menu small-search-menu"
                        aria-controls="small-navigation-menu small-search-menu" data-is-focus="false"
                        data-yeti-box="small-navigation-menu small-search-menu" aria-haspopup="true" aria-expanded="false"
                        id="32rdph-dd-anchor"><!--Sections --> 
                         <i class="icon-menu">
                    
                      
                          
                        </i> 
                    </a>
                    

 
                    <ul class="vertical dropdown-pane menu has-position-left has-alignment-top"
                        id="small-navigation-menu" data-dropdown="vd5cbf-dropdown" data-position="left"
                        data-alignment="top" xxdata-close-on-click="false" data-auto-focus="false"
                        aria-labelledby="32rdph-dd-anchor" aria-hidden="true" data-yeti-box="small-navigation-menu"
                        data-resize="small-navigation-menu" data-events="resize" style="top: 0px; left: -536.78px;" data-closable>
                        
                        <button class="close-button float-right" aria-label="Close alert" type="button" data-close data-close-on-click="true" data-position="right">
    <span aria-hidden="true">&times;</span>
  </button>
  
                        <form id="article-search" action="/search" method="get" class="search-input">
                            <input type="text" id="master-search" placeholder="Search" value="" aria-label="Search" class="ui-autocomplete-input" autocomplete="off" name="q">
                            <a class="search closed icon-search" href="#" aria-label="Search" onclick="jQuery(this).parent().submit();"> <!-- Search -->
                    </a>
                         
                            <i id="search_in_progress"></i>
                        </form>
                         <li>
                            <a href="/latest" class="large-1 cell">Latest</a>
                        </li>
                         <li>
                            <a href="/article-type/news" class="large-1 cell">News</a>
                        </li>
                        <li>
                            <a href="/film" class="large-1 cell">Film</a>
                        </li>
                        <li>
                            <a href="/tv" class="large-1 cell">TV</a>
                        </li>
                         <li>
                            <a href="/music" class="large-1 cell">Music</a>
                        </li>
                        
                        <li>
                            <a href="/games" class="large-1 cell">Games</a>
                        </li>
                         <li>
                            <a href="/av-undercover" class="large-1 cell">AV Undercover</a>
                        </li>
                        <li>
                            <a href="/books" class="large-1 cell">Books</a>
                        </li>
                          <li>
                            <a href="/aux" class="large-1 cell">Aux</a>
                        </li>
                           
                       
                      
                       
                      
                      <li class="empty">
                            <!--to force order-->
                        </li> 
 
                        <li class="hide-not-large">
                            <a href="/newsletter">Newsletter</a>
                        </li>
                         <li class="hide-not-large">
                            <a href="https://bsky.app/profile/avclub.com">Bluesky</a>
                        </li>
                        <li class="hide-not-large">
                            <a href="https://www.instagram.com/theavc/">Instagram</a>
                        </li>
                        <li class="hide-not-large">
                            <a href="https://x.com/theavclub">Twitter</a>
                        </li>
                        <li class="hide-not-large">
                            <a href="https://www.youtube.com/user/theavclub">YouTube</a>
                        </li>
                        <li class="hide-not-large">
                            <a href="https://www.facebook.com/theavclub">Facebook</a>
                        </li>  
                        
 
                    </ul>



                </div>
                <div class="title-bar grid-x cell align-bottom">
                    <h1 class="large-1 medium-1 small-5 cell logo">
                        <a href="/">
                            <svg id="Layer_1" data-name="Layer 1" viewBox="0 0 150 59" 
                                alt="AV Club">
                                xmlns="http://www.w3.org/2000/svg">
                               
                                <title>AV Club</title>
    <path fill="#1C263C" fill-rule="evenodd" d="M83.87 37.92a12.85 12.85 0 0 1-9.28 3.72c-3.62 0-6.7-1.24-9.27-3.72a12.04 12.04 0 0 1-3.84-8.98c0-3.5 1.28-6.5 3.84-8.98a12.86 12.86 0 0 1 9.27-3.72c3.63 0 6.72 1.24 9.28 3.72l-3.55 3.44a7.99 7.99 0 0 0-5.73-2.28c-2.22 0-4.13.76-5.7 2.3a7.42 7.42 0 0 0-2.38 5.52c0 2.16.8 4 2.38 5.53a7.92 7.92 0 0 0 5.71 2.3c2.23 0 4.14-.76 5.73-2.29l3.54 3.44zm20.27 2.66H87.07V16.24h5.07v19.53h12v4.81zm22.4-9.88c0 3.02-1.1 5.6-3.28 7.74a10.91 10.91 0 0 1-7.92 3.2c-3.1 0-5.74-1.07-7.92-3.2a10.42 10.42 0 0 1-3.28-7.74V16.24h5.06V30.7c0 1.65.6 3.06 1.8 4.23a5.97 5.97 0 0 0 4.34 1.76c1.69 0 3.13-.58 4.33-1.76a5.7 5.7 0 0 0 1.8-4.23V16.24h5.07V30.7zm15.19-14.46c2.02 0 3.75.72 5.18 2.15a7.02 7.02 0 0 1 2.15 5.16c0 1.65-.5 3.13-1.49 4.44a7.6 7.6 0 0 1 2.43 5.74c0 2.17-.78 4.03-2.32 5.58a7.54 7.54 0 0 1-5.55 2.33H130.8v-25.4h10.93zm.3 14.82h-5.9v5.29h5.9c.74 0 1.36-.25 1.87-.76a2.63 2.63 0 0 0-.01-3.72 2.5 2.5 0 0 0-1.86-.81zm.26-9.53h-6.16v4.24h6.16c.65 0 1.21-.21 1.68-.63a1.93 1.93 0 0 0 0-2.98 2.43 2.43 0 0 0-1.68-.63zM47.26 5.94a29.5 29.5 0 1 1-35.5 47.12 29.5 29.5 0 1 1 35.5-47.12zM31.93 16.86h-5.58l11.71 24.23 11.47-24.23h-5.35l-6.23 13.5-6.02-13.5zm-10.3 0L9.48 41.09h5.28l1.46-3.17h9.97l1.23 3.17h5.25L21.63 16.86zm.08 11.59l2.53 5.26h-5.27l2.74-5.26z"></path>

                            </svg>
                        </a>
                       
                    </h1>
                   
                </div>
                 <div class="tagline">Pop culture obsessives writing for the pop culture obsessed.</div>
               <nav>   
                
            
                 
                  
                    
                   
                    <div class="top-bar-right show-for-large cell">
                       
                    </div>
                </nav>
  
             <div class="bottom-link-row horizontal"> 
               <a class="search closed icon-search" href="/search"
                        aria-label="Search"> <!-- Search -->
                    </a> 
            
                        
               <a href="/latest"
                        >Latest</a>
                    <a href="/article-type/news"
                        >News</a>
                  
                   <a href="/tv"
                        >TV</a>
                        
                         <a href="/film"
                        >Film</a>
                        
                    <a  href="/music"
                         class="hide-extra">Music</a>
                    <a   href="/games"
                        class="hide-extra hide-extra-medium">Games</a>
                        
                         <a href="/av-undercover"
                        class="show-for-large">AV Undercover</a>
                        
                        
                         <a   href="/newsletter"
                        class="">Newsletter</a>
                        
                      <!--
                         <a href="/2004-retrospective-spiderman-2-friends-the-killers"
                        >2004 Week</a>
                        -->
                        
                        
                        <div class="social-icon-group show-for-large">
                        <!-- email -->
                        <a class="social-icon" href="https://bsky.app/profile/avclub.com">

<svg height="20px" width="20px" xmlns="http://www.w3.org/2000/svg" shape-rendering="geometricPrecision" text-rendering="geometricPrecision" image-rendering="optimizeQuality" fill-rule="evenodd" clip-rule="evenodd" viewBox="0 0 511.999 452.266">
    <path fill="#00000" fill-rule="nonzero" d="M110.985 30.442c58.695 44.217 121.837 133.856 145.013 181.961 23.176-48.105 86.322-137.744 145.016-181.961 42.361-31.897 110.985-56.584 110.985 21.96 0 15.681-8.962 131.776-14.223 150.628-18.272 65.516-84.873 82.228-144.112 72.116 103.55 17.68 129.889 76.238 73 134.8-108.04 111.223-155.288-27.905-167.385-63.554-3.489-10.262-2.991-10.498-6.561 0-12.098 35.649-59.342 174.777-167.382 63.554-56.89-58.562-30.551-117.12 72.999-134.8-59.239 10.112-125.84-6.6-144.112-72.116C8.962 184.178 0 68.083 0 52.402c0-78.544 68.633-53.857 110.985-21.96z"></path>
</svg>

</a>

                   <!--       <a class="social-icon" href="/newsletter" > 
                         
                        
                      <svg height="20px" viewBox="0 0 72 72" width="20px" xmlns="http://www.w3.org/2000/svg"><g fill="none" fill-rule="evenodd"><path d="M36,72 L36,72 C55.882251,72 72,55.882251 72,36 L72,36 C72,16.117749 55.882251,-3.65231026e-15 36,0 L36,0 C16.117749,3.65231026e-15 -2.4348735e-15,16.117749 0,36 L0,36 C2.4348735e-15,55.882251 16.117749,72 36,72 Z" fill="#1C263C"/><path d="M18,26.1623226 L18,46.5476129 C18,47.6566452 18.8117419,48.5554839 19.9300645,48.5554839 L51.7447742,48.5554839 C52.8619355,48.5554839 53.6748387,47.6461935 53.6748387,46.5476129 L53.6748387,26.1623226 C53.6748387,24.9452903 52.947871,24 51.7447742,24 L19.9300645,24 C18.6805161,24 18,24.9685161 18,26.1623226 M20.9334194,27.9379355 C20.9334194,27.4467097 21.2307097,27.1656774 21.7056774,27.1656774 C21.9994839,27.1656774 33.560129,34.4910968 34.2603871,34.9207742 L36.0696774,36.0460645 C36.6433548,35.6616774 37.2193548,35.3330323 37.8139355,34.9347097 C39.0274839,34.1589677 49.8251613,27.1656774 50.1224516,27.1656774 C50.5985806,27.1656774 50.8947097,27.4467097 50.8947097,27.9379355 C50.8947097,28.4581935 49.8925161,28.9749677 49.239871,29.3732903 C45.1393548,31.8723871 41.04,34.5967742 36.980129,37.1887742 C36.7432258,37.3490323 36.2845161,37.6916129 35.9407742,37.6393548 C35.5575484,37.580129 23.7936774,30.0224516 21.6534194,28.7636129 C21.3317419,28.5743226 20.9334194,28.4012903 20.9334194,27.9379355" fill="#FFF"/></g></svg>
                      
                          
                        
                    </a> -->
                      <!-- insta -->
                         <a class="social-icon" href="https://www.instagram.com/theavc/" > 
                        <svg height="20px" width="20px" style="fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;" version="1.1" viewBox="0 0 512 512"   xml:space="preserve" xmlns="http://www.w3.org/2000/svg" xmlns:serif="http://www.serif.com/" xmlns:xlink="http://www.w3.org/1999/xlink"><path d="M256,0c141.29,0 256,114.71 256,256c0,141.29 -114.71,256 -256,256c-141.29,0 -256,-114.71 -256,-256c0,-141.29 114.71,-256 256,-256Zm0,96c-43.453,0 -48.902,0.184 -65.968,0.963c-17.03,0.777 -28.661,3.482 -38.839,7.437c-10.521,4.089 -19.444,9.56 -28.339,18.455c-8.895,8.895 -14.366,17.818 -18.455,28.339c-3.955,10.177 -6.659,21.808 -7.437,38.838c-0.778,17.066 -0.962,22.515 -0.962,65.968c0,43.453 0.184,48.902 0.962,65.968c0.778,17.03 3.482,28.661 7.437,38.838c4.089,10.521 9.56,19.444 18.455,28.34c8.895,8.895 17.818,14.366 28.339,18.455c10.178,3.954 21.809,6.659 38.839,7.436c17.066,0.779 22.515,0.963 65.968,0.963c43.453,0 48.902,-0.184 65.968,-0.963c17.03,-0.777 28.661,-3.482 38.838,-7.436c10.521,-4.089 19.444,-9.56 28.34,-18.455c8.895,-8.896 14.366,-17.819 18.455,-28.34c3.954,-10.177 6.659,-21.808 7.436,-38.838c0.779,-17.066 0.963,-22.515 0.963,-65.968c0,-43.453 -0.184,-48.902 -0.963,-65.968c-0.777,-17.03 -3.482,-28.661 -7.436,-38.838c-4.089,-10.521 -9.56,-19.444 -18.455,-28.339c-8.896,-8.895 -17.819,-14.366 -28.34,-18.455c-10.177,-3.955 -21.808,-6.66 -38.838,-7.437c-17.066,-0.779 -22.515,-0.963 -65.968,-0.963Zm0,28.829c42.722,0 47.782,0.163 64.654,0.933c15.6,0.712 24.071,3.318 29.709,5.509c7.469,2.902 12.799,6.37 18.397,11.969c5.6,5.598 9.067,10.929 11.969,18.397c2.191,5.638 4.798,14.109 5.509,29.709c0.77,16.872 0.933,21.932 0.933,64.654c0,42.722 -0.163,47.782 -0.933,64.654c-0.711,15.6 -3.318,24.071 -5.509,29.709c-2.902,7.469 -6.369,12.799 -11.969,18.397c-5.598,5.6 -10.928,9.067 -18.397,11.969c-5.638,2.191 -14.109,4.798 -29.709,5.509c-16.869,0.77 -21.929,0.933 -64.654,0.933c-42.725,0 -47.784,-0.163 -64.654,-0.933c-15.6,-0.711 -24.071,-3.318 -29.709,-5.509c-7.469,-2.902 -12.799,-6.369 -18.398,-11.969c-5.599,-5.598 -9.066,-10.928 -11.968,-18.397c-2.191,-5.638 -4.798,-14.109 -5.51,-29.709c-0.77,-16.872 -0.932,-21.932 -0.932,-64.654c0,-42.722 0.162,-47.782 0.932,-64.654c0.712,-15.6 3.319,-24.071 5.51,-29.709c2.902,-7.468 6.369,-12.799 11.968,-18.397c5.599,-5.599 10.929,-9.067 18.398,-11.969c5.638,-2.191 14.109,-4.797 29.709,-5.509c16.872,-0.77 21.932,-0.933 64.654,-0.933Zm0,49.009c-45.377,0 -82.162,36.785 -82.162,82.162c0,45.377 36.785,82.162 82.162,82.162c45.377,0 82.162,-36.785 82.162,-82.162c0,-45.377 -36.785,-82.162 -82.162,-82.162Zm0,135.495c-29.455,0 -53.333,-23.878 -53.333,-53.333c0,-29.455 23.878,-53.333 53.333,-53.333c29.455,0 53.333,23.878 53.333,53.333c0,29.455 -23.878,53.333 -53.333,53.333Zm104.609,-138.741c0,10.604 -8.597,19.199 -19.201,19.199c-10.603,0 -19.199,-8.595 -19.199,-19.199c0,-10.604 8.596,-19.2 19.199,-19.2c10.604,0 19.201,8.596 19.201,19.2Z" fill="#1C263C"/></svg>
                           </a>
                            <!-- youtube -->
                         <a class="social-icon" href="https://www.youtube.com/user/theavclub" > 
                        <svg height="20px" style="fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;" version="1.1" viewBox="0 0 512 512" width="20px" xml:space="preserve" xmlns="http://www.w3.org/2000/svg" xmlns:serif="http://www.serif.com/" xmlns:xlink="http://www.w3.org/1999/xlink"><path d="M256,0c141.29,0 256,114.71 256,256c0,141.29 -114.71,256 -256,256c-141.29,0 -256,-114.71 -256,-256c0,-141.29 114.71,-256 256,-256Zm153.315,178.978c-3.68,-13.769 -14.522,-24.61 -28.29,-28.29c-24.958,-6.688 -125.025,-6.688 -125.025,-6.688c0,0 -100.067,0 -125.025,6.688c-13.765,3.68 -24.61,14.521 -28.29,28.29c-6.685,24.955 -6.685,77.024 -6.685,77.024c0,0 0,52.067 6.685,77.02c3.68,13.769 14.525,24.614 28.29,28.293c24.958,6.685 125.025,6.685 125.025,6.685c0,0 100.067,0 125.025,-6.685c13.768,-3.679 24.61,-14.524 28.29,-28.293c6.685,-24.953 6.685,-77.02 6.685,-77.02c0,0 0,-52.069 -6.685,-77.024Zm-185.316,125.025l0,-96.002l83.137,48.001l-83.137,48.001Z" fill="#1C263C"/></svg>
                           </a>
                            <!-- x -->
                         <a class="social-icon" href="https://x.com/theavclub" > 
                      <svg height="20px" width="20px" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="216" height="216" viewBox="0 0 21600 21600"><image id="twitter-x" x="14" y="14" width="21572" height="21572" xlink:href="data:img/png;base64,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"/></svg>

                     
                           </a>
                             <!-- fb -->
                          <a class="social-icon" href="https://www.facebook.com/theavclub" > 
                         
                        
                      <svg height="20px" style="fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;" version="1.1" viewBox="0 0 512 512" width="20px" xml:space="preserve" xmlns="http://www.w3.org/2000/svg" xmlns:serif="http://www.serif.com/" xmlns:xlink="http://www.w3.org/1999/xlink"><path d="M255.022,511.998l0.229,0.001l-0.079,0l-0.15,-0.001Zm1.806,0.001l-0.079,0l0.229,-0.001l-0.15,0.001Zm-2.588,-0.005l0.247,0.001l-0.142,0l-0.105,-0.001Zm3.415,0.001l-0.142,0l0.247,-0.001l-0.105,0.001Zm-4.169,-0.007l0.165,0.001l-0.132,-0.001l-0.033,0Zm4.995,0l-0.132,0.001l0.165,-0.001l-0.033,0Zm0.826,-0.009l-0.058,0.001l0.223,-0.003l-0.165,0.002Zm-6.779,-0.002l0.223,0.003l-0.058,-0.001l-0.165,-0.002Zm7.604,-0.01l-0.135,0.002l0.275,-0.004l-0.14,0.002Zm-8.404,-0.002l0.275,0.004l-0.135,-0.002l-0.14,-0.002Zm9.228,-0.012l-0.182,0.003l0.254,-0.005l-0.072,0.002Zm-9.984,-0.002l0.254,0.005l-0.182,-0.003l-0.072,-0.002Zm-0.937,-0.019l0.225,0.005l-0.04,-0.001l-0.185,-0.004Zm11.745,0.004l-0.04,0.001l0.225,-0.005l-0.185,0.004Zm-12.567,-0.025l0.309,0.008l-0.125,-0.003l-0.184,-0.005Zm13.39,0.005l-0.125,0.003l0.309,-0.008l-0.184,0.005Zm0.823,-0.022l-0.201,0.006l0.316,-0.009l-0.115,0.003Zm-14.967,-0.003l0.316,0.009l-0.201,-0.006l-0.115,-0.003Zm-0.72,-0.022l0.225,0.007l-0.212,-0.007l-0.194,-0.006l0.181,0.006Zm16.509,0l-0.212,0.007l0.225,-0.007l0.181,-0.006l-0.194,0.006Zm0.821,-0.027l-0.112,0.004l0.345,-0.012l-0.233,0.008Zm-18.371,-0.008l0.345,0.012l-0.112,-0.004l-0.233,-0.008Zm-0.749,-0.028l0.362,0.013l-0.201,-0.007l-0.161,-0.006Zm19.941,0.006l-0.201,0.007l0.362,-0.013l-0.161,0.006Zm-20.676,-0.036l0.354,0.015l-0.277,-0.011l-0.077,-0.004Zm21.495,0.004l-0.277,0.011l0.354,-0.015l-0.077,0.004Zm-22.525,-0.049l0.38,0.017l-0.093,-0.003l-0.287,-0.014Zm23.345,0.014l-0.093,0.003l0.38,-0.017l-0.287,0.014Zm-24.084,-0.048l0.394,0.018l-0.186,-0.008l-0.208,-0.01Zm24.902,0.01l-0.186,0.008l0.394,-0.018l-0.208,0.01Zm-25.63,-0.047l0.397,0.02l-0.279,-0.013l-0.118,-0.007Zm26.448,0.007l-0.279,0.013l0.397,-0.02l-0.118,0.007Zm0.818,-0.043l-0.362,0.019l0.321,-0.017l0.378,-0.021l-0.337,0.019Zm-27.925,0.002l0.321,0.017l-0.362,-0.019l-0.337,-0.019l0.378,0.021Zm28.741,-0.048l-0.16,0.009l0.406,-0.023l-0.246,0.014Zm-29.844,-0.014l0.406,0.023l-0.16,-0.009l-0.246,-0.014Zm-0.722,-0.043l0.405,0.024l-0.253,-0.014l-0.152,-0.01Zm31.382,0.01l-0.253,0.014l0.405,-0.024l-0.152,0.01Zm-32.071,-0.053l0.365,0.023l-0.34,-0.021l-0.342,-0.022l0.317,0.02Zm32.887,0.002l-0.34,0.021l0.365,-0.023l0.317,-0.02l-0.342,0.022Zm0.814,-0.053l-0.122,0.008l0.387,-0.026l-0.265,0.018Zm-34.755,-0.018l0.387,0.026l-0.122,-0.008l-0.265,-0.018Zm-0.721,-0.05l0.38,0.027l-0.208,-0.014l-0.172,-0.013Zm36.29,0.013l-0.208,0.014l0.38,-0.027l-0.172,0.013Zm-37.009,-0.064l0.349,0.025l-0.271,-0.019l-0.078,-0.006Zm37.822,0.006l-0.271,0.019l0.349,-0.025l-0.078,0.006Zm-38.789,-0.079l0.306,0.023l-0.074,-0.005l-0.232,-0.018Zm39.602,0.018l-0.074,0.005l0.306,-0.023l-0.232,0.018Zm0.811,-0.063l-0.146,0.011l0.311,-0.025l-0.165,0.014Zm-41.157,-0.014l0.311,0.025l-0.146,-0.011l-0.165,-0.014Zm-0.725,-0.059l0.264,0.022l-0.186,-0.015l-0.078,-0.007Zm42.694,0.007l-0.186,0.015l0.264,-0.022l-0.078,0.007Zm-43.492,-0.074l0.079,0.007l-0.013,-0.001l-0.066,-0.006Zm44.302,0.006l-0.013,0.001l0.079,-0.007l-0.066,0.006Zm0.81,-0.071l-0.072,0.006l0.181,-0.016l-0.109,0.01Zm-45.965,-0.01l0.181,0.016l-0.072,-0.006l-0.109,-0.01Zm-0.75,-0.068l0.135,0.013l-0.084,-0.008l-0.051,-0.005Zm47.523,0.005l-0.084,0.008l0.135,-0.013l-0.051,0.005Zm-63.736,-2.025c-122.319,-19.226 -216,-125.203 -216,-252.887c0,-141.29 114.71,-256 256,-256c141.29,0 256,114.71 256,256c0,127.684 -93.681,233.661 -216,252.887l0,-178.887l59.65,0l11.35,-74l-71,0l0,-48.021c0,-20.245 9.918,-39.979 41.719,-39.979l32.281,0l0,-63c0,0 -29.296,-5 -57.305,-5c-58.476,0 -96.695,35.44 -96.695,99.6l0,56.4l-65,0l0,74l65,0l0,178.887Z" fill="#1C263C"/></svg>
                      
                          
                        
                    </a>
                        </div>
                      <!--  <a class="subscribe text" x="2" href="/membership-account"
                        aria-label="Log In/Subscribe">Log In/Subscribe</a>
                        -->
                  </div>
        </header>
       <!-- <div class="head-bottom-line"> </div> -->
        <div class="header-top-ad cell center dfp">
       <!-- </div> -->
    </div>
</div><main class="expanded site-body" id="site_body" role="main">
        <div class="grid-container">


         
<div class="grid-x grid-padding-x landing-top">
    
    
    <div class="large-12 cell articles-header show-for-small-only add-top-featured-margin">
        <a href="/articles/article-type/features/" class="float-left hed">Featured         </a>
    </div>
    <div class="large-12 cell articles">
        <ul>
                        
            <li>
                <a class="image" href="https://www.avclub.com/regretting-you-review">
                    <picture data-sizes="[&quot;(min-width: 40em)&quot;,&quot;(min-width: 64em)&quot;]" class="main"
                        data-sources="[&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/08/05163556/regretting-you-trailer-screenshot-square.jpg&quot;,&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/10/22121539/regretting-you-header.jpg&quot;,&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/10/22121539/regretting-you-header.jpg&quot;]">
                        <source media="(min-width: 40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22121539/regretting-you-header.jpg">
                        <source media="(min-width: 64em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22121539/regretting-you-header.jpg"><img class="no-lazy lazyload"
                            alt="Regretting You read Colleen Hoover? Then you probably shouldn't watch this romance"
                            src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/05163556/regretting-you-trailer-screenshot-square.jpg" decoding="async">
                    </picture><noscript><img class="no-lazy"
                            alt="Regretting You read Colleen Hoover? Then you probably shouldn't watch this romance"
                            src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/05163556/regretting-you-trailer-screenshot-square.jpg" data-eio="l"></noscript>
                </a>
                <a class="copy-container" href="https://www.avclub.com/regretting-you-review">
                    <b class="type hide-for-medium">Movies</b>
                    <b class="title"><i>Regretting You</i> read Colleen Hoover? Then you probably shouldn't watch this romance</b>
                    <b class="byline hide-for-medium">By Jacob Oller</b>
                    <b class="time hide-for-medium">October 23, 2025 | 3:00pm</b>
                </a>
            </li>

                        
            <li>
                <a class="image" href="https://www.avclub.com/5-to-watch-flashback-episodes-that-fill-in-all-the-gaps-lost-twin-peaks">
                    <picture data-sizes="[&quot;(min-width: 40em)&quot;,&quot;(min-width: 64em)&quot;]" class="main"
                        data-sources="[&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133542/5twoct-feature-squared.jpg&quot;,&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133607/5twoct-feature-header.jpg&quot;,&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133607/5twoct-feature-header.jpg&quot;]">
                        <source media="(min-width: 40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133607/5twoct-feature-header.jpg">
                        <source media="(min-width: 64em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133607/5twoct-feature-header.jpg"><img class="no-lazy lazyload"
                            alt="5 To Watch: Flashback episodes that fill in all the gaps"
                            src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133542/5twoct-feature-squared.jpg" decoding="async">
                    </picture><noscript><img class="no-lazy"
                            alt="5 To Watch: Flashback episodes that fill in all the gaps"
                            src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22133542/5twoct-feature-squared.jpg" data-eio="l"></noscript>
                </a>
                <a class="copy-container" href="https://www.avclub.com/5-to-watch-flashback-episodes-that-fill-in-all-the-gaps-lost-twin-peaks">
                    <b class="type hide-for-medium">Movies</b>
                    <b class="title">5 To Watch: Flashback episodes that fill in all the gaps</b>
                    <b class="byline hide-for-medium">By A.V. Club Staff</b>
                    <b class="time hide-for-medium">October 23, 2025 | 1:00pm</b>
                </a>
            </li>

                        
            <li>
                <a class="image" href="https://www.avclub.com/jon-m-chu-swears-crazy-rich-asians-tv-show-actually-happening">
                    <picture data-sizes="[&quot;(min-width: 40em)&quot;,&quot;(min-width: 64em)&quot;]" class="main"
                        data-sources="[&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122722/jon-m-chu-daily-show-screenshot-square.jpg&quot;,&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122736/jon-m-chu-daily-show-screenshot-feature.jpg&quot;,&quot;https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122736/jon-m-chu-daily-show-screenshot-feature.jpg&quot;]">
                        <source media="(min-width: 40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122736/jon-m-chu-daily-show-screenshot-feature.jpg">
                        <source media="(min-width: 64em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122736/jon-m-chu-daily-show-screenshot-feature.jpg"><img class="no-lazy lazyload"
                            alt="Jon M. Chu swears that Crazy Rich Asians sequel TV show is actually getting made"
                            src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122722/jon-m-chu-daily-show-screenshot-square.jpg" decoding="async">
                    </picture><noscript><img class="no-lazy"
                            alt="Jon M. Chu swears that Crazy Rich Asians sequel TV show is actually getting made"
                            src="https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122722/jon-m-chu-daily-show-screenshot-square.jpg" data-eio="l"></noscript>
                </a>
                <a class="copy-container" href="https://www.avclub.com/jon-m-chu-swears-crazy-rich-asians-tv-show-actually-happening">
                    <b class="type hide-for-medium">Movies</b>
                    <b class="title">Jon M. Chu swears that <i>Crazy Rich Asians</i> sequel TV show is actually getting made</b>
                    <b class="byline hide-for-medium">By William Hughes</b>
                    <b class="time hide-for-medium">October 24, 2025 | 12:37am</b>
                </a>
            </li>

            
        </ul>
    </div>
</div>

        <div class="grid-x landing-wrapper __web-inspector-hide-shortcut__">
            <div class="large-12 cell">
                <div class="grid-x small-up-1 medium-up-2 large-up-12">
                    <div class="large-auto medium-auto small-auto">

                        <div class="grid-x articles-standard" id="landing-more-featured">
            <div class="large-12 cell articles-header  show-for-medium"><a href="/articles/article-type/features" class="float-left hed">Features</a></div><ul class="articles grid-margin-x flex-container flex-dir-column"><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/ace-attorney-soundtrack-music" aria-label="We have no objections to Ace Attorney's action-packed music">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="We have no objections to Ace Attorney's action-packed music" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22132707/ace_attorney_music_151.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22132707/ace_attorney_music_151.jpg" alt="We have no objections to Ace Attorney's action-packed music" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/ace-attorney-soundtrack-music"><b class="title">We have no objections to <i>Ace Attorney</i>'s action-packed music</b><b class="byline">By Marc Normandin</b><b class="time" data-iso-date="2025-10-22T14:15:19+00:00">October 22, 2025 | 2:15pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/chicago-international-film-festival-2025-arco-the-plague-kontinental-25" aria-label="Exciting debuts and Radu Jude fill the Chicago International Film Festival">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Exciting debuts and Radu Jude fill the Chicago International Film Festival" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21165845/arco-squared.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21165845/arco-squared.jpg" alt="Exciting debuts and Radu Jude fill the Chicago International Film Festival" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/chicago-international-film-festival-2025-arco-the-plague-kontinental-25"><b class="title">Exciting debuts and Radu Jude fill the Chicago International Film Festival</b><b class="byline">By Jacob Oller</b><b class="time" data-iso-date="2025-10-22T14:00:17+00:00">October 22, 2025 | 2:00pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/michael-cyril-creighton-interview-only-murders-in-the-building-season-5" aria-label="Michael Cyril Creighton didn't plan to be Only Murders In The Building's fourth musketeer">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Michael Cyril Creighton didn't plan to be Only Murders In The Building's fourth musketeer" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21151309/mcc-omitb-1.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21151309/mcc-omitb-1.jpg" alt="Michael Cyril Creighton didn't plan to be Only Murders In The Building's fourth musketeer" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/michael-cyril-creighton-interview-only-murders-in-the-building-season-5"><b class="title">Michael Cyril Creighton didn't plan to be <I>Only Murders In The Building</I>'s fourth musketeer</b><b class="byline">By Saloni Gajjar</b><b class="time" data-iso-date="2025-10-22T08:00:10+00:00">October 22, 2025 | 8:00am</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/reunion-word-game-merriam-webster" aria-label="Reunion is a great post-car-crash game">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Reunion is a great post-car-crash game" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21163311/reunion_word_game_151.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21163311/reunion_word_game_151.jpg" alt="Reunion is a great post-car-crash game" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/reunion-word-game-merriam-webster"><b class="title"><i>Reunion</i> is a great post-car-crash game</b><b class="byline">By Wallace Truesdale</b><b class="time" data-iso-date="2025-10-21T17:30:10+00:00">October 21, 2025 | 5:30pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/super-metroid-music-soundtrack-silence" aria-label="The strength of Super Metroid's soundtrack is in its silences">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="The strength of Super Metroid's soundtrack is in its silences" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21162452/super_metroid_151.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21162452/super_metroid_151.jpg" alt="The strength of Super Metroid's soundtrack is in its silences" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/super-metroid-music-soundtrack-silence"><b class="title">The strength of <i>Super Metroid</i>'s soundtrack is in its silences</b><b class="byline">By Maddy Myers</b><b class="time" data-iso-date="2025-10-21T16:27:56+00:00">October 21, 2025 | 4:27pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/jeff-tweedy-cover-story" aria-label="COVER STORY | It’s a Tweedy Family Affair">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="COVER STORY | It’s a Tweedy Family Affair" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21145745/jeff-tweedy-sq.jpeg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21145745/jeff-tweedy-sq.jpeg" alt="COVER STORY | It’s a Tweedy Family Affair" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/jeff-tweedy-cover-story"><b class="title">COVER STORY | It’s a Tweedy Family Affair</b><b class="byline">By Matt Mitchell</b><b class="time" data-iso-date="2025-10-21T15:05:14+00:00">October 21, 2025 | 3:05pm</b></a></li><li class="more">
                    <a href="/articles/article-type/features">More Features</a>
                </li></ul>
            </div>
                     
                        <div class="grid-x articles-standard articles-reviews" id="landing-reviews">
            <div class="large-12 cell articles-header "><a href="/articles/article-type/reviews" class="float-left hed">Reviews</a></div><ul class="articles reviews grid-margin-x flex-container flex-dir-column"><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/regretting-you-review" aria-label="Regretting You read Colleen Hoover? Then you probably shouldn't watch this romance">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Regretting You read Colleen Hoover? Then you probably shouldn't watch this romance" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/05163556/regretting-you-trailer-screenshot-square.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/05163556/regretting-you-trailer-screenshot-square.jpg" alt="Regretting You read Colleen Hoover? Then you probably shouldn't watch this romance" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/regretting-you-review"><b class="title"><i>Regretting You</i> read Colleen Hoover? Then you probably shouldn't watch this romance</b><b class="rating"><i class="text">Rating</i><i class="number">C-</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/hedda-review" aria-label="Hedda reimagines Ibsen with psychological precision and ruthless energy">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Hedda reimagines Ibsen with psychological precision and ruthless energy" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22101942/hedda-squared.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22101942/hedda-squared.jpg" alt="Hedda reimagines Ibsen with psychological precision and ruthless energy" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/hedda-review"><b class="title"><i>Hedda</i> reimagines Ibsen with psychological precision and ruthless energy</b><b class="rating"><i class="text">Rating</i><i class="number">B+</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/nobody-wants-this-season-2-review-netflix" aria-label="Nobody Wants This mostly nails what comes after the grand gesture">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Nobody Wants This mostly nails what comes after the grand gesture" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22092107/nobody-wants-this-lead.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/22092107/nobody-wants-this-lead.jpg" alt="Nobody Wants This mostly nails what comes after the grand gesture" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/nobody-wants-this-season-2-review-netflix"><b class="title"><I>Nobody Wants This</I> mostly nails what comes after the grand gesture</b><b class="rating"><i class="text">Rating</i><i class="number">B+</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/gen-v-season-2-finale-recap" aria-label="Gen V's season 2 finale is déjà vu all over again">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Gen V's season 2 finale is déjà vu all over again" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/20193422/GENVS2finale-recap-squared.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/20193422/GENVS2finale-recap-squared.jpg" alt="Gen V's season 2 finale is déjà vu all over again" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/gen-v-season-2-finale-recap"><b class="title"><i>Gen V</i>'s season 2 finale is déjà vu all over again</b><b class="rating"><i class="text">Rating</i><i class="number">C+</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/the-hand-that-rocks-the-cradle-review" aria-label="Modern motherhood leads to murderous mayhem in The Hand That Rocks The Cradle remake">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Modern motherhood leads to murderous mayhem in The Hand That Rocks The Cradle remake" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21103220/the-hand-that-rocks-the-cradle-squared.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21103220/the-hand-that-rocks-the-cradle-squared.jpg" alt="Modern motherhood leads to murderous mayhem in The Hand That Rocks The Cradle remake" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/the-hand-that-rocks-the-cradle-review"><b class="title">Modern motherhood leads to murderous mayhem in <i>The Hand That Rocks The Cradle</i> remake</b><b class="rating"><i class="text">Rating</i><i class="number">B</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/dispatch-game-review" aria-label="Dispatch is a smart superhero story that lives up to Telltale’s legacy">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Dispatch is a smart superhero story that lives up to Telltale’s legacy" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21184715/dispatch_game_151.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21184715/dispatch_game_151.jpg" alt="Dispatch is a smart superhero story that lives up to Telltale’s legacy" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/dispatch-game-review"><b class="title"><I>Dispatch</I> is a smart superhero story that lives up to Telltale’s legacy</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/tame-impala-deadbeat-review" aria-label="Tame Impala Is Spread Too Thin On Deadbeat">
                        <picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21170525/tame-sq.jpg">
                            <img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Tame Impala Is Spread Too Thin On Deadbeat" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21170525/tame-sq.jpg" decoding="async" class="lazyload" />
                        </picture><noscript><img src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21170525/tame-sq.jpg" alt="Tame Impala Is Spread Too Thin On Deadbeat" data-eio="l" /></noscript>
                    </a><a class="auto cell copy-container" href="https://www.avclub.com/tame-impala-deadbeat-review"><b class="title">Tame Impala Is Spread Too Thin On <em>Deadbeat</em></b><b class="rating"><i class="text">Rating</i><i class="number">6.4</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/bugonia-review" aria-label="Yorgos Lanthimos neuters the politics of Bugonia's alien conspiracy">
                        <picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/08/28110118/Untitled-6.jpeg">
                            <img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Yorgos Lanthimos neuters the politics of Bugonia's alien conspiracy" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/28110118/Untitled-6.jpeg" decoding="async" class="lazyload" />
                        </picture><noscript><img src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/28110118/Untitled-6.jpeg" alt="Yorgos Lanthimos neuters the politics of Bugonia's alien conspiracy" data-eio="l" /></noscript>
                    </a><a class="auto cell copy-container" href="https://www.avclub.com/bugonia-review"><b class="title">Yorgos Lanthimos neuters the politics of <i>Bugonia</i>'s alien conspiracy</b><b class="rating"><i class="text">Rating</i><i class="number">C+</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/lazarus-review-prime-video-tv-harlan-coben" aria-label="In Harlan Coben's Lazarus, a groan-worthy ghost is born">
                        <picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/20164907/Lazarus-review-squared.jpg">
                            <img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="In Harlan Coben's Lazarus, a groan-worthy ghost is born" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/20164907/Lazarus-review-squared.jpg" decoding="async" class="lazyload" />
                        </picture><noscript><img src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/20164907/Lazarus-review-squared.jpg" alt="In Harlan Coben's Lazarus, a groan-worthy ghost is born" data-eio="l" /></noscript>
                    </a><a class="auto cell copy-container" href="https://www.avclub.com/lazarus-review-prime-video-tv-harlan-coben"><b class="title">In <i>Harlan Coben's Lazarus</i>, a groan-worthy ghost is born</b><b class="rating"><i class="text">Rating</i><i class="number">D</i></b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/talamasca-the-secret-order-review-amc-tv" aria-label="Talamasca: The Secret Order taps a vein Anne Rice never did">
                        <picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/17153926/TALAMASCA-review-squared.jpg">
                            <img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Talamasca: The Secret Order taps a vein Anne Rice never did" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/17153926/TALAMASCA-review-squared.jpg" decoding="async" class="lazyload" />
                        </picture><noscript><img src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/17153926/TALAMASCA-review-squared.jpg" alt="Talamasca: The Secret Order taps a vein Anne Rice never did" data-eio="l" /></noscript>
                    </a><a class="auto cell copy-container" href="https://www.avclub.com/talamasca-the-secret-order-review-amc-tv"><b class="title"><i>Talamasca: The Secret Order</i> taps a vein Anne Rice never did</b><b class="rating"><i class="text">Rating</i><i class="number">B+</i></b></a></li></ul><ul class="articles grid-margin-x flex-container flex-dir-column more"><li class="more">
                    <a href="/articles/article-type/reviews">More Reviews</a>
                </li></ul>
            </div>                           <div class="newsletter-container">
                            <div class="newsletter-copy-container">
                                <p class="copy-a">GET AV CLUB RIGHT IN YOUR INBOX</p>
                                <p class="copy-b">Pop culture obsessives writing for the pop culture obsessed.</p>

                                <p id="newsletter-signup-result" class="copy-a"></p>
                                <div id="newsletter-signup" class="copy newsletter-signup">
                                    <script>(function() {
	window.mc4wp = window.mc4wp || {
		listeners: [],
		forms: {
			on: function(evt, cb) {
				window.mc4wp.listeners.push(
					{
						event   : evt,
						callback: cb
					}
				);
			}
		}
	}
})();
</script><!-- Mailchimp for WordPress v4.10.7 - https://wordpress.org/plugins/mailchimp-for-wp/ --><form id="mc4wp-form-1" class="mc4wp-form mc4wp-form-261672" method="post" data-id="261672" data-name="Subscribe Form" ><div class="mc4wp-form-fields"><p class="grid-x grid-margin-x">
  <input id="newsletter-signup-email" class="medium-8 small-8 cell" type="email"
         placeholder="email address" name="EMAIL">
  <button type="submit" id="newsletter-signup-submit" class="medium-2 small-4 button">Sign
    Up</button>
  
</p></div><label style="display: none !important;">Leave this field empty if you're human: <input type="text" name="_mc4wp_honeypot" value="" tabindex="-1" autocomplete="off" /></label><input type="hidden" name="_mc4wp_timestamp" value="1761284289" /><input type="hidden" name="_mc4wp_form_id" value="261672" /><input type="hidden" name="_mc4wp_form_element_id" value="mc4wp-form-1" /><div class="mc4wp-response"></div></form><!-- / Mailchimp for WordPress Plugin -->                                </div>
                            </div>

                        </div>

                         <div class="grid-x articles-standard" id="landing-detail-news">
            <div class="large-12 cell articles-header "><a href="/articles/article-type/news" class="float-left hed">News</a></div><ul class="articles grid-margin-x flex-container flex-dir-column"><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/jon-m-chu-swears-crazy-rich-asians-tv-show-actually-happening" aria-label="Jon M. Chu swears that Crazy Rich Asians sequel TV show is actually getting made">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Jon M. Chu swears that Crazy Rich Asians sequel TV show is actually getting made" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122722/jon-m-chu-daily-show-screenshot-square.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/07/07122722/jon-m-chu-daily-show-screenshot-square.jpg" alt="Jon M. Chu swears that Crazy Rich Asians sequel TV show is actually getting made" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/jon-m-chu-swears-crazy-rich-asians-tv-show-actually-happening"><b class="title">Jon M. Chu swears that <i>Crazy Rich Asians</i> sequel TV show is actually getting made</b><b class="byline">By William Hughes</b><b class="time" data-iso-date="2025-10-24T00:37:35+00:00">October 24, 2025 | 12:37am</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/writers-guild-pledges-to-block-warner-bros-merger" aria-label="Writers Guilds pledge to "block" Warner Bros. merger, call it a "disaster"">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Writers Guilds pledge to "block" Warner Bros. merger, call it a "disaster"" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/03/04132203/Untitled-14.jpeg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/03/04132203/Untitled-14.jpeg" alt="Writers Guilds pledge to "block" Warner Bros. merger, call it a "disaster"" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/writers-guild-pledges-to-block-warner-bros-merger"><b class="title">Writers Guilds pledge to "block" Warner Bros. merger, call it a "disaster"</b><b class="byline">By William Hughes</b><b class="time" data-iso-date="2025-10-23T21:18:05+00:00">October 23, 2025 | 9:18pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/michael-b-jordan-in-talks-for-miami-vice-joseph-kosinski" aria-label="Michael B. Jordan might be half of the new Miami Vice">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Michael B. Jordan might be half of the new Miami Vice" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/04/26133038/jordan-lead.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/04/26133038/jordan-lead.jpg" alt="Michael B. Jordan might be half of the new Miami Vice" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/michael-b-jordan-in-talks-for-miami-vice-joseph-kosinski"><b class="title">Michael B. Jordan might be half of the new <i>Miami Vice</i></b><b class="byline">By William Hughes</b><b class="time" data-iso-date="2025-10-23T20:18:22+00:00">October 23, 2025 | 8:18pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/frankie-muniz-malcolm-in-the-middle-photo" aria-label="Frankie Muniz shares photographic evidence of Malcolm In The Middle reunion">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Frankie Muniz shares photographic evidence of Malcolm In The Middle reunion" data-src="https://img.pastemagazine.com/wp-content/avuploads/2015/11/13121433/MixCollage-13-Dec-2024-11-14-AM-821.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2015/11/13121433/MixCollage-13-Dec-2024-11-14-AM-821.jpg" alt="Frankie Muniz shares photographic evidence of Malcolm In The Middle reunion" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/frankie-muniz-malcolm-in-the-middle-photo"><b class="title">Frankie Muniz shares photographic evidence of <i>Malcolm In The Middle</i> reunion</b><b class="byline">By Matt Schimkowitz</b><b class="time" data-iso-date="2025-10-23T20:15:26+00:00">October 23, 2025 | 8:15pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/hunt-for-ben-solo-banner-flown-over-disney-adam-driver" aria-label="Kylo Ren fans have already flown a "Save #TheHuntForBenSolo" banner over Disney">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Kylo Ren fans have already flown a "Save #TheHuntForBenSolo" banner over Disney" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/23191102/driver-star-wars-lead.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/23191102/driver-star-wars-lead.jpg" alt="Kylo Ren fans have already flown a "Save #TheHuntForBenSolo" banner over Disney" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/hunt-for-ben-solo-banner-flown-over-disney-adam-driver"><b class="title">Kylo Ren fans have already flown a "Save #TheHuntForBenSolo" banner over Disney</b><b class="byline">By William Hughes</b><b class="time" data-iso-date="2025-10-23T19:16:38+00:00">October 23, 2025 | 7:16pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/dark-winds-season-four-release-announcement" aria-label="First look at Dark Winds' fourth season blows into town">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="First look at Dark Winds' fourth season blows into town" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/04/10181421/dark-winds-episode-6.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/04/10181421/dark-winds-episode-6.jpg" alt="First look at Dark Winds' fourth season blows into town" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/dark-winds-season-four-release-announcement"><b class="title">First look at <i>Dark Winds</i>' fourth season blows into town</b><b class="byline">By Matt Schimkowitz</b><b class="time" data-iso-date="2025-10-23T19:11:27+00:00">October 23, 2025 | 7:11pm</b></a></li><li class="more">
                    <a href="/articles/article-type/news">More News</a>
                </li></ul>
            </div><div class="grid-x articles-standard" id="landing-lists">
            <div class="large-12 cell articles-header "><a href="/articles/article-type/lists" class="float-left hed">Lists</a></div><ul class="articles grid-margin-x flex-container flex-dir-column"><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/what-to-watch-on-netflix-best-tv-shows-1848758095" aria-label="What to watch on Netflix: The best TV shows streaming right now">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="What to watch on Netflix: The best TV shows streaming right now" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/09/15215357/iwtv-netflix.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/09/15215357/iwtv-netflix.jpg" alt="What to watch on Netflix: The best TV shows streaming right now" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/what-to-watch-on-netflix-best-tv-shows-1848758095"><b class="title">What to watch on Netflix: The best TV shows streaming right now</b><b class="byline">By The A.V. Club</b><b class="time" data-iso-date="2025-10-22T18:29:00+00:00">October 22, 2025 | 6:29pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/taylor-swift-albums-ranked" aria-label="Every Taylor Swift Album Ranked">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Every Taylor Swift Album Ranked" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21173018/tsranked-sq.jpeg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/21173018/tsranked-sq.jpeg" alt="Every Taylor Swift Album Ranked" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/taylor-swift-albums-ranked"><b class="title">Every Taylor Swift Album Ranked</b><b class="byline">By Ellen Johnson</b><b class="time" data-iso-date="2025-10-21T03:31:18+00:00">October 21, 2025 | 3:31am</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/what-to-watch-disney-plus" aria-label="What to watch on Disney Plus: The best shows streaming right now">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="What to watch on Disney Plus: The best shows streaming right now" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/12100410/high-potential-s2.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/08/12100410/high-potential-s2.jpg" alt="What to watch on Disney Plus: The best shows streaming right now" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/what-to-watch-disney-plus"><b class="title">What to watch on Disney Plus: The best shows streaming right now</b><b class="byline">By The A.V. Club</b><b class="time" data-iso-date="2025-10-20T20:27:00+00:00">October 20, 2025 | 8:27pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/hulu-what-to-watch" aria-label="What to watch on Hulu: The best shows streaming right now">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="What to watch on Hulu: The best shows streaming right now" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/09/13100531/the-lowdown-hulu.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2025/09/13100531/the-lowdown-hulu.jpg" alt="What to watch on Hulu: The best shows streaming right now" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/hulu-what-to-watch"><b class="title">What to watch on Hulu: The best shows streaming right now</b><b class="byline">By The A.V. Club</b><b class="time" data-iso-date="2025-10-17T17:54:00+00:00">October 17, 2025 | 5:54pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/the-best-available-movies-to-watch-on-netflix-1842540580" aria-label="The best movies on Netflix right now">
                    
                        <img class="no-lazy lazyload" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAJcAAACXAQAAAAAw5PTUAAAAAnRSTlMAAHaTzTgAAAAaSURBVEjH7cEBDQAAAMKg909tDjegAACARwMLzAABUcE4zwAAAABJRU5ErkJggg==" alt="The best movies on Netflix right now" data-src="https://img.pastemagazine.com/wp-content/avuploads/2022/09/15005438/8a685e3fae96381c2a4e67a628364e44_sq.jpg" decoding="async" width="151" height="151" data-eio-rwidth="151" data-eio-rheight="151" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2022/09/15005438/8a685e3fae96381c2a4e67a628364e44_sq.jpg" alt="The best movies on Netflix right now" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/the-best-available-movies-to-watch-on-netflix-1842540580"><b class="title">The best movies on Netflix right now</b><b class="byline">By The A.V. Club</b><b class="time" data-iso-date="2025-10-01T01:00:00+00:00">October 1, 2025 | 1:00am</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.avclub.com/the-best-movies-right-now-on-amazon-prime-video-1842870366" aria-label="The best movies on Amazon Prime Video right now">
                    
                        <img class="no-lazy lazyload" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAJcAAACXAQAAAAAw5PTUAAAAAnRSTlMAAHaTzTgAAAAaSURBVEjH7cEBDQAAAMKg909tDjegAACARwMLzAABUcE4zwAAAABJRU5ErkJggg==" alt="The best movies on Amazon Prime Video right now" data-src="https://img.pastemagazine.com/wp-content/avuploads/2022/09/15005729/71d4c142c6deb44e069fe8083a7c7b5c_sq.jpg" decoding="async" width="151" height="151" data-eio-rwidth="151" data-eio-rheight="151" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/avuploads/2022/09/15005729/71d4c142c6deb44e069fe8083a7c7b5c_sq.jpg" alt="The best movies on Amazon Prime Video right now" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.avclub.com/the-best-movies-right-now-on-amazon-prime-video-1842870366"><b class="title">The best movies on Amazon Prime Video right now</b><b class="byline">By The A.V. Club</b><b class="time" data-iso-date="2025-10-01T01:00:00+00:00">October 1, 2025 | 1:00am</b></a></li><li class="more">
                    <a href="/articles/article-type/lists">More Lists</a>
                </li></ul>
            </div><div class="grid-x articles-standard" id="also-from-paste">
            <div class="large-12 cell articles-header "><a href="/articles/article-type/external" class="float-left hed v2">Also From Paste Media</a></div><ul class="articles grid-margin-x flex-container flex-dir-column"><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.jezebel.com/which-piece-of-stolen-louvre-jewelry-are-you-based-on-your-zodiac-sign" aria-label="Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign" data-src="https://img.pastemagazine.com/wp-content/juploads/2025/10/louvre151.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/juploads/2025/10/louvre151.jpg" alt="Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.jezebel.com/which-piece-of-stolen-louvre-jewelry-are-you-based-on-your-zodiac-sign"><b class="site jezebel">JEZEBEL</b><b class="title">Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign</b><b class="byline">By Lauren Tousignant</b><b class="time" data-iso-date="2025-10-23T11:26:36+00:00">October 23, 2025 | 11:26am</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.pastemagazine.com/music/best-new-songs/10-songs-you-need-to-hear-this-week-october-23-2025" aria-label="10 Songs You Need to Hear This Week (October 23, 2025)">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="10 Songs You Need to Hear This Week (October 23, 2025)" data-src="https://img.pastemagazine.com/wp-content/uploads/2025/10/23130418/CE8AE569-DD0B-442E-8A83-FFE52C4873CC-e1761239068362.jpeg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/uploads/2025/10/23130418/CE8AE569-DD0B-442E-8A83-FFE52C4873CC-e1761239068362.jpeg" alt="10 Songs You Need to Hear This Week (October 23, 2025)" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.pastemagazine.com/music/best-new-songs/10-songs-you-need-to-hear-this-week-october-23-2025"><b class="site paste">PASTE</b><b class="title">10 Songs You Need to Hear This Week (October 23, 2025)</b><b class="byline">By Paste Staff</b><b class="time" data-iso-date="2025-10-23T14:00:01+00:00">October 23, 2025 | 2:00pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.splinter.com/do-ice-recruits-know-how-to-read" aria-label="Do ICE Recruits Know How to Read?">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Do ICE Recruits Know How to Read?" data-src="https://img.pastemagazine.com/wp-content/suploads/2025/10/151-Secretary_Noem_leading_an_ICE_raid_on_illegal_immigrants_in_New_York_City_2025.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/suploads/2025/10/151-Secretary_Noem_leading_an_ICE_raid_on_illegal_immigrants_in_New_York_City_2025.jpg" alt="Do ICE Recruits Know How to Read?" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.splinter.com/do-ice-recruits-know-how-to-read"><b class="site splinter">SPLINTER</b><b class="title">Do ICE Recruits Know How to Read?</b><b class="byline">By Jacob Weindling</b><b class="time" data-iso-date="2025-10-23T14:24:41+00:00">October 23, 2025 | 2:24pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.endlessmode.com/anime/uma-musume/umamusume-cinderella-gray-explained-sports-drama" aria-label="I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama" data-src="https://img.pastemagazine.com/wp-content/uploads/2025/10/22170537/umamusume-cinderella-gray-lead-1.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/uploads/2025/10/22170537/umamusume-cinderella-gray-lead-1.jpg" alt="I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.endlessmode.com/anime/uma-musume/umamusume-cinderella-gray-explained-sports-drama"><b class="site endlessmode">ENDLESS MODE</b><b class="title">I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama</b><b class="byline">By Elijah Gonzalez</b><b class="time" data-iso-date="2025-10-23T16:00:13+00:00">October 23, 2025 | 4:00pm</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.jezebel.com/grimes-got-a-face-tattoo" aria-label="Grimes Got a Face Tattoo">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Grimes Got a Face Tattoo" data-src="https://img.pastemagazine.com/wp-content/juploads/2025/10/grimes151sdf.jpg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/juploads/2025/10/grimes151sdf.jpg" alt="Grimes Got a Face Tattoo" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.jezebel.com/grimes-got-a-face-tattoo"><b class="site jezebel">JEZEBEL</b><b class="title">Grimes Got a Face Tattoo</b><b class="byline">By Audra Heinrichs</b><b class="time" data-iso-date="2025-10-23T09:46:28+00:00">October 23, 2025 | 9:46am</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image" href="https://www.pastemagazine.com/music/rush/rush-power-windows-turns-40" aria-label="Wild Kinetic Dreams: Rush’s Power Windows at 40">
                    
                        <img class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Wild Kinetic Dreams: Rush’s Power Windows at 40" data-src="https://img.pastemagazine.com/wp-content/uploads/2025/10/22183223/AF50F6DF-E738-46CB-85D1-08ABB27BB5B2-e1761172365926.jpeg" decoding="async" /><noscript><img class="no-lazy" src="https://img.pastemagazine.com/wp-content/uploads/2025/10/22183223/AF50F6DF-E738-46CB-85D1-08ABB27BB5B2-e1761172365926.jpeg" alt="Wild Kinetic Dreams: Rush’s Power Windows at 40" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container" href="https://www.pastemagazine.com/music/rush/rush-power-windows-turns-40"><b class="site paste">PASTE</b><b class="title">Wild Kinetic Dreams: Rush’s <em>Power Windows</em> at 40</b><b class="byline">By Andy Steiner</b><b class="time" data-iso-date="2025-10-23T09:00:59+00:00">October 23, 2025 | 9:00am</b></a></li><li class="grid-x grid-padding-x"><a x="scott" class="large-3 medium-3 cell image" href="https://www.splinter.com/sports-embraced-the-devil-and-now-the-devil-is-at-their-doorstep" aria-label="Sports Embraced the Devil, and Now the Devil Is At their Doorstep">
                        <picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/suploads/2024/04/Adam-Silver-Jontay-Porter-1-e1713381237690.jpg">
                            <img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Sports Embraced the Devil, and Now the Devil Is At their Doorstep" data-src="https://img.pastemagazine.com/wp-content/suploads/2024/04/Adam-Silver-Jontay-Porter-1-e1713381237690.jpg" decoding="async" class="lazyload" />
                        </picture><noscript><img src="https://img.pastemagazine.com/wp-content/suploads/2024/04/Adam-Silver-Jontay-Porter-1-e1713381237690.jpg" alt="Sports Embraced the Devil, and Now the Devil Is At their Doorstep" data-eio="l" /></noscript>
                    </a><a class="auto cell copy-container" href="https://www.splinter.com/sports-embraced-the-devil-and-now-the-devil-is-at-their-doorstep"><b class="site splinter">SPLINTER</b><b class="title">Sports Embraced the Devil, and Now the Devil Is At their Doorstep</b><b class="byline">By Jacob Weindling</b><b class="time" data-iso-date="2025-10-23T12:16:43+00:00">October 23, 2025 | 12:16pm</b></a></li><li class="grid-x grid-padding-x"><a x="scott" class="large-3 medium-3 cell image" href="https://www.endlessmode.com/article/life-is-strange-endures-a-decade-later-thanks-to-its-music" aria-label="Life Is Strange Endures a Decade Later Thanks To Its Music">
                        <picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/uploads/2025/10/23150135/life_is_strange_hallway_151.jpg">
                            <img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Life Is Strange Endures a Decade Later Thanks To Its Music" data-src="https://img.pastemagazine.com/wp-content/uploads/2025/10/23150135/life_is_strange_hallway_151.jpg" decoding="async" class="lazyload" />
                        </picture><noscript><img src="https://img.pastemagazine.com/wp-content/uploads/2025/10/23150135/life_is_strange_hallway_151.jpg" alt="Life Is Strange Endures a Decade Later Thanks To Its Music" data-eio="l" /></noscript>
                    </a><a class="auto cell copy-container" href="https://www.endlessmode.com/article/life-is-strange-endures-a-decade-later-thanks-to-its-music"><b class="site endlessmode">ENDLESS MODE</b><b class="title"><i>Life Is Strange</i> Endures a Decade Later Thanks To Its Music</b><b class="byline">By Willa Rowe</b><b class="time" data-iso-date="2025-10-23T15:04:13+00:00">October 23, 2025 | 3:04pm</b></a></li></ul>
            </div><!-- RevContent -->
  <div data-widget-host="revcontent" data-pub-id="196664" data-widget-id="286664"></div>
  <script src="https://delivery.revcontent.com/196664/286664/widget.js"></script>                     
                    </div>

                    <aside id="sidebar" role="complementary" class="large-3 medium-3 small-auto">

    <li id="block-12" class="widget-container widget_block"><div class="htlad-top_rectangle" id="top_rectangle"></div><div class="vertical-ad-spacer"></div></li><li id="block-17" class="widget-container widget_block"><p>
        <div class="grid-x articles-abbreviated" id="article-detail-essentials-small">
            <div class="large-12 cell articles-header">
                <span class="float-left hed">Editors' Picks</span>
            </div>
            <ul class="articles grid-margin-x flex-container flex-dir-column">
                <li class="grid-x grid-padding-x">
                  <a href="https://www.avclub.com/return-of-the-king-70th-anniversary-scouring-of-the-shire" class="large-3 medium-3 cell image sidebar"><picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/14185345/scouring-lead.jpg">
                            <img decoding="async" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Why do Return Of The King adaptations flinch away from its most crucial chapter?" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/14185345/scouring-lead.jpg" class="lazyload" />
                        </picture><noscript><img decoding="async" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/14185345/scouring-lead.jpg" alt="Why do Return Of The King adaptations flinch away from its most crucial chapter?" data-eio="l" /></noscript>
                        </a>
                    <a href="https://www.avclub.com/return-of-the-king-70th-anniversary-scouring-of-the-shire" class="auto cell copy-container noimage">
                    <b class="title">Why do <i>Return Of The King</i> adaptations flinch away from its most crucial chapter?</b>
                    <b class="byline hide-for-large">By Grace Benfell</b>
                    <b class="time hide-for-medium" data-iso-date="2025-10-20T10:00:42+00:00">October 20, 2025 | 10:00am</b>
                    </a>
                </li>
                <li class="grid-x grid-padding-x">
                  <a href="https://www.avclub.com/the-chair-company-recap-season-1-episode-2" class="large-3 medium-3 cell image sidebar"><picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/17115819/ChairCompany2-recap-squared.jpg">
                            <img decoding="async" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="The Chair Company’s darkness starts to seep out" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/17115819/ChairCompany2-recap-squared.jpg" class="lazyload" />
                        </picture><noscript><img decoding="async" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/17115819/ChairCompany2-recap-squared.jpg" alt="The Chair Company’s darkness starts to seep out" data-eio="l" /></noscript>
                        </a>
                    <a href="https://www.avclub.com/the-chair-company-recap-season-1-episode-2" class="auto cell copy-container noimage">
                    <b class="title"><i>The Chair Company</i>’s darkness starts to seep out</b>
                    <b class="byline hide-for-large">By Erik Adams</b>
                    <b class="time hide-for-medium" data-iso-date="2025-10-19T22:30:05+00:00">October 19, 2025 | 10:30pm</b>
                    </a>
                </li>
                <li class="grid-x grid-padding-x">
                  <a href="https://www.avclub.com/task-season-1-finale-recap-a-still-small-voice" class="large-3 medium-3 cell image sidebar"><picture class="lazyload">
                            <source media="(min-width:40em)"  data-srcset="https://img.pastemagazine.com/wp-content/avuploads/2025/10/16155428/taskfinale-recap-squared.jpg">
                            <img decoding="async" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Task's gentle yet intense finale ties up some emotional loose ends" data-src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/16155428/taskfinale-recap-squared.jpg" class="lazyload" />
                        </picture><noscript><img decoding="async" src="https://img.pastemagazine.com/wp-content/avuploads/2025/10/16155428/taskfinale-recap-squared.jpg" alt="Task's gentle yet intense finale ties up some emotional loose ends" data-eio="l" /></noscript>
                        </a>
                    <a href="https://www.avclub.com/task-season-1-finale-recap-a-still-small-voice" class="auto cell copy-container noimage">
                    <b class="title"><i>Task</i>'s gentle yet intense finale ties up some emotional loose ends</b>
                    <b class="byline hide-for-large">By Caroline Siede</b>
                    <b class="time hide-for-medium" data-iso-date="2025-10-19T22:00:02+00:00">October 19, 2025 | 10:00pm</b>
                    </a>
                </li></ul>
                </div></p>
</li><li id="block-13" class="widget-container widget_block"><div class="htlad-middle_rectangle" id="middle_rectangle_xa"></div><div class="vertical-ad-spacer"></div></li><li id="block-10" class="widget-container widget_block"><p><div class="grid-x articles-standard" id="">
            <div class="large-12 cell articles-header  show-for-medium"><a href="#" class="float-left hed v2">Paste Media</a></div><ul class="articles grid-margin-x flex-container flex-dir-column"><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image sidebar" href="https://www.jezebel.com/which-piece-of-stolen-louvre-jewelry-are-you-based-on-your-zodiac-sign" aria-label="Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign">
                    
                        <img decoding="async" class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign" data-src="https://img.pastemagazine.com/wp-content/juploads/2025/10/louvre151.jpg" /><noscript><img decoding="async" class="no-lazy" src="https://img.pastemagazine.com/wp-content/juploads/2025/10/louvre151.jpg" alt="Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container sidebar" href="https://www.jezebel.com/which-piece-of-stolen-louvre-jewelry-are-you-based-on-your-zodiac-sign"><b class="site jezebel">JEZEBEL</b><b class="title">Which Piece of Stolen Louvre Jewelry Are You, Based on Your Zodiac Sign</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image sidebar" href="https://www.pastemagazine.com/music/best-new-songs/10-songs-you-need-to-hear-this-week-october-23-2025" aria-label="10 Songs You Need to Hear This Week (October 23, 2025)">
                    
                        <img decoding="async" class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="10 Songs You Need to Hear This Week (October 23, 2025)" data-src="https://img.pastemagazine.com/wp-content/uploads/2025/10/23130418/CE8AE569-DD0B-442E-8A83-FFE52C4873CC-e1761239068362.jpeg" /><noscript><img decoding="async" class="no-lazy" src="https://img.pastemagazine.com/wp-content/uploads/2025/10/23130418/CE8AE569-DD0B-442E-8A83-FFE52C4873CC-e1761239068362.jpeg" alt="10 Songs You Need to Hear This Week (October 23, 2025)" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container sidebar" href="https://www.pastemagazine.com/music/best-new-songs/10-songs-you-need-to-hear-this-week-october-23-2025"><b class="site paste">PASTE</b><b class="title">10 Songs You Need to Hear This Week (October 23, 2025)</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image sidebar" href="https://www.splinter.com/do-ice-recruits-know-how-to-read" aria-label="Do ICE Recruits Know How to Read?">
                    
                        <img decoding="async" class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="Do ICE Recruits Know How to Read?" data-src="https://img.pastemagazine.com/wp-content/suploads/2025/10/151-Secretary_Noem_leading_an_ICE_raid_on_illegal_immigrants_in_New_York_City_2025.jpg" /><noscript><img decoding="async" class="no-lazy" src="https://img.pastemagazine.com/wp-content/suploads/2025/10/151-Secretary_Noem_leading_an_ICE_raid_on_illegal_immigrants_in_New_York_City_2025.jpg" alt="Do ICE Recruits Know How to Read?" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container sidebar" href="https://www.splinter.com/do-ice-recruits-know-how-to-read"><b class="site splinter">SPLINTER</b><b class="title">Do ICE Recruits Know How to Read?</b></a></li><li class="grid-x grid-padding-x"><a class="large-3 medium-3 cell image sidebar" href="https://www.endlessmode.com/anime/uma-musume/umamusume-cinderella-gray-explained-sports-drama" aria-label="I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama">
                    
                        <img decoding="async" class="no-lazy lazyload" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" alt="I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama" data-src="https://img.pastemagazine.com/wp-content/uploads/2025/10/22170537/umamusume-cinderella-gray-lead-1.jpg" /><noscript><img decoding="async" class="no-lazy" src="https://img.pastemagazine.com/wp-content/uploads/2025/10/22170537/umamusume-cinderella-gray-lead-1.jpg" alt="I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama" data-eio="l" /></noscript>
                   
                </a><a class="auto cell copy-container sidebar" href="https://www.endlessmode.com/anime/uma-musume/umamusume-cinderella-gray-explained-sports-drama"><b class="site endlessmode">ENDLESS MODE</b><b class="title">I Regret To Inform You That the Horse Girl Anime Is an Extremely Compelling Sports Drama</b></a></li></ul>
            </div></p>
</li><li id="block-21" class="widget-container widget_block"><div class="htlad-sidebar_rectangle" id="sidebar_rectangle"></div><div class="vertical-ad-spacer"></div></li><li id="block-23" class="widget-container widget_block"><div class="htlad-middle_rectangle" id="middle_rectangle_x01"></div><div class="vertical-ad-spacer"></div></li><li id="block-11" class="widget-container widget_block"><div class="htlad-bottom_rectangle" id="bottom_rectangle"></div>
<div class="vertical-ad-spacer"></div>


<div class="htlad-bottom_rectangle" id="bottom_rectangle_x02"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-middle_rectangle" id="middle_rectangle_x01"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-middle_rectangle" id="middle_rectangle_x02"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-bottom_rectangle" id="bottom_rectangle_x03"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-middle_rectangle" id="middle_rectangle_x03"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-bottom_rectangle" id="bottom_rectangle_x04"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-middle_rectangle" id="middle_rectangle_x04"></div>
<div class="vertical-ad-spacer"></div>


<div class="htlad-bottom_rectangle" id="bottom_rectangle_x05"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-middle_rectangle" id="middle_rectangle_x05"></div>
<div class="vertical-ad-spacer"></div>



<div class="htlad-bottom_rectangle" id="bottom_rectangle_x06"></div>
<div class="vertical-ad-spacer"></div>
<div class="htlad-middle_rectangle" id="middle_rectangle_x06"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-bottom_rectangle" id="bottom_rectangle_x07"></div>
<div class="vertical-ad-spacer"></div>
<div class="htlad-middle_rectangle" id="middle_rectangle_x07"></div>
<div class="vertical-ad-spacer"></div>

<div class="htlad-bottom_rectangle" id="bottom_rectangle_x08"></div>
<div class="vertical-ad-spacer"></div>
<div class="htlad-middle_rectangle" id="middle_rectangle_x08"></div>
<div class="vertical-ad-spacer"></div>


<div class="htlad-bottom_rectangle" id="bottom_rectangle_x09"></div>
<div class="vertical-ad-spacer"></div>
<div class="htlad-middle_rectangle" id="middle_rectangle_x09"></div>
<div class="vertical-ad-spacer"></div>


<div class="htlad-bottom_rectangle" id="bottom_rectangle_x10"></div>
<div class="vertical-ad-spacer"></div>
<div class="htlad-middle_rectangle" id="middle_rectangle_x10"></div>
<div class="vertical-ad-spacer"></div></li><li id="block-20" class="widget-container widget_block widget_text">
<p></p>
</li>
</aside>                </div>
            </div>
        </div>
    </div>
</main>
<footer id="master-footer" class="row" role="contentinfo">
    <!-- <div class="grid-container">
        <div class="grid-x landing-wrapper __web-inspector-hide-shortcut__">
            <div class="large-12 cell">
                <div class="grid-x small-up-1 medium-up-2 large-up-12">
                    <div class="large-auto medium-auto small-auto"> -->
    <ul id="menu-footer-menu" class="menu"><li id="menu-item-358" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-358"><a href="https://www.avclub.com/about" itemprop="url">About</a></li>
<li id="menu-item-357" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-357"><a href="https://www.avclub.com/advertise" itemprop="url">Advertise</a></li>
<li id="menu-item-364" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-privacy-policy menu-item-364"><a rel="privacy-policy" href="https://www.avclub.com/privacy" itemprop="url">Privacy</a></li>
<li id="menu-item-1854879957" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-1854879957"><a href="https://www.avclub.com/newsletter" itemprop="url">Newsletter</a></li>
<li id="menu-item-355" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-355"><a href="https://www.avclub.com/copyright" itemprop="url">Copyright</a></li>
<li id="menu-item-369" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-369"><a target="_blank" rel="noopener" href="https://www.facebook.com/theavclub" itemprop="url">Facebook</a></li>
<li id="menu-item-370" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-370"><a target="_blank" rel="noopener" href="https://twitter.com/pastemagazine" itemprop="url">Twitter</a></li>
<li id="menu-item-354" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-354"><a href="https://www.avclub.com/customer-service" itemprop="url">Contact Us</a></li>
</ul>
    <p>&copy; 2025 Paste Media Group. All Rights Reserved</p>

    <!-- </div>
                </div>
            </div>
        </div>
    </div> -->
</footer>
<div id="bottom-fixed-unit" class="dfp">
    <div>
        <div class="htlad-bottom_leaderboard" id="bottom_leaderboard"></div>
    </div>
</div>
<script type="speculationrules">
{"prefetch":[{"source":"document","where":{"and":[{"href_matches":"\/*"},{"not":{"href_matches":["\/wp-*.php","\/wp-admin\/*","\/wp-content\/uploads\/*","\/wp-content\/*","\/wp-content\/plugins\/*","\/wp-content\/themes\/pastemagazine\/*","\/*\\?(.+)"]}},{"not":{"selector_matches":"a[rel~=\"nofollow\"]"}},{"not":{"selector_matches":".no-prefetch, .no-prefetch a"}}]},"eagerness":"conservative"}]}
</script>
<script>(function() {function maybePrefixUrlField () {
  const value = this.value.trim()
  if (value !== '' && value.indexOf('http') !== 0) {
    this.value = 'http://' + value
  }
}

const urlFields = document.querySelectorAll('.mc4wp-form input[type="url"]')
for (let j = 0; j < urlFields.length; j++) {
  urlFields[j].addEventListener('blur', maybePrefixUrlField)
}
})();</script><script>
jQuery(document).ready(function($) {
    var deviceAgent = navigator.userAgent.toLowerCase();
    if (deviceAgent.match(/(iphone|ipod|ipad)/)) {
        $("html").addClass("ios");
        $("html").addClass("mobile");
    }
    if (deviceAgent.match(/(Android)/)) {
        $("html").addClass("android");
        $("html").addClass("mobile");
    }
    if (navigator.userAgent.search("MSIE") >= 0) {
        $("html").addClass("ie");
    } else if (navigator.userAgent.search("Chrome") >= 0) {
        $("html").addClass("chrome");
    } else if (navigator.userAgent.search("Firefox") >= 0) {
        $("html").addClass("firefox");
    } else if (navigator.userAgent.search("Safari") >= 0 && navigator.userAgent.search("Chrome") < 0) {
        $("html").addClass("safari");
    } else if (navigator.userAgent.search("Opera") >= 0) {
        $("html").addClass("opera");
    }
});
</script>
<script type="text/javascript">
		/* MonsterInsights Scroll Tracking */
		if ( typeof(jQuery) !== 'undefined' ) {
		jQuery( document ).ready(function(){
		function monsterinsights_scroll_tracking_load() {
		if ( ( typeof(__gaTracker) !== 'undefined' && __gaTracker && __gaTracker.hasOwnProperty( "loaded" ) && __gaTracker.loaded == true ) || ( typeof(__gtagTracker) !== 'undefined' && __gtagTracker ) ) {
		(function(factory) {
		factory(jQuery);
		}(function($) {

		/* Scroll Depth */
		"use strict";
		var defaults = {
		percentage: true
		};

		var $window = $(window),
		cache = [],
		scrollEventBound = false,
		lastPixelDepth = 0;

		/*
		* Plugin
		*/

		$.scrollDepth = function(options) {

		var startTime = +new Date();

		options = $.extend({}, defaults, options);

		/*
		* Functions
		*/

		function sendEvent(action, label, scrollDistance, timing) {
		if ( 'undefined' === typeof MonsterInsightsObject || 'undefined' === typeof MonsterInsightsObject.sendEvent ) {
		return;
		}
			var paramName = action.toLowerCase();
	var fieldsArray = {
	send_to: 'G-B6Y9GVDWSB',
	non_interaction: true
	};
	fieldsArray[paramName] = label;

	if (arguments.length > 3) {
	fieldsArray.scroll_timing = timing
	MonsterInsightsObject.sendEvent('event', 'scroll_depth', fieldsArray);
	} else {
	MonsterInsightsObject.sendEvent('event', 'scroll_depth', fieldsArray);
	}
			}

		function calculateMarks(docHeight) {
		return {
		'25%' : parseInt(docHeight * 0.25, 10),
		'50%' : parseInt(docHeight * 0.50, 10),
		'75%' : parseInt(docHeight * 0.75, 10),
		/* Cushion to trigger 100% event in iOS */
		'100%': docHeight - 5
		};
		}

		function checkMarks(marks, scrollDistance, timing) {
		/* Check each active mark */
		$.each(marks, function(key, val) {
		if ( $.inArray(key, cache) === -1 && scrollDistance >= val ) {
		sendEvent('Percentage', key, scrollDistance, timing);
		cache.push(key);
		}
		});
		}

		function rounded(scrollDistance) {
		/* Returns String */
		return (Math.floor(scrollDistance/250) * 250).toString();
		}

		function init() {
		bindScrollDepth();
		}

		/*
		* Public Methods
		*/

		/* Reset Scroll Depth with the originally initialized options */
		$.scrollDepth.reset = function() {
		cache = [];
		lastPixelDepth = 0;
		$window.off('scroll.scrollDepth');
		bindScrollDepth();
		};

		/* Add DOM elements to be tracked */
		$.scrollDepth.addElements = function(elems) {

		if (typeof elems == "undefined" || !$.isArray(elems)) {
		return;
		}

		$.merge(options.elements, elems);

		/* If scroll event has been unbound from window, rebind */
		if (!scrollEventBound) {
		bindScrollDepth();
		}

		};

		/* Remove DOM elements currently tracked */
		$.scrollDepth.removeElements = function(elems) {

		if (typeof elems == "undefined" || !$.isArray(elems)) {
		return;
		}

		$.each(elems, function(index, elem) {

		var inElementsArray = $.inArray(elem, options.elements);
		var inCacheArray = $.inArray(elem, cache);

		if (inElementsArray != -1) {
		options.elements.splice(inElementsArray, 1);
		}

		if (inCacheArray != -1) {
		cache.splice(inCacheArray, 1);
		}

		});

		};

		/*
		* Throttle function borrowed from:
		* Underscore.js 1.5.2
		* http://underscorejs.org
		* (c) 2009-2013 Jeremy Ashkenas, DocumentCloud and Investigative Reporters & Editors
		* Underscore may be freely distributed under the MIT license.
		*/

		function throttle(func, wait) {
		var context, args, result;
		var timeout = null;
		var previous = 0;
		var later = function() {
		previous = new Date;
		timeout = null;
		result = func.apply(context, args);
		};
		return function() {
		var now = new Date;
		if (!previous) previous = now;
		var remaining = wait - (now - previous);
		context = this;
		args = arguments;
		if (remaining <= 0) {
		clearTimeout(timeout);
		timeout = null;
		previous = now;
		result = func.apply(context, args);
		} else if (!timeout) {
		timeout = setTimeout(later, remaining);
		}
		return result;
		};
		}

		/*
		* Scroll Event
		*/

		function bindScrollDepth() {

		scrollEventBound = true;

		$window.on('scroll.scrollDepth', throttle(function() {
		/*
		* We calculate document and window height on each scroll event to
		* account for dynamic DOM changes.
		*/

		var docHeight = $(document).height(),
		winHeight = window.innerHeight ? window.innerHeight : $window.height(),
		scrollDistance = $window.scrollTop() + winHeight,

		/* Recalculate percentage marks */
		marks = calculateMarks(docHeight),

		/* Timing */
		timing = +new Date - startTime;

		checkMarks(marks, scrollDistance, timing);
		}, 500));

		}

		init();
		};

		/* UMD export */
		return $.scrollDepth;

		}));

		jQuery.scrollDepth();
		} else {
		setTimeout(monsterinsights_scroll_tracking_load, 200);
		}
		}
		monsterinsights_scroll_tracking_load();
		});
		}
		/* End MonsterInsights Scroll Tracking */
		
</script><script type="text/javascript" id="eio-lazy-load-js-before">
/* <![CDATA[ */
var eio_lazy_vars = {"exactdn_domain":"","skip_autoscale":0,"threshold":0,"use_dpr":1};
/* ]]> */
</script>
<script type="text/javascript" defer src="https://www.avclub.com/wp-content/plugins/ewww-image-optimizer/includes/lazysizes.min.js?ver=821" id="eio-lazy-load-js" async="async" data-wp-strategy="async"></script>
<script type="text/javascript" id="disqus_count-js-extra">
/* <![CDATA[ */
var countVars = {"disqusShortname":"avclub"};
/* ]]> */
</script>
<script type="text/javascript" defer src="https://www.avclub.com/wp-content/plugins/disqus-comment-system/public/js/comment_count.js?ver=3.1.3" id="disqus_count-js"></script>
<script type="text/javascript" id="disqus_embed-js-extra">
/* <![CDATA[ */
var embedVars = {"disqusConfig":{"integration":"wordpress 3.1.3 6.8.3"},"disqusIdentifier":"2 https:\/\/www.avclub.com\/wp-content\/backups-dup-pro\/imports\/?page_id=2","disqusShortname":"avclub","disqusTitle":"Home","disqusUrl":"https:\/\/www.avclub.com\/","postId":"2"};
/* ]]> */
</script>
<script type="text/javascript" defer src="https://www.avclub.com/wp-content/plugins/disqus-comment-system/public/js/comment_embed.js?ver=3.1.3" id="disqus_embed-js"></script>

<script>
function loadScript(url, callback) {
    var script = document.createElement("script");
    script.type = "text/javascript";
    if (script.readyState) {
        //IE
        script.onreadystatechange = function() {
            if (script.readyState == "loaded" || script.readyState == "complete") {
                script.onreadystatechange = null;
               //if (callback) {
                    callback();
              // }
            }
        };
    } else {
        //Others
        script.onload = function() {
            if (callback) {
                callback();
             }
        };
    }
    script.src = url;
    document.getElementsByTagName("head")[0].appendChild(script);
}
</script>



<script>
 
setTimeout(
    loadScript,
    5000,
    `https://www.avclub.com/wp-content/plugins/mailchimp-for-wp/assets/js/forms.js?ver=4.8.8`,
    function() {}
);




</script>
</body>
<!--<script type="text/javascript">
  window._taboola = window._taboola || [];
  _taboola.push({flush: true});
</script>
-->
</html>

<!--
Performance optimized by W3 Total Cache. Learn more: https://www.boldgrid.com/w3-total-cache/

Object Caching 0/310 objects using Memcached
Database Caching using Memcached (Request-wide modification query)

Served from: www.avclub.com @ 2025-10-24 01:38:09 by W3 Total Cache
-->