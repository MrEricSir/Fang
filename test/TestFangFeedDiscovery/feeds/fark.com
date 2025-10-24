<!doctype html>
<!-- Report problems to https://www.fark.com/farkback/error -->
<!-- Duke Sucks -->
<html class="no-js" lang="en-US">
<head>
<title>Drew Curtis' FARK.com</title>   <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta name="description" content="Humorous views on interesting, bizarre and amusing articles, submitted by a community of millions of news junkies, with regular Photoshop contests.">
<meta name="keywords" content="Fark, Fark.com, Drew Curtis, News, Community News, Social News, News Flash, Funny News, Weird News, Odd News, Strange News, Satirical News, Humor, Photoshop, Photoshop Contest, Memes, Caturday, Comments, News Commentary, Political News, Celebrity News, Sports News, Geek News">

 <meta property="fb:admins" content="741339004,690298743,503216953">
<meta property="og:type" content="website">  <meta property="og:image" content="https://img.fark.net/images/2013/site/farkLogo2Big.gif">  <link rel="image_src" type="image/gif" href="https://img.fark.net/images/2013/site/farkLogo2Big.gif">  <meta property="og:url" content="https://www.fark.com/">   <link rel="canonical" href="https://www.fark.com/">       <meta name="viewport" content="minimum-scale=0.35, width=device-width">   <meta name="apple-itunes-app" content="app-id=529972412">  <link rel="shortcut icon" href="https://www.fark.com/favicon.ico">
<link rel="apple-touch-icon" href="https://img.fark.net/images/2008/site/fark-webclip.png">

  <meta name="referrer" content="always">      <link rel="stylesheet" href="https://www.fark.com/css/farkstyle_desktop.min_1761247003.css" media="screen">           <script src="https://www.fark.com/js/farktools_desktop.min_1761270536.js"></script>   <script>
function fnGetDomain(url) {
    var domain = url.match(/^(?:ftp|https?):\/\/(?:www\.)?([^\/:]+)[\/:]?.*$/i);
    return (domain) ? domain[1].toLowerCase() : "";
}
var adsense_referrer_channel = fnGetDomain(document.referrer);
</script> <!-- GAM setup -->
    <script async src="//www.googletagservices.com/tag/js/gpt.js"></script>
    <script>

    var googletag = googletag || {};
    googletag.cmd = googletag.cmd || [];
    googletag.cmd.push(function() {
        googletag.pubads().disableInitialLoad();
    });

    googletag.cmd.push(function() {
        fark.globals.leaderboardTopAdSlot = googletag.defineSlot(
            '/1055466/MainPage-Leaderboard',
            [  [728, 90],  [970, 90],  'fluid'
            ],
            'topAd728x90'
        ).addService(googletag.pubads());

        fark.globals.billboardTopAdSlot = googletag.defineSlot(
            '/1055466/MainPage-Billboard',
            [  [300, 250],  [336, 280],  [300, 600],  [160, 600],  'fluid'
            ],
            'rightAd300x250'
        ).addService(googletag.pubads());

        fark.globals.billboardMidAdSlot = googletag.defineSlot(
            '/1055466/MainPage-Billboard-Middle',
            [  [300, 250],  [336, 280],  'fluid'
            ],
            'rightAd300x250Middle'
        ).addService(googletag.pubads());

        fark.globals.billboardStickyAdSlot = googletag.defineSlot(
            '/1055466/MainPage-Billboard-Sticky-fg',
            [  [300, 250],  'fluid'
            ],
            'stickyAd300x250'
        ).addService(googletag.pubads());

        fark.globals.billboardBotAdSlot = googletag.defineSlot(
            '/1055466/MainPage-Billboard-Lower',
            [  [300, 250],  [336, 280],  [300, 600],  [160, 600],  'fluid'
            ],
            'rightAd300x250Lower'
        ).addService(googletag.pubads());

        /*
        fark.globals.leaderboardBotAdSlot = googletag.defineSlot(
            '/1055466/MainPage-Leaderboard-Lower',
            [  [728, 90],  [970, 90],  'fluid'
            ],
            'bottomAd728x90'
        ).addService(googletag.pubads());
        */

         /*
        fark.globals.intellidisplayAdSlot = googletag.defineSlot(
            '/1055466/Intellidisplay',
            [  [300, 250],  [300, 600],  ],
            'intelli-1'
        ).addService(googletag.pubads());
        */  // set up native ad slots
            fark.globals.fullsiteNative1AdSlot = googletag.defineSlot(
                '/1055466/MainPage-Native-Desktop-1-2x2',
                [  [2, 2],  [2, 70],  [775, 50],  'fluid'],
                 'native_ad1').addService(googletag.pubads()).setTargeting("str_pkey", "13fc1914");

            fark.globals.fullsiteNative2AdSlot = googletag.defineSlot(
                '/1055466/MainPage-Native-Desktop-2-2x2',
                [  [2, 2],  [2, 70],  [775, 50],  'fluid'],
                 'native_ad2').addService(googletag.pubads()).setTargeting("str_pkey", "1686c574");   fark.globals.wunderkindAdSlot = googletag.defineOutOfPageSlot('/1055466/Wunderkind_out-of-page', 'wunderkind').addService(googletag.pubads());

              

        // googletag.pubads().enableSingleRequest();

           googletag.pubads().set("page_url", window.location.href);
        googletag.pubads().set("adsense_channel_ids", adsense_referrer_channel);
        googletag.pubads().setSafeFrameConfig({sandbox: true, allowOverlayExpansion: false, allowPushExpansion: false});  googletag.pubads().setTargeting("ut","n");
        googletag.pubads().setTargeting("rf","0");
        googletag.pubads().setTargeting("up_recovery","false");
        googletag.pubads().setTargeting("bidderTimeout", fark.page.bidder_timeout);
        googletag.pubads().setTargeting("rand_key", fark.page.gamRandKey);
        googletag.pubads().setTargeting("platform", "d");

        // Number of seconds to wait after the slot becomes viewable.
        let MINIMUM_REFRESH_DELAY = 10;

        googletag.pubads().addEventListener('slotRenderEnded', function (event) {
            if(event.slot === fark.globals.fullsiteNative1AdSlot || event.slot === fark.globals.fullsiteNative2AdSlot){
                if (!event.isEmpty && event.advertiserId == 54383786) {  // revcontent
                    // javascript code to add 'sponsored' goes here
                    farkDebug.log('NATIVE AD - ADD SPONSORED TAG');
                    // add 'revcontent' class which adds sponsored topic tag
                    document.querySelector('#' + event.slot.getSlotElementId()).classList.add('revcontent');
                } else {
                    document.querySelector('#' + event.slot.getSlotElementId()).classList.remove('revcontent');
                }
            }

            var containerId = event.slot.getSlotElementId();
            var containerEl = document.getElementById(containerId);
            if (containerEl === null) return;

            var iframeEl = containerEl.querySelectorAll('iframe')[0];

            let slot_id = containerId;
            // Record when the slot was rendered for display
            // Every unit will be different with lazyload & refreshing
            if (typeof fark.globals.adUnitsDict[slot_id] == 'object') {
                // console.log('DEBUG: ' + slot_id + ' IS LOADED');
                fark.globals.adUnitsDict[slot_id].lastDisplay = Date.now();
            }

            // it's delayed by 10 milliseconds, because iframe is not yet fully rendered
            // and limited to max to 10 seconds to wait
            setTimeout(
                function () {
                    var thisad;
                    // `src` attribute is null when iframe is FriendlyIframe (non AdX), and
                    // when it's present, then it's SafeFrame (AdX)
                    if (typeof iframeEl !== "undefined" && iframeEl.getAttribute('src') !== null) {
                        thisad  = containerEl.getAttribute('id') + ' is a google adx ad. \n';
                        thisad += 'name: '+iframeEl.getAttribute('name')+'\n';
                        thisad += 'advertiserId: '+event.advertiserId+'\n';
                        thisad += 'campaignId: '+event.campaignId+'\n';
                        thisad += 'creativeId: '+event.creativeId+'\n';
                        thisad += 'sourceAgnosticCreativeId: '+event.sourceAgnosticCreativeId+'\n';
                        thisad += 'sourceAgnosticLineItemId: '+event.sourceAgnosticLineItemId+'\n';
                        thisad += 'slot.getEscapedQemQueryId(): '+event.slot.getEscapedQemQueryId()+'\n';
                        //thisad += 'slot.N._html_: '+event.slot.N._html_+'\n';

                    } else {
                        thisad  = containerEl.getAttribute('id')+' is not a google adx ad \n';
                        thisad += 'advertiserId: '+event.advertiserId+'\n';
                        thisad += 'campaignId: '+event.campaignId+'\n';
                        thisad += 'creativeId: '+event.creativeId+'\n';
                        thisad += 'lineItemId: '+event.lineItemId+'\n';
                        thisad += 'sourceAgnosticCreativeId: '+event.sourceAgnosticCreativeId+'\n';
                        thisad += 'sourceAgnosticLineItemId: '+event.sourceAgnosticLineItemId+'\n';
                    }
                    fark.page.ofnida[containerId] = thisad;
                }, 10);

            processGTEventListener(event);
        });

        // Track when the slot was viewed
        googletag.pubads().addEventListener('impressionViewable', function(event) {
            // Get the Slot from the event
            let slot = event.slot;
            // Get the slot ID
            let slot_id = slot.getSlotElementId();

            // console.log('DEBUG: VIEWED ' + slot_id );
            // don't refresh the wunderkind ad or videoad
            if (slot_id == 'wunderkind' || slot_id == 'videoad') {
                // console.log('DEBUG: NOT RELOADING: ' + slot_id);
                return;
            }

            var responseInfo = event.slot.getResponseInformation();
            if (responseInfo && responseInfo.advertiserId) {
                var advertiserId = responseInfo.advertiserId;

                if (advertiserId == 5415290290) {  // Vuukle's advertiser id
                   console.log('DEBUG: NOT RELOADING Vuukle');
                   return;
                }
            }

            // If we tracked the last load time, calculate how long to wait to refresh
            // The reload time is 30 seconds from last load + a minimum delay
            // Otherwise default to 30 seconds
            let refreshIn = (typeof fark.globals.adUnitsDict[slot_id] == 'object')
                ? Math.max(0, 30 - Math.round((Date.now() - fark.globals.adUnitsDict[slot_id].lastDisplay)/1000)) + MINIMUM_REFRESH_DELAY
                : 30;

            // console.log('DEBUG: ' + slot_id + ' REFRESH IN ' + refreshIn);

            // Create the refresh callback
            let doRefresh = function(slot) {
                // Return the setTimeout handler with current slot in context
                return function() {
                    let slot_id = slot.getSlotElementId();

                    // Add targeting key to indicate in GAM this is a refresh call
                    // Use this to declare the request as a refresh
                    slot.setTargeting('refresh', 'true');

                    // increment the refresh_count and send to GAM as a key-value
                    if (typeof fark.globals.adUnitsDict[slot_id].refresh_count === "undefined") {
                        console.log('DEBUG: no refresh_count was defined for slot_id. Setting to zero');
                        fark.globals.adUnitsDict[slot_id].refresh_count = 0;
                    }

                    fark.globals.adUnitsDict[slot_id].refresh_count++;
                    console.log('DEBUG: REFRESHING ' + slot_id + ' NOW.  Refresh Count is ' + fark.globals.adUnitsDict[slot_id].refresh_count);
                    slot.setTargeting('refresh_count', fark.globals.adUnitsDict[slot_id].refresh_count);

                    // console.log('DEBUG: REFRESHING ' + slot_id + ' NOW');

                    if(slot_id === 'native_ad1' || slot_id === 'native_ad2'){
                        document.querySelector('#' + slot.getSlotElementId()).classList.remove('revcontent');
                    }


                    // execute Auction script
                    executeParallelAuctionAlongsidePrebidForSingleAdUnit(
                        slot_id,
                        fark.globals.adUnitsDict[slot_id].full_dfp_ad_unit_name,
                        fark.globals.adUnitsDict[slot_id].defined_ad_slot,
                        fark.globals.adUnitsDict[slot_id].ad_sizes
                    );
                }
            }

            // Schedule the refresh
            setTimeout(doRefresh(slot), refreshIn*1000 );

        });

        /*
        googletag.pubads().enableLazyLoad({
          // fetchMarginPercent: 200,  // Fetch slots within 2 viewports.
          // renderMarginPercent: 200,  // Render slots within 2 viewports.
          fetchMarginPercent: 100,  // Fetch slots within 1 viewport.
          renderMarginPercent: 100,  // Render slots within 1 viewport.
          mobileScaling: 10.0  // large value to load all ads on mobile at once
        });
        */

        googletag.enableServices();

        // set up dictionary to be used by IntersectionObserver to lazy load auctions
        // we want this global, so don't use 'var' (or 'let')
        fark.globals.adUnitsDict = { topAd728x90: {
                defined_ad_slot: fark.globals.leaderboardTopAdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Leaderboard',
                ad_sizes: [  [728, 90],  [970, 90],  ],
                refresh_count: 0,
            }, rightAd300x250: {
                defined_ad_slot: fark.globals.billboardTopAdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Billboard',
                ad_sizes: [  [300, 250],  [336, 280],  [300, 600],  [160, 600],  ],
                refresh_count: 0,
            }, rightAd300x250Middle: {
                defined_ad_slot: fark.globals.billboardMidAdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Billboard-Middle',
                ad_sizes: [  [300, 250],  [336, 280],  ],
                refresh_count: 0,
            }, stickyAd300x250: {
                defined_ad_slot: fark.globals.billboardStickyAdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Billboard-Sticky-fg',
                ad_sizes: [  [300, 250],  ],
                refresh_count: 0,
            }, rightAd300x250Lower: {
                defined_ad_slot: fark.globals.billboardBotAdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Billboard-Lower',
                ad_sizes: [  [300, 250],  [336, 280],  [300, 600],  [160, 600],  ],
                refresh_count: 0,
            },
            /*
            bottomAd728x90: {
                defined_ad_slot: fark.globals.leaderboardBotAdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Leaderboard-Lower',
                ad_sizes: [  [728, 90],  [970, 90],  ],
                refresh_count: 0,
            },
            */
            native_ad1: {
                defined_ad_slot: fark.globals.fullsiteNative1AdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Native-Desktop-1-2x2',
                ad_sizes: [  [2, 2],  [2, 70],  [775, 50],  ],
                refresh_count: 0,
            }, native_ad2: {
                defined_ad_slot: fark.globals.fullsiteNative2AdSlot,
                full_dfp_ad_unit_name: '/1055466/MainPage-Native-Desktop-2-2x2',
                ad_sizes: [  [2, 2],  [2, 70],  [775, 50],  ],
                refresh_count: 0,
            },


        };

    });
    </script>
    <!-- End GAM Setup -->


    <!-- Amazon AUM setup -->

    <script>
        //load the apstag.js library
        !function(a9,a,p,s,t,A,g){if(a[a9])return;function q(c,r){a[a9]._Q.push([c,r])}a[a9]={init:function(){q("i",arguments)},fetchBids:function(){q("f",arguments)},setDisplayBids:function(){},targetingKeys:function(){return[]},_Q:[]};A=p.createElement(s);A.async=!0;A.src=t;g=p.getElementsByTagName(s)[0];g.parentNode.insertBefore(A,g)}("apstag",window,document,"script","//c.amazon-adsystem.com/aax2/apstag.js");
        //initialize the apstag.js library on the page to allow bidding
        apstag.init({
            pubID: '59bb6420-55c2-4d42-9b17-abd4f27d4710', //enter your pub ID here as shown above, it must within quotes
            adServer: 'googletag',
            signals: {
                ortb2: {
                    // site details
                    site: {
                        name: "Fark",
                        domain: "fark.com",
                        cattax: 7,
                        cat: 'JLBCU7',
                        sectioncat: 'JLBCU7',
                        pagecat: 'JLBCU7',
                        page: document.location.protocol + '//' + document.location.hostname + document.location.pathname,
                        bcat: [163, 164, 165, 25] // firearms, cryptomining, porn, etc
                    }
                }
            }
        });

    </script>
    <!-- End Amazon AUM setup -->


    <!-- Prebid.js setup -->
    <script>
        let src = 'https://www.fark.com/js/prebid';
         //if (fark.page.gamRandKey <= 10) {
        //    src += '9.35.0.js';
        //} else {
            src += '_1744822557.js';
        //}
        let pb = document.createElement('script');
        pb.src = src;
        pb.setAttribute('async', true);
        document.head.appendChild(pb);
        farkDebug.log('adding src', src);

        //var PREBID_TIMEOUT = 1200;
        var PREBID_TIMEOUT = fark.page.bidder_timeout;

        var pbjs = pbjs || {};
        pbjs.que = pbjs.que || [];

        fark.globals.farkPriceBucket = 0;

        pbjs.que.push(function() {

                pbjs.onEvent('bidResponse', function(bidResponse) {
                  console.log("PRICE BUCKET " + bidResponse.adUnitCode, bidResponse);

                  fark.globals.farkPriceBucket = (bidResponse.cpm && fark.globals.farkPriceBucket > bidResponse.cpm)
                                ? fark.globals.farkPriceBucket
                                : bidResponse.cpm;
                  console.log("PRICE BUCKET New best price: " + fark.globals.farkPriceBucket);

                  let priceBucket = Math.round(fark.globals.farkPriceBucket * 10) * 10;
                  googletag.pubads().setTargeting('priceBucket', String(priceBucket) );
                  console.log("PRICE BUCKET New price bucket: " + priceBucket);

                  // Pass FloorBucket
                  let m = 0.00238;
                  let b = 0.185;
                  let floorBucket = (m * priceBucket) + b;
                  floorBucket = Math.floor(floorBucket / 0.05) * 0.05;
                  floorBucket = (floorBucket < 0.15) ? 0.15 : floorBucket;
                  floorBucket = (priceBucket > 300) ? 300 : floorBucket.toFixed(2);
                  googletag.pubads().setTargeting('floorBucket', floorBucket );
                  console.log("PRICE BUCKET New floor bucket: " +  floorBucket );
                });

        });




        var adUnits = [{
            "code": "rightAd300x250",
            "mediaTypes": {
                "banner": {
                    "sizes": [[300, 250], [336, 280], [300, 600], [160, 600]],
                    "pos" : 1  }
            },
            "bids": [  {
                "bidder": "appnexus",
                "params": {
                    "placementId": "9972657",
                }
            }, {
                "bidder": "sharethrough",
                "params": {
                    "pkey": "te3wMRv1ow0w6qvDIa0Yeb7I",
                }
            //}, {
            //   "bidder": "brightcom",
            //   "params": {
            //       "publisherId": '8437',
            //    }
            //}, {
            //    "bidder": "emx_digital",
            //    "params": {
            //        "tagid": '58000',
            //    }
            }, {
                "bidder": "sonobi",
                "params": {
                    "ad_unit": '/1055466/MainPage-Billboard',
                    "dom_id": 'rightAd300x250'
                }
            }, {
                "bidder": "rubicon",
                "params": {
                    "accountId": "9659",
                    "siteId": "17567",
                    "zoneId": "215714",
                    "position": "atf",
                }
            }, {
                "bidder": "shemedia",
                "params": {
                    "accountId": "10278",
                    "siteId": "210096",
                    "zoneId": "3339680",
                    "position": "atf",
                }
            },  {
                "bidder": "sovrn",
                "params": {
                    "tagid": 337561
                }
            }, {
                "bidder": "openx",
                "params": {
                    "delDomain": "fark-d.openx.net",
                    "unit": "537178659",
                }
            }, {
                "bidder": "33across",
                "params": {
                    "siteId": 'aHvmW6t2er6R82aKkv7mNO',
                    "productId": 'siab'
                }
            }, {
                "bidder": 'pubmatic',
                "params": {
                    "publisherId": '161641',
                    "adSlot": '4350347'
                }
            }, {
                "bidder": 'smartadserver',
                "params": {
                    "siteId": '561669',
                    "pageId": '1705788',
                    "formatId": '118120'
                }
            }, {
                "bidder": 'unruly',
                "params": {
                    "siteId": '259331'
                }
            },  {
                "bidder": "datablocks",
                "params": {
                    "source_id": 2727819
                }
            },  {
                "bidder": "minutemedia",
                "params": {
                    "org": "01jpaztd8982",
                    "placementId": "rightAd300x250"
                }
            //}, {
            //    "bidder": "komoona",
            //    "params": {
            //        "hbid": "689e29180e0a4df1b94b4b746bf6874a",
            //        "placementId": "7895d426a704c60f43d29e95c61599d9"
            //    }
            }]
        }, {
            "code": "rightAd300x250Middle",
            "mediaTypes": {
                "banner": {
                    "sizes": [[300, 250], [336, 280], [300, 600], [160, 600]]
                }
            },
            "bids": [  {
                "bidder": "appnexus",
                "params": {
                    "placementId": "15570605",
                }
            }, {
                "bidder": "sharethrough",
                "params": {
                    "pkey": "DdWKurLrMy4fyoOfjGRM8VGt",
                }
            //}, {
            //   "bidder": "brightcom",
            //   "params": {
            //       "publisherId": '8437',
            //   }
            //}, {
            //    "bidder": "emx_digital",
            //    "params": {
            //        "tagid": '61915',
            //    }
            }, {
                  "bidder": "sonobi",
                  "params": {
                      "ad_unit": '/1055466/MainPage-Billboard-Middle',
                      "dom_id": 'rightAd300x250Middle'
                  }
            }, {
                "bidder": "rubicon",
                "params": {
                    "accountId": "9659",
                    "siteId": "17567",
                    "zoneId": "1246006",
                    "position": "btf",
                }
            }, {
                "bidder": "shemedia",
                "params": {
                    "accountId": "10278",
                    "siteId": "210096",
                    "zoneId": "3339680",
                    "position": "btf",
                }
            },  {
                "bidder": "sovrn",
                "params": {
                    "tagid": '605461'
                }
            }, {
                "bidder": "openx",
                "params": {
                    "delDomain": "fark-d.openx.net",
                    "unit": "540686937",
                }
            }, {
                "bidder": "33across",
                "params": {
                    "siteId": 'aXK9aat2er6OoZaKkGJozW',
                    "productId": 'siab'
                }
            }, {
                "bidder": 'pubmatic',
                "params": {
                    "publisherId": '161641',
                    "adSlot": '4350348'
                }
            }, {
                "bidder": 'smartadserver',
                "params": {
                    "siteId": '561669',
                    "pageId": '1705788',
                    "formatId": '118121'
                }
            }, {
                "bidder": 'unruly',
                "params": {
                    "siteId": '259332'
                }
            },  {
                "bidder": "datablocks",
                "params": {
                    "source_id": 2727819
                }
            },  {
                "bidder": "minutemedia",
                "params": {
                    "org": "01jpaztd8982",
                    "placementId": "rightAd300x250Middle"
                }
            //}, {
            //    "bidder": "komoona",
            //    "params": {
            //        "hbid": "689e29180e0a4df1b94b4b746bf6874a",
            //        "placementId": "f15508bbb9b7c36f3b65c54fbcfc018d"
            //    }
            }]
        }, {
            "code": "rightAd300x250Lower",
            "mediaTypes": {
                "banner": {
                    "sizes": [[300, 250], [336, 280], [300, 600], [160, 600]]
                }
            },
            "bids": [  {
                "bidder": "appnexus",
                "params": {
                    "placementId": "9972661",
                }
            }, {
                "bidder": "sharethrough",
                "params": {
                    "pkey": "CM1Eml5MQq08Bpyjwlj7xmVw",
                }
            //}, {
            //   "bidder": "brightcom",
            //   "params": {
            //       "publisherId": '8437',
            //   }
            //}, {
            //    "bidder": "emx_digital",
            //    "params": {
            //        "tagid": '58001',
            //    }
            }, {
                "bidder": "sonobi",
                "params": {
                    "ad_unit": '/1055466/MainPage-Billboard-Lower',
                    "dom_id": 'rightAd300x250Lower'
                }
            }, {
                "bidder": "rubicon",
                "params": {
                    "accountId": "9659",
                    "siteId": "17567",
                    "zoneId": "218414",
                    "position": "btf",
                }
            }, {
                "bidder": "shemedia",
                "params": {
                    "accountId": "10278",
                    "siteId": "210096",
                    "zoneId": "3339680",
                    "position": "btf",
                }
            },  {
                "bidder": "sovrn",
                "params": {
                    "tagid": 337563
                }
            }, {
                "bidder": "openx",
                "params": {
                    "delDomain": "fark-d.openx.net",
                    "unit": "537178650",
                }
            }, {
                "bidder": "33across",
                "params": {
                    "siteId": 'bgf90at2er6Qz2aKkGJozW',
                    "productId": 'siab'
                }
            }, {
                "bidder": 'pubmatic',
                "params": {
                    "publisherId": '161641',
                    "adSlot": '4350349'
                }
            }, {
                "bidder": 'smartadserver',
                "params": {
                    "siteId": '561669',
                    "pageId": '1705788',
                    "formatId": '118122'
                }
            }, {
                "bidder": 'unruly',
                "params": {
                    "siteId": '259333'
                }
            },  {
                "bidder": "datablocks",
                "params": {
                    "source_id": 2727819
                }
            },  {
                "bidder": "minutemedia",
                "params": {
                    "org": "01jpaztd8982",
                    "placementId": "rightAd300x250Lower"
                }
            //}, {
            //    "bidder": "komoona",
            //    "params": {
            //        "hbid": "689e29180e0a4df1b94b4b746bf6874a",
            //        "placementId": "f15508bbb9b7c36f3b65c54fbcfc018d"
            //    }
            }]
        }, {
            "code": "stickyAd300x250",
            "mediaTypes": {
                "banner": {
                    "sizes": [[300, 250]]
                }
            },
            "bids": [  {
                "bidder": "appnexus",
                "params": {
                    "placementId": "18576545",
                }
//                }, {
//                   "bidder": "brightcom",
//                   "params": {
//                       "publisherId": '8437',
//                   }
            //}, {
            //    "bidder": "emx_digital",
            //    "params": {
            //         //        "tagid": '95672',
            //    }
            }, {
                "bidder": "sonobi",
                "params": {
                    "ad_unit": '/1055466/MainPage-Billboard-Sticky-fg',
                    "dom_id": 'stickyAd300x250'
                }
            }, {
                "bidder": "rubicon",
                "params": {
                    "accountId": "9659",
                    "siteId": "17567",
                    "zoneId": "1590322",   "position": "btf",
                }
            }, {
                "bidder": "shemedia",
                "params": {
                    "accountId": "10278",
                    "siteId": "210096",
                    "zoneId": "3421084",
                    "position": "btf",
                }
            },  {
                "bidder": "sovrn",
                "params": {
                    "tagid": 687828
                }
            }, {
                "bidder": "openx",
                "params": {
                    "delDomain": "fark-d.openx.net",
                    "unit": "540976194",
                }
            }, {
                "bidder": 'pubmatic',
                "params": {
                    "publisherId": '161641',
                    "adSlot": '4558715'
                }
            }, {
                "bidder": 'smartadserver',
                "params": {
                    "siteId": '561669',
                    "pageId": '1705788',
                    "formatId": '118123'
                }
            //}, {
            //    "bidder": "cedato",
            //    "params": {
            //        "player_id": "710497154",
            //    }
            }, {
                "bidder": "33across",
                "params": {
                    "siteId": 'b_cqtQt2er6Qb-aKlId8sQ',
                    "productId": 'siab'
                }
            }, {
                "bidder": "sharethrough",
                "params": {
                    "pkey": "veKQhsRVUssEE2ZxXKPs0wQi",
                }
            }, {
                "bidder": 'unruly',
                "params": {
                    "siteId": '259334'
                }
            },  {
                "bidder": "datablocks",
                "params": {
                    "source_id": 2727819
                }
            },  {
                "bidder": "minutemedia",
                "params": {
                    "org": "01jpaztd8982",
                    "placementId": "stickyAd300x250"
                }
            //}, {
            //    "bidder": "komoona",
            //    "params": {
            //        "hbid": "689e29180e0a4df1b94b4b746bf6874a",
            //        "placementId": "f15508bbb9b7c36f3b65c54fbcfc018d"
            //    }
            }]
        }, {
            "code": "topAd728x90",
            "mediaTypes": {
                "banner": {
                    "sizes": [[728, 90], [970, 90]],
                    "pos" : 1
                }
            },
            "bids": [  {
                "bidder": "appnexus",
                "params": {
                    "placementId": "9972641",
                }
            }, {
                "bidder": "sharethrough",
                "params": {
                    "pkey": "YAlbuiCkVF4fMV17MC8YtoZe",
                }
            //}, {
            //   "bidder": "brightcom",
            //   "params": {
            //       "publisherId": '8437',
            //   }
            //}, {
            //    "bidder": "emx_digital",
            //    "params": {
            //       "tagid": '58002',
            //    }
            }, {
                "bidder": "sonobi",
                "params": {
                    "ad_unit": '/1055466/MainPage-Leaderboard',
                    "dom_id": 'topAd728x90'
                }
            }, {
                "bidder": "rubicon",
                "params": {
                    "accountId": "9659",
                    "siteId": "17567",
                    "zoneId": "215714",
                    "position": "atf",
                }
            }, {
                "bidder": "shemedia",
                "params": {
                    "accountId": "10278",
                    "siteId": "210096",
                    "zoneId": "3339680",
                    "position": "atf",
                }
            },  {
                "bidder": "sovrn",
                "params": {
                    "tagid": 337564
                }
            }, {
                "bidder": "openx",
                "params": {
                    "delDomain": "fark-d.openx.net",
                    "unit": "537178632",
                }
            }, {
                "bidder": "33across",
                "params": {
                    "siteId": 'ajhXCgt2er6PueaKlId8sQ',
                    "productId": 'siab'
                }
            }, {
                "bidder": 'pubmatic',
                "params": {
                    "publisherId": '161641',
                    "adSlot": '4350345'
                }
            }, {
                "bidder": 'smartadserver',
                "params": {
                    "siteId": '561669',
                    "pageId": '1705788',
                    "formatId": '118118'
                }
            }, {
                "bidder": 'unruly',
                "params": {
                    "siteId": '259330'
                }
            },  {
                "bidder": "datablocks",
                "params": {
                    "source_id": 2727819
                }
            },  {
                "bidder": "minutemedia",
                "params": {
                    "org": "01jpaztd8982",
                    "placementId": "topAd728x90"
                }
            //}, {
            //    "bidder": "komoona",
            //    "params": {
            //        "hbid": "689e29180e0a4df1b94b4b746bf6874a",
            //        "placementId": "30f7da928a1e074a0b1c923734549d06"
            //    }
            }]
        /*
        }, {
            "code": "bottomAd728x90",
            "mediaTypes": {
                "banner": {
                    "sizes": [[728, 90], [970, 90]]
                }
            },
            "bids": [  {
                "bidder": "appnexus",
                "params": {
                    "placementId": "9972653",
                }
            }, {
                "bidder": "sharethrough",
                "params": {
                    "pkey": "zTFbLFy9BFrtSLlOF2x3u1Xk",
                }
            //}, {
            //   "bidder": "brightcom",
            //   "params": {
            //       "publisherId": '8437',
            //   }
            //}, {
            //   "bidder": "emx_digital",
            //   "params": {
            //       "tagid": '58003',
            //   }
            }, {
                "bidder": "sonobi",
                "params": {
                    "ad_unit": '/1055466/MainPage-Leaderboard-Lower',
                    "dom_id": 'bottomAd728x90'
                }
            }, {
                "bidder": "rubicon",
                "params": {
                    "accountId": "9659",
                    "siteId": "17567",
                    "zoneId": "218414",
                    "position": "btf",
                }
            },  {
                "bidder": "sovrn",
                "params": {
                    "tagid": 337566
                }
            }, {
                "bidder": "openx",
                "params": {
                    "delDomain": "fark-d.openx.net",
                    "unit": "537178630",
                }
            }, {
                "bidder": "33across",
                "params": {
                    "siteId": 'bBGiskt2er6OoZaKkGJozW',
                    "productId": 'siab'
                }
            }, {
                "bidder": 'pubmatic',
                "params": {
                    "publisherId": '161641',
                    "adSlot": '4350346'
                }
            //}, {
            //    "bidder": "komoona",
            //    "params": {
            //        "hbid": "689e29180e0a4df1b94b4b746bf6874a",
            //        "placementId": "25a94ecb6a0d4d1dea2ab5f335438d98"
            //    }
            }]
        */  }, {
            "code": "native_ad1",
            "bids": [{
                "bidder": "sharethrough",
                "params": {
                    "pkey": "13fc1914"
                }
            }, {
                "bidder": "appnexus",
                "params": {
                    "placementId": "28574740"
                }
            }],
            "mediaTypes": {
                "banner": {
                    "sizes": [[2, 70]]
                }
            }   }, {
            "code": "native_ad2",
            "bids": [{
                "bidder": "sharethrough",
                "params": {
                    "pkey": "1686c574"
                }
            }, {
                "bidder": "appnexus",
                "params": {
                    "placementId": "28574741"
                }
            }],
            "mediaTypes": {
                "banner": {
                    "sizes": [[2, 70]]
                }
            }  }];

        pbjs.que.push(function() {
            pbjs.aliasBidder('rubicon', 'shemedia', {gvlid: 337});

            pbjs.addAdUnits(adUnits);

            pbjs.bidderSettings = {
                datablocks: {
                    storageAllowed: true
                }
            };

            pbjs.bidderSettings = {
                // adjust the bid in real time before the auction takes place
                shemedia: {
                    bidCpmAdjustment : function(bidCpm){
                      return bidCpm * .45;
                    },
                },
                 };

            const customConfigObject = {
              "buckets" : [{
                  "precision": 2,  //default is 2 if omitted - means 2.1234 rounded to 2 decimal places = 2.12
                  "max" : 3,
                  "increment" : 0.01  // from $0 to $3, 1-cent increments
                },
                {
                  "max" : 8,
                  "increment" : 0.05  // from $3 to $8, round down to the previous 5-cent increment
                },
                {
                  "max" : 20,
                  "increment" : 0.50   // from $8 to $20, round down to the previous 50-cent increment
                },
                {
                  "max" : 42,
                  "increment" : 1.00   // from $20 to $42, round down to the previous 1-dollar increment
                },
                {
                  "max" : 50,
                  "increment" : 2.00   // from $42 to $50, round down to the previous 2-dollar increment
                }]
            };


            // Prepare keys to send to ID5
            let pdKeys = {
                8: encodeURIComponent(document.location.href),
                9: encodeURIComponent(document.location.hostname),
                12: encodeURIComponent(window.navigator.userAgent)
            };  // convert the key/values into a querystring format
            let pdRaw = Object.keys(pdKeys).map(key => key + '=' + pdKeys[key]).join('&');

            // base64 encode the raw string; this is the final value
            let id5_pdstring = btoa(pdRaw);
            farkDebug.log('MEG DEBUG: id5_pdstring is:' + id5_pdstring);

            pbjs.setConfig({
                 
                enableSendAllBids: true,
                bidderSequence: "random",
                priceGranularity: customConfigObject,
                publisherDomain: "fark.com",
                bidderTimeout: PREBID_TIMEOUT,
                useBidCache: true,
                consentManagement: {
                    usp: {
                        cmpApi: 'iab'
                        // timeout: 3000 // US Privacy timeout - use the default (10_000)
                   }
                },
                userSync: {
                    filterSettings: {
                        all: {
                            bidders: '*',
                            filter: 'include'
                        }
                    },
                    userIds: [
                        {
                            name: "id5Id",
                            params: {
                                partner: 1354,
                                externalModuleUrl: 'https://cdn.id5-sync.com/api/1.0/id5PrebidModule.js',
                                pd: id5_pdstring
                            },
                            storage: {
                                type: "html5",
                                name: "id5id",
                                expires: 90,
                                refreshInSeconds: 7200   // refresh ID every 2 hours to ensure it's fresh
                            }
                        }  ]
                },
                ortb2: {
                    site: {
                        cat: ['IAB12'],
                        sectioncat: ['IAB12'],
                        pagecat: ['IAB12'],
                        content: {
                            data: [{
                                ext: { segtax: 7 },
                                segment: [
                                    {
                                        "id": 'JLBCU7'
                                    },  ]
                            }]
                        },
                        bcat: [163, 164, 165] // firearms, cryptomining, porn, etc
                    }
                }
            });
        });
    </script>

    <!-- End Prebid.js setup -->  <script>

    var observer = new IntersectionObserver(handleIntersection, { rootMargin: fark.page.io_vp + '%' });

    function handleIntersection(entries) {
        entries.map((entry) => {
            // let divId = entry.target.id;
            // let content = divId+' - ';
            // content += (entry.isIntersecting) ? 'Is Shown' : 'Not Shown';
            // let currentDate = new Date();
            // let time = currentDate.getHours() + ':' + currentDate.getMinutes() + ':' + currentDate.getSeconds();
            // farkDebug.log('MEG DEBUG: '+time+' - '+content);

            if (entry.isIntersecting) {
                let divId = entry.target.id;
                farkDebug.log('fetching ad for '+divId);

                // This is the first time we load the ad, so refresh is false and refresh_count is 0
                let slot = fark.globals.adUnitsDict[divId].defined_ad_slot;
                slot.setTargeting('refresh', 'false');
                slot.setTargeting('refresh_count', '0');

                executeParallelAuctionAlongsidePrebidForSingleAdUnit(divId, fark.globals.adUnitsDict[divId].full_dfp_ad_unit_name, fark.globals.adUnitsDict[divId].defined_ad_slot, fark.globals.adUnitsDict[divId].ad_sizes);
                observer.unobserve(entry.target);
            }
        });

    }


    // fark.page.headerbidTargeting = "";
    fark.page.rcPageName = "homepage";
    fark.page.isMobile = false;
    fark.page.isDesktop = true;

    $.ajaxSetup({ timeout: 15000 });
    fark.ajax.ajaxSpinner = new Image();
    fark.ajax.ajaxSpinner.src = 'https://img.fark.net/images/2011/site/ajax-loader.gif';
    fark.ajax.ajaxSpinnerRaw = '<\img alt="..." src="https://img.fark.net/images/2011/site/ajax-loader.gif" width="16" height="16">';
