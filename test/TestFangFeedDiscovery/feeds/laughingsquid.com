<!doctype html>
<html lang="en-US">
<head>
	
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=5, viewport-fit=cover">
	<link rel="profile" href="https://gmpg.org/xfn/11">

	<script data-no-optimize="1" data-cfasync="false">!function(){"use strict";const t={adt_ei:{identityApiKey:"plainText",source:"url",type:"plaintext",priority:1},adt_eih:{identityApiKey:"sha256",source:"urlh",type:"hashed",priority:2},sh_kit:{identityApiKey:"sha256",source:"urlhck",type:"hashed",priority:3}},e=Object.keys(t);function i(t){return function(t){const e=t.match(/((?=([a-z0-9._!#$%+^&*()[\]<>-]+))\2@[a-z0-9._-]+\.[a-z0-9._-]+)/gi);return e?e[0]:""}(function(t){return t.replace(/\s/g,"")}(t.toLowerCase()))}!async function(){const n=new URL(window.location.href),o=n.searchParams;let a=null;const r=Object.entries(t).sort(([,t],[,e])=>t.priority-e.priority).map(([t])=>t);for(const e of r){const n=o.get(e),r=t[e];if(!n||!r)continue;const c=decodeURIComponent(n),d="plaintext"===r.type&&i(c),s="hashed"===r.type&&c;if(d||s){a={value:c,config:r};break}}if(a){const{value:t,config:e}=a;window.adthrive=window.adthrive||{},window.adthrive.cmd=window.adthrive.cmd||[],window.adthrive.cmd.push(function(){window.adthrive.identityApi({source:e.source,[e.identityApiKey]:t},({success:i,data:n})=>{i?window.adthrive.log("info","Plugin","detectEmails",`Identity API called with ${e.type} email: ${t}`,n):window.adthrive.log("warning","Plugin","detectEmails",`Failed to call Identity API with ${e.type} email: ${t}`,n)})})}!function(t,e){const i=new URL(e);t.forEach(t=>i.searchParams.delete(t)),history.replaceState(null,"",i.toString())}(e,n)}()}();
</script><meta name='robots' content='index, follow, max-image-preview:large, max-snippet:-1, max-video-preview:-1' />
	<style>img:is([sizes="auto" i], [sizes^="auto," i]) { contain-intrinsic-size: 3000px 1500px }</style>
	<style data-no-optimize="1" data-cfasync="false">
	.adthrive-ad {
		margin-top: 10px;
		margin-bottom: 10px;
		text-align: center;
		overflow-x: visible;
		clear: both;
		line-height: 0;
	}
	.adthrive-ad {
clear: both;
}

@media (max-width:359px) {
.site-inner {
padding-left:2.5%;
padding-right:2.5%;
}
}

/* Fix for left aligned ads, 10/11/19 */
.adthrive-ad > div[id^='google_ads_iframe'] {margin: 0 auto !important;}
.adthrive-ad iframe {max-width: none !important;}

/* confirm click footer ad fix test */
body.adthrive-device-phone .adthrive-footer.adthrive-sticky {
padding-top:0px;
overflow:visible !important;
border-top:0px !important;
}
body.adthrive-device-phone .adthrive-sticky.adthrive-footer>.adthrive-close {
top:-25px !important;
right:0px !important;
border-radius: 0px !important;
line-height: 24px !important;
font-size: 24px !important;
}
/* confirm click footer ad fix test end */

.adthrive-ad-cls>div, .adthrive-ad-cls>iframe {
flex-basis: auto;
}

/**/

/* Adjust min height of header for CLS */
.adthrive-header {
min-height: 250px!important;
}
/* End Header adjustment */

.adthrive-ad:not(.adthrive-content){
margin-top:0!important;
margin-bottom:0!important;
}</style>
<script data-no-optimize="1" data-cfasync="false">
	window.adthriveCLS = {
		enabledLocations: ['Content', 'Recipe'],
		injectedSlots: [],
		injectedFromPlugin: true,
					};
	window.adthriveCLS.siteAds = {"betaTester":true,"targeting":[{"value":"59974fbe501eec0ea0ce5c9c","key":"siteId"},{"value":"6233884d3dead87088cb958d","key":"organizationId"},{"value":"Laughing Squid","key":"siteName"},{"value":"AdThrive Edge","key":"service"},{"value":"on","key":"bidding"},{"value":["Entertainment"],"key":"verticals"}],"siteUrl":"https://laughingsquid.com/","siteId":"59974fbe501eec0ea0ce5c9c","siteName":"Laughing Squid","breakpoints":{"tablet":768,"desktop":1024},"cloudflare":{"version":"b770817"},"adUnits":[{"sequence":null,"thirdPartyAdUnitName":null,"targeting":[{"value":["Header"],"key":"location"}],"devices":["desktop","tablet"],"name":"Header","sticky":false,"location":"Header","dynamic":{"pageSelector":"","spacing":0,"max":1,"lazyMax":null,"enable":true,"lazy":false,"elementSelector":"#main","skip":0,"classNames":[],"position":"afterbegin","every":1,"enabled":true},"stickyOverlapSelector":"","adSizes":[[728,90],[320,50],[468,60],[970,90],[1,1],[320,100],[970,250],[300,50],[728,250]],"priority":399,"autosize":true},{"sequence":1,"thirdPartyAdUnitName":null,"targeting":[{"value":["Sidebar"],"key":"location"}],"devices":["desktop"],"name":"Sidebar_1","sticky":false,"location":"Sidebar","dynamic":{"pageSelector":"","spacing":0,"max":1,"lazyMax":null,"enable":true,"lazy":false,"elementSelector":".ct-sidebar > *","skip":0,"classNames":[],"position":"afterend","every":1,"enabled":true},"stickyOverlapSelector":"","adSizes":[[160,600],[336,280],[320,50],[300,600],[250,250],[1,1],[320,100],[300,1050],[300,50],[300,420],[300,250]],"priority":299,"autosize":true},{"sequence":9,"thirdPartyAdUnitName":null,"targeting":[{"value":["Sidebar"],"key":"location"},{"value":true,"key":"sticky"}],"devices":["desktop"],"name":"Sidebar_9","sticky":true,"location":"Sidebar","dynamic":{"pageSelector":"","spacing":0,"max":1,"lazyMax":null,"enable":true,"lazy":false,"elementSelector":"#sidebar","skip":0,"classNames":[],"position":"beforeend","every":1,"enabled":true},"stickyOverlapSelector":".ct-footer","adSizes":[[160,600],[336,280],[320,50],[300,600],[250,250],[1,1],[320,100],[300,1050],[300,50],[300,420],[300,250]],"priority":291,"autosize":true},{"sequence":null,"thirdPartyAdUnitName":null,"targeting":[{"value":["Content"],"key":"location"}],"devices":["desktop"],"name":"Content","sticky":false,"location":"Content","dynamic":{"pageSelector":"body.blog, body.search, body.archive","spacing":0,"max":2,"lazyMax":1,"enable":true,"lazy":true,"elementSelector":"article.post","skip":0,"classNames":[],"position":"afterend","every":2,"enabled":true},"stickyOverlapSelector":"","adSizes":[[728,90],[336,280],[320,50],[468,60],[970,90],[250,250],[1,1],[320,100],[970,250],[1,2],[300,50],[300,300],[552,334],[728,250],[300,250]],"priority":199,"autosize":true},{"sequence":null,"thirdPartyAdUnitName":null,"targeting":[{"value":["Content"],"key":"location"}],"devices":["tablet","phone"],"name":"Content","sticky":false,"location":"Content","dynamic":{"pageSelector":"body.blog, body.search, body.archive","spacing":0,"max":3,"lazyMax":null,"enable":true,"lazy":false,"elementSelector":"article.post","skip":0,"classNames":[],"position":"afterend","every":2,"enabled":true},"stickyOverlapSelector":"","adSizes":[[728,90],[336,280],[320,50],[468,60],[970,90],[250,250],[1,1],[320,100],[970,250],[1,2],[300,50],[300,300],[552,334],[728,250],[300,250]],"priority":199,"autosize":true},{"sequence":1,"thirdPartyAdUnitName":null,"targeting":[{"value":["Content"],"key":"location"}],"devices":["desktop"],"name":"Content_1","sticky":false,"location":"Content","dynamic":{"pageSelector":"body.single","spacing":1,"max":3,"lazyMax":96,"enable":true,"lazy":true,"elementSelector":"article.post > .entry-content > *:not(h2):not(h3):not(.hosting-below-post)","skip":2,"classNames":[],"position":"afterend","every":1,"enabled":true},"stickyOverlapSelector":"","adSizes":[[120,240],[250,250],[300,250],[320,50],[320,100],[336,280],[468,60],[728,90],[970,90],[1,1],[300,300],[552,334],[300,50],[728,250],[970,250],[1,2]],"priority":199,"autosize":true},{"sequence":1,"thirdPartyAdUnitName":null,"targeting":[{"value":["Content"],"key":"location"}],"devices":["tablet","phone"],"name":"Content_1","sticky":false,"location":"Content","dynamic":{"pageSelector":"body.single","spacing":1,"max":3,"lazyMax":96,"enable":true,"lazy":true,"elementSelector":"article.post > .entry-content > *:not(h2):not(h3):not(.hosting-below-post)","skip":2,"classNames":[],"position":"afterend","every":1,"enabled":true},"stickyOverlapSelector":"","adSizes":[[120,240],[250,250],[300,250],[320,50],[320,100],[336,280],[468,60],[728,90],[970,90],[1,1],[300,300],[552,334],[300,50],[728,250],[970,250],[1,2]],"priority":199,"autosize":true},{"sequence":null,"thirdPartyAdUnitName":null,"targeting":[{"value":["Below Post"],"key":"location"}],"devices":["phone","tablet","desktop"],"name":"Below_Post","sticky":false,"location":"Below Post","dynamic":{"pageSelector":"body.single, body.page","spacing":0,"max":0,"lazyMax":1,"enable":true,"lazy":true,"elementSelector":".ct-related-posts","skip":0,"classNames":[],"position":"beforebegin","every":1,"enabled":true},"stickyOverlapSelector":"","adSizes":[[728,90],[336,280],[320,50],[468,60],[250,250],[1,1],[320,100],[300,250],[970,250],[728,250]],"priority":99,"autosize":true},{"sequence":null,"thirdPartyAdUnitName":null,"targeting":[{"value":["Footer"],"key":"location"},{"value":true,"key":"sticky"}],"devices":["tablet","phone","desktop"],"name":"Footer","sticky":true,"location":"Footer","dynamic":{"pageSelector":"","spacing":0,"max":1,"lazyMax":null,"enable":true,"lazy":false,"elementSelector":"body","skip":0,"classNames":[],"position":"beforeend","every":1,"enabled":true},"stickyOverlapSelector":"","adSizes":[[320,50],[320,100],[728,90],[970,90],[468,60],[1,1],[300,50]],"priority":-1,"autosize":true}],"adDensityLayout":{"mobile":{"adDensity":0.24,"onePerViewport":false},"pageOverrides":[{"mobile":{"adDensity":0.3,"onePerViewport":false},"note":null,"pageSelector":"body.postid-779356","desktop":{"adDensity":0.3,"onePerViewport":false}},{"mobile":{"adDensity":0.3,"onePerViewport":false},"note":null,"pageSelector":"body.blog, body.search, body.archive","desktop":{"adDensity":0.3,"onePerViewport":false}}],"desktop":{"adDensity":0.2,"onePerViewport":false}},"adDensityEnabled":true,"siteExperiments":[],"adTypes":{"sponsorTileDesktop":true,"interscrollerDesktop":true,"nativeBelowPostDesktop":true,"miniscroller":true,"largeFormatsMobile":true,"nativeMobileContent":true,"inRecipeRecommendationMobile":true,"nativeMobileRecipe":true,"sponsorTileMobile":true,"expandableCatalogAdsMobile":true,"outstreamMobile":true,"nativeHeaderMobile":true,"inRecipeRecommendationDesktop":true,"nativeDesktopContent":true,"outstreamDesktop":true,"animatedFooter":true,"skylineHeader":true,"expandableFooter":true,"nativeDesktopSidebar":true,"videoFootersMobile":true,"videoFootersDesktop":true,"interscroller":true,"nativeDesktopRecipe":true,"nativeHeaderDesktop":true,"nativeBelowPostMobile":true,"expandableCatalogAdsDesktop":true,"largeFormatsDesktop":true},"adOptions":{"theTradeDesk":true,"rtbhouse":true,"undertone":true,"sidebarConfig":{"dynamicStickySidebar":{"minHeight":1800,"enabled":true,"blockedSelectors":[]}},"footerCloseButton":true,"teads":true,"seedtag":true,"pmp":true,"thirtyThreeAcross":true,"sharethrough":true,"optimizeVideoPlayersForEarnings":true,"removeVideoTitleWrapper":true,"pubMatic":true,"contentTermsFooterEnabled":false,"infiniteScroll":false,"longerVideoAdPod":true,"yahoossp":true,"spa":false,"stickyContainerConfig":{"recipeDesktop":{"minHeight":null,"enabled":false},"blockedSelectors":[],"stickyHeaderSelectors":[],"content":{"minHeight":null,"enabled":false},"recipeMobile":{"minHeight":null,"enabled":false}},"sonobi":true,"gatedPrint":{"printClasses":[],"siteEmailServiceProviderId":null,"defaultOptIn":false,"enabled":false,"newsletterPromptEnabled":false},"yieldmo":true,"footerSelector":"","amazonUAM":true,"gamMCMEnabled":true,"gamMCMChildNetworkCode":"1005972","rubicon":true,"conversant":true,"openx":true,"customCreativeEnabled":true,"mobileHeaderHeight":1,"secColor":"#000000","unruly":true,"mediaGrid":true,"bRealTime":true,"adInViewTime":null,"gumgum":true,"comscoreFooter":true,"desktopInterstitial":true,"amx":true,"footerCloseButtonDesktop":true,"ozone":true,"isAutoOptimized":false,"adform":true,"comscoreTAL":true,"targetaff":true,"bgColor":"#FFFFFF","advancePlaylistOptions":{"playlistPlayer":{"enabled":true},"relatedPlayer":{"enabled":true,"applyToFirst":false}},"kargo":true,"liveRampATS":true,"footerCloseButtonMobile":true,"interstitialBlockedPageSelectors":"","prioritizeShorterVideoAds":true,"allowSmallerAdSizes":true,"comscore":"Lifestyle","blis":true,"wakeLock":{"desktopEnabled":true,"mobileValue":15,"mobileEnabled":true,"desktopValue":30},"mobileInterstitial":true,"tripleLift":true,"sensitiveCategories":["alc","ast","cbd","cosm","dat","gamc","pol","rel","ssr","srh","ske","tob","wtl"],"liveRamp":true,"mobileInterstitialBlockedPageSelectors":"","adthriveEmailIdentity":true,"criteo":true,"nativo":true,"infiniteScrollOptions":{"selector":"","heightThreshold":0},"siteAttributes":{"mobileHeaderSelectors":[],"desktopHeaderSelectors":[]},"dynamicContentSlotLazyLoading":true,"clsOptimizedAds":true,"ogury":true,"verticals":["Entertainment"],"inImage":false,"stackadapt":true,"usCMP":{"enabled":false,"regions":[]},"advancePlaylist":true,"medianet":true,"delayLoading":true,"inImageZone":null,"appNexus":true,"rise":true,"liveRampId":"","infiniteScrollRefresh":false,"indexExchange":true},"thirdPartySiteConfig":{"partners":{"discounts":[]}},"featureRollouts":{"mobile-footer-close-button-css-conflict":{"featureRolloutId":9,"data":null,"enabled":true}},"videoPlayers":{"contextual":{"autoplayCollapsibleEnabled":true,"overrideEmbedLocation":false,"defaultPlayerType":"static"},"videoEmbed":"wordpress","footerSelector":"","contentSpecificPlaylists":[{"isDraft":false,"playlistId":"H6G5B6aq","categories":[],"shuffle":false}],"players":[{"playlistId":"","pageSelector":"","devices":["mobile"],"mobileLocation":"top-center","description":"","skip":0,"title":"Sticky related player - mobile","type":"stickyRelated","enabled":true,"formattedType":"Sticky Related","elementSelector":".entry-content > p:not(:has(iframe)), .entry-content > blockquote","id":4056894,"position":"afterend","saveVideoCloseState":false,"shuffle":false,"mobileHeaderSelector":null,"playerId":"mDaoNZ7q"},{"playlistId":"DH12rcBA","pageSelector":"body.single","devices":["mobile"],"mobileLocation":"top-center","description":"","skip":0,"title":"","type":"stickyPlaylist","enabled":false,"footerSelector":"","formattedType":"Sticky Playlist","elementSelector":".entry-content > p:not(:has(iframe)), .entry-content > blockquote","id":4056896,"position":"afterend","saveVideoCloseState":false,"shuffle":true,"mobileHeaderSelector":null,"playerId":"jhO4eaIe"},{"playlistId":"DH12rcBA","pageSelector":"body.single","devices":["desktop"],"description":"","skip":0,"title":"","type":"stickyPlaylist","enabled":false,"footerSelector":"","formattedType":"Sticky Playlist","elementSelector":".entry-content > p:not(:has(iframe)), .entry-content > blockquote","id":4056895,"position":"afterend","saveVideoCloseState":false,"shuffle":true,"mobileHeaderSelector":null,"playerId":"jhO4eaIe"},{"playlistId":"","pageSelector":"","devices":["desktop"],"description":"","skip":0,"title":"Sticky related player - desktop","type":"stickyRelated","enabled":true,"formattedType":"Sticky Related","elementSelector":".entry-content > p:not(:has(iframe)), .entry-content > blockquote","id":4056893,"position":"afterend","saveVideoCloseState":false,"shuffle":false,"mobileHeaderSelector":null,"playerId":"mDaoNZ7q"},{"devices":["desktop","mobile"],"formattedType":"Stationary Related","description":"","id":4056892,"title":"Stationary related player - desktop and mobile","type":"stationaryRelated","enabled":true,"playerId":"mDaoNZ7q"}],"partners":{"theTradeDesk":true,"unruly":true,"mediaGrid":true,"undertone":true,"gumgum":true,"seedtag":true,"amx":true,"ozone":true,"adform":true,"pmp":true,"kargo":true,"connatix":true,"stickyOutstream":{"desktop":{"enabled":true},"blockedPageSelectors":"","mobileLocation":"bottom-left","allowOnHomepage":true,"mobile":{"enabled":true},"saveVideoCloseState":false,"mobileHeaderSelector":null,"allowForPageWithStickyPlayer":{"enabled":true}},"sharethrough":true,"blis":true,"tripleLift":true,"pubMatic":true,"criteo":true,"yahoossp":true,"nativo":true,"stackadapt":true,"yieldmo":true,"amazonUAM":true,"medianet":true,"rubicon":true,"appNexus":true,"rise":true,"openx":true,"indexExchange":true}}};</script>

<script data-no-optimize="1" data-cfasync="false">
(function(w, d) {
	w.adthrive = w.adthrive || {};
	w.adthrive.cmd = w.adthrive.cmd || [];
	w.adthrive.plugin = 'adthrive-ads-3.9.0';
	w.adthrive.host = 'ads.adthrive.com';
	w.adthrive.integration = 'plugin';

	var commitParam = (w.adthriveCLS && w.adthriveCLS.bucket !== 'prod' && w.adthriveCLS.branch) ? '&commit=' + w.adthriveCLS.branch : '';

	var s = d.createElement('script');
	s.async = true;
	s.referrerpolicy='no-referrer-when-downgrade';
	s.src = 'https://' + w.adthrive.host + '/sites/59974fbe501eec0ea0ce5c9c/ads.min.js?referrer=' + w.encodeURIComponent(w.location.href) + commitParam + '&cb=' + (Math.floor(Math.random() * 100) + 1) + '';
	var n = d.getElementsByTagName('script')[0];
	n.parentNode.insertBefore(s, n);
})(window, document);
</script>
<link rel="dns-prefetch" href="https://ads.adthrive.com/"><link rel="preconnect" href="https://ads.adthrive.com/"><link rel="preconnect" href="https://ads.adthrive.com/" crossorigin>
	<!-- This site is optimized with the Yoast SEO Premium plugin v26.1 (Yoast SEO v26.1.1) - https://yoast.com/wordpress/plugins/seo/ -->
	<title>Laughing Squid</title>
	<meta name="description" content="a daily dose of unique and curious things" />
	<link rel="canonical" href="https://laughingsquid.com/" />
	<link rel="next" href="https://laughingsquid.com/page/2/" />
	<meta property="og:locale" content="en_US" />
	<meta property="og:type" content="website" />
	<meta property="og:title" content="Laughing Squid" />
	<meta property="og:description" content="a daily dose of unique and curious things" />
	<meta property="og:url" content="https://laughingsquid.com/" />
	<meta property="og:site_name" content="Laughing Squid" />
	<meta property="og:image" content="https://laughingsquid.com/wp-content/uploads/2018/03/laughing-squid-facbook-open-graph.jpg" />
	<meta property="og:image:width" content="1200" />
	<meta property="og:image:height" content="630" />
	<meta property="og:image:type" content="image/jpeg" />
	<meta name="twitter:card" content="summary_large_image" />
	<meta name="twitter:site" content="@LaughingSquid" />
	<script type="application/ld+json" class="yoast-schema-graph">{"@context":"https://schema.org","@graph":[{"@type":"CollectionPage","@id":"https://laughingsquid.com/","url":"https://laughingsquid.com/","name":"Laughing Squid","isPartOf":{"@id":"https://laughingsquid.com/#website"},"about":{"@id":"https://laughingsquid.com/#organization"},"description":"a daily dose of unique and curious things","breadcrumb":{"@id":"https://laughingsquid.com/#breadcrumb"},"inLanguage":"en-US"},{"@type":"BreadcrumbList","@id":"https://laughingsquid.com/#breadcrumb","itemListElement":[{"@type":"ListItem","position":1,"name":"Home"}]},{"@type":"WebSite","@id":"https://laughingsquid.com/#website","url":"https://laughingsquid.com/","name":"Laughing Squid","description":"a daily dose of unique and curious things","publisher":{"@id":"https://laughingsquid.com/#organization"},"potentialAction":[{"@type":"SearchAction","target":{"@type":"EntryPoint","urlTemplate":"https://laughingsquid.com/?s={search_term_string}"},"query-input":{"@type":"PropertyValueSpecification","valueRequired":true,"valueName":"search_term_string"}}],"inLanguage":"en-US"},{"@type":"Organization","@id":"https://laughingsquid.com/#organization","name":"Laughing Squid","url":"https://laughingsquid.com/","logo":{"@type":"ImageObject","inLanguage":"en-US","@id":"https://laughingsquid.com/#/schema/logo/image/","url":"https://laughingsquid.com/wp-content/uploads/2018/03/laughing-squid-menu.png","contentUrl":"https://laughingsquid.com/wp-content/uploads/2018/03/laughing-squid-menu.png","width":150,"height":150,"caption":"Laughing Squid"},"image":{"@id":"https://laughingsquid.com/#/schema/logo/image/"},"sameAs":["https://www.facebook.com/laughingsquid","https://x.com/LaughingSquid","https://mastodon.social/@laughingsquid","https://www.instagram.com/laughingsquid/","https://www.linkedin.com/company/laughing-squid","https://www.pinterest.com/laughingsquid/laughing-squid/","https://www.youtube.com/user/laughingsquidsf","https://en.wikipedia.org/wiki/Laughing_Squid","https://www.threads.net/@laughingsquid"]}]}</script>
	<meta name="msvalidate.01" content="025390F08D242EF9553D9FB91E800B51" />
	<meta name="google-site-verification" content="jJyLGaYS5OcLQKNjQ3hN9jTVV6CMcalfPNN3lA3lir4" />
	<meta name="yandex-verification" content="a843a3bd30673488" />
	<link rel="me" href="https://mastodon.social/@laughingsquid" />
	<!-- / Yoast SEO Premium plugin. -->


<link rel='dns-prefetch' href='//stats.wp.com' />
<link rel='dns-prefetch' href='//v0.wordpress.com' />
<link rel="alternate" type="application/rss+xml" title="Laughing Squid &raquo; Feed" href="https://laughingsquid.com/feed/" />
<link rel="alternate" type="application/rss+xml" title="Laughing Squid &raquo; Comments Feed" href="https://laughingsquid.com/comments/feed/" />
<link rel='stylesheet' id='all-css-0' href='https://laughingsquid.com/_static/??-eJyNy0sKgDAMRdENWYNCFQfiWvoJEk2rNBXp7nUi6Mzh5b0D564oOj48CjgR8CQZLG9uVUw2mVRAcmGsA8X6PlTwFotAQE8GGQPG/ImdTcGkGGfjyj9+b+9+0BTGptdDq7u+7S6HyUGz' type='text/css' media='all' />
<style id='jetpack-sharing-buttons-style-inline-css'>
.jetpack-sharing-buttons__services-list{display:flex;flex-direction:row;flex-wrap:wrap;gap:0;list-style-type:none;margin:5px;padding:0}.jetpack-sharing-buttons__services-list.has-small-icon-size{font-size:12px}.jetpack-sharing-buttons__services-list.has-normal-icon-size{font-size:16px}.jetpack-sharing-buttons__services-list.has-large-icon-size{font-size:24px}.jetpack-sharing-buttons__services-list.has-huge-icon-size{font-size:36px}@media print{.jetpack-sharing-buttons__services-list{display:none!important}}.editor-styles-wrapper .wp-block-jetpack-sharing-buttons{gap:0;padding-inline-start:0}ul.jetpack-sharing-buttons__services-list.has-background{padding:1.25em 2.375em}
</style>
<style id='elasticpress-facet-style-inline-css'>
.widget_ep-facet input[type=search],.wp-block-elasticpress-facet input[type=search]{margin-bottom:1rem}.widget_ep-facet .searchable .inner,.wp-block-elasticpress-facet .searchable .inner{max-height:20em;overflow:scroll}.widget_ep-facet .term.hide,.wp-block-elasticpress-facet .term.hide{display:none}.widget_ep-facet .empty-term,.wp-block-elasticpress-facet .empty-term{opacity:.5;position:relative}.widget_ep-facet .empty-term:after,.wp-block-elasticpress-facet .empty-term:after{bottom:0;content:" ";display:block;left:0;position:absolute;right:0;top:0;width:100%;z-index:2}.widget_ep-facet .level-1,.wp-block-elasticpress-facet .level-1{padding-left:20px}.widget_ep-facet .level-2,.wp-block-elasticpress-facet .level-2{padding-left:40px}.widget_ep-facet .level-3,.wp-block-elasticpress-facet .level-3{padding-left:60px}.widget_ep-facet .level-4,.wp-block-elasticpress-facet .level-4{padding-left:5pc}.widget_ep-facet .level-5,.wp-block-elasticpress-facet .level-5{padding-left:75pt}.widget_ep-facet input[disabled],.wp-block-elasticpress-facet input[disabled]{cursor:pointer;opacity:1}.widget_ep-facet .term a,.wp-block-elasticpress-facet .term a{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;position:relative}.widget_ep-facet .term a:hover .ep-checkbox,.wp-block-elasticpress-facet .term a:hover .ep-checkbox{background-color:#ccc}.ep-checkbox{-webkit-box-align:center;-ms-flex-align:center;-ms-flex-negative:0;-webkit-box-pack:center;-ms-flex-pack:center;align-items:center;background-color:#eee;display:-webkit-box;display:-ms-flexbox;display:flex;flex-shrink:0;height:1em;justify-content:center;margin-right:.25em;width:1em}.ep-checkbox:after{border:solid #fff;border-width:0 .125em .125em 0;content:"";display:none;height:.5em;-webkit-transform:rotate(45deg);transform:rotate(45deg);width:.25em}.ep-checkbox.checked{background-color:#5e5e5e}.ep-checkbox.checked:after{display:block}

</style>
<link rel='stylesheet' id='all-css-4' href='https://laughingsquid.com/wp-content/mu-plugins/search/elasticpress/dist/css/related-posts-block-styles.min.css?m=1761070183g' type='text/css' media='all' />
<style id='global-styles-inline-css'>
:root{--wp--preset--aspect-ratio--square: 1;--wp--preset--aspect-ratio--4-3: 4/3;--wp--preset--aspect-ratio--3-4: 3/4;--wp--preset--aspect-ratio--3-2: 3/2;--wp--preset--aspect-ratio--2-3: 2/3;--wp--preset--aspect-ratio--16-9: 16/9;--wp--preset--aspect-ratio--9-16: 9/16;--wp--preset--color--black: #000000;--wp--preset--color--cyan-bluish-gray: #abb8c3;--wp--preset--color--white: #ffffff;--wp--preset--color--pale-pink: #f78da7;--wp--preset--color--vivid-red: #cf2e2e;--wp--preset--color--luminous-vivid-orange: #ff6900;--wp--preset--color--luminous-vivid-amber: #fcb900;--wp--preset--color--light-green-cyan: #7bdcb5;--wp--preset--color--vivid-green-cyan: #00d084;--wp--preset--color--pale-cyan-blue: #8ed1fc;--wp--preset--color--vivid-cyan-blue: #0693e3;--wp--preset--color--vivid-purple: #9b51e0;--wp--preset--color--palette-color-1: var(--theme-palette-color-1, #008900);--wp--preset--color--palette-color-2: var(--theme-palette-color-2, #4169e1);--wp--preset--color--palette-color-3: var(--theme-palette-color-3, #000000);--wp--preset--color--palette-color-4: var(--theme-palette-color-4, #000000);--wp--preset--color--palette-color-5: var(--theme-palette-color-5, #ffffff);--wp--preset--color--palette-color-6: var(--theme-palette-color-6, #ffffff);--wp--preset--color--palette-color-7: var(--theme-palette-color-7, #ffffff);--wp--preset--color--palette-color-8: var(--theme-palette-color-8, #ffffff);--wp--preset--gradient--vivid-cyan-blue-to-vivid-purple: linear-gradient(135deg,rgba(6,147,227,1) 0%,rgb(155,81,224) 100%);--wp--preset--gradient--light-green-cyan-to-vivid-green-cyan: linear-gradient(135deg,rgb(122,220,180) 0%,rgb(0,208,130) 100%);--wp--preset--gradient--luminous-vivid-amber-to-luminous-vivid-orange: linear-gradient(135deg,rgba(252,185,0,1) 0%,rgba(255,105,0,1) 100%);--wp--preset--gradient--luminous-vivid-orange-to-vivid-red: linear-gradient(135deg,rgba(255,105,0,1) 0%,rgb(207,46,46) 100%);--wp--preset--gradient--very-light-gray-to-cyan-bluish-gray: linear-gradient(135deg,rgb(238,238,238) 0%,rgb(169,184,195) 100%);--wp--preset--gradient--cool-to-warm-spectrum: linear-gradient(135deg,rgb(74,234,220) 0%,rgb(151,120,209) 20%,rgb(207,42,186) 40%,rgb(238,44,130) 60%,rgb(251,105,98) 80%,rgb(254,248,76) 100%);--wp--preset--gradient--blush-light-purple: linear-gradient(135deg,rgb(255,206,236) 0%,rgb(152,150,240) 100%);--wp--preset--gradient--blush-bordeaux: linear-gradient(135deg,rgb(254,205,165) 0%,rgb(254,45,45) 50%,rgb(107,0,62) 100%);--wp--preset--gradient--luminous-dusk: linear-gradient(135deg,rgb(255,203,112) 0%,rgb(199,81,192) 50%,rgb(65,88,208) 100%);--wp--preset--gradient--pale-ocean: linear-gradient(135deg,rgb(255,245,203) 0%,rgb(182,227,212) 50%,rgb(51,167,181) 100%);--wp--preset--gradient--electric-grass: linear-gradient(135deg,rgb(202,248,128) 0%,rgb(113,206,126) 100%);--wp--preset--gradient--midnight: linear-gradient(135deg,rgb(2,3,129) 0%,rgb(40,116,252) 100%);--wp--preset--gradient--juicy-peach: linear-gradient(to right, #ffecd2 0%, #fcb69f 100%);--wp--preset--gradient--young-passion: linear-gradient(to right, #ff8177 0%, #ff867a 0%, #ff8c7f 21%, #f99185 52%, #cf556c 78%, #b12a5b 100%);--wp--preset--gradient--true-sunset: linear-gradient(to right, #fa709a 0%, #fee140 100%);--wp--preset--gradient--morpheus-den: linear-gradient(to top, #30cfd0 0%, #330867 100%);--wp--preset--gradient--plum-plate: linear-gradient(135deg, #667eea 0%, #764ba2 100%);--wp--preset--gradient--aqua-splash: linear-gradient(15deg, #13547a 0%, #80d0c7 100%);--wp--preset--gradient--love-kiss: linear-gradient(to top, #ff0844 0%, #ffb199 100%);--wp--preset--gradient--new-retrowave: linear-gradient(to top, #3b41c5 0%, #a981bb 49%, #ffc8a9 100%);--wp--preset--gradient--plum-bath: linear-gradient(to top, #cc208e 0%, #6713d2 100%);--wp--preset--gradient--high-flight: linear-gradient(to right, #0acffe 0%, #495aff 100%);--wp--preset--gradient--teen-party: linear-gradient(-225deg, #FF057C 0%, #8D0B93 50%, #321575 100%);--wp--preset--gradient--fabled-sunset: linear-gradient(-225deg, #231557 0%, #44107A 29%, #FF1361 67%, #FFF800 100%);--wp--preset--gradient--arielle-smile: radial-gradient(circle 248px at center, #16d9e3 0%, #30c7ec 47%, #46aef7 100%);--wp--preset--gradient--itmeo-branding: linear-gradient(180deg, #2af598 0%, #009efd 100%);--wp--preset--gradient--deep-blue: linear-gradient(to right, #6a11cb 0%, #2575fc 100%);--wp--preset--gradient--strong-bliss: linear-gradient(to right, #f78ca0 0%, #f9748f 19%, #fd868c 60%, #fe9a8b 100%);--wp--preset--gradient--sweet-period: linear-gradient(to top, #3f51b1 0%, #5a55ae 13%, #7b5fac 25%, #8f6aae 38%, #a86aa4 50%, #cc6b8e 62%, #f18271 75%, #f3a469 87%, #f7c978 100%);--wp--preset--gradient--purple-division: linear-gradient(to top, #7028e4 0%, #e5b2ca 100%);--wp--preset--gradient--cold-evening: linear-gradient(to top, #0c3483 0%, #a2b6df 100%, #6b8cce 100%, #a2b6df 100%);--wp--preset--gradient--mountain-rock: linear-gradient(to right, #868f96 0%, #596164 100%);--wp--preset--gradient--desert-hump: linear-gradient(to top, #c79081 0%, #dfa579 100%);--wp--preset--gradient--ethernal-constance: linear-gradient(to top, #09203f 0%, #537895 100%);--wp--preset--gradient--happy-memories: linear-gradient(-60deg, #ff5858 0%, #f09819 100%);--wp--preset--gradient--grown-early: linear-gradient(to top, #0ba360 0%, #3cba92 100%);--wp--preset--gradient--morning-salad: linear-gradient(-225deg, #B7F8DB 0%, #50A7C2 100%);--wp--preset--gradient--night-call: linear-gradient(-225deg, #AC32E4 0%, #7918F2 48%, #4801FF 100%);--wp--preset--gradient--mind-crawl: linear-gradient(-225deg, #473B7B 0%, #3584A7 51%, #30D2BE 100%);--wp--preset--gradient--angel-care: linear-gradient(-225deg, #FFE29F 0%, #FFA99F 48%, #FF719A 100%);--wp--preset--gradient--juicy-cake: linear-gradient(to top, #e14fad 0%, #f9d423 100%);--wp--preset--gradient--rich-metal: linear-gradient(to right, #d7d2cc 0%, #304352 100%);--wp--preset--gradient--mole-hall: linear-gradient(-20deg, #616161 0%, #9bc5c3 100%);--wp--preset--gradient--cloudy-knoxville: linear-gradient(120deg, #fdfbfb 0%, #ebedee 100%);--wp--preset--gradient--soft-grass: linear-gradient(to top, #c1dfc4 0%, #deecdd 100%);--wp--preset--gradient--saint-petersburg: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);--wp--preset--gradient--everlasting-sky: linear-gradient(135deg, #fdfcfb 0%, #e2d1c3 100%);--wp--preset--gradient--kind-steel: linear-gradient(-20deg, #e9defa 0%, #fbfcdb 100%);--wp--preset--gradient--over-sun: linear-gradient(60deg, #abecd6 0%, #fbed96 100%);--wp--preset--gradient--premium-white: linear-gradient(to top, #d5d4d0 0%, #d5d4d0 1%, #eeeeec 31%, #efeeec 75%, #e9e9e7 100%);--wp--preset--gradient--clean-mirror: linear-gradient(45deg, #93a5cf 0%, #e4efe9 100%);--wp--preset--gradient--wild-apple: linear-gradient(to top, #d299c2 0%, #fef9d7 100%);--wp--preset--gradient--snow-again: linear-gradient(to top, #e6e9f0 0%, #eef1f5 100%);--wp--preset--gradient--confident-cloud: linear-gradient(to top, #dad4ec 0%, #dad4ec 1%, #f3e7e9 100%);--wp--preset--gradient--glass-water: linear-gradient(to top, #dfe9f3 0%, white 100%);--wp--preset--gradient--perfect-white: linear-gradient(-225deg, #E3FDF5 0%, #FFE6FA 100%);--wp--preset--font-size--small: 13px;--wp--preset--font-size--medium: 20px;--wp--preset--font-size--large: clamp(22px, 1.375rem + ((1vw - 3.2px) * 0.625), 30px);--wp--preset--font-size--x-large: clamp(30px, 1.875rem + ((1vw - 3.2px) * 1.563), 50px);--wp--preset--font-size--xx-large: clamp(45px, 2.813rem + ((1vw - 3.2px) * 2.734), 80px);--wp--preset--spacing--20: 0.44rem;--wp--preset--spacing--30: 0.67rem;--wp--preset--spacing--40: 1rem;--wp--preset--spacing--50: 1.5rem;--wp--preset--spacing--60: 2.25rem;--wp--preset--spacing--70: 3.38rem;--wp--preset--spacing--80: 5.06rem;--wp--preset--shadow--natural: 6px 6px 9px rgba(0, 0, 0, 0.2);--wp--preset--shadow--deep: 12px 12px 50px rgba(0, 0, 0, 0.4);--wp--preset--shadow--sharp: 6px 6px 0px rgba(0, 0, 0, 0.2);--wp--preset--shadow--outlined: 6px 6px 0px -3px rgba(255, 255, 255, 1), 6px 6px rgba(0, 0, 0, 1);--wp--preset--shadow--crisp: 6px 6px 0px rgba(0, 0, 0, 1);}:root { --wp--style--global--content-size: var(--theme-block-max-width);--wp--style--global--wide-size: var(--theme-block-wide-max-width); }:where(body) { margin: 0; }.wp-site-blocks > .alignleft { float: left; margin-right: 2em; }.wp-site-blocks > .alignright { float: right; margin-left: 2em; }.wp-site-blocks > .aligncenter { justify-content: center; margin-left: auto; margin-right: auto; }:where(.wp-site-blocks) > * { margin-block-start: var(--theme-content-spacing); margin-block-end: 0; }:where(.wp-site-blocks) > :first-child { margin-block-start: 0; }:where(.wp-site-blocks) > :last-child { margin-block-end: 0; }:root { --wp--style--block-gap: var(--theme-content-spacing); }:root :where(.is-layout-flow) > :first-child{margin-block-start: 0;}:root :where(.is-layout-flow) > :last-child{margin-block-end: 0;}:root :where(.is-layout-flow) > *{margin-block-start: var(--theme-content-spacing);margin-block-end: 0;}:root :where(.is-layout-constrained) > :first-child{margin-block-start: 0;}:root :where(.is-layout-constrained) > :last-child{margin-block-end: 0;}:root :where(.is-layout-constrained) > *{margin-block-start: var(--theme-content-spacing);margin-block-end: 0;}:root :where(.is-layout-flex){gap: var(--theme-content-spacing);}:root :where(.is-layout-grid){gap: var(--theme-content-spacing);}.is-layout-flow > .alignleft{float: left;margin-inline-start: 0;margin-inline-end: 2em;}.is-layout-flow > .alignright{float: right;margin-inline-start: 2em;margin-inline-end: 0;}.is-layout-flow > .aligncenter{margin-left: auto !important;margin-right: auto !important;}.is-layout-constrained > .alignleft{float: left;margin-inline-start: 0;margin-inline-end: 2em;}.is-layout-constrained > .alignright{float: right;margin-inline-start: 2em;margin-inline-end: 0;}.is-layout-constrained > .aligncenter{margin-left: auto !important;margin-right: auto !important;}.is-layout-constrained > :where(:not(.alignleft):not(.alignright):not(.alignfull)){max-width: var(--wp--style--global--content-size);margin-left: auto !important;margin-right: auto !important;}.is-layout-constrained > .alignwide{max-width: var(--wp--style--global--wide-size);}body .is-layout-flex{display: flex;}.is-layout-flex{flex-wrap: wrap;align-items: center;}.is-layout-flex > :is(*, div){margin: 0;}body .is-layout-grid{display: grid;}.is-layout-grid > :is(*, div){margin: 0;}body{padding-top: 0px;padding-right: 0px;padding-bottom: 0px;padding-left: 0px;}.has-black-color{color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-color{color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-color{color: var(--wp--preset--color--white) !important;}.has-pale-pink-color{color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-color{color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-color{color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-color{color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-color{color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-color{color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-color{color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-color{color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-color{color: var(--wp--preset--color--vivid-purple) !important;}.has-palette-color-1-color{color: var(--wp--preset--color--palette-color-1) !important;}.has-palette-color-2-color{color: var(--wp--preset--color--palette-color-2) !important;}.has-palette-color-3-color{color: var(--wp--preset--color--palette-color-3) !important;}.has-palette-color-4-color{color: var(--wp--preset--color--palette-color-4) !important;}.has-palette-color-5-color{color: var(--wp--preset--color--palette-color-5) !important;}.has-palette-color-6-color{color: var(--wp--preset--color--palette-color-6) !important;}.has-palette-color-7-color{color: var(--wp--preset--color--palette-color-7) !important;}.has-palette-color-8-color{color: var(--wp--preset--color--palette-color-8) !important;}.has-black-background-color{background-color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-background-color{background-color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-background-color{background-color: var(--wp--preset--color--white) !important;}.has-pale-pink-background-color{background-color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-background-color{background-color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-background-color{background-color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-background-color{background-color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-background-color{background-color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-background-color{background-color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-background-color{background-color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-background-color{background-color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-background-color{background-color: var(--wp--preset--color--vivid-purple) !important;}.has-palette-color-1-background-color{background-color: var(--wp--preset--color--palette-color-1) !important;}.has-palette-color-2-background-color{background-color: var(--wp--preset--color--palette-color-2) !important;}.has-palette-color-3-background-color{background-color: var(--wp--preset--color--palette-color-3) !important;}.has-palette-color-4-background-color{background-color: var(--wp--preset--color--palette-color-4) !important;}.has-palette-color-5-background-color{background-color: var(--wp--preset--color--palette-color-5) !important;}.has-palette-color-6-background-color{background-color: var(--wp--preset--color--palette-color-6) !important;}.has-palette-color-7-background-color{background-color: var(--wp--preset--color--palette-color-7) !important;}.has-palette-color-8-background-color{background-color: var(--wp--preset--color--palette-color-8) !important;}.has-black-border-color{border-color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-border-color{border-color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-border-color{border-color: var(--wp--preset--color--white) !important;}.has-pale-pink-border-color{border-color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-border-color{border-color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-border-color{border-color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-border-color{border-color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-border-color{border-color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-border-color{border-color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-border-color{border-color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-border-color{border-color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-border-color{border-color: var(--wp--preset--color--vivid-purple) !important;}.has-palette-color-1-border-color{border-color: var(--wp--preset--color--palette-color-1) !important;}.has-palette-color-2-border-color{border-color: var(--wp--preset--color--palette-color-2) !important;}.has-palette-color-3-border-color{border-color: var(--wp--preset--color--palette-color-3) !important;}.has-palette-color-4-border-color{border-color: var(--wp--preset--color--palette-color-4) !important;}.has-palette-color-5-border-color{border-color: var(--wp--preset--color--palette-color-5) !important;}.has-palette-color-6-border-color{border-color: var(--wp--preset--color--palette-color-6) !important;}.has-palette-color-7-border-color{border-color: var(--wp--preset--color--palette-color-7) !important;}.has-palette-color-8-border-color{border-color: var(--wp--preset--color--palette-color-8) !important;}.has-vivid-cyan-blue-to-vivid-purple-gradient-background{background: var(--wp--preset--gradient--vivid-cyan-blue-to-vivid-purple) !important;}.has-light-green-cyan-to-vivid-green-cyan-gradient-background{background: var(--wp--preset--gradient--light-green-cyan-to-vivid-green-cyan) !important;}.has-luminous-vivid-amber-to-luminous-vivid-orange-gradient-background{background: var(--wp--preset--gradient--luminous-vivid-amber-to-luminous-vivid-orange) !important;}.has-luminous-vivid-orange-to-vivid-red-gradient-background{background: var(--wp--preset--gradient--luminous-vivid-orange-to-vivid-red) !important;}.has-very-light-gray-to-cyan-bluish-gray-gradient-background{background: var(--wp--preset--gradient--very-light-gray-to-cyan-bluish-gray) !important;}.has-cool-to-warm-spectrum-gradient-background{background: var(--wp--preset--gradient--cool-to-warm-spectrum) !important;}.has-blush-light-purple-gradient-background{background: var(--wp--preset--gradient--blush-light-purple) !important;}.has-blush-bordeaux-gradient-background{background: var(--wp--preset--gradient--blush-bordeaux) !important;}.has-luminous-dusk-gradient-background{background: var(--wp--preset--gradient--luminous-dusk) !important;}.has-pale-ocean-gradient-background{background: var(--wp--preset--gradient--pale-ocean) !important;}.has-electric-grass-gradient-background{background: var(--wp--preset--gradient--electric-grass) !important;}.has-midnight-gradient-background{background: var(--wp--preset--gradient--midnight) !important;}.has-juicy-peach-gradient-background{background: var(--wp--preset--gradient--juicy-peach) !important;}.has-young-passion-gradient-background{background: var(--wp--preset--gradient--young-passion) !important;}.has-true-sunset-gradient-background{background: var(--wp--preset--gradient--true-sunset) !important;}.has-morpheus-den-gradient-background{background: var(--wp--preset--gradient--morpheus-den) !important;}.has-plum-plate-gradient-background{background: var(--wp--preset--gradient--plum-plate) !important;}.has-aqua-splash-gradient-background{background: var(--wp--preset--gradient--aqua-splash) !important;}.has-love-kiss-gradient-background{background: var(--wp--preset--gradient--love-kiss) !important;}.has-new-retrowave-gradient-background{background: var(--wp--preset--gradient--new-retrowave) !important;}.has-plum-bath-gradient-background{background: var(--wp--preset--gradient--plum-bath) !important;}.has-high-flight-gradient-background{background: var(--wp--preset--gradient--high-flight) !important;}.has-teen-party-gradient-background{background: var(--wp--preset--gradient--teen-party) !important;}.has-fabled-sunset-gradient-background{background: var(--wp--preset--gradient--fabled-sunset) !important;}.has-arielle-smile-gradient-background{background: var(--wp--preset--gradient--arielle-smile) !important;}.has-itmeo-branding-gradient-background{background: var(--wp--preset--gradient--itmeo-branding) !important;}.has-deep-blue-gradient-background{background: var(--wp--preset--gradient--deep-blue) !important;}.has-strong-bliss-gradient-background{background: var(--wp--preset--gradient--strong-bliss) !important;}.has-sweet-period-gradient-background{background: var(--wp--preset--gradient--sweet-period) !important;}.has-purple-division-gradient-background{background: var(--wp--preset--gradient--purple-division) !important;}.has-cold-evening-gradient-background{background: var(--wp--preset--gradient--cold-evening) !important;}.has-mountain-rock-gradient-background{background: var(--wp--preset--gradient--mountain-rock) !important;}.has-desert-hump-gradient-background{background: var(--wp--preset--gradient--desert-hump) !important;}.has-ethernal-constance-gradient-background{background: var(--wp--preset--gradient--ethernal-constance) !important;}.has-happy-memories-gradient-background{background: var(--wp--preset--gradient--happy-memories) !important;}.has-grown-early-gradient-background{background: var(--wp--preset--gradient--grown-early) !important;}.has-morning-salad-gradient-background{background: var(--wp--preset--gradient--morning-salad) !important;}.has-night-call-gradient-background{background: var(--wp--preset--gradient--night-call) !important;}.has-mind-crawl-gradient-background{background: var(--wp--preset--gradient--mind-crawl) !important;}.has-angel-care-gradient-background{background: var(--wp--preset--gradient--angel-care) !important;}.has-juicy-cake-gradient-background{background: var(--wp--preset--gradient--juicy-cake) !important;}.has-rich-metal-gradient-background{background: var(--wp--preset--gradient--rich-metal) !important;}.has-mole-hall-gradient-background{background: var(--wp--preset--gradient--mole-hall) !important;}.has-cloudy-knoxville-gradient-background{background: var(--wp--preset--gradient--cloudy-knoxville) !important;}.has-soft-grass-gradient-background{background: var(--wp--preset--gradient--soft-grass) !important;}.has-saint-petersburg-gradient-background{background: var(--wp--preset--gradient--saint-petersburg) !important;}.has-everlasting-sky-gradient-background{background: var(--wp--preset--gradient--everlasting-sky) !important;}.has-kind-steel-gradient-background{background: var(--wp--preset--gradient--kind-steel) !important;}.has-over-sun-gradient-background{background: var(--wp--preset--gradient--over-sun) !important;}.has-premium-white-gradient-background{background: var(--wp--preset--gradient--premium-white) !important;}.has-clean-mirror-gradient-background{background: var(--wp--preset--gradient--clean-mirror) !important;}.has-wild-apple-gradient-background{background: var(--wp--preset--gradient--wild-apple) !important;}.has-snow-again-gradient-background{background: var(--wp--preset--gradient--snow-again) !important;}.has-confident-cloud-gradient-background{background: var(--wp--preset--gradient--confident-cloud) !important;}.has-glass-water-gradient-background{background: var(--wp--preset--gradient--glass-water) !important;}.has-perfect-white-gradient-background{background: var(--wp--preset--gradient--perfect-white) !important;}.has-small-font-size{font-size: var(--wp--preset--font-size--small) !important;}.has-medium-font-size{font-size: var(--wp--preset--font-size--medium) !important;}.has-large-font-size{font-size: var(--wp--preset--font-size--large) !important;}.has-x-large-font-size{font-size: var(--wp--preset--font-size--x-large) !important;}.has-xx-large-font-size{font-size: var(--wp--preset--font-size--xx-large) !important;}
:root :where(.wp-block-pullquote){font-size: clamp(0.984em, 0.984rem + ((1vw - 0.2em) * 0.645), 1.5em);line-height: 1.6;}
</style>
<link rel='stylesheet' id='all-css-6' href='https://laughingsquid.com/_static/??-eJytkMEOgjAMhl/IUYxBvBifZYwKC7Rr1i3I27uLHowxEj300v7f17SwiHGBE3KCNCKhQjcHN+kKmtYZK6e6g08hm7yDLnM/I5D1XFGpTZTYAU3yqWzbzKrvsbPxLShzHjw/ydInsewDG4kBrtESLiFOIBHJZ3o1o41uNJ4lp7/o8VYwLXMFwsEaQs7f/u+3UyRIFn2IL3Tet8f61Db1obkDyrvCSA==' type='text/css' media='all' />

		<!-- Global site tag (gtag.js) - Google Analytics v4 -->
		<script async src="https://www.googletagmanager.com/gtag/js?id=G-G7HRPLW4E5"></script>
		<script>
		window.dataLayer = window.dataLayer || [];
		function gtag(){dataLayer.push(arguments);}
		gtag('js', new Date());

		gtag('config', 'G-G7HRPLW4E5');

		</script>
		<!-- End Google Analytics v4 -->

		<link rel="https://api.w.org/" href="https://laughingsquid.com/wp-json/" /><link rel="EditURI" type="application/rsd+xml" title="RSD" href="https://laughingsquid.com/xmlrpc.php?rsd" />
<meta name="generator" content="WordPress 6.8.3" />
	<style>img#wpstats{display:none}</style>
		<meta name="robots" content="noai, noimageai"><noscript><link rel='stylesheet' href='https://laughingsquid.com/wp-content/themes/blocksy/static/bundle/no-scripts.min.css' type='text/css'></noscript>
<style id="ct-main-styles-inline-css">[data-header*="type-1"] .ct-header [data-id="logo"] .site-logo-container {--logo-max-height:80px;} [data-header*="type-1"] .ct-header [data-id="logo"] .site-title {--theme-font-weight:700;--theme-font-size:25px;--theme-line-height:1.5;--theme-link-initial-color:var(--theme-palette-color-4);} [data-header*="type-1"] .ct-header [data-id="logo"] {--margin:0px !important;--horizontal-alignment:center;} [data-header*="type-1"] .ct-header [data-id="menu"] {--menu-items-spacing:38px;--margin:0 80px 0 0px !important;} [data-header*="type-1"] .ct-header [data-id="menu"] > ul > li > a {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:16px;--theme-line-height:1.3;--theme-letter-spacing:0em;--theme-link-initial-color:var(--theme-palette-color-1);--theme-link-hover-color:var(--theme-palette-color-2);--theme-link-active-color:var(--theme-palette-color-1);} [data-header*="type-1"] .ct-header [data-id="menu"] .sub-menu .ct-menu-link {--theme-link-initial-color:#ffffff;--theme-font-weight:500;--theme-font-size:12px;} [data-header*="type-1"] .ct-header [data-id="menu"] .sub-menu {--dropdown-items-spacing:20px;--dropdown-divider:1px dashed rgba(255, 255, 255, 0.1);--theme-box-shadow:0px 10px 20px rgba(41, 51, 61, 0.1);--theme-border-radius:0px 0px 2px 2px;} [data-header*="type-1"] .ct-header [data-row*="middle"] {--height:130px;background-color:var(--theme-palette-color-8);background-image:none;--theme-border-top:none;--theme-border-bottom:none;--theme-box-shadow:none;} [data-header*="type-1"] .ct-header [data-row*="middle"] > div {--theme-border-top:none;--theme-border-bottom:none;} [data-header*="type-1"] [data-id="mobile-menu"] {--theme-font-weight:700;--theme-font-size:30px;--theme-link-initial-color:#008900;--theme-link-hover-color:#4169e1;--theme-link-active-color:#008900;--mobile-menu-divider:none;} [data-header*="type-1"] #offcanvas {background-color:#ffffff;--panel-content-height:100%;--horizontal-alignment:initial;--text-horizontal-alignment:initial;--has-indentation:1;} [data-header*="type-1"] #offcanvas .ct-toggle-close {--theme-icon-color:var(--theme-palette-color-1);} [data-header*="type-1"] #offcanvas .ct-toggle-close:hover {--theme-icon-color:var(--theme-palette-color-2);} [data-header*="type-1"] [data-id="search"] {--theme-icon-size:20px;} [data-header*="type-1"] [data-id="search"] .ct-label {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;} [data-header*="type-1"] #search-modal .ct-search-results {--theme-font-weight:500;--theme-font-size:14px;--theme-line-height:1.4;} [data-header*="type-1"] #search-modal .ct-search-form {--theme-link-initial-color:var(--theme-palette-color-1);--theme-link-hover-color:var(--theme-palette-color-1);--theme-form-text-initial-color:var(--theme-palette-color-1);--theme-form-text-focus-color:var(--theme-palette-color-1);--theme-form-field-border-initial-color:rgba(255, 255, 255, 0.2);--theme-button-background-hover-color:var(--theme-palette-color-1);} [data-header*="type-1"] #search-modal .ct-toggle-close {--theme-icon-color:var(--theme-palette-color-1);} [data-header*="type-1"] #search-modal .ct-toggle-close:hover {--theme-icon-color:var(--theme-palette-color-1);} [data-header*="type-1"] #search-modal {background-color:var(--theme-palette-color-5);} [data-header*="type-1"] [data-id="trigger"] {--theme-icon-size:18px;} [data-header*="type-1"] .ct-header [data-id="search-input"] {--max-width:100%;--theme-form-field-border-initial-color:var(--theme-palette-color-1);--theme-form-field-border-focus-color:var(--theme-palette-color-2);--margin:0 0px 0 0 !important;} [data-header*="type-1"] .ct-header [data-middle="search-input"] {--search-box-max-width:100%;} [data-header*="type-1"] .ct-header [data-id="search-input"] .ct-search-results {--theme-font-weight:500;--theme-font-size:14px;--theme-line-height:1.4;--theme-link-initial-color:var(--theme-text-color);--search-dropdown-background:#ffffff;--items-divider:none;} [data-header*="type-1"] {--header-height:130px;} [data-header*="type-1"] .ct-header {background-image:none;} [data-footer*="type-1"] [data-id="copyright"] {--theme-font-weight:400;--theme-font-size:13px;--theme-line-height:2;--theme-link-initial-color:var(--theme-palette-color-1);} [data-footer*="type-1"] [data-column="copyright"] {--horizontal-alignment:center;--vertical-alignment:center;} [data-footer*="type-1"] .ct-footer [data-row*="middle"] > div {--container-spacing:35px;--vertical-alignment:center;--theme-border:none;--theme-border-top:1px solid #dddddd;--theme-border-bottom:none;--grid-template-columns:repeat(3, 1fr);} [data-footer*="type-1"] .ct-footer [data-row*="middle"] .widget-title {--theme-font-size:16px;} [data-footer*="type-1"] .ct-footer [data-row*="middle"] {--theme-border-top:none;--theme-border-bottom:none;background-color:#ffffff;} [data-footer*="type-1"] [data-id="socials"].ct-footer-socials {--theme-icon-size:30px;--items-spacing:40px;} [data-footer*="type-1"] [data-column="socials"] {--horizontal-alignment:center;--vertical-alignment:center;} [data-footer*="type-1"] [data-id="socials"].ct-footer-socials [data-color="custom"] {--theme-icon-color:var(--theme-palette-color-1);--background-color:rgba(218, 222, 228, 0.3);--background-hover-color:var(--theme-palette-color-1);} [data-footer*="type-1"] [data-id="socials"].ct-footer-socials .ct-label {--visibility:none;} [data-footer*="type-1"] .ct-footer [data-id="d2xrsV"] {--max-width:100%;--theme-font-size:13px;--theme-line-height:2;--theme-letter-spacing:0em;} [data-footer*="type-1"] .ct-footer [data-column="text:d2xrsV"] {--horizontal-alignment:center;--vertical-alignment:center;} [data-footer*="type-1"] .ct-footer {background-color:var(--theme-palette-color-6);}:root {--theme-font-family:Helvetica;--theme-font-weight:400;--theme-text-transform:none;--theme-text-decoration:none;--theme-font-size:18px;--theme-line-height:1.65;--theme-letter-spacing:0em;--theme-button-font-weight:500;--theme-button-font-size:15px;--has-classic-forms:var(--true);--has-modern-forms:var(--false);--theme-form-text-initial-color:var(--theme-palette-color-3);--theme-form-text-focus-color:var(--theme-palette-color-4);--theme-form-field-border-initial-color:var(--border-color);--theme-form-field-border-focus-color:var(--theme-palette-color-2);--theme-form-selection-field-initial-color:var(--theme-border-color);--theme-form-selection-field-active-color:var(--theme-palette-color-1);--theme-palette-color-1:#008900;--theme-palette-color-2:#4169e1;--theme-palette-color-3:#000000;--theme-palette-color-4:#000000;--theme-palette-color-5:#ffffff;--theme-palette-color-6:#ffffff;--theme-palette-color-7:#ffffff;--theme-palette-color-8:#ffffff;--theme-text-color:var(--theme-palette-color-3);--theme-link-initial-color:var(--theme-palette-color-1);--theme-link-hover-color:var(--theme-palette-color-2);--theme-selection-text-color:#ffffff;--theme-selection-background-color:var(--theme-palette-color-1);--theme-border-color:var(--theme-palette-color-1);--theme-headings-color:var(--theme-palette-color-1);--theme-content-spacing:1.5em;--theme-button-min-height:40px;--theme-button-shadow:none;--theme-button-transform:none;--theme-button-text-initial-color:#ffffff;--theme-button-text-hover-color:#ffffff;--theme-button-background-initial-color:var(--theme-palette-color-1);--theme-button-background-hover-color:var(--theme-palette-color-2);--theme-button-border:none;--theme-button-padding:5px 20px;--theme-normal-container-max-width:1130px;--theme-content-vertical-spacing:30px;--theme-container-edge-spacing:90vw;--theme-narrow-container-max-width:750px;--theme-wide-offset:130px;}h1 {--theme-font-weight:500;--theme-font-size:30px;--theme-line-height:1.5;}h2 {--theme-font-weight:500;--theme-font-size:28px;--theme-line-height:1.5;}h3 {--theme-font-weight:500;--theme-font-size:26px;--theme-line-height:1.5;}h4 {--theme-font-weight:500;--theme-font-size:24px;--theme-line-height:1.5;}h5 {--theme-font-weight:500;--theme-font-size:20px;--theme-line-height:1.5;}h6 {--theme-font-weight:500;--theme-font-size:16px;--theme-line-height:1.5;}.wp-block-pullquote {--theme-font-family:Georgia;--theme-font-weight:600;--theme-font-style:italic;--theme-font-size:25px;}pre, code, samp, kbd {--theme-font-family:monospace;--theme-font-weight:400;--theme-font-size:16px;}figcaption {--theme-font-size:14px;}.ct-sidebar .widget-title {--theme-font-size:20px;}.ct-breadcrumbs {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;}body {background-color:var(--theme-palette-color-7);background-image:none;} [data-prefix="single_blog_post"] .entry-header .page-title {--theme-font-weight:500;--theme-font-size:29px;--theme-line-height:1.2;} [data-prefix="single_blog_post"] .entry-header .entry-meta {--theme-font-weight:500;--theme-text-transform:uppercase;--theme-text-decoration:none;--theme-font-size:12px;--theme-line-height:1.3;--theme-text-color:var(--theme-palette-color-3);} [data-prefix="single_blog_post"] .hero-section[data-type="type-1"] {--alignment:left;--margin-bottom:20px;} [data-prefix="single_blog_post"] .hero-section .entry-meta {--itemSpacing:15px;} [data-prefix="blog"] .entry-header .page-title {--theme-font-weight:600;--theme-font-size:50px;} [data-prefix="blog"] .entry-header .entry-meta {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;--theme-line-height:1.3;} [data-prefix="blog"] .entry-header .page-description {--theme-font-weight:500;--theme-font-size:16px;} [data-prefix="blog"] .hero-section[data-type="type-1"] {--alignment:center;--margin-bottom:49px;} [data-prefix="blog"] .hero-section .page-description {--itemSpacing:0px;--description-max-width:100%;} [data-prefix="categories"] .entry-header .page-title {--theme-font-size:30px;} [data-prefix="categories"] .entry-header .entry-meta {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;--theme-line-height:1.3;} [data-prefix="categories"] .hero-section[data-type="type-1"] {--margin-bottom:30px;} [data-prefix="search"] .entry-header .page-title {--theme-font-size:30px;} [data-prefix="search"] .entry-header .entry-meta {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;--theme-line-height:1.3;} [data-prefix="search"] .hero-section[data-type="type-1"] {--alignment:center;--margin-bottom:30px;} [data-prefix="author"] .entry-header .page-title {--theme-font-size:30px;} [data-prefix="author"] .entry-header .entry-meta {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;--theme-line-height:1.3;} [data-prefix="author"] .hero-section[data-type="type-1"] {--alignment:left;--margin-bottom:30px;} [data-prefix="author"] .hero-section .page-description {--itemSpacing:10px;} [data-prefix="single_page"] .entry-header .page-title {--theme-font-weight:500;--theme-font-size:30px;} [data-prefix="single_page"] .entry-header .entry-meta {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;--theme-line-height:1.3;} [data-prefix="single_page"] .hero-section[data-type="type-1"] {--margin-bottom:20px;} [data-prefix="blog"] .ct-pagination {--spacing:20px;} [data-prefix="categories"] .ct-pagination {--spacing:20px;} [data-prefix="author"] .ct-pagination {--spacing:20px;} [data-prefix="search"] .ct-pagination {--spacing:20px;} [data-prefix="blog"] .entry-card .entry-title {--theme-font-size:20px;--theme-line-height:1.3;} [data-prefix="blog"] .entry-excerpt {--theme-letter-spacing:0em;} [data-prefix="blog"] .entry-card .entry-meta {--theme-font-weight:600;--theme-text-transform:uppercase;--theme-font-size:12px;} [data-prefix="blog"] [data-cards="simple"] .entry-card {--card-border:none;} [data-prefix="blog"] [data-archive="default"] .card-content .ct-media-container {--card-element-spacing:30px;} [data-prefix="blog"] .entries {--grid-columns-gap:10px;} [data-prefix="categories"] .entry-card .entry-title {--theme-font-weight:500;--theme-font-size:20px;--theme-line-height:1.3;} [data-prefix="categories"] .entry-card .entry-meta {--theme-font-weight:500;--theme-text-transform:uppercase;--theme-font-size:12px;} [data-prefix="categories"] [data-cards="simple"] .entry-card {--card-border:none;} [data-prefix="categories"] [data-archive="default"] .card-content .ct-media-container {--card-element-spacing:30px;} [data-prefix="categories"] [data-archive="default"] .card-content .entry-meta[data-id="tGLqOZ"] {--card-element-spacing:15px;} [data-prefix="categories"] .entries {--grid-columns-gap:10px;} [data-prefix="author"] .entry-card .entry-title {--theme-font-weight:500;--theme-font-size:20px;--theme-line-height:1.3;} [data-prefix="author"] .entry-card .entry-meta {--theme-font-weight:500;--theme-text-transform:uppercase;--theme-font-size:12px;} [data-prefix="author"] [data-cards="simple"] .entry-card {--card-border:none;} [data-prefix="author"] [data-archive="default"] .card-content .ct-media-container {--card-element-spacing:30px;} [data-prefix="author"] .entries {--grid-columns-gap:10px;} [data-prefix="search"] .entry-card .entry-title {--theme-font-weight:500;--theme-font-size:20px;--theme-line-height:1.3;} [data-prefix="search"] .entry-card .entry-meta {--theme-font-weight:500;--theme-text-transform:uppercase;--theme-font-size:12px;} [data-prefix="search"] [data-cards="simple"] .entry-card {--card-border:none;} [data-prefix="search"] [data-archive="default"] .card-content .ct-media-container {--card-element-spacing:30px;} [data-prefix="search"] [data-archive="default"] .card-content .entry-meta[data-id="ra3ERY"] {--card-element-spacing:15px;} [data-prefix="search"] .entries {--grid-columns-gap:10px;}form textarea {--theme-form-field-height:170px;} [data-sidebar] {--sidebar-width:32%;--sidebar-width-no-unit:32;--sidebar-gap:3%;}.ct-sidebar > * {--theme-text-color:var(--theme-palette-color-1);}.ct-sidebar {--theme-link-initial-color:var(--theme-palette-color-1);--sidebar-widgets-spacing:30px;} [data-prefix="single_blog_post"] .ct-share-box {--theme-icon-size:13px;--items-spacing:14px;} [data-prefix="single_blog_post"] .ct-share-box[data-location="top"] {--margin:25px;} [data-prefix="single_blog_post"] .ct-share-box .ct-module-title {--theme-font-weight:600;--theme-font-size:14px;} [data-prefix="single_blog_post"] .author-box {--spacing:30px;} [data-prefix="single_blog_post"] .author-box .author-box-name {--theme-heading-color:var(--theme-palette-color-1);} [data-prefix="single_blog_post"] .author-box[data-type="type-2"] {--theme-border-color:var(--theme-palette-color-1);} [data-prefix="single_blog_post"] .ct-related-posts-container {background-color:var(--theme-palette-color-6);} [data-prefix="single_blog_post"] .ct-related-posts .related-entry-title {--theme-font-size:16px;--card-element-spacing:5px;} [data-prefix="single_blog_post"] .ct-related-posts .entry-meta {--theme-font-size:14px;} [data-prefix="single_blog_post"] .ct-related-posts .ct-media-container {--theme-border-radius:0px;} [data-prefix="single_blog_post"] .ct-related-posts {--grid-template-columns:repeat(3, minmax(0, 1fr));} [data-prefix="single_blog_post"] {background-color:#ffffff;} [data-prefix="single_blog_post"] [class*="ct-container"] > article[class*="post"] {--has-boxed:var(--false);--has-wide:var(--true);} [data-prefix="single_page"] {background-color:#ffffff;} [data-prefix="single_page"] [class*="ct-container"] > article[class*="post"] {--has-boxed:var(--false);--has-wide:var(--true);}[data-block*="939527"] {--popup-padding:5px;--popup-box-shadow:0px 10px 20px rgba(41, 51, 61, 0.1);} [data-block*="939527"] .ct-toggle-close {--toggle-button-background:var(--theme-palette-color-1);} [data-block*="939527"] .ct-toggle-close:hover {--toggle-button-background:var(--theme-palette-color-2);} [data-block*="939527"] .ct-popup-inner > article {background-color:var(--theme-palette-color-2);} [data-block*="939527"] > [class*="ct-container"] > article[class*="post"] {--has-boxed:var(--false);--has-wide:var(--true);}@media (max-width: 999.98px) {[data-footer*="type-1"] .ct-footer [data-row*="middle"] > div {--container-spacing:50px;--grid-template-columns:initial;} [data-prefix="single_blog_post"] .ct-related-posts {--grid-template-columns:repeat(2, minmax(0, 1fr));}}@media (max-width: 689.98px) {[data-header*="type-1"] [data-id="mobile-menu"] {--theme-font-size:20px;} [data-header*="type-1"] #offcanvas {--horizontal-alignment:center;--text-horizontal-alignment:center;--has-indentation:0;} [data-header*="type-1"] [data-id="search"] {--theme-icon-color:var(--theme-palette-color-1);--theme-icon-hover-color:var(--theme-palette-color-1);--theme-link-initial-color:var(--theme-palette-color-1);--theme-link-hover-color:var(--theme-palette-color-1);} [data-footer*="type-1"] .ct-footer [data-row*="middle"] > div {--container-spacing:40px;--grid-template-columns:initial;} [data-prefix="blog"] .entry-header .page-title {--theme-font-size:40px;} [data-prefix="blog"] .hero-section[data-type="type-1"] {--margin-bottom:0px;} [data-prefix="search"] .entry-header .page-title {--theme-font-size:25px;} [data-prefix="author"] .entry-header .page-title {--theme-font-size:25px;} [data-prefix="single_page"] .entry-header .page-title {--theme-font-size:25px;} [data-prefix="blog"] .entry-card .entry-title {--theme-font-size:18px;} [data-prefix="blog"] .entries {--grid-columns-gap:10;} [data-prefix="categories"] .entry-card .entry-title {--theme-font-size:18px;} [data-prefix="author"] .entry-card .entry-title {--theme-font-size:18px;} [data-prefix="search"] .entry-card .entry-title {--theme-font-size:18px;}:root {--theme-container-edge-spacing:88vw;} [data-prefix="single_blog_post"] .ct-related-posts {--grid-template-columns:repeat(1, minmax(0, 1fr));}}</style>
<meta property="fb:pages" content="6976292194">

<meta property="fb:app_id" content="102633291605" />

<script src="https://embeds.beehiiv.com/recommendations.js?_bhpid=937f11f7-9378-44c0-aa0a-11c98c2ae62e&v=1" data-beehiiv-recommendations-widget defer></script><link rel="icon" href="https://laughingsquid.com/wp-content/uploads/2018/03/cropped-laughing-squid-favicon.png?w=32" sizes="32x32" />
<link rel="icon" href="https://laughingsquid.com/wp-content/uploads/2018/03/cropped-laughing-squid-favicon.png?w=192" sizes="192x192" />
<link rel="apple-touch-icon" href="https://laughingsquid.com/wp-content/uploads/2018/03/cropped-laughing-squid-favicon.png?w=180" />
<meta name="msapplication-TileImage" content="https://laughingsquid.com/wp-content/uploads/2018/03/cropped-laughing-squid-favicon.png?w=270" />
		<style id="wp-custom-css">
			.post-edit-link { 
		display: none;
}

a {
	color: #008900;
}

.wp-block-quote:not(.has-text-align-center):not(.has-text-align-right) {
    --padding: 0 0 0 15px;
		color: #666;
	  background: #f9f9f9;
    border-left: 5px solid #ccc;
    font-style: italic;
		margin-left: 20px;
}

blockquote {
    padding: 15px;
		color: #666;
		background: #f9f9f9;
    border-left: 5px solid #ccc;
    font-style: italic;
		margin-left: 20px !important;
}

.hosting-below-post {
	background-color: #ffffff;
	border: 1px solid #4169E1;
	overflow: hidden;
	padding: 15px;
}

.hosting-below-post-title {
	font-size: 18px;
	text-align: center;
}

.meh {
	background-color: #ffffff;
	border: 1px solid #4169E1;
	overflow: hidden;
	margin-top: 50px;
	padding: 40px;
}

.jetpack_widget_social_icons ul {
    display: block;
    margin: 0 0 1.5em;
    padding: 0;
    text-align: center;
}

.jetpack_widget_social_icons ul li {
    border: 0;
    display: inline-block;
    line-height: 1;
    margin: 0;
    padding: 15px !important;
}

.widget_top-posts .widgets-list-layout li > a {
    width: 40%;
} 
 
.widget_top-posts .widgets-list-layout img.widgets-list-layout-blavatar {
    max-width: 150px;
    width: inherit;
}

.widget_top-posts .widgets-list-layout div.widgets-list-layout-links {
    max-width: 100%;
    width: 55%;
    padding-left: 15px;
    float: left;
}

.widget-title {
	font-size: 22px;
	text-transform: none;
	text-align: center;
	color: #000;
	margin-top: 30px !important;
}

#jp-relatedposts h3.jp-relatedposts-headline {
    font-size: 25px !important;
    font-weight: 400 !important;
		color: #000000;
}

#jp-relatedposts .jp-relatedposts-items-visual .jp-relatedposts-post img.jp-relatedposts-post-img, #jp-relatedposts .jp-relatedposts-items-visual .jp-relatedposts-post span {
    max-width: 100%;
    margin-bottom: 10px;
}

#jp-relatedposts .jp-relatedposts-items-visual .jp-relatedposts-post {
    padding-right: 20px;
    padding-bottom: 10px;
    filter:alpha(opacity=100);
    -moz-opacity: 1;
    opacity: 1 !important;
}

div#jp-relatedposts div.jp-relatedposts-items .jp-relatedposts-post .jp-relatedposts-post-title a:hover {
	color: #4169E1;
	text-decoration: none;
}

div#jp-relatedposts div.jp-relatedposts-items .jp-relatedposts-post:hover .jp-relatedposts-post-title a {
	color: #4169E1;
	text-decoration: none;
}

#jp-relatedposts {
    display: none;
    padding-top: 40px;
    margin: 1em 0;
    position: relative;
    clear: both;
}

#jp-relatedposts .jp-relatedposts-items .jp-relatedposts-post .jp-relatedposts-post-title a {
    font-size: 16px;
		line-height: 1.5;
}

@media only screen and (max-width: 640px) {
	div#jp-relatedposts div.jp-relatedposts-items .jp-relatedposts-post {
		width: 100%;
		float: left;
	}
	
@media only screen and (max-width: 350px) {
	div#jp-relatedposts div.jp-relatedposts-items .jp-relatedposts-post {
		width: 100%;
		clear: both;
		margin: 0 0 1em;
	}
}

	div#jp-relatedposts div.jp-relatedposts-items .jp-relatedposts-post:nth-child(3n+4) {
		clear: none !important;
	}

	div#jp-relatedposts div.jp-relatedposts-items .jp-relatedposts-post:nth-child(3n+5) {
		clear: both;
	}

	div#jp-relatedposts div.jp-relatedposts-items-visual {
		margin-right: 20px;
	}
}