</script>

   <!-- InMobi Choice. Consent Manager Tag v3.0 (for TCF 2.2) -->
<script async>
(function() {
  var host = 'fark.com';
  var element = document.createElement('script');
  var firstScript = document.getElementsByTagName('script')[0];
  var url = 'https://cmp.inmobi.com'
    .concat('/choice/', '90W110YesRJyT', '/', host, '/choice.js?tag_version=V3');
  var uspTries = 0;
  var uspTriesLimit = 3;
  element.async = true;
  element.type = 'text/javascript';
  element.src = url;

  firstScript.parentNode.insertBefore(element, firstScript);

  function makeStub() {
    var TCF_LOCATOR_NAME = '__tcfapiLocator';
    var queue = [];
    var win = window;
    var cmpFrame;

    function addFrame() {
      var doc = win.document;
      var otherCMP = !!(win.frames[TCF_LOCATOR_NAME]);

      if (!otherCMP) {
        if (doc.body) {
          var iframe = doc.createElement('iframe');

          iframe.style.cssText = 'display:none';
          iframe.name = TCF_LOCATOR_NAME;
          doc.body.appendChild(iframe);
        } else {
          setTimeout(addFrame, 5);
        }
      }
      return !otherCMP;
    }

    function tcfAPIHandler() {
      var gdprApplies;
      var args = arguments;

      if (!args.length) {
        return queue;
      } else if (args[0] === 'setGdprApplies') {
        if (
          args.length > 3 &&
          args[2] === 2 &&
          typeof args[3] === 'boolean'
        ) {
          gdprApplies = args[3];
          if (typeof args[2] === 'function') {
            args[2]('set', true);
          }
        }
      } else if (args[0] === 'ping') {
        var retr = {
          gdprApplies: gdprApplies,
          cmpLoaded: false,
          cmpStatus: 'stub'
        };

        if (typeof args[2] === 'function') {
          args[2](retr);
        }
      } else {
        if(args[0] === 'init' && typeof args[3] === 'object') {
          args[3] = Object.assign(args[3], { tag_version: 'V3' });
        }
        queue.push(args);
      }
    }

    function postMessageEventHandler(event) {
      var msgIsString = typeof event.data === 'string';
      var json = {};

      try {
        if (msgIsString) {
          json = JSON.parse(event.data);
        } else {
          json = event.data;
        }
      } catch (ignore) {}

      var payload = json.__tcfapiCall;

      if (payload) {
        window.__tcfapi(
          payload.command,
          payload.version,
          function(retValue, success) {
            var returnMsg = {
              __tcfapiReturn: {
                returnValue: retValue,
                success: success,
                callId: payload.callId
              }
            };
            if (msgIsString) {
              returnMsg = JSON.stringify(returnMsg);
            }
            if (event && event.source && event.source.postMessage) {
              event.source.postMessage(returnMsg, '*');
            }
          },
          payload.parameter
        );
      }
    }

    while (win) {
      try {
        if (win.frames[TCF_LOCATOR_NAME]) {
          cmpFrame = win;
          break;
        }
      } catch (ignore) {}

      if (win === window.top) {
        break;
      }
      win = win.parent;
    }
    if (!cmpFrame) {
      addFrame();
      win.__tcfapi = tcfAPIHandler;
      win.addEventListener('message', postMessageEventHandler, false);
    }
  };

  makeStub();

  var uspStubFunction = function() {
    var arg = arguments;
    if (typeof window.__uspapi !== uspStubFunction) {
      setTimeout(function() {
        if (typeof window.__uspapi !== 'undefined') {
          window.__uspapi.apply(window.__uspapi, arg);
        }
      }, 500);
    }
  };

  var checkIfUspIsReady = function() {
    uspTries++;
    if (window.__uspapi === uspStubFunction && uspTries < uspTriesLimit) {
      console.warn('USP is not accessible');
    } else {
      clearInterval(uspInterval);
    }
  };

  if (typeof window.__uspapi === 'undefined') {
    window.__uspapi = uspStubFunction;
    var uspInterval = setInterval(checkIfUspIsReady, 6000);
  }
})();
</script>
<!-- End InMobi Choice. Consent Manager Tag v3.0 (for TCF 2.2) -->  <!-- CONFIANT CODE -->

  <script async src="https://cdn.confiant-integrations.net/cEfft1aujoR3mcJAi8Jzh_8If_c/gpt_and_prebid/config.js"></script>  <!-- END CONFIANT CODE --> <!-- CARBON STUB -->
    <script>
    !function(e,a){e.cca=e.cca||{tapPrebidQue:[],tapGAMQue:[]};var n=e.cca;e.pbjs=e.pbjs||{que:[]};var t=e.pbjs;t.que.push(function(){t.onEvent("bidWon",function(e){n.tapReady||n.tapPrebidQue.push(JSON.stringify(e))})}),e.googletag=e.googletag||{cmd:[]};var u=e.googletag;u.cmd.push(function(){u.pubads().addEventListener("slotRenderEnded",function(e){n.tapReady||n.tapGAMQue.push(e)})})}(window);
    </script>
    <!-- END CARBON STUB -->  <script>  // dimension2