.post-navigation .item-label {
    font-size: 12px;
    font-weight: 600;
		color: #000000;
    text-transform: uppercase;
    opacity: .9;
}

.entry-excerpt {
	font-size: 16px;
}

.entry-title {
		font-size: 20px;
    margin-bottom: 10px !important;
}

.ct-block-title {color: #000000}

.ct-widget {
		margin-top: 0px;
    margin-bottom: 30px;
}

.ct-related-posts .ct-module-title {
   color: black;
}

.entry-card {
		margin: 30px 0px 30px 0px !important;
		padding: 0px 0px 0px 0px !important;
}

.ct-container {
		margin-top: 10px;
}

hr {
    background-color: #ffffff;
}

.ct-post-title {
		font-weight: normal;
		font-size: 14px;
}

.ct-posts-widget ul[data-type=rounded] .ct-image-container, .ct-posts-widget ul[data-type=large-small] .ct-image-container, .ct-posts-widget ul[data-type=small-thumbs] .ct-image-container {
    flex: 0 0 40%;
}

.ct-trending-block .ct-image-container {
    flex: 0 0 100px;
		border-radius: 0%;
}

.entry-content figcaption {
    text-align: left;
}

.ct-related-posts .related-entry-title {
    --fontSize: 16px;
    margin: 10px 0 0;
}

article>.ct-comments, article>.ct-related-posts {
    margin-top: 30px;
    padding-top: 30px;
    border-top: 0px solid var(--border-color);
}

.widgets-list-layout li {
    font-size: 16px;
}

.disclosure {
	margin-top: 30px;
	font-size: 13px;
	font-style: italic;
	text-align: center;
	color: black;
}

.author-box[data-type=type-2] {
    margin-top: 60px;
}

.author-box p {
	text-align: left;
	margin-bottom: 0px;
}

.tiktok-embed {
	background: 000000;
	border-left: none;
	margin-left: 0px !important;
	border: 0px solid !important;
}

.adthrive-ad {
    margin-bottom: 30px !important;
    margin-top: 20px !important;
}

.ct-pagination {
    --spacing: 40px;
}
		</style>
			</head>


<body class="home blog wp-custom-logo wp-embed-responsive wp-theme-blocksy wp-child-theme-laughing-squid" data-link="type-1" data-prefix="blog" data-header="type-1" data-footer="type-1">

<a class="skip-link screen-reader-text" href="#main">Skip to content</a><div class="ct-drawer-canvas" data-location="start">
		<div id="search-modal" class="ct-panel" data-behaviour="modal" role="dialog" aria-label="Search modal" inert>
			<div class="ct-panel-actions">
				<button class="ct-toggle-close" data-type="type-1" aria-label="Close search modal">
					<svg class="ct-icon" width="12" height="12" viewBox="0 0 15 15"><path d="M1 15a1 1 0 01-.71-.29 1 1 0 010-1.41l5.8-5.8-5.8-5.8A1 1 0 011.7.29l5.8 5.8 5.8-5.8a1 1 0 011.41 1.41l-5.8 5.8 5.8 5.8a1 1 0 01-1.41 1.41l-5.8-5.8-5.8 5.8A1 1 0 011 15z"/></svg>				</button>
			</div>

			<div class="ct-panel-content">
				

<form role="search" method="get" class="ct-search-form"  action="https://laughingsquid.com/" aria-haspopup="listbox" data-live-results="thumbs">

	<input type="search" class="modal-field" placeholder="Search" value="" name="s" autocomplete="off" title="Search for..." aria-label="Search for...">

	<div class="ct-search-form-controls">
		
		<button type="submit" class="wp-element-button" data-button="icon" aria-label="Search button">
			<svg class="ct-icon ct-search-button-content" aria-hidden="true" width="15" height="15" viewBox="0 0 15 15"><path d="M14.8,13.7L12,11c0.9-1.2,1.5-2.6,1.5-4.2c0-3.7-3-6.8-6.8-6.8S0,3,0,6.8s3,6.8,6.8,6.8c1.6,0,3.1-0.6,4.2-1.5l2.8,2.8c0.1,0.1,0.3,0.2,0.5,0.2s0.4-0.1,0.5-0.2C15.1,14.5,15.1,14,14.8,13.7z M1.5,6.8c0-2.9,2.4-5.2,5.2-5.2S12,3.9,12,6.8S9.6,12,6.8,12S1.5,9.6,1.5,6.8z"/></svg>
			<span class="ct-ajax-loader">
				<svg viewBox="0 0 24 24">
					<circle cx="12" cy="12" r="10" opacity="0.2" fill="none" stroke="currentColor" stroke-miterlimit="10" stroke-width="2"/>

					<path d="m12,2c5.52,0,10,4.48,10,10" fill="none" stroke="currentColor" stroke-linecap="round" stroke-miterlimit="10" stroke-width="2">
						<animateTransform
							attributeName="transform"
							attributeType="XML"
							type="rotate"
							dur="0.6s"
							from="0 12 12"
							to="360 12 12"
							repeatCount="indefinite"
						/>
					</path>
				</svg>
			</span>
		</button>

					<input type="hidden" name="post_type" value="post">
		
		
		

		<input type="hidden" value="03212c65a4" class="ct-live-results-nonce">	</div>

			<div class="screen-reader-text" aria-live="polite" role="status">
			No results		</div>
	
</form>


			</div>
		</div>

		<div id="offcanvas" class="ct-panel ct-header" data-behaviour="modal" role="dialog" aria-label="Offcanvas modal" inert="">
		<div class="ct-panel-actions">
			
			<button class="ct-toggle-close" data-type="type-1" aria-label="Close drawer">
				<svg class="ct-icon" width="12" height="12" viewBox="0 0 15 15"><path d="M1 15a1 1 0 01-.71-.29 1 1 0 010-1.41l5.8-5.8-5.8-5.8A1 1 0 011.7.29l5.8 5.8 5.8-5.8a1 1 0 011.41 1.41l-5.8 5.8 5.8 5.8a1 1 0 01-1.41 1.41l-5.8-5.8-5.8 5.8A1 1 0 011 15z"/></svg>
			</button>
		</div>
		<div class="ct-panel-content" data-device="desktop"><div class="ct-panel-content-inner"></div></div><div class="ct-panel-content" data-device="mobile"><div class="ct-panel-content-inner">
<nav
	class="mobile-menu menu-container"
	data-id="mobile-menu" data-interaction="click" data-toggle-type="type-1" data-submenu-dots="yes"	aria-label="main">

	<ul id="menu-main-1" class=""><li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-51182"><a href="https://laughingsquid.com/what-is-laughing-squid/" class="ct-menu-link" data-wpel-link="internal">About</a></li>
<li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-282062"><a href="https://laughingsquid.com/faq/" class="ct-menu-link" data-wpel-link="internal">FAQ</a></li>
<li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-51185"><a href="https://laughingsquid.us?utm_source=menu" class="ct-menu-link" data-wpel-link="external" target="_blank" rel="external noopener">Hosting</a></li>
<li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-738456"><a href="https://laughingsquid.com/laughing-squid-newsletter/" class="ct-menu-link" data-wpel-link="internal">Newsletter</a></li>
<li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-913746"><a href="https://laughingsquid.com/laughing-squid-social-media/" class="ct-menu-link" data-wpel-link="internal">Socials</a></li>
<li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-665857"><a href="https://laughingsquid.com/how-to-support-laughing-squid/" class="ct-menu-link" data-wpel-link="internal">Support</a></li>
<li class="menu-item menu-item-type-custom menu-item-object-custom menu-item-51183"><a href="https://laughingsquid.com/contact/" class="ct-menu-link" data-wpel-link="internal">Contact</a></li>
</ul></nav>

</div></div></div><div data-block="popup:939527" class="ct-popup" id="ct-popup-939527" data-popup-size="medium" data-popup-position="middle:center" data-popup-overflow="scroll" data-popup-backdrop="no" data-popup-animation="fade-in" data-popup-close-strategy="{&quot;esc&quot;:true,&quot;form_submit&quot;:true}" data-popup-mode="scroll:300px" data-popup-relaunch="custom:43200:129600"><div class="ct-popup-inner"><article id="post-939527" class="post-939527"><button class="ct-toggle-close" data-location="outside" data-type="type-3" aria-label="Close popup">
				<svg class="ct-icon" width="12" height="12" viewBox="0 0 15 15">
				<path d="M1 15a1 1 0 01-.71-.29 1 1 0 010-1.41l5.8-5.8-5.8-5.8A1 1 0 011.7.29l5.8 5.8 5.8-5.8a1 1 0 011.41 1.41l-5.8 5.8 5.8 5.8a1 1 0 01-1.41 1.41l-5.8-5.8-5.8 5.8A1 1 0 011 15z"></path>
				</svg>
				</button><div class="entry-content is-layout-constrained ct-popup-content">
<iframe src="https://embeds.beehiiv.com/6638d477-53d4-466d-8483-c45b47b931ea" data-test-id="beehiiv-embed" width="480" height="320" frameborder="0" scrolling="no" style="border-radius: 4px; border: 2px solid #e5e7eb; margin: 0; background-color: transparent;"></iframe>
</div></article></div></div></div>
<div id="main-container">
	<header id="header" class="ct-header" data-id="type-1"><div data-device="desktop"><div data-row="middle" data-column-set="3"><div class="ct-container"><div data-column="start" data-placements="1"><div data-items="primary">
<div	class="site-branding"
	data-id="logo"		>

			<a href="https://laughingsquid.com/" class="site-logo-container" rel="home" itemprop="url" data-wpel-link="internal"><img width="150" height="150" src="https://laughingsquid.com/wp-content/uploads/2018/03/laughing-squid-menu.png" class="default-logo" alt="Laughing Squid" decoding="async" /></a>	
	</div>

</div></div><div data-column="middle"><div data-items="">
<nav
	id="header-menu-1"
	class="header-menu-1 menu-container"
	data-id="menu" data-interaction="hover"	data-menu="type-1"
	data-dropdown="type-1:simple"	data-stretch			aria-label="main">

	<ul id="menu-main" class="menu"><li id="menu-item-51182" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-51182"><a href="https://laughingsquid.com/what-is-laughing-squid/" class="ct-menu-link" data-wpel-link="internal">About</a></li>
<li id="menu-item-282062" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-282062"><a href="https://laughingsquid.com/faq/" class="ct-menu-link" data-wpel-link="internal">FAQ</a></li>
<li id="menu-item-51185" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-51185"><a href="https://laughingsquid.us?utm_source=menu" class="ct-menu-link" data-wpel-link="external" target="_blank" rel="external noopener">Hosting</a></li>
<li id="menu-item-738456" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-738456"><a href="https://laughingsquid.com/laughing-squid-newsletter/" class="ct-menu-link" data-wpel-link="internal">Newsletter</a></li>
<li id="menu-item-913746" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-913746"><a href="https://laughingsquid.com/laughing-squid-social-media/" class="ct-menu-link" data-wpel-link="internal">Socials</a></li>
<li id="menu-item-665857" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-665857"><a href="https://laughingsquid.com/how-to-support-laughing-squid/" class="ct-menu-link" data-wpel-link="internal">Support</a></li>
<li id="menu-item-51183" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-51183"><a href="https://laughingsquid.com/contact/" class="ct-menu-link" data-wpel-link="internal">Contact</a></li>
</ul></nav>

</div></div><div data-column="end" data-placements="1"><div data-items="primary">
<div class="ct-search-box " data-id="search-input">

	

<form role="search" method="get" class="ct-search-form" data-form-controls="inside" data-taxonomy-filter="false" data-submit-button="icon" action="https://laughingsquid.com/" aria-haspopup="listbox" data-live-results="thumbs">

	<input type="search"  placeholder="Search" value="" name="s" autocomplete="off" title="Search for..." aria-label="Search for...">

	<div class="ct-search-form-controls">
		
		<button type="submit" class="wp-element-button" data-button="inside:icon" aria-label="Search button">
			<svg class="ct-icon ct-search-button-content" aria-hidden="true" width="15" height="15" viewBox="0 0 15 15"><path d="M14.8,13.7L12,11c0.9-1.2,1.5-2.6,1.5-4.2c0-3.7-3-6.8-6.8-6.8S0,3,0,6.8s3,6.8,6.8,6.8c1.6,0,3.1-0.6,4.2-1.5l2.8,2.8c0.1,0.1,0.3,0.2,0.5,0.2s0.4-0.1,0.5-0.2C15.1,14.5,15.1,14,14.8,13.7z M1.5,6.8c0-2.9,2.4-5.2,5.2-5.2S12,3.9,12,6.8S9.6,12,6.8,12S1.5,9.6,1.5,6.8z"/></svg>
			<span class="ct-ajax-loader">
				<svg viewBox="0 0 24 24">
					<circle cx="12" cy="12" r="10" opacity="0.2" fill="none" stroke="currentColor" stroke-miterlimit="10" stroke-width="2"/>

					<path d="m12,2c5.52,0,10,4.48,10,10" fill="none" stroke="currentColor" stroke-linecap="round" stroke-miterlimit="10" stroke-width="2">
						<animateTransform
							attributeName="transform"
							attributeType="XML"
							type="rotate"
							dur="0.6s"
							from="0 12 12"
							to="360 12 12"
							repeatCount="indefinite"
						/>
					</path>
				</svg>
			</span>
		</button>

					<input type="hidden" name="post_type" value="post">
		
		
		

		<input type="hidden" value="03212c65a4" class="ct-live-results-nonce">	</div>

			<div class="screen-reader-text" aria-live="polite" role="status">
			No results		</div>
	
</form>


</div>
</div></div></div></div></div><div data-device="mobile"><div data-row="middle" data-column-set="3"><div class="ct-container"><div data-column="start" data-placements="1"><div data-items="primary">
<button
	class="ct-header-trigger ct-toggle "
	data-toggle-panel="#offcanvas"
	aria-controls="offcanvas"
	data-design="simple"
	data-label="right"
	aria-label="Menu"
	data-id="trigger">

	<span class="ct-label ct-hidden-sm ct-hidden-md ct-hidden-lg" aria-hidden="true">Menu</span>

	<svg
		class="ct-icon"
		width="18" height="14" viewBox="0 0 18 14"
		data-type="type-1"
		aria-hidden="true">

		<rect y="0.00" width="18" height="1.7" rx="1"/>
		<rect y="6.15" width="18" height="1.7" rx="1"/>
		<rect y="12.3" width="18" height="1.7" rx="1"/>
	</svg>
</button>
</div></div><div data-column="middle"><div data-items="">
<div	class="site-branding"
	data-id="logo"		>

			<a href="https://laughingsquid.com/" class="site-logo-container" rel="home" itemprop="url" data-wpel-link="internal"><img width="150" height="150" src="https://laughingsquid.com/wp-content/uploads/2018/03/laughing-squid-menu.png" class="default-logo" alt="Laughing Squid" decoding="async" /></a>	
	</div>

</div></div><div data-column="end" data-placements="1"><div data-items="primary">
<button
	class="ct-header-search ct-toggle "
	data-toggle-panel="#search-modal"
	aria-controls="search-modal"
	aria-label="Search"
	data-label="left"
	data-id="search">

	<span class="ct-label ct-hidden-md ct-hidden-lg" aria-hidden="true">Search</span>

	<svg class="ct-icon" aria-hidden="true" width="15" height="15" viewBox="0 0 15 15"><path d="M14.8,13.7L12,11c0.9-1.2,1.5-2.6,1.5-4.2c0-3.7-3-6.8-6.8-6.8S0,3,0,6.8s3,6.8,6.8,6.8c1.6,0,3.1-0.6,4.2-1.5l2.8,2.8c0.1,0.1,0.3,0.2,0.5,0.2s0.4-0.1,0.5-0.2C15.1,14.5,15.1,14,14.8,13.7z M1.5,6.8c0-2.9,2.4-5.2,5.2-5.2S12,3.9,12,6.8S9.6,12,6.8,12S1.5,9.6,1.5,6.8z"/></svg></button>
</div></div></div></div></div></header>
	<main id="main" class="site-main">

		
<div class="ct-container" data-sidebar="right" data-vertical-spacing="top:bottom">
	<section >
		
<div class="hero-section is-width-constrained" data-type="type-1">
			<header class="entry-header">
			<h1 class="page-title">Laughing Squid</h1><div class="page-description ">a daily dose of unique and curious things</div>		</header>
	</div><div class="entries" data-archive="default" data-layout="simple" data-cards="simple"><article class="entry-card post-988110 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/cat-loves-taking-showers/" aria-label="Rescued Cat Loves Taking Long Hot Showers" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Cat Loves Taking Showers" decoding="async" fetchpriority="high" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/cat-loves-taking-showers/" rel="bookmark" data-wpel-link="internal">Rescued Cat Loves Taking Long Hot Showers</a></h2><div class="entry-excerpt"><p>A rescued cat loves taking long, hot showers whenever she likes and will always sprint to the bathroom when she hears water running.</p>
</div></div></article><article class="entry-card post-987991 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/david-byrne-music-knowledge-test/" aria-label="Testing David Byrne&#8217;s Music Knowledge" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/David-Byrne-Music-Knowledge-Test.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="David Byrne Music Knowledge Test" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/David-Byrne-Music-Knowledge-Test.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/David-Byrne-Music-Knowledge-Test.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/David-Byrne-Music-Knowledge-Test.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/David-Byrne-Music-Knowledge-Test.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/david-byrne-music-knowledge-test/" rel="bookmark" data-wpel-link="internal">Testing David Byrne&#8217;s Music Knowledge</a></h2><div class="entry-excerpt"><p>Track Star's Jack Coyne tested the great David Byrne of Talking Heads on his music knowledge, which he passed with flying colors.</p>
</div></div></article><article class="entry-card post-988085 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/bats-synonymous-with-halloween/" aria-label="How Bats Became Synonymous With Halloween" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Bats-Synonymous-With-Halloween.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Bats Synonymous With Halloween" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Bats-Synonymous-With-Halloween.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Bats-Synonymous-With-Halloween.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Bats-Synonymous-With-Halloween.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Bats-Synonymous-With-Halloween.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/bats-synonymous-with-halloween/" rel="bookmark" data-wpel-link="internal">How Bats Became Synonymous With Halloween</a></h2><div class="entry-excerpt"><p>Dr. Emily Zarka of Monstrum visited North America's largest urban bat colony in Austin to explain why bats became synonymous with Halloween.</p>
</div></div></article><article class="entry-card post-988049 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/drinking-coffee-from-cup-made-of-coffee/" aria-label="Drinking Coffee Out of a Cup Made Out of Coffee" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Drinking-Coffee-From-Cup-Made-of-Coffee.jpeg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Drinking Coffee From Cup Made of Coffee" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Drinking-Coffee-From-Cup-Made-of-Coffee.jpeg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Drinking-Coffee-From-Cup-Made-of-Coffee.jpeg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Drinking-Coffee-From-Cup-Made-of-Coffee.jpeg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Drinking-Coffee-From-Cup-Made-of-Coffee.jpeg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/drinking-coffee-from-cup-made-of-coffee/" rel="bookmark" data-wpel-link="internal">Drinking Coffee Out of a Cup Made Out of Coffee</a></h2><div class="entry-excerpt"><p>High school art and design teacher Luis Giestas drank coffee out of a "disposable" bioplastic cup made from coffee grounds.</p>
</div></div></article><article class="entry-card post-988009 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/bardcord-dont-fear-the-reaper/" aria-label="A Foreboding Bardcore Cover of &#8216;Don&#8217;t Fear the Reaper&#8217;" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Bardcord Dont Fear the Reaper" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/bardcord-dont-fear-the-reaper/" rel="bookmark" data-wpel-link="internal">A Foreboding Bardcore Cover of &#8216;Don&#8217;t Fear the Reaper&#8217;</a></h2><div class="entry-excerpt"><p>Algal the Bard plays a foreboding cover of the Blue Öyster Cult song "Don't Fear the Reaper" on a variety of instruments from the Dark Ages.</p>
</div></div></article><article class="entry-card post-988035 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/colin-farrell-danny-devito-the-penguin/" aria-label="Colin Farrell and Danny DeVito Talk About Playing The Penguin in Two Different &#8216;Batman&#8217; Movies" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Danny-DeVito-Colin-Farrell-The-Penguin.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Danny DeVito Colin Farrell The Penguin" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Danny-DeVito-Colin-Farrell-The-Penguin.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Danny-DeVito-Colin-Farrell-The-Penguin.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Danny-DeVito-Colin-Farrell-The-Penguin.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Danny-DeVito-Colin-Farrell-The-Penguin.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/colin-farrell-danny-devito-the-penguin/" rel="bookmark" data-wpel-link="internal">Colin Farrell and Danny DeVito Talk About Playing The Penguin in Two Different &#8216;Batman&#8217; Movies</a></h2><div class="entry-excerpt"><p>Colin Farrell and Danny DeVito spoke about playing The Penguin in two different "Batman" movies in an episode of 'Actors on Actors'.</p>
</div></div></article><article class="entry-card post-987930 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/spy-octopus-coconut-octopus-self-defense/" aria-label="Robotic Spy Octopus Watches As a Once Helpless Coconut Octopus Becomes an Expert in Self-Defense" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Spy-Octopus-Coconut-Octopus-Self-Defense.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Spy Octopus Coconut Octopus Self Defense" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Spy-Octopus-Coconut-Octopus-Self-Defense.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Spy-Octopus-Coconut-Octopus-Self-Defense.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Spy-Octopus-Coconut-Octopus-Self-Defense.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Spy-Octopus-Coconut-Octopus-Self-Defense.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/spy-octopus-coconut-octopus-self-defense/" rel="bookmark" data-wpel-link="internal">Robotic Spy Octopus Watches As a Once Helpless Coconut Octopus Becomes an Expert in Self-Defense</a></h2><div class="entry-excerpt"><p>In a clip from "Spy in the Wild", a robotic spy octopus looked on proudly as a once helpless cephalopod became an expert in self-defense</p>
</div></div></article><article class="entry-card post-987633 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/bearded-dragon-trying-new-foods/" aria-label="Bearded Dragon Loves to Try New Foods With His Human Except When It Comes to Spinach" data-wpel-link="internal"><img width="768" height="402" src="https://laughingsquid.com/wp-content/uploads/2025/10/Lenny-Bearded-Dragon-Eating.jpeg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Lenny Bearded Dragon Eating" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Lenny-Bearded-Dragon-Eating.jpeg 1200w, https://laughingsquid.com/wp-content/uploads/2025/10/Lenny-Bearded-Dragon-Eating.jpeg?resize=300,157 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Lenny-Bearded-Dragon-Eating.jpeg?resize=768,402 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Lenny-Bearded-Dragon-Eating.jpeg?resize=750,393 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 300/157;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/bearded-dragon-trying-new-foods/" rel="bookmark" data-wpel-link="internal">Bearded Dragon Loves to Try New Foods With His Human Except When It Comes to Spinach</a></h2><div class="entry-excerpt"><p>A funny little bearded dragon named Lenny loves to eat with his human Emily, however he draws the line when it comes to spinach.</p>
</div></div></article><article class="entry-card post-987999 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/skateboarding-down-highest-skate-ramp/" aria-label="Champion Skateboarder Rides Down the World&#8217;s Highest Skate Ramp on the Side of a Building" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/Skateboarder-Ride-Down-Largest-Skate-Ramp.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="Skateboarder Ride Down Largest Skate Ramp" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/Skateboarder-Ride-Down-Largest-Skate-Ramp.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/Skateboarder-Ride-Down-Largest-Skate-Ramp.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/Skateboarder-Ride-Down-Largest-Skate-Ramp.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/Skateboarder-Ride-Down-Largest-Skate-Ramp.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/skateboarding-down-highest-skate-ramp/" rel="bookmark" data-wpel-link="internal">Champion Skateboarder Rides Down the World&#8217;s Highest Skate Ramp on the Side of a Building</a></h2><div class="entry-excerpt"><p>Sandro Diaz rode down the world's highest skate ramp on a sloping building in Puerto Allegro, Brazil that is 88.91 meters (291.73 feet) high.</p>
</div></div></article><article class="entry-card post-987969 post type-post status-publish format-standard has-post-thumbnail hentry category-blog" ><a class="ct-media-container" href="https://laughingsquid.com/disney-skeleton-dance-origins/" aria-label="The Innovative Origins Behind the Spooky 1929 Disney &#8216;Silly Symphonies&#8217; Animation &#8216;The Skeleton Dance&#8217;" data-wpel-link="internal"><img width="768" height="432" src="https://laughingsquid.com/wp-content/uploads/2025/10/The-Skeleton-Dance-Origins.jpg?w=768" class="attachment-medium_large size-medium_large wp-post-image" alt="The Skeleton Dance Origins" decoding="async" srcset="https://laughingsquid.com/wp-content/uploads/2025/10/The-Skeleton-Dance-Origins.jpg 1280w, https://laughingsquid.com/wp-content/uploads/2025/10/The-Skeleton-Dance-Origins.jpg?resize=300,169 300w, https://laughingsquid.com/wp-content/uploads/2025/10/The-Skeleton-Dance-Origins.jpg?resize=768,432 768w, https://laughingsquid.com/wp-content/uploads/2025/10/The-Skeleton-Dance-Origins.jpg?resize=750,422 750w" sizes="(max-width: 768px) 100vw, 768px" style="aspect-ratio: 16/9;" /></a><div class="card-content"><h2 class="entry-title"><a href="https://laughingsquid.com/disney-skeleton-dance-origins/" rel="bookmark" data-wpel-link="internal">The Innovative Origins Behind the Spooky 1929 Disney &#8216;Silly Symphonies&#8217; Animation &#8216;The Skeleton Dance&#8217;</a></h2><div class="entry-excerpt"><p>Dennis West of West of Neverland dove into the origins of the classic 1929 Disney "Silly Symphony" animation "The Skeleton Dance".</p>
</div></div></article></div>
		<nav class="ct-pagination" data-pagination="load_more"  >
			<span aria-current="page" class="page-numbers current">1</span>
<a class="page-numbers" href="https://laughingsquid.com/page/2/" data-wpel-link="internal">2</a>
<a class="page-numbers" href="https://laughingsquid.com/page/3/" data-wpel-link="internal">3</a>
<a class="page-numbers" href="https://laughingsquid.com/page/4/" data-wpel-link="internal">4</a>
<span class="page-numbers dots">&hellip;</span>
<a class="page-numbers" href="https://laughingsquid.com/page/7082/" data-wpel-link="internal">7,082</a><a class="next page-numbers" rel="next" href="https://laughingsquid.com/page/2/" data-wpel-link="internal">Next <svg width="9px" height="9px" viewBox="0 0 15 15" fill="currentColor"><path d="M4.1,15c0.2,0,0.4-0.1,0.6-0.2L11.4,8c0.3-0.3,0.3-0.8,0-1.1L4.8,0.2C4.5-0.1,4-0.1,3.7,0.2C3.4,0.5,3.4,1,3.7,1.3l6.1,6.1l-6.2,6.2c-0.3,0.3-0.3,0.8,0,1.1C3.7,14.9,3.9,15,4.1,15z"/></svg></a>
			<div class="ct-load-more-helper"><button class="wp-element-button ct-load-more">Load More Blog Posts</button><span class="ct-ajax-loader">
				<svg viewBox="0 0 24 24">
					<circle cx="12" cy="12" r="10" opacity="0.2" fill="none" stroke="currentColor" stroke-miterlimit="10" stroke-width="2"/>

					<path d="m12,2c5.52,0,10,4.48,10,10" fill="none" stroke="currentColor" stroke-linecap="round" stroke-miterlimit="10" stroke-width="2">
						<animateTransform
							attributeName="transform"
							attributeType="XML"
							type="rotate"
							dur="0.6s"
							from="0 12 12"
							to="360 12 12"
							repeatCount="indefinite"
						/>
					</path>
				</svg>
			</span><div class="ct-last-page-text">No more posts to load</div></div>
		</nav>	</section>

	<aside class="" data-type="type-1" id="sidebar"><div class="ct-sidebar"><div class="ct-widget is-layout-flow jetpack_widget_social_icons" id="jetpack_widget_social_icons-2">
			<ul class="jetpack-social-widget-list size-large">

				
											<li class="jetpack-social-widget-item">
							<a href="https://www.facebook.com/laughingsquid/" target="_blank" rel="noopener noreferrer external" data-wpel-link="external"><span class="screen-reader-text">Facebook</span><svg class="icon icon-facebook" aria-hidden="true" role="presentation"> <use href="#icon-facebook" xlink:href="#icon-facebook"></use> </svg>							</a>
						</li>
					
				
											<li class="jetpack-social-widget-item">
							<a href="https://bsky.app/profile/laughingsquid.com" target="_blank" rel="noopener noreferrer external" data-wpel-link="external"><span class="screen-reader-text">Bluesky</span><svg class="icon icon-bluesky" aria-hidden="true" role="presentation"> <use href="#icon-bluesky" xlink:href="#icon-bluesky"></use> </svg>							</a>
						</li>
					
				
											<li class="jetpack-social-widget-item">
							<a href="https://www.threads.net/@laughingsquid" target="_blank" rel="noopener noreferrer external" data-wpel-link="external"><span class="screen-reader-text">Threads</span><svg class="icon icon-threads" aria-hidden="true" role="presentation"> <use href="#icon-threads" xlink:href="#icon-threads"></use> </svg>							</a>
						</li>
					
				
											<li class="jetpack-social-widget-item">
							<a href="https://mastodon.social/@laughingsquid" target="_blank" rel="noopener noreferrer external" data-wpel-link="external"><span class="screen-reader-text">Mastodon</span><svg class="icon icon-mastodon" aria-hidden="true" role="presentation"> <use href="#icon-mastodon" xlink:href="#icon-mastodon"></use> </svg>							</a>
						</li>
					
				
			</ul>

			</div><div class="widget_text ct-widget is-layout-flow widget_custom_html" id="custom_html-6"><div class="textwidget custom-html-widget"><div class="disclosure">Our blog posts may contain <a href="https://laughingsquid.com/affiliate-disclosure/" target="_blank" rel="noreferrer noopener external" data-wpel-link="external">affiliate links</a>. If you make a purchase through our site, we may earn a small commission.</div></div></div><div class="ct-widget is-layout-flow widget_top-posts" id="top-posts-2"><h3 class="widget-title">Trending on Laughing Squid</h3><ul class='widgets-list-layout no-grav'>
<li><a href="https://laughingsquid.com/rescued-malnourished-baby-walrus/" title="Malnourished Orphaned Baby Walrus Rescued From a Life of Isolation by Alaska Sanctuary" class="bump-view" data-bump-view="tp" data-wpel-link="internal"><img loading="lazy" width="150" height="150" src="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Baby-Walrus-Drinking.jpg?resize=150%2C150&#038;ssl=1" srcset="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Baby-Walrus-Drinking.jpg?resize=150%2C150&amp;ssl=1 1x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Baby-Walrus-Drinking.jpg?resize=225%2C225&amp;ssl=1 1.5x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Baby-Walrus-Drinking.jpg?resize=300%2C300&amp;ssl=1 2x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Baby-Walrus-Drinking.jpg?resize=450%2C450&amp;ssl=1 3x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Baby-Walrus-Drinking.jpg?resize=600%2C600&amp;ssl=1 4x" alt="Malnourished Orphaned Baby Walrus Rescued From a Life of Isolation by Alaska Sanctuary" data-pin-nopin="true" class="widgets-list-layout-blavatar" /></a><div class="widgets-list-layout-links">
								<a href="https://laughingsquid.com/rescued-malnourished-baby-walrus/" title="Malnourished Orphaned Baby Walrus Rescued From a Life of Isolation by Alaska Sanctuary" class="bump-view" data-bump-view="tp" data-wpel-link="internal">Malnourished Orphaned Baby Walrus Rescued From a Life of Isolation by Alaska Sanctuary</a>
							</div>
							</li><li><a href="https://laughingsquid.com/1970s-horror-movies/" title="The Most Iconic Horror Movies of the 1970s" class="bump-view" data-bump-view="tp" data-wpel-link="internal"><img loading="lazy" width="150" height="150" src="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/1970s-Top-Horror-Movies.jpg?resize=150%2C150&#038;ssl=1" srcset="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/1970s-Top-Horror-Movies.jpg?resize=150%2C150&amp;ssl=1 1x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/1970s-Top-Horror-Movies.jpg?resize=225%2C225&amp;ssl=1 1.5x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/1970s-Top-Horror-Movies.jpg?resize=300%2C300&amp;ssl=1 2x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/1970s-Top-Horror-Movies.jpg?resize=450%2C450&amp;ssl=1 3x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/1970s-Top-Horror-Movies.jpg?resize=600%2C600&amp;ssl=1 4x" alt="The Most Iconic Horror Movies of the 1970s" data-pin-nopin="true" class="widgets-list-layout-blavatar" /></a><div class="widgets-list-layout-links">
								<a href="https://laughingsquid.com/1970s-horror-movies/" title="The Most Iconic Horror Movies of the 1970s" class="bump-view" data-bump-view="tp" data-wpel-link="internal">The Most Iconic Horror Movies of the 1970s</a>
							</div>
							</li><li><a href="https://laughingsquid.com/jetson-one-air-games/" title="Jetson Personal Electric Aerial Vehicles Race Against Each Other in an &#039;Air Games&#039; Showcase" class="bump-view" data-bump-view="tp" data-wpel-link="internal"><img loading="lazy" width="150" height="150" src="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Jetson-ONE-Air-Games.jpg?resize=150%2C150&#038;ssl=1" srcset="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Jetson-ONE-Air-Games.jpg?resize=150%2C150&amp;ssl=1 1x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Jetson-ONE-Air-Games.jpg?resize=225%2C225&amp;ssl=1 1.5x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Jetson-ONE-Air-Games.jpg?resize=300%2C300&amp;ssl=1 2x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Jetson-ONE-Air-Games.jpg?resize=450%2C450&amp;ssl=1 3x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Jetson-ONE-Air-Games.jpg?resize=600%2C600&amp;ssl=1 4x" alt="Jetson Personal Electric Aerial Vehicles Race Against Each Other in an &#039;Air Games&#039; Showcase" data-pin-nopin="true" class="widgets-list-layout-blavatar" /></a><div class="widgets-list-layout-links">
								<a href="https://laughingsquid.com/jetson-one-air-games/" title="Jetson Personal Electric Aerial Vehicles Race Against Each Other in an &#039;Air Games&#039; Showcase" class="bump-view" data-bump-view="tp" data-wpel-link="internal">Jetson Personal Electric Aerial Vehicles Race Against Each Other in an &#039;Air Games&#039; Showcase</a>
							</div>
							</li><li><a href="https://laughingsquid.com/cat-loves-taking-showers/" title="Rescued Cat Loves Taking Long Hot Showers" class="bump-view" data-bump-view="tp" data-wpel-link="internal"><img loading="lazy" width="150" height="150" src="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=150%2C150&#038;ssl=1" srcset="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=150%2C150&amp;ssl=1 1x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=225%2C225&amp;ssl=1 1.5x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=300%2C300&amp;ssl=1 2x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=450%2C450&amp;ssl=1 3x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Cat-Loves-Taking-Showers.jpeg?resize=600%2C600&amp;ssl=1 4x" alt="Rescued Cat Loves Taking Long Hot Showers" data-pin-nopin="true" class="widgets-list-layout-blavatar" /></a><div class="widgets-list-layout-links">
								<a href="https://laughingsquid.com/cat-loves-taking-showers/" title="Rescued Cat Loves Taking Long Hot Showers" class="bump-view" data-bump-view="tp" data-wpel-link="internal">Rescued Cat Loves Taking Long Hot Showers</a>
							</div>
							</li><li><a href="https://laughingsquid.com/bardcord-dont-fear-the-reaper/" title="A Foreboding Bardcore Cover of &#039;Don&#039;t Fear the Reaper&#039;" class="bump-view" data-bump-view="tp" data-wpel-link="internal"><img loading="lazy" width="150" height="150" src="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=150%2C150&#038;ssl=1" srcset="https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=150%2C150&amp;ssl=1 1x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=225%2C225&amp;ssl=1 1.5x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=300%2C300&amp;ssl=1 2x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=450%2C450&amp;ssl=1 3x, https://i0.wp.com/laughingsquid.com/wp-content/uploads/2025/10/Bard-Dont-Fear-the-Reaper-Dark-Ages.jpg?resize=600%2C600&amp;ssl=1 4x" alt="A Foreboding Bardcore Cover of &#039;Don&#039;t Fear the Reaper&#039;" data-pin-nopin="true" class="widgets-list-layout-blavatar" /></a><div class="widgets-list-layout-links">
								<a href="https://laughingsquid.com/bardcord-dont-fear-the-reaper/" title="A Foreboding Bardcore Cover of &#039;Don&#039;t Fear the Reaper&#039;" class="bump-view" data-bump-view="tp" data-wpel-link="internal">A Foreboding Bardcore Cover of &#039;Don&#039;t Fear the Reaper&#039;</a>
							</div>
							</li></ul>
</div></div></aside></div>
	</main>

	<footer id="footer" class="ct-footer" data-id="type-1"><div data-row="middle"><div class="ct-container"><div data-column="socials">
<div
	class="ct-footer-socials"
	data-id="socials">

	
		<div class="ct-social-box" data-color="custom" data-icon-size="custom" data-icons-type="simple" >
			
			
							
				<a href="https://www.facebook.com/laughingsquid/" data-network="facebook" aria-label="Facebook" rel="nofollow external noopener" data-wpel-link="external" target="_blank">
					<span class="ct-icon-container">
					<svg
					width="20px"
					height="20px"
					viewBox="0 0 20 20"
					aria-hidden="true">
						<path d="M20,10.1c0-5.5-4.5-10-10-10S0,4.5,0,10.1c0,5,3.7,9.1,8.4,9.9v-7H5.9v-2.9h2.5V7.9C8.4,5.4,9.9,4,12.2,4c1.1,0,2.2,0.2,2.2,0.2v2.5h-1.3c-1.2,0-1.6,0.8-1.6,1.6v1.9h2.8L13.9,13h-2.3v7C16.3,19.2,20,15.1,20,10.1z"/>
					</svg>
				</span>				</a>
							
				<a href="https://bsky.app/profile/laughingsquid.com" data-network="bluesky" aria-label="Bluesky" rel="nofollow external noopener" data-wpel-link="external" target="_blank">
					<span class="ct-icon-container">
					<svg
					width="20"
					height="20"
					viewBox="0 0 20 20"
					aria-hidden="true">
						<path d="M4.3 2.4C6.6 4.1 9.1 7.6 10 9.5v5c0-.1 0 0-.1.3-.5 1.4-2.3 6.8-6.5 2.5C1.2 15 2.2 12.7 6.3 12c-2.3.4-4.9-.3-5.6-2.8C.5 8.5.1 3.9.1 3.3 0 .1 2.7 1.1 4.3 2.4Zm11.4 0c-2.3 1.7-4.8 5.2-5.7 7.1v5c0-.1 0 0 .1.3.5 1.4 2.3 6.8 6.5 2.5 2.2-2.3 1.2-4.6-2.9-5.3 2.3.4 4.9-.3 5.6-2.8.2-.7.6-5.3.6-5.9 0-3.1-2.7-2.1-4.3-.9Z"/>
					</svg>
				</span>				</a>
							
				<a href="https://www.threads.net/@laughingsquid" data-network="threads" aria-label="Threads" rel="nofollow external noopener" data-wpel-link="external" target="_blank">
					<span class="ct-icon-container">
					<svg
					width="20"
					height="20"
					viewBox="0 0 20 20"
					aria-hidden="true">
						<path d="M10.7 10.2c.5 0 1 .1 1.5.2-.1 1.1-.5 2.2-1.9 2.3-.6 0-1.1-.1-1.5-.5-.2-.2-.3-.4-.3-.9 0-.3.2-.6.5-.8.5-.2 1-.3 1.7-.3zM20 10c0 4.8 0 7.3-1.4 8.6C17.3 20 14.8 20 10 20s-7.3 0-8.6-1.4C0 17.3 0 14.8 0 10c0-4.9 0-7.3 1.4-8.6C2.7 0 5.1 0 10 0c4.9 0 7.3 0 8.6 1.4C20 2.7 20 5.2 20 10zM6.4 5.2c.9-.9 2.1-1.4 3.8-1.4 3.7 0 4.8 2.6 5 3.7l1.3-.3c-.3-1.1-1.6-4.7-6.3-4.7-2 0-3.5.6-4.7 1.8-1.3 1.4-2 3.5-1.9 6.2.1 4.4 2.6 7 6.5 7 3.3 0 5.7-1.9 5.7-4.5 0-1.7-.8-2.9-2.4-3.6-.2-2.4-1.6-3.3-3-3.4-2.2-.1-3 1.4-3.1 1.5l1.1.6s.5-.9 1.9-.8c.6 0 1.5.3 1.7 1.7-1.4-.3-2.8-.1-3.7.4-.6.4-1 1-1.1 1.7-.1.7.1 1.4.6 1.9.6.6 1.5 1 2.5.9 1.7-.1 2.7-1.3 3-3.1.8.5 1.1 1.1 1.1 2.2 0 1.8-1.9 3.2-4.4 3.2-4.6 0-5.2-4-5.2-5.7 0-1.7.2-3.9 1.6-5.3z"/>
					</svg>
				</span>				</a>
							
				<a href="https://mastodon.social/@laughingsquid" data-network="mastodon" aria-label="Mastodon" rel="nofollow external noopener" data-wpel-link="external" target="_blank">
					<span class="ct-icon-container">
					<svg
					width="20px"
					height="20px"
					viewBox="0 0 20 20"
					aria-hidden="true">
						<path d="M19.3 6.6c0-4.3-2.8-5.6-2.8-5.6C13.7-.3 6.3-.3 3.5 1 3.5 1 .7 2.3.7 6.6c0 5.2-.3 11.6 4.7 12.9 1.8.5 3.4.6 4.6.5 2.3-.1 3.5-.8 3.5-.8l-.1-1.6s-1.6.5-3.4.5c-1.8-.1-3.7-.2-4-2.4v-.6c3.8.9 7.1.4 8 .3 2.5-.3 4.7-1.8 5-3.3.4-2.3.3-5.5.3-5.5zM16 12.2h-2.1V7.1c0-2.2-2.9-2.3-2.9.3v2.8H9V7.4c0-2.6-2.9-2.5-2.9-.3v5.1H4c0-5.4-.2-6.6.8-7.8C6 3.1 8.4 3 9.5 4.6l.5.9.5-.9c1.1-1.6 3.5-1.5 4.7-.3 1 1.3.8 2.4.8 7.9z"/>
					</svg>
				</span>				</a>
			
			
					</div>

	</div>

</div><div data-column="text:d2xrsV">
<div
	class="ct-header-text "
	data-id="d2xrsV">
	<div class="entry-content is-layout-flow">
		<p><a href="https://laughingsquid.com/privacy-policy/" data-wpel-link="internal">Privacy Policy</a> | <a href="https://laughingsquid.com/terms-of-service/" data-wpel-link="internal">Terms of Service</a><br /><a href="https://laughingsquid.com/accessibility-statement/" data-wpel-link="internal">Accessibility Statement</a> | <a href="https://laughingsquid.com/affiliate-disclosure/" data-wpel-link="internal">Affiliate Disclosure</a></p>	</div>
</div>
</div><div data-column="copyright">
<div
	class="ct-footer-copyright"
	data-id="copyright">

	<p>Powered by <a href="https://laughingsquid.us/" data-wpel-link="external" target="_blank" rel="external noopener">Laughing Squid Hosting</a> and <a href="https://wpvip.com/" data-wpel-link="external" target="_blank" rel="external noopener">WordPress VIP</a><br />© 1995-2025 Laughing Squid LLC, all rights reserved</p></div>
</div></div></div></footer></div>

<script data-no-optimize="1" data-cfasync="false">(function () {var clsElements = document.querySelectorAll("script[id^='cls-']"); window.adthriveCLS && clsElements && clsElements.length === 0 ? window.adthriveCLS.injectedFromPlugin = false : ""; })();</script><script type="text/javascript" async src="https://embeds.beehiiv.com/attribution.js"></script><script type="speculationrules">
{"prefetch":[{"source":"document","where":{"and":[{"href_matches":"\/*"},{"not":{"href_matches":["\/wp-*.php","\/wp-admin\/*","\/wp-content\/uploads\/*","\/wp-content\/*","\/wp-content\/plugins\/*","\/wp-content\/themes\/laughing-squid\/*","\/wp-content\/themes\/blocksy\/*","\/*\\?(.+)"]}},{"not":{"selector_matches":"a[rel~=\"nofollow\"]"}},{"not":{"selector_matches":".no-prefetch, .no-prefetch a"}}]},"eagerness":"conservative"}]}
</script>
<link rel='stylesheet' id='all-css-0' href='https://laughingsquid.com/_static/??-eJydzDEKwzAMQNELRVEUaD2FnsU4IrixLYFkTG/fZOza8Q//4VBI0pybY+2gpR+5Gb7ZNaYT6DETVtl7YcOR94Pd0CTlWCBf32/MyWzCP0QXBRW7bf8Uvp1X3Sg8aQnLSuEL/c070A==' type='text/css' media='all' />
<script id="ct-scripts-js-extra">
var ct_localizations = {"ajax_url":"https:\/\/laughingsquid.com\/wp-admin\/admin-ajax.php","public_url":"https:\/\/laughingsquid.com\/wp-content\/themes\/blocksy\/static\/bundle\/","rest_url":"https:\/\/laughingsquid.com\/wp-json\/","search_url":"https:\/\/laughingsquid.com\/search\/QUERY_STRING\/","show_more_text":"Show more","more_text":"More","search_live_results":"Search results","search_live_no_results":"No results","search_live_no_result":"No results","search_live_one_result":"You got %s result. Please press Tab to select it.","search_live_many_results":"You got %s results. Please press Tab to select one.","clipboard_copied":"Copied!","clipboard_failed":"Failed to Copy","expand_submenu":"Expand dropdown menu","collapse_submenu":"Collapse dropdown menu","dynamic_js_chunks":[{"id":"blocksy_pro_micro_popups","selector":".ct-popup","url":"https:\/\/laughingsquid.com\/wp-content\/plugins\/blocksy-companion-pro\/framework\/premium\/static\/bundle\/micro-popups.js?ver=2.1.17"},{"id":"blocksy_mega_menu","selector":".menu .ct-ajax-pending","trigger":"slight-mousemove","url":"https:\/\/laughingsquid.com\/wp-content\/plugins\/blocksy-companion-pro\/framework\/premium\/extensions\/mega-menu\/static\/bundle\/main.js?ver=2.1.17","global_data":[{"var":"blocksyMegaMenu","data":{"persistence_key":"blocksy:mega-menu:b855b5"}}]},{"id":"blocksy_sticky_header","selector":"header [data-sticky]","url":"https:\/\/laughingsquid.com\/wp-content\/plugins\/blocksy-companion-pro\/static\/bundle\/sticky.js?ver=2.1.17"}],"dynamic_styles":{"lazy_load":"https:\/\/laughingsquid.com\/wp-content\/themes\/blocksy\/static\/bundle\/non-critical-styles.min.css?ver=2.1.17","search_lazy":"https:\/\/laughingsquid.com\/wp-content\/themes\/blocksy\/static\/bundle\/non-critical-search-styles.min.css?ver=2.1.17","back_to_top":"https:\/\/laughingsquid.com\/wp-content\/themes\/blocksy\/static\/bundle\/back-to-top.min.css?ver=2.1.17"},"dynamic_styles_selectors":[{"selector":".ct-header-cart, #woo-cart-panel","url":"https:\/\/laughingsquid.com\/wp-content\/themes\/blocksy\/static\/bundle\/cart-header-element-lazy.min.css?ver=2.1.17"},{"selector":".flexy","url":"https:\/\/laughingsquid.com\/wp-content\/themes\/blocksy\/static\/bundle\/flexy.min.css?ver=2.1.17"},{"selector":".ct-media-container[data-media-id], .ct-dynamic-media[data-media-id]","url":"https:\/\/laughingsquid.com\/wp-content\/plugins\/blocksy-companion-pro\/framework\/premium\/static\/bundle\/video-lazy.min.css?ver=2.1.17"},{"selector":"#account-modal","url":"https:\/\/laughingsquid.com\/wp-content\/plugins\/blocksy-companion-pro\/static\/bundle\/header-account-modal-lazy.min.css?ver=2.1.17"},{"selector":".ct-header-account","url":"https:\/\/laughingsquid.com\/wp-content\/plugins\/blocksy-companion-pro\/static\/bundle\/header-account-dropdown-lazy.min.css?ver=2.1.17"}]};
</script>
<script type="text/javascript" src="https://laughingsquid.com/wp-content/themes/blocksy/static/bundle/main.js?m=1760875035g" ></script><script id="jetpack-stats-js-before">
_stq = window._stq || [];
_stq.push([ "view", JSON.parse("{\"v\":\"ext\",\"blog\":\"1065188\",\"post\":\"0\",\"tz\":\"-4\",\"srv\":\"laughingsquid.com\",\"arch_home\":\"1\",\"hp\":\"vip\",\"j\":\"1:15.1.1\"}") ]);
_stq.push([ "clickTrackerInit", "1065188", "0" ]);
</script>
<script src="https://stats.wp.com/e-202543.js" id="jetpack-stats-js" defer data-wp-strategy="defer"></script>
<svg style="position: absolute;width: 0;height: 0;overflow: hidden" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
<defs>
<symbol id="icon-500px" viewBox="0 0 24 24">
<path d="M6.94026,15.1412c.00437.01213.108.29862.168.44064a6.55008,6.55008,0,1,0,6.03191-9.09557,6.68654,6.68654,0,0,0-2.58357.51467A8.53914,8.53914,0,0,0,8.21268,8.61344L8.209,8.61725V3.22948l9.0504-.00008c.32934-.0036.32934-.46353.32934-.61466s0-.61091-.33035-.61467L7.47248,2a.43.43,0,0,0-.43131.42692v7.58355c0,.24466.30476.42131.58793.4819.553.11812.68074-.05864.81617-.2457l.018-.02481A10.52673,10.52673,0,0,1,9.32258,9.258a5.35268,5.35268,0,1,1,7.58985,7.54976,5.417,5.417,0,0,1-3.80867,1.56365,5.17483,5.17483,0,0,1-2.69822-.74478l.00342-4.61111a2.79372,2.79372,0,0,1,.71372-1.78792,2.61611,2.61611,0,0,1,1.98282-.89477,2.75683,2.75683,0,0,1,1.95525.79477,2.66867,2.66867,0,0,1,.79656,1.909,2.724,2.724,0,0,1-2.75849,2.748,4.94651,4.94651,0,0,1-.86254-.13719c-.31234-.093-.44519.34058-.48892.48349-.16811.54966.08453.65862.13687.67489a3.75751,3.75751,0,0,0,1.25234.18375,3.94634,3.94634,0,1,0-2.82444-6.742,3.67478,3.67478,0,0,0-1.13028,2.584l-.00041.02323c-.0035.11667-.00579,2.881-.00644,3.78811l-.00407-.00451a6.18521,6.18521,0,0,1-1.0851-1.86092c-.10544-.27856-.34358-.22925-.66857-.12917-.14192.04372-.57386.17677-.47833.489Zm4.65165-1.08338a.51346.51346,0,0,0,.19513.31818l.02276.022a.52945.52945,0,0,0,.3517.18416.24242.24242,0,0,0,.16577-.0611c.05473-.05082.67382-.67812.73287-.738l.69041.68819a.28978.28978,0,0,0,.21437.11032.53239.53239,0,0,0,.35708-.19486c.29792-.30419.14885-.46821.07676-.54751l-.69954-.69975.72952-.73469c.16-.17311.01874-.35708-.12218-.498-.20461-.20461-.402-.25742-.52855-.14083l-.7254.72665-.73354-.73375a.20128.20128,0,0,0-.14179-.05695.54135.54135,0,0,0-.34379.19648c-.22561.22555-.274.38149-.15656.5059l.73374.7315-.72942.73072A.26589.26589,0,0,0,11.59191,14.05782Zm1.59866-9.915A8.86081,8.86081,0,0,0,9.854,4.776a.26169.26169,0,0,0-.16938.22759.92978.92978,0,0,0,.08619.42094c.05682.14524.20779.531.50006.41955a8.40969,8.40969,0,0,1,2.91968-.55484,7.87875,7.87875,0,0,1,3.086.62286,8.61817,8.61817,0,0,1,2.30562,1.49315.2781.2781,0,0,0,.18318.07586c.15529,0,.30425-.15253.43167-.29551.21268-.23861.35873-.4369.1492-.63538a8.50425,8.50425,0,0,0-2.62312-1.694A9.0177,9.0177,0,0,0,13.19058,4.14283ZM19.50945,18.6236h0a.93171.93171,0,0,0-.36642-.25406.26589.26589,0,0,0-.27613.06613l-.06943.06929A7.90606,7.90606,0,0,1,7.60639,18.505a7.57284,7.57284,0,0,1-1.696-2.51537,8.58715,8.58715,0,0,1-.5147-1.77754l-.00871-.04864c-.04939-.25873-.28755-.27684-.62981-.22448-.14234.02178-.5755.088-.53426.39969l.001.00712a9.08807,9.08807,0,0,0,15.406,4.99094c.00193-.00192.04753-.04718.0725-.07436C19.79425,19.16234,19.87422,18.98728,19.50945,18.6236Z" />
</symbol>
<symbol id="icon-amazon" viewBox="0 0 24 24">
<path d="M13.582,8.182C11.934,8.367,9.78,8.49,8.238,9.166c-1.781,0.769-3.03,2.337-3.03,4.644 c0,2.953,1.86,4.429,4.253,4.429c2.02,0,3.125-0.477,4.685-2.065c0.516,0.747,0.685,1.109,1.629,1.894 c0.212,0.114,0.483,0.103,0.672-0.066l0.006,0.006c0.567-0.505,1.599-1.401,2.18-1.888c0.231-0.188,0.19-0.496,0.009-0.754 c-0.52-0.718-1.072-1.303-1.072-2.634V8.305c0-1.876,0.133-3.599-1.249-4.891C15.23,2.369,13.422,2,12.04,2 C9.336,2,6.318,3.01,5.686,6.351C5.618,6.706,5.877,6.893,6.109,6.945l2.754,0.298C9.121,7.23,9.308,6.977,9.357,6.72 c0.236-1.151,1.2-1.706,2.284-1.706c0.584,0,1.249,0.215,1.595,0.738c0.398,0.584,0.346,1.384,0.346,2.061V8.182z M13.049,14.088 c-0.451,0.8-1.169,1.291-1.967,1.291c-1.09,0-1.728-0.83-1.728-2.061c0-2.42,2.171-2.86,4.227-2.86v0.615 C13.582,12.181,13.608,13.104,13.049,14.088z M20.683,19.339C18.329,21.076,14.917,22,11.979,22c-4.118,0-7.826-1.522-10.632-4.057 c-0.22-0.199-0.024-0.471,0.241-0.317c3.027,1.762,6.771,2.823,10.639,2.823c2.608,0,5.476-0.541,8.115-1.66 C20.739,18.62,21.072,19.051,20.683,19.339z M21.336,21.043c-0.194,0.163-0.379,0.076-0.293-0.139 c0.284-0.71,0.92-2.298,0.619-2.684c-0.301-0.386-1.99-0.183-2.749-0.092c-0.23,0.027-0.266-0.173-0.059-0.319 c1.348-0.946,3.555-0.673,3.811-0.356C22.925,17.773,22.599,19.986,21.336,21.043z" />
</symbol>
<symbol id="icon-apple" viewBox="0 0 24 24">
<path d="M20.07,17.586a10.874,10.874,0,0,1-1.075,1.933,9.822,9.822,0,0,1-1.385,1.674,2.687,2.687,0,0,1-1.78.784,4.462,4.462,0,0,1-1.644-.393,4.718,4.718,0,0,0-1.77-.391,4.878,4.878,0,0,0-1.82.391A4.9,4.9,0,0,1,9.021,22a2.53,2.53,0,0,1-1.82-.8A10.314,10.314,0,0,1,5.752,19.46,11.987,11.987,0,0,1,4.22,16.417a11.143,11.143,0,0,1-.643-3.627,6.623,6.623,0,0,1,.87-3.465A5.1,5.1,0,0,1,6.268,7.483a4.9,4.9,0,0,1,2.463-.695,5.8,5.8,0,0,1,1.9.443,6.123,6.123,0,0,0,1.511.444,9.04,9.04,0,0,0,1.675-.523,5.537,5.537,0,0,1,2.277-.4,4.835,4.835,0,0,1,3.788,1.994,4.213,4.213,0,0,0-2.235,3.827,4.222,4.222,0,0,0,1.386,3.181,4.556,4.556,0,0,0,1.385.909q-.167.483-.353.927ZM16.211,2.4a4.267,4.267,0,0,1-1.094,2.8,3.726,3.726,0,0,1-3.1,1.528A3.114,3.114,0,0,1,12,6.347a4.384,4.384,0,0,1,1.16-2.828,4.467,4.467,0,0,1,1.414-1.061A4.215,4.215,0,0,1,16.19,2a3.633,3.633,0,0,1,.021.4Z" />
</symbol>
<symbol id="icon-bandcamp" viewBox="0 0 24 24">
<path d="M15.27 17.289 3 17.289 8.73 6.711 21 6.711 15.27 17.289" />
</symbol>
<symbol id="icon-behance" viewBox="0 0 24 24">
<path d="M7.799,5.698c0.589,0,1.12,0.051,1.606,0.156c0.482,0.102,0.894,0.273,1.241,0.507c0.344,0.235,0.612,0.546,0.804,0.938 c0.188,0.387,0.281,0.871,0.281,1.443c0,0.619-0.141,1.137-0.421,1.551c-0.284,0.413-0.7,0.751-1.255,1.014 c0.756,0.218,1.317,0.601,1.689,1.146c0.374,0.549,0.557,1.205,0.557,1.975c0,0.623-0.12,1.161-0.359,1.612 c-0.241,0.457-0.569,0.828-0.973,1.114c-0.408,0.288-0.876,0.5-1.399,0.637C9.052,17.931,8.514,18,7.963,18H2V5.698H7.799 M7.449,10.668c0.481,0,0.878-0.114,1.192-0.345c0.311-0.228,0.463-0.603,0.463-1.119c0-0.286-0.051-0.523-0.152-0.707 C8.848,8.315,8.711,8.171,8.536,8.07C8.362,7.966,8.166,7.894,7.94,7.854c-0.224-0.044-0.457-0.06-0.697-0.06H4.709v2.874H7.449z M7.6,15.905c0.267,0,0.521-0.024,0.759-0.077c0.243-0.053,0.457-0.137,0.637-0.261c0.182-0.12,0.332-0.283,0.441-0.491 C9.547,14.87,9.6,14.602,9.6,14.278c0-0.633-0.18-1.084-0.533-1.357c-0.356-0.27-0.83-0.404-1.413-0.404H4.709v3.388L7.6,15.905z M16.162,15.864c0.367,0.358,0.897,0.538,1.583,0.538c0.493,0,0.92-0.125,1.277-0.374c0.354-0.248,0.571-0.514,0.654-0.79h2.155 c-0.347,1.072-0.872,1.838-1.589,2.299C19.534,18,18.67,18.23,17.662,18.23c-0.701,0-1.332-0.113-1.899-0.337 c-0.567-0.227-1.041-0.544-1.439-0.958c-0.389-0.415-0.689-0.907-0.904-1.484c-0.213-0.574-0.32-1.21-0.32-1.899 c0-0.666,0.11-1.288,0.329-1.863c0.222-0.577,0.529-1.075,0.933-1.492c0.406-0.42,0.885-0.751,1.444-0.994 c0.558-0.241,1.175-0.363,1.857-0.363c0.754,0,1.414,0.145,1.98,0.44c0.563,0.291,1.026,0.686,1.389,1.181 c0.363,0.493,0.622,1.057,0.783,1.69c0.16,0.632,0.217,1.292,0.171,1.983h-6.428C15.557,14.84,15.795,15.506,16.162,15.864 M18.973,11.184c-0.291-0.321-0.783-0.496-1.384-0.496c-0.39,0-0.714,0.066-0.973,0.2c-0.254,0.132-0.461,0.297-0.621,0.491 c-0.157,0.197-0.265,0.405-0.328,0.628c-0.063,0.217-0.101,0.413-0.111,0.587h3.98C19.478,11.969,19.265,11.509,18.973,11.184z M15.057,7.738h4.985V6.524h-4.985L15.057,7.738z" />
</symbol>
<symbol id="icon-blogger" viewBox="0 0 24 24">
<path d="M14.722,14.019c0,0.361-0.293,0.654-0.654,0.654H9.977c-0.361,0-0.654-0.293-0.654-0.654s0.293-0.654,0.654-0.654h4.091C14.429,13.365,14.722,13.658,14.722,14.019z M9.981,10.698h2.038c0.382,0,0.692-0.31,0.692-0.692c0-0.382-0.31-0.692-0.692-0.692H9.981c-0.382,0-0.692,0.31-0.692,0.692C9.289,10.388,9.599,10.698,9.981,10.698z M21,5v14c0,1.105-0.895,2-2,2H5c-1.105,0-2-0.895-2-2V5c0-1.105,0.895-2,2-2h14C20.105,3,21,3.895,21,5z M17.544,11.39c0-0.398-0.322-0.72-0.72-0.72h-0.607l-0.013,0.001c-0.38,0-0.692-0.295-0.718-0.668l-0.001-0.008c0-1.988-1.611-3.599-3.599-3.599h-1.816c-1.988,0-3.599,1.611-3.599,3.599v3.947c0,1.987,1.611,3.599,3.599,3.599h3.874c1.988,0,3.599-1.611,3.599-3.599L17.544,11.39z" />
</symbol>
<symbol id="icon-bluesky" viewBox="0 0 24 24">
<path d="M21.2 3.3C20.7 3.1 19.8 2.8 17.6 4.3C15.4 6 12.9 9.2 12 11C11.1 9.2 8.6 6 6.3 4.3C4.1 2.7 3.3 3 2.7 3.3C2.1 3.6 2 4.6 2 5.1C2 5.6 2.3 9.8 2.5 10.5C3.2 12.8 5.6 13.6 7.8 13.3C4.5 13.8 1.6 15 5.4 19.2C9.6 23.5 11.1 18.3 11.9 15.6C12.7 18.3 13.6 23.3 18.3 19.2C21.9 15.6 19.3 13.8 16 13.3C18.2 13.5 20.6 12.8 21.3 10.5C21.7 9.8 22 5.7 22 5.1C22 4.6 21.9 3.6 21.2 3.3Z" />
</symbol>
<symbol id="icon-chain" viewBox="0 0 24 24">
<path d="M19.647,16.706a1.134,1.134,0,0,0-.343-.833l-2.549-2.549a1.134,1.134,0,0,0-.833-.343,1.168,1.168,0,0,0-.883.392l.233.226q.2.189.264.264a2.922,2.922,0,0,1,.184.233.986.986,0,0,1,.159.312,1.242,1.242,0,0,1,.043.337,1.172,1.172,0,0,1-1.176,1.176,1.237,1.237,0,0,1-.337-.043,1,1,0,0,1-.312-.159,2.76,2.76,0,0,1-.233-.184q-.073-.068-.264-.264l-.226-.233a1.19,1.19,0,0,0-.4.895,1.134,1.134,0,0,0,.343.833L15.837,19.3a1.13,1.13,0,0,0,.833.331,1.18,1.18,0,0,0,.833-.318l1.8-1.789a1.12,1.12,0,0,0,.343-.821Zm-8.615-8.64a1.134,1.134,0,0,0-.343-.833L8.163,4.7a1.134,1.134,0,0,0-.833-.343,1.184,1.184,0,0,0-.833.331L4.7,6.473a1.12,1.12,0,0,0-.343.821,1.134,1.134,0,0,0,.343.833l2.549,2.549a1.13,1.13,0,0,0,.833.331,1.184,1.184,0,0,0,.883-.38L8.728,10.4q-.2-.189-.264-.264A2.922,2.922,0,0,1,8.28,9.9a.986.986,0,0,1-.159-.312,1.242,1.242,0,0,1-.043-.337A1.172,1.172,0,0,1,9.254,8.079a1.237,1.237,0,0,1,.337.043,1,1,0,0,1,.312.159,2.761,2.761,0,0,1,.233.184q.073.068.264.264l.226.233a1.19,1.19,0,0,0,.4-.895ZM22,16.706a3.343,3.343,0,0,1-1.042,2.488l-1.8,1.789a3.536,3.536,0,0,1-4.988-.025l-2.525-2.537a3.384,3.384,0,0,1-1.017-2.488,3.448,3.448,0,0,1,1.078-2.561l-1.078-1.078a3.434,3.434,0,0,1-2.549,1.078,3.4,3.4,0,0,1-2.5-1.029L3.029,9.794A3.4,3.4,0,0,1,2,7.294,3.343,3.343,0,0,1,3.042,4.806l1.8-1.789A3.384,3.384,0,0,1,7.331,2a3.357,3.357,0,0,1,2.5,1.042l2.525,2.537a3.384,3.384,0,0,1,1.017,2.488,3.448,3.448,0,0,1-1.078,2.561l1.078,1.078a3.551,3.551,0,0,1,5.049-.049l2.549,2.549A3.4,3.4,0,0,1,22,16.706Z" />
</symbol>
<symbol id="icon-codepen" viewBox="0 0 24 24">
<path d="M22.016,8.84c-0.002-0.013-0.005-0.025-0.007-0.037c-0.005-0.025-0.008-0.048-0.015-0.072 c-0.003-0.015-0.01-0.028-0.013-0.042c-0.008-0.02-0.015-0.04-0.023-0.062c-0.007-0.015-0.013-0.028-0.02-0.042 c-0.008-0.02-0.018-0.037-0.03-0.057c-0.007-0.013-0.017-0.027-0.025-0.038c-0.012-0.018-0.023-0.035-0.035-0.052 c-0.01-0.013-0.02-0.025-0.03-0.037c-0.015-0.017-0.028-0.032-0.043-0.045c-0.01-0.012-0.022-0.023-0.035-0.035 c-0.015-0.015-0.032-0.028-0.048-0.04c-0.012-0.01-0.025-0.02-0.037-0.03c-0.005-0.003-0.01-0.008-0.015-0.012l-9.161-6.096 c-0.289-0.192-0.666-0.192-0.955,0L2.359,8.237C2.354,8.24,2.349,8.245,2.344,8.249L2.306,8.277 c-0.017,0.013-0.033,0.027-0.048,0.04C2.246,8.331,2.234,8.342,2.222,8.352c-0.015,0.015-0.028,0.03-0.042,0.047 c-0.012,0.013-0.022,0.023-0.03,0.037C2.139,8.453,2.125,8.471,2.115,8.488C2.107,8.501,2.099,8.514,2.09,8.526 C2.079,8.548,2.069,8.565,2.06,8.585C2.054,8.6,2.047,8.613,2.04,8.626C2.032,8.648,2.025,8.67,2.019,8.69 c-0.005,0.013-0.01,0.027-0.013,0.042C1.999,8.755,1.995,8.778,1.99,8.803C1.989,8.817,1.985,8.828,1.984,8.84 C1.978,8.879,1.975,8.915,1.975,8.954v6.093c0,0.037,0.003,0.075,0.008,0.112c0.002,0.012,0.005,0.025,0.007,0.038 c0.005,0.023,0.008,0.047,0.015,0.072c0.003,0.015,0.008,0.028,0.013,0.04c0.007,0.022,0.013,0.042,0.022,0.063 c0.007,0.015,0.013,0.028,0.02,0.04c0.008,0.02,0.018,0.038,0.03,0.058c0.007,0.013,0.015,0.027,0.025,0.038 c0.012,0.018,0.023,0.035,0.035,0.052c0.01,0.013,0.02,0.025,0.03,0.037c0.013,0.015,0.028,0.032,0.042,0.045 c0.012,0.012,0.023,0.023,0.035,0.035c0.015,0.013,0.032,0.028,0.048,0.04l0.038,0.03c0.005,0.003,0.01,0.007,0.013,0.01 l9.163,6.095C11.668,21.953,11.833,22,12,22c0.167,0,0.332-0.047,0.478-0.144l9.163-6.095l0.015-0.01 c0.013-0.01,0.027-0.02,0.037-0.03c0.018-0.013,0.035-0.028,0.048-0.04c0.013-0.012,0.025-0.023,0.035-0.035 c0.017-0.015,0.03-0.032,0.043-0.045c0.01-0.013,0.02-0.025,0.03-0.037c0.013-0.018,0.025-0.035,0.035-0.052 c0.008-0.013,0.018-0.027,0.025-0.038c0.012-0.02,0.022-0.038,0.03-0.058c0.007-0.013,0.013-0.027,0.02-0.04 c0.008-0.022,0.015-0.042,0.023-0.063c0.003-0.013,0.01-0.027,0.013-0.04c0.007-0.025,0.01-0.048,0.015-0.072 c0.002-0.013,0.005-0.027,0.007-0.037c0.003-0.042,0.007-0.079,0.007-0.117V8.954C22.025,8.915,22.022,8.879,22.016,8.84z M12.862,4.464l6.751,4.49l-3.016,2.013l-3.735-2.492V4.464z M11.138,4.464v4.009l-3.735,2.494L4.389,8.954L11.138,4.464z M3.699,10.562L5.853,12l-2.155,1.438V10.562z M11.138,19.536l-6.749-4.491l3.015-2.011l3.735,2.492V19.536z M12,14.035L8.953,12 L12,9.966L15.047,12L12,14.035z M12.862,19.536v-4.009l3.735-2.492l3.016,2.011L12.862,19.536z M20.303,13.438L18.147,12 l2.156-1.438L20.303,13.438z" />
</symbol>
<symbol id="icon-deviantart" viewBox="0 0 24 24">
<path d="M 18.19 5.636 18.19 2 18.188 2 14.553 2 14.19 2.366 12.474 5.636 11.935 6 5.81 6 5.81 10.994 9.177 10.994 9.477 11.357 5.81 18.363 5.81 22 5.811 22 9.447 22 9.81 21.634 11.526 18.364 12.065 18 18.19 18 18.19 13.006 14.823 13.006 14.523 12.641 18.19 5.636z" />
</symbol>
<symbol id="icon-digg" viewBox="0 0 24 24">
<path d="M4.5,5.4h2.2V16H1V8.5h3.5V5.4L4.5,5.4z M4.5,14.2v-4H3.2v4H4.5z M7.6,8.5V16h2.2V8.5C9.8,8.5,7.6,8.5,7.6,8.5z M7.6,5.4 v2.2h2.2V5.4C9.8,5.4,7.6,5.4,7.6,5.4z M10.7,8.5h5.7v10.1h-5.7v-1.8h3.5V16h-3.5C10.7,16,10.7,8.5,10.7,8.5z M14.2,14.2v-4h-1.3v4 H14.2z M17.3,8.5H23v10.1h-5.7v-1.8h3.5V16h-3.5C17.3,16,17.3,8.5,17.3,8.5z M20.8,14.2v-4h-1.3v4H20.8z" />
</symbol>
<symbol id="icon-discord" viewBox="0 0 24 24">
<path d="M10.227 9.957c-.559 0-1 .48-1 1.063 0 .585.453 1.066 1 1.066.558 0 1-.48 1-1.066.007-.582-.442-1.063-1-1.063zm3.574 0c-.559 0-.996.48-.996 1.063 0 .585.449 1.066.996 1.066.558 0 1-.48 1-1.066 0-.582-.442-1.063-1-1.063zm0 0 M18.563 1.918H5.438c-1.11 0-2.008.879-2.008 1.973v12.957c0 1.093.898 1.972 2.007 1.972h11.11l-.52-1.773 1.254 1.14 1.184 1.075 2.105 1.82V3.891c0-1.094-.898-1.973-2.008-1.973zM14.78 14.434s-.351-.414-.644-.778c1.281-.355 1.773-1.14 1.773-1.14a5.745 5.745 0 0 1-1.129.566c-.488.2-.96.336-1.418.41a7.07 7.07 0 0 1-2.539-.008 8.133 8.133 0 0 1-1.441-.414 6.219 6.219 0 0 1-.715-.324c-.027-.02-.059-.027-.086-.047a.113.113 0 0 1-.039-.031c-.176-.094-.273-.16-.273-.16s.468.765 1.71 1.129c-.293.363-.656.797-.656.797-2.164-.067-2.984-1.457-2.984-1.457 0-3.086 1.41-5.586 1.41-5.586 1.41-1.036 2.75-1.008 2.75-1.008l.098.113c-1.762.5-2.575 1.258-2.575 1.258s.215-.117.579-.277c1.046-.454 1.878-.579 2.222-.606.059-.008.11-.02.168-.02a8.728 8.728 0 0 1 1.977-.019c.933.106 1.93.375 2.949.922 0 0-.773-.719-2.438-1.219l.137-.152s1.34-.028 2.75 1.008c0 0 1.414 2.5 1.414 5.586 0 0-.836 1.39-3 1.457zm0 0" />
</symbol>
<symbol id="icon-dribbble" viewBox="0 0 24 24">
<path d="M12,22C6.486,22,2,17.514,2,12S6.486,2,12,2c5.514,0,10,4.486,10,10S17.514,22,12,22z M20.434,13.369 c-0.292-0.092-2.644-0.794-5.32-0.365c1.117,3.07,1.572,5.57,1.659,6.09C18.689,17.798,20.053,15.745,20.434,13.369z M15.336,19.876c-0.127-0.749-0.623-3.361-1.822-6.477c-0.019,0.006-0.038,0.013-0.056,0.019c-4.818,1.679-6.547,5.02-6.701,5.334 c1.448,1.129,3.268,1.803,5.243,1.803C13.183,20.555,14.311,20.313,15.336,19.876z M5.654,17.724 c0.193-0.331,2.538-4.213,6.943-5.637c0.111-0.036,0.224-0.07,0.337-0.102c-0.214-0.485-0.448-0.971-0.692-1.45 c-4.266,1.277-8.405,1.223-8.778,1.216c-0.003,0.087-0.004,0.174-0.004,0.261C3.458,14.207,4.29,16.21,5.654,17.724z M3.639,10.264 c0.382,0.005,3.901,0.02,7.897-1.041c-1.415-2.516-2.942-4.631-3.167-4.94C5.979,5.41,4.193,7.613,3.639,10.264z M9.998,3.709 c0.236,0.316,1.787,2.429,3.187,5c3.037-1.138,4.323-2.867,4.477-3.085C16.154,4.286,14.17,3.471,12,3.471 C11.311,3.471,10.641,3.554,9.998,3.709z M18.612,6.612C18.432,6.855,17,8.69,13.842,9.979c0.199,0.407,0.389,0.821,0.567,1.237 c0.063,0.148,0.124,0.295,0.184,0.441c2.842-0.357,5.666,0.215,5.948,0.275C20.522,9.916,19.801,8.065,18.612,6.612z" />
</symbol>
<symbol id="icon-dropbox" viewBox="0 0 24 24">
<path d="M12,6.134L6.069,9.797L2,6.54l5.883-3.843L12,6.134z M2,13.054l5.883,3.843L12,13.459L6.069,9.797L2,13.054z M12,13.459 l4.116,3.439L22,13.054l-4.069-3.257L12,13.459z M22,6.54l-5.884-3.843L12,6.134l5.931,3.663L22,6.54z M12.011,14.2l-4.129,3.426 l-1.767-1.153v1.291l5.896,3.539l5.897-3.539v-1.291l-1.769,1.153L12.011,14.2z" />
</symbol>
<symbol id="icon-etsy" viewBox="0 0 24 24">
<path d="M9.16033,4.038c0-.27174.02717-.43478.48913-.43478h6.22283c1.087,0,1.68478.92391,2.11957,2.663l.35326,1.38587h1.05978C19.59511,3.712,19.75815,2,19.75815,2s-2.663.29891-4.23913.29891h-7.962L3.29076,2.163v1.1413L4.731,3.57609c1.00543.19022,1.25.40761,1.33152,1.33152,0,0,.08152,2.71739.08152,7.20109s-.08152,7.17391-.08152,7.17391c0,.81522-.32609,1.11413-1.33152,1.30435l-1.44022.27174V22l4.2663-.13587h7.11957c1.60326,0,5.32609.13587,5.32609.13587.08152-.97826.625-5.40761.70652-5.89674H19.7038L18.644,18.52174c-.84239,1.90217-2.06522,2.038-3.42391,2.038H11.1712c-1.3587,0-2.01087-.54348-2.01087-1.712V12.65217s3.0163,0,3.99457.08152c.76087.05435,1.22283.27174,1.46739,1.33152l.32609,1.413h1.16848l-.08152-3.55978.163-3.587H15.02989l-.38043,1.57609c-.24457,1.03261-.40761,1.22283-1.46739,1.33152-1.38587.13587-4.02174.1087-4.02174.1087Z" />
</symbol>
<symbol id="icon-eventbrite" viewBox="0 0 24 24">
<path d="M18.041,3.931L5.959,3C4.325,3,3,4.325,3,5.959v12.083C3,19.675,4.325,21,5.959,21l12.083-0.931C19.699,19.983,21,18.744,21,17.11V6.89C21,5.256,19.741,4.027,18.041,3.931zM16.933,8.17c-0.082,0.215-0.192,0.432-0.378,0.551c-0.188,0.122-0.489,0.132-0.799,0.132c-1.521,0-3.062-0.048-4.607-0.048c-0.152,0.708-0.304,1.416-0.451,2.128c0.932-0.004,1.873,0.005,2.81,0.005c0.726,0,1.462-0.069,1.586,0.525c0.04,0.189-0.001,0.426-0.052,0.615c-0.105,0.38-0.258,0.676-0.625,0.783c-0.185,0.054-0.408,0.058-0.646,0.058c-1.145,0-2.345,0.017-3.493,0.02c-0.169,0.772-0.328,1.553-0.489,2.333c1.57-0.005,3.067-0.041,4.633-0.058c0.627-0.007,1.085,0.194,1.009,0.85c-0.031,0.262-0.098,0.497-0.211,0.725c-0.102,0.208-0.248,0.376-0.488,0.452c-0.237,0.075-0.541,0.064-0.862,0.078c-0.304,0.014-0.614,0.008-0.924,0.016c-0.309,0.009-0.619,0.022-0.919,0.022c-1.253,0-2.429,0.08-3.683,0.073c-0.603-0.004-1.014-0.249-1.124-0.757c-0.059-0.273-0.018-0.58,0.036-0.841c0.541-2.592,1.083-5.176,1.629-7.763c0.056-0.265,0.114-0.511,0.225-0.714C9.279,7.051,9.534,6.834,9.9,6.735c0.368-0.099,0.883-0.047,1.344-0.047c0.305,0,0.612,0.008,0.914,0.016c0.925,0.026,1.817,0.03,2.747,0.053c0.304,0.007,0.615,0.016,0.915,0.016c0.621,0,1.17,0.073,1.245,0.614C17.104,7.675,17.014,7.954,16.933,8.17z" />
</symbol>
<symbol id="icon-facebook" viewBox="0 0 24 24">
<path d="M12,2C6.5,2,2,6.5,2,12c0,5,3.7,9.1,8.4,9.9v-7H7.9V12h2.5V9.8c0-2.5,1.5-3.9,3.8-3.9c1.1,0,2.2,0.2,2.2,0.2v2.5h-1.3 c-1.2,0-1.6,0.8-1.6,1.6V12h2.8l-0.4,2.9h-2.3v7C18.3,21.1,22,17,22,12C22,6.5,17.5,2,12,2z" />
</symbol>
<symbol id="icon-fediverse" viewBox="0 0 24 24">
<path d="M5.85081 8.88733C5.63868 9.29358 5.30628 9.62442 4.89905 9.83466L10.1241 15.0801L11.3838 14.4417L5.85081 8.88733ZM12.7428 15.8059L11.4831 16.4443L14.1306 19.1022C14.3428 18.6958 14.6752 18.3649 15.0825 18.1547L12.7428 15.8059ZM18.788 10.9628L15.83 12.4619L16.0481 13.857L19.3951 12.1608C19.0742 11.8335 18.8622 11.4151 18.788 10.9628ZM14.1128 13.3322L7.11871 16.8768C7.43963 17.2041 7.65166 17.6225 7.72582 18.0748L14.3309 14.7273L14.1128 13.3322ZM11.8635 4.60095L8.48868 11.1895L9.48512 12.1898L13.0584 5.21403C12.6065 5.13759 12.1892 4.92348 11.8635 4.60095ZM7.61092 12.9031L5.90146 16.2403C6.35333 16.3168 6.77058 16.5309 7.0962 16.8534L8.60729 13.9033L7.61092 12.9031ZM4.87004 9.8493C4.52582 10.0216 4.14278 10.1017 3.75836 10.0817C3.68642 10.0777 3.61473 10.0702 3.54352 10.0593L4.54173 16.444C4.88595 16.2717 5.26899 16.1916 5.65342 16.2116C5.7253 16.2156 5.79694 16.2231 5.86809 16.2341L4.87004 9.8493ZM7.73111 18.1064C7.75395 18.2547 7.76177 18.4049 7.75437 18.5547C7.73734 18.8604 7.65743 19.1592 7.51964 19.4326L13.9033 20.457C13.8805 20.3087 13.8727 20.1585 13.88 20.0087C13.897 19.703 13.977 19.4042 14.1148 19.1308L7.73111 18.1064ZM19.4175 12.1841L16.471 17.9364C16.923 18.0128 17.3403 18.227 17.666 18.5496L20.6124 12.7973C20.1604 12.7208 19.7431 12.5067 19.4175 12.1841ZM15.3989 4.04834C15.1867 4.45466 14.8542 4.78556 14.4469 4.99581L19.01 9.57651C19.2221 9.17019 19.5546 8.83929 19.9619 8.62904L15.3989 4.04834ZM11.234 3.37973L5.46578 6.30295C5.78666 6.63022 5.99866 7.04859 6.07282 7.50088L11.841 4.57753C11.5202 4.25029 11.3082 3.83197 11.234 3.37973ZM14.4364 5.0011C14.0876 5.17976 13.6978 5.26314 13.3064 5.24282C13.2412 5.23884 13.1762 5.23202 13.1116 5.22237L13.6226 8.49422L15.0168 8.71794L14.4364 5.0011ZM13.9196 10.3964L15.1276 18.132C15.4678 17.9652 15.8448 17.888 16.2231 17.9077C16.3011 17.9121 16.3788 17.9207 16.4559 17.9333L15.3138 10.62L13.9196 10.3964ZM6.07692 7.52543C6.10063 7.67596 6.10884 7.82852 6.10141 7.98072C6.08459 8.28399 6.00588 8.5806 5.87013 8.85231L9.1445 9.37821L9.78804 8.12143L6.07692 7.52543ZM11.6889 8.42664L11.0452 9.68356L18.7819 10.9261C18.7596 10.7795 18.7521 10.631 18.7594 10.483C18.7766 10.1755 18.8575 9.87496 18.9968 9.60035L11.6889 8.42664Z" />
<path d="M13.3174 5.04077C14.433 5.10157 15.3867 4.24642 15.4474 3.13079C15.5082 2.01516 14.6531 1.06149 13.5374 1.00073C12.4218 0.93994 11.4682 1.79509 11.4074 2.91072C11.3466 4.02635 12.2018 4.98002 13.3174 5.04077ZM20.8714 12.6241C21.987 12.6848 22.9407 11.8297 23.0015 10.714C23.0623 9.59842 22.2071 8.64478 21.0915 8.58399C19.9759 8.52323 19.0222 9.37838 18.9614 10.494C18.9006 11.6096 19.7558 12.5633 20.8714 12.6241ZM15.992 22.1497C17.1076 22.2105 18.0613 21.3554 18.1221 20.2398C18.1828 19.1241 17.3277 18.1705 16.2121 18.1097C15.0965 18.0489 14.1428 18.9041 14.082 20.0197C14.0212 21.1353 14.8764 22.089 15.992 22.1497ZM5.42232 20.4537C6.53795 20.5144 7.49162 19.6593 7.55238 18.5437C7.61317 17.428 6.75802 16.4744 5.64239 16.4136C4.52677 16.3529 3.5731 17.208 3.51234 18.3236C3.45158 19.4392 4.3067 20.3929 5.42232 20.4537ZM3.76933 9.87973C4.88496 9.94052 5.83863 9.08537 5.89938 7.96974C5.96014 6.85411 5.10503 5.90045 3.98937 5.83969C2.87374 5.77893 1.9201 6.63405 1.85931 7.74967C1.79855 8.8653 2.6537 9.81897 3.76933 9.87973Z" />
</symbol>
<symbol id="icon-feed" viewBox="0 0 24 24">
<path d="M2,8.667V12c5.515,0,10,4.485,10,10h3.333C15.333,14.637,9.363,8.667,2,8.667z M2,2v3.333 c9.19,0,16.667,7.477,16.667,16.667H22C22,10.955,13.045,2,2,2z M4.5,17C3.118,17,2,18.12,2,19.5S3.118,22,4.5,22S7,20.88,7,19.5 S5.882,17,4.5,17z" />
</symbol>
<symbol id="icon-flickr" viewBox="0 0 24 24">
<path d="M6.5,7c-2.75,0-5,2.25-5,5s2.25,5,5,5s5-2.25,5-5S9.25,7,6.5,7z M17.5,7c-2.75,0-5,2.25-5,5s2.25,5,5,5s5-2.25,5-5 S20.25,7,17.5,7z" />
</symbol>
<symbol id="icon-foursquare" viewBox="0 0 24 24">
<path d="M17.573,2c0,0-9.197,0-10.668,0S5,3.107,5,3.805s0,16.948,0,16.948c0,0.785,0.422,1.077,0.66,1.172 c0.238,0.097,0.892,0.177,1.285-0.275c0,0,5.035-5.843,5.122-5.93c0.132-0.132,0.132-0.132,0.262-0.132h3.26 c1.368,0,1.588-0.977,1.732-1.552c0.078-0.318,0.692-3.428,1.225-6.122l0.675-3.368C19.56,2.893,19.14,2,17.573,2z M16.495,7.22 c-0.053,0.252-0.372,0.518-0.665,0.518c-0.293,0-4.157,0-4.157,0c-0.467,0-0.802,0.318-0.802,0.787v0.508 c0,0.467,0.337,0.798,0.805,0.798c0,0,3.197,0,3.528,0s0.655,0.362,0.583,0.715c-0.072,0.353-0.407,2.102-0.448,2.295 c-0.04,0.193-0.262,0.523-0.655,0.523c-0.33,0-2.88,0-2.88,0c-0.523,0-0.683,0.068-1.033,0.503 c-0.35,0.437-3.505,4.223-3.505,4.223c-0.032,0.035-0.063,0.027-0.063-0.015V4.852c0-0.298,0.26-0.648,0.648-0.648 c0,0,8.228,0,8.562,0c0.315,0,0.61,0.297,0.528,0.683L16.495,7.22z" />
</symbol>
<symbol id="icon-ghost" viewBox="0 0 24 24">
<path d="M10.203,20.997H3.005v-3.599h7.198V20.997z M20.995,17.398h-7.193v3.599h7.193V17.398z M20.998,10.2H3v3.599h17.998V10.2zM13.803,3.003H3.005v3.599h10.798V3.003z M21,3.003h-3.599v3.599H21V3.003z" />
</symbol>
<symbol id="icon-github" viewBox="0 0 24 24">
<path d="M12,2C6.477,2,2,6.477,2,12c0,4.419,2.865,8.166,6.839,9.489c0.5,0.09,0.682-0.218,0.682-0.484 c0-0.236-0.009-0.866-0.014-1.699c-2.782,0.602-3.369-1.34-3.369-1.34c-0.455-1.157-1.11-1.465-1.11-1.465 c-0.909-0.62,0.069-0.608,0.069-0.608c1.004,0.071,1.532,1.03,1.532,1.03c0.891,1.529,2.341,1.089,2.91,0.833
c0.091-0.647,0.349-1.086,0.635-1.337c-2.22-0.251-4.555-1.111-4.555-4.943c0-1.091,0.39-1.984,1.03-2.682 C6.546,8.54,6.202,7.524,6.746,6.148c0,0,0.84-0.269,2.75,1.025C10.295,6.95,11.15,6.84,12,6.836 c0.85,0.004,1.705,0.114,2.504,0.336c1.909-1.294,2.748-1.025,2.748-1.025c0.546,1.376,0.202,2.394,0.1,2.646 c0.64,0.699,1.026,1.591,1.026,2.682c0,3.841-2.337,4.687-4.565,4.935c0.359,0.307,0.679,0.917,0.679,1.852 c0,1.335-0.012,2.415-0.012,2.741c0,0.269,0.18,0.579,0.688,0.481C19.138,20.161,22,16.416,22,12C22,6.477,17.523,2,12,2z" /></symbol>
<symbol id="icon-goodreads" viewBox="0 0 24 24">
<path d="M17.3,17.5c-0.2,0.8-0.5,1.4-1,1.9c-0.4,0.5-1,0.9-1.7,1.2C13.9,20.9,13.1,21,12,21c-0.6,0-1.3-0.1-1.9-0.2 c-0.6-0.1-1.1-0.4-1.6-0.7c-0.5-0.3-0.9-0.7-1.2-1.2c-0.3-0.5-0.5-1.1-0.5-1.7h1.5c0.1,0.5,0.2,0.9,0.5,1.2 c0.2,0.3,0.5,0.6,0.9,0.8c0.3,0.2,0.7,0.3,1.1,0.4c0.4,0.1,0.8,0.1,1.2,0.1c1.4,0,2.5-0.4,3.1-1.2c0.6-0.8,1-2,1-3.5v-1.7h0 c-0.4,0.8-0.9,1.4-1.6,1.9c-0.7,0.5-1.5,0.7-2.4,0.7c-1,0-1.9-0.2-2.6-0.5C8.7,15,8.1,14.5,7.7,14c-0.5-0.6-0.8-1.3-1-2.1 c-0.2-0.8-0.3-1.6-0.3-2.5c0-0.9,0.1-1.7,0.4-2.5c0.3-0.8,0.6-1.5,1.1-2c0.5-0.6,1.1-1,1.8-1.4C10.3,3.2,11.1,3,12,3 c0.5,0,0.9,0.1,1.3,0.2c0.4,0.1,0.8,0.3,1.1,0.5c0.3,0.2,0.6,0.5,0.9,0.8c0.3,0.3,0.5,0.6,0.6,1h0V3.4h1.5V15 C17.6,15.9,17.5,16.7,17.3,17.5z M13.8,14.1c0.5-0.3,0.9-0.7,1.3-1.1c0.3-0.5,0.6-1,0.8-1.6c0.2-0.6,0.3-1.2,0.3-1.9 c0-0.6-0.1-1.2-0.2-1.9c-0.1-0.6-0.4-1.2-0.7-1.7c-0.3-0.5-0.7-0.9-1.3-1.2c-0.5-0.3-1.1-0.5-1.9-0.5s-1.4,0.2-1.9,0.5 c-0.5,0.3-1,0.7-1.3,1.2C8.5,6.4,8.3,7,8.1,7.6C8,8.2,7.9,8.9,7.9,9.5c0,0.6,0.1,1.3,0.2,1.9C8.3,12,8.6,12.5,8.9,13 c0.3,0.5,0.8,0.8,1.3,1.1c0.5,0.3,1.1,0.4,1.9,0.4C12.7,14.5,13.3,14.4,13.8,14.1z" />
</symbol>
<symbol id="icon-google" viewBox="0 0 24 24">
<path d="M12.02,10.18v3.72v0.01h5.51c-0.26,1.57-1.67,4.22-5.5,4.22c-3.31,0-6.01-2.75-6.01-6.12s2.7-6.12,6.01-6.12 c1.87,0,3.13,0.8,3.85,1.48l2.84-2.76C16.99,2.99,14.73,2,12.03,2c-5.52,0-10,4.48-10,10s4.48,10,10,10c5.77,0,9.6-4.06,9.6-9.77 c0-0.83-0.11-1.42-0.25-2.05H12.02z" />
</symbol>
<symbol id="icon-instagram" viewBox="0 0 24 24">
<path d="M12,4.622c2.403,0,2.688,0.009,3.637,0.052c0.877,0.04,1.354,0.187,1.671,0.31c0.42,0.163,0.72,0.358,1.035,0.673 c0.315,0.315,0.51,0.615,0.673,1.035c0.123,0.317,0.27,0.794,0.31,1.671c0.043,0.949,0.052,1.234,0.052,3.637 s-0.009,2.688-0.052,3.637c-0.04,0.877-0.187,1.354-0.31,1.671c-0.163,0.42-0.358,0.72-0.673,1.035 c-0.315,0.315-0.615,0.51-1.035,0.673c-0.317,0.123-0.794,0.27-1.671,0.31c-0.949,0.043-1.233,0.052-3.637,0.052 s-2.688-0.009-3.637-0.052c-0.877-0.04-1.354-0.187-1.671-0.31c-0.42-0.163-0.72-0.358-1.035-0.673 c-0.315-0.315-0.51-0.615-0.673-1.035c-0.123-0.317-0.27-0.794-0.31-1.671C4.631,14.688,4.622,14.403,4.622,12 s0.009-2.688,0.052-3.637c0.04-0.877,0.187-1.354,0.31-1.671c0.163-0.42,0.358-0.72,0.673-1.035 c0.315-0.315,0.615-0.51,1.035-0.673c0.317-0.123,0.794-0.27,1.671-0.31C9.312,4.631,9.597,4.622,12,4.622 M12,3 C9.556,3,9.249,3.01,8.289,3.054C7.331,3.098,6.677,3.25,6.105,3.472C5.513,3.702,5.011,4.01,4.511,4.511 c-0.5,0.5-0.808,1.002-1.038,1.594C3.25,6.677,3.098,7.331,3.054,8.289C3.01,9.249,3,9.556,3,12c0,2.444,0.01,2.751,0.054,3.711 c0.044,0.958,0.196,1.612,0.418,2.185c0.23,0.592,0.538,1.094,1.038,1.594c0.5,0.5,1.002,0.808,1.594,1.038 c0.572,0.222,1.227,0.375,2.185,0.418C9.249,20.99,9.556,21,12,21s2.751-0.01,3.711-0.054c0.958-0.044,1.612-0.196,2.185-0.418 c0.592-0.23,1.094-0.538,1.594-1.038c0.5-0.5,0.808-1.002,1.038-1.594c0.222-0.572,0.375-1.227,0.418-2.185 C20.99,14.751,21,14.444,21,12s-0.01-2.751-0.054-3.711c-0.044-0.958-0.196-1.612-0.418-2.185c-0.23-0.592-0.538-1.094-1.038-1.594 c-0.5-0.5-1.002-0.808-1.594-1.038c-0.572-0.222-1.227-0.375-2.185-0.418C14.751,3.01,14.444,3,12,3L12,3z M12,7.378 c-2.552,0-4.622,2.069-4.622,4.622S9.448,16.622,12,16.622s4.622-2.069,4.622-4.622S14.552,7.378,12,7.378z M12,15 c-1.657,0-3-1.343-3-3s1.343-3,3-3s3,1.343,3,3S13.657,15,12,15z M16.804,6.116c-0.596,0-1.08,0.484-1.08,1.08 s0.484,1.08,1.08,1.08c0.596,0,1.08-0.484,1.08-1.08S17.401,6.116,16.804,6.116z" />
</symbol>
<symbol id="icon-linkedin" viewBox="0 0 24 24">
<path d="M19.7,3H4.3C3.582,3,3,3.582,3,4.3v15.4C3,20.418,3.582,21,4.3,21h15.4c0.718,0,1.3-0.582,1.3-1.3V4.3 C21,3.582,20.418,3,19.7,3z M8.339,18.338H5.667v-8.59h2.672V18.338z M7.004,8.574c-0.857,0-1.549-0.694-1.549-1.548 c0-0.855,0.691-1.548,1.549-1.548c0.854,0,1.547,0.694,1.547,1.548C8.551,7.881,7.858,8.574,7.004,8.574z M18.339,18.338h-2.669 v-4.177c0-0.996-0.017-2.278-1.387-2.278c-1.389,0-1.601,1.086-1.601,2.206v4.249h-2.667v-8.59h2.559v1.174h0.037 c0.356-0.675,1.227-1.387,2.526-1.387c2.703,0,3.203,1.779,3.203,4.092V18.338z" />
</symbol>
<symbol id="icon-mail" viewBox="0 0 24 24">
<path d="M20,4H4C2.895,4,2,4.895,2,6v12c0,1.105,0.895,2,2,2h16c1.105,0,2-0.895,2-2V6C22,4.895,21.105,4,20,4z M20,8.236l-8,4.882 L4,8.236V6h16V8.236z" />
</symbol>
<symbol id="icon-mastodon" viewBox="0 0 24 24">
<path d="M20.617 13.92c-.265 1.36-2.37 2.85-4.788 3.14-1.262.15-2.503.288-3.827.228-2.165-.1-3.873-.517-3.873-.517 0 .212.013.412.04.6.28 2.136 2.118 2.264 3.858 2.324 1.756.06 3.32-.433 3.32-.433l.072 1.59s-1.228.658-3.417.78c-1.207.066-2.705-.03-4.45-.493-3.785-1-4.436-5.036-4.536-9.13-.03-1.215-.01-2.36-.01-3.32 0-4.186 2.74-5.413 2.74-5.413 1.384-.635 3.757-.902 6.225-.923h.06c2.467.022 4.842.29 6.225.924 0 0 2.742 1.227 2.742 5.413 0 0 .034 3.09-.383 5.233zm-2.854-4.91v5.07h-2.008V9.16c0-1.037-.436-1.563-1.31-1.563-.964 0-1.447.624-1.447 1.86v2.692h-1.996V9.455c0-1.235-.484-1.86-1.45-1.86-.872 0-1.308.527-1.308 1.564v4.92H6.236V9.01c0-1.034.263-1.858.793-2.467.546-.61 1.26-.92 2.15-.92 1.027 0 1.805.394 2.32 1.184l.5.84.5-.84c.514-.79 1.292-1.185 2.32-1.185.888 0 1.604.312 2.15.92.53.61.793 1.434.793 2.47z" />
</symbol>
<symbol id="icon-medium" viewBox="0 0 24 24">
<path d="M5.727 8.027a.623.623 0 0 0-.204-.527L4.02 5.687v-.273H8.69l3.614 7.926 3.175-7.926h4.457v.274l-1.285 1.234a.367.367 0 0 0-.144.36v9.066a.374.374 0 0 0 .144.363l1.258 1.234v.27h-6.324v-.27l1.3-1.265c.13-.13.13-.164.13-.36V8.988l-3.621 9.196h-.489L6.691 8.988v6.164c-.035.258.051.52.235.707l1.691 2.055v.27h-4.8v-.27l1.69-2.055a.814.814 0 0 0 .22-.707zm0 0" />
</symbol>
<symbol id="icon-meetup" viewBox="0 0 24 24">
<path d="M19.24775,14.722a3.57032,3.57032,0,0,1-2.94457,3.52073,3.61886,3.61886,0,0,1-.64652.05634c-.07314-.0008-.10187.02846-.12507.09547A2.38881,2.38881,0,0,1,13.49453,20.094a2.33092,2.33092,0,0,1-1.827-.50716.13635.13635,0,0,0-.19878-.00408,3.191,3.191,0,0,1-2.104.60248,3.26309,3.26309,0,0,1-3.00324-2.71993,2.19076,2.19076,0,0,1-.03512-.30865c-.00156-.08579-.03413-.1189-.11608-.13493a2.86421,2.86421,0,0,1-1.23189-.56111,2.945,2.945,0,0,1-1.166-2.05749,2.97484,2.97484,0,0,1,.87524-2.50774.112.112,0,0,0,.02091-.16107,2.7213,2.7213,0,0,1-.36648-1.48A2.81256,2.81256,0,0,1,6.57673,7.58838a.35764.35764,0,0,0,.28869-.22819,4.2208,4.2208,0,0,1,6.02892-1.90111.25161.25161,0,0,0,.22023.0243,3.65608,3.65608,0,0,1,3.76031.90678A3.57244,3.57244,0,0,1,17.95918,8.626a2.97339,2.97339,0,0,1,.01829.57356.10637.10637,0,0,0,.0853.12792,1.97669,1.97669,0,0,1,1.27939,1.33733,2.00266,2.00266,0,0,1-.57112,2.12652c-.05284.05166-.04168.08328-.01173.13489A3.51189,3.51189,0,0,1,19.24775,14.722Zm-6.35959-.27836a1.6984,1.6984,0,0,0,1.14556,1.61113,3.82039,3.82039,0,0,0,1.036.17935,1.46888,1.46888,0,0,0,.73509-.12255.44082.44082,0,0,0,.26057-.44274.45312.45312,0,0,0-.29211-.43375.97191.97191,0,0,0-.20678-.063c-.21326-.03806-.42754-.0701-.63973-.11215a.54787.54787,0,0,1-.50172-.60926,2.75864,2.75864,0,0,1,.1773-.901c.1763-.535.414-1.045.64183-1.55913A12.686,12.686,0,0,0,15.85,10.47863a1.58461,1.58461,0,0,0,.04861-.87208,1.04531,1.04531,0,0,0-.85432-.83981,1.60658,1.60658,0,0,0-1.23654.16594.27593.27593,0,0,1-.36286-.03413c-.085-.0747-.16594-.15379-.24918-.23055a.98682.98682,0,0,0-1.33577-.04933,6.1468,6.1468,0,0,1-.4989.41615.47762.47762,0,0,1-.51535.03566c-.17448-.09307-.35512-.175-.53531-.25665a1.74949,1.74949,0,0,0-.56476-.2016,1.69943,1.69943,0,0,0-1.61654.91787,8.05815,8.05815,0,0,0-.32952.80126c-.45471,1.2557-.82507,2.53825-1.20838,3.81639a1.24151,1.24151,0,0,0,.51532,1.44389,1.42659,1.42659,0,0,0,1.22008.17166,1.09728,1.09728,0,0,0,.66994-.69764c.44145-1.04111.839-2.09989,1.25981-3.14926.11581-.28876.22792-.57874.35078-.86438a.44548.44548,0,0,1,.69189-.19539.50521.50521,0,0,1,.15044.43836,1.75625,1.75625,0,0,1-.14731.50453c-.27379.69219-.55265,1.38236-.82766,2.074a2.0836,2.0836,0,0,0-.14038.42876.50719.50719,0,0,0,.27082.57722.87236.87236,0,0,0,.66145.02739.99137.99137,0,0,0,.53406-.532q.61571-1.20914,1.228-2.42031.28423-.55863.57585-1.1133a.87189.87189,0,0,1,.29055-.35253.34987.34987,0,0,1,.37634-.01265.30291.30291,0,0,1,.12434.31459.56716.56716,0,0,1-.04655.1915c-.05318.12739-.10286.25669-.16183.38156-.34118.71775-.68754,1.43273-1.02568,2.152A2.00213,2.00213,0,0,0,12.88816,14.44366Zm4.78568,5.28972a.88573.88573,0,0,0-1.77139.00465.8857.8857,0,0,0,1.77139-.00465Zm-14.83838-7.296a.84329.84329,0,1,0,.00827-1.68655.8433.8433,0,0,0-.00827,1.68655Zm10.366-9.43673a.83506.83506,0,1,0-.0091,1.67.83505.83505,0,0,0,.0091-1.67Zm6.85014,5.22a.71651.71651,0,0,0-1.433.0093.71656.71656,0,0,0,1.433-.0093ZM5.37528,6.17908A.63823.63823,0,1,0,6.015,5.54483.62292.62292,0,0,0,5.37528,6.17908Zm6.68214,14.80843a.54949.54949,0,1,0-.55052.541A.54556.54556,0,0,0,12.05742,20.98752Zm8.53235-8.49689a.54777.54777,0,0,0-.54027.54023.53327.53327,0,0,0,.532.52293.51548.51548,0,0,0,.53272-.5237A.53187.53187,0,0,0,20.58977,12.49063ZM7.82846,2.4715a.44927.44927,0,1,0,.44484.44766A.43821.43821,0,0,0,7.82846,2.4715Zm13.775,7.60492a.41186.41186,0,0,0-.40065.39623.40178.40178,0,0,0,.40168.40168A.38994.38994,0,0,0,22,10.48172.39946.39946,0,0,0,21.60349,10.07642ZM5.79193,17.96207a.40469.40469,0,0,0-.397-.39646.399.399,0,0,0-.396.405.39234.39234,0,0,0,.39939.389A.39857.39857,0,0,0,5.79193,17.96207Z" />
</symbol>
<symbol id="icon-nextdoor" viewBox="0 0 24 24">
<path d="M11.8615 0.651877C6.11188 0.714092 1.22843 5.12326 0.698031 10.9732C0.132369 17.213 4.73317 22.7304 10.9732 23.2962C17.213 23.8619 22.7304 19.2611 23.2962 13.0211C23.8619 6.78111 19.2611 1.26369 13.0211 0.69803C12.6356 0.663073 12.2486 0.647668 11.8615 0.651877ZM12.5886 7.09625C15.2249 7.09625 17.2615 8.96861 17.2615 11.3538V16.3385C17.2615 16.4649 17.1572 16.5692 17.0308 16.5692H14.9365C14.8755 16.5684 14.8173 16.5438 14.7742 16.5007C14.7311 16.4576 14.7065 16.3994 14.7057 16.3385V11.7C14.7057 10.6698 13.9102 9.49606 12.5884 9.49606C11.2093 9.49606 10.4712 10.6698 10.4712 11.7V16.3385C10.4712 16.4649 10.3669 16.5692 10.2404 16.5692H8.14615C8.02062 16.5692 7.92111 16.464 7.92111 16.3385V11.8442C7.92111 11.7076 7.82345 11.5924 7.69034 11.5615C5.26634 11.0206 4.89988 9.66277 4.85188 7.66154C4.85095 7.60025 4.87809 7.53785 4.92111 7.49428C4.96412 7.45052 5.02135 7.42505 5.08265 7.42505L7.24043 7.43649C7.36228 7.43834 7.45957 7.53415 7.46529 7.65581C7.48929 8.47551 7.54615 9.39231 8.28462 9.39231C8.43785 9.39231 8.55102 9.17464 8.61932 9.07495C9.43348 7.87864 10.8864 7.09625 12.5886 7.09625Z" />
</symbol>
<symbol id="icon-patreon" viewBox="0 0 24 24">
<path d="M20 7.40755C19.9969 5.10922 18.2543 3.22555 16.2097 2.54588C13.6708 1.70188 10.3222 1.82421 7.89775 2.99921C4.95932 4.42355 4.03626 7.54355 4.00186 10.6552C3.97363 13.2136 4.2222 19.9517 7.92225 19.9997C10.6715 20.0356 11.0809 16.3967 12.3529 14.6442C13.258 13.3974 14.4233 13.0452 15.8578 12.6806C18.3233 12.0537 20.0036 10.0551 20 7.40755Z" />
</symbol>
<symbol id="icon-pinterest" viewBox="0 0 24 24">
<path d="M12.289,2C6.617,2,3.606,5.648,3.606,9.622c0,1.846,1.025,4.146,2.666,4.878c0.25,0.111,0.381,0.063,0.439-0.169 c0.044-0.175,0.267-1.029,0.365-1.428c0.032-0.128,0.017-0.237-0.091-0.362C6.445,11.911,6.01,10.75,6.01,9.668 c0-2.777,2.194-5.464,5.933-5.464c3.23,0,5.49,2.108,5.49,5.122c0,3.407-1.794,5.768-4.13,5.768c-1.291,0-2.257-1.021-1.948-2.277 c0.372-1.495,1.089-3.112,1.089-4.191c0-0.967-0.542-1.775-1.663-1.775c-1.319,0-2.379,1.309-2.379,3.059 c0,1.115,0.394,1.869,0.394,1.869s-1.302,5.279-1.54,6.261c-0.405,1.666,0.053,4.368,0.094,4.604 c0.021,0.126,0.167,0.169,0.25,0.063c0.129-0.165,1.699-2.419,2.142-4.051c0.158-0.59,0.817-2.995,0.817-2.995 c0.43,0.784,1.681,1.446,3.013,1.446c3.963,0,6.822-3.494,6.822-7.833C20.394,5.112,16.849,2,12.289,2" />
</symbol>
<symbol id="icon-pocket" viewBox="0 0 24 24">
<path d="M21.927,4.194C21.667,3.48,20.982,3,20.222,3h-0.01h-1.721H3.839C3.092,3,2.411,3.47,2.145,4.17 C2.066,4.378,2.026,4.594,2.026,4.814v6.035l0.069,1.2c0.29,2.73,1.707,5.115,3.899,6.778c0.039,0.03,0.079,0.059,0.119,0.089 l0.025,0.018c1.175,0.859,2.491,1.441,3.91,1.727c0.655,0.132,1.325,0.2,1.991,0.2c0.615,0,1.232-0.057,1.839-0.17 c0.073-0.014,0.145-0.028,0.219-0.044c0.02-0.004,0.042-0.012,0.064-0.023c1.359-0.297,2.621-0.864,3.753-1.691l0.025-0.018 c0.04-0.029,0.08-0.058,0.119-0.089c2.192-1.664,3.609-4.049,3.898-6.778l0.069-1.2V4.814C22.026,4.605,22,4.398,21.927,4.194z M17.692,10.481l-4.704,4.512c-0.266,0.254-0.608,0.382-0.949,0.382c-0.342,0-0.684-0.128-0.949-0.382l-4.705-4.512 C5.838,9.957,5.82,9.089,6.344,8.542c0.524-0.547,1.392-0.565,1.939-0.04l3.756,3.601l3.755-3.601 c0.547-0.524,1.415-0.506,1.939,0.04C18.256,9.089,18.238,9.956,17.692,10.481z" />
</symbol>
<symbol id="icon-ravelry" viewBox="0 0 23 20">
<path d="M12.098 19.34a.25.25 0 01-.118-.043 13.986 13.986 0 01-.394-.258c-.164-.11-.477-.352-.934-.723-.46-.375-.882-.761-1.27-1.168-.39-.406-.796-.925-1.218-1.562a8.521 8.521 0 01-.976-1.926c-.125-.023-.758-.16-1.907-.414A8.785 8.785 0 007.84 17.29a8.152 8.152 0 004.258 2.05zm-6.98-6.762l1.831.313A13.424 13.424 0 016.5 11.02a16.216 16.216 0 01-.207-1.622l-.043-.593c-.61.61-1.047 1.445-1.316 2.5.035.484.097.91.183 1.273zm1.198-6.797a9.064 9.064 0 00-.84 1.653c.32-.344.59-.598.81-.758zm15.649 4.844a8.8 8.8 0 00-.676-3.426 8.85 8.85 0 00-1.824-2.812 8.614 8.614 0 00-2.727-1.883 8.115 8.115 0 00-3.312-.695 8.131 8.131 0 00-3.059.586A8.412 8.412 0 007.754 4.05c-.219.433-.383 1.027-.488 1.785a5.407 5.407 0 011.554-.93 7.481 7.481 0 011.727-.48 16.642 16.642 0 011.558-.153c.489-.02.883-.015 1.18.012l.438.035c.238.008.43.063.574.172a.66.66 0 01.27.367c.03.141.054.278.07.414a.8.8 0 01-.012.317 12.781 12.781 0 00-2.477-.004 7.093 7.093 0 00-1.992.484 9.6 9.6 0 00-1.554.801A12.46 12.46 0 007.176 7.97c.031.27.07.613.125 1.031.054.422.183 1.082.386 1.988.204.903.43 1.57.676 2.004.895.043 1.793-.012 2.696-.164.902-.152 1.683-.351 2.336-.598a20.681 20.681 0 001.77-.746c.526-.254.925-.472 1.19-.66l.407-.265c.156-.121.3-.196.43-.23a.367.367 0 01.331.058c.094.07.157.199.184.383.102.722-.039 1.171-.426 1.351-1.508.723-3.203 1.219-5.086 1.496-.976.149-2.129.207-3.449.176a7.673 7.673 0 001.195 1.973c.504.597 1 1.07 1.493 1.418.496.343.968.636 1.421.878.454.243.825.407 1.106.489l.426.133c1.039.171 1.992.113 2.863-.168 1.414-.739 2.555-1.813 3.418-3.227.867-1.414 1.297-2.969 1.297-4.664zm.805-.414c-.102 1.004-.247 1.793-.434 2.367-.508 1.547-1.168 2.836-1.977 3.867-.808 1.032-1.964 1.973-3.468 2.828-.348.247-.645.41-.895.493-.52.195-1.113.254-1.773.18-.262.019-.528.03-.797.03-2.055 0-3.883-.64-5.492-1.93-1.61-1.288-2.68-2.929-3.22-4.933-.007 0-.019 0-.042-.004-.024-.004-.04-.007-.055-.007-.043.375-.035.793.028 1.257.062.465.156.891.285 1.282.125.39.254.757.39 1.093.133.34.25.606.344.801l.152.29c.059.09.254.394.586.913a4.327 4.327 0 01-1.355-1.187 5.669 5.669 0 01-.856-1.563 14.087 14.087 0 01-.43-1.531 9.012 9.012 0 01-.19-1.2l-.02-.468c-.035-.016-.16-.059-.367-.137-.207-.078-.383-.148-.528-.203-.144-.054-.336-.133-.578-.226a9.221 9.221 0 01-.625-.282c-.176-.09-.36-.183-.543-.285-.187-.097-.34-.199-.465-.3a1.27 1.27 0 01-.27-.286c.138.075.321.172.548.285.23.118.64.286 1.23.508.594.223 1.121.364 1.586.426l.023-.36c.079-1.109.418-2.187 1.024-3.234A9.226 9.226 0 016.5 4.621c.203-.855.5-1.652.883-2.39.11-.208.226-.376.347-.5.125-.13.305-.247.536-.36 1.148-.55 2.25-.937 3.304-1.16A9.935 9.935 0 0114.86.09c1.136.14 2.25.5 3.34 1.082 1.593.855 2.804 2.105 3.624 3.75.82 1.644 1.137 3.406.946 5.289zm0 0" />
</symbol>
<symbol id="icon-reddit" viewBox="0 0 24 24">
<path d="M22,11.816c0-1.256-1.021-2.277-2.277-2.277c-0.593,0-1.122,0.24-1.526,0.614c-1.481-0.965-3.455-1.594-5.647-1.69 l1.171-3.702l3.18,0.748c0.008,1.028,0.846,1.862,1.876,1.862c1.035,0,1.877-0.842,1.877-1.878c0-1.035-0.842-1.877-1.877-1.877 c-0.769,0-1.431,0.466-1.72,1.13l-3.508-0.826c-0.203-0.047-0.399,0.067-0.46,0.261l-1.35,4.268 c-2.316,0.038-4.411,0.67-5.97,1.671C5.368,9.765,4.853,9.539,4.277,9.539C3.021,9.539,2,10.56,2,11.816 c0,0.814,0.433,1.523,1.078,1.925c-0.037,0.221-0.061,0.444-0.061,0.672c0,3.292,4.011,5.97,8.941,5.97s8.941-2.678,8.941-5.97 c0-0.214-0.02-0.424-0.053-0.632C21.533,13.39,22,12.661,22,11.816z M18.776,4.394c0.606,0,1.1,0.493,1.1,1.1s-0.493,1.1-1.1,1.1 s-1.1-0.494-1.1-1.1S18.169,4.394,18.776,4.394z M2.777,11.816c0-0.827,0.672-1.5,1.499-1.5c0.313,0,0.598,0.103,0.838,0.269 c-0.851,0.676-1.477,1.479-1.812,2.36C2.983,12.672,2.777,12.27,2.777,11.816z M11.959,19.606c-4.501,0-8.164-2.329-8.164-5.193 S7.457,9.22,11.959,9.22s8.164,2.329,8.164,5.193S16.46,19.606,11.959,19.606z M20.636,13.001c-0.326-0.89-0.948-1.701-1.797-2.384 c0.248-0.186,0.55-0.301,0.883-0.301c0.827,0,1.5,0.673,1.5,1.5C21.223,12.299,20.992,12.727,20.636,13.001z M8.996,14.704 c-0.76,0-1.397-0.616-1.397-1.376c0-0.76,0.637-1.397,1.397-1.397c0.76,0,1.376,0.637,1.376,1.397 C10.372,14.088,9.756,14.704,8.996,14.704z M16.401,13.328c0,0.76-0.616,1.376-1.376,1.376c-0.76,0-1.399-0.616-1.399-1.376 c0-0.76,0.639-1.397,1.399-1.397C15.785,11.931,16.401,12.568,16.401,13.328z M15.229,16.708c0.152,0.152,0.152,0.398,0,0.55 c-0.674,0.674-1.727,1.002-3.219,1.002c-0.004,0-0.007-0.002-0.011-0.002c-0.004,0-0.007,0.002-0.011,0.002 c-1.492,0-2.544-0.328-3.218-1.002c-0.152-0.152-0.152-0.398,0-0.55c0.152-0.152,0.399-0.151,0.55,0 c0.521,0.521,1.394,0.775,2.669,0.775c0.004,0,0.007,0.002,0.011,0.002c0.004,0,0.007-0.002,0.011-0.002 c1.275,0,2.148-0.253,2.669-0.775C14.831,16.556,15.078,16.556,15.229,16.708z" />
</symbol>
<symbol id="icon-slideshare" viewBox="0 0 24 24">
<path d="M11.738,10.232a2.142,2.142,0,0,1-.721,1.619,2.556,2.556,0,0,1-3.464,0,2.183,2.183,0,0,1,0-3.243,2.572,2.572,0,0,1,3.464,0A2.136,2.136,0,0,1,11.738,10.232Zm5.7,0a2.15,2.15,0,0,1-.715,1.619,2.563,2.563,0,0,1-3.469,0,2.183,2.183,0,0,1,0-3.243,2.58,2.58,0,0,1,3.469,0A2.144,2.144,0,0,1,17.439,10.232Zm2.555,2.045V4.7a2.128,2.128,0,0,0-.363-1.4,1.614,1.614,0,0,0-1.261-.415H5.742a1.656,1.656,0,0,0-1.278.386A2.246,2.246,0,0,0,4.129,4.7v7.643a8.212,8.212,0,0,0,1,.454q.516.193.92.318a6.847,6.847,0,0,0,.92.21q.516.085.806.125a6.615,6.615,0,0,0,.795.045l.665.006q.16,0,.642-.023t.506-.023a1.438,1.438,0,0,1,1.079.307,1.134,1.134,0,0,0,.114.1,7.215,7.215,0,0,0,.693.579q.079-1.033,1.34-.988.057,0,.415.017l.488.023q.13.006.517.011t.6-.011l.619-.051a5.419,5.419,0,0,0,.693-.1l.7-.153a5.353,5.353,0,0,0,.761-.221q.345-.131.766-.307a8.727,8.727,0,0,0,.818-.392Zm1.851-.057a10.4,10.4,0,0,1-4.225,2.862,6.5,6.5,0,0,1-.261,5.281,3.524,3.524,0,0,1-2.078,1.681,2.452,2.452,0,0,1-2.067-.17,1.915,1.915,0,0,1-.931-1.863l-.011-3.7V16.3l-.279-.068q-.188-.045-.267-.057l-.011,3.839a1.9,1.9,0,0,1-.943,1.863,2.481,2.481,0,0,1-2.078.17,3.519,3.519,0,0,1-2.067-1.7,6.546,6.546,0,0,1-.25-5.258A10.4,10.4,0,0,1,2.152,12.22a.56.56,0,0,1-.045-.715q.238-.3.681.011l.125.079a.767.767,0,0,1,.125.091V3.8a1.987,1.987,0,0,1,.534-1.4,1.7,1.7,0,0,1,1.295-.579H19.141a1.7,1.7,0,0,1,1.295.579,1.985,1.985,0,0,1,.534,1.4v7.882l.238-.17q.443-.307.681-.011a.56.56,0,0,1-.045.715Z" />
</symbol>
<symbol id="icon-sms" viewBox="0 0 24 24">
<path d="M17.696 4C20.069 4 22 5.973 22 8.398v4.357c0 2.04-1.368 3.783-3.261 4.266v4.427l-5.234-4.295h-7.2C3.93 17.153 2 15.18 2 12.755V8.398C2 5.973 3.931 4 6.304 4h11.392ZM7.028 8.515c-.98 0-1.66.562-1.66 1.349-.009.497.322.91.985 1.178l.39.142c.242.097.305.171.305.297 0 .162-.131.251-.442.251s-.76-.135-1.004-.284l-.112.046-.215.868c.359.258.832.364 1.33.364 1.104 0 1.764-.523 1.764-1.333-.008-.574-.305-.956-.954-1.216l-.393-.146c-.266-.108-.341-.181-.341-.287 0-.152.131-.243.387-.243.274 0 .587.093.808.214l.109-.047.214-.837c-.315-.224-.741-.316-1.171-.316Zm10.302 0c-.98 0-1.66.562-1.66 1.349-.008.497.322.91.985 1.178l.39.142c.243.097.305.171.305.297 0 .162-.13.251-.442.251-.311 0-.76-.135-1.004-.284l-.112.046-.215.868c.359.258.832.364 1.33.364 1.104 0 1.764-.523 1.764-1.333-.008-.574-.305-.956-.954-1.216l-.393-.146c-.266-.108-.341-.181-.341-.287 0-.152.131-.243.387-.243.274 0 .587.093.808.214l.109-.047.214-.837c-.316-.224-.741-.316-1.171-.316Zm-3.733 0c-.297 0-.55.066-.78.202l-.144.098a1.823 1.823 0 0 0-.264.247l-.078.095-.027-.077c-.15-.34-.55-.565-1.033-.565l-.169.007a1.363 1.363 0 0 0-.896.42l-.08.09-.038-.363-.075-.067H8.994l-.075.079.024.634c.005.2.008.397.008.604v2.652l.075.075h1.178l.075-.075v-2.269c0-.113.012-.202.042-.274.083-.23.262-.392.496-.392.314 0 .483.267.483.753v2.182l.075.075h1.179l.075-.075v-2.277c0-.097.016-.213.043-.285.077-.224.26-.373.486-.373.33 0 .5.272.5.817v2.118l.074.075h1.179l.075-.075v-2.293c0-1.131-.537-1.763-1.39-1.763Z" />
</symbol>
<symbol id="icon-snapchat" viewBox="0 0 24 24">
<path d="M12.065,2a5.526,5.526,0,0,1,3.132.892A5.854,5.854,0,0,1,17.326,5.4a5.821,5.821,0,0,1,.351,2.33q0,.612-.117,2.487a.809.809,0,0,0,.365.091,1.93,1.93,0,0,0,.664-.176,1.93,1.93,0,0,1,.664-.176,1.3,1.3,0,0,1,.729.234.7.7,0,0,1,.351.6.839.839,0,0,1-.41.7,2.732,2.732,0,0,1-.9.41,3.192,3.192,0,0,0-.9.378.728.728,0,0,0-.41.618,1.575,1.575,0,0,0,.156.56,6.9,6.9,0,0,0,1.334,1.953,5.6,5.6,0,0,0,1.881,1.315,5.875,5.875,0,0,0,1.042.3.42.42,0,0,1,.365.456q0,.911-2.852,1.341a1.379,1.379,0,0,0-.143.507,1.8,1.8,0,0,1-.182.605.451.451,0,0,1-.429.241,5.878,5.878,0,0,1-.807-.085,5.917,5.917,0,0,0-.833-.085,4.217,4.217,0,0,0-.807.065,2.42,2.42,0,0,0-.82.293,6.682,6.682,0,0,0-.755.5q-.351.267-.755.527a3.886,3.886,0,0,1-.989.436A4.471,4.471,0,0,1,11.831,22a4.307,4.307,0,0,1-1.256-.176,3.784,3.784,0,0,1-.976-.436q-.4-.26-.749-.527a6.682,6.682,0,0,0-.755-.5,2.422,2.422,0,0,0-.807-.293,4.432,4.432,0,0,0-.82-.065,5.089,5.089,0,0,0-.853.1,5,5,0,0,1-.762.1.474.474,0,0,1-.456-.241,1.819,1.819,0,0,1-.182-.618,1.411,1.411,0,0,0-.143-.521q-2.852-.429-2.852-1.341a.42.42,0,0,1,.365-.456,5.793,5.793,0,0,0,1.042-.3,5.524,5.524,0,0,0,1.881-1.315,6.789,6.789,0,0,0,1.334-1.953A1.575,1.575,0,0,0,6,12.9a.728.728,0,0,0-.41-.618,3.323,3.323,0,0,0-.9-.384,2.912,2.912,0,0,1-.9-.41.814.814,0,0,1-.41-.684.71.71,0,0,1,.338-.593,1.208,1.208,0,0,1,.716-.241,1.976,1.976,0,0,1,.625.169,2.008,2.008,0,0,0,.69.169.919.919,0,0,0,.416-.091q-.117-1.849-.117-2.474A5.861,5.861,0,0,1,6.385,5.4,5.516,5.516,0,0,1,8.625,2.819,7.075,7.075,0,0,1,12.062,2Z" />
</symbol>
<symbol id="icon-soundcloud" viewBox="0 0 24 24">
<path d="M8.9,16.1L9,14L8.9,9.5c0-0.1,0-0.1-0.1-0.1c0,0-0.1-0.1-0.1-0.1c-0.1,0-0.1,0-0.1,0.1c0,0-0.1,0.1-0.1,0.1L8.3,14l0.1,2.1 c0,0.1,0,0.1,0.1,0.1c0,0,0.1,0.1,0.1,0.1C8.8,16.3,8.9,16.3,8.9,16.1z M11.4,15.9l0.1-1.8L11.4,9c0-0.1,0-0.2-0.1-0.2 c0,0-0.1,0-0.1,0s-0.1,0-0.1,0c-0.1,0-0.1,0.1-0.1,0.2l0,0.1l-0.1,5c0,0,0,0.7,0.1,2v0c0,0.1,0,0.1,0.1,0.1c0.1,0.1,0.1,0.1,0.2,0.1 c0.1,0,0.1,0,0.2-0.1c0.1,0,0.1-0.1,0.1-0.2L11.4,15.9z M2.4,12.9L2.5,14l-0.2,1.1c0,0.1,0,0.1-0.1,0.1c0,0-0.1,0-0.1-0.1L2.1,14 l0.1-1.1C2.2,12.9,2.3,12.9,2.4,12.9C2.3,12.9,2.4,12.9,2.4,12.9z M3.1,12.2L3.3,14l-0.2,1.8c0,0.1,0,0.1-0.1,0.1 c-0.1,0-0.1,0-0.1-0.1L2.8,14L3,12.2C3,12.2,3,12.2,3.1,12.2C3.1,12.2,3.1,12.2,3.1,12.2z M3.9,11.9L4.1,14l-0.2,2.1 c0,0.1,0,0.1-0.1,0.1c-0.1,0-0.1,0-0.1-0.1L3.5,14l0.2-2.1c0-0.1,0-0.1,0.1-0.1C3.9,11.8,3.9,11.8,3.9,11.9z M4.7,11.9L4.9,14 l-0.2,2.1c0,0.1-0.1,0.1-0.1,0.1c-0.1,0-0.1,0-0.1-0.1L4.3,14l0.2-2.2c0-0.1,0-0.1,0.1-0.1C4.7,11.7,4.7,11.8,4.7,11.9z M5.6,12 l0.2,2l-0.2,2.1c0,0.1-0.1,0.1-0.1,0.1c0,0-0.1,0-0.1,0c0,0,0-0.1,0-0.1L5.1,14l0.2-2c0,0,0-0.1,0-0.1s0.1,0,0.1,0 C5.5,11.9,5.5,11.9,5.6,12L5.6,12z M6.4,10.7L6.6,14l-0.2,2.1c0,0,0,0.1,0,0.1c0,0-0.1,0-0.1,0c-0.1,0-0.1-0.1-0.2-0.2L5.9,14 l0.2-3.3c0-0.1,0.1-0.2,0.2-0.2c0,0,0.1,0,0.1,0C6.4,10.7,6.4,10.7,6.4,10.7z M7.2,10l0.2,4.1l-0.2,2.1c0,0,0,0.1,0,0.1 c0,0-0.1,0-0.1,0c-0.1,0-0.2-0.1-0.2-0.2l-0.1-2.1L6.8,10c0-0.1,0.1-0.2,0.2-0.2c0,0,0.1,0,0.1,0S7.2,9.9,7.2,10z M8,9.6L8.2,14 L8,16.1c0,0.1-0.1,0.2-0.2,0.2c-0.1,0-0.2-0.1-0.2-0.2L7.5,14l0.1-4.4c0-0.1,0-0.1,0.1-0.1c0,0,0.1-0.1,0.1-0.1c0.1,0,0.1,0,0.1,0.1 C8,9.6,8,9.6,8,9.6z M11.4,16.1L11.4,16.1L11.4,16.1z M9.7,9.6L9.8,14l-0.1,2.1c0,0.1,0,0.1-0.1,0.2s-0.1,0.1-0.2,0.1 c-0.1,0-0.1,0-0.1-0.1s-0.1-0.1-0.1-0.2L9.2,14l0.1-4.4c0-0.1,0-0.1,0.1-0.2s0.1-0.1,0.2-0.1c0.1,0,0.1,0,0.2,0.1S9.7,9.5,9.7,9.6 L9.7,9.6z M10.6,9.8l0.1,4.3l-0.1,2c0,0.1,0,0.1-0.1,0.2c0,0-0.1,0.1-0.2,0.1c-0.1,0-0.1,0-0.2-0.1c0,0-0.1-0.1-0.1-0.2L10,14 l0.1-4.3c0-0.1,0-0.1,0.1-0.2c0,0,0.1-0.1,0.2-0.1c0.1,0,0.1,0,0.2,0.1S10.6,9.7,10.6,9.8z M12.4,14l-0.1,2c0,0.1,0,0.1-0.1,0.2 c-0.1,0.1-0.1,0.1-0.2,0.1c-0.1,0-0.1,0-0.2-0.1c-0.1-0.1-0.1-0.1-0.1-0.2l-0.1-1l-0.1-1l0.1-5.5v0c0-0.1,0-0.2,0.1-0.2 c0.1,0,0.1-0.1,0.2-0.1c0,0,0.1,0,0.1,0c0.1,0,0.1,0.1,0.1,0.2L12.4,14z M22.1,13.9c0,0.7-0.2,1.3-0.7,1.7c-0.5,0.5-1.1,0.7-1.7,0.7 h-6.8c-0.1,0-0.1,0-0.2-0.1c-0.1-0.1-0.1-0.1-0.1-0.2V8.2c0-0.1,0.1-0.2,0.2-0.3c0.5-0.2,1-0.3,1.6-0.3c1.1,0,2.1,0.4,2.9,1.1 c0.8,0.8,1.3,1.7,1.4,2.8c0.3-0.1,0.6-0.2,1-0.2c0.7,0,1.3,0.2,1.7,0.7C21.8,12.6,22.1,13.2,22.1,13.9L22.1,13.9z" />
</symbol>
<symbol id="icon-spotify" viewBox="0 0 24 24">
<path d="M12,2C6.477,2,2,6.477,2,12c0,5.523,4.477,10,10,10c5.523,0,10-4.477,10-10C22,6.477,17.523,2,12,2 M16.586,16.424 c-0.18,0.295-0.563,0.387-0.857,0.207c-2.348-1.435-5.304-1.76-8.785-0.964c-0.335,0.077-0.67-0.133-0.746-0.469 c-0.077-0.335,0.132-0.67,0.469-0.746c3.809-0.871,7.077-0.496,9.713,1.115C16.673,15.746,16.766,16.13,16.586,16.424 M17.81,13.7 c-0.226,0.367-0.706,0.482-1.072,0.257c-2.687-1.652-6.785-2.131-9.965-1.166C6.36,12.917,5.925,12.684,5.8,12.273 C5.675,11.86,5.908,11.425,6.32,11.3c3.632-1.102,8.147-0.568,11.234,1.328C17.92,12.854,18.035,13.335,17.81,13.7 M17.915,10.865 c-3.223-1.914-8.54-2.09-11.618-1.156C5.804,9.859,5.281,9.58,5.131,9.086C4.982,8.591,5.26,8.069,5.755,7.919 c3.532-1.072,9.404-0.865,13.115,1.338c0.445,0.264,0.59,0.838,0.327,1.282C18.933,10.983,18.359,11.129,17.915,10.865" />
</symbol>
<symbol id="icon-stackoverflow" viewBox="0 0 24 24">
<path d="m 17.817128,20.228605 v -5.337217 h 1.771431 V 22 H 3.6 v -7.108612 h 1.771401 v 5.337217 z" />
<path d="m 7.3267845,14.385359 8.6959295,1.817316 0.368168,-1.748385 -8.6959318,-1.817319 z m 1.1503197,-4.140944 8.0517968,3.749872 0.73617,-1.610385 -8.0518344,-3.7728517 z m 2.2315078,-3.9569154 6.832405,5.6822664 1.12738,-1.357316 -6.832576,-5.6822636 z m 4.417,-4.2099019 -1.426448,1.0581864 5.291191,7.1316119 1.426412,-1.0582745 z M 7.1427296,18.434189 h 8.8799844 v -1.7713 H 7.1427296 Z" />
<path d="m 17.817128,20.228605 v -5.337217 h 1.771431 V 22 H 3.6 v -7.108612 h 1.771401 v 5.337217 z" />
<path d="m 7.3267845,14.385359 8.6959295,1.817316 0.368168,-1.748385 -8.6959318,-1.817319 z m 1.1503197,-4.140944 8.0517968,3.749872 0.73617,-1.610385 -8.0518344,-3.7728517 z m 2.2315078,-3.9569154 6.832405,5.6822664 1.12738,-1.357316 -6.832576,-5.6822636 z m 4.417,-4.2099019 -1.426448,1.0581864 5.291191,7.1316119 1.426412,-1.0582745 z M 7.1427296,18.434189 h 8.8799844 v -1.7713 H 7.1427296 Z" />
</symbol>
<symbol id="icon-strava" viewBox="0 0 24 24">
<path d="M15.387 17.944l-2.089-4.116h-3.065L15.387 24l5.15-10.172h-3.066m-7.008-5.599l2.836 5.598h4.172L10.463 0l-7 13.828h4.169" />
</symbol>
<symbol id="icon-stumbleupon" viewBox="0 0 24 24">
<path d="M12,4.294c-2.469,0-4.471,2.002-4.471,4.471v6.353c0,0.585-0.474,1.059-1.059,1.059c-0.585,0-1.059-0.474-1.059-1.059 v-2.824H2v2.941c0,2.469,2.002,4.471,4.471,4.471c2.469,0,4.471-2.002,4.471-4.471V8.765c0-0.585,0.474-1.059,1.059-1.059 s1.059,0.474,1.059,1.059v1.294l1.412,0.647l2-0.647V8.765C16.471,6.296,14.469,4.294,12,4.294z M13.059,12.353v2.882 c0,2.469,2.002,4.471,4.471,4.471S22,17.704,22,15.235v-2.824h-3.412v2.824c0,0.585-0.474,1.059-1.059,1.059 c-0.585,0-1.059-0.474-1.059-1.059v-2.882l-2,0.647L13.059,12.353z" />
</symbol>
<symbol id="icon-telegram" viewBox="0 0 24 24">
<path d="M12 2C6.477 2 2 6.477 2 12s4.477 10 10 10 10-4.477 10-10S17.523 2 12 2zm3.08 14.757s-.25.625-.936.325l-2.541-1.949-1.63 1.486s-.127.096-.266.036c0 0-.12-.011-.27-.486-.15-.475-.911-2.972-.911-2.972L6 12.349s-.387-.137-.425-.438c-.037-.3.437-.462.437-.462l10.03-3.934s.824-.362.824.238l-1.786 9.004z" />
</symbol>
<symbol id="icon-threads" viewBox="0 0 24 24">
<path d="M16.0671 11.1235C15.9632 11.0737 15.8583 11.0261 15.7524 10.9806C15.5671 7.56725 13.702 5.61312 10.5702 5.59312H10.5278C8.6545 5.59312 7.09663 6.39262 6.13775 7.84762L7.86012 9.02913C8.57637 7.94225 9.70062 7.71063 10.5286 7.71063H10.5573C11.5884 7.71725 12.3665 8.01713 12.8701 8.60175C13.2366 9.02738 13.4817 9.61562 13.6031 10.358C12.6889 10.2026 11.7001 10.1547 10.6431 10.2155C7.66562 10.3869 5.75138 12.1235 5.88 14.5365C5.94525 15.7605 6.555 16.8135 7.59688 17.5014C8.47775 18.0829 9.61238 18.3673 10.7915 18.3029C12.3488 18.2175 13.5704 17.6234 14.4226 16.537C15.0699 15.712 15.4792 14.6429 15.66 13.2957C16.4021 13.7436 16.9521 14.333 17.2559 15.0415C17.7724 16.2459 17.8025 18.225 16.1876 19.8385C14.7728 21.252 13.072 21.8635 10.5016 21.8824C7.6505 21.8613 5.49412 20.9469 4.09225 19.1646C2.7795 17.4958 2.101 15.0852 2.07562 12C2.101 8.91475 2.77937 6.50425 4.09225 4.83537C5.49425 3.05312 7.6505 2.13875 10.5016 2.1175C13.3735 2.13875 15.5674 3.0575 17.023 4.84837C17.7368 5.72662 18.2749 6.83087 18.6296 8.11862L20.648 7.58012C20.218 5.99512 19.5414 4.62937 18.6206 3.49662C16.7545 1.20088 14.0252 0.024375 10.5087 0H10.4946C6.98525 0.02425 4.2865 1.20525 2.4735 3.51C0.86025 5.56063 0.0280001 8.41437 0.000125051 11.9915L0 12V12.0084C0.028 15.5855 0.86025 18.4393 2.4735 20.4901C4.2865 22.7948 6.98525 23.9757 10.4946 24H10.5087C13.6287 23.9784 15.828 23.1615 17.6397 21.3514C20.0101 18.9833 19.9387 16.0149 19.1575 14.1926C18.597 12.8859 17.5284 11.8245 16.0671 11.1235ZM10.68 16.1884C9.375 16.2619 8.01925 15.6761 7.9525 14.4215C7.90288 13.4913 8.6145 12.4533 10.7601 12.3296C11.0059 12.3154 11.247 12.3085 11.4839 12.3085C12.2633 12.3085 12.9924 12.3843 13.6552 12.5291C13.408 15.6169 11.9578 16.1183 10.68 16.1884Z" />
</symbol>
<symbol id="icon-tiktok" viewBox="0 0 24 24">
<path d="M12.22 2H15.64C15.64 2 15.4502 6.39351 20.3898 6.70186V10.0981C20.3898 10.0981 17.7537 10.2636 15.64 8.64957L15.6769 15.6615C15.6769 16.9151 15.3052 18.1406 14.6087 19.1829C13.9123 20.2253 12.9224 21.0377 11.7642 21.5175C10.606 21.9972 9.33162 22.1228 8.10209 21.8782C6.87257 21.6337 5.74316 21.0301 4.85669 20.1437C3.97022 19.2573 3.3665 18.1279 3.12186 16.8984C2.87723 15.6689 3.00267 14.3945 3.48233 13.2363C3.96199 12.0781 4.77432 11.0881 5.8166 10.3916C6.85888 9.69502 8.0843 9.32318 9.33791 9.32307H10.2271V12.7231V12.7954C9.64757 12.6147 9.02578 12.6217 8.45043 12.8152C7.87508 13.0088 7.37556 13.3792 7.02314 13.8734C6.67071 14.3677 6.48338 14.9606 6.48786 15.5677C6.49235 16.1747 6.68842 16.7648 7.04811 17.2538C7.40781 17.7428 7.91274 18.1057 8.49089 18.2908C9.06903 18.4758 9.69086 18.4736 10.2676 18.2843C10.8444 18.0951 11.3467 17.7285 11.7029 17.2369C12.059 16.7454 12.2508 16.1538 12.2509 15.5468L12.22 2Z" />
</symbol>
<symbol id="icon-tumblr" viewBox="0 0 24 24">
<path d="M16.749,17.396c-0.357,0.17-1.041,0.319-1.551,0.332c-1.539,0.041-1.837-1.081-1.85-1.896V9.847h3.861V6.937h-3.847V2.039 c0,0-2.77,0-2.817,0c-0.046,0-0.127,0.041-0.138,0.144c-0.165,1.499-0.867,4.13-3.783,5.181v2.484h1.945v6.282 c0,2.151,1.587,5.206,5.775,5.135c1.413-0.024,2.982-0.616,3.329-1.126L16.749,17.396z" />
</symbol>
<symbol id="icon-twitch" viewBox="0 0 24 24">
<path d="M16.499,8.089h-1.636v4.91h1.636V8.089z M12,8.089h-1.637v4.91H12V8.089z M4.228,3.178L3,6.451v13.092h4.499V22h2.456 l2.454-2.456h3.681L21,14.636V3.178H4.228z M19.364,13.816l-2.864,2.865H12l-2.453,2.453V16.68H5.863V4.814h13.501V13.816z" />
</symbol>
<symbol id="icon-twitter" viewBox="0 0 24 24">
<path d="M22.23,5.924c-0.736,0.326-1.527,0.547-2.357,0.646c0.847-0.508,1.498-1.312,1.804-2.27 c-0.793,0.47-1.671,0.812-2.606,0.996C18.324,4.498,17.257,4,16.077,4c-2.266,0-4.103,1.837-4.103,4.103 c0,0.322,0.036,0.635,0.106,0.935C8.67,8.867,5.647,7.234,3.623,4.751C3.27,5.357,3.067,6.062,3.067,6.814 c0,1.424,0.724,2.679,1.825,3.415c-0.673-0.021-1.305-0.206-1.859-0.513c0,0.017,0,0.034,0,0.052c0,1.988,1.414,3.647,3.292,4.023 c-0.344,0.094-0.707,0.144-1.081,0.144c-0.264,0-0.521-0.026-0.772-0.074c0.522,1.63,2.038,2.816,3.833,2.85 c-1.404,1.1-3.174,1.756-5.096,1.756c-0.331,0-0.658-0.019-0.979-0.057c1.816,1.164,3.973,1.843,6.29,1.843 c7.547,0,11.675-6.252,11.675-11.675c0-0.178-0.004-0.355-0.012-0.531C20.985,7.47,21.68,6.747,22.23,5.924z" />
</symbol>
<symbol id="icon-vimeo" viewBox="0 0 24 24">
<path d="M22.396,7.164c-0.093,2.026-1.507,4.799-4.245,8.32C15.322,19.161,12.928,21,10.97,21c-1.214,0-2.24-1.119-3.079-3.359 c-0.56-2.053-1.119-4.106-1.68-6.159C5.588,9.243,4.921,8.122,4.206,8.122c-0.156,0-0.701,0.328-1.634,0.98L1.594,7.841 c1.027-0.902,2.04-1.805,3.037-2.708C6.001,3.95,7.03,3.327,7.715,3.264c1.619-0.156,2.616,0.951,2.99,3.321 c0.404,2.557,0.685,4.147,0.841,4.769c0.467,2.121,0.981,3.181,1.542,3.181c0.435,0,1.09-0.688,1.963-2.065 c0.871-1.376,1.338-2.422,1.401-3.142c0.125-1.187-0.343-1.782-1.401-1.782c-0.498,0-1.012,0.115-1.541,0.341 c1.023-3.35,2.977-4.977,5.862-4.884C21.511,3.066,22.52,4.453,22.396,7.164z" />
</symbol>
<symbol id="icon-vk" viewBox="0 0 24 24">
<path d="M22,7.1c0.2,0.4-0.4,1.5-1.6,3.1c-0.2,0.2-0.4,0.5-0.7,0.9c-0.5,0.7-0.9,1.1-0.9,1.4c-0.1,0.3-0.1,0.6,0.1,0.8 c0.1,0.1,0.4,0.4,0.8,0.9h0l0,0c1,0.9,1.6,1.7,2,2.3c0,0,0,0.1,0.1,0.1c0,0.1,0,0.1,0.1,0.3c0,0.1,0,0.2,0,0.4 c0,0.1-0.1,0.2-0.3,0.3c-0.1,0.1-0.4,0.1-0.6,0.1l-2.7,0c-0.2,0-0.4,0-0.6-0.1c-0.2-0.1-0.4-0.1-0.5-0.2l-0.2-0.1 c-0.2-0.1-0.5-0.4-0.7-0.7s-0.5-0.6-0.7-0.8c-0.2-0.2-0.4-0.4-0.6-0.6C14.8,15,14.6,15,14.4,15c0,0,0,0-0.1,0c0,0-0.1,0.1-0.2,0.2 c-0.1,0.1-0.2,0.2-0.2,0.3c-0.1,0.1-0.1,0.3-0.2,0.5c-0.1,0.2-0.1,0.5-0.1,0.8c0,0.1,0,0.2,0,0.3c0,0.1-0.1,0.2-0.1,0.2l0,0.1 c-0.1,0.1-0.3,0.2-0.6,0.2h-1.2c-0.5,0-1,0-1.5-0.2c-0.5-0.1-1-0.3-1.4-0.6s-0.7-0.5-1.1-0.7s-0.6-0.4-0.7-0.6l-0.3-0.3 c-0.1-0.1-0.2-0.2-0.3-0.3s-0.4-0.5-0.7-0.9s-0.7-1-1.1-1.6c-0.4-0.6-0.8-1.3-1.3-2.2C2.9,9.4,2.5,8.5,2.1,7.5C2,7.4,2,7.3,2,7.2 c0-0.1,0-0.1,0-0.2l0-0.1c0.1-0.1,0.3-0.2,0.6-0.2l2.9,0c0.1,0,0.2,0,0.2,0.1S5.9,6.9,5.9,7L6,7c0.1,0.1,0.2,0.2,0.3,0.3 C6.4,7.7,6.5,8,6.7,8.4C6.9,8.8,7,9,7.1,9.2l0.2,0.3c0.2,0.4,0.4,0.8,0.6,1.1c0.2,0.3,0.4,0.5,0.5,0.7s0.3,0.3,0.4,0.4 c0.1,0.1,0.3,0.1,0.4,0.1c0.1,0,0.2,0,0.3-0.1c0,0,0,0,0.1-0.1c0,0,0.1-0.1,0.1-0.2c0.1-0.1,0.1-0.3,0.1-0.5c0-0.2,0.1-0.5,0.1-0.8 c0-0.4,0-0.8,0-1.3c0-0.3,0-0.5-0.1-0.8c0-0.2-0.1-0.4-0.1-0.5L9.6,7.6C9.4,7.3,9.1,7.2,8.7,7.1C8.6,7.1,8.6,7,8.7,6.9 C8.9,6.7,9,6.6,9.1,6.5c0.4-0.2,1.2-0.3,2.5-0.3c0.6,0,1,0.1,1.4,0.1c0.1,0,0.3,0.1,0.3,0.1c0.1,0.1,0.2,0.1,0.2,0.3 c0,0.1,0.1,0.2,0.1,0.3s0,0.3,0,0.5c0,0.2,0,0.4,0,0.6c0,0.2,0,0.4,0,0.7c0,0.3,0,0.6,0,0.9c0,0.1,0,0.2,0,0.4c0,0.2,0,0.4,0,0.5 c0,0.1,0,0.3,0,0.4s0.1,0.3,0.1,0.4c0.1,0.1,0.1,0.2,0.2,0.3c0.1,0,0.1,0,0.2,0c0.1,0,0.2,0,0.3-0.1c0.1-0.1,0.2-0.2,0.4-0.4 s0.3-0.4,0.5-0.7c0.2-0.3,0.5-0.7,0.7-1.1c0.4-0.7,0.8-1.5,1.1-2.3c0-0.1,0.1-0.1,0.1-0.2c0-0.1,0.1-0.1,0.1-0.1l0,0l0.1,0 c0,0,0,0,0.1,0s0.2,0,0.2,0l3,0c0.3,0,0.5,0,0.7,0S21.9,7,21.9,7L22,7.1z" />
</symbol>
<symbol id="icon-whatsapp" viewBox="0 0 24 24">
<path d="M2.048,22l1.406-5.136c-0.867-1.503-1.324-3.208-1.323-4.955C2.133,6.446,6.579,2,12.042,2c2.651,0.001,5.14,1.033,7.011,2.906c1.871,1.873,2.901,4.363,2.9,7.011c-0.002,5.464-4.448,9.91-9.91,9.91c0,0,0,0,0,0h-0.004c-1.659-0.001-3.288-0.417-4.736-1.206L2.048,22z M7.545,18.828l0.301,0.179c1.265,0.751,2.714,1.148,4.193,1.148h0.003c4.54,0,8.235-3.695,8.237-8.237c0.001-2.201-0.855-4.271-2.41-5.828c-1.555-1.557-3.623-2.415-5.824-2.416c-4.544,0-8.239,3.695-8.241,8.237c-0.001,1.556,0.435,3.072,1.259,4.384l0.196,0.312l-0.832,3.04L7.545,18.828z M17.035,14.274c-0.062-0.103-0.227-0.165-0.475-0.289c-0.248-0.124-1.465-0.723-1.692-0.806c-0.227-0.083-0.392-0.124-0.557,0.124c-0.165,0.248-0.64,0.806-0.784,0.971c-0.144,0.165-0.289,0.186-0.536,0.062c-0.248-0.124-1.046-0.385-1.991-1.229c-0.736-0.657-1.233-1.468-1.378-1.715c-0.144-0.248-0.015-0.382,0.109-0.505c0.111-0.111,0.248-0.289,0.371-0.434c0.124-0.145,0.165-0.248,0.248-0.413c0.083-0.165,0.041-0.31-0.021-0.434c-0.062-0.124-0.557-1.343-0.763-1.839C9.364,7.284,9.159,7.35,9.007,7.342c-0.144-0.007-0.31-0.009-0.475-0.009c-0.165,0-0.433,0.062-0.66,0.31C7.646,7.891,7.006,8.49,7.006,9.709c0,1.219,0.887,2.396,1.011,2.562c0.124,0.165,1.746,2.666,4.23,3.739c0.591,0.255,1.052,0.408,1.412,0.522c0.593,0.189,1.133,0.162,1.56,0.098c0.476-0.071,1.465-0.599,1.671-1.177C17.096,14.873,17.096,14.378,17.035,14.274z" />
</symbol>
<symbol id="icon-woocommerce" viewBox="0 0 24 24">
<path d="M19,2H5C3.3,2,2,3.3,2,5v11c0,1.7,1.3,3,3,3h4l6,3l-1-3h5c1.7,0,3-1.3,3-3V5C22,3.3,20.7,2,19,2z M17.4,6.5c-0.4,0.8-0.8,2.1-1,3.9c-0.3,1.8-0.4,3.1-0.3,4.1c0,0.3,0,0.5-0.1,0.7s-0.3,0.4-0.6,0.4s-0.6-0.1-0.9-0.4c-1-1-1.8-2.6-2.4-4.6c-0.7,1.4-1.2,2.4-1.6,3.1c-0.6,1.2-1.2,1.8-1.6,1.9c-0.3,0-0.5-0.2-0.8-0.7C7.6,13.5,7,10.7,6.4,6.7c0-0.3,0-0.5,0.2-0.7C6.7,5.8,7,5.7,7.3,5.6c0.5,0,0.9,0.2,0.9,0.8c0.3,2.3,0.7,4.2,1.1,5.7l2.4-4.5C11.9,7.2,12.1,7,12.5,7c0.5,0,0.8,0.3,0.9,0.9c0.3,1.4,0.6,2.6,1,3.7c0.3-2.7,0.8-4.7,1.4-5.9c0.2-0.3,0.4-0.5,0.7-0.5c0.2,0,0.5,0.1,0.7,0.2c0.2,0.2,0.3,0.4,0.3,0.6S17.5,6.4,17.4,6.5z" />
</symbol>
<symbol id="icon-wordpress" viewBox="0 0 24 24">
<path d="M12.158,12.786L9.46,20.625c0.806,0.237,1.657,0.366,2.54,0.366c1.047,0,2.051-0.181,2.986-0.51 c-0.024-0.038-0.046-0.079-0.065-0.124L12.158,12.786z M3.009,12c0,3.559,2.068,6.634,5.067,8.092L3.788,8.341 C3.289,9.459,3.009,10.696,3.009,12z M18.069,11.546c0-1.112-0.399-1.881-0.741-2.48c-0.456-0.741-0.883-1.368-0.883-2.109 c0-0.826,0.627-1.596,1.51-1.596c0.04,0,0.078,0.005,0.116,0.007C16.472,3.904,14.34,3.009,12,3.009 c-3.141,0-5.904,1.612-7.512,4.052c0.211,0.007,0.41,0.011,0.579,0.011c0.94,0,2.396-0.114,2.396-0.114 C7.947,6.93,8.004,7.642,7.52,7.699c0,0-0.487,0.057-1.029,0.085l3.274,9.739l1.968-5.901l-1.401-3.838 C9.848,7.756,9.389,7.699,9.389,7.699C8.904,7.67,8.961,6.93,9.446,6.958c0,0,1.484,0.114,2.368,0.114 c0.94,0,2.397-0.114,2.397-0.114c0.485-0.028,0.542,0.684,0.057,0.741c0,0-0.488,0.057-1.029,0.085l3.249,9.665l0.897-2.996 C17.841,13.284,18.069,12.316,18.069,11.546z M19.889,7.686c0.039,0.286,0.06,0.593,0.06,0.924c0,0.912-0.171,1.938-0.684,3.22 l-2.746,7.94c2.673-1.558,4.47-4.454,4.47-7.771C20.991,10.436,20.591,8.967,19.889,7.686z M12,22C6.486,22,2,17.514,2,12 C2,6.486,6.486,2,12,2c5.514,0,10,4.486,10,10C22,17.514,17.514,22,12,22z" />
</symbol>
<symbol id="icon-yelp" viewBox="0 0 24 24">
<path d="M12.271,16.718v1.417q-.011,3.257-.067,3.4a.707.707,0,0,1-.569.446,4.637,4.637,0,0,1-2.024-.424A4.609,4.609,0,0,1,7.8,20.565a.844.844,0,0,1-.19-.4.692.692,0,0,1,.044-.29,3.181,3.181,0,0,1,.379-.524q.335-.412,2.019-2.409.011,0,.669-.781a.757.757,0,0,1,.44-.274.965.965,0,0,1,.552.039.945.945,0,0,1,.418.324.732.732,0,0,1,.139.468Zm-1.662-2.8a.783.783,0,0,1-.58.781l-1.339.435q-3.067.981-3.257.981a.711.711,0,0,1-.6-.4,2.636,2.636,0,0,1-.19-.836,9.134,9.134,0,0,1,.011-1.857,3.559,3.559,0,0,1,.335-1.389.659.659,0,0,1,.625-.357,22.629,22.629,0,0,1,2.253.859q.781.324,1.283.524l.937.379a.771.771,0,0,1,.4.34A.982.982,0,0,1,10.609,13.917Zm9.213,3.313a4.467,4.467,0,0,1-1.021,1.8,4.559,4.559,0,0,1-1.512,1.417.671.671,0,0,1-.7-.078q-.156-.112-2.052-3.2l-.524-.859a.761.761,0,0,1-.128-.513.957.957,0,0,1,.217-.513.774.774,0,0,1,.926-.29q.011.011,1.327.446,2.264.736,2.7.887a2.082,2.082,0,0,1,.524.229.673.673,0,0,1,.245.68Zm-7.5-7.049q.056,1.137-.6,1.361-.647.19-1.272-.792L6.237,4.08a.7.7,0,0,1,.212-.691,5.788,5.788,0,0,1,2.314-1,5.928,5.928,0,0,1,2.5-.352.681.681,0,0,1,.547.5q.034.2.245,3.407T12.327,10.181Zm7.384,1.2a.679.679,0,0,1-.29.658q-.167.112-3.67.959-.747.167-1.015.257l.011-.022a.769.769,0,0,1-.513-.044.914.914,0,0,1-.413-.357.786.786,0,0,1,0-.971q.011-.011.836-1.137,1.394-1.908,1.673-2.275a2.423,2.423,0,0,1,.379-.435A.7.7,0,0,1,17.435,8a4.482,4.482,0,0,1,1.372,1.489,4.81,4.81,0,0,1,.9,1.868v.034Z" />
</symbol>
<symbol id="icon-x" viewBox="0 0 24 24">
<path d="M14.1173 9.62177L20.4459 2H18.9463L13.4511 8.61788L9.06215 2H4L10.637 12.0074L4 20H5.49977L11.3028 13.0113L15.9379 20H21L14.1169 9.62177H14.1173ZM12.0632 12.0956L11.3907 11.0991L6.04016 3.16971H8.34371L12.6617 9.56895L13.3341 10.5655L18.947 18.8835H16.6434L12.0632 12.096V12.0956Z" />
</symbol>
<symbol id="icon-xanga" viewBox="0 0 24 24">
<path d="M9,9h6v6H9V9z M3,9h6V3H3V9z M15,9h6V3h-6V9z M15,21h6v-6h-6V21z M3,21h6v-6H3V21z" />
</symbol>
<symbol id="icon-youtube" viewBox="0 0 24 24">
<path d="M21.8,8.001c0,0-0.195-1.378-0.795-1.985c-0.76-0.797-1.613-0.801-2.004-0.847c-2.799-0.202-6.997-0.202-6.997-0.202 h-0.009c0,0-4.198,0-6.997,0.202C4.608,5.216,3.756,5.22,2.995,6.016C2.395,6.623,2.2,8.001,2.2,8.001S2,9.62,2,11.238v1.517 c0,1.618,0.2,3.237,0.2,3.237s0.195,1.378,0.795,1.985c0.761,0.797,1.76,0.771,2.205,0.855c1.6,0.153,6.8,0.201,6.8,0.201 s4.203-0.006,7.001-0.209c0.391-0.047,1.243-0.051,2.004-0.847c0.6-0.607,0.795-1.985,0.795-1.985s0.2-1.618,0.2-3.237v-1.517 C22,9.62,21.8,8.001,21.8,8.001z M9.935,14.594l-0.001-5.62l5.404,2.82L9.935,14.594z" />
</symbol>
</defs>
</svg>
<script>!function(e){const r={"Europe/Brussels":"gdpr","Europe/Sofia":"gdpr","Europe/Prague":"gdpr","Europe/Copenhagen":"gdpr","Europe/Berlin":"gdpr","Europe/Tallinn":"gdpr","Europe/Dublin":"gdpr","Europe/Athens":"gdpr","Europe/Madrid":"gdpr","Africa/Ceuta":"gdpr","Europe/Paris":"gdpr","Europe/Zagreb":"gdpr","Europe/Rome":"gdpr","Asia/Nicosia":"gdpr","Europe/Nicosia":"gdpr","Europe/Riga":"gdpr","Europe/Vilnius":"gdpr","Europe/Luxembourg":"gdpr","Europe/Budapest":"gdpr","Europe/Malta":"gdpr","Europe/Amsterdam":"gdpr","Europe/Vienna":"gdpr","Europe/Warsaw":"gdpr","Europe/Lisbon":"gdpr","Atlantic/Madeira":"gdpr","Europe/Bucharest":"gdpr","Europe/Ljubljana":"gdpr","Europe/Bratislava":"gdpr","Europe/Helsinki":"gdpr","Europe/Stockholm":"gdpr","Europe/London":"gdpr","Europe/Vaduz":"gdpr","Atlantic/Reykjavik":"gdpr","Europe/Oslo":"gdpr","Europe/Istanbul":"gdpr","Europe/Zurich":"gdpr"},p=(()=>{const e=Intl.DateTimeFormat().resolvedOptions().timeZone;return r[e]||null})();if(null===p||"gdpr"!==p){const r="__adblocker";if(-1===e.cookie.indexOf(r)){const p=new XMLHttpRequest;p.open("GET","https://ads.adthrive.com/abd/abd.js",!0),p.onreadystatechange=function(){if(XMLHttpRequest.DONE===p.readyState)if(200===p.status){const r=e.createElement("script");r.innerHTML=p.responseText,e.getElementsByTagName("head")[0].appendChild(r)}else{const p=new Date;p.setTime(p.getTime()+3e5),e.cookie=r+"=true; expires="+p.toUTCString()+"; path=/"}},p.send()}}}(document);</script><script>!function(e){(function(){var n,t;function r(){var n=e.createElement("script");n.src="https://cafemedia-com.videoplayerhub.com/galleryplayer.js",e.head.appendChild(n)}function a(){var n=e.cookie.match("(^|[^;]+)\\s*__adblocker\\s*=\\s*([^;]+)");return n&&n.pop()}function c(){clearInterval(t)}return{init:function(){var e;"true"===(n=a())?r():(e=0,t=setInterval(function(){100!==e&&"false"!==n||c(),"true"===n&&(r(),c()),n=a(),e++},50))}}})().init()}(document);</script>
</body>
</html>