var pixelRatio = (window.devicePixelRatio >= 1.5) ? "high" : "normal";

// dimension4
var hlview_mode = fark.helpers.getCookie('hlview') ? fark.helpers.getCookie('hlview') : 'd';

// dimension5  </script>


<!-- Global site tag (gtag.js) - Google Analytics for GA4 -->
 <script async src="https://www.googletagmanager.com/gtag/js?id=UA-225200-2"></script>



<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());

  // add data collection for GA4
  gtag('config', 'G-2CGLGL25G6', {
    'ads_on_page': 'g',
    'user_type': 'Lurker',
    'pixel_ratio': pixelRatio,
    'platform': 'd',
    'gam_rand_key': fark.page.gamRandKey,  });

</script>
<!-- End Google Analytics 4 -->   <script type="text/javascript">!(function(o,_name){o[_name]=o[_name]||function $(){($.q=$.q||[]).push(arguments)},o[_name].v=o[_name].v||2;!(function(o,n,t,e,f,c){function i(e,f){(e=(function(n,t){try{if(t=(n=o.localStorage).getItem("_aQS02Njg1OEVDM0E5N0Q1OTM1NkJCRDgyREQtMQ"))return JSON.parse(t).lgk||[];if((n.getItem('%76%34ac%31%65iZ%72%30')||"").split(",")[4]>0)return[[_name+"-engaged","true"]]}catch(e){}})())&&typeof e.forEach===t&&(f=o[n].pubads())&&e.forEach((function(o){o&&o[0]&&f.setTargeting(o[0],o[1]||"")}))}(c=o[n]=o[n]||{}).cmd=c.cmd||[],typeof c.pubads===t?i():typeof c.cmd.unshift===t?c.cmd.unshift(i):c.cmd.push(i)})(window,"googletag","function");;})(window,decodeURI('ad%6d%69%72al'));!(function(t,c,i){i=t.createElement(c),t=t.getElementsByTagName(c)[0],i.async=1,i.src="https://tackytrains.com/chunks/39e8d6a/6baa32ea942a3dfd2d659ea0685a1.min.js",t.parentNode.insertBefore(i,t)})(document,"script");</script>    <script>
        abimg(1);
        //  ga('send', 'event', 'Ads', 'Display', 'A', 1, {'nonInteraction': 1});

        var dfp_ad_source = ''; 
            dfp_ad_source = 'Fark DFP';
            // ga('send', 'event', 'dfpsource', 'Display', 'Fark', 1, {'nonInteraction': 1});     abimg(2);
            // ga('send', 'event', 'Ads', 'Display', 'B', 1, {'nonInteraction': 1});

            //abimg(3);  //  ga('send', 'event', 'Ads', 'Display', 'C', 1, {'nonInteraction': 1});

             
             var house_ad_billboard = "<iframe src=\"https://www.fark.com/aptminus/size3/1?abp=1\" width=\"300\" height=\"250\" style=\"overflow:hidden;\" marginwidth=\"0\" marginheight=\"0\" frameborder=\"0\" scrolling=\"no\"></iframe>";

             
             var house_ad_leaderboard = "<iframe src=\"https://www.fark.com/aptminus/size1/1?abp=1\" width=\"728\" height=\"90\" style=\"overflow:hidden;\" marginwidth=\"0\" marginheight=\"0\" frameborder=\"0\" scrolling=\"no\"></iframe>";

            $(document).ready(function() {
                 if (!$('#header_ad').is(':visible')) {
                    // showPlea();
                }

                var tfarkToShow = '';
                setTimeout(function() {
                    if(abTest()) {
                        abimg(4);
                        // ga('send', 'event', 'Ads', 'Display', 'D', 1, {'nonInteraction': 1});
                    };
                }, 8000);
            });  </script>    <script async src="https://fundingchoicesmessages.google.com/i/pub-8861438340519172?ers=1" nonce="7wPWdbU4_WBUJFuGMSTZCA"></script><script nonce="7wPWdbU4_WBUJFuGMSTZCA">(function() {function signalGooglefcPresent() {if (!window.frames['googlefcPresent']) {if (document.body) {const iframe = document.createElement('iframe'); iframe.style = 'width: 0; height: 0; border: none; z-index: -1000; left: -1000px; top: -1000px;'; iframe.style.display = 'none'; iframe.name = 'googlefcPresent'; document.body.appendChild(iframe);} else {setTimeout(signalGooglefcPresent, 0);}}}signalGooglefcPresent();})();</script>  <meta name="robots" content="max-image-preview:large"><link rel="alternate" href="https://www.fark.com/fark.rss" type="application/rss+xml" title="FARK.com Fark RSS Feed">       <style> .headlineRow:hover, .headlineRow:hover:nth-child(odd) { background-color: #eeeeff; } </style> <script src="https://www.youtube.com/iframe_api"></script>

    <!-- CARBON RULES -->
<script>
window.cca = window.cca || {};
window.cca.adiq = window.cca.adiq || {};
window.cca.adiq.que = window.cca.adiq.que || [];
window.cca.adiq.que.push(function(){
    //syntactic sugar
    var Check = window.cca.adiq.Check;
    var addAttribute = window.cca.adiq.addAttribute;
    var activateRule= window.cca.adiq.activateRule;
    var pageload = window.cca.adiq.makeRule;
    var revenueevent = window.cca.adiq.makeRevenueRule;
    var timesinceload = window.cca.adiq.makeTimedRule;

    var adiqfunc1 = function(){
        if(document.querySelector('intelli-1')){
            console.log('intelli-1 already exists - do nothing');
            // ad already exists; do nothing
        } else {
            console.log('loading intelli-1 ad');
            googletag.cmd.push(function(){
                // set up intellidisplay slot
                var node = document.querySelector('.rightColContent #intelli-1');
                // node.style.marginTop="10px";
                var parent = node.parentElement;
                parent.style.display="block";

                window.fark.globals.intellidisplayAdSlot = googletag.defineSlot(
                    '/1055466/Intellidisplay',
                    [  [300, 250],  [300, 600],  ],
                    'intelli-1'
                ).addService(googletag.pubads());
                // Register the div
                googletag.display('intelli-1');
            });

            googletag.cmd.push(function(){
                pbjs.que.push( function() {
                    pbjs.addAdUnits({
                        "code": "intelli-1",
                        "mediaTypes": {
                            "banner": {
                                "sizes": [[300, 250], [300, 600]],
                                "pos" : 1
                            }
                        },
                        "bids": [  {
                            "bidder": "appnexus",
                            "params": {
                                "placementId": "18576580",
                            }
                        }, {
                            "bidder": "sharethrough",
                            "params": {
                                "pkey": "8yQoP3RZDpiCV8IItjnALpUl",
                            }
            //                }, {
            //                   "bidder": "brightcom",
            //                   "params": {
            //                       "publisherId": '8437',
            //                   }
            //            }, {
            //               "bidder": "emx_digital",
            //               "params": {
            //                   "tagid": '95671',
            //               }
                        }, {
                            "bidder": "sonobi",
                            "params": {
                                "ad_unit": '/1055466/Intellidisplay',
                                "dom_id": 'intelli-1'
                            }
                        }, {
                            "bidder": "rubicon",
                            "params": {
                                "accountId": "9659",
                                "siteId": "17567",
                                "zoneId": "1590324",
                                "position": "atf",
                            }
                        }, {
                            "bidder": "shemedia",
                            "params": {
                                "accountId": "10278",
                                "siteId": "210096",
                                "zoneId": "3421078",
                                "position": "atf",
                            }
                        },  {
                            "bidder": "sovrn",
                            "params": {
                                "tagid": 687826
                            }
                        }, {
                            "bidder": "openx",
                            "params": {
                                "delDomain": "fark-d.openx.net",
                                 "unit": "540976197",
                            }
                        }, {
                            "bidder": "33across",
                            "params": {
                                "siteId": 'bQ5HVyt2er6OoWaKkGJozW',
                                "productId": 'siab'
                            }
                        }, {
                            "bidder": 'pubmatic',
                            "params": {
                                "publisherId": '161641',
                                "adSlot": '4350350'
                            }
                        }, {
                            "bidder": 'smartadserver',
                            "params": {
                                "siteId": '561669',
                                "pageId": '1705788',
                                "formatId": '118119'
                            }
                        }, {
                            "bidder": 'unruly',
                            "params": {
                                "siteId": '259335'
                            }
                        },  {
                            "bidder": "datablocks",
                            "params": {
                                "source_id": 2727819
                            }
                        }]
                    });
                    pbjs.requestBids( {
                        timeout: PREBID_TIMEOUT,
                        adUnitCodes: ['intelli-1'],
                        bidsBackHandler: function() {
                            pbjs.setTargetingForGPTAsync( [ window.fark.globals.intellidisplayAdSlot.getSlotElementId() ] );
                            //fark.page.headerbidTargeting = pbjs.getAdserverTargeting();
                            googletag.pubads().refresh([window.fark.globals.intellidisplayAdSlot]);
                        }
                    } );
                } );
            } );
        }

        function showIntellidisplayReportAdLink() {
            var reportAdBlock = document.querySelector('#intelli-1-reportLink');
            reportAdBlock.style.display="block";  }

        if (document.readyState === 'loading') {
            document.addEventListener('DOMContentLoaded', (event) => {
                showIntellidisplayReportAdLink();
            });
        } else {
            showIntellidisplayReportAdLink();
        }

    }//end function 1

    var adiqfunc2 = function(){
        function hideIntellidisplayAndShowFns() {
            var node = document.querySelector('#intelli-1');
            var parent = node.parentElement;
            parent.style.display="none";
            //node.style.display="none";
/*
            var kids = parent.children;
             for (i=0;i<3;i++){
                parent.removeChild(kids[0])
            }
*/  }

        if (document.readyState === 'loading') {
            document.addEventListener('DOMContentLoaded', (event) => {
                hideIntellidisplayAndShowFns();
            });
        } else {
            hideIntellidisplayAndShowFns();
        }
    }//end function 2

    console.log('intelli-1 setting up rules');
    //Rule 1 - First Page
    cca.adiq.addEventListener("rule1", adiqfunc1);
    var rule1 = pageload("rule1", 100,false);
    addAttribute(rule1, new Check("getPageViews","=",1));
    activateRule(rule1);

    //Rule 2 - Later Page High Revenue
    cca.adiq.addEventListener("rule2", adiqfunc1);
    var rule2 = revenueevent("rule2", 100,false);
    addAttribute(rule2, new Check("getPageViews",">",1));
    addAttribute(rule2, new Check("getNumberRevenueEvents",">",4));
    addAttribute(rule2, new Check("getAvgPageRevenue",">",2.95));
    activateRule(rule2);

    //Rule 3 - Hide The Unit
    cca.adiq.addEventListener("rule3", adiqfunc2);
    var rule3 = pageload("rule3", 100,false);
    addAttribute(rule3, new Check("getPageViews",">",1));
    activateRule(rule3);
});
</script>  <!-- END CARBON RULES -->


</head>  <body >        <a href="#newsContainer" class="skipToContent" tabindex="1">Skip to content</a>  <script>  fark.ajax.globalToken = 'FcLk_--V08KPQUq_5wLZodB2raOvpni5cxRLJZfjega40Or4CYlLO7TpNZbH88uzwIrcctalu1DbJt1tx76pJktmLyd5fzUiS_';
</script>
<!-- BEGIN left 2025-10-24 02:50:05--> <div class="fullwidthheaderbackground"></div>

  <div id="header_ad">Do you have adblock enabled?</div>  <div class="fullwidthheaderbackground">&nbsp;</div>
<div id="container">
<table id="newLayoutTable">
<tr>
<td colspan="2">

<div id="header">  <div class="tryBareFark">
        <a href="https://www.fark.com/barefarksignup" target="_blank">Try Ads-Free Fark</a>
    </div>   <a id="logo" class="retina header_logo" href="https://www.fark.com"><img src="https://img.fark.net/images/2013/site/farkLogoBig.png" srcset="https://img.fark.net/images/2013/site/farkLogoBig.png 1x, https://img.fark.net/images/2013/site/farkLogoBig-2x.png 2x" alt="Fark" height="85"></a>   <div class="ad_container top">  <div id="topAd728x90"><!-- begin ad tag (leaderboard_top) -->
            <script>  googletag.cmd.push(function() { googletag.display('topAd728x90'); });  </script></div>   <div class="reportAdBlock"  id="topAd728x90-reportLink"><a href="https://www.fark.com/farkback/" onclick="reportAd('topAd728x90'); return false;">Report</a></div>   </div> <div id="headerBottom">  <div id="tagLine">It's Not News, It's Fark </div> <form method="post" name="signinbox" enctype="application/x-www-form-urlencoded" action="https://www.fark.com/login"> <input type="hidden" name="e0$Fc5k_$C8ChLnN3YsnFEuYtkevIOWwvOIpz" value="Fcqk_-PSFDLjECLjrgvlK6MLNLzQPCvMDWSYdqPxMvtRhtDBBK1Jr2FFTLLDueNRzQ9_k3am9pQ9iRJM2IFKmCz_qKvRLj41Ps_">
    <input type="hidden" name="continue" value="Fcck_-QSR953MtvNpUqjAbdAtbfA6TSoihhe4LjI5ROYXY7__N-qvRHrhX">   <div id="messageCenter">


         <div id="loginContainer">
        <div id="loginContent" class="js">
            <div id="loginLinks">  <a href="javascript:run_walkthrough('Link')" id="how_to_fark_link">How To Fark</a>  <a href="#" id="loginLink" onclick="document.getElementById('loginLinks').classList.add('slidup'); setTimeout(function() { document.getElementById('loginName').focus(); }, 250); return false;">Log In</a> &nbsp;|&nbsp; <a href="https://www.fark.com/signup?e0$FcFk_$$2423SVD3YEorlZ2ZMuyP6FqiwDfad1DsG18=Fc5k_-CEbdOUPacxdMgJGNBRI9KfsNH40LpajdYYyXlzHnh0">Sign Up &raquo;</a>
            </div>
            <div id="loginBoxes">
                <div class="loginSection">
                    <label for="loginName">Login</label>
                    <input type="text" name="ulogin" id="loginName" autocomplete="username" autocorrect="off" autocapitalize="off" spellcheck="false">
                </div>
                <div class="loginSection">
                    <label for="loginPass">Password</label>
                    <input type="password" name="passwd" id="loginPass" autocomplete="current-password" autocorrect="off" autocapitalize="off" spellcheck="false">
                </div>
                <div class="loginSection submitLogin">
                    <input type="submit" class="searchSubmButton" value="Go">
                </div>
                <div class="loginForgotPass">
                    <a href="https://www.fark.com/forgotpassword">Forgot password?</a>
                </div>
                <div class="loginCancel">
                    <a href="#" id="cancelLogin" onclick="document.getElementById('loginLinks').classList.remove('slidup'); return false;">X</a>
                </div>
            </div>
        </div>

    </div>  </div> </form>
 </div>
</div>  </td>
</tr>
<tr>
<td colspan="2">

 <div id="headerMenuContainer"> <!-- Top navigation menu -->
    <ul id="headerMenu">
    <li class="menuSelected"><a href="https://www.fark.com/">FARK</a></li>
    <li><a href="https://total.fark.com/commented">TotalFark</a></li>
    <li><a href="https://www.fark.com/users"><em>my</em>Fark</a></li>
    <li><a href="https://www.fark.com/farq/">About/FArQ</a></li>  <li><a href="https://www.fark.com/contests/">Contests</a></li>  <li><a href="https://www.fark.com/shop">Store</a></li>
    <li><a href="https://www.fark.com/farkback" title="Farkback">Contact Us</a></li>
    <li><a href="https://m.fark.com">Mobile</a></li>
    </ul>

    <div id="searchBar" style="display: flex; gap: 8px">
        <a href="https://www.fark.com/subscribe" class="farkButton sButton">SUBSCRIBE</a>

        <!-- Dropdown Trigger for Search -->
        <div class="dropdown searchDD" style="display: inline-block; position: relative;">
        <div class="searchContainer" style="display: flex;">
            <button class="farkButton searchButton" id="searchDropdownButton" title="Fark Search">
                <img src="https://img.fark.net/images/2014/site/magnify.png" alt="Search Fark" style="height: 1em; vertical-align: middle;">
            </button>

            <form method="get" action="https://www.fark.com/hlsearch" name="topSearchFrm" target="_top" class="killspacehack">
                <div style="display: flex; justify-content: center; align-items: center;">
                    <input type="text" placeholder="Search Fark" name="qq" id="searchInput" maxlength="255" style="flex-grow: 1; padding: 5px; margin-top: 0;border-width: 1px;" onclick="event.stopPropagation();">
                    <input type="submit" class="searchSubmButton" value="Go" style="margin-left: 8px;" onclick="event.stopPropagation();">
                </div>
            </form>
        </div></div>

<!--
        <div id="searchDropdown" class="dropdown-content" style="display: none; padding-right: 14px; padding-left: 14px; margin-top: 6px;">
            <form method="get" action="https://www.fark.com/hlsearch" name="topSearchFrm" target="_top" class="killspacehack">
                <div style="display: flex; justify-content: center; align-items: center;">
                    <input type="text" placeholder="Search Fark" name="qq" id="searchInput" maxlength="255" style="flex-grow: 1;" onclick="event.stopPropagation();">
                    <input type="submit" class="searchSubmButton" value="Go" style="margin-left: 8px;" onclick="event.stopPropagation();">
                </div>
            </form>
        </div>
-->
        <!-- Existing Dropdown for Menu -->
        <div class="dropdown" style="display: inline-block; position: relative;">
            <button class="farkButton" id="dropdownMenuButton">&#9776;</button>
            <div id="myDropdown" class="dropdown-content" style="display: none; margin-top: 6px;">
              <a target="_blank" href="https://youtu.be/o6QDjDPRF5c?si=UjI4RcphEdHKxBYY" style="display: block; color: black;">Bobcaygeon</a>  </div>
        </div>
        <script>
            document.addEventListener('DOMContentLoaded', function() {
                var dropdownButton = document.getElementById('dropdownMenuButton');
                var searchDropdownButton = document.getElementById('searchDropdownButton');
                var dropdownContent = document.getElementById('myDropdown');
                var searchDropdownContent = document.getElementById('searchDropdown');

                function closeAllDropdowns(exceptId) {
                    var dropdowns = document.getElementsByClassName("dropdown-content");
                    for (var i = 0; i < dropdowns.length; i++) {
                        if (dropdowns[i].id !== exceptId) {
                            dropdowns[i].style.display = 'none';
                        }
                    }
                }

                dropdownButton.addEventListener('click', function() {
                    closeAllDropdowns('myDropdown');
                    dropdownContent.style.display = dropdownContent.style.display === 'block' ? 'none' : 'block';
                });

                searchDropdownButton.addEventListener('click', function() {
                document.querySelector('.searchDD').classList.toggle('searchOpen')

                });

                window.addEventListener('click', function(event) {
                    if (!event.target.matches('#dropdownMenuButton') && !event.target.matches('#searchDropdownButton') && !event.target.matches('img')) {
                        closeAllDropdowns('');
                    }
                });
            });
        </script>
    </div>

</div> <!-- headerMenuContainer -->  <!-- headerMenuContainer NOSCRIPT -->  <noscript>
 <div id="headerMenuContainerNoScript"> <!-- Top navigation menu -->
    <div id="loginBoxesNoScript">
        <form method="post" enctype="application/x-www-form-urlencoded" action="https://www.fark.com/login"> <input type="hidden" name="e0$Fc5k_$C8ChLnN3YsnFEuYtkevIOWwvOIpz" value="Fctk_-AAqF9rvBFrq-x4k8kj6R1BL201vq6DfsC0NDWdyE3poszR3Ce0rNtSBn6yJ-zfPJAg__EJAlOv1R_Mx1q4Q6DvY5OMSiA">
  <div class="loginSectionNoScript submitLogin">
                <input type="submit" class="searchSubmButtonNoScript" value="Go">
            </div>
            <div class="loginSectionNoScript">
                <label for="loginPass_ns">Password</label>
                <input type="password" name="passwd" id="loginPass_ns" autocomplete="current-password" autocorrect="off" autocapitalize="off" spellcheck="false">
            </div>
            <div class="loginSectionNoScript">
                <label for="loginName_ns">Login</label>
                <input type="text" name="ulogin" id="loginName_ns" autocomplete="username" autocorrect="off" autocapitalize="off" spellcheck="false">
            </div>
            <div class="loginSectionNoScript" style="vertical-align:middle; padding-right:15px; padding-top:10px;"> Turn on javascript (or enable it for Fark) for a better user experience.</div>
        </form>
    </div>
</div>
</noscript> <!-- /headerMenuContainer NOSCRIPT -->         <div class="invis"><strong><small>If you can read this, either the style sheet didn't load or you have an older browser that doesn't support
style sheets. Try clearing your browser cache and refreshing the page.</small></strong></div>

</td>
</tr>
 <tr><td id="leftColSpacer"><!-- --></td><td id="rightColSpacer"><!-- --></td></tr>
<tr>
<td id="leftCol">

 <ul id="catMenu">

     
        <li class="catSelected"><a href="https://www.fark.com/"> Main</a></li>
        <li><a href="https://www.fark.com/discussion/"> Discussion</a></li>
        <li><a href="https://www.fark.com/sports/"> Sports</a></li>
        <li><a href="https://www.fark.com/business/"> Business</a></li>
        <li><a href="https://www.fark.com/stem/"> STEM</a></li>
        <li><a href="https://www.fark.com/entertainment/"> Entertainment</a></li>
        <li><a href="https://www.fark.com/fandom/"> Fandom</a></li>
        <li><a href="https://www.fark.com/dawww/"> D'awww</a></li>
        <li><a href="https://www.fark.com/food/"> Food</a></li>
        <li><a href="https://www.fark.com/politics/"> Politics</a></li>        </ul> <div id="newsContainer">
<!-- TOP end -->
<!-- Temporary announcements go here -->
<!-- $Id: motd 46616 2024-12-19 04:58:31Z mmangler $ -->

<script>
    var number_newer_headlines = 0;
    fark.page.ajaxTab = 'main';
    fark.page.ajaxTabGroup = 'Fark';
    fark.ajax.headlineAjaxPerCall = 25;
    fark.page.title = document.title;
    fark.page.type = "headline";

    // noheadlinecount = don't show the number of headlines to load
    fark.ajax.noHeadlineCount = false;
    fark.ajax.ajaxCheckEnabled = true;  $(document).ready(function() {
          fark.ajax.headlinesPerCall = fark.ajax.normalHeadlinesPerCall;  fark.ajax.headlinesCheckInterval = fark.ajax.desktopHeadlinesCheckInterval;
        check_for_new_headlines(); /* run automatically to update link } */
        headline_check_new_headlines_timer = setInterval( function() { check_for_new_headlines(); }, fark.ajax.headlinesCheckInterval );
    });  fark.headlines.newestEpochDate = '1761285660';
fark.headlines.firstNewEpochDate = '1761285660';
fark.headlines.firstHeadlineDate = 'Fri October 24, 2025';
fark.headlines.oldestEpochDate = '1761192060';
fark.headlines.lastHeadlineDate = 'Thu October 23, 2025';
 </script>     <p class="new_to_fark_p" style="display: none">NEW To Fark? Find Out <a href="javascript:run_walkthrough('Banner')">HOW TO FARK</a><a href="javascript:close_new_to_fark_p()" class="close_new_to_fark_p">X</a></p>  <div style="text-align: center;">
    <a href="https://www.fark.com/submit/" class="submitLink loadNewerHeadlinesTrigger">Submit a Link &raquo;</a>
</div>   <div class="load_newer_container" style="display: none">
        <a id="headline_ajax_load_newer">&nbsp;</a>
    </div>   <table style="width: 100%;">
    <tr>
        <td id="headline_container">      <table class="headlineTable ">
            <tbody>
                <tr>
                    <td class="mainDate headline_date" colspan="4" data-farkHD="FriOctober242025"> Fri October 24, 2025 </td>
                </tr> <tr class="headlineRow id13855108" data-headline-count="1">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13855108 "  data-farkdomain="wbur.org" target="_blank" href="https://www.fark.com/goto/13855108/www.wbur.org/news/2025/10/20/mbta-narcan-pilot-cabinets%3Futm_source%3Dfark%26utm_medium%3Dwebsite"><img src="https://img.fark.net/images/2014/links/wburboston.png" width="77" height="27" srcset="https://img.fark.net/images/2014/links/wburboston.png 1x, https://img.fark.net/images/2014/links/wburboston-2x.png 2x"  class="retina" alt="(WBUR Boston)" title="WBUR Boston"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/awkward" title="Awkward"><span class="ttag topic48">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13855108 "  data-farkdomain="wbur.org" target="_blank" href="https://www.fark.com/goto/13855108/www.wbur.org/news/2025/10/20/mbta-narcan-pilot-cabinets%3Futm_source%3Dfark%26utm_medium%3Dwebsite">Good news: all the free Narcan put in cabinets at subway stations to combat overdoses was taken. Bad news: no evidence any of it was used to combat overdoses in the subway stations</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13855108 "  data-farkdomain="wbur.org" target="_blank" href="https://www.fark.com/goto/13855108">wbur.org</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13855108_2335" onclick="copyLinkToClipboard('copylink_13855108_2335', 'https://fark.com/13855108 --Fark headline: Good news: all the free Narcan put in cabinets at subway stations to combat overdoses was taken. Bad news: no evidence any of it was used to combat overdoses in the subway stations')" onmouseout="showCopyLink('copylink_13855108_2335')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13855108/Good-news-all-free-Narcan-put-in-cabinets-at-subway-stations-to-combat-overdoses-was-taken-Bad-news-no-evidence-any-of-it-was-used-to-combat-overdoses-in-subway-stations" target="_top" class="icon_comment">  <span class="icon_comment_count">6</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13855040" data-headline-count="2">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13855040 "  data-farkdomain="theguardian.com" target="_blank" href="https://www.fark.com/goto/13855040/www.theguardian.com/world/2025/oct/23/louvre-thieves-slow-motion-getaway-caught-on-video%3Futm_sourc"><img src="https://img.fark.net/images/2013/links/guardian.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/guardian.png 1x, https://img.fark.net/images/2013/links/guardian-2x.png 2x"  class="retina" alt="(Guardian)" title="Guardian"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/followup" title="Followup"><span class="ttag topic26">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13855040 "  data-farkdomain="theguardian.com" target="_blank" href="https://www.fark.com/goto/13855040/www.theguardian.com/world/2025/oct/23/louvre-thieves-slow-motion-getaway-caught-on-video%3Futm_sourc">Damn. They&#39;re very slowly getting away</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13855040 "  data-farkdomain="theguardian.com" target="_blank" href="https://www.fark.com/goto/13855040">theguardian.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13855040_6898" onclick="copyLinkToClipboard('copylink_13855040_6898', 'https://fark.com/13855040 --Fark headline: Damn. They\&#39;re very slowly getting away')" onmouseout="showCopyLink('copylink_13855040_6898')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13855040/Damn-Theyre-very-slowly-getting-away" target="_top" class="icon_comment">  <span class="icon_comment_count">12</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854846" data-headline-count="3">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854846 "  data-farkdomain="ksat.com" target="_blank" href="https://www.fark.com/goto/13854846/www.ksat.com/news/local/2025/10/23/bexar-county-family-survives-drive-by-shooting-their-16-year-old-"><img src="https://img.fark.net/images/2013/links/ksatsanantonio.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/ksatsanantonio.png 1x, https://img.fark.net/images/2013/links/ksatsanantonio-2x.png 2x"  class="retina" alt="(KSAT San Antonio)" title="KSAT San Antonio"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/dumbass" title="Dumbass"><span class="ttag topic34">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854846 "  data-farkdomain="ksat.com" target="_blank" href="https://www.fark.com/goto/13854846/www.ksat.com/news/local/2025/10/23/bexar-county-family-survives-drive-by-shooting-their-16-year-old-">Hey, stop shooting at us or you&#39;re grounded</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854846 "  data-farkdomain="ksat.com" target="_blank" href="https://www.fark.com/goto/13854846">ksat.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854846_8108" onclick="copyLinkToClipboard('copylink_13854846_8108', 'https://fark.com/13854846 --Fark headline: Hey, stop shooting at us or you\&#39;re grounded')" onmouseout="showCopyLink('copylink_13854846_8108')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854846/Hey-stop-shooting-at-us-youre-grounded" target="_top" class="icon_comment">  <span class="icon_comment_count">19</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr> </tbody>
        </table>  <table class="headlineTable ">
            <tbody>
                <tr>
                    <td class="mainDate headline_date" colspan="4" data-farkHD="ThuOctober232025"> Thu October 23, 2025 </td>
                </tr> <tr class="headlineRow id13855092" data-headline-count="4">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13855092 "  data-farkdomain="levittownnow.com" target="_blank" href="https://www.fark.com/goto/13855092/levittownnow.com/2025/10/22/police-name-young-supporter-first-honorary-k-9-unit-member/%3Futm_source"><img src="https://img.fark.net/images/2013/links/levittownnow.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/levittownnow.png 1x, https://img.fark.net/images/2013/links/levittownnow-2x.png 2x"  class="retina" alt="(Levittown Now)" title="Levittown Now"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/sappy" title="Sappy"><span class="ttag topic06">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13855092 "  data-farkdomain="levittownnow.com" target="_blank" href="https://www.fark.com/goto/13855092/levittownnow.com/2025/10/22/police-name-young-supporter-first-honorary-k-9-unit-member/%3Futm_source">Kid who raised $3k for police department&#39;s K-9 unit gets named honorary member of unit. Will get agility training and learn how to bite baddies</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13855092 "  data-farkdomain="levittownnow.com" target="_blank" href="https://www.fark.com/goto/13855092">levittownnow.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13855092_3841" onclick="copyLinkToClipboard('copylink_13855092_3841', 'https://fark.com/13855092 --Fark headline: Kid who raised $3k for police department\&#39;s K-9 unit gets named honorary member of unit. Will get agility training and learn how to bite baddies')" onmouseout="showCopyLink('copylink_13855092_3841')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13855092/Kid-who-raised-$3k-for-police-departments-K-9-unit-gets-named-honorary-member-of-unit-Will-get-agility-training-learn-how-to-bite-baddies" target="_top" class="icon_comment">  <span class="icon_comment_count">22</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow spau"><td colspan="4" style="max-width: 865px">  <div id="native_ad1"><script> googletag.cmd.push(function() { googletag.display('native_ad1'); });</script></div>   </td></tr><tr class="headlineRow id13855008" data-headline-count="5">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13855008 "  data-farkdomain="inquisitr.com" target="_blank" href="https://www.fark.com/goto/13855008/www.inquisitr.com/ice-detains-blind-protester-drops-him-on-his-head-while-he-sat-quietly-outside-fac"><img src="https://img.fark.net/images/2017/links/inquisitr.jpg" width="77" height="27" srcset="https://img.fark.net/images/2017/links/inquisitr.jpg 1x, https://img.fark.net/images/2017/links/inquisitr-2x.jpg 2x"  class="retina" alt="(Inquisitr)" title="Inquisitr"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/sick" title="Sick"><span class="ttag topic08">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13855008 "  data-farkdomain="inquisitr.com" target="_blank" href="https://www.fark.com/goto/13855008/www.inquisitr.com/ice-detains-blind-protester-drops-him-on-his-head-while-he-sat-quietly-outside-fac">He did not see this coming</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13855008 "  data-farkdomain="inquisitr.com" target="_blank" href="https://www.fark.com/goto/13855008">inquisitr.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13855008_3666" onclick="copyLinkToClipboard('copylink_13855008_3666', 'https://fark.com/13855008 --Fark headline: He did not see this coming')" onmouseout="showCopyLink('copylink_13855008_3666')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13855008/He-did-not-see-this-coming" target="_top" class="icon_comment">  <span class="icon_comment_count">52</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13855110" data-headline-count="6">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13855110 "  data-farkdomain="boston.com" target="_blank" href="https://www.fark.com/goto/13855110/www.boston.com/news/local-news/2025/10/23/city-councilor-pushes-for-more-scrutiny-of-adult-entertain"><img src="https://img.fark.net/images/2013/links/bostoncom.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/bostoncom.png 1x, https://img.fark.net/images/2013/links/bostoncom-2x.png 2x"  class="retina" alt="(Boston.com)" title="Boston.com"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/giggity" title="Giggity"><span class="ttag topic50">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13855110 "  data-farkdomain="boston.com" target="_blank" href="https://www.fark.com/goto/13855110/www.boston.com/news/local-news/2025/10/23/city-councilor-pushes-for-more-scrutiny-of-adult-entertain">City councilor calls for more scrutiny of strippers. Sounds like a noble cause; where do we sign up?</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13855110 "  data-farkdomain="boston.com" target="_blank" href="https://www.fark.com/goto/13855110">boston.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13855110_5363" onclick="copyLinkToClipboard('copylink_13855110_5363', 'https://fark.com/13855110 --Fark headline: City councilor calls for more scrutiny of strippers. Sounds like a noble cause; where do we sign up?')" onmouseout="showCopyLink('copylink_13855110_5363')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13855110/City-councilor-calls-for-more-scrutiny-of-strippers-Sounds-like-a-noble-cause-where-do-we-sign-up" target="_top" class="icon_comment">  <span class="icon_comment_count">42</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13851796" data-headline-count="7">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13851796 "  data-farkdomain="artlogic-res.cloudinary.com" target="_blank" href="https://www.fark.com/goto/13851796/artlogic-res.cloudinary.com/w_2400,h_2400,c_limit,f_auto,fl_lossy,q_auto/ws-tanyabonakdargallery/usr">(Some Guy)</a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/photoshop" title="Photoshop"><span class="ttag topic23">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13851796 "  data-farkdomain="artlogic-res.cloudinary.com" target="_blank" href="https://www.fark.com/goto/13851796/artlogic-res.cloudinary.com/w_2400,h_2400,c_limit,f_auto,fl_lossy,q_auto/ws-tanyabonakdargallery/usr">Photoshop this toy exhibition</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13851796 "  data-farkdomain="artlogic-res.cloudinary.com" target="_blank" href="https://www.fark.com/goto/13851796">artlogic-res.cloudinary.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13851796_5255" onclick="copyLinkToClipboard('copylink_13851796_5255', 'https://fark.com/13851796 --Fark headline: Photoshop this toy exhibition')" onmouseout="showCopyLink('copylink_13851796_5255')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13851796/Photoshop-this-toy-exhibition" target="_top" class="icon_comment">  <span class="icon_comment_count">9</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13855024" data-headline-count="8">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13855024 "  data-farkdomain="thegamer.com" target="_blank" href="https://www.fark.com/goto/13855024/www.thegamer.com/counter-strike-2-cs2-knives-gloves-update-skin-market-cap-2-billion-dollar-loss/%3F"><img src="https://img.fark.net/images/2022/links/thegamer.png" width="77" height="27" srcset="https://img.fark.net/images/2022/links/thegamer.png 1x, https://img.fark.net/images/2022/links/thegamer-2x.png 2x"  class="retina" alt="(The Gamer)" title="The Gamer"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/fail" title="Fail"><span class="ttag topic42">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13855024 "  data-farkdomain="thegamer.com" target="_blank" href="https://www.fark.com/goto/13855024/www.thegamer.com/counter-strike-2-cs2-knives-gloves-update-skin-market-cap-2-billion-dollar-loss/%3F">Using Counter-Strike skins as an investment vehicle? We have some very bad news for you. Also what the hell</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13855024 "  data-farkdomain="thegamer.com" target="_blank" href="https://www.fark.com/goto/13855024">thegamer.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13855024_4786" onclick="copyLinkToClipboard('copylink_13855024_4786', 'https://fark.com/13855024 --Fark headline: Using Counter-Strike skins as an investment vehicle? We have some very bad news for you. Also what the hell')" onmouseout="showCopyLink('copylink_13855024_4786')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13855024/Using-Counter-Strike-skins-as-an-investment-vehicle-We-have-some-very-bad-news-for-you-Also-what-hell" target="_top" class="icon_comment">  <span class="icon_comment_count">92</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854878" data-headline-count="9">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854878 "  data-farkdomain="npr.org" target="_blank" href="https://www.fark.com/goto/13854878/www.npr.org/2025/10/23/nx-s1-5577963/guillermo-del-toro-frankenstein"><img src="https://img.fark.net/images/2013/links/npr.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/npr.png 1x, https://img.fark.net/images/2013/links/npr-2x.png 2x"  class="retina" alt="(NPR)" title="NPR"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/obvious" title="Obvious"><span class="ttag topic15">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854878 "  data-farkdomain="npr.org" target="_blank" href="https://www.fark.com/goto/13854878/www.npr.org/2025/10/23/nx-s1-5577963/guillermo-del-toro-frankenstein">Dr. Frankenstein was basically the original techbro: A possibly brilliant but self-deluded narcissist who rushed blindly into the process of creating something new without giving the slightest thought whatsoever to the potential negative consequences</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854878 "  data-farkdomain="npr.org" target="_blank" href="https://www.fark.com/goto/13854878">npr.org</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854878_9303" onclick="copyLinkToClipboard('copylink_13854878_9303', 'https://fark.com/13854878 --Fark headline: Dr. Frankenstein was basically the original techbro: A possibly brilliant but self-deluded narcissist who rushed blindly into the process of creating something new without giving the slightest thought whatsoever to the potential negative consequences')" onmouseout="showCopyLink('copylink_13854878_9303')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854878/Dr-Frankenstein-was-basically-original-techbro-A-possibly-brilliant-but-self-deluded-narcissist-who-rushed-blindly-into-process-of-creating-something-new-without-giving-slightest-thought-whatsoever-to-potential-negative-consequences" target="_top" class="icon_comment">  <span class="icon_comment_count">48</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow spau"><td colspan="4" style="max-width: 865px">  <div id="native_ad2"><script> googletag.cmd.push(function() { googletag.display('native_ad2'); });</script></div>   </td></tr><tr class="headlineRow id13854734" data-headline-count="10">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854734 "  data-farkdomain="bbc.co.uk" target="_blank" href="https://www.fark.com/goto/13854734/www.bbc.co.uk/mediacentre/2025/new-ebu-research-ai-assistants-news-content%3Futm_source%3Dfark%26utm"><img src="https://img.fark.net/images/2013/links/bbc.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/bbc.png 1x, https://img.fark.net/images/2013/links/bbc-2x.png 2x"  class="retina" alt="(BBC)" title="BBC"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/spiffy" title="Spiffy"><span class="ttag topic16">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854734 "  data-farkdomain="bbc.co.uk" target="_blank" href="https://www.fark.com/goto/13854734/www.bbc.co.uk/mediacentre/2025/new-ebu-research-ai-assistants-news-content%3Futm_source%3Dfark%26utm">Good news: AI assistants misrepresent the news only 45% of the time</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854734 "  data-farkdomain="bbc.co.uk" target="_blank" href="https://www.fark.com/goto/13854734">bbc.co.uk</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854734_9486" onclick="copyLinkToClipboard('copylink_13854734_9486', 'https://fark.com/13854734 --Fark headline: Good news: AI assistants misrepresent the news only 45% of the time')" onmouseout="showCopyLink('copylink_13854734_9486')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854734/Good-news-AI-assistants-misrepresent-news-only-45-of-time" target="_top" class="icon_comment">  <span class="icon_comment_count">41</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854790" data-headline-count="11">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854790 "  data-farkdomain="youtube.com" target="_blank" href="https://www.fark.com/goto/13854790/www.youtube.com/watch%3Fv%3DSDMETM8rJBk"><img src="https://img.fark.net/images/2020/links/youtube.png" width="77" height="27" srcset="https://img.fark.net/images/2020/links/youtube.png 1x, https://img.fark.net/images/2020/links/youtube-2x.png 2x"  class="retina" alt="(YouTube)" title="YouTube"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/asinine" title="Asinine"><span class="ttag topic13">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854790 "  data-farkdomain="youtube.com" target="_blank" href="https://www.fark.com/goto/13854790/www.youtube.com/watch%3Fv%3DSDMETM8rJBk">Britain&#39;s fart-powered Edwardian street lamps - cuz when life crop-dusts you lemons squeeze them off into lemonade</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854790 "  data-farkdomain="youtube.com" target="_blank" href="https://www.fark.com/goto/13854790">youtube.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854790_2862" onclick="copyLinkToClipboard('copylink_13854790_2862', 'https://fark.com/13854790 --Fark headline: Britain\&#39;s fart-powered Edwardian street lamps - cuz when life crop-dusts you lemons squeeze them off into lemonade')" onmouseout="showCopyLink('copylink_13854790_2862')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854790/Britains-fart-powered-Edwardian-street-lamps-cuz-when-life-crop-dusts-you-lemons-squeeze-them-off-into-lemonade" target="_top" class="icon_comment">  <span class="icon_comment_count">14</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854370" data-headline-count="12">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854370 "  data-farkdomain="nationaltoday.com" target="_blank" href="https://www.fark.com/goto/13854370/nationaltoday.com/national-slap-your-coworker-day/%3Futm_source%3Dfark%26utm_medium%3Dwebsite%26utm_"><img src="https://img.fark.net/images/2021/links/nationaltoday.png" width="77" height="27" srcset="https://img.fark.net/images/2021/links/nationaltoday.png 1x, https://img.fark.net/images/2021/links/nationaltoday-2x.png 2x"  class="retina" alt="(National Today)" title="National Today"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/silly" title="Silly"><span class="ttag topic09">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854370 "  data-farkdomain="nationaltoday.com" target="_blank" href="https://www.fark.com/goto/13854370/nationaltoday.com/national-slap-your-coworker-day/%3Futm_source%3Dfark%26utm_medium%3Dwebsite%26utm_">Doo eet. DOO EET</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854370 "  data-farkdomain="nationaltoday.com" target="_blank" href="https://www.fark.com/goto/13854370">nationaltoday.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854370_4244" onclick="copyLinkToClipboard('copylink_13854370_4244', 'https://fark.com/13854370 --Fark headline: Doo eet. DOO EET')" onmouseout="showCopyLink('copylink_13854370_4244')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854370/Doo-eet-DOO-EET" target="_top" class="icon_comment">  <span class="icon_comment_count">30</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13851740" data-headline-count="13">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13851740 "  data-farkdomain="angelicahenrydesign.com" target="_blank" href="https://www.fark.com/goto/13851740/angelicahenrydesign.com/wp-content/uploads/2018/01/Cozy-Cabin-with-Rustic-Charm-Kitchen-Angelica-Hen">(Some Hipster)</a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/photoshop" title="Photoshop"><span class="ttag topic23">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13851740 "  data-farkdomain="angelicahenrydesign.com" target="_blank" href="https://www.fark.com/goto/13851740/angelicahenrydesign.com/wp-content/uploads/2018/01/Cozy-Cabin-with-Rustic-Charm-Kitchen-Angelica-Hen">Photoshop this retro kitchen</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13851740 "  data-farkdomain="angelicahenrydesign.com" target="_blank" href="https://www.fark.com/goto/13851740">angelicahenrydesign.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13851740_8722" onclick="copyLinkToClipboard('copylink_13851740_8722', 'https://fark.com/13851740 --Fark headline: Photoshop this retro kitchen')" onmouseout="showCopyLink('copylink_13851740_8722')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13851740/Photoshop-this-retro-kitchen" target="_top" class="icon_comment">  <span class="icon_comment_count">13</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854310" data-headline-count="14">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854310 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854310/apnews.com/article/germany-pumpkins-halloween-farm-festival-cb94e3a160a87a8041cbd23c78487f24%3Futm_s"><img src="https://img.fark.net/images/2013/links/apnews.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/apnews.png 1x, https://img.fark.net/images/2013/links/apnews-2x.png 2x"  class="retina" alt="(AP News)" title="AP News"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/giggity" title="Giggity"><span class="ttag topic50">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854310 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854310/apnews.com/article/germany-pumpkins-halloween-farm-festival-cb94e3a160a87a8041cbd23c78487f24%3Futm_s">Gourdous women shaping up in Berlin</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854310 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854310">apnews.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854310_1448" onclick="copyLinkToClipboard('copylink_13854310_1448', 'https://fark.com/13854310 --Fark headline: Gourdous women shaping up in Berlin')" onmouseout="showCopyLink('copylink_13854310_1448')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854310/Gourdous-women-shaping-up-in-Berlin" target="_top" class="icon_comment">  <span class="icon_comment_count">9</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854506" data-headline-count="15">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854506 "  data-farkdomain="northpennnow.com" target="_blank" href="https://www.fark.com/goto/13854506/northpennnow.com/news/2025/oct/22/teen-facing-felony-charges-for-bringing-9mm-handgun-to-north-penn-"><img src="https://img.fark.net/images/2022/links/northpennnow.png" width="77" height="27" srcset="https://img.fark.net/images/2022/links/northpennnow.png 1x, https://img.fark.net/images/2022/links/northpennnow-2x.png 2x"  class="retina" alt="(North Penn Now)" title="North Penn Now"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/murica" title="Murica"><span class="ttag topic52">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854506 "  data-farkdomain="northpennnow.com" target="_blank" href="https://www.fark.com/goto/13854506/northpennnow.com/news/2025/oct/22/teen-facing-felony-charges-for-bringing-9mm-handgun-to-north-penn-">Teen facing a felony for bringing a gun that is less than a centimeter in size to school. Probably because of using the metric system</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854506 "  data-farkdomain="northpennnow.com" target="_blank" href="https://www.fark.com/goto/13854506">northpennnow.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854506_9240" onclick="copyLinkToClipboard('copylink_13854506_9240', 'https://fark.com/13854506 --Fark headline: Teen facing a felony for bringing a gun that is less than a centimeter in size to school. Probably because of using the metric system')" onmouseout="showCopyLink('copylink_13854506_9240')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854506/Teen-facing-a-felony-for-bringing-a-gun-that-is-less-than-a-centimeter-in-size-to-school-Probably-because-of-using-metric-system" target="_top" class="icon_comment">  <span class="icon_comment_count">54</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854826" data-headline-count="16">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854826 "  data-farkdomain="wfmz.com" target="_blank" href="https://www.fark.com/goto/13854826/www.wfmz.com/news/area/berks/reading-area/its-already-a-traffic-nightmare-residents-react-to-roundab"><img src="https://img.fark.net/images/2022/links/wfmz.png" width="77" height="27" srcset="https://img.fark.net/images/2022/links/wfmz.png 1x, https://img.fark.net/images/2022/links/wfmz-2x.png 2x"  class="retina" alt="(WFMZ Allentown)" title="WFMZ Allentown"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/silly" title="Silly"><span class="ttag topic09">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854826 "  data-farkdomain="wfmz.com" target="_blank" href="https://www.fark.com/goto/13854826/www.wfmz.com/news/area/berks/reading-area/its-already-a-traffic-nightmare-residents-react-to-roundab">3 roundabouts to complete roundabout trifecta. With bonus input from self taught traffic engineers</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854826 "  data-farkdomain="wfmz.com" target="_blank" href="https://www.fark.com/goto/13854826">wfmz.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854826_437" onclick="copyLinkToClipboard('copylink_13854826_437', 'https://fark.com/13854826 --Fark headline: 3 roundabouts to complete roundabout trifecta. With bonus input from self taught traffic engineers')" onmouseout="showCopyLink('copylink_13854826_437')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854826/-3-roundabouts-to-complete-roundabout-trifecta-With-bonus-input-from-self-taught-traffic-engineers" target="_top" class="icon_comment">  <span class="icon_comment_count">39</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854852" data-headline-count="17">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854852 "  data-farkdomain="cbsnews.com" target="_blank" href="https://www.fark.com/goto/13854852/www.cbsnews.com/news/turkey-price-increase-thanksgiving-2025/%3Futm_source%3Dfark%26utm_medium%3Dweb"><img src="https://img.fark.net/images/2013/links/cbsnews.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/cbsnews.png 1x, https://img.fark.net/images/2013/links/cbsnews-2x.png 2x"  class="retina" alt="(CBS News)" title="CBS News"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/followup" title="Followup"><span class="ttag topic26">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854852 "  data-farkdomain="cbsnews.com" target="_blank" href="https://www.fark.com/goto/13854852/www.cbsnews.com/news/turkey-price-increase-thanksgiving-2025/%3Futm_source%3Dfark%26utm_medium%3Dweb">Worried about rising grocery prices? Wait till you go to buy a thanksgiving turkey</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854852 "  data-farkdomain="cbsnews.com" target="_blank" href="https://www.fark.com/goto/13854852">cbsnews.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854852_9248" onclick="copyLinkToClipboard('copylink_13854852_9248', 'https://fark.com/13854852 --Fark headline: Worried about rising grocery prices? Wait till you go to buy a thanksgiving turkey')" onmouseout="showCopyLink('copylink_13854852_9248')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854852/Worried-about-rising-grocery-prices-Wait-till-you-go-to-buy-a-thanksgiving-turkey" target="_top" class="icon_comment">  <span class="icon_comment_count">186</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854722" data-headline-count="18">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854722 "  data-farkdomain="msn.com" target="_blank" href="https://www.fark.com/goto/13854722/www.msn.com/en-us/entertainment/celebrities/boob-jobs-are-shrinking/ar-AA1P253L%3Focid%3DBingNewsVer"><img src="https://img.fark.net/images/2014/links/msn.png" width="77" height="27" srcset="https://img.fark.net/images/2014/links/msn.png 1x, https://img.fark.net/images/2014/links/msn-2x.png 2x"  class="retina" alt="(MSN)" title="MSN"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/boobies" title="Boobies"><img src="https://img.fark.net/images/2013/topics/boobies.gif" width="54" height="11" srcset="https://img.fark.net/images/2013/topics/boobies.gif 1x, https://img.fark.net/images/2013/topics/boobies-2x.gif 2x"  class="retina" alt="Boobies" title="Boobies"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854722 "  data-farkdomain="msn.com" target="_blank" href="https://www.fark.com/goto/13854722/www.msn.com/en-us/entertainment/celebrities/boob-jobs-are-shrinking/ar-AA1P253L%3Focid%3DBingNewsVer">American women are putting for plums over cantaloupes</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854722 "  data-farkdomain="msn.com" target="_blank" href="https://www.fark.com/goto/13854722">msn.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854722_981" onclick="copyLinkToClipboard('copylink_13854722_981', 'https://fark.com/13854722 --Fark headline: American women are putting for plums over cantaloupes')" onmouseout="showCopyLink('copylink_13854722_981')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854722/American-women-are-putting-for-plums-over-cantaloupes" target="_top" class="icon_comment">  <span class="icon_comment_count">173</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854422" data-headline-count="19">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854422 "  data-farkdomain="atlantablackstar.com" target="_blank" href="https://www.fark.com/goto/13854422/atlantablackstar.com/2025/10/22/nypd-cops-swerved-into-black-man-on-scooter-then-tried-to-blame-him-"><img src="https://img.fark.net/images/2024/links/atlantablackstar.jpg" width="77" height="27" srcset="https://img.fark.net/images/2024/links/atlantablackstar.jpg 1x, https://img.fark.net/images/2024/links/atlantablackstar-2x.jpg 2x"  class="retina" alt="(Atlanta Black Star)" title="Atlanta Black Star"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/facepalm" title="Facepalm"><span class="ttag topic49">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854422 "  data-farkdomain="atlantablackstar.com" target="_blank" href="https://www.fark.com/goto/13854422/atlantablackstar.com/2025/10/22/nypd-cops-swerved-into-black-man-on-scooter-then-tried-to-blame-him-">Police insist they tried to avoid collision after being caught on video aiming straight for it</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854422 "  data-farkdomain="atlantablackstar.com" target="_blank" href="https://www.fark.com/goto/13854422">atlantablackstar.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854422_3380" onclick="copyLinkToClipboard('copylink_13854422_3380', 'https://fark.com/13854422 --Fark headline: Police insist they tried to avoid collision after being caught on video aiming straight for it')" onmouseout="showCopyLink('copylink_13854422_3380')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854422/Police-insist-they-tried-to-avoid-collision-after-being-caught-on-video-aiming-straight-for-it" target="_top" class="icon_comment">  <span class="icon_comment_count">43</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854262" data-headline-count="20">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854262 "  data-farkdomain="people.com" target="_blank" href="https://www.fark.com/goto/13854262/people.com/luigi-mangione-texted-joke-prostitute-pornstar-pokemon-cards-11835279%3Futm_source%3Dfark"><img src="https://img.fark.net/images/2013/links/peoplemagazine.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/peoplemagazine.png 1x, https://img.fark.net/images/2013/links/peoplemagazine-2x.png 2x"  class="retina" alt="(People Magazine)" title="People Magazine"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/giggity" title="Giggity"><span class="ttag topic50">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854262 "  data-farkdomain="people.com" target="_blank" href="https://www.fark.com/goto/13854262/people.com/luigi-mangione-texted-joke-prostitute-pornstar-pokemon-cards-11835279%3Futm_source%3Dfark">Yes, it&#39;s an article about Luigi Mangione, but the only thing Subby learned from it was that apparently there are Pornstar Pok&eacute;mon Cards</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854262 "  data-farkdomain="people.com" target="_blank" href="https://www.fark.com/goto/13854262">people.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854262_8695" onclick="copyLinkToClipboard('copylink_13854262_8695', 'https://fark.com/13854262 --Fark headline: Yes, it\&#39;s an article about Luigi Mangione, but the only thing Subby learned from it was that apparently there are Pornstar Pok&eacute;mon Cards')" onmouseout="showCopyLink('copylink_13854262_8695')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854262/Yes-its-an-article-about-Luigi-Mangione-but-only-thing-Subby-learned-from-it-was-that-apparently-there-are-Pornstar-Pokmon-Cards" target="_top" class="icon_comment">  <span class="icon_comment_count">35</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854566" data-headline-count="21">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854566 "  data-farkdomain="thegrio.com" target="_blank" href="https://www.fark.com/goto/13854566/thegrio.com/2025/10/23/plan-to-sell-golf-course-built-on-slaves-graves-sparks-outrage-in-floridas-ca"><img src="https://img.fark.net/images/2014/links/thegrio.png" width="77" height="27" srcset="https://img.fark.net/images/2014/links/thegrio.png 1x, https://img.fark.net/images/2014/links/thegrio-2x.png 2x"  class="retina" alt="(The Grio)" title="The Grio"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/florida" title="Florida"><span class="ttag topic35">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854566 "  data-farkdomain="thegrio.com" target="_blank" href="https://www.fark.com/goto/13854566/thegrio.com/2025/10/23/plan-to-sell-golf-course-built-on-slaves-graves-sparks-outrage-in-floridas-ca">Poltergeist 4: Golf Course Boogaloo</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854566 "  data-farkdomain="thegrio.com" target="_blank" href="https://www.fark.com/goto/13854566">thegrio.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854566_4806" onclick="copyLinkToClipboard('copylink_13854566_4806', 'https://fark.com/13854566 --Fark headline: Poltergeist 4: Golf Course Boogaloo')" onmouseout="showCopyLink('copylink_13854566_4806')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854566/Poltergeist-4-Golf-Course-Boogaloo" target="_top" class="icon_comment">  <span class="icon_comment_count">17</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853998" data-headline-count="22">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853998 "  data-farkdomain="dims.apnews.com" target="_blank" href="https://www.fark.com/goto/13853998/dims.apnews.com/dims4/default/34955bb/2147483647/strip/true/crop/7702x5135%2B0%2B0/resize/2720x1814!"><img src="https://img.fark.net/images/2013/links/apnews.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/apnews.png 1x, https://img.fark.net/images/2013/links/apnews-2x.png 2x"  class="retina" alt="(AP News)" title="AP News"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/caption" title="Caption"><span class="ttag topic22">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853998 "  data-farkdomain="dims.apnews.com" target="_blank" href="https://www.fark.com/goto/13853998/dims.apnews.com/dims4/default/34955bb/2147483647/strip/true/crop/7702x5135%2B0%2B0/resize/2720x1814!">Caption this excited passenger</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853998 "  data-farkdomain="dims.apnews.com" target="_blank" href="https://www.fark.com/goto/13853998">dims.apnews.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853998_1495" onclick="copyLinkToClipboard('copylink_13853998_1495', 'https://fark.com/13853998 --Fark headline: Caption this excited passenger')" onmouseout="showCopyLink('copylink_13853998_1495')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853998/Caption-this-excited-passenger" target="_top" class="icon_comment">  <span class="icon_comment_count">31</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854638" data-headline-count="23">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854638 "  data-farkdomain="wtop.com" target="_blank" href="https://www.fark.com/goto/13854638/wtop.com/loudoun-county/2025/10/roundabout-project-to-keep-commuters-moving-begins-in-loudoun-co/"><img src="https://img.fark.net/images/2016/links/wtop.png" width="77" height="27" srcset="https://img.fark.net/images/2016/links/wtop.png 1x, https://img.fark.net/images/2016/links/wtop-2x.png 2x"  class="retina" alt="(WTOP)" title="WTOP"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/scary" title="Scary"><span class="ttag topic19">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854638 "  data-farkdomain="wtop.com" target="_blank" href="https://www.fark.com/goto/13854638/wtop.com/loudoun-county/2025/10/roundabout-project-to-keep-commuters-moving-begins-in-loudoun-co/">Commuters in Loudoun County, VA are about to experience...A ROUNDABOUT. Americans too stupid for traffic circles trifecta now in play</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854638 "  data-farkdomain="wtop.com" target="_blank" href="https://www.fark.com/goto/13854638">wtop.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854638_9278" onclick="copyLinkToClipboard('copylink_13854638_9278', 'https://fark.com/13854638 --Fark headline: Commuters in Loudoun County, VA are about to experience...A ROUNDABOUT. Americans too stupid for traffic circles trifecta now in play')" onmouseout="showCopyLink('copylink_13854638_9278')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854638/Commuters-in-Loudoun-County-VA-are-about-to-experienceA-ROUNDABOUT-Americans-too-stupid-for-traffic-circles-trifecta-now-in-play" target="_top" class="icon_comment">  <span class="icon_comment_count">59</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854062" data-headline-count="24">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854062 "  data-farkdomain="abc.net.au" target="_blank" href="https://www.fark.com/goto/13854062/www.abc.net.au/news/2025-10-22/red-crab-migration-begins-on-christmas-island/105916362%3Futm_source"><img src="https://img.fark.net/images/2013/links/abcnetau.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/abcnetau.png 1x, https://img.fark.net/images/2013/links/abcnetau-2x.png 2x"  class="retina" alt="(Abc.net.au)" title="Abc.net.au"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/creepy" title="Creepy"><span class="ttag topic53">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854062 "  data-farkdomain="abc.net.au" target="_blank" href="https://www.fark.com/goto/13854062/www.abc.net.au/news/2025-10-22/red-crab-migration-begins-on-christmas-island/105916362%3Futm_source">If you suffer from kabourophobia, now is not the time to visit Christmas Island</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854062 "  data-farkdomain="abc.net.au" target="_blank" href="https://www.fark.com/goto/13854062">abc.net.au</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854062_5129" onclick="copyLinkToClipboard('copylink_13854062_5129', 'https://fark.com/13854062 --Fark headline: If you suffer from kabourophobia, now is not the time to visit Christmas Island')" onmouseout="showCopyLink('copylink_13854062_5129')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854062/If-you-suffer-from-kabourophobia-now-is-not-time-to-visit-Christmas-Island" target="_top" class="icon_comment">  <span class="icon_comment_count">18</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854130" data-headline-count="25">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854130 "  data-farkdomain="armytimes.com" target="_blank" href="https://www.fark.com/goto/13854130/www.armytimes.com/news/your-army/2025/10/22/should-the-army-bring-back-the-pentomic-division/%3Futm_"><img src="https://img.fark.net/images/2012/links/armytimes.png" width="77" height="27" srcset="https://img.fark.net/images/2012/links/armytimes.png 1x, https://img.fark.net/images/2012/links/armytimes-2x.png 2x"  class="retina" alt="(Army Times)" title="Army Times"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/interesting" title="Interesting"><span class="ttag topic02">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854130 "  data-farkdomain="armytimes.com" target="_blank" href="https://www.fark.com/goto/13854130/www.armytimes.com/news/your-army/2025/10/22/should-the-army-bring-back-the-pentomic-division/%3Futm_">In our new world of drone warfare, US Army considers returning to Cold War relic, the Pentomic Division</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854130 "  data-farkdomain="armytimes.com" target="_blank" href="https://www.fark.com/goto/13854130">armytimes.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854130_871" onclick="copyLinkToClipboard('copylink_13854130_871', 'https://fark.com/13854130 --Fark headline: In our new world of drone warfare, US Army considers returning to Cold War relic, the Pentomic Division')" onmouseout="showCopyLink('copylink_13854130_871')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854130/In-our-new-world-of-drone-warfare-US-Army-considers-returning-to-Cold-War-relic-Pentomic-Division" target="_top" class="icon_comment">  <span class="icon_comment_count">12</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854576" data-headline-count="26">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854576 "  data-farkdomain="stripes.com" target="_blank" href="https://www.fark.com/goto/13854576/www.stripes.com/branches/air_force/2025-10-23/air-force-barracks-inspection-safe-conditions-19517142"><img src="https://img.fark.net/images/2013/links/starsandstripes.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/starsandstripes.png 1x, https://img.fark.net/images/2013/links/starsandstripes-2x.png 2x"  class="retina" alt="(Stars and Stripes)" title="Stars and Stripes"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/unlikely" title="Unlikely"><span class="ttag topic33">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854576 "  data-farkdomain="stripes.com" target="_blank" href="https://www.fark.com/goto/13854576/www.stripes.com/branches/air_force/2025-10-23/air-force-barracks-inspection-safe-conditions-19517142">US Air Force announces it will conduct 100% barracks inspection worldwide in just seven days &quot;to improve living conditions.&quot; Quick, everybody, hide your dope</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854576 "  data-farkdomain="stripes.com" target="_blank" href="https://www.fark.com/goto/13854576">stripes.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854576_4199" onclick="copyLinkToClipboard('copylink_13854576_4199', 'https://fark.com/13854576 --Fark headline: US Air Force announces it will conduct 100% barracks inspection worldwide in just seven days &quot;to improve living conditions.&quot; Quick, everybody, hide your dope')" onmouseout="showCopyLink('copylink_13854576_4199')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854576/US-Air-Force-announces-it-will-conduct-100-barracks-inspection-worldwide-in-just-seven-days-to-improve-living-conditions-Quick-everybody-hide-your-dope" target="_top" class="icon_comment">  <span class="icon_comment_count">77</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854572" data-headline-count="27">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854572 "  data-farkdomain="wpln.org" target="_blank" href="https://www.fark.com/goto/13854572/wpln.org/post/what-to-know-about-elon-musks-nashville-tunnel-project/%3Futm_source%3Dfark%26utm_medi"><img src="https://img.fark.net/images/2020/links/wpln.png" width="77" height="27" srcset="https://img.fark.net/images/2020/links/wpln.png 1x, https://img.fark.net/images/2020/links/wpln-2x.png 2x"  class="retina" alt="(WPLN Nashville)" title="WPLN Nashville"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/facepalm" title="Facepalm"><span class="ttag topic49">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854572 "  data-farkdomain="wpln.org" target="_blank" href="https://www.fark.com/goto/13854572/wpln.org/post/what-to-know-about-elon-musks-nashville-tunnel-project/%3Futm_source%3Dfark%26utm_medi">Elmo is boring. And that&#39;s not a good thing</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854572 "  data-farkdomain="wpln.org" target="_blank" href="https://www.fark.com/goto/13854572">wpln.org</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854572_9647" onclick="copyLinkToClipboard('copylink_13854572_9647', 'https://fark.com/13854572 --Fark headline: Elmo is boring. And that\&#39;s not a good thing')" onmouseout="showCopyLink('copylink_13854572_9647')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854572/Elmo-is-boring-And-thats-not-a-good-thing" target="_top" class="icon_comment">  <span class="icon_comment_count">64</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854264" data-headline-count="28">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854264 "  data-farkdomain="metro.co.uk" target="_blank" href="https://www.fark.com/goto/13854264/metro.co.uk/2025/10/23/storm-benjamin-causes-travel-misery-hits-uk-75mph-winds-24502202/%3Futm_sourc"><img src="https://img.fark.net/images/2025/links/metro.png" width="77" height="27" srcset="https://img.fark.net/images/2025/links/metro.png 1x, https://img.fark.net/images/2025/links/metro-2x.png 2x"  class="retina" alt="(Metro)" title="Metro"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/psa" title="PSA"><span class="ttag topic14">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854264 "  data-farkdomain="metro.co.uk" target="_blank" href="https://www.fark.com/goto/13854264/metro.co.uk/2025/10/23/storm-benjamin-causes-travel-misery-hits-uk-75mph-winds-24502202/%3Futm_sourc">Hurricane Benjamin set to inconvenience millions</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854264 "  data-farkdomain="metro.co.uk" target="_blank" href="https://www.fark.com/goto/13854264">metro.co.uk</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854264_5246" onclick="copyLinkToClipboard('copylink_13854264_5246', 'https://fark.com/13854264 --Fark headline: Hurricane Benjamin set to inconvenience millions')" onmouseout="showCopyLink('copylink_13854264_5246')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854264/Hurricane-Benjamin-set-to-inconvenience-millions" target="_top" class="icon_comment">  <span class="icon_comment_count">22</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854174" data-headline-count="29">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854174 "  data-farkdomain="bbc.com" target="_blank" href="https://www.fark.com/goto/13854174/www.bbc.com/culture/article/20251021-the-key-to-man-rays-le-violon-dingres-disturbing-erotic-power"><img src="https://img.fark.net/images/2013/links/bbcus.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/bbcus.png 1x, https://img.fark.net/images/2013/links/bbcus-2x.png 2x"  class="retina" alt="(BBC-US)" title="BBC-US"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/interesting" title="Interesting"><span class="ttag topic02">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854174 "  data-farkdomain="bbc.com" target="_blank" href="https://www.fark.com/goto/13854174/www.bbc.com/culture/article/20251021-the-key-to-man-rays-le-violon-dingres-disturbing-erotic-power">Woman&#39;s body continues to fascinate, confuse, and upset viewers after over 100 years, and not just the basement-dwellers. This is not an allegory (sfw-ish)</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854174 "  data-farkdomain="bbc.com" target="_blank" href="https://www.fark.com/goto/13854174">bbc.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854174_24" onclick="copyLinkToClipboard('copylink_13854174_24', 'https://fark.com/13854174 --Fark headline: Woman\&#39;s body continues to fascinate, confuse, and upset viewers after over 100 years, and not just the basement-dwellers. This is not an allegory (sfw-ish)')" onmouseout="showCopyLink('copylink_13854174_24')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854174/Womans-body-continues-to-fascinate-confuse-upset-viewers-after-over-100-years-not-just-basement-dwellers-This-is-not-an-allegory-sfw-ish" target="_top" class="icon_comment">  <span class="icon_comment_count">46</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854096" data-headline-count="30">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854096 "  data-farkdomain="wmur.com" target="_blank" href="https://www.fark.com/goto/13854096/www.wmur.com/article/surveillance-video-speedo-sheriffs-office-102225/69126184%3Futm_source%3Dfark"><img src="https://img.fark.net/images/2013/links/wmurnewhampshire.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/wmurnewhampshire.png 1x, https://img.fark.net/images/2013/links/wmurnewhampshire-2x.png 2x"  class="retina" alt="(WMUR New Hampshire)" title="WMUR New Hampshire"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/dumbass" title="Dumbass"><span class="ttag topic34">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854096 "  data-farkdomain="wmur.com" target="_blank" href="https://www.fark.com/goto/13854096/www.wmur.com/article/surveillance-video-speedo-sheriffs-office-102225/69126184%3Futm_source%3Dfark">Man in Speedo leads police on a brief chase</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854096 "  data-farkdomain="wmur.com" target="_blank" href="https://www.fark.com/goto/13854096">wmur.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854096_2855" onclick="copyLinkToClipboard('copylink_13854096_2855', 'https://fark.com/13854096 --Fark headline: Man in Speedo leads police on a brief chase')" onmouseout="showCopyLink('copylink_13854096_2855')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854096/Man-in-Speedo-leads-police-on-a-brief-chase" target="_top" class="icon_comment">  <span class="icon_comment_count">22</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854414" data-headline-count="31">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854414 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854414/apnews.com/video/patient-with-parkinsons-disease-plays-clarinet-during-brain-procedure-at-london-hos"><img src="https://img.fark.net/images/2013/links/apnews.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/apnews.png 1x, https://img.fark.net/images/2013/links/apnews-2x.png 2x"  class="retina" alt="(AP News)" title="AP News"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/cool" title="Cool"><span class="ttag topic18">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854414 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854414/apnews.com/video/patient-with-parkinsons-disease-plays-clarinet-during-brain-procedure-at-london-hos">Patient with Parkinson&#39;s disease plays clarinet during brain procedure at London hospital. Which is even more amazing because she had a sax in her hands</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854414 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854414">apnews.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854414_1409" onclick="copyLinkToClipboard('copylink_13854414_1409', 'https://fark.com/13854414 --Fark headline: Patient with Parkinson\&#39;s disease plays clarinet during brain procedure at London hospital. Which is even more amazing because she had a sax in her hands')" onmouseout="showCopyLink('copylink_13854414_1409')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854414/Patient-with-Parkinsons-disease-plays-clarinet-during-brain-procedure-at-London-hospital-Which-is-even-more-amazing-because-she-had-a-sax-in-her-hands" target="_top" class="icon_comment">  <span class="icon_comment_count">30</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854306" data-headline-count="32">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854306 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854306/apnews.com/article/artificial-intelligence-data-centers-poll-climate-change-c9f95aa014254ef454b763cc"><img src="https://img.fark.net/images/2013/links/apnews.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/apnews.png 1x, https://img.fark.net/images/2013/links/apnews-2x.png 2x"  class="retina" alt="(AP News)" title="AP News"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/murica" title="Murica"><span class="ttag topic52">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854306 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854306/apnews.com/article/artificial-intelligence-data-centers-poll-climate-change-c9f95aa014254ef454b763cc">A close look at what Americans think about the impact of AI on climate change shows that it&#39;s really no different at all from how Americans think about pretty much anything else</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854306 "  data-farkdomain="apnews.com" target="_blank" href="https://www.fark.com/goto/13854306">apnews.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854306_4626" onclick="copyLinkToClipboard('copylink_13854306_4626', 'https://fark.com/13854306 --Fark headline: A close look at what Americans think about the impact of AI on climate change shows that it\&#39;s really no different at all from how Americans think about pretty much anything else')" onmouseout="showCopyLink('copylink_13854306_4626')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854306/A-close-look-at-what-Americans-think-about-impact-of-AI-on-climate-change-shows-that-its-really-no-different-at-all-from-how-Americans-think-about-pretty-much-anything-else" target="_top" class="icon_comment">  <span class="icon_comment_count">28</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854144" data-headline-count="33">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854144 "  data-farkdomain="nj.com" target="_blank" href="https://www.fark.com/goto/13854144/www.nj.com/news/2025/10/remember-all-those-drones-in-nj-skies-the-mystery-just-got-weirder.html%3Fut"><img src="https://img.fark.net/images/2013/links/njcom.jpg" width="77" height="27" srcset="https://img.fark.net/images/2013/links/njcom.jpg 1x, https://img.fark.net/images/2013/links/njcom-2x.jpg 2x"  class="retina" alt="(NJ.com)" title="NJ.com"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/followup" title="Followup"><span class="ttag topic26">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854144 "  data-farkdomain="nj.com" target="_blank" href="https://www.fark.com/goto/13854144/www.nj.com/news/2025/10/remember-all-those-drones-in-nj-skies-the-mystery-just-got-weirder.html%3Fut">NJ&#39;s mystery drone story is getting weirder, and Leon is getting larger</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854144 "  data-farkdomain="nj.com" target="_blank" href="https://www.fark.com/goto/13854144">nj.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854144_3394" onclick="copyLinkToClipboard('copylink_13854144_3394', 'https://fark.com/13854144 --Fark headline: NJ\&#39;s mystery drone story is getting weirder, and Leon is getting larger')" onmouseout="showCopyLink('copylink_13854144_3394')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854144/NJs-mystery-drone-story-is-getting-weirder-Leon-is-getting-larger" target="_top" class="icon_comment">  <span class="icon_comment_count">17</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854176" data-headline-count="34">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854176 "  data-farkdomain="thegrimhistorian.substack.com" target="_blank" href="https://www.fark.com/goto/13854176/thegrimhistorian.substack.com/p/from-butt-trumpets-to-farting-clubs%3FtriedRedirect%3Dtrue%26utm_sou"><img src="https://img.fark.net/images/2022/links/substack.png" width="77" height="27" srcset="https://img.fark.net/images/2022/links/substack.png 1x, https://img.fark.net/images/2022/links/substack-2x.png 2x"  class="retina" alt="(Substack)" title="Substack"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/interesting" title="Interesting"><span class="ttag topic02">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854176 "  data-farkdomain="thegrimhistorian.substack.com" target="_blank" href="https://www.fark.com/goto/13854176/thegrimhistorian.substack.com/p/from-butt-trumpets-to-farting-clubs%3FtriedRedirect%3Dtrue%26utm_sou">For those of you seeking intellectual content, here&#39;s the history of fart humour</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854176 "  data-farkdomain="thegrimhistorian.substack.com" target="_blank" href="https://www.fark.com/goto/13854176">thegrimhistorian.substack.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854176_5798" onclick="copyLinkToClipboard('copylink_13854176_5798', 'https://fark.com/13854176 --Fark headline: For those of you seeking intellectual content, here\&#39;s the history of fart humour')" onmouseout="showCopyLink('copylink_13854176_5798')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854176/For-those-of-you-seeking-intellectual-content-heres-history-of-fart-humour" target="_top" class="icon_comment">  <span class="icon_comment_count">33</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854292" data-headline-count="35">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854292 "  data-farkdomain="youtube.com" target="_blank" href="https://www.fark.com/goto/13854292/www.youtube.com/watch%3Fv%3Dce7e8R6fCsY"><img src="https://img.fark.net/images/2020/links/youtube.png" width="77" height="27" srcset="https://img.fark.net/images/2020/links/youtube.png 1x, https://img.fark.net/images/2020/links/youtube-2x.png 2x"  class="retina" alt="(YouTube)" title="YouTube"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/stupid" title="Stupid"><span class="ttag topic11">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854292 "  data-farkdomain="youtube.com" target="_blank" href="https://www.fark.com/goto/13854292/www.youtube.com/watch%3Fv%3Dce7e8R6fCsY">Engineer fails to consider how stupid most drivers are when designing new traffic circle</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854292 "  data-farkdomain="youtube.com" target="_blank" href="https://www.fark.com/goto/13854292">youtube.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854292_9423" onclick="copyLinkToClipboard('copylink_13854292_9423', 'https://fark.com/13854292 --Fark headline: Engineer fails to consider how stupid most drivers are when designing new traffic circle')" onmouseout="showCopyLink('copylink_13854292_9423')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854292/Engineer-fails-to-consider-how-stupid-most-drivers-are-when-designing-new-traffic-circle" target="_top" class="icon_comment">  <span class="icon_comment_count">147</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13851734" data-headline-count="36">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13851734 "  data-farkdomain="upload.wikimedia.org" target="_blank" href="https://www.fark.com/goto/13851734/upload.wikimedia.org/wikipedia/commons/thumb/6/6a/&quot;A_New_Sandow_Pose_(VIII)&quot;,_Eugen_Sandow"><img src="https://img.fark.net/images/2012/links/wikimedia.png" width="77" height="27" srcset="https://img.fark.net/images/2012/links/wikimedia.png 1x, https://img.fark.net/images/2012/links/wikimedia-2x.png 2x"  class="retina" alt="(Wikimedia)" title="Wikimedia"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/photoshop" title="Photoshop"><span class="ttag topic23">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13851734 "  data-farkdomain="upload.wikimedia.org" target="_blank" href="https://www.fark.com/goto/13851734/upload.wikimedia.org/wikipedia/commons/thumb/6/6a/&quot;A_New_Sandow_Pose_(VIII)&quot;,_Eugen_Sandow">Photoshop this Prussian poser</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13851734 "  data-farkdomain="upload.wikimedia.org" target="_blank" href="https://www.fark.com/goto/13851734">upload.wikimedia.org</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13851734_5515" onclick="copyLinkToClipboard('copylink_13851734_5515', 'https://fark.com/13851734 --Fark headline: Photoshop this Prussian poser')" onmouseout="showCopyLink('copylink_13851734_5515')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13851734/Photoshop-this-Prussian-poser" target="_top" class="icon_comment">  <span class="icon_comment_count">12</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854122" data-headline-count="37">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854122 "  data-farkdomain="metro.co.uk" target="_blank" href="https://www.fark.com/goto/13854122/metro.co.uk/2025/10/23/mysterious-underground-complex-dubbed-egypts-area-51-revealed-unearthed-photo"><img src="https://img.fark.net/images/2025/links/metro.png" width="77" height="27" srcset="https://img.fark.net/images/2025/links/metro.png 1x, https://img.fark.net/images/2025/links/metro-2x.png 2x"  class="retina" alt="(Metro)" title="Metro"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/strange" title="Strange"><span class="ttag topic10">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854122 "  data-farkdomain="metro.co.uk" target="_blank" href="https://www.fark.com/goto/13854122/metro.co.uk/2025/10/23/mysterious-underground-complex-dubbed-egypts-area-51-revealed-unearthed-photo">Apparently the US isn&#39;t the only country with an Area 51, Egypt has one just three miles away from the Giza Pyramids and could have been a &#39;gateway to the stars&#39;</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854122 "  data-farkdomain="metro.co.uk" target="_blank" href="https://www.fark.com/goto/13854122">metro.co.uk</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854122_9011" onclick="copyLinkToClipboard('copylink_13854122_9011', 'https://fark.com/13854122 --Fark headline: Apparently the US isn\&#39;t the only country with an Area 51, Egypt has one just three miles away from the Giza Pyramids and could have been a \&#39;gateway to the stars\&#39;')" onmouseout="showCopyLink('copylink_13854122_9011')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854122/Apparently-US-isnt-only-country-with-an-Area-51-Egypt-has-one-just-three-miles-away-from-Giza-Pyramids-could-have-been-a-gateway-to-stars" target="_top" class="icon_comment">  <span class="icon_comment_count">51</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853976" data-headline-count="38">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853976 "  data-farkdomain="wbez.org" target="_blank" href="https://www.fark.com/goto/13853976/www.wbez.org/immigration/2025/10/22/illinois-crack-down-ice-immigration-cars-illegal-license-plates-"><img src="https://img.fark.net/images/2013/links/wbezchicago.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/wbezchicago.png 1x, https://img.fark.net/images/2013/links/wbezchicago-2x.png 2x"  class="retina" alt="(WBEZ Chicago)" title="WBEZ Chicago"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/followup" title="Followup"><span class="ttag topic26">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853976 "  data-farkdomain="wbez.org" target="_blank" href="https://www.fark.com/goto/13853976/www.wbez.org/immigration/2025/10/22/illinois-crack-down-ice-immigration-cars-illegal-license-plates-">After multiple reports, Illinois decides to crack down on ICE cars with illegal license plates. Now there&#39;s a hunt of illegals subby can get behind</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853976 "  data-farkdomain="wbez.org" target="_blank" href="https://www.fark.com/goto/13853976">wbez.org</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853976_9928" onclick="copyLinkToClipboard('copylink_13853976_9928', 'https://fark.com/13853976 --Fark headline: After multiple reports, Illinois decides to crack down on ICE cars with illegal license plates. Now there\&#39;s a hunt of illegals subby can get behind')" onmouseout="showCopyLink('copylink_13853976_9928')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853976/After-multiple-reports-Illinois-decides-to-crack-down-on-ICE-cars-with-illegal-license-plates-Now-theres-a-hunt-of-illegals-subby-can-get-behind" target="_top" class="icon_comment">  <span class="icon_comment_count">62</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854102" data-headline-count="39">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854102 "  data-farkdomain="kyivindependent.com" target="_blank" href="https://www.fark.com/goto/13854102/kyivindependent.com/poland-hopes-ukraine-knocks-out-druzhba-pipeline-sikorski-taunts-hungary/%3Futm_"><img src="https://img.fark.net/images/2022/links/kyivindependent.png" width="77" height="27" srcset="https://img.fark.net/images/2022/links/kyivindependent.png 1x, https://img.fark.net/images/2022/links/kyivindependent-2x.png 2x"  class="retina" alt="(The Kyiv Independent)" title="The Kyiv Independent"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/news" title="News"><span class="ttag topic04">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854102 "  data-farkdomain="kyivindependent.com" target="_blank" href="https://www.fark.com/goto/13854102/kyivindependent.com/poland-hopes-ukraine-knocks-out-druzhba-pipeline-sikorski-taunts-hungary/%3Futm_">Day 1,338 of WW3. Poland trolls Hungary, openly hoping Magyar shuts down the Druzhba pipeline. Ukraine signs deal for more than 100 Gripen warplanes from Sweden, and Cheetolini finally sanctions russia. This is your Thursday Ukraine War thread</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854102 "  data-farkdomain="kyivindependent.com" target="_blank" href="https://www.fark.com/goto/13854102">kyivindependent.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854102_9100" onclick="copyLinkToClipboard('copylink_13854102_9100', 'https://fark.com/13854102 --Fark headline: Day 1,338 of WW3. Poland trolls Hungary, openly hoping Magyar shuts down the Druzhba pipeline. Ukraine signs deal for more than 100 Gripen warplanes from Sweden, and Cheetolini finally sanctions russia. This is your Thursday Ukraine War thread')" onmouseout="showCopyLink('copylink_13854102_9100')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854102/Day-1338-of-WW3-Poland-trolls-Hungary-openly-hoping-Magyar-shuts-down-Druzhba-pipeline-Ukraine-signs-deal-for-more-than-100-Gripen-warplanes-from-Sweden-Cheetolini-finally-sanctions-russia-This-is-your-Thursday-Ukraine-War-thread" target="_top" class="icon_comment">  <span class="icon_comment_count">252</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853906" data-headline-count="40">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853906 "  data-farkdomain="finance.yahoo.com" target="_blank" href="https://www.fark.com/goto/13853906/finance.yahoo.com/news/trump-demands-cattle-ranchers-lower-174255467.html%3Futm_source%3Dfark%26utm_"><img src="https://img.fark.net/images/2014/links/yahoo.png" width="77" height="27" srcset="https://img.fark.net/images/2014/links/yahoo.png 1x, https://img.fark.net/images/2014/links/yahoo-2x.png 2x"  class="retina" alt="(Yahoo)" title="Yahoo"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/ironic" title="Ironic"><span class="ttag topic20">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853906 "  data-farkdomain="finance.yahoo.com" target="_blank" href="https://www.fark.com/goto/13853906/finance.yahoo.com/news/trump-demands-cattle-ranchers-lower-174255467.html%3Futm_source%3Dfark%26utm_">Trump gives ranchers the ol&#39; cattle prod., promises his &#39;big package&#39; to follow. What?</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853906 "  data-farkdomain="finance.yahoo.com" target="_blank" href="https://www.fark.com/goto/13853906">finance.yahoo.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853906_7366" onclick="copyLinkToClipboard('copylink_13853906_7366', 'https://fark.com/13853906 --Fark headline: Trump gives ranchers the ol\&#39; cattle prod., promises his \&#39;big package\&#39; to follow. What?')" onmouseout="showCopyLink('copylink_13853906_7366')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853906/Trump-gives-ranchers-ol-cattle-prod-promises-his-big-package-to-follow-What" target="_top" class="icon_comment">  <span class="icon_comment_count">107</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853962" data-headline-count="41">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853962 "  data-farkdomain="yahoo.com" target="_blank" href="https://www.fark.com/goto/13853962/www.yahoo.com/news/articles/diagnostic-dilemma-toddler-accidently-ate-100000745.html%3Futm_source%3D"><img src="https://img.fark.net/images/2014/links/yahoo.png" width="77" height="27" srcset="https://img.fark.net/images/2014/links/yahoo.png 1x, https://img.fark.net/images/2014/links/yahoo-2x.png 2x"  class="retina" alt="(Yahoo)" title="Yahoo"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/vintage" title="Vintage"><span class="ttag topic56">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853962 "  data-farkdomain="yahoo.com" target="_blank" href="https://www.fark.com/goto/13853962/www.yahoo.com/news/articles/diagnostic-dilemma-toddler-accidently-ate-100000745.html%3Futm_source%3D">I&#39;m sorry, he ate WHAT?</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853962 "  data-farkdomain="yahoo.com" target="_blank" href="https://www.fark.com/goto/13853962">yahoo.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853962_993" onclick="copyLinkToClipboard('copylink_13853962_993', 'https://fark.com/13853962 --Fark headline: I\&#39;m sorry, he ate WHAT?')" onmouseout="showCopyLink('copylink_13853962_993')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853962/Im-sorry-he-ate-WHAT" target="_top" class="icon_comment">  <span class="icon_comment_count">54</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853946" data-headline-count="42">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853946 "  data-farkdomain="ktvo.com" target="_blank" href="https://www.fark.com/goto/13853946/ktvo.com/news/local/teen-uses-social-media-to-drive-business-at-ottumwa-pharmacys-soda-fountain%3Fut"><img src="https://img.fark.net/images/2015/links/ktvo.png" width="77" height="27" srcset="https://img.fark.net/images/2015/links/ktvo.png 1x, https://img.fark.net/images/2015/links/ktvo-2x.png 2x"  class="retina" alt="(KTVO Kirksville)" title="KTVO Kirksville"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/cool" title="Cool"><span class="ttag topic18">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853946 "  data-farkdomain="ktvo.com" target="_blank" href="https://www.fark.com/goto/13853946/ktvo.com/news/local/teen-uses-social-media-to-drive-business-at-ottumwa-pharmacys-soda-fountain%3Fut">Just another jerk on social media</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853946 "  data-farkdomain="ktvo.com" target="_blank" href="https://www.fark.com/goto/13853946">ktvo.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853946_4908" onclick="copyLinkToClipboard('copylink_13853946_4908', 'https://fark.com/13853946 --Fark headline: Just another jerk on social media')" onmouseout="showCopyLink('copylink_13853946_4908')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853946/Just-another-jerk-on-social-media" target="_top" class="icon_comment">  <span class="icon_comment_count">20</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13854030" data-headline-count="43">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13854030 "  data-farkdomain="azfamily.com" target="_blank" href="https://www.fark.com/goto/13854030/www.azfamily.com/2025/10/23/woman-finds-uncle-dead-west-valley-independent-living-facility-days-afte"><img src="https://img.fark.net/images/2013/links/azfamily.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/azfamily.png 1x, https://img.fark.net/images/2013/links/azfamily-2x.png 2x"  class="retina" alt="(AZ Family)" title="AZ Family"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/sad" title="Sad"><span class="ttag topic05">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13854030 "  data-farkdomain="azfamily.com" target="_blank" href="https://www.fark.com/goto/13854030/www.azfamily.com/2025/10/23/woman-finds-uncle-dead-west-valley-independent-living-facility-days-afte">Finding a skeleton in a chair is good fun when it&#39;s a Halloween decoration on a front porch. But it&#39;s just sad when it&#39;s your beloved uncle in an assisted living facility</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13854030 "  data-farkdomain="azfamily.com" target="_blank" href="https://www.fark.com/goto/13854030">azfamily.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13854030_5159" onclick="copyLinkToClipboard('copylink_13854030_5159', 'https://fark.com/13854030 --Fark headline: Finding a skeleton in a chair is good fun when it\&#39;s a Halloween decoration on a front porch. But it\&#39;s just sad when it\&#39;s your beloved uncle in an assisted living facility')" onmouseout="showCopyLink('copylink_13854030_5159')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13854030/Finding-a-skeleton-in-a-chair-is-good-fun-when-its-a-Halloween-decoration-on-a-front-porch-But-its-just-sad-when-its-your-beloved-uncle-in-an-assisted-living-facility" target="_top" class="icon_comment">  <span class="icon_comment_count">38</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853766" data-headline-count="44">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853766 "  data-farkdomain="turnto10.com" target="_blank" href="https://www.fark.com/goto/13853766/turnto10.com/news/local/glocester-man-arrested-police-officers-seize-12000-cocaine-drugs-outstanding"><img src="https://img.fark.net/images/2013/links/nbc10newengland.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/nbc10newengland.png 1x, https://img.fark.net/images/2013/links/nbc10newengland-2x.png 2x"  class="retina" alt="(NBC 10 New England)" title="NBC 10 New England"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/dumbass" title="Dumbass"><span class="ttag topic34">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853766 "  data-farkdomain="turnto10.com" target="_blank" href="https://www.fark.com/goto/13853766/turnto10.com/news/local/glocester-man-arrested-police-officers-seize-12000-cocaine-drugs-outstanding">RI man arrested after police seize $12,000 worth of cocaine. No word from police on how many Rhode Islands that is</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853766 "  data-farkdomain="turnto10.com" target="_blank" href="https://www.fark.com/goto/13853766">turnto10.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853766_7033" onclick="copyLinkToClipboard('copylink_13853766_7033', 'https://fark.com/13853766 --Fark headline: RI man arrested after police seize $12,000 worth of cocaine. No word from police on how many Rhode Islands that is')" onmouseout="showCopyLink('copylink_13853766_7033')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853766/RI-man-arrested-after-police-seize-$12000-worth-of-cocaine-No-word-from-police-on-how-many-Rhode-Islands-that-is" target="_top" class="icon_comment">  <span class="icon_comment_count">23</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853948" data-headline-count="45">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853948 "  data-farkdomain="independent.co.uk" target="_blank" href="https://www.fark.com/goto/13853948/www.independent.co.uk/bulletin/news/dusky-shark-attack-israel-diver-feeding-ban-b2850223.html%3Futm_"><img src="https://img.fark.net/images/2023/links/independent.png" width="77" height="27" srcset="https://img.fark.net/images/2023/links/independent.png 1x, https://img.fark.net/images/2023/links/independent-2x.png 2x"  class="retina" alt="(Independent)" title="Independent"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/scary" title="Scary"><span class="ttag topic19">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853948 "  data-farkdomain="independent.co.uk" target="_blank" href="https://www.fark.com/goto/13853948/www.independent.co.uk/bulletin/news/dusky-shark-attack-israel-diver-feeding-ban-b2850223.html%3Futm_">Shark species formerly believed to be harmless to humans was just biding its time</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853948 "  data-farkdomain="independent.co.uk" target="_blank" href="https://www.fark.com/goto/13853948">independent.co.uk</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853948_1129" onclick="copyLinkToClipboard('copylink_13853948_1129', 'https://fark.com/13853948 --Fark headline: Shark species formerly believed to be harmless to humans was just biding its time')" onmouseout="showCopyLink('copylink_13853948_1129')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853948/Shark-species-formerly-believed-to-be-harmless-to-humans-was-just-biding-its-time" target="_top" class="icon_comment">  <span class="icon_comment_count">37</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13853720" data-headline-count="46">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13853720 "  data-farkdomain="cbsnews.com" target="_blank" href="https://www.fark.com/goto/13853720/www.cbsnews.com/boston/news/massachusetts-boat-fire-rescue-naushon-island/%3Futm_source%3Dfark%26utm"><img src="https://img.fark.net/images/2013/links/cbsnews.png" width="77" height="27" srcset="https://img.fark.net/images/2013/links/cbsnews.png 1x, https://img.fark.net/images/2013/links/cbsnews-2x.png 2x"  class="retina" alt="(CBS News)" title="CBS News"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/scary" title="Scary"><span class="ttag topic19">&nbsp;</span></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13853720 "  data-farkdomain="cbsnews.com" target="_blank" href="https://www.fark.com/goto/13853720/www.cbsnews.com/boston/news/massachusetts-boat-fire-rescue-naushon-island/%3Futm_source%3Dfark%26utm">A boat is a hole in the water you throw money into, until it catches fire and you have to swim, severely burned, to an island where you spend two nights before being rescued by helicopter</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13853720 "  data-farkdomain="cbsnews.com" target="_blank" href="https://www.fark.com/goto/13853720">cbsnews.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13853720_8372" onclick="copyLinkToClipboard('copylink_13853720_8372', 'https://fark.com/13853720 --Fark headline: A boat is a hole in the water you throw money into, until it catches fire and you have to swim, severely burned, to an island where you spend two nights before being rescued by helicopter')" onmouseout="showCopyLink('copylink_13853720_8372')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13853720/A-boat-is-a-hole-in-water-you-throw-money-into-until-it-catches-fire-you-have-to-swim-severely-burned-to-an-island-where-you-spend-two-nights-before-being-rescued-by-helicopter" target="_top" class="icon_comment">  <span class="icon_comment_count">20</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr><tr class="headlineRow id13849848" data-headline-count="47">

     <td class="headlineSourceImage">   <a rel="nofollow" class="outbound_link id13849848 "  data-farkdomain="farktography.com" target="_blank" href="https://www.fark.com/goto/13849848/www.farktography.com/forums/topic/10-29-25-autumn-7/%3Futm_source%3Dfark%26utm_medium%3Dwebsite%26ut"><img src="https://img.fark.net/images/2008/links/farktography.gif" width="77" height="27" class="retina" alt="(Farktography)" title="Farktography"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

    <td class="headlineTopic">
          <a target="_top" href="https://www.fark.com/topic/farktography" title="Farktography"><img src="https://img.fark.net/images/2013/topics/farktography.gif" width="54" height="11" srcset="https://img.fark.net/images/2013/topics/farktography.gif 1x, https://img.fark.net/images/2013/topics/farktography-2x.gif 2x"  class="retina" alt="Farktography" title="Farktography"></a>         <div class="hlSpacer">&nbsp;</div>  </td>

     <td class="headlineText">  <span class="headline"> <a rel="nofollow" class="outbound_link id13849848 "  data-farkdomain="farktography.com" target="_blank" href="https://www.fark.com/goto/13849848/www.farktography.com/forums/topic/10-29-25-autumn-7/%3Futm_source%3Dfark%26utm_medium%3Dwebsite%26ut">Theme of Farktography Contest No. 1068: &quot;A Point in Time&quot;. Details and rules in first post. LGT next week&#39;s theme</a> </span>
                <div class="hlSpacer URLHover">
                    source: <a rel="nofollow" class="outbound_link id13849848 "  data-farkdomain="farktography.com" target="_blank" href="https://www.fark.com/goto/13849848">farktography.com</a> &nbsp;&nbsp;|&nbsp;&nbsp; share:  <a href="javascript:void(0);" id="copylink_13849848_6193" onclick="copyLinkToClipboard('copylink_13849848_6193', 'https://fark.com/13849848 --Fark headline: Theme of Farktography Contest No. 1068: &quot;A Point in Time&quot;. Details and rules in first post. LGT next week\&#39;s theme')" onmouseout="showCopyLink('copylink_13849848_6193')">Copy Link</a>  </div>   </td>

    <td class="headlineComments">    <div class="icon_comment_container">
                 <a href="https://www.fark.com/comments/13849848/Theme-of-Farktography-Contest-No-1068-A-Point-in-Time-Details-rules-in-first-post-LGT-next-weeks-theme" target="_top" class="icon_comment">  <span class="icon_comment_count">28</span>  </a>    </div>          <div class="hlSpacer">&nbsp;</div>  </td>   </tr> </tbody>
        </table>   </td>
    </tr>
</table>

<script>
    var total_headlines_to_track = 0;
     fark.headlines.headlineCount = 47;

    //setTimeout(function() { process_extra_tracking_logic(); }, 2000);
</script>  <a id="headline_ajax_load_older">Load older headlines</a>    <div id="native_ad3"></div> <div class="comlinkcount">These are only a small percentage of links submitted. Join <a href="https://www.fark.com/farq/about#What_is_TotalFark">TotalFark</a> to see them all!</div><p class="linkArchives"><a href="https://www.fark.com/archives/">Link archives &raquo;</a></p>
    <!-- BOTTOM start -->
</div> <!-- end #newsContainer -->
        </td>
        <td id="rightCol">
            <div class="rightColContent">   <div class="ad_container intelli1">  <div id="intelli-1"><!-- begin ad tag (intellidisplay) --></div>   <div class="reportAdBlock" style="display:none;" id="intelli-1-reportLink"><a href="https://www.fark.com/farkback/" onclick="reportAd('intelli-1'); return false;">Report</a></div>   </div>  <div class="sidebar_callout_container tfark_callout">
                    <p style="font-size:13px;">If you like these links, you'll love</p>
                    <!--<img src="https://img.fark.net/images/2017/site/totalfark_logo_2017.png" srcset="https://img.fark.net/images/2017/site/totalfark_logo_2017.png 1x, https://img.fark.net/images/2017/site/totalfark_logo_2017-2x.png 2x" class="retina" alt="TotalFark">-->
                    <img src="https://img.fark.net/images/2017/site/totalfark_logo_2017.png" srcset="https://img.fark.net/images/2017/site/totalfark_logo_2017.png 1x, https://img.fark.net/images/2017/site/totalfark_logo_2017-2x.png 2x" class="retina" alt="TotalFark">
                    <p class="tf-callout-text">More Farking, less working</p>

                    <a href="https://www.fark.com/farq/about/#What_is_TotalFark">learn more</a> | <a href="/totalfarksignup">sign up</a>
                </div>      <div class="top_right_container"> <div class="ad_container rightTop">  <div id="rightAd300x250"><!-- begin ad tag (billboard_top) -->
            <script>  googletag.cmd.push(function() { googletag.display('rightAd300x250'); });  </script></div>   <div class="reportAdBlock"  id="rightAd300x250-reportLink"><a href="https://www.fark.com/farkback/" onclick="reportAd('rightAd300x250'); return false;">Report</a></div>   </div> </div>   <div id="supportfark">
            <hr>
            <a href="https://www.fark.com/supportfark">Support Fark</a>
            <hr>
        </div>

        <div class="sidebar_callout_container newsletter_callout">
            <p>Sign up for the Fark NotNewsletter!</p>
              <form name="newsletter_signup" action="https://www.fark.com/newslettersignup" method="post" class="ajaxsubmit">
                <input type="text" name="nnl_e" placeholder="you@you.com">
                <input type="hidden" name="submitbutton" value="Sign Me Up!"> <input type="hidden" name="e0$Fc5k_$C8ChLnN3YsnFEuYtkevIOWwvOIpz" value="FcBk_--vn01Pv0Ux67lO0ywv65FAmyQ2v-8qOpaqVAnLJFfu7wz4R2Jt52TBrCX_zxmHR73tZqvihrWHk-sjK82IesHHxL753R0">
 <input type="submit" class="gradientbutton" value="Go&raquo;">
            </form>
            <a href="https://www.fark.com/farq/services/#What_is_the_Fark_NotNewsletter" style="display: inline-block; margin-top: 5px; ">learn more</a>
        </div>  <hr>
        <div id="hotw"><a href="https://www.fark.com/topic/hotm">Headlines of the Month</a><br>
                       <a href="https://www.fark.com/blog/NotNewsletterMonkey">Fark NotNewsletter</a>
        </div>

        <hr>
        <ul class="sidebarLinks">  <li><a target="_top" href="https://www.fark.com/totalfarksignup">TotalFark signup</a></li>   <li><a target="_top" href="https://www.fark.com/barefarksignup">BareFark signup</a></li>  <li><a target="_top" href="https://www.fark.com/farkunits">Purchase FarkUnits</a></li>
            <li><a target="_top" href="https://www.fark.com/badges">Purchase Badges</a></li>
        </ul>

        <hr>

        <ul class="sidebarLinks">
            <li><a href="https://www.fark.com/top/links/">Top Links</a></li>
            <li><a href="https://www.fark.com/top/comments/">Top Comments</a></li>
            <li><a href="https://www.fark.com/top/submitters/">Top Submitters</a></li>
            <li><a href="https://www.fark.com/top/comments/smart/">Top Smart Comments</a></li>
            <li><a href="https://www.fark.com/top/source-topic/">Top Sources/Topics</a></li>
            <li><a href="https://www.fark.com/top/comments/funny/">Top Funny Comments</a></li>
            <li><a href="https://www.fark.com/publicity/">Press/Publicity</a></li>
        </ul>

        <hr>

          <div class="ad_container right">  <div id="rightAd300x250Middle"><!-- begin ad tag (billboard_mid) -->
            <script>  googletag.cmd.push(function() { googletag.display('rightAd300x250Middle'); });  </script></div>   <div class="reportAdBlock"  id="rightAd300x250Middle-reportLink"><a href="https://www.fark.com/farkback/" onclick="reportAd('rightAd300x250Middle'); return false;">Report</a></div>   </div>  <ul class="sidebarLinks">
            <li><a href="https://www.fark.com/combined/">All Latest</a></li>
            <li><a href="https://www.fark.com/comments/1">Fark Forum</a></li>  <li><a href="https://www.fark.com/linkvote/">Link Voting</a></li>
            <li><a href="https://www.fark.com/comments/2">Sports Forum</a></li>

            <li><a href="https://www.fark.com/blog/DisseminationMonkey">Fark Blogs</a></li>
            <li><a href="https://www.fark.com/comments/4">Fandom Forum</a></li>

            <li><a target="_blank" href="https://www.amazon.com/Its-Not-News-Fark-Media/dp/1592402917/sr=8-1/qid=1168639219/ref=pd_bbs_sr_1/102-1500276-2229705?ie=UTF8&amp;s=books&amp;tag=farkcom-20">Fark Book</a></li>
            <li><a href="https://www.fark.com/comments/3">Entertainment Forum</a></li>

            <li><a href="https://www.fark.com/quiz">Fark Quiz</a></li>
            <li><a href="https://www.fark.com/comments/5">Politics Forum</a></li>

            <li><a href="https://www.fark.com/farkparty/">Fark Parties</a></li>
            <li><a href="https://www.fark.com/comments/550396">Fark Party Forum</a></li>

            <li><a href="https://www.fark.com/psbrowser">PS/Photo Browser</a></li>
            <li><a href="https://www.fark.com/comments/6">Photoshop Forum</a></li>

            <li>&nbsp;</li>
            <li><a href="https://www.fark.com/comments/7">Farktography Forum</a></li>

            <li>&nbsp;</li>
            <li><a href="https://www.fark.com/comments/8">Discussion/TF Live Forum</a></li>

        </ul>
        <hr>


        <!-- <br> -->
           <div class="ad_container right">  <div id="rightAd300x250Lower"><!-- begin ad tag (billboard_bot) -->
            <script>  googletag.cmd.push(function() { googletag.display('rightAd300x250Lower'); });  </script></div>   <div class="reportAdBlock"  id="rightAd300x250Lower-reportLink"><a href="https://www.fark.com/farkback/" onclick="reportAd('rightAd300x250Lower'); return false;">Report</a></div>   </div>       <div id="rightBottomWidget">
              <div id="rightBottomWidgetVids">
                      <div class="ad_container">  <div id="stickyAd300x250"><!-- begin ad tag (billboard_sticky) -->
            <script>  googletag.cmd.push(function() { googletag.display('stickyAd300x250'); });  </script></div>    <div class="closeAdBlock" style="display:none;" id="stickyAd300x250-closeAdLink"> <a href="javascript:void();" onclick="close_sticky_vids(); return false;">Close Ad</a></div>  <div class="reportAdBlock"  id="stickyAd300x250-reportLink"><a href="https://www.fark.com/farkback/" onclick="reportAd('stickyAd300x250'); return false;">Report</a></div>   </div> </div>  <div id="rightBottomWidgetLinks"> <div id="widgetTopHeadlinescontainer">
    <div id="widgetTopHeadlinesheader">
        <div id="widgetTopHeadlinesfark_logo">Fark.com</div>
        <div id="widgetTopHeadlinesheadertitles" class="headertitles">
            Top Commented
        </div>
    </div>

    <div class="widgetOptions">
        <a id="widgetSelected" onclick="toggleDropdown()">
            <span id="widgetHeader">Top Commented</span> <span class="arrow">&#x25BC;</span>
        </a>
        <ul id="widgetOptionsDropdown"> 
            <li><a onclick="changeWidgetLink('topcommented'); return false;" id="widgetDropdown-topcommented">Top Commented</a></li>
            <li><a onclick="changeWidgetLink('topclicked'); return false;" id="widgetDropdown-topclicked">Top Clicked</a></li>
            <li><a onclick="changeWidgetLink('topvoted'); return false;" id="widgetDropdown-topvoted">Top Voted</a></li>
            <li><a onclick="changeWidgetLink('mycommented'); return false;" id="widgetDropdown-mycommented">My Recent Commented</a></li>
            <li><a onclick="changeWidgetLink('mytagged'); return false;" id="widgetDropdown-mytagged">Recent Mentions</a></li>
        </ul>
    </div>

    <div id="widgetTopHeadlineslinkbody">
        <div id="widgetContent">
            <div style="margin: 20px 10px;">Javascript is required to view headlines in widget.</div>
            <script>
            $('#widgetContent').html('<p style="margin-left: 15px;">Loading headlines...</p>').load('/widget?ajax=1', function() {
                refreshIconAnimation(false);
            });
            </script>
        </div>
    </div>
</div>
<div id="widgetTopHeadlinesrefreshListing">
    <a onclick="refreshIconAnimation(true); changeWidgetLink(openWidget);"><svg height="32" id="refresh" viewBox="0 0 32 32" width="32" xmlns="http://www.w3.org/2000/svg"><path d=" M16 2 A14 14 0 0 0 2 16 A14 14 0 0 0 16 30 A14 14 0 0 0 26 26 L 23.25 23 A10 10 0 0 1 16 26 A10 10 0 0 1 6 16 A10 10 0 0 1 16 6 A10 10 0 0 1 23.25 9 L19 13 L30 13 L30 2 L26 6 A14 14 0 0 0 16 2 "></path></svg></a>
</div>
<script>
    var stickyWidget = 'rbw';
    function toggleDropdown() {
        var dropdown = document.getElementById('widgetOptionsDropdown');
        var is_view = (dropdown.style.display == 'block') ? true : false;
        if (is_view) {
            dropdown.style.display = 'none';
        } else {
            dropdown.style.display = 'block';
        }
    }

    function refreshIconAnimation(doit) {
        if (doit) {
            document.getElementById('widgetTopHeadlinesrefreshListing').classList.add('active');
        } else {
            document.getElementById('widgetTopHeadlinesrefreshListing').classList.remove('active');
        }
    }

    var openWidget;
    function changeWidgetLink(value, skipRedirect) {
        $('#widgetOptionsDropdown a').removeClass('active_widget');
        $('#widgetDropdown-'+value).addClass('active_widget');
        openWidget = value;
        if (typeof skipRedirect !==  undefined && skipRedirect != true) { 
            refreshIconAnimation(true);
        }
        var headertitle = document.getElementById('widgetHeader');
            headertext = '';
        switch (value) {
            case 'topcommented':
                headertext = 'Top Commented';
                break;
            case 'topclicked':
                headertext = 'Top Clicked';
                break;
            case 'topvoted':
                headertext = 'Top Voted';
                break;
            case 'mycommented':
                headertext = 'My Recent Commented';
                break;
            case 'mytagged':
                headertext = 'Recent Mentions';
                break;
        }
        headertitle.innerHTML = headertext;
        // if (typeof skipRedirect !==  undefined && skipRedirect != true) { document.getElementById('sidebarWidgetIframe').src = '/widget/'+value; }
        if (typeof skipRedirect !==  undefined && skipRedirect != true) { 
            document.getElementById('widgetOptionsDropdown').style.display = 'none';
            $('#widgetContent').text('');
            $('#widgetContent').load('/widget/'+value+'?ajax=1', function() {
                setTimeout(function() {
                    refreshIconAnimation(false);
                }, 500);
            });
        }
    }
</script> </div>
        </div>  </div>
        </td>
        </tr>
        <tr>
        <td colspan="2">
<script>
/*
var loadNewer = new Vue({
  el: '#load_newer_container',
  data: {
    newer: 0,
    count: 25,
    getCount: function() {
        return (this.newer > this.count ) ? this.count : this.newer
    },
    isLoading: false,
    showLoadNewer: true,
    linkText: fark.ajax.headlineAjaxCheckNewer,
    getText: function () {
        this.showLoadNewer = true;
        if ( this.newer == 0 && this.getCount() == 0 ) {
            if ( fark.page.isDesktop ) {
                // this.showLoadNewer = false;
            }
            return fark.ajax.headlineAjaxCheckNewer;
        } else if ( (this.newer < this.count) || this.newer >= 1000 ) {
            var return_msg = "Load "+this.newer+" newer headlines";
            if ( this.isLoading ) {
                return_msg = return_msg.replace('Load', 'Loading');
            }
            return return_msg;
        } else {
            var return_msg = fark.ajax.headlineAjaxLoadNewer.replace( "XX", this.getCount() );
            return_msg = return_msg.replace( "YY", this.newer );
            if ( this.isLoading ) {
                return_msg = return_msg.replace('Load', 'Loading');
            }
            return return_msg;
        }
    }
  }
});
*/
</script>

 <ol id="joyRideTipContent">
    <li data-class="headlineRow" data-text="Next" class="walkthrough_headline">
        <!--<h2>Stop #1</h2>-->
        <p>Links are submitted by members of the Fark community.</p>
    </li>
    <li data-class="headlineText" data-button="Next" data-options="tipLocation:top;tipAnimation:fade" class="walkthrough_subject">
        <!--<h2>Stop #2</h2>-->
        <p>When community members submit a link, they also write a custom headline for the story.</p>
    </li>
    <li data-class="headlineComments" data-button="Next" data-options="tipLocation:left" class="walkthrough_comments">
        <!--<h2>Stop #3</h2>-->
        <p>Other Farkers comment on the links. This is the number of comments. Click here to read them.</p>
    </li>
    <li data-id="loginLinks" data-button="Next" data-options="tipLocation:top;nubPosition:top-right" class="walkthrough_login">
        <!--<h2>Stop #4</h2>-->
        <p>You need to create an account to submit links or post comments.</p>
    </li>
    <li data-class="submitLink" data-button="Done" data-options="tipLocation:left" class="walkthrough_submit">
        <!--<h2>Stop #5</h2>-->
        <p>Click here to submit a link.</p>
    </li>
</ol>
<script>
    function run_walkthrough(trackInfo) {
        $('#joyRideTipContent').joyride({
            autoStart : true,
            modal : true,
            expose: false
        });
        // console.log("Tracking Walkthrough Click: "+trackInfo);
        gtag('event', 'How to Fark Walkthrough', {
            'send_to': 'G-2CGLGL25G6',
            'event_label': trackInfo
        });
    }
    // check if the get params contain "walkthrough" and if so
    // run the walkthrough automatically
    // we do this to auto run the walkthrough when users aren't on headline pages
    var getParams = window.location.search.replace("?", "");
    if (getParams.indexOf("walkthrough") > -1) { run_walkthrough(); }
</script>
 <div id="footer">  <!-- SellWyld ad unit -->
        <script src="//widget.sellwild.com/fark/fark-fark.js"></script>
        <div id="sellwyld" style="height: 670px; width: 100%">
        <sellwild-widget></sellwild-widget>
        </div>
        <!-- End SellWyld ad unit -->   <p class="alsoOnFark">Also on Fark</p>
        <script>
            function send_ga_events(event_category, event_name, event_label) {
                gtag('event', event_category, {
                    'send_to': 'G-2CGLGL25G6',
                    'page_name': event_label,
                    'event_label': event_name
                });
            }
        </script>
        <table id="alsoOnFarkTable">
            <tbody>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Main -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/">Main</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13855108" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Main');">Good news: all the free Narcan put in cabinets at subway stations to combat overdoses was taken. Bad news: no evidence any of it was used to combat overdoses in the subway stations</a> ( <a rel="nofollow" class="outbound_link id13855108 "  data-farkdomain="wbur.org" target="_blank" href="https://www.fark.com/goto/13855108">wbur.org</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13855108/Good-news-all-free-Narcan-put-in-cabinets-at-subway-stations-to-combat-overdoses-was-taken-Bad-news-no-evidence-any-of-it-was-used-to-combat-overdoses-in-subway-stations" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Main');">(6 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Discussion -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/discussion/">Discussion</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13853808" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Discussion');">Thursday Night Football has the Minnesota Vikings and the Los Angeles Chargers right in Inglewood. Skol Vikings or Super Chargers? Kickoff is at 8:15 PM ET on Prime Video</a> ( <a rel="nofollow" class="outbound_link id13853808 "  data-farkdomain="espn.com" target="_blank" href="https://www.fark.com/goto/13853808">espn.com</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13853808/Thursday-Night-Football-has-Minnesota-Vikings-the-Los-Angeles-Chargers-right-in-Inglewood-Skol-Vikings-Super-Chargers-Kickoff-is-at-815-PM-ET-on-Prime-Video" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Discussion');">(289 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Sports -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/sports/">Sports</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13854518" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Sports');">Just in case you wanted to know, the current status of ping pong in each of the NFL teams&#39; locker rooms</a> ( <a rel="nofollow" class="outbound_link id13854518 "  data-farkdomain="awfulannouncing.com" target="_blank" href="https://www.fark.com/goto/13854518">awfulannouncing.com</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13854518/Just-in-case-you-wanted-to-know-current-status-of-ping-pong-in-each-of-NFL-teams-locker-rooms" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Sports');">(1 comment)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Business -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/business/">Business</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13855140" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Business');">Breaking: Target</a> ( <a rel="nofollow" class="outbound_link id13855140 "  data-farkdomain="kstp.com" target="_blank" href="https://www.fark.com/goto/13855140">kstp.com</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13855140/Breaking-Target" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Business');">(28 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is STEM -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/stem/">STEM</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13854162" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'STEM');">Tiny fossil bone helps unlock history of the bowerbird, your mom&#39;s family tree</a> ( <a rel="nofollow" class="outbound_link id13854162 "  data-farkdomain="phys.org" target="_blank" href="https://www.fark.com/goto/13854162">phys.org</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13854162/Tiny-fossil-bone-helps-unlock-history-of-bowerbird-your-moms-family-tree" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'STEM');">(0 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Entertainment -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/entertainment/">Entertainment</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13855002" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Entertainment');">Lying liar told everyone he &quot;wasn&#39;t the werewolf&quot; when he absolutely was the werewolf. His girlfriend of four years, who he met on the set of &quot;The Amazing Were-Wolf,&quot; snapped back. Snapped. Back</a> ( <a rel="nofollow" class="outbound_link id13855002 "  data-farkdomain="ew.com" target="_blank" href="https://www.fark.com/goto/13855002">ew.com</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13855002/Lying-liar-told-everyone-he-wasnt-werewolf-when-he-absolutely-was-werewolf-His-girlfriend-of-four-years-who-he-met-on-set-of-The-Amazing-Were-Wolf-snapped-back-Snapped-Back" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Entertainment');">(3 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Fandom -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/fandom/">Fandom</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13855024" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Fandom');">Using Counter-Strike skins as an investment vehicle? We have some very bad news for you. Also what the hell</a> ( <a rel="nofollow" class="outbound_link id13855024 "  data-farkdomain="thegamer.com" target="_blank" href="https://www.fark.com/goto/13855024">thegamer.com</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13855024/Using-Counter-Strike-skins-as-an-investment-vehicle-We-have-some-very-bad-news-for-you-Also-what-hell" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Fandom');">(92 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is D'awww -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/dawww/">D'awww</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13855028" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'D\'awww');">&quot;She&#39;s such a gentle cat who has endured such hardship. It broke my heart when I first saw her. I&#39;m so happy that I can give her a new start&quot;</a> ( <a rel="nofollow" class="outbound_link id13855028 "  data-farkdomain="goodnewsnetwork.org" target="_blank" href="https://www.fark.com/goto/13855028">goodnewsnetwork.org</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13855028/Shes-such-a-gentle-cat-who-has-endured-such-hardship-It-broke-my-heart-when-I-first-saw-her-Im-so-happy-that-I-can-give-her-a-new-start" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'D\'awww');">(1 comment)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Food -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/food/">Food</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13854880" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Food');">Taco bell silences anti-American food critics world-wide by releasing a Mountain Dew Baja Blast creme pie</a> ( <a rel="nofollow" class="outbound_link id13854880 "  data-farkdomain="tasteofcountry.com" target="_blank" href="https://www.fark.com/goto/13854880">tasteofcountry.com</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13854880/Taco-bell-silences-anti-American-food-critics-world-wide-by-releasing-a-Mountain-Dew-Baja-Blast-creme-pie" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Food');">(17 comments)</a></td>
                    </tr>      <!-- MEG DEBUG after creating the tab with page.new: tab display name is Politics -->
                    <tr>
                        <td class="alsoOnFarkLabel"><a href="https://www.fark.com/politics/">Politics</a></td>
                         <td><a target="_blank" href="https://www.fark.com/goto/13854700" rel="nofollow" onClick="send_ga_events('Also on Fark Links', 'Outbound Click', 'Politics');">No charges filed for non-crime of projecting picture of two best friends onto a wall</a> ( <a rel="nofollow" class="outbound_link id13854700 "  data-farkdomain="bbc.co.uk" target="_blank" href="https://www.fark.com/goto/13854700">bbc.co.uk</a> ) &raquo;&nbsp;<a href="https://www.fark.com/comments/13854700/No-charges-filed-for-non-crime-of-projecting-picture-of-two-best-friends-onto-a-wall" target="_top" onClick="send_ga_events('Also on Fark Links', 'Internal Click', 'Politics');">(3 comments)</a></td>
                    </tr>  </tbody>
        </table>   <ul id="footerFarkLinks">
        <li>Fark :: <a href="https://www.fark.com/">Main</a> | <a href="https://www.fark.com/discussion/">Discussion</a> | <a href="https://www.fark.com/sports/">Sports</a> | <a href="https://www.fark.com/business/">Business</a> | <a href="https://www.fark.com/stem/">STEM</a> | <a href="https://www.fark.com/entertainment/">Entertainment</a> | <a href="https://www.fark.com/fandom/">Fandom</a> | <a href="https://www.fark.com/dawww/">D'awww</a> | <a href="https://www.fark.com/food/">Food</a> | <a href="https://www.fark.com/politics/">Politics</a></li>
        <li>Total Fark :: <a href="https://total.fark.com/">TotalFark</a> | <a href="https://total.fark.com/live/">TF Live</a> | <a href="https://total.fark.com/advice/">TF Advice</a> | <a href="https://total.fark.com/tfdiscussion/">TF Discussion</a> | <a href="https://total.fark.com/commented/">Commented</a> | <a href="https://total.fark.com/linkvote/">Top Voted</a> | <a href="https://total.fark.com/greenlit/">Greenlit</a></li>
        <li>FArQ :: <a href="https://www.fark.com/farq/about#What_is_Fark" target="_blank">About Us</a> | <a href="https://www.fark.com/farq/faq#Quick_Answers" target="_blank">Quick Answers</a> | <a href="https://www.fark.com/farq/posting#Posting_Rules" target="_blank">Posting Rules</a> | <a href="https://www.fark.com/farq/farkisms#Farkisms" target="_blank">Farkisms</a></li>
        <li>Contests :: <a href="https://www.fark.com/topic/photoshop">Photoshop</a> | <a href="https://www.fark.com/topic/farktography">Farktography</a> | <a href="https://www.fark.com/topic/caption">Caption</a></li>
        <li>Buy Fark :: <a href="https://www.amazon.com/Its-Not-News-Fark-Media/dp/1592402917/sr=8-1/qid=1168639219/ref=pd_bbs_sr_1/102-1500276-2229705?ie=UTF8&amp;s=books&amp;tag=farkcom-20">Fark Book</a> | <a href="https://www.fark.com/shop">Fark Store</a></li>
    </ul>
    <p class="submitLinkcontainer"><a href="https://www.fark.com/submit/" class="submitLink">Submit a Link &raquo;</a></p>
    <p id="copyrightInfo">
        Copyright &copy; 1999 - 2025 Fark, Inc | Last updated: Oct 24 2025 02:50:06<br>
        <a href="https://www.fark.com/farkback" target="_blank">Contact Us via Farkback</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a href="https://www.fark.com/farkback/error" target="_blank">Report a bug/error msg</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a href="https://www.fark.com/farq/legal" target="_blank">Terms of service/legal/privacy policy</a>&nbsp;&nbsp;|&nbsp;&nbsp;<a href="javascript:void(0)" onclick="__uspapi('displayUspUi');">Do Not Sell or Share My Personal Information</a><br>
<script>
  document.write('<img width="4" height="1" alt="" src="https://www.fark.com/ll?l=' + farkfp() + '">');
</script>
<noscript>
  <img width="4" height="1" alt="" src="https://www.fark.com/ll">
</noscript>  </p>

</div>  </td>
</tr>
</table> <!-- newLayoutTable -->
</div> <!-- container -->
<script>
    var is_tfark = (typeof fark.page.ajaxTabGroup != "undefined" && fark.page.ajaxTabGroup == "TotalFark") ? true : false;
</script>

<script>
     $(function() {
        process_lazy_load();
    });
</script>  <noscript>
<img src="https://img.fark.net/imagesnoc/trans.gif?usertype=Lurker" width="16" height="1" alt="">
</noscript>   <script src="/js/plugins/footer-ad.js?adx"></script>       <br><br><br>  <div id="videoad" style="width: 600px !important; line-height: 0; margin-top: 5px; margin-bottom: 12px;">
        <script>
            googletag.cmd.push(function() {
                window.fark.globals.videoAdSlot = googletag.defineOutOfPageSlot(
                    '/1055466/EXCO_Videoplayer_Desktop_out-of-page',
                    'videoad'
                ).addService(googletag.pubads());
                // Register the div
                googletag.display('videoad');

                googletag.pubads().refresh([window.fark.globals.videoAdSlot]);

            });

        </script>
    </div>
    <br><br>
      <br><br>

  <div id="modal">
        <a href="#" onclick="Custombox.modal.close(); return false;" class="modal_close">X</a>

        <div class="modal_header">
            <span class="modal_header_title"></span>
        </div>
        <div class="modal_content"></div>
    </div>
    <script>
        // Instantiate new modal
        fark.modal = new Custombox.modal({
            content: {
                effect: 'fadein',
                target: '#modal',
                onClose: function() {
                    // clear classes when closing
                    document.getElementById("modal").className = '';
                }
            }
        });

        function processGTEventListener(event) {
            // process any googletag stuff we need for specific ads
            if (event.slot.getSlotElementId() == "stickyAd300x250" && event.advertiserId === 4920996698) {
                // right sticky video ad
                document.querySelector("#stickyAd300x250 iframe").setAttribute("height",175);
            }
        }

        

    </script>


<!-- CARBON TAG -->
<script>
!function(a,l,b,c,k,s,t,g,A){a.CustomerConnectAnalytics=k,a[k]=a[k]||function(){
  (a[k].q=a[k].q||[]).push(arguments)},g=l.createElement(b),A=l.getElementsByTagName(b)[0],
  g.type="text/javascript",g.async=!0,g.src=c+"?id="+s+"&parentId="+t,A.parentNode.insertBefore(g,A)
}(window,document,"script","//carbon-cdn.ccgateway.net/script","cca",window.location.hostname,"53fe1d4767");
</script>
<!-- END CARBON TAG -->  <script>
        googletag.cmd.push(function() {
            googletag.pubads().addEventListener('slotOnload', function(event) {
                fark.sl = true;
                var adContainer = $("#"+event.slot.getSlotElementId());

                if (!adContainer.parent().is('body')) {
                    adContainer.parent().addClass('advis');
                }
                if (event.slot.getSlotElementId() == "stickyAd300x250") {
                    // turn this back on if we switch back to the X close from the "Close Ad" link text
                    // which we can do if we stop allowing the 336x280 size and only allow 300x250
                    // document.getElementById("closeVid").style.display = 'block';
                    document.getElementById("stickyAd300x250-closeAdLink").style.display = 'block';
                }
            });
        });

        googletag.cmd.push(function() {
            googletag.pubads().setTargeting("io_vp", fark.page.io_vp);
        });

        var as = [];
        fark.page.adSlots.forEach(slot => {
             if (slot.id != 'intelli-1') {
                as.push(document.getElementById(slot.id));
            }
        });

        // push this on the googletag.cmd queue so that fark.globals.adUnitsDict is populated before we get here
        googletag.cmd.push(function() {
            as.forEach((slot) => {
                if (slot) {
                    observer.observe(slot);
                    // slot.style.border = '1px solid red';
                }
            })
        });

    </script>

    <div id="wunderkind">
        <script>
          googletag.cmd.push(function() {
              googletag.display('wunderkind');
              googletag.pubads().refresh([fark.globals.wunderkindAdSlot]);
          });
        </script>
    </div>  <script>
    farkDebug.log(0);
      </script>

<script>(function(){function c(){var b=a.contentDocument||a.contentWindow.document;if(b){var d=b.createElement('script');d.innerHTML="window.__CF$cv$params={r:'99378c502c342700',t:'MTc2MTI4ODcxMQ=='};var a=document.createElement('script');a.src='/cdn-cgi/challenge-platform/scripts/jsd/main.js';document.getElementsByTagName('head')[0].appendChild(a);";b.getElementsByTagName('head')[0].appendChild(d)}}if(document.body){var a=document.createElement('iframe');a.height=1;a.width=1;a.style.position='absolute';a.style.top=0;a.style.left=0;a.style.border='none';a.style.visibility='hidden';document.body.appendChild(a);if('loading'!==document.readyState)c();else if(window.addEventListener)document.addEventListener('DOMContentLoaded',c);else{var e=document.onreadystatechange||function(){};document.onreadystatechange=function(b){e(b);'loading'!==document.readyState&&(document.onreadystatechange=e,c())}}}})();</script></body>
</html>
