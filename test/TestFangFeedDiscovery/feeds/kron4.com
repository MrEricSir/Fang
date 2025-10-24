
<!doctype html>
<html lang="en-US">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="manifest" href="https://www.kron4.com/wp-json/lakana/v1/onesignal-manifest">
	<meta http-equiv="refresh" content="3600">
	<link rel="profile" href="https://gmpg.org/xfn/11">
	<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin /><!-- nname:nxs: -->
	<link rel="preload" as="style" href="https://fonts.googleapis.com/css?family=Source+Sans+Pro:400,400i,600,600i,700,700i,900,900i|Source+Serif+Pro:400,600,700,900|Roboto+Condensed:400,700|Lora:400,700&#038;display=swap" />

	<style>
.nxst-retrans-banner__inner--heading p {
  font-size: 44px !important;
  font-weight: 700 !important;
  line-height: 30px !important;
}
.nxst-retrans-banner__inner--message p {
  font-size: 24px !important;
  font-weight: 600 !important;
  line-height: 24px !important;
}
.nxst-retrans-banner__inner--submit p {
  font-size: 20px;
  font-weight: 700;
  line-height: 30px;
}
@media (max-width: 899px) {
  .nxst-retrans-banner__inner--heading p {
    font-size: 18px !important;
    line-height: 20px !important;
  }
  .nxst-retrans-banner__inner--message p {
    font-size: 14px !important;
    line-height: 16px !important;
  }
  .nxst-retrans-banner__inner--submit p {
    font-size: 16px;
    line-height: 20px;
  }
}
</style>
<style>
div.hurrytimer-campaign > .dark-overlay{
 pointer-events: none; 
}
</style><script src="/CvbtpUrj/init.js" async></script>					<script id="blueconic_deprioritization" src="https://nxst.megpxs.com/ndn.js"></script>
	
			
	<!-- Cookies Consent Notice start - OneTrust -->
	<script
		src="https://cdn.cookielaw.org/scripttemplates/gpp.stub.js "
		type="text/javascript" charset="UTF-8">
	</script> 	<script
		src="https://cdn.cookielaw.org/scripttemplates/otSDKStub.js"
		type="text/javascript" charset="UTF-8"
		data-domain-script="fd137de5-c96c-424c-afa7-f92a90556e38">
	</script> 	<script type="text/javascript">
		function OptanonWrapper() { }
	</script> 	<script
		src="https://cdn.cookielaw.org/opt-out/otCCPAiab.js"
		type="text/javascript" charset="UTF-8"
		ccpa-opt-out-ids="SSPD_BG" ccpa-opt-out-geo="us" ccpa-opt-out-lspa="false">
	</script> 	<!-- Cookies Consent Notice end - OneTrust -->

	<script>
		window.addEventListener("load", function() {
			const oneTrustAccept = document.getElementById("onetrust-accept-btn-handler");
			oneTrustAccept?.addEventListener("click", function() {
				permutive.consent({"opt_in": true, "token": window.NXSTdata.identity.blueconicId});
			});
		});
	</script>

	
	
<script>
    window.addEventListener("load", function() {
        // Promise that check if the user has consented or not
        window.consentGranted = () => new Promise((resolve) => {
            if (window.__uspapi && 'function' === typeof __uspapi) {
                __uspapi('getUSPData', 1, (uspData, success) => {
                    if(success) {
                        const consent = uspData.uspString.split('')[2];
                        if (consent === 'N') {
                            resolve(true);
                        } else {
                            resolve(false);
                        }
                    } else {
                        resolve(false);
                    }
                });
            } else {
                resolve(false);
            }
        });

        // Dispatch event for user consent
        window.OneTrust?.OnConsentChanged(({ detail }) => {
            const nxsConsentEvent = new CustomEvent('nxsConsent', { detail });
            dispatchEvent(nxsConsentEvent);
        });

        // groups the user has consented to
        window.nxsConsentGroups = window.OnetrustActiveGroups;
    })
</script>

			<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/universal-data-layer/js/udl.js?ver=1.3.0"></script>
		<script>
			window.NXSTdata = window.NXSTdata || {};
			window.NXSTdata.content = window.NXSTdata.content || {};
			window.NXSTdata.page = window.NXSTdata.page || {};
			window.NXSTdata.site = window.NXSTdata.site || {};
			window.NXSTdata.ads = window.NXSTdata.ads || {};
			window.NXSTdata.layout = window.NXSTdata.layout || {};
			window.NXSTdata.privacy = window.NXSTdata.privacy || {};
			window.NXSTdata.alerts = window.NXSTdata.alerts || {};
			window.NXSTdata.location = window.NXSTdata.location || {};
			window.NXSTdata.content = Object.assign( window.NXSTdata.content, {"title":"San Francisco Bay Area News & Weather | KRON4","homepageTitle":"","metaKeywords":"","socialTitle":"","pageType":"home page","authorName":"","authorNonByline":"","description":"San Francisco Bay Area's local news & weather station. Local reporting to make San Francisco, San Jose, Oakland and the rest of the Bay Area a better place to live.","publicationDate":"","lastModifiedDate":"","publicationDayOfWeek":"","categoryList":[],"primaryCategory":"","tagList":[],"wordCount":0,"paragraphCount":0,"imageCount":0,"videoCount":0,"slideshowCount":0,"pageId":"","providerName":"","isShared":false,"originalSource":"","sharingMode":"","pageDcode":["294","317","912"],"localId":"nxs-11-home_page-0","seoTitle":"","iabGenre":[],"iabCategory":[],"initialCreator":null,"newsletterTitle":"","pageName":"kron:home-page","publicationDateLocal":"","persistentId":"nxs-11-home_page-0"} )
			window.NXSTdata.page = Object.assign( window.NXSTdata.page, {"canonicalUrl":"","ampUrl":"","urlHostname":"https:\/\/www.kron4.com","urlSlug":"","directoryPath":[]} )
			window.NXSTdata.site = Object.assign( window.NXSTdata.site, {"activeTheme":"nexstar wv","appVersion":"wp","brandName":"KRON4","callSign":"KRON","domainName":"kron4.com","timeZone":"America\/Los_Angeles","segmentKey":"","gaId":"","networkId":"nxs-11","adobeMediaAPI":"https:\/\/edge.adobedc.net\/ee\/va\/v1\/","adobeDataStreamId":"2d3a9df0-344f-464e-8b3c-79141641d86e","adobeAnalyticsEnabled":true,"adobeOrgId":"","primaryCallSign":"KRON","uniqueSiteShortcode":"KRON"} )
			window.NXSTdata.ads = Object.assign( window.NXSTdata.ads, {"adSlots":[],"adUnitPath":"home","a9Enabled":true,"confiantEnabled":true,"indexExchangeEnabled":false,"nativoEnabled":true,"prebidEnabled":true,"teadsEnabled":false,"isSponsored":false,"sponsor":"","outstreamAvailable":false,"companionsEnabled":false,"htlbidEnabled":true,"magniteEnabled":false} )
			window.NXSTdata.layout = Object.assign( window.NXSTdata.layout, {"mainModule":"daily news video","templateType":"standard"} )
			window.NXSTdata.location = Object.assign( window.NXSTdata.location, {"publicIp":"64.54.15.000"} )
					</script>
		
						<script
					async defer  src="https://blue.kron4.com/script.js"></script>
	
	
				<!-- start Permutive -->
		<script>
					!function(n,e,i){if(!n){n=n||{},window.permutive=n,n.q=[],n.config=i||{},n.config.apiKey=e,n.config.environment=n.config.environment||"production";for(var o=["addon","identify","track","trigger","query","segment","segments","ready","on","once","user","consent"],r=0;r<o.length;r++){var t=o[r];n[t]=function(e){return function(){var i=Array.prototype.slice.call(arguments,0);n.q.push({functionName:e,arguments:i})}}(t)}}}(window.permutive,"fc894c11-5ec8-48d7-b952-0a3aefdb3968", { "consentRequired": true });
			window.googletag=window.googletag||{},window.googletag.cmd=window.googletag.cmd||[],window.googletag.cmd.push(function(){if(0===window.googletag.pubads().getTargeting("permutive").length){var g=window.localStorage.getItem("_pdfps");window.googletag.pubads().setTargeting("permutive",g?JSON.parse(g):[])}});

			// Consent the user on permutive based on the user consent
			window.addEventListener("load", async function() {
				// Listen for change in user consent and enable the SDK accordingly
				addEventListener('nxsConsent', async () => {
					window.permutive.consent({
						"opt_in": await window.consentGranted(),
						"token": "GRANTED",
					});
				});

				// Enable Permutive SDK by default is consent not required according to OneTrust
				if (window.nxsConsentGroups?.includes('Notice_Only')) {
					window.permutive.consent({
						"opt_in": false,
						"token": "none"
					});
				// Enable SDK if user has submitted consent
				} else if (await window.consentGranted()) {
					window.permutive.consent({
						"opt_in": true,
						"token": "Consent_Captured",
					});
				} else {
					window.permutive.consent({
						"opt_in": true,
						"token": "Consent_Captured",
					})
				}
			});

			if (window.NXSTdata.identity.blueconicId) {
				permutive.identify([
					{
						id: NXSTdata.identity.nexstarId,
						tag: "nexstar_id",
						priority: 0
					}
				]);
				permutive.identify([
					{
						id: window.NXSTdata.identity.blueconicId,
						tag: "blueconic_id",
						priority: 1
					}
				]);
			}
			var isNlpCategoriesAnObject = 'object' === typeof window.NXSTdata.content.nlpCategories && null !== window.NXSTdata.content.nlpCategories;
			var isNlpSentimentAnObject = 'object' === typeof window.NXSTdata.content.nlpSentiment && null !== window.NXSTdata.content.nlpSentiment;
			var pageVars = {
					"content": {
					"pageType": window.NXSTdata.content.pageType,
					"authorName": window.NXSTdata.content.authorName,
					"providerName": window.NXSTdata.content.providerName,
					"categoryList": window.NXSTdata.content.categoryList,
					"primaryCategory": window.NXSTdata.content.primaryCategory,
					"wordCount": window.NXSTdata.content.wordCount,
					"paragraphCount": window.NXSTdata.content.paragraphCount,
					"tagList": window.NXSTdata.content.tagList,
					"nlpCategories1": isNlpCategoriesAnObject ? Object.keys(window.NXSTdata.content.nlpCategories)[0] : '',
					"nlpCategories2": isNlpCategoriesAnObject ? Object.keys(window.NXSTdata.content.nlpCategories)[1] : '',
					"nlpCategories3": isNlpCategoriesAnObject ? Object.keys(window.NXSTdata.content.nlpCategories)[2] : '',
					"nlpConsumerGood": 'object' === typeof window.NXSTdata.content.nlpConsumerGood && null !== window.NXSTdata.content.nlpConsumerGood ? Object.keys(window.NXSTdata.content.nlpConsumerGood).toString() : '',
					"nlpEvent": 'object' === typeof window.NXSTdata.content.nlpEvent && null !== window.NXSTdata.content.nlpEvent ? Object.keys(window.NXSTdata.content.nlpEvent).toString() : '',
					"nlpLocation": 'object' === typeof window.NXSTdata.content.nlpLocation && null !== window.NXSTdata.content.nlpLocation ? Object.keys(window.NXSTdata.content.nlpLocation).toString() : '',
					"nlpOrganization": 'object' === typeof window.NXSTdata.content.nlpOrganization && null !== window.NXSTdata.content.nlpOrganization ? Object.keys(window.NXSTdata.content.nlpOrganization).toString() : '',
					"nlpPerson": 'object' === typeof window.NXSTdata.content.nlpPerson && null !== window.NXSTdata.content.nlpPerson ? Object.keys(window.NXSTdata.content.nlpPerson).toString() : '',
					},
					"page": {
						"utmCampaign": window.NXSTdata.page.queryParams.utm_campaign,
						"utmMedium": window.NXSTdata.page.queryParams.utm_medium,
						"utmSource": window.NXSTdata.page.queryParams.utm_source,
					},
				};
				if ( isNlpSentimentAnObject ) {
					pageVars['content']['nlpSentimentScore'] = window.NXSTdata.content.nlpSentiment.score;
				}
				if ( isNlpSentimentAnObject ) {
					pageVars['content']['nlpSentimentMag'] = window.NXSTdata.content.nlpSentiment.magnitude;
				}

			permutive.addon('web', {
				page: pageVars,
			});

		</script>
		<script async src="https://3a6b0682-f3e1-4576-a706-5eb4101b9cc3.edge.permutive.app/3a6b0682-f3e1-4576-a706-5eb4101b9cc3-web.js"></script>
		<!-- end Permutive -->
					
	
	
<!-- BoB -->
<script async type="text/javascript" id="bob_tag_loader">
var page_url = "https:\/\/www.kron4.com\/" || "";
var cats = "" || "";
var bob_kw = "" || "";
var bob_desc = "" || "";
var bob_story_author = "" || "";
var cat_data = "&cats=" + encodeURIComponent(cats) + "&bob_kw=" + encodeURIComponent(bob_kw) + "&bob_desc=" + encodeURIComponent(bob_desc) + "&story_author=" + encodeURIComponent(bob_story_author) + "&page_url=" + encodeURIComponent(page_url);
var bob_base = "bob.dmpxs.com";

var bob_cb = '1';
bob_cb = ((new Date()).getTime() + "" + Math.floor(Math.random() * 1000000)).substr(0, 16);
(function () {
var bob_tag = document.createElement('script');
bob_tag.type = 'text/javascript';
bob_tag.async = true;
bob_tag.id = "bob_tag";
bob_tag.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + bob_base + '/static/bob_001.js?bob_cb=' + bob_cb + cat_data;
var bts = document.getElementsByTagName('script')[0];
bts.parentNode.insertBefore(bob_tag, bts);
})();
</script>



	
			
<!-- OTTOBOX -->
<script
	id="ns_script_dc"
	data-key="31b9b552-f32e-4036-8364-726eb992b71d"
	data-e="5"
	src="//d3plfjw9uod7ab.cloudfront.net/31b9b552-f32e-4036-8364-726eb992b71d.js"
	type="text/javascript"
	defer
></script>
	
	
<!-- Prebid -->
<script>
	window.isPrebidEnabled = false;
	window.isPrebidVideoEnabled = false;
</script>


	
<!-- Ad Config -->
<script>
	window.isAdRefreshEnabled     = true;
	window.isAdLazyloadEnabled    = false;
	window.isAdSponsorshipEnabled = true;
	window.adRefreshConfig        = {"index\/adhesion\/desktop":30,"index\/adhesion\/mobile":30,"index\/adhesion\/tablet":30,"index\/billboard1\/desktop":30,"index\/billboard1\/mobile":30,"index\/billboard1\/tablet":30,"index\/leaderboard1\/desktop":30,"index\/leaderboard1\/mobile":30,"index\/leaderboard1\/tablet":30,"index\/leaderboard3\/desktop":30,"index\/leaderboard3\/mobile":30,"index\/leaderboard3\/tablet":30,"index\/mr1\/desktop":30,"index\/mr1\/mobile":30,"index\/mr1\/tablet":30,"index\/mr1_mobile\/desktop":30,"index\/mr1_mobile\/mobile":30,"index\/mr1_mobile\/tablet":30,"index\/mr_combo1\/desktop":30,"index\/mr_combo1\/mobile":30,"index\/mr_combo1\/tablet":30,"index\/mr_combo2\/desktop":30,"index\/mr_combo2\/mobile":30,"index\/mr_combo2\/tablet":30,"other\/adhesion\/desktop":30,"other\/adhesion\/mobile":30,"other\/adhesion\/tablet":30,"other\/billboard1\/desktop":30,"other\/billboard1\/mobile":30,"other\/billboard1\/tablet":30,"other\/leaderboard3\/desktop":30,"other\/leaderboard3\/mobile":30,"other\/leaderboard3\/tablet":30,"other\/mr1_mobile\/desktop":30,"other\/mr1_mobile\/mobile":30,"other\/mr1_mobile\/tablet":30,"other\/mr_combo1\/desktop":30,"other\/mr_combo1\/mobile":30,"other\/mr_combo1\/tablet":30,"other\/mr_combo2\/mobile":30,"other\/mr_combo2\/tablet":30,"story\/adhesion\/desktop":30,"story\/adhesion\/mobile":30,"story\/adhesion\/tablet":30,"story\/billboard1\/desktop":30,"story\/billboard1\/mobile":30,"story\/billboard1\/tablet":30,"story\/leader_mr1\/desktop":30,"story\/leader_mr1\/mobile":30,"story\/leader_mr1\/tablet":30,"story\/leader_mr2\/desktop":30,"story\/leader_mr2\/mobile":30,"story\/leader_mr2\/tablet":30,"story\/leader_mr3\/desktop":30,"story\/leader_mr3\/mobile":30,"story\/leader_mr3\/tablet":30,"story\/leader_mr4\/desktop":30,"story\/leader_mr4\/mobile":30,"story\/leader_mr4\/tablet":30,"story\/leaderboard3\/desktop":30,"story\/leaderboard3\/mobile":30,"story\/leaderboard3\/tablet":30,"story\/mr1\/desktop":30,"story\/mr1\/mobile":30,"story\/mr1\/tablet":30,"story\/mr1_ab\/desktop":30,"story\/mr1_ab\/mobile":30,"story\/mr1_ab\/tablet":30,"story\/mr1_mobile\/desktop":30,"story\/mr1_mobile\/mobile":30,"story\/mr1_mobile\/tablet":30,"story\/mr2_ab\/desktop":30,"story\/mr2_ab\/mobile":30,"story\/mr2_ab\/tablet":30,"story\/mr3_ab\/desktop":30,"story\/mr3_ab\/mobile":30,"story\/mr3_ab\/tablet":30,"story\/mr4_ab\/desktop":30,"story\/mr4_ab\/mobile":30,"story\/mr4_ab\/tablet":30,"story\/mr5_ab\/desktop":30,"story\/mr5_ab\/mobile":30,"story\/mr5_ab\/tablet":30,"story\/mr6_ab\/desktop":30,"story\/mr6_ab\/mobile":30,"story\/mr6_ab\/tablet":30,"story\/mr7_ab\/desktop":30,"story\/mr7_ab\/mobile":30,"story\/mr7_ab\/tablet":30,"story\/mr_combo1\/desktop":30,"story\/mr_combo1\/mobile":30,"story\/mr_combo1\/tablet":30,"story\/mr_combo2\/desktop":30,"story\/mr_combo2\/mobile":30,"story\/mr_combo2\/tablet":30,"subindex\/adhesion\/desktop":30,"subindex\/adhesion\/mobile":30,"subindex\/adhesion\/tablet":30,"subindex\/billboard1\/desktop":30,"subindex\/billboard1\/mobile":30,"subindex\/billboard1\/tablet":30,"subindex\/leaderboard3\/desktop":30,"subindex\/leaderboard3\/mobile":30,"subindex\/leaderboard3\/tablet":30,"subindex\/mr1\/desktop":30,"subindex\/mr1\/mobile":30,"subindex\/mr1\/tablet":30,"subindex\/mr1_mobile\/desktop":30,"subindex\/mr1_mobile\/mobile":30,"subindex\/mr1_mobile\/tablet":30,"subindex\/mr_combo1\/desktop":30,"subindex\/mr_combo1\/mobile":30,"subindex\/mr_combo1\/tablet":30,"subindex\/mr_combo2\/desktop":30,"subindex\/mr_combo2\/mobile":30,"subindex\/mr_combo2\/tablet":30};
	window.adLazyloadConfig       = [];
	window.adExclusionIds         = [290002782,6242377631,6242377631,6242377631];
</script>

	
	
<!-- A9 APS -->
<script>
	window.apsPubID = "3410";
	window.isApsEnabled = false;
	window.isApsVideoEnabled = true;
</script>


<!-- A9 APS -->
<script type="text/javascript">
	!function(a9,a,p,s,t,A,g){if(a[a9])return;function q(c,r){a[a9]._Q.push([c,r])}a[a9]={init:function(){q("i",arguments)},fetchBids:function(){q("f",arguments)},setDisplayBids:function(){},targetingKeys:function(){return[]},_Q:[]};A=p.createElement(s);A.async=!0;A.src=t;g=p.getElementsByTagName(s)[0];g.parentNode.insertBefore(A,g)}("apstag",window,document,"script","//c.amazon-adsystem.com/aax2/apstag.js");

	if (typeof window.__gpp === 'function') {
		const originalGppStubApi = window.__gpp;

		window.__gpp = function (...args) {
			// Check if the 'ping' command is being called
			if (args[0] === 'ping') {
				const response = originalGppStubApi(...args);
				response.gppString = 'DBABBg~BUUAAAGA.QA'; // sets a default value fallback on __gpp stub
				console.debug('gppConsentDefaultValue:', true)
				// pase new data to callback
				args[1](response, true)
				return response;
			}
			return originalGppStubApi(...args);
		};
	}

	let initArgs = {"pubID":"3410","adServer":"googletag","deals":true};

	if (window.__uspapi && 'function' === typeof __uspapi) {
		__uspapi('getUSPData', 1, (uspData, success) => {
			if(success) {
				initArgs.params = { us_privacy: uspData?.uspString };
			}
		});
	}

	const initParams = initArgs?.params || { us_privacy: window.NXSTdata?.privacy?.usPrivacyString || '1---' };

	function get_si_section() {
		const nlp_categories = Object.keys(
			NXSTdata.content?.nlpCategories || {}
		)
		if (
			!nlp_categories.length
			|| nlp_categories[0].toLowerCase().includes('sensitive subjects')
		) {
			return '';
		}
		return nlp_categories[0].split('/').filter(Boolean)[0].replaceAll(' ', '_')
	}

	apstag.init({
		...initArgs,
		params: {
			...initParams,
			si_section: get_si_section(),
		},
	});
</script>

				
<!-- Confiant ad fraud protection -->
<script async="" src="https://cdn.confiant-integrations.net/Y2Nn8JmiAY8HpnF4sl5n7J71jaI/gpt_and_prebid/config.js"></script> 	
	
	
<!-- Google Tag Manager dataLayer -->
<script>
var dataLayer = window.dataLayer || [];
if ('function' === typeof dataLayer.push) {
	dataLayer.push({"fireGTM":true,"propID":""});
}
</script>
<!-- End Google Tag Manager dataLayer  -->

<!-- Google Tag Manager -->
<script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer',"GTM-KJJZHXD");</script>
<!-- End Google Tag Manager -->
	
<!-- Google Tag Manager -->
<script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer',"GTM-KNNPZPH");</script>
<!-- End Google Tag Manager -->
	
	
	

	<script type="text/javascript">
		// Blockthrough is disabled
		window.NXSTdata.ads.blockthroughStatus = 'disabled';
	</script>

	

	
	
<!-- OneSignal SDK -->
<script src="https://cdn.onesignal.com/sdks/OneSignalSDK.js" async defer></script>
<!-- End OneSignal SDK -->
	
<!-- OneSignal initialization -->
<script>
	var OneSignal = window.OneSignal || [];
	OneSignal.push(["init", {
		appId: "6406479b-bd97-428d-ba43-bdc338b5dce1",
		httpPermissionRequest: {
			enable: true
		},
		notifyButton: {
			enable: false /* Set to false to hide */
		},
		promptOptions: {
			customlink: {
				enabled: true, /* Required to use the Custom Link */
				style: "button", /* Has value of 'button' or 'link' */
				size: "medium", /* One of 'small', 'medium', or 'large' */
				color: {
					button: '#E12D30', /* Color of the button background if style = "button" */
					text: '#FFFFFF', /* Color of the prompt's text */
				},
				text: {
					subscribe: "Subscribe to push notifications", /* Prompt's text when not subscribed */
					unsubscribe: "Unsubscribe from push notifications", /* Prompt's text when subscribed */
					explanation: "Get updates from all sorts of things that matter to you", /* Optional text appearing before the prompt button */
				},
				unsubscribeEnabled: true, /* Controls whether the prompt is visible after subscription */
			}
		}
	}]);
</script>
<!-- End OneSignal initialization -->
	
	<script type="application/ld+json">
	{"@context":"https:\/\/schema.org","@type":"WebSite","publisher":{"@type":"Organization","name":"KRON4","logo":{"@type":"ImageObject","url":"https:\/\/www.kron4.com\/wp-content\/uploads\/sites\/11\/2025\/04\/cropped-KRON4-footer-update-1.png"}},"name":"KRON4","description":"The Bay Area&#039;s Local News Station","potentialAction":{"@type":"SearchAction","target":"https:\/\/www.kron4.com\/search\/{search_term_string}\/","query-input":"required name=search_term_string"},"url":"https:\/\/www.kron4.com\/"}</script>

	
	<link rel="canonical" href="https://www.kron4.com">

	
<script>
	window.preloadAnvato = [];
	window.loadAnvato = window.loadAnvato || function (json) {
		window.preloadAnvato.push(json);
	};
</script>

				<script>
				window.SecondStreetSDK = {
					version: '1.0.0',
					ready: function (secondstreet) {
						window.SecondStreetSDK.secondstreet = secondstreet;
					}
				}
			</script>
		<title>San Francisco Bay Area News & Weather | KRON4</title>
<meta name='robots' content='max-image-preview:large' />
	<style>img:is([sizes="auto" i], [sizes^="auto," i]) { contain-intrinsic-size: 3000px 1500px }</style>
	<script type='text/javascript'>
window.isMobileReadMoreEnabled = false;
</script><script type='text/javascript'>
window.isGdprPrebidEnabled = false;
</script><link rel='dns-prefetch' href='//assets.adobedtm.com' />
<link rel='dns-prefetch' href='//segment.psg.nexstardigital.net' />
<link rel='dns-prefetch' href='//ak.sail-horizon.com' />
<link rel='dns-prefetch' href='//static.chartbeat.com' />
<link rel='dns-prefetch' href='//htlbid.com' />
<link rel='dns-prefetch' href='//stats.wp.com' />
<link rel='dns-prefetch' href='//securepubads.g.doubleclick.net' />
<link rel='dns-prefetch' href='//static.doubleclick.net' />
<link rel='dns-prefetch' href='//ib.adnxs.com' />
<link rel='dns-prefetch' href='//as-sec.casalemedia.com' />
<link rel='dns-prefetch' href='//js-sec.indexww.com' />
<link rel='dns-prefetch' href='//fastlane.rubiconproject.com' />
<link rel='dns-prefetch' href='//tlx.3lift.com' />
<link rel='dns-prefetch' href='//pubgw.ads.yahoo.com' />
<link rel='dns-prefetch' href='//c.amazon-adsystem.com' />
<link rel='dns-prefetch' href='//a.teads.tv' />
<link rel='dns-prefetch' href='//ats.rlcdn.com' />
<link rel="alternate" type="application/rss+xml" title="KRON4 &raquo; Feed" href="https://www.kron4.com/feed/" />
<link rel="alternate" type="application/rss+xml" title="KRON4 &raquo; Comments Feed" href="https://www.kron4.com/comments/feed/" />
<script class="wp-asset-manager ns-global-utils" type="text/javascript">!function(e){var t={};function n(r){if(t[r])return t[r].exports;var o=t[r]={i:r,l:!1,exports:{}};return e[r].call(o.exports,o,o.exports,n),o.l=!0,o.exports}n.m=e,n.c=t,n.d=function(e,t,r){n.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:r})},n.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},n.t=function(e,t){if(1&t&&(e=n(e)),8&t)return e;if(4&t&&"object"==typeof e&&e&&e.__esModule)return e;var r=Object.create(null);if(n.r(r),Object.defineProperty(r,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var o in e)n.d(r,o,function(t){return e[t]}.bind(null,o));return r},n.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return n.d(t,"a",t),t},n.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},n.p="/wp-content/themes/nexstar/client/build/",n(n.s=840)}({840:function(e,t,n){e.exports=n(841)},841:function(e,t){window.setCookie=function(e,t){var n=arguments.length>2&&void 0!==arguments[2]?arguments[2]:1,r=arguments.length>3&&void 0!==arguments[3]?arguments[3]:"/",o=new Date(Date.now()+60*n*60*1e3).toUTCString();document.cookie=e+"="+t+"; expires="+o+"; path="+r},window.getCookie=function(e){for(var t=e+"=",n=document.cookie.split(";"),r=0;r<n.length;r++){for(var o=n[r];" "==o.charAt(0);)o=o.substring(1);if(0==o.indexOf(t))return o.substring(t.length,o.length)}return""},window.isAutoPlay=function(e){return e.closest(".video-player--hero")||e.closest(".video-center-content")||e.closest(".article-featured-media--lakanaanvplayer")}}});
//# sourceMappingURL=global-utils.bundle.min.js.map</script><script class="wp-asset-manager ad_referral_source_inline" type="text/javascript">window.amScripts = window.amScripts || {}; window.amScripts["ad_referral_source_inline"] = {"socialSites":["12seconds.tv","4travel.jp","advogato.org","ameba.jp","anobii.com","answers.yahoo.com","asmallworld.net","avforums.com","badoo.com","bebo.com","biip.no","blackplanet.com","blog.seesaa.jp","blogspot.com","blomotion.jp","boards.qwant.com","bolt.com","brightkite.com","buzznet.com","cafemom.com","care2.com","classmates.com","cyworld.co.kr","dailymotion.com","delicious.com","deviantart.com","digg.com","diigo.com","disqus.com","draugiem.lv","l.facebook.com","www.facebook.com","faceparty.com","fc2.com","flickr.com","fotolog.com","foursquare.com","friendfeed.com","friendsreunited.com","fubar.com","gaiaonline.com","geni.com","goodreads.com","plus.google.com","grono.net","habbo.com","hatena.ne.jp","hi5.com","hyves.nl","ibibo.com","identi.ca","t.ifeng.com","instagram.com","intensedebate.com","irc-galleria.net","jp.myspace.com","kaixin001.com","kakaku.com","last.fm","www.linkedin.com","livejournal.com","lnkd.in","meetup.com","mister-wong.com","mixi.jp","mixx.com","mouthshut.com","mp.weixin.qq.com","multiply.com","mumsnet.com","myheritage.com","myspace.com","nasza-klasa.pl","matome.naver.jp","netlog.com","netvibes.com","nextdoor.com","nicovideo.jp","ning.com","odnoklassniki.ru","ok.ru","orkut.com","pakila.jp","photobucket.com","pinterest.com","pinterest.co.uk","pinterest.ca","pinterest.fr","pinterest.es","pinterest.de","pinterest.se","pinterest.pt","pinterest.dk","pinterest.ie","pinterest.co.kr","pinterest.ch","pinterest.at","pinterest.nz","pinterest.ph","pinterest.cl","pinterest.hu","pinterest.be","pinterest.in","pinterest.co","plurk.com","po.st","reddit.com","renren.com","skyrock.com","slideshare.net","smcb.jp","smugmug.com","snapchat.com","stumbleupon.com","t.co","t.ifeng.com","t.sina.com.cn","t.sohu.com","tabelog.com","tagged.com","taringa.net","thefancy.com","tiktok.com","toutiao.com","tripit.com","trombi.com","trytrend.jp","tumblr.com","twitter.com","uhuru.jp","viadeo.com","vimeo.com","vk.com","wayn.com","weibo.com","wordpress.com","xanga.com","xing.com","answers.yahoo.com","yammer.com","yaplog.jp","yelp.com","yelp.co.uk","youku.com","youtube.com","yozm.daum.net","yuku.com","zooomr.com","zhihu.com","m.badoo.com","m.blogspot.com","m.brightkite.com","m.classmates.com","m.cyworld.co.kr","m.dailymotion.com","m.deviantart.com","m.diigo.com","m.disqus.com","m.draugiem.lv","m.facebook.com","m.flickr.com","m.foursquare.com","m.fubar.com","m.gaiaonline.com","m.plus.google.com","m.hatena.ne.jp","m.hi5.com","m.ibibo.com","m.ifeng.com","m.instagram.com","m.irc-galleria.net","m.kaixin001.com","m.last.fm","m.linkedin.com","m.livejournal.com","m.mixi.jp","m.mixx.com","m.mouthshut.com","m.myheritage.com","m.mylife.com","m.myspace.com","m.nasza-klasa.pl","m.odnoklassniki.ru","m.ok.ru","m.reddit.com","m.renren.com","m.slideshare.net","m.smugmug.com","m.co","m.ifeng.com","m.qq.com","m.sina.com.cn","m.sohu.com","m.tagged.com","m.taringa.net","m.tiktok.com","m.toutiao.com","m.tripit.com","m.tumblr.com","m.twitter.com","m.vk.com","m.weibo.com","m.wordpress.com","m.xanga.com","m.xing.com","m.answers.yahoo.com","m.youku.com","m.youtube.com","m.yuku.com","m.zhihu.com","www.12seconds.tv","www.advogato.org","www.anobii.com","www.answers.yahoo.com","www.asmallworld.net","www.avforums.com","www.badoo.com","www.bebo.com","www.blackplanet.com","www.blogspot.com","www.bolt.com","www.brightkite.com","www.buzznet.com","www.cafemom.com","www.care2.com","www.classmates.com","www.cyworld.co.kr","www.dailymotion.com","www.delicious.com","www.deviantart.com","www.digg.com","www.diigo.com","www.disqus.com","www.draugiem.lv","www.faceparty.com","www.fc2.com","www.flickr.com","www.flixster.com","www.fotolog.com","www.foursquare.com","www.friendsreunited.com","www.fubar.com","www.gaiaonline.com","www.goodreads.com","www.plus.google.com","www.grono.net","www.habbo.com","www.hatena.ne.jp","www.hi5.com","www.hyves.nl","www.ibibo.com","www.identi.ca","www.instagram.com","www.intensedebate.com","www.kaixin001.com","www.kakaku.com","www.last.fm","www.livejournal.com","www.meetup.com","www.mister-wong.com","www.mixi.jp","www.mixx.com","www.mouthshut.com","www.multiply.com","www.mumsnet.com","www.myheritage.com","www.myspace.com","www.nasza-klasa.pl","www.netlog.com","www.netvibes.com","www.nextdoor.com","www.nicovideo.jp","www.ning.com","www.odnoklassniki.ru","www.ok.ru","www.orkut.com","www.photobucket.com","www.pinterest.com","www.pinterest.co.uk","www.pinterest.ca","www.pinterest.fr","www.pinterest.es","www.pinterest.de","www.pinterest.se","www.pinterest.pt","www.pinterest.dk","www.pinterest.ie","www.pinterest.co.kr","www.pinterest.ch","www.pinterest.at","www.pinterest.nz","www.pinterest.ph","www.pinterest.cl","www.pinterest.hu","www.pinterest.be","www.pinterest.in","www.pinterest.co","www.plurk.com","www.po.st","www.reddit.com","www.renren.com","www.skyrock.com","www.slideshare.net","www.smugmug.com","www.snapchat.com","www.stumbleupon.com","www.t.ifeng.com","www.tabelog.com","www.tagged.com","www.taringa.net","www.thefancy.com","www.tiktok.com","www.toutiao.com","www.tripit.com","www.trombi.com","www.tumblr.com","www.twitter.com","www.uhuru.jp","www.viadeo.com","www.vimeo.com","www.vk.com","www.wayn.com","www.weibo.com","www.wordpress.com","www.xanga.com","www.xing.com","www.answers.yahoo.com","www.yammer.com","www.youku.com","www.youtube.com","www.zooomr.com","www.zhihu.com"],"nxstDomains":["www.nxsttv.com","www.kget.com","www.wavy.com","www.abc4.com","www.ktalnews.com","www.cnyhomepage.com","www.counton2.com","www.khon2.com","www.klfy.com","www.koin.com","www.kron4.com","www.krqe.com","www.ksn.com","www.dcnewsnow.com","www.myarklamiss.com","www.kxnet.com","www.mystateline.com","www.nbc4i.com","www.ourquadcities.com","www.wfxrtv.com","www.wane.com","www.wbtw.com","www.wpri.com","www.wrbl.com","www.wtrf.com","www.wwlp.com","www.yourerie.com","www.borderreport.com","www.cbs17.com","www.cenlanow.com","www.wdhn.com","www.ketk.com","www.everythinglubbock.com","www.fourstateshomepage.com","www.fox21news.com","www.ktsm.com","www.valleycentral.com","www.kxan.com","www.texomashomepage.com","www.wate.com","www.wboy.com","www.wcia.com","www.wdtn.com","www.wiproud.com","www.wjbf.com","www.wkbn.com","www.wkrg.com","www.wlns.com","www.woodtv.com","www.wowktv.com","www.wspa.com","www.yourcentralvalley.com","www.abc27.com","www.bigcountryhomepage.com","www.centralillinoisproud.com","www.informnny.com","www.8newsnow.com","www.localmemphis.com","www.mychamplainvalley.com","www.mywabashvalley.com","www.localsyr.com","www.news10.com","www.ozarksfirst.com","www.rochesterfirst.com","www.rocketcitynow.com","www.siouxlandproud.com","www.wtaj.com","www.wearegreenbay.com","www.wfla.com","www.wjtv.com","www.wkrn.com","www.wric.com","www.wsav.com","www.wvnstv.com","www.wytv.com","www.yourbasin.com","www.binghamtonhomepage.com","www.brproud.com","www.cbs42.com","www.fox44news.com","www.conchovalleyhomepage.com","www.fox16.com","www.kark.com","www.ksnt.com","www.myhighplains.com","www.mypanhandle.com","www.mytwintiers.com","www.nwahomepage.com","www.pahomepage.com","www.tristatehomepage.com","www.weareiowa.com","www.westernslopenow.com","www.wishtv.com","www.wivb.com","www.wjhl.com","www.wnct.com","www.wtnh.com","www.yourbigsky.com","www.yourphx.com","www.keloland.com","www.wvillustrated.com","www.channel4000.com","www.mysterywire.com","www.nxsmediawire.com","www.newsnationnow.com","www.qcnews.com","nxstrib.com","wgno.com","kfor.com","ktla.com","wgntv.com","wgnradio.com","phl17.com","cw33.com","dcw50.com","cw39.com","kdvr.com","fox8.com","fox40.com","fox2now.com","fox5sandiego.com","fox4kc.com","myfox8.com","wreg.com","who13.com","whnt.com","fox59.com","cbs4indy.com","fox56news.com","pix11.com","www.snntv.com","digital-network.thehill.com","thehill.com"]}</script><script class="wp-asset-manager page_attributes" type="text/javascript">window.amScripts = window.amScripts || {}; window.amScripts["page_attributes"] = {"page_url":"https:\/\/www.kron4.com\/","page_slug":"\/","page_type":"index","page_category":"","article_id":"","subpath":"\/home"}</script><script class="wp-asset-manager gpt" type="text/javascript">window.amScripts = window.amScripts || {}; window.amScripts["gpt"] = {"ab_test":{"min":1,"max":101,"storage_key":"ns.gpt.sessiontest"}}</script><script class="wp-asset-manager bob" type="text/javascript">window.amScripts = window.amScripts || {}; window.amScripts["bob"] = {"base_host":"bob.dmpxs.com"}</script><style class="wp-asset-manager nswv-global-critical-css" type="text/css">.site-header{background-color:#fff;left:0;min-width:20rem;position:fixed;position:relative;top:0;width:100%;z-index:7}@media screen and (max-width:782px){.admin-bar .site-header{top:2.875rem}}@media (max-width:899px){.site-header{position:sticky}}.site-header__branding{background-color:var(--primary_color);color:#fff;height:5.3125rem}.site-header__branding:active,.site-header__branding:hover{background:-webkit-gradient(linear,left top,left bottom,from(#1c1c1c),to(var(--primary_color)));background:-o-linear-gradient(top,#1c1c1c 0,var(--primary_color) 100%);background:linear-gradient(180deg,#1c1c1c,var(--primary_color))}@media (max-width:899px){.site-header__branding{height:4.0625rem}}.site-header__branding__content{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:nowrap;flex-wrap:nowrap;height:100%;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;margin:0;max-width:100%;padding-left:1.875rem;padding-right:1.875rem}@media (max-width:899px){.site-header__branding__content{padding-left:.8125rem;padding-right:.8125rem}}.site-header__branding__content>*{width:33.33333%}.site-header__info{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}@media (min-width:900px){.site-header__info .site-header__weather{display:none}}.site-header__logo{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-flex:1;-ms-flex:1 1 0px;flex:1 1 0;height:3.125rem;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;max-width:18.75rem;min-width:6.25rem;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;padding:0;width:100%}@media (max-width:899px){.site-header__logo{max-width:7.5rem}}.site-header__logo a{display:block;height:100%;max-height:6.25rem;max-width:18.75rem;width:100%}.site-header__logo-bg{background-position:50%;background-repeat:no-repeat;background-size:contain;height:100%;width:100%}.site-header__weather{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-flex:0;-ms-flex:0 0 30%;flex:0 0 30%;-webkit-box-pack:end;-ms-flex-pack:end;justify-content:flex-end;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}@media (max-width:899px){.site-header__weather{-webkit-box-pack:start;-ms-flex-pack:start;justify-content:flex-start;-webkit-box-ordinal-group:1;-ms-flex-order:0;order:0}}.site-header__weather a{color:#fff;text-decoration:none;-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex}.site-header__weather a:hover{color:#fff}.site-header__weather-region{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-weight:900;line-height:1.25;text-transform:uppercase;font-size:1.25rem;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}@media (max-width:899px){.site-header__weather-region{display:none}}.site-header__weather-forecast{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.25rem;font-weight:900;line-height:1.25;text-transform:none;-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:nowrap;flex-wrap:nowrap;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}.site-header__weather-forecast__text{margin-right:.625rem;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}.site-header__weather-forecast__icon{display:block;height:1.875rem;margin-right:.625rem;width:1.875rem}.site-header__widget{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;gap:.9375rem;-webkit-box-pack:end;-ms-flex-pack:end;justify-content:flex-end;-webkit-box-ordinal-group:4;-ms-flex-order:3;order:3}.site-header__widget:has(.site-header__live-button.watch-now){-webkit-box-pack:end;-ms-flex-pack:end;justify-content:flex-end}@media (max-width:899px){.site-header__widget .site-header__weather{display:none}}.site-header__sponsor{display:none;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}.site-header__sponsor .ad-unit__content>div,.site-header__sponsor .ad_unit__label{margin-left:1.5625rem}@media (min-width:900px){.site-header__sponsor{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-pack:end;-ms-flex-pack:end;justify-content:flex-end}}.site-header__toggle{-webkit-appearance:none;-moz-appearance:none;appearance:none;background-color:rgba(0,0,0,0);border:none;border-radius:0;cursor:pointer;overflow:visible;text-decoration:none;float:right;padding-right:.125rem}@media (min-width:900px){.site-header__toggle{display:none}}.site-header__toggle .icon{display:block;height:1.3125rem;width:1.3125rem}.site-header__toggle .icon svg{display:block;height:100%;-o-object-fit:cover;object-fit:cover;-o-object-position:center;object-position:center;width:100%}.site-header__toggle[aria-expanded=false] .icon--close,.site-header__toggle[aria-expanded=true] .icon--navicon{display:none}.site-header__navigation__content{background-color:var(--primary_color)}.site-header__navigation__content .site-header__search-form{margin-left:.9375rem;margin-right:0;max-width:12.5rem;min-width:10.625rem;padding:0 .625rem}.site-header__navigation__content .site-header__search-form .search-form__fields{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center}.site-header__navigation__content .site-header__search-form .search-form__fields input[type=submit]{display:block;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1;position:relative;top:none;-webkit-transform:none;-ms-transform:none;transform:none}.site-header__navigation__content .site-header__search-form .search-form__fields input[type=search]{-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}.site-header__search-form{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0;background-color:hsla(0,0%,100%,.2);position:relative;width:100%}@media (max-width:899px){.site-header__search-form{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:1.25rem;padding-right:1.25rem}}@media (min-width:900px){.site-header__search-form{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:.625rem;padding-right:.625rem}}@media (min-width:71.25rem){.site-header__search-form{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0}}.site-header__search-form .search-message{display:none}.site-header__search-form .search-form__fields{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;width:100%}.site-header__search-form input[type=search]{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.875rem;font-weight:400;line-height:.9375rem;text-transform:none;background:none;border:0;color:#fff;height:2.5rem;line-height:1.875rem;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;outline:none;width:100%}.site-header__search-form input[type=search]::-ms-clear,.site-header__search-form input[type=search]::-ms-reveal{display:none;height:0;width:0}.site-header__search-form input[type=search]::-webkit-search-cancel-button,.site-header__search-form input[type=search]::-webkit-search-decoration,.site-header__search-form input[type=search]::-webkit-search-results-button,.site-header__search-form input[type=search]::-webkit-search-results-decoration{display:none}@media (max-width:899px){.site-header__search-form input[type=search]{line-height:2rem;padding:0 .25rem}}.site-header__search-form input[type=search]::-webkit-input-placeholder{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:400;line-height:1.3;text-transform:none;color:#ddd}.site-header__search-form input[type=search]::-moz-placeholder{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:400;line-height:1.3;text-transform:none;color:#ddd}.site-header__search-form input[type=search]:-ms-input-placeholder{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:400;line-height:1.3;text-transform:none;color:#ddd}.site-header__search-form input[type=search]::placeholder{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:400;line-height:1.3;text-transform:none;color:#ddd}.site-header__search-form input[type=submit][value=""]{background-color:rgba(0,0,0,0);background:rgba(0,0,0,0) no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 16 17'%3E%3Cpath fill-rule='evenodd' d='M15.72 15.4l-3.75-3.8a7 7 0 001.72-4.612 6.851 6.851 0 10-6.85 6.98 6.713 6.713 0 003.72-1.127l3.85 3.9a.9.9 0 00.65.276.92.92 0 00.66-.276.965.965 0 000-1.341zM1.85 6.984a4.991 4.991 0 114.99 5.087 5.036 5.036 0 01-4.99-5.09z'/%3E%3C/svg%3E");-webkit-filter:invert(1);filter:invert(1);height:1.25rem;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1;padding:0;width:2.5rem}.site-header__search-form input[type=submit]:not([value=""]),.site-header__search-form input[type=submit][value=""]{-webkit-appearance:none;-moz-appearance:none;appearance:none;border:none;border-radius:0;cursor:pointer;overflow:visible;text-decoration:none}.site-header__search-form input[type=submit]:not([value=""]){background-color:rgba(0,0,0,0);font-family:"Source Serif Pro",georgia,times,serif;font-size:.75rem;font-weight:400;line-height:32px;text-transform:uppercase;padding:0 22px;width:auto;background-color:var(--primary_color);color:#fff;-webkit-transition:background-color .5s ease-in-out;-o-transition:background-color .5s ease-in-out;transition:background-color .5s ease-in-out}.site-header__search-form input[type=submit]:not([value=""]):active,.site-header__search-form input[type=submit]:not([value=""]):hover{background-color:#000}.site-header__search-full{background-color:var(--primary_color);padding:1rem;width:100%;z-index:1}.site-header__search-full .search-form__fields input[type=search]{font-size:1rem}@media (min-width:900px){.site-header__search-full{display:none}}.site-header__navigation{background-color:var(--primary_color);border:none;height:2.5rem;width:100%}@media (max-width:899px){.site-header__navigation{display:none}.site-header__navigation--open{display:block}}@media (min-width:900px){body.has-active-alert-banners .site-header__navigation{border-bottom:unset}}.site-header__navigation__content{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:nowrap;flex-wrap:nowrap;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;padding:0 1.875rem;position:relative}@media (max-width:899px){.site-header__navigation__content{background:-webkit-gradient(linear,left top,left bottom,color-stop(50.77%,var(--primary_color)),to(#1c1c1c));background:-o-linear-gradient(top,var(--primary_color) 50.77%,#1c1c1c 100%);background:linear-gradient(180deg,var(--primary_color) 50.77%,#1c1c1c);bottom:0;left:0;-webkit-overflow-scrolling:touch;overflow-y:scroll;padding:1rem 0;position:fixed;top:5rem;width:100%;z-index:-1}.site-header__navigation__content .site-header__search-form{display:none}.has-loaded-super-billboard-ad .site-header__navigation__content{height:100vh;position:static}}@media (min-width:900px){.site-header__navigation .menu{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;height:2.5rem;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;overflow:hidden;width:100%}.site-header__navigation .menu .lr-login-button{display:none}}@media (max-width:899px){.site-header__navigation .menu{display:block;height:auto;width:100%}.site-header__navigation .menu>*{margin-bottom:1.25rem}.site-header__navigation .menu>:last-child{margin-bottom:0}}.site-header__navigation .menu a{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:700;line-height:1.25rem;text-transform:none}.site-header__navigation .menu>li{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;height:2.5rem;padding:.625rem}@media (max-width:899px){.site-header__navigation .menu>li{-webkit-box-align:start;-ms-flex-align:start;align-items:flex-start;height:auto;margin-bottom:1.5rem;padding:.5rem 0;width:100%}}@media (min-width:900px){.site-header__navigation .menu>li:hover{background-color:rgba(28,28,28,.3)}}.site-header__navigation .menu>li.menu-item__hidden{display:none}.site-header__navigation .menu>li#more-item{cursor:default}.site-header__navigation .menu>li#more-item .menu-item__hidden{display:none}.site-header__navigation .menu>li#more-item .sub-menu__columns{-webkit-box-flex:1;-ms-flex:1 1;flex:1 1}.site-header__navigation .menu>li>a{color:#fff;text-decoration:none;display:block;padding:0;white-space:nowrap;z-index:1}.site-header__navigation .menu>li>a:hover{color:#fff}@media (max-width:899px){.site-header__navigation .menu>li>a{outline:none;padding-left:1.25rem;width:8rem}}.site-header__navigation .menu>li>a:hover{text-decoration:underline}.site-header__navigation .menu-item-has-children{position:relative}@media (min-width:900px){.site-header__navigation .menu-item-has-children{position:static}}@media (min-width:900px){.site-header__navigation .menu-item-has-children>a:after{content:"▾";display:inline-block;height:.75rem;margin:0 .33333rem;width:.75rem}}@media (min-width:900px){.site-header__navigation .menu-item-has-articles{position:static}}.site-header__navigation .menu-item__toggle{-webkit-appearance:none;-moz-appearance:none;appearance:none;background-color:rgba(0,0,0,0);border-radius:0;cursor:pointer;overflow:visible;text-decoration:none;border:none;outline:none;position:absolute;right:0}@media (min-width:900px){.site-header__navigation .menu-item__toggle{display:none}}@media (max-width:899px){.site-header__navigation .menu-item__toggle{-webkit-filter:invert(1);filter:invert(1);padding-right:1.25rem}}.site-header__navigation .menu-item__toggle .icon{display:block;height:.875rem;width:1.3125rem}.site-header__navigation .menu-item__toggle .icon svg{-webkit-transform-origin:center;-ms-transform-origin:center;transform-origin:center;-webkit-transition:-webkit-transform .5s ease-out;transition:-webkit-transform .5s ease-out;-o-transition:transform .5s ease-out;transition:transform .5s ease-out;transition:transform .5s ease-out,-webkit-transform .5s ease-out}.site-header__navigation .menu-item__toggle[aria-expanded=true] .icon svg{-webkit-transform:rotate(-180deg);-ms-transform:rotate(-180deg);transform:rotate(-180deg)}@media (max-width:899px){.site-header__navigation .sub-menu{width:100%}}@media (min-width:900px){.site-header__navigation .sub-menu{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-ms-flex-wrap:wrap;flex-wrap:wrap;max-height:25rem;padding:2.1875rem 0 2.1875rem 4.6875rem}}.site-header__navigation .sub-menu[aria-hidden=false]{max-height:50rem}@media (max-width:899px){.site-header__navigation .sub-menu li{margin:1rem}}.site-header__navigation .sub-menu a{background-color:#fff;display:block;font-weight:400;outline:none}.site-header__navigation .sub-menu a:hover{text-decoration:underline}@media (min-width:900px){.site-header__navigation .sub-menu a{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:700;line-height:1.25rem;text-transform:none;-webkit-box-align:center;-ms-flex-align:center;align-items:center;color:#1c1c1c;display:-webkit-box;display:-ms-flexbox;display:flex;height:2.5rem;max-width:95%}}@media (max-width:899px){.site-header__navigation .sub-menu a{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:700;line-height:1.25rem;text-transform:none;background:none;color:#fff;padding-left:2rem}}.dropnav{width:100%}@media (max-width:899px){.dropnav{display:none}}@media (min-width:900px){.dropnav{background-clip:padding-box;background-color:#fff;left:0!important;overflow:hidden;position:absolute;top:100%;visibility:hidden;width:100%}.dropnav:after{-webkit-backdrop-filter:blur(5px);backdrop-filter:blur(5px);background-color:rgba(28,28,28,.6);bottom:0;content:"";height:calc(100vh - 70px);pointer-events:none;position:fixed;width:100%;z-index:-1}}@media (min-width:900px){.menu-item-has-children:nth-last-of-type(-n+3) .dropnav{left:auto;right:0}}.dropnav[aria-hidden=false]{background:hsla(0,0%,100%,.2);display:block;margin:-.625rem 0 0 -8rem;padding-top:2.5rem;width:calc(100% + 2px)}@media (min-width:900px){li.menu-item-has-children:hover .dropnav{display:-webkit-box;display:-ms-flexbox;display:flex;left:0;-webkit-transition-delay:.5s;-o-transition-delay:.5s;transition-delay:.5s;-webkit-transition-property:visibility;-o-transition-property:visibility;transition-property:visibility;visibility:visible;width:100%}}.dropnav__section{padding:0;width:100%}.dropnav__section .article-list__article-mediaicon.article-list__article-mediaicon--default{display:none!important}@media (min-width:90rem){.dropnav__section{margin:0 8%;width:92%}}@media (max-width:899px){.dropnav__section--article-list{display:none}}.dropnav__section--article-list .article-list__heading{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1.25rem;text-transform:uppercase}.dropnav__section--article-list .article-list__article-mediaicon{display:none}.dropnav__section--article-list .article-list--bulleted .article-list__article-meta{line-height:.9375rem;margin-top:.125rem;padding-left:1.5rem}.dropnav__section--article-list .article-list__article--has-thumb .article-list__article-title{margin-top:.9375rem}.dropnav__section--article-list .article-list:not(.slick-slide) .text-padded{padding-left:0}.dropnav__section--article-list .article-list__article-title a{font-family:"Source Serif Pro",georgia,times,serif;font-size:.9375rem;font-weight:700;line-height:.9375rem;text-transform:none}.dropnav__section .article-list--top-story{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between}.dropnav__section .article-list--top-story .article-list__article-title a{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.25rem;font-weight:700;line-height:1.25rem;text-transform:none}.dropnav__section .article-list{padding:2.1875rem 4.6875rem 2.1875rem 0}.dropnav__section__more-button{display:-webkit-box;display:-ms-flexbox;display:flex}.dropnav .submenu-item__more-button{display:inline-block;height:auto;margin:0;min-height:0;padding:0;width:100%}.dropnav .submenu-item__more-button a{display:block;font-size:1rem;font-weight:600;height:auto;margin-bottom:.625rem;padding:0 0 0 1rem}.dropnav__section__more-button .sub-menu{max-height:none}.dropnav__section__more-button .sub-menu:not(:first-child){padding-left:2.5rem}.dropnav__section__more-button .sub-menu .menu-item a{font-weight:700}.dropnav__section__more-button .sub-menu__columns-5{padding-left:2.5rem;width:18vw}@media (min-width:900px){.dropnav__section__more-button{max-height:none;padding:0}.dropnav__section__more-button .sub-menu__columns-1{width:25%}.dropnav__section__more-button .sub-menu__columns-2{width:50%}.dropnav__section__more-button .sub-menu__columns-3{width:75%}.dropnav__section__more-button .sub-menu__columns-4{width:100%}}@media (min-width:900px){.dropnav__section--quarter{flex-grow:0;flex-shrink:0;flex-basis:calc(24.975% - 12px);max-width:calc(24.975% - 12px);width:calc(24.975% - 12px)}.dropnav__section--quarter:nth-child(1n){margin-right:16px;margin-left:0}.dropnav__section--quarter:last-child{margin-right:0}}@media (min-width:900px){.dropnav__section--half{flex-grow:0;flex-shrink:0;flex-basis:calc(49.95% - 8px);max-width:calc(49.95% - 8px);width:calc(49.95% - 8px)}.dropnav__section--half:nth-child(1n){margin-right:16px;margin-left:0}.dropnav__section--half:last-child{margin-right:0}.dropnav__section--half:nth-child(2n){margin-right:0;margin-left:auto}}@media (min-width:900px){.dropnav__section--autofill{-webkit-box-flex:1;-ms-flex-positive:1;flex-grow:1}}@media (min-width:900px){.site-header.is-scrolling--not-top .dropnav{top:100%}.site-header.is-scrolling--not-top .dropnav:after{height:calc(100vh - 140px)}.site-header.is-scrolling--not-top .site-header__info{display:none}}@media (min-width:900px){.site-header.is-scrolling--not-top{background-color:var(--primary_color);height:4.375rem;left:0;position:fixed;right:0;top:0;width:100%}.site-header.is-scrolling--not-top+*{margin-top:0}}@media (max-width:600px){.admin-bar .site-header.is-scrolling--not-top{top:0}}@media (min-width:900px){.admin-bar .site-header.is-scrolling--not-top{top:2rem}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__content{-webkit-box-align:center;-ms-flex-align:center;align-items:center;-ms-flex-wrap:nowrap;flex-wrap:nowrap;height:4.375rem;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;display:flex;flex-flow:row wrap;max-width:70rem;margin:0;max-width:none;padding:0;position:relative}}.site-header.is-scrolling--not-top .site-header__branding:active,.site-header.is-scrolling--not-top .site-header__branding:hover{background:var(--primary_color)}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__branding{height:unset}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__branding__content{display:block;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-flow:unset;flex-flow:unset;margin:unset;max-width:unset;padding:unset}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__logo{-webkit-box-flex:unset;-ms-flex:unset;flex:unset;height:4.375rem;margin-right:unset;max-width:6.25rem;-webkit-box-ordinal-group:unset;-ms-flex-order:unset;order:unset;padding:1.125rem 0 1.375rem 1.875rem}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__logo-bg{height:100%}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__weather,.site-header.is-scrolling--not-top .site-header__widget{display:none}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation{border-bottom:unset;height:4.375rem;width:calc(100% - 130px)}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation .site-header__navigation__content{height:4.375rem;position:unset}}.site-header.is-scrolling--not-top .site-header__navigation .site-header__navigation__content .site-header__search-form{margin:0}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation .menu{height:4.375rem}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation .menu>li{height:4.375rem;line-height:4.375rem}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation .menu>li:hover{background:rgba(28,28,28,.3)}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation .menu>li>a{color:#fff;text-decoration:none;font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:700;line-height:1.25rem;text-transform:none}.site-header.is-scrolling--not-top .site-header__navigation .menu>li>a:hover{color:#fff}}@media (min-width:900px){.site-header.is-scrolling--not-top .site-header__navigation svg path{fill:#fff}}.site-header__widget .btn-signup{-webkit-box-align:center;-ms-flex-align:center;align-items:center;-ms-flex-item-align:center;align-self:center;border:.0625rem solid hsla(0,0%,100%,.31);border-radius:.1875rem;color:#fff;display:-webkit-box;display:-ms-flexbox;display:flex;font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.9375rem;font-weight:700;height:1.875rem;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;margin-right:35px;padding:.375rem .3125rem;text-transform:uppercase;width:6.5625rem}@media screen and (max-width:1123px){.site-header__widget .btn-signup{margin-right:0}}@media screen and (max-width:1000px){.site-header__widget .btn-signup{display:none}}.site-header__widget .btn-signup i{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='16' height='11' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'%3E%3Cdefs%3E%3Cpath id='a' d='M0 0h5.01v8.804H0z'/%3E%3Cpath id='c' d='M0 0h4.983v8.779H0z'/%3E%3C/defs%3E%3Cg fill='%23fff' fill-rule='evenodd'%3E%3Cpath d='M1.366.023L14.687 0c.045 0 .066.055.033.084L8.046 6.016a.048.048 0 01-.064 0L1.334.107a.048.048 0 01.032-.084'/%3E%3Cpath d='M5.705 5.296a.048.048 0 01.064 0l2.215 1.969.019-.022.03.031 2.226-1.978a.048.048 0 01.064 0l5.533 4.912c.033.03.012.085-.032.085l-15.65.025c-.044.001-.065-.054-.032-.084l5.563-4.938z'/%3E%3Cg transform='translate(0 .228)'%3E%3Cmask id='b'%3E%3Cuse xlink:href='%23a'/%3E%3C/mask%3E%3Cpath d='M.08.012L4.995 4.38a.049.049 0 01-.001.072l-4.89 4.34a.049.049 0 01-.08-.035L0 .049C0 .007.05-.015.08.012' mask='url(%23b)'/%3E%3C/g%3E%3Cg transform='translate(11.017 .251)'%3E%3Cmask id='d'%3E%3Cuse xlink:href='%23c'/%3E%3C/mask%3E%3Cpath d='M.016 4.356L4.903.012a.048.048 0 01.08.037V8.73c0 .041-.05.063-.08.036L.016 4.428a.048.048 0 010-.072' mask='url(%23d)'/%3E%3C/g%3E%3C/g%3E%3C/svg%3E");display:block;height:.645rem;margin-right:.375rem;width:1rem}.site-header .live-now-button{display:-webkit-box;display:-ms-flexbox;display:flex;left:0;position:absolute}.site-header .live-now-button a{color:#fff;text-decoration:none}.site-header .live-now-button.has-thumb .live-card__badge-text:before{content:"LIVE";font-size:.8125rem;font-weight:800;letter-spacing:.03125rem}.site-header .live-now-button.no-thumb:not(.has-thumb) .live-card__badge{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;left:0;padding:0;position:relative;top:0}.site-header .live-now-button.no-thumb:not(.has-thumb) .live-card__badge-text:before{content:"LIVE NOW";font-size:.9375rem;font-weight:800;letter-spacing:.03125rem}.site-header .live-now-button.watchnow .live-card__badge-text:before{content:"WATCH NOW";font-size:.71875rem;font-weight:800;letter-spacing:.03125rem}.site-header .site-header__live-button-desktop{display:-webkit-box;display:-ms-flexbox;display:flex}@media (max-width:899px){.site-header .site-header__live-button-desktop{display:none}}.site-header .site-header__live-button-description,.site-header .site-header__live-button-mobile{display:-webkit-box;display:-ms-flexbox;display:flex}.site-header .site-header__live-button-description{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.4375rem;font-weight:600;line-height:.5;text-transform:none;-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-orient:horizontal;-webkit-box-direction:normal;-ms-flex-direction:row;flex-direction:row;margin-left:1.5625rem;margin-top:0;position:relative}.site-header .site-header__live-button-description a:hover{color:#fff;text-decoration:underline}.site-header .live-now-button-mobile.no-thumb .live-card,.site-header .live-now-button.no-thumb .live-card,.site-header .site-header__live-button-mobile.no-thumb .live-card{height:auto;margin-left:2.5rem;width:auto}.site-header .live-now-button-mobile.no-thumb .live-card__img,.site-header .live-now-button.no-thumb .live-card__img,.site-header .site-header__live-button-mobile.no-thumb .live-card__img{display:none}.site-header .live-now-button-mobile.no-thumb .live-card__badge,.site-header .live-now-button.no-thumb .live-card__badge,.site-header .site-header__live-button-mobile.no-thumb .live-card__badge{height:1.625rem;position:relative;width:5rem}@media (max-width:899px){.site-header .live-now-button-mobile.no-thumb .live-card,.site-header .live-now-button.no-thumb .live-card,.site-header .site-header__live-button-mobile.no-thumb .live-card{height:auto;margin-left:0;width:auto}}.site-header .live-now-button-mobile.no-thumb:not(.has-thumb) .live-card__badge,.site-header .site-header__live-button-mobile.no-thumb:not(.has-thumb) .live-card__badge{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;left:0;padding:0;position:relative;top:0}.site-header .live-now-button-mobile.no-thumb:not(.has-thumb) .live-card__badge-text:before,.site-header .site-header__live-button-mobile.no-thumb:not(.has-thumb) .live-card__badge-text:before{content:"LIVE NOW";font-size:.9375rem;font-weight:800;letter-spacing:.03125rem}.site-header .no-thumb .live-card__badge-text{display:-webkit-box;display:-ms-flexbox;display:flex;font-size:1.4375rem}.site-header .live-now-button-mobile{display:none}.site-header .live-now-button-mobile a{color:#fff;line-height:1;text-decoration:none}@media (max-width:899px){.site-header .live-now-button-mobile{-webkit-box-align:center;-ms-flex-align:center;align-items:center;background:#103894;color:#fff;display:-webkit-box;display:-ms-flexbox;display:flex;height:4.0625rem;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:start;padding-left:.625rem;position:relative;z-index:-100}.site-header .live-now-button-mobile.has-thumb{-webkit-box-pack:left;-ms-flex-pack:left;justify-content:left}}.site-header .live-now-button-mobile.watchnow .live-card__badge-text:before{content:"WATCH NOW";font-size:.9375rem;font-weight:800;letter-spacing:.03125rem}.site-header .live-card{border-radius:.125rem;display:-webkit-box;display:-ms-flexbox;display:flex;height:5.3125rem;left:0;overflow:hidden;top:0;width:8.25rem}@media (max-width:899px){.site-header .live-card{height:4.0625rem;position:relative;width:6.875rem}}.site-header .live-card__img{display:block;height:100%;-o-object-fit:cover;object-fit:cover;width:100%}.site-header .live-card__badge{background:#ff3b1f;border-radius:.375rem;-webkit-box-shadow:0 1px 2px rgba(0,0,0,.25);box-shadow:0 1px 2px rgba(0,0,0,.25);color:#fff;font-size:.8125rem;font-weight:800;left:.375rem;letter-spacing:.03125rem;line-height:1;padding:.375rem .625rem;position:absolute;text-transform:uppercase;top:.375rem}.site-header .live-now-button-mobile.has-thumb .live-card__badge-text:before,.site-header .site-header__live-button-mobile.has-thumb .live-card__badge-text:before{content:"LIVE";font-size:.8125rem;font-weight:800;letter-spacing:.03125rem}.site-header .has-thumb .live-card__badge{left:.375rem;position:absolute;top:.375rem}.site-header .live-now-button-mobile.no-thumb:not(.has-thumb) .live-card__badge,.site-header .live-now-button.no-thumb:not(.has-thumb) .live-card__badge,.site-header .site-header__live-button-mobile.no-thumb:not(.has-thumb) .live-card__badge{left:auto;top:auto}@media (max-width:899px){.site-header .has-thumb{left:0;position:relative}}.site-header .live-now-button-mobile.watchnow .live-card__badge-text:before,.site-header .live-now-button-mobile.watchnow.no-thumb:not(.has-thumb) .live-card__badge-text:before,.site-header .live-now-button.watchnow .live-card__badge-text:before,.site-header .live-now-button.watchnow.no-thumb:not(.has-thumb) .live-card__badge-text:before{content:"WATCH NOW";font-size:.8125rem}.site-header .live-now-button-mobile.watchnow.no-thumb:not(.has-thumb) .live-card__badge,.site-header .live-now-button.watchnow.no-thumb:not(.has-thumb) .live-card__badge{width:5.5rem}@media (max-width:899px){section.article-list:last-child{padding-bottom:.9375rem}}.article-list.article-list--headline-two-col .article-list-infinite{margin-top:0}.article-list--homepage-headline-list{margin-bottom:0!important;padding-bottom:1.875rem}@media (max-width:899px){.article-list--homepage-headline-list{padding-bottom:.625rem}}.article-list--is-infinite .article-list__content{margin-bottom:0}.article-list-infinite{margin-top:0}.article-list__blanketing-link{color:#000;display:block}.article-list__blanketing-link:hover{color:#000}.article-list__heading{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1.125rem;text-transform:uppercase;color:#1c1c1c;display:block;letter-spacing:.04em;margin-bottom:1.25rem;text-align:left;text-align:initial}@media (max-width:899px){.article-list__heading{padding-top:.625rem}}.article-list__heading .article-list__heading-link{color:#1c1c1c}.article-list__heading .article-list__heading-link:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%231C1C1C'/%3E%3C/svg%3E");background-size:.5625rem;content:"";float:left;height:1.25rem;position:absolute;width:1.25rem}.article-list__heading .article-list__heading-link:hover{text-decoration:underline}.article-list__heading--notched:before{display:none}.article-list__heading--dot-block{text-align:center;width:100%}.article-list__heading--dot-block:after{background:-o-linear-gradient(left,#fff 3px,rgba(0,0,0,0) 1%) 50%,-o-linear-gradient(#fff 3px,rgba(0,0,0,0) 1%) 50%,#000;background:linear-gradient(90deg,#fff 3px,rgba(0,0,0,0) 1%) 50%,linear-gradient(#fff 3px,rgba(0,0,0,0) 1%) 50%,#000;background-position:bottom;background-size:4px 4px;content:"";display:block;height:.625rem;margin:.5rem auto 1rem;padding:1px;width:50%}.article-list__heading--bottom-divider,.article-list__heading--bottom-divider-flush{text-align:center;width:100%;border-bottom:2px solid #000;padding-bottom:1rem}.article-list__heading--bottom-divider-flush{margin-bottom:0}.article-list__heading--bottom-divider-half-sized{text-align:center;width:100%}.article-list__heading--bottom-divider-half-sized:after{background-color:#000;content:"";display:block;height:1px;margin:1rem auto;width:50%}.article-list__heading--small{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1.125rem;text-transform:uppercase;color:#1c1c1c;display:block;letter-spacing:.04em;margin-bottom:1.25rem;text-align:left}@media (max-width:899px){.article-list__heading--small{padding-top:.625rem}}.article-list__heading--dotted-thick-full-rule{text-align:center;width:100%;line-height:1.7;position:relative}.article-list__heading--dotted-thick-full-rule:before{left:50%;margin-right:-50%;position:absolute;top:50%;-webkit-transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%);transform:translate(-50%,-50%);background-color:#fff;content:"";display:block;height:100%;width:25%;z-index:-1}.article-list__heading--dotted-thick-full-rule:after{background:-o-linear-gradient(left,#fff 3px,rgba(0,0,0,0) 1%) 50%,-o-linear-gradient(#fff 3px,rgba(0,0,0,0) 1%) 50%,#000;background:linear-gradient(90deg,#fff 3px,rgba(0,0,0,0) 1%) 50%,linear-gradient(#fff 3px,rgba(0,0,0,0) 1%) 50%,#000;background-position:bottom;background-size:4px 4px;content:"";display:block;height:.625rem;margin:.5rem auto 1rem;padding:1px;width:50%;position:absolute;top:50%;-webkit-transform:translateY(-50%);-ms-transform:translateY(-50%);transform:translateY(-50%);top:0;width:100%;z-index:-2}.article-list__heading--hidden{visibility:hidden}.article-list__content>*{margin-bottom:1.25rem}.article-list__content>:last-child{margin-bottom:0}.article-list__article{margin-bottom:.625rem}.article-list__article--is-stacked{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column}.article-list__article--is-stacked .article-list__article-thumb{-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}.article-list__article--is-stacked .article-list__article-text{-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}.article-list__article--is-slat{display:-webkit-box;display:-ms-flexbox;display:flex}.article-list__article--is-slat-top-border{border-bottom:unset;border-top:1px dotted #fff;padding-bottom:unset;padding-top:1rem}.article-list__article--is-slat .article-list__article-thumb{display:block;margin-right:10px;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}.article-list__article--is-slat .article-list__article-thumb .article-list__article-image-wrapper{height:3.4375rem;width:3.4375rem}.article-list__article--is-slat .article-list__article-thumb .article-list__article-image-wrapper img{border-radius:3px}.article-list__article--is-slat .article-list__article-text{-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;width:100%}.article-list__article--is-slat .article-list__article-mediaicon--video svg{height:.875rem;width:.8125rem}.article-list__article--is-media-type .article-list__article-thumb img{display:block}.article-list__article--is-media-type .article-list__article-thumb a{color:#fff;text-decoration:none}.article-list__article--is-media-type .article-list__article-thumb a:hover{color:#fff}@media (min-width:48rem){.article-list__article--is-media-type .article-list__article-thumb a{display:block}}.article-list__article--is-media-type .article-list__article-mediaicon{-webkit-box-align:center;-ms-flex-align:center;align-items:center;background:rgba(28,28,28,.698);display:-webkit-box;display:-ms-flexbox;display:flex}.article-list__article--is-media-type .article-list__article-mediaicon--livestream,.article-list__article--is-media-type .article-list__article-mediaicon--livestream:hover{background:rgba(255,63,63,.7)}.article-list__article--is-media-type .article-list__article-mediaicon-svg{height:1.25rem;position:relative;width:1.25rem}.article-list__article--is-media-type .article-list__article-mediaicon-svg svg{left:50%;margin-right:-50%;position:absolute;top:50%;-webkit-transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%);transform:translate(-50%,-50%)}.article-list__article--is-media-type .article-list__article-mediaicon-svg path{fill:#fff}.article-list__article--is-media-type .article-list__article-mediaicon-text{font-family:"Source Serif Pro",georgia,times,serif;font-size:.6875rem;font-weight:700;line-height:1;text-transform:uppercase;display:none;margin-left:.5rem}.article-list__article--is-media-type:active .article-list__article-mediaicon,.article-list__article--is-media-type:hover .article-list__article-mediaicon{background:rgba(28,28,28,.698)}.article-list__article--is-media-type:active .article-list__article-mediaicon--livestream,.article-list__article--is-media-type:hover .article-list__article-mediaicon--livestream{background:rgba(255,63,63,.7)}.article-list__article--is-media-type:active .article-list__article-mediaicon-text,.article-list__article--is-media-type:hover .article-list__article-mediaicon-text{color:#fff}@media (min-width:900px){.article-list__article--is-media-type:active .article-list__article-mediaicon-text,.article-list__article--is-media-type:hover .article-list__article-mediaicon-text{display:none}}.article-list__article--is-media-type figure .article-list__article-image-wrapper{position:relative}.article-list__article--is-media-type figure .article-list__article-image-wrapper .article-list__article-mediaicon{left:0;position:absolute;top:0}.article-list__article--is-media-type.article-list__article--is-slat:not(.article-list__article--has-thumb) .article-list__article-text{position:relative}.article-list__article--is-media-type.article-list__article--is-slat:not(.article-list__article--has-thumb) .article-list__article-mediaicon{left:0;position:absolute;top:0}.article-list__article--is-media-type.article-list__article--is-slat:not(.article-list__article--has-thumb) .article-list__article-mediaicon .article-list__article-mediaicon--livestream,.article-list__article--is-media-type.article-list__article--is-slat:not(.article-list__article--has-thumb) .article-list__article-mediaicon .article-list__article-mediaicon--livestream:hover{background:rgba(0,0,0,0)}.article-list__article--is-media-type.article-list__article--is-slat:not(.article-list__article--has-thumb) .article-list__article-mediaicon .article-list__article-mediaicon--livestream svg circle{fill:#cc1f3b}.article-list__article--is-media-type.article-list__article--is-slat:not(.article-list__article--has-thumb) .article-list__article-mediaicon--svg svg{height:.75rem;width:.75rem}.article-list__article.article-list__article--is-stacked:not(.article-list__article--has-thumb){position:relative}.article-list__article.article-list__article--is-stacked:not(.article-list__article--has-thumb) .article-list__article-mediaicon{left:0;position:absolute;top:0}.article-list__article:not(.article-list__article--is-media-type) .article-list__article-mediaicon--default{display:block;left:0;position:absolute;top:0}.article-list__article-text{overflow-wrap:break-word}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded .article-list__article-mediaicon-svg{display:block;left:0;position:absolute;top:0}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded .article-list__article-mediaicon--default svg{height:.6875rem;width:.6875rem}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded .article-list__article-mediaicon--default circle{fill:#1c1c1c}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded .article-list__article-mediaicon--livestream circle{fill:#cc1f3b}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded .article-list__article-mediaicon--livestream svg{height:.75rem;width:.75rem}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded .article-list__article-mediaicon--video svg{height:.8125rem;width:.8125rem}.article-list:not(.article-list--story-grid--hero-story-package):not(.article-list--story-grid--hero-big-story):not(.article-list--story-grid-hero-daily-news-video):not(.article-list--story-grid-hero-daily-news-main-video):not(.article-list--story-grid-hero-big-story-video):not(.article-list--story-grid-hero-big-story-video-new):not(.article-list--story-grid--hero-full):not(.article-list--grid) .article-list:not(.slick-slide) .text-padded path{fill:#1c1c1c}.article-list__article-title{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.25rem;font-weight:700;line-height:1;text-transform:none}.article-list__article-title a{color:#1c1c1c}.article-list__article-title a:hover{color:#1c1c1c;text-decoration:none;text-decoration:underline}.article-list__article-title a:hover:hover{color:#1c1c1c}.article-list__article-thumb>a{font-size:0}.article-list__article-thumb-caption{font-family:"Source Serif Pro",georgia,times,serif;font-size:.8125rem;font-weight:400;line-height:1.3;text-transform:none}.article-list__article-excerpt a,.article-list__article-excerpt a:hover{color:#000}.article-list__article-meta{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:1.35;text-transform:none;color:#1c1c1c}.article-list__article-meta a{color:#1c1c1c}.article-list__article-meta a:hover{color:#1c1c1c;text-decoration:none;text-decoration:underline}.article-list__article-meta a:hover:hover{color:#1c1c1c}.article-list__read-more{border:.09375rem solid #1c1c1c;border-radius:.125rem;-webkit-box-sizing:border-box;box-sizing:border-box;display:-webkit-box;display:-ms-flexbox;display:flex;margin-top:1.5625rem;min-width:4rem;width:-webkit-fit-content;width:-moz-fit-content;width:fit-content}.article-list__read-more:hover{background:#1c1c1c;border:.09375rem solid #fff}.article-list__read-more:hover a{color:#fff;text-decoration:none}.article-list__read-more:hover a:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%23fff'/%3E%3C/svg%3E");background-size:.4375rem;content:"";float:none;height:.4375rem;position:relative;width:.4375rem}.article-list__read-more a{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:700;line-height:1.25rem;text-transform:none;color:#1c1c1c;padding:.75rem 1.25rem;text-align:center}.article-list__read-more a:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%231C1C1C'/%3E%3C/svg%3E");background-size:.4375rem;content:"";float:none;height:.4375rem;position:relative;width:.4375rem;display:inline-block;padding-bottom:.15625rem;padding-left:1.125rem}.article-list__read-more:last-of-type{margin-bottom:0}.article-list__article-excerpt--is-faded{position:relative}.article-list__article-excerpt--is-faded:after{background:-webkit-gradient(linear,left top,left bottom,from(hsla(0,0%,100%,0)),to(#fff));background:-o-linear-gradient(top,hsla(0,0%,100%,0) 0,#fff 100%);background:linear-gradient(180deg,hsla(0,0%,100%,0),#fff);bottom:0;content:"";display:block;height:100%;position:absolute;width:100%}.article-list__link-below-excerpt{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.9375rem;font-weight:700;line-height:1.3;text-transform:none;color:#fff;float:right;margin-top:.25rem}.article-list__link-below-excerpt:hover{color:#fff;text-decoration:underline}.article-list__link-below-excerpt .icon{display:none}.article-list--headline-two-col .article-list__load-more-cta__button{left:50%;margin-right:-50%;position:absolute;top:50%;-webkit-transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%);transform:translate(-50%,-50%)}.article-list__load-more-cta{margin:1.5625rem 0;min-height:2rem;position:relative;width:100%}.article-list__load-more-cta__button{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:700;line-height:1.25rem;background:#fff;border:.09375rem solid #1c1c1c;border-radius:.125rem;color:#1c1c1c;padding:.75rem 1.25rem;text-align:center;text-transform:none}.article-list__load-more-cta__button:hover{background:#1c1c1c;border:.09375rem solid #fff;color:#fff;cursor:pointer}.article-list__article-label-link{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1.25rem;text-transform:uppercase;display:-webkit-box;display:-ms-flexbox;display:flex}.article-list__article-label-link:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%231C1C1C'/%3E%3C/svg%3E");background-size:.5625rem;content:"";float:left;height:1.25rem;position:absolute;width:1.25rem;background-color:#fff;border-radius:0 3px 2px 0;height:1.5rem;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;position:relative;width:1.469rem}.article-list__article-label-text{background-color:#fff;color:#1c1c1c;margin-bottom:.9375rem;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1;padding:.125rem 0 .125rem 1.25rem}.article-list.post-video-bin.video-playlist--carousel.article-list-carousel--dropin{padding-bottom:0}@media (max-width:899px){.article-list.post-video-bin.video-playlist--carousel.article-list-carousel--dropin{margin-left:0}}.article-list .icon-up-next{background:currentColor;display:inline-block;left:1rem;position:relative;width:.1875rem}.article-list .icon-up-next,.article-list .icon-up-next:after{-webkit-box-sizing:border-box;box-sizing:border-box;height:.625rem}.article-list .icon-up-next:after{border-bottom:.3125rem solid rgba(0,0,0,0);border-left:.5625rem solid;border-top:.3125rem solid rgba(0,0,0,0);content:"";display:block;left:-.625rem;position:absolute;width:0}.article-list .slick-slide article{display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important;-webkit-box-pack:end;-ms-flex-pack:end;justify-content:end}.article-list .slick-slide article .text-padded{margin-top:auto;position:unset}.article-list:not(.slick-slide)__article--is-stacked .text-padded{padding-left:0!important}.article-list:not(.slick-slide)__article--is-stacked .text-padded .article-list__article-mediaicon--default{display:none}.article-list:not(.slick-slide) .text-padded{padding-left:1.5rem;position:relative}.custom-primary-color .article-list .article-list__read-more{border-color:var(--primary_color)}.custom-primary-color .article-list .article-list__read-more:hover{background-color:var(--primary_color_pale)}.custom-primary-color .article-list .article-list__read-more:hover a{color:#1c1c1c}.custom-primary-color .article-list .article-list__read-more:hover a:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%231C1C1C'/%3E%3C/svg%3E");background-size:.4375rem;content:"";float:none;height:.4375rem;position:relative;width:.4375rem}@media (min-width:900px){.two-columns .article-list__read-more{margin-top:.9375rem}}@media (min-width:900px){.two-columns .article-list__content{display:grid;grid-column-gap:1rem;grid-template-columns:1fr 1fr}}@media (min-width:900px){.three-columns .article-list__read-more{margin-top:.9375rem}}@media (min-width:900px){.three-columns .article-list__content{display:grid;grid-column-gap:1rem;grid-template-columns:1fr 1fr 1fr}}#secondary .two-columns .article-list__content{display:block}.article-list--story-grid--hero-full{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding-bottom:3.125rem}@media (max-width:899px){.article-list--story-grid--hero-full{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:1.25rem;padding-right:1.25rem}}@media (min-width:900px){.article-list--story-grid--hero-full{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:.625rem;padding-right:.625rem}}@media (min-width:71.25rem){.article-list--story-grid--hero-full{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0}}@media (max-width:899px){.article-list--story-grid--hero-full{-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column}}.article-list--story-grid--hero-full .main-stories{height:auto;margin-bottom:0;width:66.072%}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories{margin-left:-1.25rem;width:100vw;height:auto}}.article-list--story-grid--hero-full .main-stories .article-list__content{height:100%;width:100%}@media (min-width:900px){.article-list--story-grid--hero-full .main-stories .article-list__content{display:grid;grid-column-gap:1.25rem;grid-row-gap:.625rem;grid-template-columns:1fr 1fr;grid-template-rows:16.5625rem auto auto}}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article{width:100%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2){border-radius:.1875rem;display:inline-block;margin:0;max-width:100%;overflow:hidden;position:relative;width:100%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-image-wrapper{background:#d9d9d9}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-image-wrapper:after,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-image-wrapper:after{background:-o-radial-gradient(370% 300% at 1% 169%,#212121 37.56%,rgba(33,33,33,0) 55.78%);background:radial-gradient(370% 300% at 1% 169%,#212121 37.56%,rgba(33,33,33,0) 55.78%);content:"";height:100%;left:0;opacity:.8;position:absolute;right:0;top:0}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb{margin-bottom:0;width:100%;z-index:0}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb:hover,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb:hover{opacity:1}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper{width:100%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:3px 0;top:0;z-index:1}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon .article-list__article-mediaicon-text,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon .article-list__article-mediaicon-text{display:none}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon:hover,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon:hover{background:rgba(28,28,28,.698)}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream:hover,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream:hover{background:rgba(255,63,63,.7)}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child figure.article-list__article-thumb .article-list__article-image-wrapper .image-wrapper img,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) figure.article-list__article-thumb .article-list__article-image-wrapper .image-wrapper img{-o-object-fit:cover;object-fit:cover}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-link{z-index:10}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text{bottom:0;position:absolute;width:100%;z-index:1}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-title{margin-bottom:.3125rem}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.4375rem;font-weight:700;line-height:1.5625rem;text-transform:none;color:#fff;display:inline-block;padding:0 10px}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title .article-list__article-link:hover,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-title .article-list__article-link:hover{text-decoration:underline}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-meta{-webkit-box-align:end;-ms-flex-align:end;align-items:flex-end;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding:0 10px 10px;visibility:hidden}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-category-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-category-link{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:1;text-transform:none;background:#fff;border-radius:.1875rem;color:#212121;letter-spacing:.02rem;padding:.3125rem;text-decoration:none;visibility:initial}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-category-link:hover,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-category-link:hover{font-size:.6875rem;text-decoration:underline}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text time,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text time{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:2;text-transform:none;color:#fff;letter-spacing:.02rem;visibility:initial}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-thumb,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-thumb,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .image-wrapper{height:100%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-image-wrapper:after,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-image-wrapper:after{background:unset;height:unset}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text{padding-top:40%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-excerpt,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-label-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-excerpt,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-label-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-meta,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-title{position:relative;z-index:2}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__gradient-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__gradient-link{background:-o-radial-gradient(320% 324% at 45% 219%,#212121 44%,rgba(33,33,33,0) 52%);background:radial-gradient(320% 324% at 45% 219%,#212121 44%,rgba(33,33,33,0) 52%);bottom:0;height:100%;opacity:.9;position:absolute;width:100%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-meta{-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:start}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-meta .article-list__article-category-link{margin-right:6px}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-mediaicon{padding:.5rem}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon--default,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-mediaicon--default{display:none}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .text-padded,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .text-padded{padding-left:0}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-text,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-text{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .text-padded .article-list__article-mediaicon,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .text-padded .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:.1875rem 0;left:-8.125rem;z-index:1}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .text-padded .article-list__article-mediaicon-svg path,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .text-padded .article-list__article-mediaicon-svg path{fill:#fff}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .text-padded .article-list__article-mediaicon--livestream,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .text-padded .article-list__article-mediaicon--livestream :hover,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .text-padded .article-list__article-mediaicon--livestream,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .text-padded .article-list__article-mediaicon--livestream :hover{background:rgba(255,63,63,.7)}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-title,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-title{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-title,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-title .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-title,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.25rem;font-weight:700;line-height:1;text-transform:none;letter-spacing:-.02rem}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-thumb,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-thumb{margin-bottom:0;margin-right:20px}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-image-wrapper{background-color:rgba(0,0,0,0);border-radius:4px;height:5rem;position:relative;width:8.125rem}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-image-wrapper:after,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-image-wrapper:after{opacity:.6}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-image-wrapper .image-wrapper,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-image-wrapper .image-wrapper{height:100%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3) .article-list__article-image-wrapper .image-wrapper.no-image,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4) .article-list__article-image-wrapper .image-wrapper.no-image{background-color:rgba(0,0,0,0)}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child{grid-column:1/2;grid-row:1/4}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-image-wrapper:after{background:unset;height:unset}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text{padding-top:40%}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-excerpt,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-label-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title{position:relative;z-index:2}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__gradient-link{background:-o-radial-gradient(320% 324% at 45% 219%,#212121 48%,rgba(33,33,33,0) 62%);background:radial-gradient(320% 324% at 45% 219%,#212121 48%,rgba(33,33,33,0) 62%);bottom:0;height:100%;opacity:.9;position:absolute;width:100%}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child{height:27.5rem}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.75rem;font-weight:900;line-height:1.875rem;text-transform:none;letter-spacing:-.01rem;padding:0}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title .article-list__article-link{font-family:inherit;font-size:inherit;font-weight:inherit;letter-spacing:inherit;line-height:inherit;padding:0 1.25rem}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta{padding:0 1.25rem 1.25rem}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon{bottom:25.5625rem;max-height:2.5rem;max-width:2.5rem;top:unset}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon{bottom:25.25rem}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2){grid-column:2/3;grid-row:1/2}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2){height:19.375rem;margin:1.875rem 1.25rem 0}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-title .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.5625rem;font-weight:700;line-height:1;text-transform:none}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-text .article-list__article-title .article-list__article-link,.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.4375rem;font-weight:700;line-height:1.5625rem;text-transform:none;letter-spacing:-.01rem}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .text-padded{padding-left:0}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .text-padded .article-list__article-mediaicon{bottom:14.3125rem;top:unset}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(2) .text-padded .article-list__article-mediaicon{bottom:17.1875rem}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3){grid-column:2/3;grid-row:2/3}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(3){margin:1.25rem 1.25rem 0}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4){grid-column:2/3;grid-row:3/4;margin-top:-.3125rem}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(4){margin:.625rem 1.25rem 0}}@media (max-width:899px){.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(n+2){padding:0}}.article-list--story-grid--hero-full .main-stories .article-list__content .article-list__article:nth-child(n+2) .article-list__article-thumb{display:block}.article-list--story-grid--hero-full .main-stories .article-list__article-mediaicon--default{display:none}.article-list--story-grid--hero-full .main-stories .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list--story-grid--hero-full .main-stories .article-list__article-text .article-list__article-meta time,.article-list--story-grid--hero-full .main-stories .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1}.article-list--story-grid--hero-full .top-stories .article-list__article-text{padding-left:1.5rem;padding-right:0;position:relative}.article-list--story-grid--hero-full .top-stories .article-list__article-text .article-list__article-mediaicon{display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important}.article-list--story-grid--hero-full .top-stories .article-list__article-text .article-list__article-mediaicon .article-list__article-mediaicon-svg path{fill:#fff}.article-list--story-grid--hero-full .top-stories .article-list__article--has-thumb .article-list__article-text{padding-left:0}.article-list--story-grid--hero-full .article-list__article-title .article-list__article-link{color:#fff;letter-spacing:inherit}.article-list--story-grid--hero-full .article-list__article-title .article-list__article-link:hover{color:#fff}#big-story-video{padding-bottom:1.5625rem}@media (min-width:900px){#big-story-video{padding:0 .625rem 3.125rem}}#big-story-video .article-list.video-player--hero .post-video-bin{-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;position:relative}@media (min-width:900px){#big-story-video .article-list.video-player--hero .post-video-bin{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:horizontal;-webkit-box-direction:normal;-ms-flex-flow:row wrap;flex-flow:row wrap;margin-left:auto;margin-right:auto;max-width:70rem;padding:0 0 1.5625rem}}@media (max-width:899px){#big-story-video .article-list.video-player--hero .post-video-bin{background-color:#070707;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding:1.5625rem 0}}#big-story-video .article-list.video-player--hero .article-list__heading{font-family:"Source Serif Pro",georgia,times,serif;font-size:2.125rem;font-weight:900;line-height:1.875rem;text-transform:none;color:#fff;display:-webkit-box;display:-ms-flexbox;display:flex;letter-spacing:-.00063rem;margin-bottom:.625rem;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1;width:63.072%}@media (max-width:899px){#big-story-video .article-list.video-player--hero .article-list__heading{font-size:1.25rem;letter-spacing:.00125rem;line-height:1.5rem;margin-right:1.25rem;padding:0 0 0 1.25rem;width:100%}}#big-story-video .article-list.video-player--hero .article-list__heading a{color:#fff}#big-story-video .article-list.video-player--hero .article-list__heading:after,#big-story-video .article-list.video-player--hero .article-list__heading a:after{display:none}#big-story-video .article-list.video-player--hero .video-playlist__player{display:grid;height:auto;margin-bottom:0;-webkit-box-ordinal-group:4;-ms-flex-order:3;order:3;width:63.072%}@media (max-width:899px){#big-story-video .article-list.video-player--hero .video-playlist__player{-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;width:100%}}#big-story-video .article-list.video-player--hero .video-playlist__player .video-header{margin-top:1rem}@media (max-width:899px){#big-story-video .article-list.video-player--hero .video-playlist__player .video-header .video-title{margin-left:1.25rem;margin-right:1.25rem}}#big-story-video .article-list.video-player--hero .video-playlist__player .video-header .video-title .video-title__text{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.3125rem;font-weight:700;line-height:1.5625rem;text-transform:none;color:#fff;letter-spacing:-.00125rem}@media (min-width:900px){#big-story-video .article-list.video-player--hero .video-playlist__player .video-header .video-title .video-title__text{font-size:1.875rem;line-height:1.875rem}}#big-story-video .article-list.video-player--hero .video-playlist__player .video-header .toggle{display:none}#big-story-video .article-list.video-player--hero .article-list__content{height:100%;-webkit-box-ordinal-group:5;-ms-flex-order:4;order:4;width:36.928%}@media (max-width:899px){#big-story-video .article-list.video-player--hero .article-list__content{width:100%}}#big-story-video .article-list.video-player--hero .article-list__content .video_playlist_wrapper{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:grid;padding:.75rem .875rem}@media (min-width:900px){#big-story-video .article-list.video-player--hero .article-list__content .video_playlist_wrapper{background-color:#070707}}#big-story-video .article-list.video-player--hero .article-list__content .video_playlist_wrapper article:last-child{margin-bottom:0}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article{display:-webkit-box;display:-ms-flexbox;display:flex;grid-column:1;width:100%}@media (max-width:899px){#big-story-video .article-list.video-player--hero .article-list__content .article-list__article{margin-bottom:.75rem}}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article:first-child{display:none}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text{background-color:#1c1c1c;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-webkit-box-flex:1;-ms-flex-positive:1;flex-grow:1;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;padding:.25rem .75rem}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{font-family:"Source Serif Pro",georgia,times,serif;font-size:.8125rem;font-weight:700;line-height:1;text-transform:none}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta .article-list__article-category-link,#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta time,#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1!important}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:.1875rem 0;left:0;position:absolute;top:0;z-index:1}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg{height:1.25rem;position:relative;width:1.25rem}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg svg{height:.8125rem;padding:0 .125rem;width:.875rem}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg path{fill:#fff}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon--livestream,#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon--livestream :hover{background:rgba(255,63,63,.7)}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important;text-align:left}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title,#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:.9375rem;font-weight:700;line-height:.9375rem;text-transform:none;color:#fff;letter-spacing:-.00125rem}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title .article-list__article-link:hover,#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title:hover{text-decoration:underline}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-thumb{display:-webkit-box;display:-ms-flexbox;display:flex;margin-bottom:0;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-thumb:hover{cursor:pointer}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper{border-radius:4px;height:5rem;position:relative;width:8.125rem}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper:after{opacity:.6}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper .image-wrapper{height:100%}#big-story-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper .image-wrapper img{border-radius:3px}#big-story-video .article-list.video-player--hero .article-list__content .article-list__cta-button{text-align:right}@media (max-width:899px){#big-story-video .article-list.video-player--hero .article-list__content .article-list__cta-button{margin-top:1rem;padding-left:1.25rem;text-align:left}}#big-story-video .article-list.video-player--hero .article-list__content .article-list__cta-button a{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.9375rem;font-weight:900;line-height:.9375rem;text-transform:none;color:#fff;letter-spacing:.0025rem;margin-right:1.0625rem;padding:0;text-align:right;text-transform:uppercase}#big-story-video .article-list.video-player--hero .article-list__content .article-list__cta-button a:after{background:none;padding-left:0;width:0}#big-story-video .article-list.video-player--hero .article-list__read-more{-ms-flex-item-align:center;align-self:center;border:none;margin:0;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;width:36.928%}@media (max-width:899px){#big-story-video .article-list.video-player--hero .article-list__read-more{-ms-flex-item-align:auto;align-self:auto;margin:1rem 1.25rem;-webkit-box-ordinal-group:4;-ms-flex-order:3;order:3;width:-webkit-max-content;width:-moz-max-content;width:max-content}}#big-story-video .article-list.video-player--hero .article-list__read-more:hover{background:none;border:none}#big-story-video .article-list.video-player--hero .article-list__read-more a{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.9375rem;font-weight:900;line-height:.9375rem;text-transform:none;color:#fff;letter-spacing:.0025rem;margin-right:1rem;padding:0;text-align:right;text-transform:uppercase;width:100%}@media (min-width:900px){#big-story-video .article-list.video-player--hero .article-list__read-more a{margin-bottom:1rem}}#big-story-video .article-list.video-player--hero .article-list__read-more a:after{background:none;padding-left:0;width:0}#big-story-video .hero-video-item .article-list__article-title:hover{cursor:pointer}#big-story-video .article-list__article-title .article-list__article-link{color:#fff;letter-spacing:inherit}#big-story-video .article-list__article-title .article-list__article-link:hover{color:#fff}#big-story-video .quicklinks-bar{margin:1.875rem auto 0;max-width:70rem}@media (max-width:899px){#big-story-video .quicklinks-bar{padding:0 1.25rem}}@media (max-width:899px){#big-story-video .nxst-retrans-banner{display:inline-block}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding-bottom:3.125rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:1.25rem;padding-right:1.25rem}}@media (min-width:900px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:.625rem;padding-right:.625rem}}@media (min-width:71.25rem){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0}}@media (min-width:900px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video{display:grid;grid-column-gap:1.25rem;grid-row-gap:.5rem;grid-template-columns:1fr 1fr 1fr;grid-template-rows:29.375rem auto auto}}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;padding-bottom:2.1875rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .post-video-bin{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .video-playlist__player{-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .video-playlist__player .video-header{margin-top:.375rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .video-playlist__player .video-header .video-title .video-title__text{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.125rem;font-weight:700;line-height:1;text-transform:none;color:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .video-playlist__player .video-header .toggle{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__read-more{border:none;margin:0 0 .625rem;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__read-more h2{color:#fff;font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:700;line-height:1.25rem;padding:0;text-align:left;text-transform:uppercase;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__read-more:hover{background:none;border:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__read-more a{color:#fff;padding:0;text-align:center;text-transform:uppercase;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__read-more a:after{background:none;padding-left:0;width:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content{grid-template-rows:4.3rem 4.3rem;height:100%;-webkit-box-ordinal-group:4;-ms-flex-order:3;order:3;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article{display:-webkit-box;display:-ms-flexbox;display:flex;grid-column:1;width:100%}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article{margin-bottom:.5rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article:first-child{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text{-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{font-family:"Source Serif Pro",georgia,times,serif;font-size:.8125rem;font-weight:700;line-height:1;text-transform:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta time,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:.1875rem 0;left:0;position:absolute;top:0;z-index:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg{height:1.25rem;position:relative;width:1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg svg{height:.8125rem;padding:0 .125rem;width:.875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg path{fill:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon--livestream,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon--livestream :hover{background:rgba(255,63,63,.7)}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:1rem;font-weight:700;line-height:1;text-transform:none;color:#fff;letter-spacing:-.02rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title .article-list__article-link:hover,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title:hover{text-decoration:underline}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-thumb{display:block;margin-bottom:0;margin-right:1.25rem;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-thumb:hover{cursor:pointer}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper{border-radius:.25rem;height:4.25rem;position:relative;width:6.875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper:after{opacity:.6}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper .image-wrapper img{border-radius:.1875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .hero-video-item .article-list__article-title:hover{cursor:pointer}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story{height:auto;margin-bottom:0}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story{width:100vw;height:auto;margin-bottom:1.875rem;margin-left:0}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content{height:100%;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article{border-radius:.1875rem;display:inline-block;margin:0;max-width:100%;overflow:hidden;position:relative;grid-column:1/2;grid-row:1/4;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper{background:#d9d9d9}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper:after{background:-o-radial-gradient(370% 300% at 1% 169%,#212121 37.56%,rgba(33,33,33,0) 55.78%);background:radial-gradient(370% 300% at 1% 169%,#212121 37.56%,rgba(33,33,33,0) 55.78%);content:"";height:100%;left:0;opacity:.8;position:absolute;right:0;top:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb{margin-bottom:0;width:100%;z-index:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb:hover{opacity:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper{width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:3px 0;top:0;z-index:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon .article-list__article-mediaicon-text{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon:hover{background:rgba(28,28,28,.698)}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream:hover{background:rgba(255,63,63,.7)}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .image-wrapper img{-o-object-fit:cover;object-fit:cover}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-link{z-index:10}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text{bottom:0;position:absolute;width:100%;z-index:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title{margin-bottom:.3125rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.4375rem;font-weight:700;line-height:1.5625rem;text-transform:none;color:#fff;display:inline-block;padding:0 10px}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link:hover{text-decoration:underline}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{-webkit-box-align:end;-ms-flex-align:end;align-items:flex-end;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding:0 10px 10px;visibility:hidden}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-category-link{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:1;text-transform:none;background:#fff;border-radius:.1875rem;color:#212121;letter-spacing:.02rem;padding:.3125rem;text-decoration:none;visibility:initial}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-category-link:hover{font-size:.6875rem;text-decoration:underline}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text time{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:2;text-transform:none;color:#fff;letter-spacing:.02rem;visibility:initial}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-thumb,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .image-wrapper{height:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper:after{background:unset;height:unset}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text{padding-top:40%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-excerpt,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-label-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title{position:relative;z-index:2}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__gradient-link{background:-o-radial-gradient(320% 324% at 38% 219%,#212121 48%,rgba(33,33,33,0) 62%);background:radial-gradient(320% 324% at 38% 219%,#212121 48%,rgba(33,33,33,0) 62%);bottom:0;height:100%;opacity:.9;position:absolute;width:100%}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article{height:27.5rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:start}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta .article-list__article-category-link{margin-right:.375rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon{padding:.5rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon--default{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .text-padded{padding-left:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.75rem;font-weight:900;line-height:1.875rem;text-transform:none;letter-spacing:-.01rem;padding:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link{font-family:inherit;font-size:inherit;font-weight:inherit;letter-spacing:inherit;line-height:inherit;padding:0 1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{padding:0 1.25rem 1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon{bottom:25.5625rem;top:unset}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon{bottom:25.25rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__article-mediaicon--default{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__article-text .article-list__article-meta time,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .main-story .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .article-list__heading{margin-bottom:.5625rem!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .article-list__heading-link{color:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .article-list__heading-link:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%23fff'/%3E%3C/svg%3E");background-size:.5625rem;content:"";float:left;height:1.25rem;position:absolute;width:1.25rem;height:1.2rem;width:1.6rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories{width:100%}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories{margin-bottom:1.875rem;margin-top:.625rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories .article-list__article-thumb .article-list__article-image-wrapper{height:4.25rem;width:6.875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories .article-list__article-thumb .article-list__article-image-wrapper .image-wrapper.square{position:static}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories .article-list__article-thumb .article-list__article-image-wrapper .image-wrapper.no-image{background-color:#d9d9d9;border-radius:.1875rem;height:4.25rem;width:6.875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories .article-list__article-text{padding-left:1.5rem;padding-right:0;position:relative}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories .article-list__article-text .article-list__article-mediaicon{display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .top-stories .article-list__article-text .article-list__article-mediaicon .article-list__article-mediaicon-svg path{fill:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list__article-title .article-list__article-link{color:#fff;letter-spacing:inherit}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list__article-title .article-list__article-link:hover{color:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .video-component .article-list__article-meta{display:none!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .top-stories .post-video-bin .article-list__content{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .top-stories .article-list__content{padding-top:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .top-stories .article-list__content .article-list__article{margin-bottom:1rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .top-stories .article-list__content .article-list__article .article-list__article-text{padding-left:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .top-stories .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link{font-size:1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .top-stories .article-list__content .article-list__article .article-list__article-thumb{margin-bottom:0;margin-right:1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .ns-video-bin .hero-video-item .article-list__article-title{font-size:1.25rem!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-video .article-list .video-playlist__player{margin-bottom:1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding-bottom:3.125rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:1.25rem;padding-right:1.25rem}}@media (min-width:900px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:.625rem;padding-right:.625rem}}@media (min-width:71.25rem){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0}}@media (min-width:900px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video{-webkit-column-gap:1.25rem;-moz-column-gap:1.25rem;column-gap:1.25rem;display:grid;grid-row-gap:.625rem;grid-template-columns:2fr 1fr}}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video{background:#000;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .no-title{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video>.article-list__title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.75rem;font-weight:900;line-height:1.875rem;text-transform:none;-webkit-box-align:end;-ms-flex-align:end;align-items:end;color:#fff;-webkit-column-gap:1.25rem;-moz-column-gap:1.25rem;column-gap:1.25rem;display:grid;grid-column:span 3;grid-template-columns:auto 1fr;margin-top:1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video>.article-list__title .branded-logo,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video>.article-list__title img{border:none;height:3.125rem;margin:0;max-width:18.75rem;padding:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video>.article-list__title .article-list__title-text{border-bottom:.3125rem solid var(--primary_color);padding-bottom:.625rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video>.article-list__title{grid-template-columns:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video>.article-list__title img{margin-bottom:1.25rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .post-video-bin{background-color:#000;display:grid;grid-template-columns:repeat(2,1fr);grid-template-rows:1fr auto}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .post-video-bin{background-color:rgba(0,0,0,0)!important}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .video-playlist__player{grid-column:1/span 2;grid-row:1}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .video-playlist__player{grid-column:1/span 2;grid-row:1;margin-left:-1.25rem;margin-right:-1.25rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .video-playlist__player .video-header{margin:.375rem 0;padding:0 .9375rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .video-playlist__player .video-header .video-title{padding:1.25rem 0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .video-playlist__player .video-header .video-title .video-title__text{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.25rem;font-weight:700;line-height:1;text-transform:none;color:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .video-playlist__player .video-header .toggle{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__read-more{border:none;grid-column:1;grid-row:3;margin-top:0;padding:0 .9375rem .9375rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__read-more{grid-column:1/span 2;grid-row:2;margin-top:0;padding:0 0 .9375rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__read-more:hover{background:none;border:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__read-more a{color:#fff;margin-right:1rem;padding:0;text-align:right;text-transform:uppercase;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__read-more a:after{background:none;padding-left:0;width:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__cta-button{grid-column:2;grid-row:3;width:100%}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__cta-button{grid-column:1/span 2;grid-row:4;margin:.9375rem 0 0;padding:0;text-align:left}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__cta-button:hover{background:none;border:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__cta-button a{color:#fff;margin-right:1rem;padding:0;text-align:right;text-transform:uppercase;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__cta-button a:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%23fff'/%3E%3C/svg%3E");background-size:.5625rem;content:"";float:left;height:1.25rem;position:absolute;width:1.25rem;height:1.2rem;width:1.6rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__cta-button a{text-align:left}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content{grid-column:1/span 2;grid-column-gap:0!important;grid-row:2;padding:.9375rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content{grid-column:1/span 2;grid-row:3;padding:0}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content>:last-child{grid-column:2!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article{display:-webkit-box;display:-ms-flexbox;display:flex;grid-column:1;width:21.875rem}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article{margin-bottom:.3rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article:first-child{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text{-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;-webkit-box-ordinal-group:3;-ms-flex-order:2;order:2}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{font-family:"Source Serif Pro",georgia,times,serif;font-size:.8125rem;font-weight:700;line-height:1;text-transform:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta time,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:.1875rem 0;left:0;position:absolute;top:0;z-index:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg{height:1.25rem;position:relative;width:1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg svg{height:.8125rem;padding:0 .125rem;width:.875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon-svg path{fill:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon--livestream,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-mediaicon--livestream :hover{background:rgba(255,63,63,.7)}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.25rem;font-weight:700;line-height:1;text-transform:none;color:#fff;letter-spacing:-.02rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title .article-list__article-link:hover,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-title:hover{text-decoration:underline}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-thumb{display:block;margin-bottom:0;margin-right:1.25rem;-webkit-box-ordinal-group:2;-ms-flex-order:1;order:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-thumb:hover{cursor:pointer}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper{border-radius:.25rem;height:5rem;position:relative;width:8.125rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper:after{opacity:.6}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper .image-wrapper{height:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list.video-player--hero .article-list__content .article-list__article .article-list__article-image-wrapper .image-wrapper img{border-radius:.1875rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .hero-video-item .article-list__article-title:hover{cursor:pointer}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story{height:auto;margin-bottom:0}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story{width:100vw;height:auto;margin-left:0}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content{height:100%;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article{border-radius:.1875rem;display:inline-block;margin:0;max-width:100%;overflow:hidden;position:relative;grid-column:1/2;grid-row:1/4;width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper{background:#d9d9d9}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper:after{background:-o-radial-gradient(370% 300% at 1% 169%,#212121 37.56%,rgba(33,33,33,0) 55.78%);background:radial-gradient(370% 300% at 1% 169%,#212121 37.56%,rgba(33,33,33,0) 55.78%);content:"";height:100%;left:0;opacity:.8;position:absolute;right:0;top:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb{margin-bottom:0;width:100%;z-index:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb:hover{opacity:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper{width:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon{background:rgba(28,28,28,.698);border-radius:3px 0;top:0;z-index:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon .article-list__article-mediaicon-text{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon:hover{background:rgba(28,28,28,.698)}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .article-list__article-mediaicon--livestream:hover{background:rgba(255,63,63,.7)}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article figure.article-list__article-thumb .article-list__article-image-wrapper .image-wrapper img{-o-object-fit:cover;object-fit:cover}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-link{z-index:10}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text{bottom:0;position:absolute;width:100%;z-index:1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title{margin-bottom:.3125rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.4375rem;font-weight:700;line-height:1.5625rem;text-transform:none;color:#fff;display:inline-block;padding:0 10px}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link:hover{text-decoration:underline}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{-webkit-box-align:end;-ms-flex-align:end;align-items:flex-end;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding:0 10px 10px;visibility:hidden}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-category-link{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:1;text-transform:none;background:#fff;border-radius:.1875rem;color:#212121;letter-spacing:.02rem;padding:.3125rem;text-decoration:none;visibility:initial}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-category-link:hover{font-size:.6875rem;text-decoration:underline}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text time{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:.6875rem;font-weight:400;line-height:2;text-transform:none;color:#fff;letter-spacing:.02rem;visibility:initial}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-thumb,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .image-wrapper{height:100%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-image-wrapper:after{background:unset;height:unset}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text{padding-top:40%}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-excerpt,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-label-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title{position:relative;z-index:2}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__gradient-link{background:-o-radial-gradient(320% 324% at 38% 219%,#212121 48%,rgba(33,33,33,0) 62%);background:radial-gradient(320% 324% at 38% 219%,#212121 48%,rgba(33,33,33,0) 62%);bottom:0;height:100%;opacity:.9;position:absolute;width:100%}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article{height:27.5rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:start}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta .article-list__article-category-link{margin-right:6px}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon{padding:.5rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon--default{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .text-padded{padding-left:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.75rem;font-weight:900;line-height:1.875rem;text-transform:none;letter-spacing:-.01rem;padding:0}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-title .article-list__article-link{font-family:inherit;font-size:inherit;font-weight:inherit;letter-spacing:inherit;line-height:inherit;padding:0 1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-text .article-list__article-meta{padding:0 1.25rem 1.25rem}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon{bottom:25.5625rem;top:unset}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__content .article-list__article .article-list__article-mediaicon{bottom:25.25rem}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__article-mediaicon--default{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__article-text .article-list__article-meta time,.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .main-story .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories{width:100%}@media (max-width:899px){.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories{margin-top:0}}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories .article-list__article-label-link{display:none}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories .article-list__cta-button.article-list__read-more{display:none!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories .article-list__article-text{padding-left:1.5rem;padding-right:0;position:relative}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories .article-list__article-text .article-list__article-mediaicon{display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .top-stories .article-list__article-text .article-list__article-mediaicon .article-list__article-mediaicon-svg path{fill:#fff}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list__article-title .article-list__article-link{color:#fff;letter-spacing:inherit}.article-list.article-list--story-grid.article-list--story-grid--hero-daily-news-main-video .article-list__article-title .article-list__article-link:hover{color:#fff}.article-list--story-grid--hero-daily-news-horizontal{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding-bottom:3.125rem}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:1.25rem;padding-right:1.25rem}}@media (min-width:900px){.article-list--story-grid--hero-daily-news-horizontal{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:.625rem;padding-right:.625rem}}@media (min-width:71.25rem){.article-list--story-grid--hero-daily-news-horizontal{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0}}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal{-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column}}.article-list--story-grid--hero-daily-news-horizontal .main-stories{height:auto;margin-bottom:0;width:66.072%}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal .main-stories{margin-left:-1.25rem;width:100vw;height:auto}}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content{height:100%;width:100%}@media (min-width:900px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content{display:grid;grid-column-gap:1.25rem;grid-row-gap:.625rem;grid-template-columns:3fr 2fr;grid-template-rows:auto}}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between}}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article{width:100%}@media (min-width:900px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child{grid-column:1/2;grid-row:1/6}}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child{height:auto;margin-bottom:1.25rem}}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.75rem;font-weight:900;line-height:1.875rem;text-transform:none;letter-spacing:-.01rem;padding:.625rem 0 0}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title{padding:.625rem .625rem 0}}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-title .article-list__article-link{font-family:inherit;font-size:inherit;font-weight:inherit;letter-spacing:inherit;line-height:inherit;padding:0}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta{-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:start;padding:0;visibility:hidden}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta{padding:0 .625rem}}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-text .article-list__article-meta .article-list__article-category-link{margin-right:-.25rem}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .image-wrapper.no-image{height:15.1875rem;width:100%}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon{padding:.5rem}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon--default{display:none}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .article-list__article-mediaicon-svg{height:.75rem;width:.75rem}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:first-child .text-padded{padding-left:0}@media (max-width:899px){.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__content .article-list__article:nth-child(n+2){margin:1.25rem .625rem 0}}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__article-mediaicon--default{display:none}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__article-text .article-list__article-meta .article-list__article-category-link,.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__article-text .article-list__article-meta time,.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__article-text .article-list__article-meta time:before{color:#c1c1c1;visibility:initial}.article-list--story-grid--hero-daily-news-horizontal .main-stories .article-list__article-text .article-list__article-meta time:before{content:"\2022";margin-right:.21875rem;position:relative}.article-list--story-grid--hero-daily-news-horizontal .top-stories .article-list__article-text{padding-left:1.5rem;padding-right:0;position:relative}.article-list--story-grid--hero-daily-news-horizontal .top-stories .article-list__article-text .article-list__article-mediaicon{display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important}.article-list--story-grid--hero-daily-news-horizontal .top-stories .article-list__article-text .article-list__article-mediaicon .article-list__article-mediaicon-svg path{fill:#fff}.article-list--story-grid--hero-daily-news-horizontal .top-stories .article-list__article--has-thumb .article-list__article-text{padding-left:0}.article-list--story-grid--hero-daily-news-horizontal .article-list__article-title .article-list__article-link{color:#fff;letter-spacing:inherit}.article-list--story-grid--hero-daily-news-horizontal .article-list__article-title .article-list__article-link:hover{color:#fff}.article-list.article-list--story-grid .top-stories{width:32.143%}@media (min-width:900px){.article-list.article-list--story-grid .top-stories{margin-bottom:0}}@media (max-width:899px){.article-list.article-list--story-grid .top-stories{margin-top:1.875rem;width:100%}}.article-list.article-list--story-grid .top-stories .article-list__heading{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1;text-transform:uppercase;color:#fff;margin-bottom:1.25rem}.article-list.article-list--story-grid .top-stories .article-list__heading .article-list__heading-link{color:#fff}.article-list.article-list--story-grid .top-stories .article-list__heading .article-list__heading-link:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%23fff'/%3E%3C/svg%3E");background-size:.5625rem;content:"";float:left;height:1.25rem;position:absolute;width:1.25rem;height:1.2rem;width:1.6rem}.article-list.article-list--story-grid .top-stories .article-list__content{display:block;padding-top:.625rem}.article-list.article-list--story-grid .top-stories .article-list__content>*{margin-bottom:.625rem}.article-list.article-list--story-grid .top-stories .article-list__article{border-bottom:none;padding:0}.article-list.article-list--story-grid .top-stories .article-list__article:nth-child(n+2){padding:0}.article-list.article-list--story-grid .top-stories .article-list__article .article-list__article-title,.article-list.article-list--story-grid .top-stories .article-list__article:nth-child(n+2) .article-list__article-title{font-family:"Source Serif Pro",georgia,times,serif;font-size:1.25rem;font-weight:700;line-height:1;text-transform:none;letter-spacing:-.02rem}.article-list.article-list--story-grid .top-stories .article-list__article-meta .article-list__article-category-link,.article-list.article-list--story-grid .top-stories .article-list__article-meta time,.article-list.article-list--story-grid .top-stories .article-list__article-meta time:before{color:#c1c1c1}.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon--livestream .article-list__article-mediaicon-svg svg{height:.75rem!important;width:.75rem!important}.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon{background:rgba(0,0,0,0);left:0;position:absolute;top:0}.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon--livestream,.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon--livestream:hover{background:rgba(0,0,0,0)}.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon--livestream svg circle{fill:#cc1f3b}.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon--default .article-list__article-mediaicon-svg svg,.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon .article-list__article-mediaicon-svg svg{height:.6875rem;width:.6875rem}.article-list.article-list--story-grid .top-stories .article-list__article-mediaicon--default .article-list__article-mediaicon-svg svg circle{fill:#fff}.article-list.article-list--story-grid .top-stories .article-list__read-more{display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center;margin-bottom:0}.article-list.article-list--story-grid .top-stories .article-list__read-more a{border-color:#fff;color:#fff;-webkit-transition:all .25s ease-out;-o-transition:all .25s ease-out;transition:all .25s ease-out}.article-list.article-list--story-grid .top-stories .article-list__read-more a:hover{background-color:#fff;color:#1c1c1c}.branded-logo{border-left:2px solid #000;height:.8rem;margin-left:.3125rem;padding-left:.625rem}@media (min-width:64rem){.branded-logo{height:1rem}}.branded-logo__image{height:.8rem}@media (min-width:64rem){.branded-logo__image{height:1rem}}.psgtrib .rich-text .row>.wp-block-latest-posts.wp-block-latest-posts__list,.rich-text-cascade .wp-block-latest-posts.wp-block-latest-posts__list,.rich-text>.wp-block-latest-posts.wp-block-latest-posts__list,a,abbr,acronym,address,applet,article,aside,audio,b,big,blockquote,body,canvas,caption,center,cite,code,dd,del,details,dfn,div,dl,dt,em,embed,fieldset,figcaption,figure,footer,form,h1,h2,h3,h4,h5,h6,header,hgroup,html,i,iframe,img,ins,kbd,label,legend,li,mark,menu,nav,object,ol,output,p,pre,q,ruby,s,samp,section,small,span,strike,strong,sub,summary,sup,table,tbody,td,tfoot,th,thead,time,tr,tt,u,ul,var,video{border:0;-webkit-box-sizing:border-box;box-sizing:border-box;font:inherit;font-size:100%;margin:0;padding:0;vertical-align:baseline}article,aside,details,figcaption,figure,footer,header,hgroup,menu,nav,section{display:block}html{background-color:#fff}body{line-height:1}.psgtrib .rich-text .row>.wp-block-latest-posts.wp-block-latest-posts__list,.rich-text-cascade .wp-block-latest-posts.wp-block-latest-posts__list,.rich-text>.wp-block-latest-posts.wp-block-latest-posts__list,ol,ul{list-style:none}blockquote,q{quotes:none}blockquote:after,blockquote:before,q:after,q:before{content:"";content:none}table{border-collapse:collapse;border-spacing:0}body,html{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1rem;font-weight:400;line-height:1.3;text-transform:none;-moz-osx-font-smoothing:grayscale;-webkit-font-smoothing:antialiased;min-width:20rem}img{height:auto;max-width:100%}a{color:#2d5ea8;text-decoration:none}a:hover{color:#000}.s2nFloatBox,.s2nFriendlyFrame{clear:both}.screen-reader-text{border:0;clip:rect(0,0,0,0);height:1px;margin:-1px;overflow:hidden;padding:0;position:absolute;width:1px}.wp-block-embed-twitter{display:-webkit-box!important;display:-ms-flexbox!important;display:flex!important}.wp-block-embed-twitter .wp-block-embed__wrapper{width:94%}@media (max-width:640px){.wp-block-embed-twitter{max-width:none}.wp-block-embed-twitter .wp-block-embed__wrapper{width:100%}}.wp-block-embed-twitter.alignright{-webkit-box-pack:end;-ms-flex-pack:end;justify-content:flex-end}.wp-block-embed-twitter.alignleft{-webkit-box-pack:start;-ms-flex-pack:start;justify-content:flex-start}.wp-block-embed-twitter.aligncenter{-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center}.wp-block-embed-twitter.aligncenter .wp-block-embed__wrapper{min-width:65%;width:auto}@media (max-width:640px){.wp-block-embed-twitter.aligncenter .wp-block-embed__wrapper{width:100%}}.site-content{padding-top:0}.site-content>*{margin-bottom:1.875rem}@media (max-width:899px){.site-content>*{margin-bottom:1.25rem}}.site-content>:last-child{margin-bottom:0}.category .site-content,.home .site-content,.post-template-default .site-content{padding-top:0}@media (max-width:899px){.site-content{overflow-x:hidden}}.site-content--app{padding-top:0}.site-content__header{padding-top:1.25rem}.site-content__header>*{margin-bottom:3.125rem}@media (max-width:899px){.site-content__header>*{margin-bottom:1.25rem}}.site-content__header>:last-child{margin-bottom:0}.site-content__header .ad-unit{margin-bottom:1.25rem}@media (max-width:899px){.site-content__header .ad-unit{margin-bottom:.625rem}}@media (max-width:899px){.site-content__header{padding-top:.625rem}}.category .site-content__header,.home .site-content__header,.tag .site-content__header{background:#1c1c1c}.feed_post-template-bestreviews .site-content__header,.feed_post-template-default .site-content__header,.post-template-default .site-content__header{background:#1c1c1c;padding-top:1.25rem}@media (max-width:899px){.feed_post-template-bestreviews .site-content__header,.feed_post-template-default .site-content__header,.post-template-default .site-content__header{padding-top:.625rem}}.quicklinks-bar{color:#fff;grid-column:1/4;margin-top:1.875rem;width:100%;z-index:1}@media (max-width:899px){.quicklinks-bar{grid-column:revert;margin-top:1.25rem}}.quicklinks-bar__heading{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1;text-transform:uppercase;margin-bottom:1.0625rem}@media (max-width:899px){.quicklinks-bar__heading{margin-bottom:1.1875rem}}.quicklinks-bar__content{display:-webkit-box;display:-ms-flexbox;display:flex;gap:1.4375rem;padding-bottom:.625rem}@media (max-width:899px){.quicklinks-bar__content{-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column}}.quicklinks-bar__item{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;width:25%}@media (max-width:899px){.quicklinks-bar__item{width:100%}}.quicklinks-bar .caret:after{background:no-repeat 50% url("data:image/svg+xml;charset=utf-8,%3Csvg width='6' height='8' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Cpath fill-rule='evenodd' clip-rule='evenodd' d='M2.444 4.141a.2.2 0 000-.282l-1.51-1.51a.2.2 0 010-.283L2.066.934a.2.2 0 01.283 0L5.273 3.86a.2.2 0 010 .282L2.349 7.066a.2.2 0 01-.283 0L.934 5.934a.2.2 0 010-.282l1.51-1.51z' fill='%23fff'/%3E%3C/svg%3E");background-size:.5625rem;content:"";float:left;height:1.25rem;position:relative;width:2.5rem}.quicklinks-bar a{font-family:"Source Serif Pro",georgia,times,serif;font-size:.9375rem;font-weight:700;line-height:1;text-transform:none;color:#fff;letter-spacing:-.02em;margin-bottom:0}.quicklinks-bar a:hover{color:#fff}.site-content__layout{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0;-webkit-box-pack:center;-ms-flex-pack:center;justify-content:center}@media (max-width:899px){.site-content__layout{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:1.25rem;padding-right:1.25rem}}@media (min-width:900px){.site-content__layout{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:.625rem;padding-right:.625rem}}@media (min-width:71.25rem){.site-content__layout{display:flex;flex-flow:row wrap;max-width:70rem;margin-left:auto;margin-right:auto;padding-left:0;padding-right:0}}.site-content__layout>*{margin-bottom:3.125rem}@media (max-width:899px){.site-content__layout>*{margin-bottom:1.25rem}}.site-content__layout>:last-child{margin-bottom:0}.site-content__layout .content-area{width:100%}.site-content__layout--has-sidebar .content-area>*,.site-content__layout--has-sidebar .site-main>*,.site-content__layout--has-sidebar .widget-area>*{margin-bottom:3.125rem}@media (max-width:899px){.site-content__layout--has-sidebar .content-area>*,.site-content__layout--has-sidebar .site-main>*,.site-content__layout--has-sidebar .widget-area>*{margin-bottom:1.25rem}}.site-content__layout--has-sidebar #native-rr,.site-content__layout--has-sidebar .content-area>:last-child,.site-content__layout--has-sidebar .site-main>:last-child,.site-content__layout--has-sidebar .widget-area>:last-child{margin-bottom:0}@media (min-width:900px){.site-content__layout--has-sidebar .content-area{margin-right:2.5rem;width:calc(100% - 340px)}}@media (min-width:71.25rem){.site-content__layout--has-sidebar .content-area{margin-right:2.5rem;width:46.25rem}}.site-content__layout--has-sidebar .widget-area{width:100%}@media (min-width:900px){.site-content__layout--has-sidebar .widget-area{width:18.75rem}}@media (min-width:71.25rem){.site-content__layout--has-sidebar .widget-area{width:21.25rem}}.site-content__layout--full-width .content-area{width:100%}.site-content__layout--app{padding-left:0;padding-right:0}.site-content__layout--app .article-list{padding:1rem}@media (min-width:900px){.site-content__layout--app *{margin-bottom:0;margin-top:0}.site-content__layout--app .article-list{padding:0}}.site-content__layout--app .app-landing-inner-container{background:-webkit-gradient(linear,left top,right top,from(#bdcadb),color-stop(20%,#d8e4f2),color-stop(47%,#deeaf8),color-stop(72%,#d8e4f3),to(#c1cedf));background:-o-linear-gradient(left,#bdcadb 0,#d8e4f2 20%,#deeaf8 47%,#d8e4f3 72%,#c1cedf 100%);background:linear-gradient(90deg,#bdcadb,#d8e4f2 20%,#deeaf8 47%,#d8e4f3 72%,#c1cedf)}.site-content__header--has-story-package-hero{max-width:100%;position:relative}.site-content__header--has-big-story-hero{max-width:100%;overflow:hidden;position:relative}.widget-area{position:relative;z-index:1}.widget-area>*{margin-bottom:1rem}.widget-area>:last-child{margin-bottom:0}.widget-area .article-list__heading,.widget-area .widget-title{font-family:Source Sans Pro,arial,helvetica,verdana,sans-serif;font-size:1.125rem;font-weight:900;line-height:1.125rem;text-transform:uppercase;color:#1c1c1c;display:block;letter-spacing:.04em;margin-bottom:1.25rem;text-align:left}@media (max-width:899px){.widget-area .article-list__heading,.widget-area .widget-title{padding-top:.625rem}}.image-wrapper.landscape:not(.square-on-mobile){height:0;overflow:hidden;padding-bottom:56.25%;position:relative}.image-wrapper.landscape:not(.square-on-mobile) img{height:100%;left:0;position:absolute;top:0;width:100%;-o-object-fit:cover;object-fit:cover}.image-wrapper.portrait:not(.square-on-mobile){height:0;overflow:hidden;padding-bottom:56.25%;position:relative;background-color:#d9d9d9}.image-wrapper.portrait:not(.square-on-mobile) img{height:100%;left:0;left:50%;margin-right:-50%;position:absolute;top:0;-webkit-transform:translate(-50%);-ms-transform:translate(-50%);transform:translate(-50%);width:auto}.image-wrapper.portrait-headshot{height:0;overflow:hidden;padding-bottom:133.33333%;position:relative}.image-wrapper.portrait-headshot img{height:100%;left:0;position:absolute;top:0;width:100%;-o-object-fit:cover;object-fit:cover}.image-wrapper.square{height:0;overflow:hidden;padding-bottom:100%;position:relative}.image-wrapper.square img{height:100%;left:0;position:absolute;top:0;width:100%;-o-object-fit:cover;object-fit:cover}@media (max-width:31.9375rem){.image-wrapper.square-on-mobile.portrait{height:0;overflow:hidden;padding-bottom:100%;position:relative}}@media (max-width:31.9375rem){.image-wrapper.square-on-mobile.portrait img{height:100%;left:0;position:absolute;top:0;width:100%;-o-object-fit:cover;object-fit:cover}}@media (min-width:32rem){.image-wrapper.square-on-mobile.portrait{height:0;overflow:hidden;padding-bottom:56.25%;position:relative;background-color:#d9d9d9}.image-wrapper.square-on-mobile.portrait img{height:100%;left:0;left:50%;margin-right:-50%;position:absolute;top:0;-webkit-transform:translate(-50%);-ms-transform:translate(-50%);transform:translate(-50%);width:auto}}.image-wrapper.square-on-mobile.landscape{height:0;overflow:hidden;padding-bottom:100%;position:relative}@media (min-width:32rem){.image-wrapper.square-on-mobile.landscape{height:0;overflow:hidden;padding-bottom:56.25%;position:relative}}.image-wrapper.square-on-mobile.landscape img{height:100%;left:0;position:absolute;top:0;width:100%;-o-object-fit:cover;object-fit:cover}@media (max-width:899px){.article-featured-media .image-wrapper.landscape:not(.square-on-mobile){padding-bottom:0}}</style><meta name='description' content='San Francisco Bay Area&#039;s local news &amp; weather station. Local reporting to make San Francisco, San Jose, Oakland and the rest of the Bay Area a better place to live.' /><!-- WP SEO -->
<meta name='google-site-verification' content='QfHNV8ttyhitXaUk37DXLuakghIOnKGK-3rwtNpY_ao' /><!-- WP SEO -->
<meta name='google-site-verification' content='Q6VjcHSumT314ZkfblLllfGrWtfU8Q7KX5utbPvxv-4' /><!-- WP SEO -->

<style>
	:root {
		--primary_color: #7d0200;
		--primary_color_pale: rgba( 125, 2, 0, 0.2 );
		--primary_color_text: #ffffff;
		--alert_banner_label_sep: '/';
		--image_width_thumbnail: 160px;
		--image_width_medium: 300px;
		--image_width_large: 1280px;
	}
</style>
<link rel='stylesheet' id='nexstar/login-registration/styles/css-css' href='https://www.kron4.com/wp-content/plugins/login-registration/build/login-registration-styles.d40d4b90b421e82db16f.css?ver=d40d4b90b421e82db16f' media='all' />
<link rel='stylesheet' id='wp-block-library-css' href='https://www.kron4.com/wp-includes/css/dist/block-library/style.min.css?ver=6.8.3' media='all' />
<style id='classic-theme-styles-inline-css'>
/*! This file is auto-generated */
.wp-block-button__link{color:#fff;background-color:#32373c;border-radius:9999px;box-shadow:none;text-decoration:none;padding:calc(.667em + 2px) calc(1.333em + 2px);font-size:1.125em}.wp-block-file__button{background:#32373c;color:#fff;text-decoration:none}
</style>
<link rel='stylesheet' id='jetpack-videopress-video-block-view-css' href='https://www.kron4.com/wp-content/client-mu-plugins/jetpack/jetpack_vendor/automattic/jetpack-videopress/build/block-editor/blocks/video/view.css?minify=false&#038;ver=34ae973733627b74a14e' media='all' />
<link rel='stylesheet' id='mediaelement-css' href='https://www.kron4.com/wp-includes/js/mediaelement/mediaelementplayer-legacy.min.css?ver=4.2.17' media='all' />
<link rel='stylesheet' id='wp-mediaelement-css' href='https://www.kron4.com/wp-includes/js/mediaelement/wp-mediaelement.min.css?ver=6.8.3' media='all' />
<style id='elasticpress-facet-style-inline-css'>
.widget_ep-facet input[type=search],.wp-block-elasticpress-facet input[type=search]{margin-bottom:1rem}.widget_ep-facet .searchable .inner,.wp-block-elasticpress-facet .searchable .inner{max-height:20em;overflow:scroll}.widget_ep-facet .term.hide,.wp-block-elasticpress-facet .term.hide{display:none}.widget_ep-facet .empty-term,.wp-block-elasticpress-facet .empty-term{opacity:.5;position:relative}.widget_ep-facet .empty-term:after,.wp-block-elasticpress-facet .empty-term:after{bottom:0;content:" ";display:block;left:0;position:absolute;right:0;top:0;width:100%;z-index:2}.widget_ep-facet .level-1,.wp-block-elasticpress-facet .level-1{padding-left:20px}.widget_ep-facet .level-2,.wp-block-elasticpress-facet .level-2{padding-left:40px}.widget_ep-facet .level-3,.wp-block-elasticpress-facet .level-3{padding-left:60px}.widget_ep-facet .level-4,.wp-block-elasticpress-facet .level-4{padding-left:5pc}.widget_ep-facet .level-5,.wp-block-elasticpress-facet .level-5{padding-left:75pt}.widget_ep-facet input[disabled],.wp-block-elasticpress-facet input[disabled]{cursor:pointer;opacity:1}.widget_ep-facet .term a,.wp-block-elasticpress-facet .term a{-webkit-box-align:center;-ms-flex-align:center;align-items:center;display:-webkit-box;display:-ms-flexbox;display:flex;position:relative}.widget_ep-facet .term a:hover .ep-checkbox,.wp-block-elasticpress-facet .term a:hover .ep-checkbox{background-color:#ccc}.ep-checkbox{-webkit-box-align:center;-ms-flex-align:center;-ms-flex-negative:0;-webkit-box-pack:center;-ms-flex-pack:center;align-items:center;background-color:#eee;display:-webkit-box;display:-ms-flexbox;display:flex;flex-shrink:0;height:1em;justify-content:center;margin-right:.25em;width:1em}.ep-checkbox:after{border:solid #fff;border-width:0 .125em .125em 0;content:"";display:none;height:.5em;-webkit-transform:rotate(45deg);transform:rotate(45deg);width:.25em}.ep-checkbox.checked{background-color:#5e5e5e}.ep-checkbox.checked:after{display:block}

</style>
<link rel='stylesheet' id='elasticpress-related-posts-block-css' href='https://www.kron4.com/wp-content/mu-plugins/search/elasticpress/dist/css/related-posts-block-styles.min.css?ver=4.2.2' media='all' />
<style id='global-styles-inline-css'>
:root{--wp--preset--aspect-ratio--square: 1;--wp--preset--aspect-ratio--4-3: 4/3;--wp--preset--aspect-ratio--3-4: 3/4;--wp--preset--aspect-ratio--3-2: 3/2;--wp--preset--aspect-ratio--2-3: 2/3;--wp--preset--aspect-ratio--16-9: 16/9;--wp--preset--aspect-ratio--9-16: 9/16;--wp--preset--color--black: #000000;--wp--preset--color--cyan-bluish-gray: #abb8c3;--wp--preset--color--white: #ffffff;--wp--preset--color--pale-pink: #f78da7;--wp--preset--color--vivid-red: #cf2e2e;--wp--preset--color--luminous-vivid-orange: #ff6900;--wp--preset--color--luminous-vivid-amber: #fcb900;--wp--preset--color--light-green-cyan: #7bdcb5;--wp--preset--color--vivid-green-cyan: #00d084;--wp--preset--color--pale-cyan-blue: #8ed1fc;--wp--preset--color--vivid-cyan-blue: #0693e3;--wp--preset--color--vivid-purple: #9b51e0;--wp--preset--gradient--vivid-cyan-blue-to-vivid-purple: linear-gradient(135deg,rgba(6,147,227,1) 0%,rgb(155,81,224) 100%);--wp--preset--gradient--light-green-cyan-to-vivid-green-cyan: linear-gradient(135deg,rgb(122,220,180) 0%,rgb(0,208,130) 100%);--wp--preset--gradient--luminous-vivid-amber-to-luminous-vivid-orange: linear-gradient(135deg,rgba(252,185,0,1) 0%,rgba(255,105,0,1) 100%);--wp--preset--gradient--luminous-vivid-orange-to-vivid-red: linear-gradient(135deg,rgba(255,105,0,1) 0%,rgb(207,46,46) 100%);--wp--preset--gradient--very-light-gray-to-cyan-bluish-gray: linear-gradient(135deg,rgb(238,238,238) 0%,rgb(169,184,195) 100%);--wp--preset--gradient--cool-to-warm-spectrum: linear-gradient(135deg,rgb(74,234,220) 0%,rgb(151,120,209) 20%,rgb(207,42,186) 40%,rgb(238,44,130) 60%,rgb(251,105,98) 80%,rgb(254,248,76) 100%);--wp--preset--gradient--blush-light-purple: linear-gradient(135deg,rgb(255,206,236) 0%,rgb(152,150,240) 100%);--wp--preset--gradient--blush-bordeaux: linear-gradient(135deg,rgb(254,205,165) 0%,rgb(254,45,45) 50%,rgb(107,0,62) 100%);--wp--preset--gradient--luminous-dusk: linear-gradient(135deg,rgb(255,203,112) 0%,rgb(199,81,192) 50%,rgb(65,88,208) 100%);--wp--preset--gradient--pale-ocean: linear-gradient(135deg,rgb(255,245,203) 0%,rgb(182,227,212) 50%,rgb(51,167,181) 100%);--wp--preset--gradient--electric-grass: linear-gradient(135deg,rgb(202,248,128) 0%,rgb(113,206,126) 100%);--wp--preset--gradient--midnight: linear-gradient(135deg,rgb(2,3,129) 0%,rgb(40,116,252) 100%);--wp--preset--font-size--small: 13px;--wp--preset--font-size--medium: 20px;--wp--preset--font-size--large: 36px;--wp--preset--font-size--x-large: 42px;--wp--preset--spacing--20: 0.44rem;--wp--preset--spacing--30: 0.67rem;--wp--preset--spacing--40: 1rem;--wp--preset--spacing--50: 1.5rem;--wp--preset--spacing--60: 2.25rem;--wp--preset--spacing--70: 3.38rem;--wp--preset--spacing--80: 5.06rem;--wp--preset--shadow--natural: 6px 6px 9px rgba(0, 0, 0, 0.2);--wp--preset--shadow--deep: 12px 12px 50px rgba(0, 0, 0, 0.4);--wp--preset--shadow--sharp: 6px 6px 0px rgba(0, 0, 0, 0.2);--wp--preset--shadow--outlined: 6px 6px 0px -3px rgba(255, 255, 255, 1), 6px 6px rgba(0, 0, 0, 1);--wp--preset--shadow--crisp: 6px 6px 0px rgba(0, 0, 0, 1);}:where(.is-layout-flex){gap: 0.5em;}:where(.is-layout-grid){gap: 0.5em;}body .is-layout-flex{display: flex;}.is-layout-flex{flex-wrap: wrap;align-items: center;}.is-layout-flex > :is(*, div){margin: 0;}body .is-layout-grid{display: grid;}.is-layout-grid > :is(*, div){margin: 0;}:where(.wp-block-columns.is-layout-flex){gap: 2em;}:where(.wp-block-columns.is-layout-grid){gap: 2em;}:where(.wp-block-post-template.is-layout-flex){gap: 1.25em;}:where(.wp-block-post-template.is-layout-grid){gap: 1.25em;}.has-black-color{color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-color{color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-color{color: var(--wp--preset--color--white) !important;}.has-pale-pink-color{color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-color{color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-color{color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-color{color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-color{color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-color{color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-color{color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-color{color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-color{color: var(--wp--preset--color--vivid-purple) !important;}.has-black-background-color{background-color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-background-color{background-color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-background-color{background-color: var(--wp--preset--color--white) !important;}.has-pale-pink-background-color{background-color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-background-color{background-color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-background-color{background-color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-background-color{background-color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-background-color{background-color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-background-color{background-color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-background-color{background-color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-background-color{background-color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-background-color{background-color: var(--wp--preset--color--vivid-purple) !important;}.has-black-border-color{border-color: var(--wp--preset--color--black) !important;}.has-cyan-bluish-gray-border-color{border-color: var(--wp--preset--color--cyan-bluish-gray) !important;}.has-white-border-color{border-color: var(--wp--preset--color--white) !important;}.has-pale-pink-border-color{border-color: var(--wp--preset--color--pale-pink) !important;}.has-vivid-red-border-color{border-color: var(--wp--preset--color--vivid-red) !important;}.has-luminous-vivid-orange-border-color{border-color: var(--wp--preset--color--luminous-vivid-orange) !important;}.has-luminous-vivid-amber-border-color{border-color: var(--wp--preset--color--luminous-vivid-amber) !important;}.has-light-green-cyan-border-color{border-color: var(--wp--preset--color--light-green-cyan) !important;}.has-vivid-green-cyan-border-color{border-color: var(--wp--preset--color--vivid-green-cyan) !important;}.has-pale-cyan-blue-border-color{border-color: var(--wp--preset--color--pale-cyan-blue) !important;}.has-vivid-cyan-blue-border-color{border-color: var(--wp--preset--color--vivid-cyan-blue) !important;}.has-vivid-purple-border-color{border-color: var(--wp--preset--color--vivid-purple) !important;}.has-vivid-cyan-blue-to-vivid-purple-gradient-background{background: var(--wp--preset--gradient--vivid-cyan-blue-to-vivid-purple) !important;}.has-light-green-cyan-to-vivid-green-cyan-gradient-background{background: var(--wp--preset--gradient--light-green-cyan-to-vivid-green-cyan) !important;}.has-luminous-vivid-amber-to-luminous-vivid-orange-gradient-background{background: var(--wp--preset--gradient--luminous-vivid-amber-to-luminous-vivid-orange) !important;}.has-luminous-vivid-orange-to-vivid-red-gradient-background{background: var(--wp--preset--gradient--luminous-vivid-orange-to-vivid-red) !important;}.has-very-light-gray-to-cyan-bluish-gray-gradient-background{background: var(--wp--preset--gradient--very-light-gray-to-cyan-bluish-gray) !important;}.has-cool-to-warm-spectrum-gradient-background{background: var(--wp--preset--gradient--cool-to-warm-spectrum) !important;}.has-blush-light-purple-gradient-background{background: var(--wp--preset--gradient--blush-light-purple) !important;}.has-blush-bordeaux-gradient-background{background: var(--wp--preset--gradient--blush-bordeaux) !important;}.has-luminous-dusk-gradient-background{background: var(--wp--preset--gradient--luminous-dusk) !important;}.has-pale-ocean-gradient-background{background: var(--wp--preset--gradient--pale-ocean) !important;}.has-electric-grass-gradient-background{background: var(--wp--preset--gradient--electric-grass) !important;}.has-midnight-gradient-background{background: var(--wp--preset--gradient--midnight) !important;}.has-small-font-size{font-size: var(--wp--preset--font-size--small) !important;}.has-medium-font-size{font-size: var(--wp--preset--font-size--medium) !important;}.has-large-font-size{font-size: var(--wp--preset--font-size--large) !important;}.has-x-large-font-size{font-size: var(--wp--preset--font-size--x-large) !important;}
:where(.wp-block-post-template.is-layout-flex){gap: 1.25em;}:where(.wp-block-post-template.is-layout-grid){gap: 1.25em;}
:where(.wp-block-columns.is-layout-flex){gap: 2em;}:where(.wp-block-columns.is-layout-grid){gap: 2em;}
:root :where(.wp-block-pullquote){font-size: 1.5em;line-height: 1.6;}
</style>
<link rel='stylesheet' id='onesignal-custom-link-style-css' href='https://www.kron4.com/wp-content/plugins/onesignal/dist/os-custom-link.css?ver=3.7' media='all' />
<link rel='stylesheet' id='advertising_styles-css' href='https://www.kron4.com/wp-content/plugins/lakana/inc/civic-science/styles/civic-science.css?ver=1.0.0' media='all' />
<link rel='stylesheet' id='nexstar-carousel-structural-css' href='https://www.kron4.com/wp-content/plugins/carousel/build/structural.736aca58516227a042ff.css?ver=736aca58516227a042ff' media='all' />
<link rel='stylesheet' id='nexstar-carousel-styles-css' href='https://www.kron4.com/wp-content/plugins/carousel/build/styles.24829c7da4dfc0111e66.css?ver=24829c7da4dfc0111e66' media='all' />
<link rel='stylesheet' id='nexstar/sailthru-newsletter/newsletter-frontend/css-css' href='https://www.kron4.com/wp-content/plugins/nexstar-sailthru-newsletter/build/newsletter-frontend-styles.9d727d0d7815052fcfaa.css?ver=9d727d0d7815052fcfaa' media='all' />
<link rel='stylesheet' id='nexstar/video-auth/assets/css-css' href='https://www.kron4.com/wp-content/plugins/nexstar-video-auth/build/video-auth-entry.db04a9b3c03325e9a3a6.css?ver=db04a9b3c03325e9a3a6' media='all' />
<link rel='stylesheet' id='sailthru-subscribe-widget-styles-css' href='https://www.kron4.com/wp-content/plugins/sailthru-widget/css/widget.subscribe.css?ver=1.1.2' media='all' />
<link rel='stylesheet' id='sailthru-subscribe-display-styles-css' href='https://www.kron4.com/wp-content/plugins/sailthru-widget/css/display.css?ver=1.1.9' media='all' />
<link crossorigin="anonymous" rel='stylesheet' id='nswv-google-fonts-css' href='https://fonts.googleapis.com/css?family=Source+Sans+Pro%3A400%2C400i%2C600%2C600i%2C700%2C700i%2C900%2C900i%7CSource+Serif+Pro%3A400%2C600%2C700%2C900%7CRoboto+Condensed%3A400%2C700%7CLora%3A400%2C700&#038;display=swap&#038;ver=1.0' media='all' />
<link rel='stylesheet' id='nswv-global-css-css' href='https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/css/global.min.css?ver=c6a3e8f69f0e9151b2cd' media='all' />
<link rel='stylesheet' id='nswv-common-css-css' href='https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/css/common.chunk.min.css?ver=04978a60d22140f93330' media='all' />
<link rel='stylesheet' id='nswv-home-css-css' href='https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/css/home.min.css?ver=f7c9a5c10f35f40b6f99' media='all' />
<link rel='stylesheet' id='nswv-video-playlist-css-css' href='https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/css/video-playlist.min.css?ver=6129f78127f486ede32b' media='all' />
<link rel='stylesheet' id='jetpack_css-css' href='https://www.kron4.com/wp-content/client-mu-plugins/jetpack/css/jetpack.css?ver=12.4' media='all' />
<script type="text/javascript" id="acm-frontend-inline-js-before">
/* <![CDATA[ */
window.nxsAcmConditionals = [];
/* ]]> */
</script>
<script type="text/javascript" id="nexstar/core/theme/scripts/front-end/js-js-extra">
/* <![CDATA[ */
var PERSISTENT_EVENT_EXPECTED_TYPES = ["nexstar\/video\/player-ready","nexstar\/login-registration\/status","nexstar\/blueconic\/before_pre_listeners","nexstar\/blueconic\/ready","nexstar\/blueconic\/pageview","nexstar\/blueconic\/before_interactions","nexstar\/blueconic\/event_ready"];
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/core/build/front-end.62b3c22cb4b04df12bbf.js?ver=62b3c22cb4b04df12bbf" id="nexstar/core/theme/scripts/front-end/js-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/onesignal/dist/nexstar-onesignal-integration.min.js?ver=3.7" id="nexstar-onesignal-integration-script-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://assets.adobedtm.com/3f27c430a962/d33d8acd711c/launch-25e943fdd407.min.js?ver=1.0.0" id="adobe-launch-library-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" id="adobe-analytics-library-js-extra">
/* <![CDATA[ */
var adobe_analytics_settings = {"adobeOrgIdentityCookieName":"kndctr_19020C7354766EB60A4C98A4_AdobeOrg_identity","adobeDemdexEndpoint":"https:\/\/dpm.demdex.net\/id?d_fieldgroup=MC&d_rtbd=json&d_ver=2&d_orgid=19020C7354766EB60A4C98A4@AdobeOrg"};
/* ]]> */
</script>
<script type="text/javascript" src="https://segment.psg.nexstardigital.net/adobeanalytics.js?ver=1.0.0" id="adobe-analytics-library-js" defer="defer" data-wp-strategy="defer"></script>
<script type="module" src="https://segment.psg.nexstardigital.net/segment.js?ver=21"></script><script type="text/javascript" id="nxst-ad-tech-test-js-extra">
/* <![CDATA[ */
var NXST_AD_TECH = {"breakpoint":"768","prebid":{"display":{"desktop":2000,"mobile":2000},"video":{"desktop":2000,"mobile":2000}},"amazon":{"display":{"desktop":2000,"mobile":2000},"video":{"desktop":2000,"mobile":2000}}};
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/nxst-ad-tech/js/bidder-timeout.js?ver=8708aaf6" id="nxst-ad-tech-test-js" defer="defer" data-wp-strategy="defer"></script>
<script src='//ak.sail-horizon.com/spm/spm.v1.min.js?ver=6.8.3' type='text/javascript' async></script><script type="text/javascript" id="nexstar-sailthru-tag-js-extra">
/* <![CDATA[ */
var sailthruTag = {"options":{"customerId":"df714baaaa586c36a81d4a865d075479"}};
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/sailthru-widget/js/tag.js?ver=799b0288" id="nexstar-sailthru-tag-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" id="nexstar/chartbeat/main-js-before">
/* <![CDATA[ */
window._sf_async_config = Object.assign(window._sf_async_config||{}, {"uid":"23192","domain":"kron4.com","flickerControl":false,"useCanonical":true,"useCanonicalDomain":true,"authors":"","type":"home page"});
/* ]]> */
</script>
<script type="text/javascript" src="https://static.chartbeat.com/js/chartbeat.js" id="nexstar/chartbeat/main-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://static.chartbeat.com/js/chartbeat_mab.js" id="chartbeat/mab-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/login-registration/assets/js/LoginRadiusV2SDK.11.3.0.js?ver=11.3.0" id="nexstar/login-registration/scripts/loginradius-sdk/js-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-includes/js/dist/dom-ready.min.js?ver=f77871ff7694fffea381" id="wp-dom-ready-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-includes/js/dist/hooks.min.js?ver=4d63a3d491d11ffd8ac6" id="wp-hooks-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-includes/js/dist/i18n.min.js?ver=5e580eb46a90c2b997e6" id="wp-i18n-js"></script>
<script type="text/javascript" id="wp-i18n-js-after">
/* <![CDATA[ */
wp.i18n.setLocaleData( { 'text direction\u0004ltr': [ 'ltr' ] } );
wp.i18n.setLocaleData( { 'text direction\u0004ltr': [ 'ltr' ] } );
/* ]]> */
</script>
<script type="text/javascript" id="nexstar/video-auth/assets/js-js-extra">
/* <![CDATA[ */
var videoAuthConfig = {"enabled":"1","preview":{"enabled":true,"duration":300000},"customization":{"banner":{"header":"Live TV Free Preview","subheader":"Create your Free Account to Watch the Full Stream","ctaText":"Sign Up"},"endCard":{"header":"Free Preview Ended","subheader":"Create your Free Account to Continue Watching","ctaText":"Sign Up","image":""}},"debug":""};
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/nexstar-video-auth/build/video-auth-entry.f1fb31c127cb844bbd0e.js?ver=f1fb31c127cb844bbd0e" id="nexstar/video-auth/assets/js-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" id="htlbid_async_script-js-before">
/* <![CDATA[ */
window.isHtlbidEnabled = true; window.htlbid = window.htlbid || {}; window.htlbid.cmd = window.htlbid.cmd || [];
/* ]]> */
</script>
<script type="text/javascript" src="https://htlbid.com/v3/kron4.com/htlbid.js?ver=1.0.0" id="htlbid_async_script-js" async="async" data-wp-strategy="async"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/nxst-advertising/dist/htlbid-advertising.min.js?ver=1.0.3" id="htlbid_script-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/lakana/build/adReferralSource.js?ver=1.0.0" id="ad_referral_source_script-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-includes/js/jquery/jquery.min.js?ver=3.7.1" id="jquery-core-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-includes/js/jquery/jquery-migrate.min.js?ver=3.4.1" id="jquery-migrate-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/js/limited-view.bundle.min.js?ver=ae01f244866ceb7e5715" id="ns-limited-view-js-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/sailthru-widget/js/widget.subscribe.js?ver=1.1.5" id="sailthru-subscribe-script-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/sailthru-widget/js/display.js?ver=1.1.2" id="sailthru-subscribe-display-script-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/lakana/inc/blueconic/scripts/blueconic.js?ver=4f8a851ad7c56d2eb0470d25b065dba6" id="blueconic_script-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/lakana/inc/blueconic/scripts/login-registration-integration.js?ver=1750369402" id="nexstar/blueconic/script-url-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/lakana/inc/blueconic/scripts/login-registration-bc-wall.js?ver=1746718333" id="nexstar/blueconic/bc-wall-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/search-guard/build/search-guard.e49b9e4a0bfe7b7b8ac4.js?ver=e49b9e4a0bfe7b7b8ac4" id="search-guard-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/htlbid/build/htlbid-video-bidding.3a4f855fdd1cb9fb471a.js?ver=3a4f855fdd1cb9fb471a" id="nexstar/htlbid/scripts/js-js" defer="defer" data-wp-strategy="defer"></script>
<script defer type="text/javascript" src="https://stats.wp.com/e-202543.js" id="jetpack-stats-js"></script>
<script type="text/javascript" id="jetpack-stats-js-after">
/* <![CDATA[ */
_stq = window._stq || [];
_stq.push([ "view", {v:'ext',blog:'162595944',post:'0',tz:'-7',srv:'www.kron4.com',hp:'vip',j:'1:12.4'} ]);
_stq.push([ "clickTrackerInit", "162595944", "0" ]);
/* ]]> */
</script>
<link rel="https://api.w.org/" href="https://www.kron4.com/wp-json/" /><link rel="EditURI" type="application/rsd+xml" title="RSD" href="https://www.kron4.com/xmlrpc.php?rsd" />
<meta name="generator" content="WordPress 6.8.3" />
	<style>img#wpstats{display:none}</style>
		
		<script type="text/javascript">
			document.addEventListener("DOMContentLoaded", function() {
				// Check if the user is on a mobile device
				if (window.innerWidth <= 768) {
					// Select the div with class civic-science-sidebar-container
					var sourceDiv = document.querySelector(".civic-science-sidebar-container");
					var targetDiv = document.querySelector(".main-area-top.widget-area");

					// Check if both the source and target divs exist in the DOM
					if (sourceDiv && targetDiv) {
						// Move the sourceDiv right before the targetDiv
						targetDiv.parentNode.insertBefore(sourceDiv, targetDiv);
					}
				}
			});
		</script><style>
		.site-header .site-header__branding {
            background-position: center;
            background-repeat: no-repeat;
            background-size: cover;
        }
		@media (min-width: 1024px) {}@media (max-width: 899px) {}</style><script type="text/javascript">var sailthru_vars = {"ajaxurl":"https:\/\/www.kron4.com\/wp-admin\/admin-ajax.php"}</script>
<!-- Jetpack Open Graph Tags -->
<meta property="og:type" content="website" />
<meta property="og:title" content="KRON4" />
<meta property="og:description" content="The Bay Area&#039;s Local News Station" />
<meta property="og:url" content="https://www.kron4.com/" />
<meta property="og:site_name" content="KRON4" />
<meta property="og:image" content="https://www.kron4.com/wp-content/uploads/sites/11/2019/06/cropped-KRON4-Favicon-512x512.png?strip=1&#038;w=250" />
<meta property="og:image:alt" content="" />
<meta property="og:locale" content="en_US" />
<meta name="twitter:description" content="The Bay Area&#039;s Local News Station" />
<meta name="twitter:title" content="KRON4" />
<meta name="twitter:card" content="summary" />

<!-- End Jetpack Open Graph Tags -->
<link rel="icon" href="https://www.kron4.com/wp-content/uploads/sites/11/2019/06/cropped-KRON4-Favicon-512x512.png?w=32" sizes="32x32" />
<link rel="icon" href="https://www.kron4.com/wp-content/uploads/sites/11/2019/06/cropped-KRON4-Favicon-512x512.png?w=192" sizes="192x192" />
<link rel="apple-touch-icon" href="https://www.kron4.com/wp-content/uploads/sites/11/2019/06/cropped-KRON4-Favicon-512x512.png?w=180" />
<meta name="msapplication-TileImage" content="https://www.kron4.com/wp-content/uploads/sites/11/2019/06/cropped-KRON4-Favicon-512x512.png?w=270" />
</head>

<body class="home blog wp-custom-logo wp-theme-nexstar wp-child-theme-nexstar-wv nexstar-wv">
	
<!-- Google Tag Manager (noscript) -->
<noscript><iframe src="//www.googletagmanager.com/ns.html?id=GTM-KJJZHXD"
height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
<!-- End Google Tag Manager (noscript) -->

	
<!-- Google Tag Manager (noscript) -->
<noscript><iframe src="//www.googletagmanager.com/ns.html?id=GTM-KNNPZPH"
height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
<!-- End Google Tag Manager (noscript) -->

	<div id="page" class="site">
		<a class="skip-link screen-reader-text" href="#content">Skip to content</a>

		
<header id="masthead" class="site-header site-header--channel-selector" role="banner" data-component="siteHeader">
	<div class="site-header__content">
					<h1 class="screen-reader-text"><a href="https://www.kron4.com/" rel="home">KRON4</a></h1>
		
		<div class="site-header__branding">
			<div class="site-header__branding__content">
				<div class="site-header__info">
					
<div class="site-header__weather" data-module-type="weather-widget">
			<a href="https://www.kron4.com/weather/" data-link-type="header-weather-widget" data-link-label="San Francisco">
			<span class="site-header__weather-region">San Francisco</span>
			<span class="site-header__weather-forecast">
				<span class="site-header__weather-forecast__text">64&deg;</span>
				<figure class="site-header__weather-forecast__icon">
					<span class="weather-icon weather-icon-sm weather-icon-light-28"></span>
				</figure>
			</span>
		</a>
	</div>
					<section class="live-now-button no-thumb">
	<div class="site-header__live-button">
		<div class="site-header__live-button-desktop" data-link-category="Live Now" data-module-type="header-live-now">
			<a href="https://www.kron4.com/watch-kron4-news-online/" data-link-position='1' data-link-type="header-live-now" data-link-label="LIVE NOW">
				<div class="live-card">
					<img
						class="live-card__img"
						src=" "
						alt=""
						width="132" height="85"
						loading="eager" decoding="async"
					/>
					<span class="live-card__badge" aria-hidden="true">
						<span class="live-card__badge-text"></span>
					</span>
				</div>
			</a>
			<div class="site-header__live-button-description">
				<a title="KRON4 News" href="https://www.kron4.com/watch-kron4-news-online/">
					KRON4 News				</a>
			</div>
		</div>
	</div>
</section>
				</div>
				<div class="site-header__logo">
					<a href="https://www.kron4.com/" rel="home">
						<div
							class="site-header__logo-bg"
							style="background-image: url('https://www.kron4.com/wp-content/uploads/sites/11/2025/04/cropped-KRON4-footer-update-1.png');"
						></div>
					</a>
				</div>
				<div class="site-header__widget" data-link-category="Sailthru" data-module-type="sailthru-signup">
							<!-- Login Registration plugin links -->
		<div class="lr-login-button lr-header-links">
			<!-- Sign Up button (shown when logged out) -->
			<button class="lr-link-button lr-signup-button-main" type="button" hidden>Sign Up</button>
			<!-- Account dropdown (shown when logged in) -->
			<a href="#" class="lr-join-my-account-main" hidden>
				<span id="lr-login-text" class="lr-login-text">Account</span>
			</a>
			<div class="lr-dropdown-menu" aria-hidden="true">
				<ul class="lr-dropdown-sub-menu">
					<li><a class="lr-profile-link" href="#">Profile</a></li>
					<li><a class="lr-link-button lr-logout-button" href="#">Log Out</a></li>
				</ul>
			</div>
		</div>
							
<div class="site-header__weather" data-module-type="weather-widget">
			<a href="https://www.kron4.com/weather/" data-link-type="header-weather-widget" data-link-label="San Francisco">
			<span class="site-header__weather-region">San Francisco</span>
			<span class="site-header__weather-forecast">
				<span class="site-header__weather-forecast__text">64&deg;</span>
				<figure class="site-header__weather-forecast__icon">
					<span class="weather-icon weather-icon-sm weather-icon-light-28"></span>
				</figure>
			</span>
		</a>
	</div>
															<div class="site-header__sponsor">
						<aside class="ad-unit ad-unit--microbar ad-unit--microbar--header">
															<span class="ad_unit__label">Sponsored By</span>
														<div class="ad-unit__content">
								     <div id="acm-ad-tag-header-microbar-header-microbar"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[900,0],[[88,31]]],[[0,0],[]]],&quot;size&quot;:[88,31]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;header-microbar&quot;,&quot;fold&quot;:&quot;atf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-header-microbar-header-microbar" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     							</div>
						</aside>
					</div>
										<button class="site-header__toggle" aria-controls="supernav" aria-expanded="false">
						<span class="screen-reader-text">Toggle Menu</span>
						<span class="icon icon--navicon">
							
<svg aria-hidden="true" tabindex="-1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 19.969 12.063">
	<title>Open Navigation</title>
	<path fill="#fff" d="M.793 1.556h18.363a.778.778 0 1 0 0-1.555H.793a.854.854 0 0 0-.809.778.73.73 0 0 0 .809.777zm18.363 3.695H.793a.778.778 0 1 0 0 1.555h18.363a.778.778 0 1 0 0-1.555zm0 5.25H.793a.779.779 0 1 0 0 1.556h18.363a.779.779 0 1 0 0-1.557z" />
</svg>
						</span>
						<span class="icon icon--close">
							
<svg aria-hidden="true" tabindex="-1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16.85 16.875">
	<title>Close Navigation</title>
	<path fill="#fff" d="M9.65 8.454l6.88-7.063a.809.809 0 0 0 0-1.15.782.782 0 0 0-1.14 0L8.52 7.305 1.37.241a.782.782 0 0 0-1.14 0 .809.809 0 0 0 0 1.15l7.15 7.063-7.15 7.063a.809.809 0 0 0 0 1.15.824.824 0 0 0 .6.219.787.787 0 0 0 .59-.219l7.15-7.063 6.87 7.063a.824.824 0 0 0 .6.219.619.619 0 0 0 .54-.219.792.792 0 0 0 0-1.15z" />
</svg>
						</span>
					</button>
				</div>
			</div>
		</div>

		<nav id="siteNavigation" class="site-header__navigation">
			<div class="site-header__search-full">
				
<form role="search" class="search-form site-header__search-form" action="https://www.kron4.com/" data-module-type="site-search" data-link-category="Site Search">
	<span class="screen-reader-text">Search</span>
	<div class="search-form__fields">
		<input type="submit" name="submit" value="" />
		<input type="search" name="s" placeholder="Search" value="" />
			</div>
			<p class="search-message">Please enter a search term.</p>
	</form>
			</div>

			<div class="site-header__navigation__content">
				<h2 class="screen-reader-text">Primary Menu</h2>

				<ul id="supernav" class="menu">
	<li id="menu-item-12113" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-has-children menu-item-12113"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a target="_blank" href="https://www.kron4.com/live-news/" data-link-type="navigation-link">Watch Live</a>
<div class="dropnav dropnav--1-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="1">
	<li id="menu-item-1442287" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-1442287"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/watch-kron4-news-online/" data-link-type="navigation-link">Watch KRON4 News Online</a></li>
	<li id="menu-item-211161" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-211161"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="http://kron4.com/video" data-link-type="navigation-link">Video Center</a></li>
	<li id="menu-item-62512" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-62512"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/television-schedule/" data-link-type="navigation-link">Television Schedule</a></li>
</ul>
</div></div></li>
<li id="menu-item-11103" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-has-children menu-item-has-articles menu-item-11103"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/" data-link-type="navigation-link">News</a>
<div class="dropnav dropnav--4-col dropnav--full-width">
	<div class="dropnav__section dropnav__section--sub-menu dropnav__section--autofill">
		<ul class="sub-menu" data-columns="3">
	<li id="menu-item-11104" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-11104"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/bay-area/" data-link-type="navigation-link">Bay Area</a></li>
	<li id="menu-item-909035" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-909035"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/california/" data-link-type="navigation-link">California</a></li>
	<li id="menu-item-1501977" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1501977"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/california-politics/" data-link-type="navigation-link">California Politics</a></li>
	<li id="menu-item-2210677" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-2210677"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/technology-ai/" data-link-type="navigation-link">Tech/AI</a></li>
	<li id="menu-item-2054997" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-2054997"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/bay-area-ice-raids/" data-link-type="navigation-link">ICE raids in Bay Area</a></li>
	<li id="menu-item-1899452" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1899452"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/focus-on-fentanyl/" data-link-type="navigation-link">Focus on Fentanyl</a></li>
	<li id="menu-item-11323" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-11323"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/national/" data-link-type="navigation-link">National</a></li>
	<li id="menu-item-1607007" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1607007"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/washington-dc/" data-link-type="navigation-link">Washington-DC</a></li>
	<li id="menu-item-460986" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-460986"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/wildfires/" data-link-type="navigation-link">Wildfires</a></li>
	<li id="menu-item-1345866" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1345866"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/politics/inside-california-politics/" data-link-type="navigation-link">Inside California Politics</a></li>
	<li id="menu-item-905594" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-905594"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/reviews/br/" data-link-type="navigation-link">BestReviews</a></li>
	<li id="menu-item-615358" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-615358"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/real-estate/" data-link-type="navigation-link">Real Estate</a></li>
	<li id="menu-item-1171170" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1171170"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/hill-politics/" data-link-type="navigation-link">Politics from The Hill</a></li>
	<li id="menu-item-1409742" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1409742"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/bay-area-backroads/" data-link-type="navigation-link">Bay Area Backroads</a></li>
	<li id="menu-item-12078" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-12078"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/features/dine-dish/" data-link-type="navigation-link">Dine &#038; Dish</a></li>
	<li id="menu-item-1035368" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1035368"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/automotive/" data-link-type="navigation-link">Automotive News</a></li>
	<li id="menu-item-983582" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-983582"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/business/press-releases/" data-link-type="navigation-link">Press Releases</a></li>
	<li id="menu-item-881196" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-881196"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/world/" data-link-type="navigation-link">World</a></li>
	<li id="menu-item-1577384" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1577384"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/veterans-voices/" data-link-type="navigation-link">Veterans Voices</a></li>
</ul>
</div><div class="dropnav__section dropnav__section--article-list dropnav__section--quarter"><div class="article-list article-list--bulleted"><h3 class="article-list__heading">Top Stories</h3><div class="article-list__content"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 														>
			
			Border Patrol operations canceled for Bay Area, Oakland&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-24T12:39:24-07:00" >4 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</articledata-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 														>
			
			Police in Palo Alto looking for man who allegedly&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-24T11:21:35-07:00" >1 hour ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
</articledata-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 														>
			
			3 arrested in Bay Area after thefts from Ukiah bank
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-24T10:13:38-07:00" >2 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</articledata-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 														>
			
			Moderate to heavy rain possible in parts of Bay Area&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-24T10:07:15-07:00" >3 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</article></div></div></div></div></li>
<li id="menu-item-12044" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-has-children menu-item-12044"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/weather-san-francisco/" data-link-type="navigation-link">Weather</a>
<div class="dropnav dropnav--1-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="1">
	<li id="menu-item-12046" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12046"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/weather-san-francisco/" data-link-type="navigation-link">Today&#8217;s Forecast</a></li>
	<li id="menu-item-12045" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12045"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/weather-san-francisco/weather-san-francisco-radar/" data-link-type="navigation-link">Weather Radar</a></li>
</ul>
</div></div></li>
<li id="menu-item-81452" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-has-children menu-item-81452"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/san-francisco-traffic-conditions/" data-link-type="navigation-link">Traffic</a>
<div class="dropnav dropnav--1-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="1">
	<li id="menu-item-63568" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-63568"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/san-francisco-traffic-conditions/" data-link-type="navigation-link">Bay Area Traffic Map</a></li>
</ul>
</div></div></li>
<li id="menu-item-12067" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-has-children menu-item-has-articles menu-item-12067"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/sports/" data-link-type="navigation-link">Sports</a>
<div class="dropnav dropnav--4-col dropnav--full-width">
	<div class="dropnav__section dropnav__section--sub-menu dropnav__section--half">
		<ul class="sub-menu" data-columns="2">
	<li id="menu-item-12074" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-12074"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/mlb/giants/" data-link-type="navigation-link">San Francisco Giants</a></li>
	<li id="menu-item-12068" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-12068"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/nba/warriors/" data-link-type="navigation-link">Golden State Warriors</a></li>
	<li id="menu-item-87784" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-87784"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/nfl/49ers/" data-link-type="navigation-link">San Francisco 49ers</a></li>
	<li id="menu-item-1913801" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1913801"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/nfl/49ers/red-and-gold-zone/" data-link-type="navigation-link">Red and Gold Zone</a></li>
	<li id="menu-item-12070" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-12070"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/nhl/sharks/" data-link-type="navigation-link">San Jose Sharks Sharks</a></li>
	<li id="menu-item-12073" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-12073"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/mlb/as/" data-link-type="navigation-link">Athletics</a></li>
	<li id="menu-item-12071" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-12071"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/nfl/raiders/" data-link-type="navigation-link">Raiders</a></li>
	<li id="menu-item-2097575" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-2097575"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/reviews/br/sports-fitness-br/soccer-br/" data-link-type="navigation-link">Soccer</a></li>
	<li id="menu-item-2097568" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-2097568"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/sports/nascar-news/" data-link-type="navigation-link">NASCAR</a></li>
</ul>
</div><div class="dropnav__section dropnav__section--article-list dropnav__section--quarter"><div class="article-list article-list--top-story"><h3 class="article-list__heading">Top Stories</h3><div class="article-list__content"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/mlb/giants/tony-vitello-giants-manager/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Tennessee baseball coach Tony Vitello reportedly hired as next SF Giants manager" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/mlb/giants/tony-vitello-giants-manager/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Tennessee baseball coach Tony Vitello reportedly hired as next SF Giants manager" 														>
			
			Tennessee baseball coach Tony Vitello reportedly&nbsp;&hellip;
										</a>
					</h4>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/mlb/giants/tony-vitello-giants-manager/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Tennessee baseball coach Tony Vitello reportedly hired as next SF Giants manager" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://i0.wp.com/www.kron4.com/wp-content/uploads/sites/11/2025/10/AP23055804533263.jpg?w=2000&#038;ssl=1"
			alt=""
			srcset=""
			sizes=""
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</article></div></div></div><div class="dropnav__section dropnav__section--article-list dropnav__section--quarter"><div class="article-list article-list--bulleted"><h3 class="article-list__heading article-list__heading--hidden">Top Stories</h3><div class="article-list__content"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/former-raider-doug-martin-struggled-with-mental-health-before-dying-in-oakland-police-custody-family-says/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Former Raider Doug Martin struggled with mental health before dying in Oakland police custody, family says" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/former-raider-doug-martin-struggled-with-mental-health-before-dying-in-oakland-police-custody-family-says/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Former Raider Doug Martin struggled with mental health before dying in Oakland police custody, family says" 														>
			
			Former Raider Doug Martin struggled with mental health&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-24T07:58:12-07:00" >5 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/former-raider-doug-martin-struggled-with-mental-health-before-dying-in-oakland-police-custody-family-says/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Former Raider Doug Martin struggled with mental health before dying in Oakland police custody, family says" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</articledata-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/womens-pro-baseball-league-picks-san-francisco-for-new-team/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Women’s pro baseball league picks San Francisco for new team" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/womens-pro-baseball-league-picks-san-francisco-for-new-team/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Women’s pro baseball league picks San Francisco for new team" 														>
			
			Women’s pro baseball league picks San Francisco for&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-21T18:43:05-07:00" >3 days ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/womens-pro-baseball-league-picks-san-francisco-for-new-team/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Women’s pro baseball league picks San Francisco for new team" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</articledata-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/chess-grandmaster-and-bay-area-native-daniel-naroditsky-29-dies-unexpectedly/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Chess grandmaster and Bay Area native Daniel Naroditsky, 29, dies unexpectedly" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/chess-grandmaster-and-bay-area-native-daniel-naroditsky-29-dies-unexpectedly/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Chess grandmaster and Bay Area native Daniel Naroditsky, 29, dies unexpectedly" 														>
			
			Chess grandmaster and Bay Area native Daniel Naroditsky,&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-21T05:38:45-07:00" >3 days ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/chess-grandmaster-and-bay-area-native-daniel-naroditsky-29-dies-unexpectedly/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Chess grandmaster and Bay Area native Daniel Naroditsky, 29, dies unexpectedly" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
</articledata-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><article class="article-list__article">

<div
	class="article-list__article-text"
	data-context="supernav"
	data-article-list-id=""
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/sports/oakland-born-former-all-pro-rb-doug-martin-dies-at-36/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Oakland-born, former All-Pro RB Doug Martin dies at 36" 			>
		</a>

		<h4 class="article-list__article-title">
													<a
					href="https://www.kron4.com/sports/oakland-born-former-all-pro-rb-doug-martin-dies-at-36/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Oakland-born, former All-Pro RB Doug Martin dies at 36" 														>
			
			Oakland-born, former All-Pro RB Doug Martin dies&nbsp;&hellip;
										</a>
					</h4>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-19T16:16:51-07:00" >5 days ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/sports/oakland-born-former-all-pro-rb-doug-martin-dies-at-36/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Oakland-born, former All-Pro RB Doug Martin dies at 36" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
			<span class="article-list__article-mediaicon-text">Video</span>
	</span>
		</div>

					</a>
			</figure>
</article></div></div></div></div></li>
<li id="menu-item-2275024" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-has-children menu-item-2275024"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/kron-4-plus-shows/" data-link-type="navigation-link">KRON4+ Shows</a>
<div class="dropnav dropnav--1-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="1">
	<li id="menu-item-1945984" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1945984"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/this-is-our-city/" data-link-type="navigation-link">This Is Our City</a></li>
	<li id="menu-item-2275027" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-2275027"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/kron-4-plus-shows/15-with-justine/" data-link-type="navigation-link">15 with Justine</a></li>
	<li id="menu-item-2275029" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-2275029"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/kron-4-plus-shows/the-finish-with-kor-to/" data-link-type="navigation-link">The Finish with Kor &#038; Tor</a></li>
</ul>
</div></div></li>
<li id="menu-item-599608" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-has-children menu-item-599608"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/local-sponsor-highlights/" data-link-type="navigation-link">Community</a>
<div class="dropnav dropnav--1-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="1">
	<li id="menu-item-597471" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-597471"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/community/contests/" data-link-type="navigation-link">Contests</a></li>
	<li id="menu-item-2307297" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-2307297"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/kron4-salutes-local-businesses/" data-link-type="navigation-link">KRON4 Salutes Local Businesses</a></li>
	<li id="menu-item-1278070" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-1278070"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/community/calendar/#!/" data-link-type="navigation-link">Calendar</a></li>
</ul>
</div></div></li>
<li id="menu-item-1098629" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-has-children menu-item-1098629"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/" data-link-type="navigation-link">LIVE! in the Bay</a>
<div class="dropnav dropnav--4-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="4">
	<li id="menu-item-1343187" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1343187"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/a-may-zing-kids/" data-link-type="navigation-link">A-MAY-Zing Kids</a></li>
	<li id="menu-item-1302137" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302137"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-art/" data-link-type="navigation-link">Art</a></li>
	<li id="menu-item-1946157" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1946157"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/bae/" data-link-type="navigation-link">BAE</a></li>
	<li id="menu-item-1302138" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302138"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-beauty/" data-link-type="navigation-link">Beauty</a></li>
	<li id="menu-item-1108345" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1108345"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/community/contests/" data-link-type="navigation-link">Contests</a></li>
	<li id="menu-item-1307116" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1307116"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-live-in-the-bay-community/" data-link-type="navigation-link">Community</a></li>
	<li id="menu-item-1946158" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1946158"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/dance/" data-link-type="navigation-link">LITB Dance</a></li>
	<li id="menu-item-1946155" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1946155"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/diy/" data-link-type="navigation-link">DIY</a></li>
	<li id="menu-item-1302141" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302141"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-family/" data-link-type="navigation-link">Family</a></li>
	<li id="menu-item-1302144" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302144"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-fashion/" data-link-type="navigation-link">Fashion</a></li>
	<li id="menu-item-1302131" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302131"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-food/" data-link-type="navigation-link">Food</a></li>
	<li id="menu-item-1302146" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302146"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-happening/" data-link-type="navigation-link">Happening</a></li>
	<li id="menu-item-1302150" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302150"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-happy-hour/" data-link-type="navigation-link">Happy Hour</a></li>
	<li id="menu-item-1307119" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1307119"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-live-in-the-bay-health/" data-link-type="navigation-link">Health</a></li>
	<li id="menu-item-1302152" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302152"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-home/" data-link-type="navigation-link">Home</a></li>
	<li id="menu-item-1302158" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302158"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-kids/" data-link-type="navigation-link">Kids</a></li>
	<li id="menu-item-1133005" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-1133005"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay-viewers-voice/" data-link-type="navigation-link">LIVE! in the Bay ‘viewers’ voice</a></li>
	<li id="menu-item-1409730" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1409730"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/moneywise/" data-link-type="navigation-link">MoneyWise</a></li>
	<li id="menu-item-1302194" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302194"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-music/" data-link-type="navigation-link">Music</a></li>
	<li id="menu-item-1302196" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302196"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-people/" data-link-type="navigation-link">People</a></li>
	<li id="menu-item-1302200" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302200"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-pets/" data-link-type="navigation-link">Pets</a></li>
	<li id="menu-item-1302203" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302203"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-read/" data-link-type="navigation-link">Read</a></li>
	<li id="menu-item-1302206" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302206"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-shop/" data-link-type="navigation-link">Shop</a></li>
	<li id="menu-item-1946159" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1946159"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-sports/" data-link-type="navigation-link">LITB Sports</a></li>
	<li id="menu-item-1946163" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1946163"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/theater/" data-link-type="navigation-link">Theater</a></li>
	<li id="menu-item-1302210" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302210"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-travel/" data-link-type="navigation-link">Travel</a></li>
	<li id="menu-item-1302216" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1302216"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/live-in-the-bay-trending/" data-link-type="navigation-link">Trending</a></li>
	<li id="menu-item-1327813" class="menu-item menu-item-type-taxonomy menu-item-object-category menu-item-1327813"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/live-in-the-bay/be-on-the-show/" data-link-type="navigation-link">Be on the Show</a></li>
</ul>
</div></div></li>
<li id="menu-item-12121" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-has-children menu-item-12121"data-link-category="Navigation" data-module-type="navigation"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/contact-us/" data-link-type="navigation-link">About Us</a>
<div class="dropnav dropnav--2-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="2">
	<li id="menu-item-1232305" class="menu-item menu-item-type-post_type menu-item-object-post menu-item-1232305"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/news/about-us/" data-link-type="navigation-link">About Us</a></li>
	<li id="menu-item-82996" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-82996"data-link-category="Navigation" data-module-type="navigation"><a target="_blank" href="https://www.kron4.com/download-the-free-kron4-news-app/" data-link-type="navigation-link">KRON4-TV apps</a></li>
	<li id="menu-item-971285" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-971285"data-link-category="Navigation" data-module-type="navigation"><a href="https://nxslink.kron4.com/join/6sd/signup" data-link-type="navigation-link">Newsletters</a></li>
	<li id="menu-item-565366" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-565366"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/report-it/" data-link-type="navigation-link">Report It!</a></li>
	<li id="menu-item-970171" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-970171"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/links-seen-on-kron4/" data-link-type="navigation-link">Links seen on KRON4</a></li>
	<li id="menu-item-118871" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-118871"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/meet-the-team/" data-link-type="navigation-link">Meet the Team</a></li>
	<li id="menu-item-12126" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12126"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/contact-us/" data-link-type="navigation-link">Contact Us</a></li>
	<li id="menu-item-953761" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-953761"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/regional-news-partners/" data-link-type="navigation-link">Regional News Partners</a></li>
	<li id="menu-item-12124" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12124"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/work-for-us/" data-link-type="navigation-link">Work For Us</a></li>
	<li id="menu-item-62608" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-62608"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/advertise-with-us/" data-link-type="navigation-link">Advertise With Us</a></li>
	<li id="menu-item-12123" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12123"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/closed-captioning-contact-information/" data-link-type="navigation-link">Closed Captioning Contact Information</a></li>
	<li id="menu-item-302104" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-302104"data-link-category="Navigation" data-module-type="navigation"><a href="http://[ccpa-preferences]" data-link-type="navigation-link">Do Not Sell My Personal Information</a></li>
	<li id="menu-item-1008488" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-1008488"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/about-bestreviews/" data-link-type="navigation-link">About BestReviews</a></li>
</ul>
</div></div></li>
<li id="menu-item-1136690" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-has-children menu-item-1136690"data-link-category="Navigation" data-module-type="navigation"><a href="https://www.kron4.com/kron-marketplace/" data-link-type="navigation-link">Marketplace</a>
<div class="dropnav dropnav--1-col">
	<div class="dropnav__section dropnav__section--sub-menu">
		<ul class="sub-menu" data-columns="1">
	<li id="menu-item-1911070" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-1911070"><a href="https://bestreviews.com/deals" data-link-type="navigation-link">Epic Discounts</a></li>
</ul>
</div></div></li>

			<li class="menu-item menu-item-type-custom menu-item-object-custom lr-login-button" data-link-category="Navigation" data-module-type="navigation">
				<a href="#" class="lr-link-button lr-signup-button-main" hidden>Sign Up</a>
				<a class="lr-join-my-account-main" href="#" aria-haspopup="true" hidden><span id="lr-login-text" class="lr-login-text">Account</span></a>
				<div class="lr-dropdown-menu dropnav dropnav--1-col" aria-hidden="true">
					<div class="dropnav__section dropnav__section--sub-menu">
						<ul class="sub-menu" data-columns="1">
							<li class="menu-item"><a class="lr-profile-link" href="#">Profile</a></li>
							<li class="menu-item"><a class="lr-link-button lr-logout-button" href="#">Log Out</a></li>
						</ul>
					</div>
				</div>
			</li></ul>

				
<form role="search" class="search-form site-header__search-form" action="https://www.kron4.com/" data-module-type="site-search" data-link-category="Site Search">
	<span class="screen-reader-text">Search</span>
	<div class="search-form__fields">
		<input type="submit" name="submit" value="" />
		<input type="search" name="s" placeholder="Search" value="" />
			</div>
			<p class="search-message">Please enter a search term.</p>
	</form>
			</div>
		</nav>
	</div>

	<!--  Live Now banner for mobile.  -->
	<section class="live-now-button-mobile no-thumb">
	<div class="site-header__live-button">
		<div class="site-header__live-button-mobile">
			<a href="https://www.kron4.com/watch-kron4-news-online/" data-link-position='1' data-link-type="" data-link-label="LIVE">
				<div class="live-card">
					<img
						class="live-card__img"
						src=" "
						alt=""
						width="110" height="65"
						loading="eager" decoding="async"
					/>
					<span class="live-card__badge" aria-hidden="true">
						<span class="live-card__badge-text"></span>
					</span>
				</div>
			</a>
			<div class="site-header__live-button-description">
				<a title="KRON4 News" href="https://www.kron4.com/watch-kron4-news-online/">
					KRON4 News				</a>
			</div>
        </div>
	</div>
</section>

</header>

		<div class="site-content-wrapper">
							<div class="alert-banners-component-container" data-react-component="AlertBanners"></div>
			
			
<div id="content" class="site-content">
	<div class="site-content__header ">

	
							<aside class="ad-unit ad-unit--leaderboard ad-unit--above-hero ad-unit--billboard">
				<div class="ad-unit__content">
					<div id='innerdiv-billboard1'>     <div id="acm-ad-tag-billboard1-billboard1"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1280,0],[[728,90],[970,250],[970,90],[970,30]]],[[1024,0],[[728,90],[970,250],[970,90],[970,30]]],[[768,0],[[320,50]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],&quot;size&quot;:[320,50]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;billboard1&quot;,&quot;fold&quot;:&quot;atf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-billboard1-billboard1" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     </div>				</div>
			</aside>
					
		
		
		
		
		
<section id="daily-news-video" class="article-list article-list--story-grid article-list--story-grid--hero-daily-news-video alternate-layout" data-module-type="daily-news-video" data-link-category="Daily News Video">
	
<div class="main-story">
	



	<h2		class="article-list__heading screen-reader-text"
		data-module-type="headlines"
	>
		
		Headlines
		
			</h2>


<div
	class="article-list__content"
	data-module-type="headlines"
>
								<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type main-story-link"
			data-article-id="2321457"
			data-context="hero--daily-news-video"
			data-index="0"
			data-collection="article-list1"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text main-story-link"
	data-context="hero--daily-news-video"
	data-article-list-id="article-list1"
	data-article-text-classes="article-list__article-text main-story-link"
	data-article-thumb-classes="article-list__article-thumb article-list__article-thumb--is-fullbleed-on-mobile"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) 50vw, 512px&quot;]"
>
					
									<a
					href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
					class="article-list__article-label-link"
					data-link-type="daily-news-video-main-link" data-link-position="2" data-link-pinned="true" data-link-label="Top Story" 				>
			
							<span class="article-list__article-label-text">
					Top Story				</span>
			
							</a>
					
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
						data-link-type="daily-news-video-main-link" data-link-position="2" data-link-pinned="true" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
					class="article-list__article-link"
															data-link-type="daily-news-video-main-link" data-link-position="2" data-link-pinned="true" data-link-label="Border Patrol operations canceled for Bay Area, Oakland&nbsp;&hellip;" 														>
			
			Border Patrol operations canceled for Bay Area, Oakland&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area-ice-raids/" class="article-list__article-category-link category-link-1" data-link-type="daily-news-video-main-category-link" data-link-position="2" data-link-pinned="true" data-link-label="ICE raids in Bay Area"   >ICE raids in Bay Area</a> / <time datetime="2025-10-24T12:39:24-07:00" >7 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb article-list__article-thumb--is-fullbleed-on-mobile">
					<a
				href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
				class="article-list__article-link"
				data-link-type="daily-news-video-main-link" data-link-position="2" data-link-pinned="true" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=1536,864 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=1752,986 1752w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 512px"
			loading="eager"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>




</div>

	<div class="top-stories" >
		



	<h2		class="article-list__heading"
		data-module-type="more-top-stories"
	>
					<a
				href="https://www.kron4.com/news/"
				class="article-list__heading-link"
								data-link-type="daily-news-video-article-bin-heading-link" data-link-position="0" data-link-pinned="true" data-link-label="More Top Stories" 			>
		
		More Top Stories
					</a>
		
			</h2>


<div
	class="article-list__content"
	data-module-type="more-top-stories"
>
								<article
			class="article-list__article article-list__article--is-slat  article-list__article--is-media-type"
			data-article-id="2321093"
			data-context="homepage_top_stories"
			data-index="0"
			data-collection="article-list2"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="homepage_top_stories"
	data-article-list-id="article-list2"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 50vw, 200px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/coast-guard-shoots-at-driver-who-tried-to-ram-alameda-base-gate/"
						data-link-type="daily-news-video-article-bin-link" data-link-position="1" data-link-pinned="true" data-link-label="Coast Guard shoots driver trying to ram Alameda base gate" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/coast-guard-shoots-at-driver-who-tried-to-ram-alameda-base-gate/"
					class="article-list__article-link"
															data-link-type="daily-news-video-article-bin-link" data-link-position="1" data-link-pinned="true" data-link-label="Coast Guard shoots driver trying to ram Alameda base gate" 														>
			
			Coast Guard shoots driver trying to ram Alameda gate
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area/" class="article-list__article-category-link" data-link-type="daily-news-video-article-bin-category-link" data-link-position="1" data-link-pinned="true" data-link-label="Bay Area"   >Bay Area</a> / <time datetime="2025-10-24T08:37:58-07:00" >4 hours ago</time>			</footer>
			
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list__article--is-slat  article-list__article--is-media-type"
			data-article-id="2320054"
			data-context="homepage_top_stories"
			data-index="1"
			data-collection="article-list2"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="homepage_top_stories"
	data-article-list-id="article-list2"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 50vw, 200px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/live-updates-federal-agents-arriving-in-bay-area/"
						data-link-type="daily-news-video-article-bin-link" data-link-position="2" data-link-pinned="true" data-link-label="Protests, fears continue in Bay Area after Trump pauses SF surge" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/live-updates-federal-agents-arriving-in-bay-area/"
					class="article-list__article-link"
															data-link-type="daily-news-video-article-bin-link" data-link-position="2" data-link-pinned="true" data-link-label="Protests, fears continue in Bay Area after Trump pauses SF surge" 														>
			
			Protests continue after Trump pauses surge
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area-ice-raids/" class="article-list__article-category-link" data-link-type="daily-news-video-article-bin-category-link" data-link-position="2" data-link-pinned="true" data-link-label="ICE raids in Bay Area"   >ICE raids in Bay Area</a> / <time datetime="2025-10-24T05:39:33-07:00" >7 hours ago</time>			</footer>
			
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list__article--is-slat  article-list__article--is-media-type"
			data-article-id="2321191"
			data-context="homepage_top_stories"
			data-index="2"
			data-collection="article-list2"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="homepage_top_stories"
	data-article-list-id="article-list2"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 50vw, 200px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race-2/"
						data-link-type="daily-news-video-article-bin-link" data-link-position="3" data-link-pinned="true" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race-2/"
					class="article-list__article-link"
															data-link-type="daily-news-video-article-bin-link" data-link-position="3" data-link-pinned="true" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 														>
			
			Poll: Prop 50 likely to pass, Governor&#8217;s race tightens
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="daily-news-video-article-bin-category-link" data-link-position="3" data-link-pinned="true" data-link-label="National"   >National</a> / <time datetime="2025-10-24T09:27:37-07:00" >3 hours ago</time>			</footer>
			
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list__article--is-slat  article-list__article--is-media-type"
			data-article-id="2320239"
			data-context="homepage_top_stories"
			data-index="3"
			data-collection="article-list2"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="homepage_top_stories"
	data-article-list-id="article-list2"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 50vw, 200px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/trump-calling-off-plans-for-federal-deployment-to-sf-mayor-says/"
						data-link-type="daily-news-video-article-bin-link" data-link-position="4" data-link-pinned="true" data-link-label="Trump calling off plans for federal deployment to SF, mayor says" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/trump-calling-off-plans-for-federal-deployment-to-sf-mayor-says/"
					class="article-list__article-link"
															data-link-type="daily-news-video-article-bin-link" data-link-position="4" data-link-pinned="true" data-link-label="Trump calling off plans for federal deployment to SF, mayor says" 														>
			
			Trump calling off federal deployment to SF, mayor says
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area-ice-raids/" class="article-list__article-category-link" data-link-type="daily-news-video-article-bin-category-link" data-link-position="4" data-link-pinned="true" data-link-label="ICE raids in Bay Area"   >ICE raids in Bay Area</a> / <time datetime="2025-10-23T17:09:05-07:00" >20 hours ago</time>			</footer>
			
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list__article--is-slat  article-list__article--is-media-type"
			data-article-id="2321349"
			data-context="homepage_top_stories"
			data-index="4"
			data-collection="article-list2"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="homepage_top_stories"
	data-article-list-id="article-list2"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 50vw, 200px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
						data-link-type="daily-news-video-article-bin-link" data-link-position="5" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
					class="article-list__article-link"
															data-link-type="daily-news-video-article-bin-link" data-link-position="5" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 														>
			
			Palto Alto PD looking for man who exposed himself to girl
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area/" class="article-list__article-category-link" data-link-type="daily-news-video-article-bin-category-link" data-link-position="5" data-link-pinned="false" data-link-label="Bay Area"   >Bay Area</a> / <time datetime="2025-10-24T11:21:35-07:00" >1 hour ago</time>			</footer>
			
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list__article--is-slat  article-list__article--is-media-type"
			data-article-id="2321312"
			data-context="homepage_top_stories"
			data-index="5"
			data-collection="article-list2"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="homepage_top_stories"
	data-article-list-id="article-list2"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 50vw, 200px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
						data-link-type="daily-news-video-article-bin-link" data-link-position="6" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
					class="article-list__article-link"
															data-link-type="daily-news-video-article-bin-link" data-link-position="6" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 														>
			
			3 arrested in Bay Area after thefts from Ukiah bank
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area/" class="article-list__article-category-link" data-link-type="daily-news-video-article-bin-category-link" data-link-position="6" data-link-pinned="false" data-link-label="Bay Area"   >Bay Area</a> / <time datetime="2025-10-24T10:13:38-07:00" >3 hours ago</time>			</footer>
			
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
	</div>


							</article>

		

				


</div>




	</div>

	
<!-- Video Player w/Playlist -->
<section id="ns-video-bin-9288" class="ns-video-bin">
		<section
		class="article-list video-player--hero has- video-component alternate-layout"
		data-component="videoPlaylist"
		data-layout="daily_news_video"
		data-widget-name="Daily News Video"
		data-context=video_player--hero	>
		<aside class="post-video-bin article-list">
			




	
<div class="video-playlist__player" data-playlist="article-list3" data-use-ovp="1" data-sticky="1" data-minimized="1">
	<div class="video-playlist__player-intrinsic-sizer">
		<div id="player-8830"></div>
	</div>

			<header class="video-header" data-theme="light">
			<div class="video-header__title-wrap">
				<h2 class="video-title">
					<span class="video-title__text">What is the Miranda warning?</span>
					<button class="toggle">
						<span class="toggle-text">Toggle header content</span>
						<span class="toggle-icon">
<svg xmlns="http://www.w3.org/2000/svg" width="20" height="11.031">
	<path d="M19.73 9.623a.774.774 0 0 1 0 1.135.8.8 0 0 1-1.15 0L9.82 2.114l-8.43 8.644a.8.8 0 0 1-1.15 0 .774.774 0 0 1 0-1.135L9.87.007z" fill="#fff" fill-rule="evenodd"/>
</svg>
</span>
					</button>
				</h2>
			</div>

			<div class="video-meta">
				<footer class="article-list__article-meta">
					<a
						class="article-list__article-meta__category-link"
						href=""
					>
						<span class="article-list__article-meta__category-text"></span>
					</a>
					<time
						class="article-list__article-meta__time cache"
						datetime=""
					>
											</time>
				</footer>
			</div>

			<p class="video-description"></p>
		</header>
	</div>

<div
	class="article-list__content"
	data-module-type="no-title"
>
								<article
			class="article-list__article hero-video-item"
			data-article-id="8992465"
			data-context="video_player--hero"
			data-index="0"
			data-collection="article-list3"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;8992465&quot;,&quot;title&quot;:&quot;What is the Miranda warning?&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/what-is-the-miranda-warning\/8992465\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 160w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 256w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 320w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 640w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 960w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 1280w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 1920w, https:\/\/h104216-fcdn.mp.lura.live\/1\/938864\/pvw_lin\/F1D\/D51\/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;2 years ago&quot;,&quot;datetime&quot;:&quot;2023-09-13T11:10:00-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:true,&quot;title_visible&quot;:true,&quot;recommendations&quot;:true},&quot;video_id&quot;:8992465,&quot;category&quot;:{&quot;title&quot;:&quot;News&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/news\/&quot;}},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:8992465,&quot;autoplay&quot;:true,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p3&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;News&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;vconp=2&amp;cust_params=vid%3D8992465%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D309%2C906%2C301%2C311%2C304%2C305%2C306%2C270%2C271%2C240%2C298%2C297%2C281%2C279%2C295%2C249%2C257%2C275%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjg5OTI0NjUsImlzcyI6IkVabXJSNEV2NXhZbk1mZGJZNVRQYzduYUtteTMyTUtwIiwiZXhwIjoxNzYxMzM4NzY3fQ.v8SZPaISQx8iOdLdb3FbyqNwlGcylDRfgBbaLmTqk4U&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/8992465?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E5iGwc5cBaES%2BPilQb1ujX7loGseZvo70MQ%3D%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="video_player--hero"
	data-article-list-id="article-list3"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href=""
						data-link-type="daily-news-video-main-link" data-link-position="0" data-link-pinned="false" data-link-label="What is the Miranda warning?" 			>
		</a>

		<h2 class="article-list__article-title">
									
			What is the Miranda warning?
								</h2>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/" class="article-list__article-category-link" data-link-type="daily-news-video-video-bin-category-link" data-link-position="0" data-link-pinned="false" data-link-label="News"   >News</a> / <time datetime="2023-09-13T11:10:00-07:00" >2 years ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&#038;aktasgn=a0654305c667332cf7f1ae1d43464b19"
			alt=""
			srcset="https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 160w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 256w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 320w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 640w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 960w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 1280w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 1920w, https://h104216-fcdn.mp.lura.live/1/938864/pvw_lin/F1D/D51/F1DD5130E82944CC9D2FC1BC85A1790D_1_160x90.jpg?aktaexp=2082787200&amp;aktasgn=a0654305c667332cf7f1ae1d43464b19 2560w"
			sizes="(max-width: 1023px) 50vw, 876px"
			loading="eager"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

			</figure>
							</article>

		

											<article
			class="article-list__article hero-video-item"
			data-article-id="11199799"
			data-context="video_player--hero"
			data-index="1"
			data-collection="article-list3"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;11199799&quot;,&quot;title&quot;:&quot;Moderate to heavy rain possible in parts of Bay Area Friday&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/moderate-to-heavy-rain-possible-in-parts-of-bay-area-friday\/11199799\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 160w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 256w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 320w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 640w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 960w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 1280w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 1920w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093\/iupl_lin\/11A\/A19\/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;3 hours ago&quot;,&quot;datetime&quot;:&quot;2025-10-24T09:51:35-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:true,&quot;title_visible&quot;:true,&quot;recommendations&quot;:true},&quot;video_id&quot;:11199799,&quot;category&quot;:{&quot;title&quot;:&quot;Weather&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/weather\/&quot;}},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:11199799,&quot;autoplay&quot;:true,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p4&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;Weather&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;vconp=2&amp;cust_params=vid%3D11199799%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D1%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjExMTk5Nzk5LCJpc3MiOiJFWm1yUjRFdjV4WW5NZmRiWTVUUGM3bmFLbXkzMk1LcCIsImV4cCI6MTc2MTMzODc2N30.tKSKVBdWa9EftbbXF5xdxUpIfunLHVHWWT5vP5LoYko&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/11199799?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E7ym4eJoAZAP0MCtfY1mmW%2FRkDcaUpZnyJl8%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="video_player--hero"
	data-article-list-id="article-list3"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href=""
						data-link-type="daily-news-video-content-link" data-link-position="1" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area Friday" 			>
		</a>

		<h2 class="article-list__article-title">
									
			Moderate to heavy rain possible in parts of Bay Area&nbsp;&hellip;
								</h2>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/weather/" class="article-list__article-category-link" data-link-type="daily-news-video-video-bin-category-link" data-link-position="1" data-link-pinned="false" data-link-label="Weather"   >Weather</a> / <time datetime="2025-10-24T09:51:35-07:00" >3 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg"
			alt=""
			srcset="https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 160w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 256w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 320w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 640w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 960w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 1280w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 1920w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/57ccc6a1db1259e4c79e7e4d516f700c93ff7036b89d4cb01693565933d5b093/iupl_lin/11A/A19/11AA19CBD73C108203423CAA0C3C49D1_160x90.jpg 2560w"
			sizes="(max-width: 1023px) 50vw, 876px"
			loading="eager"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

			</figure>
							</article>

		

											<article
			class="article-list__article hero-video-item"
			data-article-id="11199182"
			data-context="video_player--hero"
			data-index="2"
			data-collection="article-list3"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;11199182&quot;,&quot;title&quot;:&quot;Martinez man faces 11 counts of lewd acts on a child&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/martinez-man-faces-11-counts-of-lewd-acts-on-a-child\/11199182\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 160w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 256w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 320w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 640w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 960w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 1280w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 1920w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885\/iupl_lin\/035\/64A\/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;5 hours ago&quot;,&quot;datetime&quot;:&quot;2025-10-24T07:29:29-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:true,&quot;title_visible&quot;:true,&quot;recommendations&quot;:true},&quot;video_id&quot;:11199182,&quot;category&quot;:{&quot;title&quot;:&quot;News&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/news\/&quot;}},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:11199182,&quot;autoplay&quot;:true,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p5&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;News,Video&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;vconp=2&amp;cust_params=vid%3D11199182%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D1%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjExMTk5MTgyLCJpc3MiOiJFWm1yUjRFdjV4WW5NZmRiWTVUUGM3bmFLbXkzMk1LcCIsImV4cCI6MTc2MTMzODc2N30.hbAfweg97pBIwhqorv3hRKGSpubpRRkRTHRTRUrlhrA&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/11199182?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E7ym4eJoGZQj0MCtfY1yrX%2F5kDcaUpZnyJl8%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="video_player--hero"
	data-article-list-id="article-list3"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href=""
						data-link-type="daily-news-video-content-link" data-link-position="2" data-link-pinned="false" data-link-label="Martinez man faces 11 counts of lewd acts on a child" 			>
		</a>

		<h2 class="article-list__article-title">
									
			Martinez man faces 11 counts of lewd acts on a child
								</h2>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/" class="article-list__article-category-link" data-link-type="daily-news-video-video-bin-category-link" data-link-position="2" data-link-pinned="false" data-link-label="News"   >News</a> / <time datetime="2025-10-24T07:29:29-07:00" >5 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg"
			alt=""
			srcset="https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 160w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 256w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 320w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 640w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 960w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 1280w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 1920w, https://c104216-ucdn.mp.lura.live/expiretime=2082787200/7285daafe6652e5115d9af20682934d5b8c716750d7d0c8e1e6e828177f1d885/iupl_lin/035/64A/03564A09390CED72FC8E6BFE1B7642B8_160x90.jpg 2560w"
			sizes="(max-width: 1023px) 50vw, 876px"
			loading="eager"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

			</figure>
							</article>

		

				


</div>




		</aside>
	</section>

</section>

	
<div class="quicklinks-bar">
	<h2 class="quicklinks-bar__heading">Quick Links</h2>
	<div class="quicklinks-bar__content">
									<h4 class="quicklinks-bar__item">
					<a
						href="https://www.kron4.com/news/bay-area-ice-raids/"
						data-link-type="daily-news-video-quicklinks-link" data-link-position="1" data-link-pinned="false" data-link-label="ICE in Bay Area" 					>
						ICE in Bay Area					</a>
					<div class="caret"></div>
				</h4>
												<h4 class="quicklinks-bar__item">
					<a
						href="https://www.kron4.com/people-behaving-badly/"
						data-link-type="daily-news-video-quicklinks-link" data-link-position="2" data-link-pinned="false" data-link-label="KRON4&#039;s 75th: A Look Back at People Behaving Badly" 					>
						KRON4&#039;s 75th: A Look Back at People Behaving Badly					</a>
					<div class="caret"></div>
				</h4>
												<h4 class="quicklinks-bar__item">
					<a
						href="https://www.kron4.com/news/this-is-our-city/"
						data-link-type="daily-news-video-quicklinks-link" data-link-position="3" data-link-pinned="false" data-link-label="This Is Our City" 					>
						This Is Our City					</a>
					<div class="caret"></div>
				</h4>
												<h4 class="quicklinks-bar__item">
					<a
						href="https://www.kron4.com/news/kids-programming-note-3/"
						data-link-type="daily-news-video-quicklinks-link" data-link-position="4" data-link-pinned="false" data-link-label="Kids programming note" 					>
						Kids programming note					</a>
					<div class="caret"></div>
				</h4>
						</div>
</div>

</section>
	</div>


	
	<div class="
		site-content__layout site-content__layout--has-sidebar	">
					<!-- Ad Unit Square mr1_mobile -->
			<aside class="ad-unit ad-unit--mr1-mobile">
				<div class="ad-unit__content">
					     <div id="acm-ad-tag-mr1_mobile-mr1_mobile"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1024,0],[]],[[900,0],[]],[[0,0],[[300,250]]]],&quot;size&quot;:[300,250]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;mr1_mobile&quot;,&quot;fold&quot;:&quot;atf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-mr1_mobile-mr1_mobile" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     				</div>
			</aside>
			<!-- END Ad Unit Square mr1_mobile -->
		
		<div id="primary" class="content-area">
			<main id="main" class="site-main">

				



	<section class="article-list article-list--homepage-headline-list">
		<div class="article-list__content">
											<section class="article-list article-list--headline-image" >
					



	<h2		class="article-list__heading"
		data-module-type="bay-area"
	>
					<a
				href="https://www.kron4.com/news/bay-area/"
				class="article-list__heading-link"
								data-link-type="heading-link" data-link-position="0" data-link-pinned="true" data-link-label="Bay Area" 			>
		
		Bay Area
					</a>
		
			</h2>


<div
	class="article-list__content"
	data-module-type="bay-area"
>
								<article
			class="article-list__article"
			data-article-id="2321457"
			data-context="two_col_media_grid"
			data-index="0"
			data-collection="article-list4"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list4"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 														>
			
			Border Patrol operations canceled for Bay Area, Oakland&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area-ice-raids/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="1" data-link-pinned="false" data-link-label="ICE raids in Bay Area"   >ICE raids in Bay Area</a> / <time datetime="2025-10-24T12:39:24-07:00" >7 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=1536,864 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=1752,986 1752w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/08/snapshot-2-1.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321349"
			data-context="two_col_media_grid"
			data-index="1"
			data-collection="article-list4"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list4"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 														>
			
			Palto Alto PD looking for man who exposed himself&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="2" data-link-pinned="false" data-link-label="Bay Area"   >Bay Area</a> / <time datetime="2025-10-24T11:21:35-07:00" >1 hour ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg 1224w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2024/08/palo-alto-police-pd-car-vehicle-cruiser.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321312"
			data-context="two_col_media_grid"
			data-index="2"
			data-collection="article-list4"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list4"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 														>
			
			3 arrested in Bay Area after thefts from Ukiah bank
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="3" data-link-pinned="false" data-link-label="Bay Area"   >Bay Area</a> / <time datetime="2025-10-24T10:13:38-07:00" >3 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/3-arrested-in-bay-area-after-thefts-from-ukiah-bank/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="3 arrested in Bay Area after thefts from Ukiah bank" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg 4500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?resize=1080,720 1080w, https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?resize=1536,1024 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?resize=2048,1365 2048w, https://www.kron4.com/wp-content/uploads/sites/11/2025/05/GettyImages-1278651554.jpg?resize=50,33 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321298"
			data-context="two_col_media_grid"
			data-index="3"
			data-collection="article-list4"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list4"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 														>
			
			Here&#8217;s when rain could return to the Bay Area
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/weather/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="4" data-link-pinned="false" data-link-label="Weather"   >Weather</a> / <time datetime="2025-10-24T10:07:15-07:00" >3 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2021/03/gettyimages-109249602-594x594-1.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2021/03/gettyimages-109249602-594x594-1.jpg 594w, https://www.kron4.com/wp-content/uploads/sites/11/2021/03/gettyimages-109249602-594x594-1.jpg?resize=300,208 300w, https://www.kron4.com/wp-content/uploads/sites/11/2021/03/gettyimages-109249602-594x594-1.jpg?resize=50,35 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321290"
			data-context="two_col_media_grid"
			data-index="4"
			data-collection="article-list4"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list4"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/mountain-view-barber-accused-in-dozens-of-sex-crimes-captured-in-guatemala/"
						data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Mountain View barber accused in dozens of sex crimes captured in Guatemala" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/mountain-view-barber-accused-in-dozens-of-sex-crimes-captured-in-guatemala/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Mountain View barber accused in dozens of sex crimes captured in Guatemala" 														>
			
			Barber accused in dozens of sex crimes found in Guatemala
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/bay-area/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="5" data-link-pinned="false" data-link-label="Bay Area"   >Bay Area</a> / <time datetime="2025-10-24T11:53:56-07:00" >52 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/mountain-view-barber-accused-in-dozens-of-sex-crimes-captured-in-guatemala/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Mountain View barber accused in dozens of sex crimes captured in Guatemala" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2024/11/barber-on-the-run.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2024/11/barber-on-the-run.jpg 1048w, https://www.kron4.com/wp-content/uploads/sites/11/2024/11/barber-on-the-run.jpg?resize=300,203 300w, https://www.kron4.com/wp-content/uploads/sites/11/2024/11/barber-on-the-run.jpg?resize=768,520 768w, https://www.kron4.com/wp-content/uploads/sites/11/2024/11/barber-on-the-run.jpg?resize=50,34 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>

	<div
		class="article-list__read-more"
		data-module-type="bay-area"
	>
					<a href="https://www.kron4.com/news/bay-area/"
								data-link-type="cta-button" data-link-position="0" data-link-pinned="true" data-link-label="View All Bay Area" 			>
				View All Bay Area							</a>
				</div>
	


				</section>
											<section class="article-list article-list--headline-image" >
					



	<h2		class="article-list__heading"
		data-module-type="national"
	>
					<a
				href="https://www.kron4.com/news/national/"
				class="article-list__heading-link"
								data-link-type="heading-link" data-link-position="0" data-link-pinned="true" data-link-label="National" 			>
		
		National
					</a>
		
			</h2>


<div
	class="article-list__content"
	data-module-type="national"
>
								<article
			class="article-list__article"
			data-article-id="2321469"
			data-context="two_col_media_grid"
			data-index="0"
			data-collection="article-list5"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list5"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/senior-advocacy-group-wants-to-establish-a-minimum-annual-cola-increase-how-would-it-work/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Senior advocacy group wants to establish a ‘minimum’ annual COLA increase: How would it work?" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/senior-advocacy-group-wants-to-establish-a-minimum-annual-cola-increase-how-would-it-work/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Senior advocacy group wants to establish a ‘minimum’ annual COLA increase: How would it work?" 														>
			
			A &#8216;minimum&#8217; annual COLA increase? How it could work
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="1" data-link-pinned="false" data-link-label="National"   >National</a> / <time datetime="2025-10-24T12:36:38-07:00" >9 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/senior-advocacy-group-wants-to-establish-a-minimum-annual-cola-increase-how-would-it-work/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Senior advocacy group wants to establish a ‘minimum’ annual COLA increase: How would it work?" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1310131960-4.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1310131960-4.jpg 724w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1310131960-4.jpg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1310131960-4.jpg?resize=50,33 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321445"
			data-context="two_col_media_grid"
			data-index="1"
			data-collection="article-list5"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list5"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/pentagon-sends-largest-aircraft-carrier-to-caribbean-amid-boat-strikes/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Pentagon sends largest aircraft carrier to Caribbean amid boat strikes" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/pentagon-sends-largest-aircraft-carrier-to-caribbean-amid-boat-strikes/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Pentagon sends largest aircraft carrier to Caribbean amid boat strikes" 														>
			
			Pentagon sends largest aircraft carrier to Caribbean
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="2" data-link-pinned="false" data-link-label="National"   >National</a> / <time datetime="2025-10-24T12:16:25-07:00" >30 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/pentagon-sends-largest-aircraft-carrier-to-caribbean-amid-boat-strikes/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Pentagon sends largest aircraft carrier to Caribbean amid boat strikes" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/7e3462dd0cd8489ca789885f5ec0293a-e1761333068458.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/7e3462dd0cd8489ca789885f5ec0293a-e1761333068458.jpg 1200w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/7e3462dd0cd8489ca789885f5ec0293a-e1761333068458.jpg?resize=300,158 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/7e3462dd0cd8489ca789885f5ec0293a-e1761333068458.jpg?resize=768,403 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/7e3462dd0cd8489ca789885f5ec0293a-e1761333068458.jpg?resize=50,26 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321325"
			data-context="two_col_media_grid"
			data-index="2"
			data-collection="article-list5"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list5"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/cholesterol-medication-recalled-over-failed-dissolution-specifications-what-to-know/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Cholesterol medication recalled over ‘failed dissolution specifications’: What to know" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/cholesterol-medication-recalled-over-failed-dissolution-specifications-what-to-know/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Cholesterol medication recalled over ‘failed dissolution specifications’: What to know" 														>
			
			Cholesterol medication recalled: What to know
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="3" data-link-pinned="false" data-link-label="National"   >National</a> / <time datetime="2025-10-24T10:18:31-07:00" >2 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/cholesterol-medication-recalled-over-failed-dissolution-specifications-what-to-know/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Cholesterol medication recalled over ‘failed dissolution specifications’: What to know" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GenericStatinGettyImages-1500544380-e1761324678234.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GenericStatinGettyImages-1500544380-e1761324678234.jpg 800w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GenericStatinGettyImages-1500544380-e1761324678234.jpg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GenericStatinGettyImages-1500544380-e1761324678234.jpg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GenericStatinGettyImages-1500544380-e1761324678234.jpg?resize=50,33 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321257"
			data-context="two_col_media_grid"
			data-index="3"
			data-collection="article-list5"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list5"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/what-states-export-the-most-beef/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="What states export the most beef?" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/what-states-export-the-most-beef/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="What states export the most beef?" 														>
			
			What states export the most beef?
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="4" data-link-pinned="false" data-link-label="National"   >National</a> / <time datetime="2025-10-24T08:58:14-07:00" >4 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/what-states-export-the-most-beef/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="What states export the most beef?" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg 1400w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Lead-Beef-imports-anger_102125_AP_Tony-Gutierrez.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="2321227"
			data-context="two_col_media_grid"
			data-index="4"
			data-collection="article-list5"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="two_col_media_grid"
	data-article-list-id="article-list5"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/thousands-of-curling-irons-recalled-amid-burn-injuries/"
						data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Thousands of curling irons recalled amid burn injuries" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/thousands-of-curling-irons-recalled-amid-burn-injuries/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Thousands of curling irons recalled amid burn injuries" 														>
			
			Thousands of curling irons recalled amid burn injuries
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="5" data-link-pinned="false" data-link-label="National"   >National</a> / <time datetime="2025-10-24T08:15:33-07:00" >5 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/thousands-of-curling-irons-recalled-amid-burn-injuries/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Thousands of curling irons recalled amid burn injuries" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1026616834-e1761318075327.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1026616834-e1761318075327.jpg 800w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1026616834-e1761318075327.jpg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1026616834-e1761318075327.jpg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/GettyImages-1026616834-e1761318075327.jpg?resize=50,33 50w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>

	<div
		class="article-list__read-more"
		data-module-type="national"
	>
					<a href="https://www.kron4.com/news/national/"
								data-link-type="cta-button" data-link-position="0" data-link-pinned="true" data-link-label="View All National" 			>
				View All National							</a>
				</div>
	


				</section>
					</div>
	</section>

<aside class="ad-unit ad-unit--leader-mr1">
	<div class="ad-unit__content">
		     <div id="acm-ad-tag-leader_mr1-leader_mr1"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1152,0],[[728,90]]],[[0,0],[[300,250]]]],&quot;size&quot;:[300,250]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;leader_mr1&quot;,&quot;fold&quot;:&quot;btf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-leader_mr1-leader_mr1" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     	</div>
</aside>

					<section class="article-list article-list--grid article-list--grid-4" >
			



	<h2		class="article-list__heading"
		data-module-type="california"
	>
					<a
				href="https://www.kron4.com/news/california/"
				class="article-list__heading-link"
								data-link-type="heading-link" data-link-position="0" data-link-pinned="true" data-link-label="California" 			>
		
		California
					</a>
		
			</h2>


<div
	class="article-list__content"
	data-module-type="california"
>
								<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2321454"
			data-context="four_col_media_grid"
			data-index="0"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) 100vw, 540px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/california/4-wolves-in-northern-california-killed-over-livestock-attacks/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="4 wolves in Northern California killed over livestock attacks" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/california/4-wolves-in-northern-california-killed-over-livestock-attacks/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="4 wolves in Northern California killed over livestock attacks" 														>
			
			4 wolves in NorCal killed over livestock attacks
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/california/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="1" data-link-pinned="false" data-link-label="California"   >California</a> / <time datetime="2025-10-24T12:44:05-07:00" >2 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/california/4-wolves-in-northern-california-killed-over-livestock-attacks/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="4 wolves in Northern California killed over livestock attacks" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/04/wolf.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/04/wolf.jpg 800w, https://www.kron4.com/wp-content/uploads/sites/11/2025/04/wolf.jpg?resize=300,187 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/04/wolf.jpg?resize=768,479 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/04/wolf.jpg?resize=50,31 50w"
			sizes="(max-width: 899px) 100vw, 540px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2321194"
			data-context="four_col_media_grid"
			data-index="1"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 360px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/ap-us-news/ap-doj-prepares-to-send-election-monitors-to-california-new-jersey-following-requests-from-state-gops/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="DOJ prepares to send election monitors to California, New Jersey following requests from state GOPs" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/ap-us-news/ap-doj-prepares-to-send-election-monitors-to-california-new-jersey-following-requests-from-state-gops/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="DOJ prepares to send election monitors to California, New Jersey following requests from state GOPs" 														>
			
			DOJ prepares to send election monitors to California,&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/ap-us-news/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="2" data-link-pinned="false" data-link-label="AP U.S. News"   >AP U.S. News</a> / <time datetime="2025-10-24T09:11:06-07:00" >4 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/ap-us-news/ap-doj-prepares-to-send-election-monitors-to-california-new-jersey-following-requests-from-state-gops/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="DOJ prepares to send election monitors to California, New Jersey following requests from state GOPs" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?strip=1"
			alt="FILE - Opponents of California Proposition 50, also known as the Election Rigging Response Act, a California ballot measure that would redraw congressional maps to benefit Democrats, rally in Westminster, Calif., on Wednesday, Sept. 10, 2025. (AP Photo/Damian Dovarganes, File)"
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg 5304w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?resize=1080,720 1080w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?resize=1536,1024 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?resize=2048,1365 2048w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/68fba113b510a9.90990576.jpeg?resize=50,33 50w"
			sizes="(max-width: 899px) 50vw, 360px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2321191"
			data-context="four_col_media_grid"
			data-index="2"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 360px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/national/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race-2/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/national/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race-2/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 														>
			
			Poll: Prop 50 likely to pass, Governor&#8217;s race tightens
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/national/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="3" data-link-pinned="false" data-link-label="National"   >National</a> / <time datetime="2025-10-24T09:27:37-07:00" >3 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/national/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race-2/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/AP25178553500780-e1761316002628.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/AP25178553500780-e1761316002628.jpg 800w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/AP25178553500780-e1761316002628.jpg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/AP25178553500780-e1761316002628.jpg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/AP25178553500780-e1761316002628.jpg?resize=50,33 50w"
			sizes="(max-width: 899px) 50vw, 360px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2320693"
			data-context="four_col_media_grid"
			data-index="3"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 360px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/nationwide-auto-theft-ring-leads-to-bay-area-car-business-ca-ag/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Nationwide auto theft ring leads to Bay Area car business: CA AG" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/nationwide-auto-theft-ring-leads-to-bay-area-car-business-ca-ag/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Nationwide auto theft ring leads to Bay Area car business: CA AG" 														>
			
			Nationwide auto theft ring leads to Bay Area car&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="4" data-link-pinned="false" data-link-label="News"   >News</a> / <time datetime="2025-10-23T15:44:15-07:00" >21 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/nationwide-auto-theft-ring-leads-to-bay-area-car-business-ca-ag/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Nationwide auto theft ring leads to Bay Area car business: CA AG" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?strip=1"
			alt="FILE - California Attorney General Rob Bonta speaks during a news conference in Ceres, Calif., April 16, 2025. (AP Photo/Noah Berger, File)"
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg 5951w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?resize=1080,720 1080w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?resize=1536,1024 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?resize=2048,1365 2048w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/68bae1be3d63d1.79206620.jpeg?resize=50,33 50w"
			sizes="(max-width: 899px) 50vw, 360px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2319054"
			data-context="four_col_media_grid"
			data-index="4"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 360px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/california/newsom-deploys-national-guard-food-banks/"
						data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Newsom to deploy National Guard to assist food banks" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/california/newsom-deploys-national-guard-food-banks/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Newsom to deploy National Guard to assist food banks" 														>
			
			Newsom to deploy National Guard to assist food banks
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/california/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="5" data-link-pinned="false" data-link-label="California"   >California</a> / <time datetime="2025-10-22T09:25:35-07:00" >2 days ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/california/newsom-deploys-national-guard-food-banks/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Newsom to deploy National Guard to assist food banks" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=1536,864 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=1752,986 1752w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/07/anaheim-police-dept-18.png?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 360px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2317673"
			data-context="four_col_media_grid"
			data-index="5"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 360px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/california/search-for-melodee-buzzard-expands-outside-california/"
						data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Search for Melodee Buzzard expands outside California" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/california/search-for-melodee-buzzard-expands-outside-california/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Search for Melodee Buzzard expands outside California" 														>
			
			Search for Melodee Buzzard expands outside California
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/california/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="6" data-link-pinned="false" data-link-label="California"   >California</a> / <time datetime="2025-10-20T19:31:53-07:00" >4 days ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/california/search-for-melodee-buzzard-expands-outside-california/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Search for Melodee Buzzard expands outside California" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg?resize=300,288 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg?resize=768,738 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg?resize=749,720 749w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg?resize=1536,1476 1536w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/Melodee-Buzzard3.jpg?resize=50,48 50w"
			sizes="(max-width: 899px) 50vw, 360px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2317156"
			data-context="four_col_media_grid"
			data-index="6"
			data-collection="article-list6"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="four_col_media_grid"
	data-article-list-id="article-list6"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 360px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/california/wild-black-bear-pays-polite-visit-to-norcal-zoo-bears/"
						data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Wild black bear pays ‘polite’ visit to NorCal zoo bears" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/california/wild-black-bear-pays-polite-visit-to-norcal-zoo-bears/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Wild black bear pays ‘polite’ visit to NorCal zoo bears" 														>
			
			Wild black bear pays ‘polite’ visit to NorCal zoo&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/news/california/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="7" data-link-pinned="false" data-link-label="California"   >California</a> / <time datetime="2025-10-20T13:03:47-07:00" >4 days ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/california/wild-black-bear-pays-polite-visit-to-norcal-zoo-bears/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Wild black bear pays ‘polite’ visit to NorCal zoo bears" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/eureka-sequoia-park-zoo-black-bear-featured.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/eureka-sequoia-park-zoo-black-bear-featured.jpg 964w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/eureka-sequoia-park-zoo-black-bear-featured.jpg?resize=300,200 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/eureka-sequoia-park-zoo-black-bear-featured.jpg?resize=768,512 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/eureka-sequoia-park-zoo-black-bear-featured.jpg?resize=50,33 50w"
			sizes="(max-width: 899px) 50vw, 360px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>




	<div
		class="article-list-infinite"
		data-react-component="ArticleListInfinite"
		data-list-id="article-list6"
		data-context="four_col_media_grid"
		data-h="2"
		data-initial-length="7"
		data-next="https://www.kron4.com/wp-json/lakana/v1/article-curation?provider=category&#038;category=57&#038;link_to%5Bprovider%5D=default&#038;link_to%5Blink%5D&#038;link_to%5Btitle%5D&#038;per_page=7&#038;after=2025-09-24T19%3A46%3A07%2B00%3A00&#038;post_type%5B0%5D=post&#038;post_type%5B1%5D=page&#038;post_type%5B2%5D=feed_post&#038;post_type%5B3%5D=gallery&#038;post_type%5B4%5D=newsletter_post&#038;post_type%5B5%5D=sst-promise&#038;context=view&#038;title_image%5Bimage%5D&#038;page=2"
		data-content-classes="article-list__content"
		data-article-classes="article-list__article article-list__article--is-stacked  article-list__article--is-media-type"
		data-button-text="Load More"
		data-loading-text="Loading..."
		data-error-text="Error loading articles"
		data-show-thumb="true"
		data-module-type="california"
	>
	</div>
			</section>
	
<aside class="ad-unit ad-unit--leader-mr2">
	<div class="ad-unit__content">
		     <div id="acm-ad-tag-leader_mr2-leader_mr2"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1152,0],[[728,90]]],[[0,0],[[300,250]]]],&quot;size&quot;:[300,250]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;leader_mr2&quot;,&quot;fold&quot;:&quot;btf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-leader_mr2-leader_mr2" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     	</div>
</aside>

<section id="ns-video-bin-3" class="widget widget--has-z-index-stacking-reset widget_ns-video-bin" data-component="dropzoneWidget">				<section
					class="article-list article-list-carousel article-list-carousel--dropin video-playlist video-playlist--carousel"
					data-component="videoPlaylist"
					data-context="carousel_dropin--video"
					data-use-ovp= "1"
					data-widget-name="Main Area Middle"
				>
					



	<h2		class="article-list__heading article-list__heading--notched"
		data-module-type="latest-video"
	>
		
		Latest Video
		
			</h2>


<div
	class="article-list__content"
	data-module-type="latest-video"
>
								<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="11172344"
			data-context="carousel_dropin--video"
			data-index="0"
			data-collection="article-list7"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;11172344&quot;,&quot;title&quot;:&quot;Interview with tag team champions #DIY&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/interview-with-tag-team-champions-diy\/11172344\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 160w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 256w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 320w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 640w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 960w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 1280w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 1920w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6\/iupl_lin\/7A9\/76E\/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;1 week ago&quot;,&quot;datetime&quot;:&quot;2025-10-15T17:13:00-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:false,&quot;recommendations&quot;:&quot;true&quot;,&quot;title_visible&quot;:&quot;true&quot;,&quot;video_player&quot;:false},&quot;video_id&quot;:11172344},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:11172344,&quot;autoplay&quot;:false,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p6&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;News&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;cust_params=vid%3D11172344%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D1%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjExMTcyMzQ0LCJpc3MiOiJFWm1yUjRFdjV4WW5NZmRiWTVUUGM3bmFLbXkzMk1LcCIsImV4cCI6MTc2MTMzODY4MH0.4BAesoz1Fa_cCyoXyWf0gCF2YVY4ZfXYaHkUT1tMZVk&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/11172344?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E7ym4dpEEaQ70MCtRZFugXPZkDcaUpZnyJl8%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin--video"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/video/interview-with-tag-team-champions-diy/11172344/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Interview with tag team champions #DIY" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/video/interview-with-tag-team-champions-diy/11172344/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Interview with tag team champions #DIY" 														>
			
			Interview with tag team champions #DIY
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-15T17:13:00-07:00" >1 week ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/video/interview-with-tag-team-champions-diy/11172344/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Interview with tag team champions #DIY" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape landscape"
>
			<img
			src="https://c104216-ucdn.mp.lura.live/expiretime=2082787200/b425beab3a93bc6372458375876e13e0fc7b11aebba1da250a30451bc81305c6/iupl_lin/7A9/76E/7A976E9E6F52A3D0DB48093AC0B05A7D_160x90.jpg"
			alt=""
			srcset=""
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="11159384"
			data-context="carousel_dropin--video"
			data-index="1"
			data-collection="article-list7"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;11159384&quot;,&quot;title&quot;:&quot;WWE\u2019s #DIY joins The Finish to talk San Jose Sharks and who\u2019s tougher \u2014 hockey players or wrestlers&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/wwe%e2%80%99s-diy-joins-the-finish-to-talk-san-jose-sharks-and-who%e2%80%99s-tougher-%e2%80%94-hockey-players-or-wrestlers\/11159384\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 160w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 256w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 320w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 640w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 960w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 1280w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 1920w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/4F7\/565\/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&amp;aktasgn=b63d863caedf69c1a4d98e9bc17f1965 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;2 weeks ago&quot;,&quot;datetime&quot;:&quot;2025-10-10T21:10:00-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:false,&quot;recommendations&quot;:&quot;true&quot;,&quot;title_visible&quot;:&quot;true&quot;,&quot;video_player&quot;:false},&quot;video_id&quot;:11159384},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:11159384,&quot;autoplay&quot;:false,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p7&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;News,Video&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;cust_params=vid%3D11159384%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D1%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjExMTU5Mzg0LCJpc3MiOiJFWm1yUjRFdjV4WW5NZmRiWTVUUGM3bmFLbXkzMk1LcCIsImV4cCI6MTc2MTMzODY4MH0.fsQZhHg-G5M3nvZqvIPkp-6pd2ABgfk-r0t-vCdSqhU&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/11159384?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E7ym4dJoEZQ70MCtSY1%2BnWPJkDcaUpZnyJl8%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin--video"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/video/wwe%e2%80%99s-diy-joins-the-finish-to-talk-san-jose-sharks-and-who%e2%80%99s-tougher-%e2%80%94-hockey-players-or-wrestlers/11159384/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="WWE’s #DIY joins The Finish to talk San Jose Sharks and who’s tougher — hockey players or wrestlers" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/video/wwe%e2%80%99s-diy-joins-the-finish-to-talk-san-jose-sharks-and-who%e2%80%99s-tougher-%e2%80%94-hockey-players-or-wrestlers/11159384/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="WWE’s #DIY joins The Finish to talk San Jose Sharks and who’s tougher — hockey players or wrestlers" 														>
			
			WWE’s #DIY joins The Finish to talk San Jose Sharks&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-10T21:10:00-07:00" >2 weeks ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/video/wwe%e2%80%99s-diy-joins-the-finish-to-talk-san-jose-sharks-and-who%e2%80%99s-tougher-%e2%80%94-hockey-players-or-wrestlers/11159384/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="WWE’s #DIY joins The Finish to talk San Jose Sharks and who’s tougher — hockey players or wrestlers" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape landscape"
>
			<img
			src="https://h104216-dcdn.mp.lura.live/1/938763/pvw_lin/4F7/565/4F75655C804EE0A58537F973B5ABF786_4_160x90.jpg?aktaexp=2082787200&#038;aktasgn=b63d863caedf69c1a4d98e9bc17f1965"
			alt=""
			srcset=""
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="11158612"
			data-context="carousel_dropin--video"
			data-index="2"
			data-collection="article-list7"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;11158612&quot;,&quot;title&quot;:&quot;&#039;The Town is The Town&#039;: West Coast Pro Wrestling talks Oakland debut on The Finish with Kor &amp; Tor&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/the-town-is-the-town-west-coast-pro-wrestling-talks-oakland-debut-on-the-finish-with-kor-tor\/11158612\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 160w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 256w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 320w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 640w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 960w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 1280w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 1920w, https:\/\/h104216-dcdn.mp.lura.live\/1\/938763\/pvw_lin\/CE8\/464\/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&amp;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;2 weeks ago&quot;,&quot;datetime&quot;:&quot;2025-10-10T17:25:00-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:false,&quot;recommendations&quot;:&quot;true&quot;,&quot;title_visible&quot;:&quot;true&quot;,&quot;video_player&quot;:false},&quot;video_id&quot;:11158612},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:11158612,&quot;autoplay&quot;:false,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p8&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;News,Video&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;cust_params=vid%3D11158612%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D1%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjExMTU4NjEyLCJpc3MiOiJFWm1yUjRFdjV4WW5NZmRiWTVUUGM3bmFLbXkzMk1LcCIsImV4cCI6MTc2MTMzODY4MH0.tF5VKWpqZFXOMx5slVGNQLVBKYIVt0CuFoWMe1odWas&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/11158612?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E7ym4dJsBbAj0MCtSZFulVPVkDcaUpZnyJl8%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin--video"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/video/the-town-is-the-town-west-coast-pro-wrestling-talks-oakland-debut-on-the-finish-with-kor-tor/11158612/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="&#039;The Town is The Town&#039;: West Coast Pro Wrestling talks Oakland debut on The Finish with Kor &amp; Tor" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/video/the-town-is-the-town-west-coast-pro-wrestling-talks-oakland-debut-on-the-finish-with-kor-tor/11158612/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="&#039;The Town is The Town&#039;: West Coast Pro Wrestling talks Oakland debut on The Finish with Kor &amp; Tor" 														>
			
			&#8216;The Town is The Town&#8217;: West Coast Pro Wrestling&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-10-10T17:25:00-07:00" >2 weeks ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/video/the-town-is-the-town-west-coast-pro-wrestling-talks-oakland-debut-on-the-finish-with-kor-tor/11158612/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="&#039;The Town is The Town&#039;: West Coast Pro Wrestling talks Oakland debut on The Finish with Kor &amp; Tor" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape landscape"
>
			<img
			src="https://h104216-dcdn.mp.lura.live/1/938763/pvw_lin/CE8/464/CE84649CB7EEE6339BD3AA8C24455234_3_160x90.jpg?aktaexp=2082787200&#038;aktasgn=3016f03ccbfa373dc89ec7ace5f5bff8"
			alt=""
			srcset=""
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="11115185"
			data-context="carousel_dropin--video"
			data-index="3"
			data-collection="article-list7"
			data-anvato-params="{&quot;ns&quot;:{&quot;id&quot;:&quot;11115185&quot;,&quot;title&quot;:&quot;BAGGU says they are now collaborating with BART&quot;,&quot;link&quot;:&quot;https:\/\/www.kron4.com\/video\/baggu-says-they-are-now-collaborating-with-bart\/11115185\/&quot;,&quot;thumbnail&quot;:{&quot;src&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg&quot;,&quot;orientation&quot;:&quot;landscape&quot;,&quot;proportional_sources&quot;:{&quot;16:9&quot;:{&quot;srcset&quot;:&quot;https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 160w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 256w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 320w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 640w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 960w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 1280w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 1920w, https:\/\/c104216-ucdn.mp.lura.live\/expiretime=2082787200\/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764\/iupl_lin\/7BB\/B94\/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg 2560w&quot;}},&quot;sizes&quot;:&quot;(max-width: 899px) 100%, 300px&quot;},&quot;date&quot;:{&quot;time&quot;:&quot;4 weeks ago&quot;,&quot;datetime&quot;:&quot;2025-09-26T17:29:10-07:00&quot;},&quot;lead_media&quot;:true,&quot;livestream&quot;:false,&quot;media_type_icon&quot;:{&quot;name&quot;:&quot;video&quot;,&quot;label&quot;:&quot;Video&quot;},&quot;shortcode_params&quot;:{&quot;no_pr&quot;:false,&quot;expect_preroll&quot;:&quot;true&quot;,&quot;autoplay&quot;:false,&quot;recommendations&quot;:&quot;true&quot;,&quot;title_visible&quot;:&quot;true&quot;,&quot;video_player&quot;:false},&quot;video_id&quot;:11115185},&quot;mcp&quot;:&quot;LIN&quot;,&quot;width&quot;:&quot;100%&quot;,&quot;height&quot;:&quot;100%&quot;,&quot;video&quot;:11115185,&quot;autoplay&quot;:false,&quot;expect_preroll&quot;:true,&quot;pInstance&quot;:&quot;p9&quot;,&quot;plugins&quot;:{&quot;comscore&quot;:{&quot;clientId&quot;:&quot;6036439&quot;,&quot;c3&quot;:&quot;kron4.com&quot;,&quot;version&quot;:&quot;5.2.0&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;c3&quot;:&quot;kron4.com&quot;,&quot;ns_st_st&quot;:&quot;kron&quot;,&quot;ns_st_pu&quot;:&quot;Nexstar&quot;,&quot;ns_st_ge&quot;:&quot;KRON ON,Bay Area,Video,News,Genre,News&quot;,&quot;c4&quot;:&quot;vod&quot;}},&quot;dfp&quot;:{&quot;adTagUrl&quot;:&quot;https:\/\/pubads.g.doubleclick.net\/gampad\/ads?sz=1x1000&amp;iu=\/5678\/mg.kron\/home&amp;pp=VOD&amp;impl=s&amp;gdfp_req=1&amp;env=vp&amp;output=vmap&amp;unviewed_position_start=1&amp;ad_rule=1&amp;description_url=https:\/\/www.kron4.com\/&amp;cust_params=vid%3D11115185%26station%3DKRON%26pers_cid%3Dunknown%26vidcat%3D\/home%26bob_ck%3D[bob_ck_val]%26d_code%3D1%26pagetype%3Dindex%26hlmeta%3D%2F%26aa%3Df&quot;,&quot;isFreewheel&quot;:false},&quot;nielsen&quot;:{&quot;apid&quot;:&quot;P4D4F9915-E46E-4B58-BCA6-DE3D1F253081&quot;,&quot;sfcode&quot;:&quot;dcr&quot;,&quot;type&quot;:&quot;dcr&quot;,&quot;apn&quot;:&quot;Anvato&quot;,&quot;environment&quot;:&quot;production&quot;,&quot;useDerivedMetadata&quot;:true,&quot;mapping&quot;:{&quot;adloadtype&quot;:2,&quot;adModel&quot;:2}},&quot;segmentCustom&quot;:{&quot;script&quot;:&quot;https:\/\/segment.psg.nexstardigital.net\/anvato.js&quot;,&quot;writeKey&quot;:&quot;&quot;,&quot;pluginsLoadingTimeout&quot;:12},&quot;videoAuth&quot;:{&quot;enabled&quot;:false}},&quot;expectPrerollTimeout&quot;:8,&quot;accessKey&quot;:&quot;EZmrR4Ev5xYnMfdbY5TPc7naKmy32MKp&quot;,&quot;token&quot;:&quot;eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ2aWQiOjExMTE1MTg1LCJpc3MiOiJFWm1yUjRFdjV4WW5NZmRiWTVUUGM3bmFLbXkzMk1LcCIsImV4cCI6MTc2MTMzODY4MH0.paCsy-zEHfAe4LhOyGsXQ5AO7BRXoDTjfy4qvJIRGbA&quot;,&quot;nxs&quot;:{&quot;mp4Url&quot;:&quot;https:\/\/tkx.mp.lura.live\/rest\/v2\/mcp\/video\/11115185?anvack=Rawk5AaXamlYMHRoV0UeKfkdB3KQ0dnD&amp;token=%7E7ym4cJYGZQ%2F0MCtVZleqWfdkDcaUpZnyJl8%3D&quot;,&quot;enableFloatingPlayer&quot;:true},&quot;disableMutedAutoplay&quot;:false,&quot;recommendations&quot;:true,&quot;expectPreroll&quot;:true,&quot;titleVisible&quot;:true,&quot;htmlEmbed&quot;:false,&quot;pauseOnClick&quot;:true,&quot;trackTimePeriod&quot;:60,&quot;isPermutiveEnabled&quot;:true,&quot;isMinimizedEnabled&quot;:true,&quot;videoClassification&quot;:[{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Desktop&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile\/Tablet&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Click to play embed&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:1,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;Mobile App&quot;,&quot;placement&quot;:1,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Lead Video&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Hero Unit&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Bin&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Video Center&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2},{&quot;location&quot;:&quot;Livestream Player&quot;,&quot;platform&quot;:&quot;AMP&quot;,&quot;placement&quot;:5,&quot;plcmt&quot;:2,&quot;playbackmethod&quot;:2}],&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin--video"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/video/baggu-says-they-are-now-collaborating-with-bart/11115185/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="BAGGU says they are now collaborating with BART" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/video/baggu-says-they-are-now-collaborating-with-bart/11115185/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="BAGGU says they are now collaborating with BART" 														>
			
			BAGGU says they are now collaborating with BART
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<time datetime="2025-09-26T17:29:10-07:00" >4 weeks ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/video/baggu-says-they-are-now-collaborating-with-bart/11115185/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="BAGGU says they are now collaborating with BART" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape landscape"
>
			<img
			src="https://c104216-ucdn.mp.lura.live/expiretime=2082787200/bbf48d0f77879790ac843d48c0cbcac38f531002640fee72228e01a99a8d4764/iupl_lin/7BB/B94/7BBB9415D007926BAE64B180CBA63CED_160x90.jpg"
			alt=""
			srcset=""
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>

	<div
		class="article-list__read-more"
		data-module-type="latest-video"
	>
					<a href="https://www.kron4.com/video"
								data-link-type="cta-button" data-link-position="0" data-link-pinned="true" data-link-label="More Videos" 			>
				More Videos							</a>
				</div>
	


				</section>
				</section>

<section id="custom_html-16" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"><div id="circularhub_module_14675"></div>
<script src="//api.circularhub.com/14675/2ffbae56b1fe4703/circularhub_module.js"></script></div></div></section><section id="custom_html-423" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"><script defer src="https://www.cwtv.com/images/widgets/cw-station-embed.js"></script>
<div class="cw-station-widget" data-width="900" data-height="600"></div></div></div></section><section id="ns-article-bin-33" class="widget widget--has-z-index-stacking-reset widget_ns-article-bin" data-component="dropzoneWidget">			<section
				class="article-list article-list-carousel article-list-carousel--dropin"
				data-component="articleListCarousel"
				data-context="carousel_dropin"
								data-carousel-duration="0"
			>
				



	<h2		class="article-list__heading article-list__heading--notched"
		data-module-type="bestreviews"
	>
					<a
				href="https://www.kron4.com/reviews/br/"
				class="article-list__heading-link"
								data-link-type="heading-link" data-link-position="0" data-link-pinned="true" data-link-label="BestReviews" 			>
		
		BestReviews
					</a>
		
			</h2>


<div
	class="article-list__content"
	data-module-type="bestreviews"
>
								<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2321419"
			data-context="carousel_dropin"
			data-index="0"
			data-collection="article-list7"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/bed-bath-br/bedding-br/wayfairs-bedding-sale-has-blankets-sheets-and-more-for-up-to-80-off/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Wayfair’s bedding sale has blankets, sheets and more for up to 80% off" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/bed-bath-br/bedding-br/wayfairs-bedding-sale-has-blankets-sheets-and-more-for-up-to-80-off/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Wayfair’s bedding sale has blankets, sheets and more for up to 80% off" 														>
			
			Wayfair’s bedding sale has blankets, sheets and more&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/reviews/br/bed-bath-br/bedding-br/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="1" data-link-pinned="false" data-link-label="Bedding"   >Bedding</a> / <time datetime="2025-10-24T11:51:41-07:00" >54 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/reviews/br/bed-bath-br/bedding-br/wayfairs-bedding-sale-has-blankets-sheets-and-more-for-up-to-80-off/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Wayfair’s bedding sale has blankets, sheets and more for up to 80% off" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg 1500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/wayfair-bedding-sale.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="1551896"
			data-context="carousel_dropin"
			data-index="1"
			data-collection="article-list7"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/walmart-quietly-discounts-huge-brands-in-weekly-flash-deals/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Walmart’s ‘Flash Deals’ are filled with hidden gems this week" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/walmart-quietly-discounts-huge-brands-in-weekly-flash-deals/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Walmart’s ‘Flash Deals’ are filled with hidden gems this week" 														>
			
			Walmart’s ‘Flash Deals’ are filled with hidden gems&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="2" data-link-pinned="false" data-link-label="Holiday"   >Holiday</a> / <time datetime="2025-10-24T11:28:43-07:00" >1 hour ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/walmart-quietly-discounts-huge-brands-in-weekly-flash-deals/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Walmart’s ‘Flash Deals’ are filled with hidden gems this week" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg 1500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-flashdeals-hidden-gems-4.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2321156"
			data-context="carousel_dropin"
			data-index="2"
			data-collection="article-list7"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/electronics-br/laptop-computers-br/acer-swift-go-16-vs-asus-vivobook-16-whats-the-difference/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Acer Swift Go 16 vs. ASUS Vivobook 16: What’s the difference?" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/electronics-br/laptop-computers-br/acer-swift-go-16-vs-asus-vivobook-16-whats-the-difference/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Acer Swift Go 16 vs. ASUS Vivobook 16: What’s the difference?" 														>
			
			Acer Swift Go 16 vs. ASUS Vivobook 16: What’s the&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/reviews/br/electronics-br/laptop-computers-br/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="3" data-link-pinned="false" data-link-label="Laptop Computers"   >Laptop Computers</a> / <time datetime="2025-10-24T06:36:40-07:00" >6 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/reviews/br/electronics-br/laptop-computers-br/acer-swift-go-16-vs-asus-vivobook-16-whats-the-difference/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Acer Swift Go 16 vs. ASUS Vivobook 16: What’s the difference?" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg 1500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature-acer-swift-go-16-vs-asus-vivobook-16.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="2320389"
			data-context="carousel_dropin"
			data-index="3"
			data-collection="article-list7"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/kitchen-br/cookware-br/le-creuset-makes-a-rare-update-to-its-classic-dutch-oven/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Le Creuset makes a rare update to its classic Dutch oven" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/kitchen-br/cookware-br/le-creuset-makes-a-rare-update-to-its-classic-dutch-oven/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Le Creuset makes a rare update to its classic Dutch oven" 														>
			
			Le Creuset makes a rare update to its classic Dutch&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/reviews/br/kitchen-br/cookware-br/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="4" data-link-pinned="false" data-link-label="Cookware"   >Cookware</a> / <time datetime="2025-10-23T13:08:44-07:00" >24 hours ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/reviews/br/kitchen-br/cookware-br/le-creuset-makes-a-rare-update-to-its-classic-dutch-oven/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Le Creuset makes a rare update to its classic Dutch oven" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg 1500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/le-creuset-modern-heritage-new-collection-1.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="1884985"
			data-context="carousel_dropin"
			data-index="4"
			data-collection="article-list7"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/beauty-personal-care-br/storage-br/here-are-amazons-10-most-wished-for-items-in-kitchen-storage-and-organization/"
						data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Here are Amazon’s 10 most-wished-for items in kitchen storage and organization" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/beauty-personal-care-br/storage-br/here-are-amazons-10-most-wished-for-items-in-kitchen-storage-and-organization/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Here are Amazon’s 10 most-wished-for items in kitchen storage and organization" 														>
			
			Here are Amazon’s 10 most-wished-for items in kitchen&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/reviews/br/beauty-personal-care-br/storage-br/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="5" data-link-pinned="false" data-link-label="Storage"   >Storage</a> / <time datetime="2025-10-23T09:28:43-07:00" >1 day ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/reviews/br/beauty-personal-care-br/storage-br/here-are-amazons-10-most-wished-for-items-in-kitchen-storage-and-organization/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Here are Amazon’s 10 most-wished-for items in kitchen storage and organization" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg 1500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/amazon-most-wished-for-kitchen-storage-organization-new.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-stacked article-list__article--has-thumb article-list__article--is-media-type"
			data-article-id="1676158"
			data-context="carousel_dropin"
			data-index="5"
			data-collection="article-list7"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="carousel_dropin"
	data-article-list-id="article-list7"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;9:16&quot;,&quot;(max-width: 899px) 50vw, 300px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/pets-br/toys-br/pet-products-rule-walmarts-flash-deals-this-week/"
						data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Pet products rule Walmart’s Flash Deals this week" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/pets-br/toys-br/pet-products-rule-walmarts-flash-deals-this-week/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Pet products rule Walmart’s Flash Deals this week" 														>
			
			Pet products rule Walmart’s Flash Deals this week
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://www.kron4.com/reviews/br/pets-br/toys-br/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="6" data-link-pinned="false" data-link-label="Toys"   >Toys</a> / <time datetime="2025-10-23T06:48:33-07:00" >1 day ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/reviews/br/pets-br/toys-br/pet-products-rule-walmarts-flash-deals-this-week/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Pet products rule Walmart’s Flash Deals this week" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?strip=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg 1500w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=1280,720 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/walmart-weekly-flash-deals-pets-new-updated.jpg?resize=50,28 50w"
			sizes="(max-width: 899px) 50vw, 300px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>

	<div
		class="article-list__read-more"
		data-module-type="bestreviews"
	>
					<a href="https://www.kron4.com/reviews/br/"
								data-link-type="cta-button" data-link-position="0" data-link-pinned="true" data-link-label="More reviews" 			>
				More reviews							</a>
				</div>
	


			</section>
			</section><section id="ns-thehill-trending-2" class="widget widget--has-z-index-stacking-reset widget_ns-thehill-trending" data-component="dropzoneWidget" data-link-category="Trending on The Hill" data-module-type="trending-on-the-hill">		<section class="article-list article-list--headline-image two-columns">
			



	<h2		class="article-list__heading"
		data-module-type="latest-stories-from-the-hill"
	>
					<a
				href="https://thehill.com"
				class="article-list__heading-link"
				target="_blank"				data-link-type="heading-link" data-link-position="0" data-link-pinned="true" data-link-label="Latest stories from The Hill" 			>
		
		Latest stories from The Hill
					</a>
		
					
<span class="branded-logo">
			<a href="https://thehill.com" target="_blank">
	
	<img
		class="branded-logo__image"
		src="https://www.kron4.com/wp-content/themes/nexstar/client/src/components/article-list/logo_thehill_horizontal.svg"
		srcset="https://www.kron4.com/wp-content/themes/nexstar/client/src/components/article-list/logo_thehill_horizontal.svg?w=175 1x, https://www.kron4.com/wp-content/themes/nexstar/client/src/components/article-list/logo_thehill_horizontal.svg?w=350 2x, https://www.kron4.com/wp-content/themes/nexstar/client/src/components/article-list/logo_thehill_horizontal.svg?w=525 3x"
	>

			</a>
	</span>
			</h2>


<div
	class="article-list__content"
	data-module-type="latest-stories-from-the-hill"
>
								<article
			class="article-list__article"
			data-article-id="5572199"
			data-context="headline_list_two_col_image_the_hill"
			data-index="1"
			data-collection="article-list8"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="headline_list_two_col_image_the_hill"
	data-article-list-id="article-list8"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://thehill.com/homenews/5572199-senior-advocacy-group-wants-to-establish-a-minimum-annual-cola-increase-how-would-it-work/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Senior advocacy group wants to establish a ‘minimum’ annual COLA increase: How would it work?" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://thehill.com/homenews/5572199-senior-advocacy-group-wants-to-establish-a-minimum-annual-cola-increase-how-would-it-work/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Senior advocacy group wants to establish a ‘minimum’ annual COLA increase: How would it work?" 														>
			
			Senior advocacy group wants to establish a ‘minimum’&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://thehill.com/homenews/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="2" data-link-pinned="false" data-link-label="News"   >News</a> | <time datetime="2025-10-24T15:30:28-04:00" >8 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://thehill.com/homenews/5572199-senior-advocacy-group-wants-to-establish-a-minimum-annual-cola-increase-how-would-it-work/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Senior advocacy group wants to establish a ‘minimum’ annual COLA increase: How would it work?" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square-true-ratio square"
>
			<img
			src="https://thehill.com/wp-content/uploads/sites/2/2023/12/GettyImages-1310131960-4.jpg?w=600&#038;h=483&#038;crop=1"
			alt="ssa cola"
			srcset="https://thehill.com/wp-content/uploads/sites/2/2023/12/GettyImages-1310131960-4.jpg?w=100&amp;h=100&amp;crop=1 100w, https://thehill.com/wp-content/uploads/sites/2/2023/12/GettyImages-1310131960-4.jpg?w=200&amp;h=200&amp;crop=1 200w, https://thehill.com/wp-content/uploads/sites/2/2023/12/GettyImages-1310131960-4.jpg?w=300&amp;h=300&amp;crop=1 300w, https://thehill.com/wp-content/uploads/sites/2/2023/12/GettyImages-1310131960-4.jpg?w=600&amp;h=483&amp;crop=1 600w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="5572245"
			data-context="headline_list_two_col_image_the_hill"
			data-index="2"
			data-collection="article-list8"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="headline_list_two_col_image_the_hill"
	data-article-list-id="article-list8"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://thehill.com/homenews/administration/5572245-white-house-ballroom-controversy/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="White House sideswiped by ballroom demolition controversy" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://thehill.com/homenews/administration/5572245-white-house-ballroom-controversy/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="White House sideswiped by ballroom demolition controversy" 														>
			
			White House sideswiped by ballroom demolition controversy
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://thehill.com/homenews/administration/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="3" data-link-pinned="false" data-link-label="Administration"   >Administration</a> | <time datetime="2025-10-24T15:27:06-04:00" >11 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://thehill.com/homenews/administration/5572245-white-house-ballroom-controversy/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="White House sideswiped by ballroom demolition controversy" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square-true-ratio square"
>
			<img
			src="https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25296597418177.jpg?w=600&#038;h=600&#038;crop=1"
			alt=""
			srcset="https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25296597418177.jpg?w=100&amp;h=100&amp;crop=1 100w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25296597418177.jpg?w=200&amp;h=200&amp;crop=1 200w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25296597418177.jpg?w=300&amp;h=300&amp;crop=1 300w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25296597418177.jpg?w=600&amp;h=600&amp;crop=1 600w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="5572068"
			data-context="headline_list_two_col_image_the_hill"
			data-index="3"
			data-collection="article-list8"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="headline_list_two_col_image_the_hill"
	data-article-list-id="article-list8"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://thehill.com/homenews/state-watch/5572068-doj-sends-election-monitors/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="DOJ sending election monitors to California, New Jersey voting sites" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://thehill.com/homenews/state-watch/5572068-doj-sends-election-monitors/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="DOJ sending election monitors to California, New Jersey voting sites" 														>
			
			DOJ sending election monitors to California, New&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://thehill.com/homenews/state-watch/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="4" data-link-pinned="false" data-link-label="State Watch"   >State Watch</a> | <time datetime="2025-10-24T15:21:38-04:00" >17 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://thehill.com/homenews/state-watch/5572068-doj-sends-election-monitors/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="DOJ sending election monitors to California, New Jersey voting sites" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square-true-ratio square"
>
			<img
			src="https://thehill.com/wp-content/uploads/sites/2/2024/03/AP24065603656176-e1709675681194.jpg?w=600&#038;h=600&#038;crop=1"
			alt=""
			srcset="https://thehill.com/wp-content/uploads/sites/2/2024/03/AP24065603656176-e1709675681194.jpg?w=100&amp;h=100&amp;crop=1 100w, https://thehill.com/wp-content/uploads/sites/2/2024/03/AP24065603656176-e1709675681194.jpg?w=200&amp;h=200&amp;crop=1 200w, https://thehill.com/wp-content/uploads/sites/2/2024/03/AP24065603656176-e1709675681194.jpg?w=300&amp;h=300&amp;crop=1 300w, https://thehill.com/wp-content/uploads/sites/2/2024/03/AP24065603656176-e1709675681194.jpg?w=600&amp;h=600&amp;crop=1 600w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="5570355"
			data-context="headline_list_two_col_image_the_hill"
			data-index="4"
			data-collection="article-list8"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="headline_list_two_col_image_the_hill"
	data-article-list-id="article-list8"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://thehill.com/homenews/administration/5570355-live-updates-trump-asia-government-shutdown-trade/"
						data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Live updates: Trump to head to Asia amid shutdown; James pleads not guilty in fraud probe" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://thehill.com/homenews/administration/5570355-live-updates-trump-asia-government-shutdown-trade/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Live updates: Trump to head to Asia amid shutdown; James pleads not guilty in fraud probe" 														>
			
			Live updates: Trump to head to Asia amid shutdown;&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://thehill.com/homenews/administration/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="5" data-link-pinned="false" data-link-label="Administration"   >Administration</a> | <time datetime="2025-10-24T15:15:50-04:00" >23 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://thehill.com/homenews/administration/5570355-live-updates-trump-asia-government-shutdown-trade/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Live updates: Trump to head to Asia amid shutdown; James pleads not guilty in fraud probe" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square-true-ratio square"
>
			<img
			src="https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295785880456-e1761328564874.jpg?w=600&#038;h=600&#038;crop=1"
			alt=""
			srcset="https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295785880456-e1761328564874.jpg?w=100&amp;h=100&amp;crop=1 100w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295785880456-e1761328564874.jpg?w=200&amp;h=200&amp;crop=1 200w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295785880456-e1761328564874.jpg?w=300&amp;h=300&amp;crop=1 300w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295785880456-e1761328564874.jpg?w=600&amp;h=600&amp;crop=1 600w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="5572083"
			data-context="headline_list_two_col_image_the_hill"
			data-index="5"
			data-collection="article-list8"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="headline_list_two_col_image_the_hill"
	data-article-list-id="article-list8"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://thehill.com/homenews/campaign/5572083-maine-senate-candidate-dropout-graham-platner-comments/"
						data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Maine Senate candidate drops out, citing Platner’s post on military rape" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://thehill.com/homenews/campaign/5572083-maine-senate-candidate-dropout-graham-platner-comments/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Maine Senate candidate drops out, citing Platner’s post on military rape" 														>
			
			Maine Senate candidate drops out, citing Platner’s&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://thehill.com/homenews/campaign/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="6" data-link-pinned="false" data-link-label="Campaign"   >Campaign</a> | <time datetime="2025-10-24T15:11:12-04:00" >27 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://thehill.com/homenews/campaign/5572083-maine-senate-candidate-dropout-graham-platner-comments/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Maine Senate candidate drops out, citing Platner’s post on military rape" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square-true-ratio square"
>
			<img
			src="https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295844730965-e1761332184726.jpg?w=600&#038;h=600&#038;crop=1"
			alt=""
			srcset="https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295844730965-e1761332184726.jpg?w=100&amp;h=100&amp;crop=1 100w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295844730965-e1761332184726.jpg?w=200&amp;h=200&amp;crop=1 200w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295844730965-e1761332184726.jpg?w=300&amp;h=300&amp;crop=1 300w, https://thehill.com/wp-content/uploads/sites/2/2025/10/AP25295844730965-e1761332184726.jpg?w=600&amp;h=600&amp;crop=1 600w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article"
			data-article-id="5572122"
			data-context="headline_list_two_col_image_the_hill"
			data-index="6"
			data-collection="article-list8"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="headline_list_two_col_image_the_hill"
	data-article-list-id="article-list8"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;1:1&quot;,&quot;(max-width: 899px) 15vw, 160px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://thehill.com/homenews/campaign/5572122-rand-paul-backs-thomas-massie/"
						data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Paul vows to support Massie against Trump-backed primary challenger" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://thehill.com/homenews/campaign/5572122-rand-paul-backs-thomas-massie/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Paul vows to support Massie against Trump-backed primary challenger" 														>
			
			Paul vows to support Massie against Trump-backed&nbsp;&hellip;
										</a>
					</h3>
	
						<footer class="article-list__article-meta">
				<a href="https://thehill.com/homenews/campaign/" class="article-list__article-category-link" data-link-type="category-link" data-link-position="7" data-link-pinned="false" data-link-label="Campaign"   >Campaign</a> | <time datetime="2025-10-24T15:09:48-04:00" >29 minutes ago</time>			</footer>
			
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://thehill.com/homenews/campaign/5572122-rand-paul-backs-thomas-massie/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Paul vows to support Massie against Trump-backed primary challenger" 											>
		
		<div class="article-list__article-image-wrapper">
			
<div

	class="image-wrapper square-true-ratio square"
>
			<img
			src="https://thehill.com/wp-content/uploads/sites/2/2025/07/paulrand_073125gn01_w.jpg?w=600&#038;h=600&#038;crop=1"
			alt="Sen. Rand Paul (R-Ky.)"
			srcset="https://thehill.com/wp-content/uploads/sites/2/2025/07/paulrand_073125gn01_w.jpg?w=100&amp;h=100&amp;crop=1 100w, https://thehill.com/wp-content/uploads/sites/2/2025/07/paulrand_073125gn01_w.jpg?w=200&amp;h=200&amp;crop=1 200w, https://thehill.com/wp-content/uploads/sites/2/2025/07/paulrand_073125gn01_w.jpg?w=300&amp;h=300&amp;crop=1 300w, https://thehill.com/wp-content/uploads/sites/2/2025/07/paulrand_073125gn01_w.jpg?w=600&amp;h=600&amp;crop=1 600w"
			sizes="(max-width: 899px) 15vw, 160px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>

<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

				


</div>

	<div
		class="article-list__read-more"
		data-module-type="latest-stories-from-the-hill"
	>
					<a href="https://thehill.com/news"
				target="_blank"				data-link-type="cta-button" data-link-position="0" data-link-pinned="true" data-link-label="More from The Hill" 			>
				More from The Hill							</a>
				</div>
	


		</section>
		</section><section id="partner-article-bin-widget widget--has-z-index-stacking-reset-3" class="widget widget--has-z-index-stacking-reset widget_partner-article-bin-widget widget--has-z-index-stacking-reset" data-component="dropzoneWidget">
		<section
			class="article-list article-list--headline-three-featured-image-col"
			data-component=""
			data-context="headline-three-featured-image-col"
		>

							
			<div class="article-list__content">
							<section class="article-list article-list--headline-list-inner ">
				

			<a
			href="https://www.kron4.com/reviews/br/home-br/vacuums-br/sharks-bestselling-robot-vacuum-is-54-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
			class="article-list__article-link article-list--headline-list-inner "
			data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Shark’s bestselling robot vacuum is 54% off on Amazon right now" 		>
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=1500&#038;h=844&#038;crop=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=160&amp;h=90&amp;crop=1 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=256&amp;h=144&amp;crop=1 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=320&amp;h=180&amp;crop=1 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=512&amp;h=288&amp;crop=1 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=640&amp;h=360&amp;crop=1 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=876&amp;h=493&amp;crop=1 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=960&amp;h=540&amp;crop=1 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=1280&amp;h=720&amp;crop=1 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=1500&amp;h=844&amp;crop=1 1752w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=1500&amp;h=844&amp;crop=1 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/09/feature_shark-robot-vacuum-deals.jpg?w=1500&amp;h=844&amp;crop=1 2560w"
			sizes="(max-width: 899px) calc(100vw - 2.5rem), 236px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
			</a>
	

	<h2		class="article-list__heading article-list--headline-list-inner "
		data-module-type="trending-now"
	>
		
		Trending now
		
			</h2>


<div
	class="article-list__content article-list--headline-list-inner "
	data-module-type="trending-now"
>
								<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="2295132"
			data-context="headline_list_inner"
			data-index="0"
			data-collection="article-list9"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list9"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/home-br/vacuums-br/sharks-bestselling-robot-vacuum-is-54-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Shark’s bestselling robot vacuum is 54% off on Amazon right now" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/home-br/vacuums-br/sharks-bestselling-robot-vacuum-is-54-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Shark’s bestselling robot vacuum is 54% off on Amazon right now" 														>
			
			Shark’s bestselling robot vacuum is 54% off on Amazon&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="2090118"
			data-context="headline_list_inner"
			data-index="1"
			data-collection="article-list9"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list9"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/fashion-accessories-br/handbags-wallets-br/vera-bradley-bags-are-up-to-67-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Vera Bradley bags are up to 55% off on Amazon right now" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/fashion-accessories-br/handbags-wallets-br/vera-bradley-bags-are-up-to-67-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Vera Bradley bags are up to 55% off on Amazon right now" 														>
			
			Vera Bradley bags are up to 55% off on Amazon right&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="2298378"
			data-context="headline_list_inner"
			data-index="2"
			data-collection="article-list9"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list9"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/home-br/candles-br/yankee-candles-fall-cult-favorites-are-40-off-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Yankee Candle’s fall cult-favorites are 40% off right now" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/home-br/candles-br/yankee-candles-fall-cult-favorites-are-40-off-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Yankee Candle’s fall cult-favorites are 40% off right now" 														>
			
			Yankee Candle’s fall cult-favorites are 40% off right&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="2295218"
			data-context="headline_list_inner"
			data-index="3"
			data-collection="article-list9"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list9"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/the-coveted-halloween-squishmallows-are-here/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="The coveted Halloween Squishmallows are here" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/the-coveted-halloween-squishmallows-are-here/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="The coveted Halloween Squishmallows are here" 														>
			
			The coveted Halloween Squishmallows are here
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

				


</div>




				</section>
							<section class="article-list article-list--headline-list-inner ">
				

			<a
			href="https://www.kron4.com/reviews/br/home-br/home-improvement-br/amazon-has-tiny-homes-for-sale-and-theyre-more-luxurious-than-you-think/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
			class="article-list__article-link article-list--headline-list-inner "
			data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Amazon has tiny homes for sale, and they’re more luxurious than you think" 		>
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=1500&#038;h=844&#038;crop=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=160&amp;h=90&amp;crop=1 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=256&amp;h=144&amp;crop=1 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=320&amp;h=180&amp;crop=1 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=512&amp;h=288&amp;crop=1 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=640&amp;h=360&amp;crop=1 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=876&amp;h=493&amp;crop=1 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=960&amp;h=540&amp;crop=1 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=1280&amp;h=720&amp;crop=1 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=1500&amp;h=844&amp;crop=1 1752w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=1500&amp;h=844&amp;crop=1 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/feature_amazon-tiny-home-deals-2.jpg?w=1500&amp;h=844&amp;crop=1 2560w"
			sizes="(max-width: 899px) calc(100vw - 2.5rem), 236px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
			</a>
	

	<h2		class="article-list__heading article-list--headline-list-inner "
		data-module-type="best-deals-this-week"
	>
		
		Best deals this week
		
			</h2>


<div
	class="article-list__content article-list--headline-list-inner "
	data-module-type="best-deals-this-week"
>
								<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="2304115"
			data-context="headline_list_inner"
			data-index="0"
			data-collection="article-list10"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list10"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/home-br/home-improvement-br/amazon-has-tiny-homes-for-sale-and-theyre-more-luxurious-than-you-think/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Amazon has tiny homes for sale, and they’re more luxurious than you think" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/home-br/home-improvement-br/amazon-has-tiny-homes-for-sale-and-theyre-more-luxurious-than-you-think/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Amazon has tiny homes for sale, and they’re more luxurious than you think" 														>
			
			Amazon has tiny homes for sale, and they’re more&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="1702599"
			data-context="headline_list_inner"
			data-index="1"
			data-collection="article-list10"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list10"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/new-le-creuset-stanley-and-more-top-amazons-hot-new-releases-this-week/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="LEGO, Apple and more top Amazon’s ‘hot’ new releases this week" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/new-le-creuset-stanley-and-more-top-amazons-hot-new-releases-this-week/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="LEGO, Apple and more top Amazon’s ‘hot’ new releases this week" 														>
			
			LEGO, Apple and more top Amazon’s ‘hot’ new releases&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="2299588"
			data-context="headline_list_inner"
			data-index="2"
			data-collection="article-list10"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list10"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/home-br/vacuums-br/sharks-bestselling-cordless-vacuum-is-50-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Shark’s bestselling cordless vacuum is 50% off on Amazon right now" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/home-br/vacuums-br/sharks-bestselling-cordless-vacuum-is-50-off-on-amazon-right-now/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Shark’s bestselling cordless vacuum is 50% off on Amazon right now" 														>
			
			Shark’s bestselling cordless vacuum is 50% off on&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="1544137"
			data-context="headline_list_inner"
			data-index="3"
			data-collection="article-list10"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list10"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/automotive-br/jump-starters-batteries-chargers-br/10-bestselling-jump-starters-worth-considering-as-winter-approaches/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Bestselling jump starters to consider during winter" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/automotive-br/jump-starters-batteries-chargers-br/10-bestselling-jump-starters-worth-considering-as-winter-approaches/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Bestselling jump starters to consider during winter" 														>
			
			Bestselling jump starters to consider during winter
										</a>
					</h3>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

				


</div>




				</section>
							<section class="article-list article-list--headline-list-inner ">
				

			<a
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/vintage-ceramic-halloween-trees-are-all-the-rage-this-season/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
			class="article-list__article-link article-list--headline-list-inner "
			data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Vintage ceramic Halloween trees are all the rage this season" 		>
			
<div

	class="image-wrapper landscape"
>
			<img
			src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=1500&#038;h=844&#038;crop=1"
			alt=""
			srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=160&amp;h=90&amp;crop=1 160w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=256&amp;h=144&amp;crop=1 256w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=320&amp;h=180&amp;crop=1 320w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=512&amp;h=288&amp;crop=1 512w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=640&amp;h=360&amp;crop=1 640w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=876&amp;h=493&amp;crop=1 876w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=960&amp;h=540&amp;crop=1 960w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=1280&amp;h=720&amp;crop=1 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=1500&amp;h=844&amp;crop=1 1752w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=1500&amp;h=844&amp;crop=1 1920w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/vintage-ceramic-halloween-trees-new-2025.jpg?w=1500&amp;h=844&amp;crop=1 2560w"
			sizes="(max-width: 899px) calc(100vw - 2.5rem), 236px"
			loading="lazy"
			onerror="this.onerror=null; this.src=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png&#039;; this.srcset=&#039;https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=160 160w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=256 256w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=320 320w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=640 640w, https://www.kron4.com/wp-content/themes/nexstar-wv/client/src/images/placeholder-1-1.png?w=876 876w&#039;; this.sizes=&#039;(max-width: 899px) 100vw, 876px&#039;;"
					/>
	</div>
			</a>
	



<div
	class="article-list__content article-list--headline-list-inner "
	data-module-type="no-title"
>
								<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="1542504"
			data-context="headline_list_inner"
			data-index="0"
			data-collection="article-list11"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list11"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/vintage-ceramic-halloween-trees-are-all-the-rage-this-season/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Vintage ceramic Halloween trees are all the rage this season" 			>
		</a>

		<h2 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/vintage-ceramic-halloween-trees-are-all-the-rage-this-season/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Vintage ceramic Halloween trees are all the rage this season" 														>
			
			Vintage ceramic Halloween trees are all the rage&nbsp;&hellip;
										</a>
					</h2>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="1448509"
			data-context="headline_list_inner"
			data-index="1"
			data-collection="article-list11"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list11"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/best-early-prime-day-deals-for-100-or-less/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="The best under-$100 deals still live after October Prime Day" 			>
		</a>

		<h2 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/best-early-prime-day-deals-for-100-or-less/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="The best under-$100 deals still live after October Prime Day" 														>
			
			The best under-$100 deals still live after October&nbsp;&hellip;
										</a>
					</h2>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="1448435"
			data-context="headline_list_inner"
			data-index="2"
			data-collection="article-list11"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list11"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/big-ticket-items-to-score-now-before-prime-day-2023/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="October Prime Day is over, but these big-ticket items are still discounted" 			>
		</a>

		<h2 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/apparel-br/holiday-br/big-ticket-items-to-score-now-before-prime-day-2023/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="October Prime Day is over, but these big-ticket items are still discounted" 														>
			
			October Prime Day is over, but these big-ticket items&nbsp;&hellip;
										</a>
					</h2>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

											<article
			class="article-list__article article-list--headline-list-inner "
			data-article-id="1659007"
			data-context="headline_list_inner"
			data-index="3"
			data-collection="article-list11"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text article-list--headline-list-inner "
	data-context="headline_list_inner"
	data-article-list-id="article-list11"
	data-article-text-classes="article-list__article-text article-list--headline-list-inner "
	data-article-thumb-classes="article-list__article-thumb article-list--headline-list-inner "
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 899px) calc(100vw - 2.5rem), 236px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/reviews/br/toys-games-br/stuffed-animals-br/the-sure-to-sell-out-harry-potter-squishmallows-are-finally-available-on-amazon/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="‘Harry Potter’ Squishmallows are here — and there’s a Dobby" 			>
		</a>

		<h2 class="article-list__article-title">
													<a
					href="https://www.kron4.com/reviews/br/toys-games-br/stuffed-animals-br/the-sure-to-sell-out-harry-potter-squishmallows-are-finally-available-on-amazon/?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
					class="article-list__article-link article-list--headline-list-inner "
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="‘Harry Potter’ Squishmallows are here — and there’s a Dobby" 														>
			
			‘Harry Potter’ Squishmallows are here — and there’s&nbsp;&hellip;
										</a>
					</h2>
	
				
	
	
	
			
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--default"
>
	<span class="article-list__article-mediaicon-svg">
		<svg xmlns="https://www.w3.org/2000/svg" width="11" height="11" viewBox="0 0 12 12"><defs><style>.cls-4{fill:#000;}</style></defs><circle id="default__bullet__button" data-name="default" class="cls-4" cx="5.5" cy="5.5" r="5.5"/></svg>
	</span>
	</span>
	</div>


							</article>

		

				


</div>




				</section>
						</div>

							<div
					class="article-list__read-more article-list--headline-list-inner "
					data-module-type="view-all-deals"
				>
					<a href="https://bestreviews.com?utm_campaign=bestreviews_homepage&#038;utm_source=www.kron4.com&#038;utm_medium=referral"
												data-link-type="cta-button" data-link-position="0" data-link-pinned="true" data-link-label="https://bestreviews.com" 					>
					View All Deals					</a>
				</div>
					</section>

		</section>
			</main>
		</div>

		
<section id="secondary" class="widget-area">

					<!-- Ad Unit Square mr_combo1 -->
		<aside class="ad-unit ad-unit--square">
			<div class="ad-unit__content">
				     <div id="acm-ad-tag-mr_combo1-mr_combo1"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1280,0],[[300,600],[300,250]]],[[1024,0],[[300,600],[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],&quot;size&quot;:[300,250]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;mr_combo1&quot;,&quot;fold&quot;:&quot;atf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-mr_combo1-mr_combo1" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     			</div>
		</aside>
		<!-- END Ad Unit Square mr_combo1 -->
				<section id="text-13" class="widget widget--has-z-index-stacking-reset widget_text" data-component="dropzoneWidget">			<div class="textwidget"><div class="rich-text-cascade"><div class="weather-radar"><div style="width:100%; height:480px;"><wx-widget  type="map" memberid="1172" mapid="0061" latitude="37.78" longitude="-122.42" group="true" layers="satrad" fullscreen="true" theme="dark-gray" opacity=".6" zoomlevel="9"></wx-widget></div></div>
</div></div>
		</section><section id="ns-article-bin-18" class="widget widget--has-z-index-stacking-reset widget_ns-article-bin" data-component="dropzoneWidget">			<section
				class="article-list article-list--trending"
				data-component=""
				data-context="numbered_list"
								data-carousel-duration="0"
			>
				



	<h2		class="article-list__heading article-list__heading--bottom-divider"
		data-module-type="trending-stories"
	>
		
		Trending Stories
		
			</h2>


<div
	class="article-list__content"
	data-module-type="trending-stories"
>
								<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2321457"
			data-context="numbered_list"
			data-index="0"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
						data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 														>
			
			Border Patrol operations canceled for Bay Area, Oakland&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area-ice-raids/border-patrol-operations-canceled-for-bay-area-oakland-mayor-says/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="1" data-link-pinned="false" data-link-label="Border Patrol operations canceled for Bay Area, Oakland mayor says" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2321093"
			data-context="numbered_list"
			data-index="1"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/coast-guard-shoots-at-driver-who-tried-to-ram-alameda-base-gate/"
						data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Coast Guard shoots driver trying to ram Alameda base gate" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/coast-guard-shoots-at-driver-who-tried-to-ram-alameda-base-gate/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Coast Guard shoots driver trying to ram Alameda base gate" 														>
			
			Coast Guard shoots driver trying to ram Alameda gate
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/coast-guard-shoots-at-driver-who-tried-to-ram-alameda-base-gate/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="2" data-link-pinned="false" data-link-label="Coast Guard shoots driver trying to ram Alameda base gate" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2321112"
			data-context="numbered_list"
			data-index="2"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/politics/inside-california-politics/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race/"
						data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/politics/inside-california-politics/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 														>
			
			Poll: Prop 50 likely to pass, Governor&#8217;s race tightens
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/politics/inside-california-politics/poll-californias-prop-50-likely-to-pass-republican-surges-in-governors-race/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="3" data-link-pinned="false" data-link-label="Poll: California’s Prop 50 likely to pass, Republican surges in governor’s race" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="1442283"
			data-context="numbered_list"
			data-index="3"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/watch-kron4-news-online/"
						data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Watch KRON4 News Online" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/watch-kron4-news-online/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Watch KRON4 News Online" 														>
			
			Watch KRON4 News Online
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/watch-kron4-news-online/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="4" data-link-pinned="false" data-link-label="Watch KRON4 News Online" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2319763"
			data-context="numbered_list"
			data-index="4"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/charges-filed-against-teen-driver-in-marin-county-crash-that-killed-four/"
						data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Charges filed against teen driver in Marin County crash that killed four" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/charges-filed-against-teen-driver-in-marin-county-crash-that-killed-four/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Charges filed against teen driver in Marin County crash that killed four" 														>
			
			Charges filed against teen in deadly Marin County&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/charges-filed-against-teen-driver-in-marin-county-crash-that-killed-four/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="5" data-link-pinned="false" data-link-label="Charges filed against teen driver in Marin County crash that killed four" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2320054"
			data-context="numbered_list"
			data-index="5"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area-ice-raids/live-updates-federal-agents-arriving-in-bay-area/"
						data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Protests, fears continue in Bay Area after Trump pauses SF surge" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area-ice-raids/live-updates-federal-agents-arriving-in-bay-area/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Protests, fears continue in Bay Area after Trump pauses SF surge" 														>
			
			Protests continue after Trump pauses surge
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area-ice-raids/live-updates-federal-agents-arriving-in-bay-area/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="6" data-link-pinned="false" data-link-label="Protests, fears continue in Bay Area after Trump pauses SF surge" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2321290"
			data-context="numbered_list"
			data-index="6"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/mountain-view-barber-accused-in-dozens-of-sex-crimes-captured-in-guatemala/"
						data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Mountain View barber accused in dozens of sex crimes captured in Guatemala" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/mountain-view-barber-accused-in-dozens-of-sex-crimes-captured-in-guatemala/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Mountain View barber accused in dozens of sex crimes captured in Guatemala" 														>
			
			Barber accused in dozens of sex crimes found in Guatemala
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/mountain-view-barber-accused-in-dozens-of-sex-crimes-captured-in-guatemala/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="7" data-link-pinned="false" data-link-label="Mountain View barber accused in dozens of sex crimes captured in Guatemala" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2321298"
			data-context="numbered_list"
			data-index="7"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
						data-link-type="content-link" data-link-position="8" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="8" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 														>
			
			Here&#8217;s when rain could return to the Bay Area
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/weather/moderate-to-heavy-rain-possible-in-parts-of-bay-area-this-weekend/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="8" data-link-pinned="false" data-link-label="Moderate to heavy rain possible in parts of Bay Area this weekend" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
				
<span
	aria-hidden="true"
	tabindex="-1"
	class="article-list__article-mediaicon article-list__article-mediaicon--video"
>
	<span class="article-list__article-mediaicon-svg">
		<svg width="15" height="16" viewBox="0 0 15 16" xmlns="http://www.w3.org/2000/svg"><defs><style>.cls-3{fill:#fff;fill-rule:evenodd}</style></defs><path d="M0 13.6457V2.35094C0 0.99199 1.41453 0.0955065 2.64344 0.675612L13.9382 6.00731C15.3192 6.65918 15.3627 8.60798 14.0123 9.32093L2.71754 15.284C1.48379 15.9354 0 15.0409 0 13.6457Z" class="cls-3"/></svg>
	</span>
	</span>
		</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2321349"
			data-context="numbered_list"
			data-index="8"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
						data-link-type="content-link" data-link-position="9" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="9" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 														>
			
			Palto Alto PD looking for man who exposed himself&nbsp;&hellip;
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/police-in-palo-alto-looking-for-man-who-allegedly-exposed-himself-to-high-school-girl/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="9" data-link-pinned="false" data-link-label="Police in Palo Alto looking for man who allegedly exposed himself to high school girl" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
							</article>

		

											<article
			class="article-list__article article-list__article--is-slat"
			data-article-id="2320627"
			data-context="numbered_list"
			data-index="9"
			data-collection="article-list12"
			data-anvato-params="{&quot;pauseOnTabInactive&quot;:false}"
						>
			<!-- Next line is not the perfect/ideal way to control hiding the items. Can revisit later. -->
				

<div
	class="article-list__article-text"
	data-context="numbered_list"
	data-article-list-id="article-list12"
	data-article-text-classes="article-list__article-text"
	data-article-thumb-classes="article-list__article-thumb"
	data-current-image-context="[&quot;16:9&quot;,&quot;(max-width: 1023px) 50vw, 876px&quot;]"
>
					
		
				<a
			class="article-list__gradient-link"
			href="https://www.kron4.com/news/bay-area/fairfield-high-student-assaulted-suspect-arrested-for-hate-crime/"
						data-link-type="content-link" data-link-position="10" data-link-pinned="false" data-link-label="Fairfield High student assaulted, suspect arrested for hate crime" 			>
		</a>

		<h3 class="article-list__article-title">
													<a
					href="https://www.kron4.com/news/bay-area/fairfield-high-student-assaulted-suspect-arrested-for-hate-crime/"
					class="article-list__article-link"
															data-link-type="content-link" data-link-position="10" data-link-pinned="false" data-link-label="Fairfield High student assaulted, suspect arrested for hate crime" 														>
			
			Fairfield High student assaulted, suspect arrested
										</a>
					</h3>
	
				
	
	
	
	</div>


	<figure class="article-list__article-thumb">
					<a
				href="https://www.kron4.com/news/bay-area/fairfield-high-student-assaulted-suspect-arrested-for-hate-crime/"
				class="article-list__article-link"
				data-link-type="content-link" data-link-position="10" data-link-pinned="false" data-link-label="Fairfield High student assaulted, suspect arrested for hate crime" 											>
		
		<div class="article-list__article-image-wrapper">
							<div class="image-wrapper no-image"></div>
						</div>

					</a>
			</figure>
							</article>

		

				


</div>




			</section>
			</section><section id="text-2" class="widget widget--has-z-index-stacking-reset widget_text" data-component="dropzoneWidget">			<div class="textwidget"><div class="rich-text-cascade"><p><img loading="lazy" decoding="async" class="alignnone size-medium wp-image-832108" src="https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?w=300" alt="" width="300" height="169" srcset="https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg 1280w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=160,90 160w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=300,169 300w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=768,432 768w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=320,180 320w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=256,144 256w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=512,288 512w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=640,360 640w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=876,493 876w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=960,540 960w, https://www.kron4.com/wp-content/uploads/sites/11/2021/05/KRON-4-App-QR-Code-FS-FLOWCODE.jpg?resize=50,28 50w" sizes="auto, (max-width: 300px) 100vw, 300px" /></p>
</div></div>
		</section><section id="media_image-59" class="widget widget--has-z-index-stacking-reset widget_media_image" data-component="dropzoneWidget"><a href="/hill-politics"><img class="image " src="https://i0.wp.com/www.nxsttv.com/nmw/wp-content/uploads/sites/107/2024/07/Hill-Promo-Pic.png?quality=75&w=300&ssl=1" alt="" width="300" height="178" decoding="async" loading="lazy" /></a></section>
	
	
	
						<!-- Ad Unit Square mr1-->
			<aside class="ad-unit ad-unit--square">
				<div class="ad-unit__content">
					     <div id="acm-ad-tag-mr1-mr1"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1280,0],[[300,250]]],[[1024,0],[[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],&quot;size&quot;:[300,250]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;mr1&quot;,&quot;fold&quot;:&quot;mid&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-mr1-mr1" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     				</div>
			</aside>
			<!-- END Ad Unit Square mr1-->
			
			<!-- Nativo -->
		<div id="native-rr"></div>
		<!-- END Nativo -->
	
	
	<section id="custom_html-7" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"><div data-cswidget="8499"> </div>
<script type="text/javascript" async defer src="//cdn.cityspark.com/wid/get.js" > </script></div></div></section><section id="custom_html-4" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"><center><a class="twitter-timeline" data-height="700" data-width="100%" href="https://twitter.com/kron4news?ref_src=twsrc%5Etfw">Tweets by kron4news</a></center><script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script></div></div></section><section id="custom_html-14" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"><div id="circularhub_module_14676"></div>
<script src="//api.circularhub.com/14676/2ffbae56b1fe4703/circularhub_module.js"></script></div></div></section><section id="custom_html-236" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"><div id="bestreviews-widget"></div>
<script async src="https://cdn.bestreviews.com/deals/main.bundle.js"></script></div></div></section><section id="custom_html-327" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"></div></div></section><section id="custom_html-328" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"></div></div></section><section id="custom_html-329" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"></div></div></section><section id="custom_html-330" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"></div></div></section><section id="custom_html-331" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"></div></div></section><section id="custom_html-332" class="widget_text widget widget--has-z-index-stacking-reset widget_custom_html" data-component="dropzoneWidget"><div class="textwidget custom-html-widget"><div class="rich-text-cascade"></div></div></section>
	
		<aside class="ad-unit ad-unit--square ad-unit--sticky">
		<div class="ad-unit__content">
			     <div id="acm-ad-tag-mr_combo2-mr_combo2"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1280,0],[[300,600],[300,250]]],[[1024,0],[[300,600],[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],&quot;size&quot;:[300,250]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;mr_combo2&quot;,&quot;fold&quot;:&quot;btf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-mr_combo2-mr_combo2" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     		</div>
	</aside>
	</section><!-- #secondary -->
	</div>

			<aside class="ad-unit ad-unit--exit">
			<div class="ad-unit__content">
				<!-- -->			</div>
		</aside>

				<aside class="ad-unit ad-unit--leaderboard">
			<div class="ad-unit__content">
				     <div id="acm-ad-tag-leaderboard3-leaderboard3"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1280,0],[[728,90],[970,250]]],[[1024,0],[[728,90],[970,250]]],[[768,0],[[728,90]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],&quot;size&quot;:[320,50]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;leaderboard3&quot;,&quot;fold&quot;:&quot;btf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-leaderboard3-leaderboard3" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     			</div>
		</aside>
			
			<aside class="ad-unit ad-unit--oop">
			<div class="ad-unit__content">
				     <div id="acm-ad-tag-oop-super-billboard"         data-slot="{&quot;is_oop&quot;:true,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[0,0],[[1,1]]]],&quot;size&quot;:[1,1]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;oop&quot;,&quot;fold&quot;:&quot;atf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-oop-super-billboard" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     			</div>
		</aside>
		<aside class="ad-unit ad-unit--interstitial">
			<div class="ad-unit__content">
				<!-- -->			</div>
		</aside>
	
			<aside class="ad-unit">
			<div class="ad-unit__content">
				<!-- -->			</div>
		</aside>
	</div><!-- #content -->

		</div>

		<footer id="footer" class="site-footer">
	<div class="site-footer__content">
		<div class="site-footer__content--two-col">
			<div class="site-footer__site-branding">
				<div class="site-footer__site-branding--logo">
					<a href="https://www.kron4.com/" rel="home">
						<img src="https://www.kron4.com/wp-content/uploads/sites/11/2025/04/cropped-KRON4-footer-update-1.png" srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/04/cropped-KRON4-footer-update-1.png?w=410 410w"
						sizes="300px" alt="KRON" loading="lazy"   />
					</a>
				</div>
				<div class="site-footer__site-branding--slogan">
					<h5>
						The Bay Area&#039;s Local News Station					</h5>
				</div>
			</div>
			<div class="site-footer__site-nav-container">
				
<div class="site-footer__site-nav-container--primary-nav">
	<div class="menu-footer-primary-container"><ul id="menu-footer-primary" class="menu"><li id="menu-item-11094" class="menu-item menu-item-type-taxonomy menu-item-object-category current-post-ancestor current-menu-parent current-post-parent menu-item-11094"><a href="https://www.kron4.com/news/bay-area/" data-link-type="navigation-link">Local News</a></li>
<li id="menu-item-12142" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12142"><a href="https://www.kron4.com/weather-san-francisco/" data-link-type="navigation-link">San Francisco Weather</a></li>
<li id="menu-item-2058777" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-2058777"><a href="https://www.kron4.com/watch-live/" data-link-type="navigation-link">KRON4+</a></li>
<li id="menu-item-12145" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12145"><a href="https://www.kron4.com/report-it/" data-link-type="navigation-link">Report It!</a></li>
</ul></div></div>
<div class="site-footer__site-nav-container--secondary-nav">
	<div class="menu-footer-secondary-container"><ul id="menu-footer-secondary" class="menu"><li id="menu-item-12137" class="menu-item menu-item-type-post_type menu-item-object-page menu-item-12137"><a href="https://www.kron4.com/privacy-policy/" data-link-type="navigation-link">About our Ads</a></li>
<li id="menu-item-12138" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-12138"><a target="_blank" href="https://www.kron4.com/wp-content/uploads/sites/11/2025/07/EEO-Public-File-Report-ending-July-31-2025.pdf" data-link-type="navigation-link">EEO Report</a></li>
<li id="menu-item-12139" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-12139"><a href="https://publicfiles.fcc.gov/tv-profile/KRON-TV" data-link-type="navigation-link">FCC Public File</a></li>
<li id="menu-item-12140" class="menu-item menu-item-type-custom menu-item-object-custom menu-item-12140"><a href="https://www.kron4.com/wp-content/uploads/sites/11/2023/11/Nexstar-CC-Certification.pdf" data-link-type="navigation-link">Nexstar CC Certification</a></li>
</ul></div></div>
			</div>
			<div class="site-footer__site-social-container">
				<div class="site-footer__site-social-container--social-apps-container">
						<div class="site-footer__apps">
		<h2 class="site-footer__heading">Get News App</h2>
		<div class="app-links">
							<div class="app-link--ios-app-store app-link">
					<a href="https://itunes.apple.com/us/app/kron-4/id472672814">
						
<svg viewBox="0 0 121 41" xmlns="http://www.w3.org/2000/svg"><defs><clipPath id="a"><path fill="#fff" d="M0 0h122v41H0z"/></clipPath></defs><g clip-path="url(#a)" stroke="null"><path d="M111.52.725H9.58c-.372 0-.739 0-1.11.002-.31.002-.617.008-.93.013-.68.008-1.36.067-2.03.178-.671.114-1.32.327-1.927.634a6.523 6.523 0 00-2.834 2.83 6.664 6.664 0 00-.633 1.925A13.108 13.108 0 00-.066 8.33c-.01.31-.01.62-.015.93V32.63c.005.314.006.618.015.932.008.678.069 1.355.182 2.024.111.67.325 1.32.633 1.925.307.605.71 1.156 1.194 1.632.48.482 1.033.885 1.64 1.192a6.802 6.802 0 001.926.637c.671.11 1.35.17 2.03.18.314.006.621.01.932.01.37.002.737.002 1.109.002h101.94c.364 0 .733 0 1.098-.002.308 0 .625-.004.934-.01a13.494 13.494 0 002.027-.18 6.897 6.897 0 001.933-.637 6.355 6.355 0 001.639-1.192 6.482 6.482 0 001.198-1.632 6.677 6.677 0 00.627-1.925c.113-.67.176-1.346.188-2.024.003-.314.003-.618.003-.932.008-.367.008-.733.008-1.106V10.365c0-.37 0-.737-.008-1.104 0-.31 0-.62-.003-.93a13.55 13.55 0 00-.188-2.025 6.702 6.702 0 00-.627-1.924 6.55 6.55 0 00-2.837-2.83 6.871 6.871 0 00-1.933-.634 13.247 13.247 0 00-2.027-.18c-.309-.004-.626-.01-.934-.012-.365-.002-.734-.002-1.098-.002v0z" fill="#A6A6A6"/><path d="M8.485 40.279c-.31 0-.61-.004-.917-.01a12.893 12.893 0 01-1.894-.166 5.974 5.974 0 01-1.678-.554 5.475 5.475 0 01-1.416-1.027 5.383 5.383 0 01-1.034-1.412 5.777 5.777 0 01-.55-1.676c-.104-.626-.16-1.26-.169-1.895a92.003 92.003 0 01-.015-.923V9.262s.01-.7.015-.905c.008-.634.064-1.267.168-1.892a5.81 5.81 0 01.55-1.68c.265-.524.612-1.001 1.03-1.414a5.638 5.638 0 011.42-1.034 5.91 5.91 0 011.675-.55 12.78 12.78 0 011.9-.166l.915-.012h104.13l.925.013c.632.007 1.262.062 1.884.164.588.1 1.16.287 1.693.554a5.661 5.661 0 012.447 2.447c.264.525.447 1.087.542 1.667.105.63.164 1.268.177 1.908.003.286.003.593.003.9.008.379.008.74.008 1.103v21.158c0 .368 0 .726-.008 1.087 0 .33 0 .63-.004.94-.012.628-.07 1.255-.174 1.874a5.809 5.809 0 01-.547 1.688c-.267.519-.614.991-1.03 1.401a5.48 5.48 0 01-1.417 1.034 5.952 5.952 0 01-1.69.556c-.626.102-1.26.157-1.894.165-.297.007-.608.01-.91.01l-1.098.003-103.04-.002z"/><path d="M25.025 21.249a4.995 4.995 0 012.388-4.198 5.13 5.13 0 00-4.044-2.181c-1.702-.178-3.351 1.016-4.218 1.016-.884 0-2.22-.998-3.657-.969a5.395 5.395 0 00-4.532 2.758c-1.96 3.385-.498 8.36 1.38 11.097.938 1.34 2.036 2.837 3.472 2.784 1.406-.059 1.93-.895 3.627-.895 1.68 0 2.173.895 3.639.86 1.508-.024 2.458-1.345 3.364-2.698a11.073 11.073 0 001.539-3.126 4.827 4.827 0 01-2.958-4.447zM22.258 13.07a4.919 4.919 0 001.13-3.529 5.028 5.028 0 00-3.251 1.678 4.683 4.683 0 00-1.159 3.398 4.162 4.162 0 003.28-1.547zM42.791 28.163h-4.796l-1.152 3.393h-2.032l4.543-12.554h2.111l4.543 12.554h-2.066l-1.151-3.393zm-4.3-1.566h3.802L40.42 21.09h-.052l-1.875 5.507zM55.819 26.98c0 2.844-1.526 4.672-3.828 4.672a3.115 3.115 0 01-2.887-1.602h-.043v4.534h-1.884V22.403H49v1.522h.035a3.251 3.251 0 012.921-1.618c2.328 0 3.863 1.837 3.863 4.673zm-1.935 0c0-1.853-.96-3.071-2.425-3.071-1.439 0-2.406 1.244-2.406 3.071 0 1.844.967 3.08 2.406 3.08 1.465 0 2.425-1.21 2.425-3.08zM65.916 26.98c0 2.844-1.526 4.672-3.829 4.672a3.115 3.115 0 01-2.886-1.602h-.043v4.534h-1.884V22.403h1.823v1.522h.035a3.25 3.25 0 012.921-1.618c2.328 0 3.863 1.837 3.863 4.673zm-1.935 0c0-1.853-.96-3.071-2.425-3.071-1.439 0-2.406 1.244-2.406 3.071 0 1.844.967 3.08 2.406 3.08 1.465 0 2.425-1.21 2.425-3.08zM72.589 28.058c.14 1.245 1.352 2.062 3.008 2.062 1.587 0 2.73-.817 2.73-1.94 0-.974-.69-1.558-2.32-1.957l-1.63-.392c-2.311-.557-3.384-1.635-3.384-3.385 0-2.166 1.892-3.654 4.579-3.654 2.659 0 4.481 1.488 4.543 3.654h-1.901c-.114-1.253-1.152-2.009-2.67-2.009-1.516 0-2.554.765-2.554 1.879 0 .887.663 1.41 2.285 1.81l1.386.34c2.582.608 3.654 1.643 3.654 3.48 0 2.348-1.875 3.82-4.857 3.82-2.79 0-4.675-1.437-4.796-3.708h1.927zM84.38 20.236v2.166h1.744v1.488H84.38v5.046c0 .784.35 1.15 1.116 1.15a5.91 5.91 0 00.62-.044v1.479a5.186 5.186 0 01-1.046.087c-1.858 0-2.582-.696-2.582-2.472V23.89h-1.334v-1.488h1.334v-2.166h1.892zM87.134 26.98c0-2.88 1.7-4.69 4.351-4.69 2.66 0 4.352 1.81 4.352 4.69 0 2.888-1.683 4.69-4.352 4.69-2.668 0-4.351-1.802-4.351-4.69zm6.784 0c0-1.976-.907-3.142-2.433-3.142s-2.432 1.175-2.432 3.142c0 1.983.906 3.14 2.432 3.14s2.433-1.157 2.433-3.14zM97.39 22.403h1.796v1.558h.044a2.185 2.185 0 012.207-1.654c.216 0 .433.023.645.07v1.758a2.636 2.636 0 00-.846-.114 1.904 1.904 0 00-1.467.603 1.885 1.885 0 00-.496 1.503v5.43H97.39v-9.154zM110.76 28.867c-.253 1.662-1.875 2.802-3.95 2.802-2.67 0-4.326-1.784-4.326-4.646 0-2.871 1.666-4.733 4.247-4.733 2.537 0 4.133 1.74 4.133 4.514v.644h-6.479v.114a2.388 2.388 0 002.468 2.593 2.078 2.078 0 002.12-1.288h1.787zm-6.366-2.732h4.587a2.2 2.2 0 00-1.364-2.158 2.21 2.21 0 00-.886-.165 2.323 2.323 0 00-2.337 2.323zM38.256 9.552a2.681 2.681 0 012.134.826 2.667 2.667 0 01.711 2.171c0 1.927-1.044 3.035-2.845 3.035h-2.184V9.552h2.184zm-1.245 5.179h1.14a1.903 1.903 0 001.93-1.337c.084-.27.105-.554.064-.833a1.899 1.899 0 00-1.172-2.02 1.91 1.91 0 00-.822-.137h-1.14v4.327zM42.162 13.306a2.154 2.154 0 011.277-2.178 2.165 2.165 0 012.926 1.292c.095.285.13.587.1.886a2.153 2.153 0 01-1.276 2.181 2.166 2.166 0 01-2.928-1.294 2.153 2.153 0 01-.099-.887zm3.377 0c0-.987-.444-1.564-1.224-1.564-.782 0-1.223.577-1.223 1.564 0 .995.44 1.567 1.223 1.567.78 0 1.224-.576 1.224-1.567zM52.186 15.584h-.934l-.943-3.353h-.071l-.94 3.353h-.925l-1.257-4.552h.913l.817 3.473h.068l.938-3.473h.864l.938 3.473h.07l.814-3.473h.9l-1.252 4.552zM54.496 11.031h.867v.723h.067a1.363 1.363 0 011.362-.81 1.487 1.487 0 011.528 1.036c.066.212.084.437.051.656v2.947h-.9v-2.721c0-.732-.32-1.096-.985-1.096a1.049 1.049 0 00-1.04.71 1.041 1.041 0 00-.05.444v2.663h-.9v-4.552zM59.806 9.254h.9v6.33h-.9v-6.33zM61.958 13.305a2.151 2.151 0 011.277-2.178 2.166 2.166 0 012.926 1.292c.095.285.13.587.1.886a2.151 2.151 0 01-1.275 2.181 2.166 2.166 0 01-2.928-1.294 2.151 2.151 0 01-.1-.887zm3.377 0c0-.987-.444-1.564-1.224-1.564-.782 0-1.223.577-1.223 1.564 0 .995.44 1.567 1.223 1.567.78 0 1.224-.576 1.224-1.567zM67.21 14.297c0-.82.612-1.292 1.697-1.359l1.236-.071v-.393c0-.48-.319-.752-.934-.752-.503 0-.851.184-.951.506h-.872c.092-.782.83-1.284 1.864-1.284 1.144 0 1.79.568 1.79 1.53v3.11h-.867v-.64H70.1a1.534 1.534 0 01-1.37.716 1.382 1.382 0 01-1.4-.806 1.372 1.372 0 01-.121-.557zm2.933-.389v-.38l-1.114.07c-.629.043-.914.256-.914.657 0 .41.357.648.847.648a1.077 1.077 0 001.18-.995zM72.223 13.306c0-1.438.741-2.35 1.894-2.35a1.507 1.507 0 011.4.799h.066v-2.5h.9v6.33h-.862v-.72h-.071a1.582 1.582 0 01-1.433.794c-1.16 0-1.894-.911-1.894-2.353zm.93 0c0 .966.456 1.547 1.22 1.547.758 0 1.227-.59 1.227-1.543 0-.949-.474-1.547-1.228-1.547-.758 0-1.219.585-1.219 1.543zM80.21 13.306a2.152 2.152 0 011.277-2.178 2.165 2.165 0 012.926 1.292c.095.285.13.587.1.886a2.153 2.153 0 01-1.276 2.181 2.165 2.165 0 01-2.927-1.294 2.151 2.151 0 01-.1-.887zm3.377 0c0-.987-.444-1.564-1.224-1.564-.782 0-1.223.577-1.223 1.564 0 .995.44 1.567 1.223 1.567.78 0 1.224-.576 1.224-1.567zM85.721 11.031h.867v.723h.067a1.364 1.364 0 011.362-.81 1.487 1.487 0 011.528 1.036c.066.212.084.437.05.656v2.947h-.9v-2.721c0-.732-.318-1.096-.984-1.096a1.049 1.049 0 00-1.04.71 1.043 1.043 0 00-.05.444v2.663h-.9v-4.552zM94.685 9.898v1.154h.989v.757h-.989v2.341c0 .477.197.686.645.686.115 0 .23-.008.344-.021v.748a2.965 2.965 0 01-.49.046c-1.002 0-1.4-.351-1.4-1.229v-2.571h-.725v-.757h.725V9.898h.901zM96.902 9.254h.892v2.51h.072a1.401 1.401 0 011.391-.816 1.505 1.505 0 011.571 1.697v2.939h-.901v-2.718c0-.727-.34-1.095-.976-1.095a1.068 1.068 0 00-1.09.699 1.062 1.062 0 00-.059.455v2.659h-.9v-6.33zM106.08 14.354a1.85 1.85 0 01-1.977 1.317 2.079 2.079 0 01-1.599-.688 2.058 2.058 0 01-.509-1.662 2.103 2.103 0 012.104-2.378c1.27 0 2.036.865 2.036 2.295v.313h-3.222v.05a1.207 1.207 0 00.319.921 1.207 1.207 0 00.896.384 1.097 1.097 0 001.085-.552h.867zm-3.167-1.467h2.304a1.101 1.101 0 00-.3-.838 1.101 1.101 0 00-.823-.341 1.165 1.165 0 00-1.182 1.179z" fill="#fff"/></g></svg>
						<span class="screen-reader-text">Get the iOS app</span>
					</a>
				</div>
										<div class="app-link--google-play app-link">
					<a href="https://play.google.com/store/apps/details?id=com.nexstar.id3542">
						<svg xmlns="http://www.w3.org/2000/svg" width="135" height="40" xmlns:v="https://vecta.io/nano"><defs><linearGradient y2=".719" x2="-.384" y1=".049" x1=".915" id="A"><stop stop-color="#00a0ff" offset="0"/><stop stop-color="#00a1ff" offset=".01"/><stop stop-color="#00beff" offset=".26"/><stop stop-color="#00d2ff" offset=".51"/><stop stop-color="#00dfff" offset=".76"/><stop stop-color="#00e3ff" offset="1"/></linearGradient><linearGradient y2=".5" x2="-1.306" y1=".5" x1="1.077" id="B"><stop stop-color="#ffe000" offset="0"/><stop stop-color="#ffbd00" offset=".41"/><stop stop-color="orange" offset=".78"/><stop stop-color="#ff9c00" offset="1"/></linearGradient><linearGradient y2="1.947" x2="-.501" y1=".179" x1=".862" id="C"><stop stop-color="#ff3a44" offset="0"/><stop stop-color="#c31162" offset="1"/></linearGradient><linearGradient y2=".249" x2=".421" y1="-.541" x1="-.188" id="D"><stop stop-color="#32a071" offset="0"/><stop stop-color="#2da771" offset=".07"/><stop stop-color="#15cf74" offset=".48"/><stop stop-color="#06e775" offset=".8"/><stop stop-color="#00f076" offset="1"/></linearGradient></defs><rect rx="5" height="40" width="135" y="-.294"/><path fill="#a6a6a6" d="M130 .506a4.2 4.2 0 0 1 4.2 4.2v30a4.2 4.2 0 0 1-4.2 4.2H5a4.2 4.2 0 0 1-4.2-4.2v-30A4.2 4.2 0 0 1 5 .506h125m0-.8H5a5 5 0 0 0-5 5v30a5 5 0 0 0 5 5h125a5 5 0 0 0 5-5v-30a5 5 0 0 0-5-5z"/><g fill="#fff"><path stroke-width=".2" stroke-miterlimit="10" stroke="#fff" d="M47.42 9.946a2.71 2.71 0 0 1-.75 2 2.91 2.91 0 0 1-2.2.89 3.15 3.15 0 0 1-2.21-5.37 3 3 0 0 1 2.21-.9 3.1 3.1 0 0 1 1.23.25 2.47 2.47 0 0 1 .94.67l-.53.53a2 2 0 0 0-1.64-.71 2.32 2.32 0 0 0-2.33 2.4 2.36 2.36 0 0 0 4 1.73 1.89 1.89 0 0 0 .5-1.22h-2.17v-.72h2.91a2.54 2.54 0 0 1 .04.45zm4.58-2.5h-2.7v1.9h2.46v.72H49.3v1.9H52v.74h-3.5v-6H52v.74zm3.28 5.26h-.77v-5.26h-1.68v-.74H57v.74h-1.72v5.26zm4.66 0v-6h.77v6h-.77zm4.19 0h-.77v-5.26h-1.68v-.74h4.12v.74h-1.67v5.26zm9.48-.78a3.12 3.12 0 0 1-4.4 0 3.24 3.24 0 0 1 0-4.45 3.1 3.1 0 0 1 4.4 0 3.23 3.23 0 0 1 0 4.45zm-3.83-.5a2.31 2.31 0 0 0 3.26 0 2.56 2.56 0 0 0 0-3.44 2.31 2.31 0 0 0-3.26 0 2.56 2.56 0 0 0 0 3.44zm5.8 1.28v-6h.94l2.92 4.67v-4.67h.77v6h-.8l-3.05-4.89v4.89h-.78z"/><path d="M68.14 21.456a4.25 4.25 0 1 0 4.27 4.25 4.19 4.19 0 0 0-4.27-4.25zm0 6.83a2.58 2.58 0 1 1 2.4-2.58 2.46 2.46 0 0 1-2.4 2.58zm-9.31-6.83a4.25 4.25 0 1 0 4.26 4.25 4.19 4.19 0 0 0-4.27-4.25h.01zm0 6.83a2.58 2.58 0 1 1 2.39-2.58 2.46 2.46 0 0 1-2.4 2.58h.01zm-11.09-5.52v1.8h4.32a3.77 3.77 0 0 1-1 2.27 4.42 4.42 0 0 1-3.33 1.32 4.8 4.8 0 0 1 0-9.6 4.6 4.6 0 0 1 3.27 1.29l1.27-1.27a6.29 6.29 0 0 0-4.53-1.87 6.61 6.61 0 1 0 0 13.21 6 6 0 0 0 4.61-1.85 6 6 0 0 0 1.56-4.22 5.87 5.87 0 0 0-.1-1.13l-6.07.05zm45.31 1.4a4 4 0 0 0-3.64-2.71 4 4 0 0 0-4 4.25 4.16 4.16 0 0 0 4.22 4.25 4.23 4.23 0 0 0 3.54-1.88l-1.45-1a2.43 2.43 0 0 1-2.09 1.18 2.16 2.16 0 0 1-2.06-1.29l5.69-2.35-.21-.45zm-5.8 1.42a2.33 2.33 0 0 1 2.22-2.48 1.65 1.65 0 0 1 1.58.9l-3.8 1.58zm-4.62 4.12h1.87v-12.5h-1.87v12.5zm-3.06-7.3h-.07a3 3 0 0 0-2.24-1 4.26 4.26 0 0 0 0 8.51 2.9 2.9 0 0 0 2.24-1h.06v.61c0 1.63-.87 2.5-2.27 2.5a2.35 2.35 0 0 1-2.14-1.51l-1.63.68a4.05 4.05 0 0 0 3.77 2.51c2.19 0 4-1.29 4-4.43v-7.57h-1.72v.7zm-2.14 5.88a2.59 2.59 0 0 1 0-5.16 2.4 2.4 0 0 1 2.27 2.58 2.38 2.38 0 0 1-2.28 2.58h.01zm24.38-11.08h-4.47v12.5h1.87v-4.74h2.61a3.89 3.89 0 1 0 0-7.76h-.01zm0 6H99.2v-4.26h2.65a2.14 2.14 0 1 1 0 4.29l-.04-.03zm11.53-1.8a3.5 3.5 0 0 0-3.33 1.91l1.66.69a1.77 1.77 0 0 1 1.7-.92 1.8 1.8 0 0 1 2 1.61v.13a4.13 4.13 0 0 0-1.95-.48c-1.79 0-3.6 1-3.6 2.81a2.89 2.89 0 0 0 3.1 2.75 2.63 2.63 0 0 0 2.4-1.2h.06v1h1.8v-4.81c0-2.19-1.66-3.46-3.79-3.46l-.05-.03zm-.23 6.85c-.61 0-1.46-.31-1.46-1.06 0-1 1.06-1.33 2-1.33a3.32 3.32 0 0 1 1.7.42 2.26 2.26 0 0 1-2.19 2l-.05-.03zm10.63-6.55l-2.14 5.42h-.06l-2.22-5.42h-2l3.33 7.58-1.9 4.21h1.95l5.12-11.79h-2.08zm-16.81 8h1.87v-12.5h-1.87v12.5z"/></g><path fill="url(#A)" d="M10.44 7.246a2 2 0 0 0-.46 1.4v22.12a2 2 0 0 0 .46 1.4l.07.07 12.39-12.38v-.29L10.51 7.176l-.07.07z"/><path fill="url(#B)" d="M27 23.986l-4.1-4.13v-.29l4.1-4.14.09.05 4.91 2.79c1.4.79 1.4 2.09 0 2.89l-4.89 2.78-.11.05z"/><path fill="url(#C)" d="M27.12 23.926l-4.22-4.22-12.46 12.46a1.63 1.63 0 0 0 2.08.06l14.61-8.3"/><path fill="url(#D)" d="M27.12 15.486l-14.61-8.3a1.63 1.63 0 0 0-2.08.06l12.47 12.46 4.22-4.22z"/><path opacity=".2" d="M27 23.836l-14.49 8.25a1.67 1.67 0 0 1-2 0l-.07.07.07.07a1.66 1.66 0 0 0 2 0l14.61-8.3-.12-.09z"/><path opacity=".12" d="M10.44 32.026a2 2 0 0 1-.46-1.4v.15a2 2 0 0 0 .46 1.4l.07-.07-.07-.08zM32 21.006l-5 2.83.09.09 4.91-2.78a1.75 1.75 0 0 0 1-1.44 1.86 1.86 0 0 1-1 1.3z"/><path opacity=".25" fill="#fff" d="M12.51 7.326L32 18.406a1.86 1.86 0 0 1 1 1.3 1.75 1.75 0 0 0-1-1.44L12.51 7.186c-1.4-.79-2.54-.13-2.54 1.47v.15c.03-1.61 1.15-2.27 2.54-1.48z"/></svg>
						<span class="screen-reader-text">Get the Android app from Google Play</span>
					</a>
				</div>
					</div>
	</div>
				</div>
				
	<div class="site-footer__social">
		<h2 class="site-footer__heading">Stay Connected</h2>
		
<aside class="social-links social-links--default">
	<ul class="social-links__list">
					<li class="social-links__list-item social-links__list-item--facebook">
				<a href="https://www.facebook.com/KRON4/">
					
<svg xmlns="http://www.w3.org/2000/svg" width="23" height="25" fill="none" xmlns:v="https://vecta.io/nano"><path d="M20.98 12.564c0-5.788-4.693-10.481-10.48-10.481S.019 6.776.019 12.564c0 5.232 3.832 9.567 8.843 10.353v-7.323H6.201v-3.031h2.661v-2.307c0-2.626 1.565-4.078 3.959-4.078 1.146 0 2.346.205 2.346.205v2.579h-1.322c-1.302 0-1.708.808-1.708 1.637v1.965h2.907l-.465 3.031h-2.442v7.323c5.012-.787 8.844-5.123 8.844-10.354z" fill="#fff"/></svg>
				</a>
			</li>
							<li class="social-links__list-item social-links__list-item--socialnetworkx">
				<a href="https://www.twitter.com/kron4news/">
					<svg width="328" height="336" viewBox="0 0 328 336" fill="none" xmlns="http://www.w3.org/2000/svg">
<path d="M195.02 142.516L316.786 0.972168H287.932L182.201 123.873L97.7552 0.972168H0.356445L128.056 186.82L0.356445 335.25H29.2129L140.867 205.463L230.048 335.25H327.447L195.013 142.516H195.02ZM155.497 188.457L142.558 169.951L39.6103 22.6949H83.9321L167.012 141.535L179.951 160.041L287.945 314.516H243.623L155.497 188.464V188.457Z" fill="white"/>
</svg>
				</a>
			</li>
							<li class="social-links__list-item social-links__list-item--instagram">
				<a href="https://www.instagram.com/kron4tv/">
					
<svg xmlns="http://www.w3.org/2000/svg" width="25" height="25" fill="none" xmlns:v="https://vecta.io/nano"><path d="M12.5 2.253l5.052.073c3.387.154 4.97 1.761 5.124 5.124l.072 5.051-.072 5.051c-.155 3.359-1.733 4.97-5.124 5.124l-5.052.073c-3.338 0-3.733-.012-5.051-.073-3.396-.155-4.97-1.77-5.124-5.125L2.252 12.5l.073-5.051c.155-3.361 1.733-4.97 5.124-5.124l5.051-.072zM12.5 0L7.347.075C2.807.283.284 2.802.076 7.346.015 8.68 0 9.105 0 12.5l.075 5.154c.208 4.54 2.727 7.063 7.271 7.271 1.334.06 1.759.075 5.154.075s3.821-.015 5.154-.075c4.535-.208 7.065-2.727 7.27-7.271.061-1.333.076-1.759.076-5.154l-.075-5.153c-.204-4.535-2.726-7.062-7.27-7.271C16.321.015 15.895 0 12.5 0h0zm0 6.081A6.42 6.42 0 0 0 6.081 12.5a6.42 6.42 0 0 0 6.419 6.42 6.42 6.42 0 0 0 6.419-6.42A6.42 6.42 0 0 0 12.5 6.081zm0 10.585c-2.301 0-4.167-1.865-4.167-4.167A4.17 4.17 0 0 1 12.5 8.333a4.17 4.17 0 0 1 4.167 4.167c0 2.302-1.866 4.167-4.167 4.167zm6.673-12.339a1.5 1.5 0 1 0 0 3 1.5 1.5 0 1 0 0-3z" fill="#fff"/></svg>
				</a>
			</li>
									<li class="social-links__list-item social-links__list-item--youtube">
				<a href="https://www.youtube.com/channel/UCVWQWc8PXy6Itt7YNrivOYw">
					
<svg xmlns="http://www.w3.org/2000/svg" width="25" height="25" fill="none" xmlns:v="https://vecta.io/nano"><path d="M24.477 6.443c-.141-.532-.42-1.018-.808-1.408a3.14 3.14 0 0 0-1.403-.817c-1.949-.526-9.767-.526-9.767-.526s-7.818 0-9.768.526c-.531.145-1.014.427-1.402.817s-.666.876-.807 1.408C0 8.406 0 12.5 0 12.5s0 4.094.523 6.056a3.14 3.14 0 0 0 2.21 2.225c1.949.526 9.767.526 9.767.526s7.818 0 9.768-.526a3.14 3.14 0 0 0 2.21-2.225C25 16.593 25 12.5 25 12.5s0-4.094-.523-6.056zM9.943 16.216V8.783l6.534 3.717-6.534 3.717z" fill="#fff"/></svg>
				</a>
			</li>
							<li class="social-links__list-item social-links__list-item--haystack">
				<a href="https://www.haystack.tv/channel/kron/">
					
<svg id="Capa_2" class="haystack"  data-name="Capa 2" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 210 210">
	<title>Haystack</title>
	<defs>
		<style>
			.cls-1 {
				fill: none;
			}

			.cls-2 {
				fill: #fff;
			}
		</style>
	</defs>
	<g class="center_svg" id="Capa_1-2" data-name="Capa 1">
		<g>
			<polygon class="cls-2" points="158.3 150 93.1 167.13 93.1 20.35 158.3 2.87 158.3 150"/>
			<polygon class="cls-2" points="11.7 20.51 11.7 85.44 76.9 67.97 76.9 3.04 11.7 20.51"/>
			<polygon class="cls-2" points="11.7 102.19 11.7 167.13 76.9 149.66 76.9 84.72 11.7 102.19"/>
		</g>
		<rect class="cls-1" width="210" height="210"/>
	</g>
</svg>
				</a>
			</li>
							<li class="social-links__list-item social-links__list-item--rss">
				<a href="https://www.kron4.com/news/app-feed">
					
<svg xmlns="http://www.w3.org/2000/svg" width="25" height="25" fill="none" xmlns:v="https://vecta.io/nano"><path d="M19.999 25C19.999 14.028 10.972 5 0 5V0c13.714 0 25 11.287 25 25h-5.001zM3.428 18.141a3.44 3.44 0 0 1 3.43 3.432C6.858 23.462 5.311 25 3.42 25S0 23.465 0 21.573s1.536-3.431 3.428-3.432zM16.572 25h-4.859c0-6.426-5.286-11.713-11.712-11.713V8.427c9.091 0 16.572 7.483 16.572 16.573z" fill="#fff"/></svg>
				</a>
			</li>
							<li class="social-links__list-item social-links__list-item--email">
				<a href="mailto:BreakingNews@kron4.com">
					
<svg xmlns="http://www.w3.org/2000/svg" width="25" height="25" fill="none" stroke="#fff" stroke-width="2.083" stroke-linejoin="round" xmlns:v="https://vecta.io/nano"><path d="M4.083 4H20.75a2.09 2.09 0 0 1 2.083 2.083v12.5a2.09 2.09 0 0 1-2.083 2.083H4.083A2.09 2.09 0 0 1 2 18.583v-12.5A2.09 2.09 0 0 1 4.083 4z"/><path d="M22.833 6.083l-10.417 7.292L2 6.083" stroke-linecap="round"/></svg>
				</a>
			</li>
			</ul>
</aside>
	</div>
				</div>
			<div class="site-footer__network-branding">
				<div class="site-footer__network-branding--logo">
																	<a href="https://www.nexstar.tv" title="Go to Nexstar.tv">
							<img src="https://www.kron4.com/wp-content/themes/nexstar/client/src/images/footer/nexstar-logo-white-nmg.png"
								loading="lazy" alt="Nexstar Logo">
						</a>
									</div>
			</div>
			<div class="site-footer__network-nav-container">
				
<div class="site-footer__network-nav-container--network-nav">
	<div class="menu">
		<ul>
														<li class="network-footer-privacy-policy">
						<a
							href="https://www.nexstar.tv/privacy-policy/"
							target="_blank"
						>
							Privacy Policy						</a>
													<span class="network-footer-privacy-policy__last-updated-date">
								09/30/2025							</span>
											</li>
																					<li class="network-footer-terms-of-use">
						<a
							href="https://www.nexstar.tv/terms-of-use/"
							target="_blank"
						>
							Terms Of Use						</a>
											</li>
																					<li class="network-footer-fcc-applications">
						<a
							href="https://www.nexstar.tv/fcc-applications/"
							target="_blank"
						>
							FCC Applications						</a>
											</li>
																					<li class="network-footer-public-file-assistance-contact">
						<a
							href="https://www.kron4.com/contact-us"
							target=""
						>
							Public File Assistance Contact						</a>
											</li>
																											<li class="network-footer-onesignal-desktop">
							<div class="onesignal-customlink-container"></div>						</li>
																										<li class="network-footer-the-hill">
						<a
							href="https://www.thehill.com/"
							target=""
						>
							The Hill						</a>
											</li>
																					<li class="network-footer-newsnation">
						<a
							href="https://www.newsnationnow.com/"
							target=""
						>
							NewsNation						</a>
											</li>
																					<li class="network-footer-bestreviews">
						<a
							href="https://www.bestreviews.com/"
							target=""
						>
							BestReviews						</a>
											</li>
																					<li class="network-footer-content-licensing">
						<a
							href="https://www.newsnationnow.com/licensing-nexstars-local-and-national-television-news-footage/"
							target=""
						>
							Content Licensing						</a>
											</li>
																					<li class="network-footer-nexstar-digital">
						<a
							href="https://www.nexstardigital.com/"
							target=""
						>
							Nexstar Digital						</a>
											</li>
																					<li class="network-footer-journalistic-integrity">
						<a
							href="https://www.nexstar.tv/corporate-social-responsibility/journalistic-integrity/"
							target=""
						>
							Journalistic Integrity						</a>
											</li>
																					<li class="network-footer-sitemap">
						<a
							href="https://www.kron4.com/sitemap/"
							target=""
						>
							Sitemap						</a>
											</li>
															<li>
								<a style="cursor: pointer;" onclick="OneTrust.ToggleInfoDisplay()"> Your Privacy Choices				<img
					src="https://www.kron4.com/wp-content/plugins/nexstar-onetrust/images/privacyoptions.svg"
					srcset="https://www.kron4.com/wp-content/plugins/nexstar-onetrust/images/privacyoptions.svg?w=15%2015vw"
					sizes="14px"
					loading="lazy"
					style="display:inline; height: 14px; margin:0 5px; vertical-align:middle;"
					alt="CCPA Privacy Icon">
			</a>
						</li>
					</ul>
	</div>
</div>

			</div>
		</div>
		<div class="site-footer__copyright--container">
			<div class="site-footer__copyright">
				© 1998 - 2025 Nexstar Media Inc. | All Rights Reserved.			</div>
	</div>
</footer>
	</div><!-- #page -->


	
	
<!-- Nielsen -->
<script>
	// Static Queue Snippet

		!function(t,n){t[n]=t[n]||{nlsQ:function(e,o,c,r,s,i){return s=t.document,r=s.createElement("script"),r.async=1,r.src=("http:"===t.location.protocol?"http:":"https:")+"//cdn-gl.imrworldwide.com/conf/"+e+".js#name="+o+"&ns="+n,i=s.getElementsByTagName("script")[0],i.parentNode.insertBefore(r,i),t[n][o]=t[n][o]||{g:c||{},ggPM:function(e,c,r,s,i){(t[n][o].q=t[n][o].q||[]).push([e,c,r,s,i])}},t[n][o]}}}(window,"NOLBUNDLE");
	
	// SDK Initialization
	var nSdkInstance = NOLBUNDLE.nlsQ("P4D4F9915-E46E-4B58-BCA6-DE3D1F253081","nlsnInstance", {nol_sdkDebug: 0});

	// Content Metadata
	var nielsenMetadata = {
		type: 'static',
		assetid: 0,
		section: "Home",
		segA: '',
		segB: '',
		segC: '',
	};

	// Event 'staticstart' call.
	nSdkInstance.ggPM("staticstart", nielsenMetadata);
</script>

	
	
			<aside class="ad-unit ad-unit--adhesion pre-render">
			<div class="close-btn-container">
				<div class="close-btn" aria-label="Close Viewport Adhesion Ad"></div>
			</div>
			<div class="ad-unit__content pre-render">
				<div class="close-btn-container--mobile">
					&#x2715;
				</div>

				     <div id="acm-ad-tag-adhesion-adhesion-mobile-home"         data-slot="{&quot;is_oop&quot;:false,&quot;is_companion&quot;:true,&quot;sizes&quot;:[[[1024,0],[]],[[768,0],[[728,90]]],[[480,0],[[320,50]]],[[0,0],[[320,50]]]],&quot;size&quot;:[320,50]}"         data-unit="/5678/mg.kron/home"         data-fbonly="false"         data-refids=""         data-not-refids=""         data-targeting="{&quot;kw&quot;:&quot;\/&quot;,&quot;pos&quot;:&quot;adhesion&quot;,&quot;fold&quot;:&quot;atf&quot;,&quot;category&quot;:&quot;&quot;}"     ></div>     <script>     try {         var event = new CustomEvent("nsDfpSlotRendered", {             detail: { id: "acm-ad-tag-adhesion-adhesion-mobile-home" }         });         console.log("HTL.nsDfpSlotRendered", event);         window.dispatchEvent(event);     } catch (err) {}     </script>     			</div>
		</aside>
	
			<div
			id="adobe-primetime-bypass-container"
			data-react-component="AdobePrimetimeBypass"
			data-logoAlt="KRON"
			data-logoUrl="https://www.kron4.com/wp-content/uploads/sites/11/2025/04/cropped-KRON4-footer-update-1.png"
		></div>
	
	<div id="aria-dialog-overlay"></div>
	<div id="tve-provider-selection-modal"></div>

	
	<script type="speculationrules">
{"prefetch":[{"source":"document","where":{"and":[{"href_matches":"\/*"},{"not":{"href_matches":["\/wp-*.php","\/wp-admin\/*","\/wp-content\/uploads\/sites\/11\/*","\/wp-content\/*","\/wp-content\/plugins\/*","\/wp-content\/themes\/nexstar-wv\/*","\/wp-content\/themes\/nexstar\/*","\/*\\?(.+)"]}},{"not":{"selector_matches":"a[rel~=\"nofollow\"]"}},{"not":{"selector_matches":".no-prefetch, .no-prefetch a"}}]},"eagerness":"conservative"}]}
</script>
		<div id="login-registration-signup" class="login-registration-modal" hidden>
			<div class="lr-modal-content-wrapper">
				<div class="lr-modal-header">
											<a class="lr-modal-logo" rel="home" href="https://www.kron4.com">
							<img width="262" height="99" src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?w=262" class="attachment-medium size-medium" alt="" decoding="async" loading="lazy" srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp 262w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?resize=50,19 50w" sizes="auto, (max-width: 262px) 100vw, 262px" />						</a>
										<div class="lr-modal-logo-tagline"><p>Provided by Nexstar Media Group, Inc.</p>
</div>
				</div>
				<div class="lr-modal-inner-card">
					<h2 class="lr-modal-title">Sign in to create your free My Nexstar account featuring exclusive livestreams</h2>
					<div class="lr-modal-subtitle">Enter your email and we’ll send a secure one-click link to sign in.</div>
					<div class="lr-form-container">
						<form id="email-validation-form" class="lr-form" novalidate>
							<div class="lr-input-wrapper">
								<input
									type="email"
									id="login-registration-check-email-field"
									class="login-registration-email-input"
									placeholder="Email"
									required
									pattern="[^\s@]+@[^\s@]+\.[^\s@]+"
								/>
								<div id="email-validation-error" class="error-message" hidden>Please enter a valid email address</div>
							</div>

							<div class="lr-terms-privacy-note-mobile lr-note lr-hidden-on-desktop">
								<p>By clicking <i>"Unlock Live News"</i> you confirm that you have read and agree to our <a href="https://www.nexstar.tv/terms-of-use/" target="_blank" rel="noopener noreferrer">Terms of Use</a>, which includes a jury trial waiver and class action waiver, and that you have read our <a href="https://www.nexstar.tv/privacy-policy/" target="_blank" rel="noopener noreferrer">Privacy Policy</a> detailing our collection, use and sharing of your personal information.</p>
							</div>
							<div class="lr-terms-privacy-note-desktop lr-note lr-hidden-on-mobile">
								<p>By clicking <i>"Unlock Live News"</i> you confirm that you have read and agree to our <a href="https://www.nexstar.tv/terms-of-use/" target="_blank" rel="noopener noreferrer">Terms of Use</a>, which includes a jury trial waiver and class action waiver, and that you have read our <a href="https://www.nexstar.tv/privacy-policy/" target="_blank" rel="noopener noreferrer">Privacy Policy</a> detailing our collection, use and sharing of your personal information.</p>
							</div>
							<button type="submit" class="lr-button" id="email-form-next-button">Unlock Live News</button>
							<button class="lr-cancel lr-button-link">No Thanks</button>
						</form>
					</div>
					<div class="lr-footer-note-mobile lr-note lr-hidden-on-desktop">
						<p><strong>KRON4 is provided by Nexstar Media Group, Inc., and uses the My Nexstar sign-in, which works across our media network.</strong></p>
<p>Learn more at <a href="https://www.nexstar.tv/privacy-policy/" target="_blank" rel="noopener noreferrer">nexstar.tv/privacy-policy.</a></p>
					</div>
					<div class="lr-footer-note-desktop lr-note lr-hidden-on-mobile">
						<p><strong>KRON4 is provided by Nexstar Media Group, Inc., and uses the My Nexstar sign-in, which works across our media network.</strong></p>
<p><strong>Nexstar Media Group, Inc.</strong> is a leading, diversified media company that produces and distributes engaging local and national news, sports, and entertainment content across its television and digital platforms. The My Nexstar sign-in works across the Nexstar network—including The CW, NewsNation, The Hill, and more. Learn more at <a href="https://www.nexstar.tv/privacy-policy/" target="_blank" rel="noopener noreferrer">nexstar.tv/privacy-policy.</a></p>
					</div>
				</div>
				<div class="lr-modal-footer-logos">
																								<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-nexstar.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-cw.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-newsnation.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-the-hill.png" alt="">
															</div>
			</div>
		</div>

		<div id="login-registration-check-email" class="login-registration-modal" hidden>
			<div class="lr-modal-content-wrapper">
				<button class="lr-cancel lr-close-modal">
					<svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
						<path d="M23.0806 1.23438L1.08057 23.2344" stroke="white" stroke-width="1.288" stroke-miterlimit="10" stroke-linecap="round" stroke-linejoin="round"/>
						<path d="M23.0806 23.2344L1.08057 1.23438" stroke="white" stroke-width="1.288" stroke-miterlimit="10" stroke-linecap="round" stroke-linejoin="round"/>
					</svg>
				</button>
				<div class="lr-modal-header">
											<a class="lr-modal-logo" rel="home" href="https://www.kron4.com">
							<img width="262" height="99" src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?w=262" class="attachment-medium size-medium" alt="" decoding="async" loading="lazy" srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp 262w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?resize=50,19 50w" sizes="auto, (max-width: 262px) 100vw, 262px" />						</a>
										<div class="lr-modal-logo-tagline"><p>Provided by Nexstar Media Group, Inc.</p>
</div>
				</div>
				<div class="lr-modal-inner-card">
					<h2 class="lr-modal-title">Check your email inbox</h2>
					<div class="lr-modal-subtitle">We’ve sent an email containing a verification link which expires in 10 minutes.</div>
					<button class="lr-reset lr-button-link">Try another email</button>
				</div>
				<div class="lr-modal-footer-logos">
																								<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-nexstar.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-cw.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-newsnation.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-the-hill.png" alt="">
															</div>
			</div>
		</div>

		<div id="login-registration-check-registered" class="login-registration-modal" hidden>
			<div class="lr-modal-content-wrapper">
				<div class="lr-modal-header">
											<a class="lr-modal-logo" rel="home" href="https://www.kron4.com">
							<img width="262" height="99" src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?w=262" class="attachment-medium size-medium" alt="" decoding="async" loading="lazy" srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp 262w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?resize=50,19 50w" sizes="auto, (max-width: 262px) 100vw, 262px" />						</a>
										<div class="lr-modal-logo-tagline"><p>Provided by Nexstar Media Group, Inc.</p>
</div>
				</div>
				<div class="lr-modal-inner-card">
					<h2 class="lr-modal-title">Thanks for registering!</h2>
					<div class="lr-modal-subtitle">Lorem ipsum arependom lipms nartop parscitum.</div>
				</div>
				<div class="lr-modal-footer-logos">
																								<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-nexstar.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-cw.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-newsnation.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-the-hill.png" alt="">
															</div>
			</div>
		</div>

		<div id="login-registration-check-logout" class="login-registration-modal login-registration-check-logout" hidden>
			<div class="lr-modal-content-wrapper">
				<div class="lr-modal-header">
											<a class="lr-modal-logo" rel="home" href="https://www.kron4.com">
							<img width="262" height="99" src="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?w=262" class="attachment-medium size-medium" alt="" decoding="async" loading="lazy" srcset="https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp 262w, https://www.kron4.com/wp-content/uploads/sites/11/2025/10/kron-login-dialog-modal.webp?resize=50,19 50w" sizes="auto, (max-width: 262px) 100vw, 262px" />						</a>
										<div class="lr-modal-logo-tagline"><p>Provided by Nexstar Media Group, Inc.</p>
</div>
				</div>
				<div class="lr-modal-inner-card">
					<h2>Are you sure you want to log out?</h2>
					<div class="lr-form">
						<div class="remember-me">
							<input type="checkbox" id="lr-remember-me" name="logout-remember-me">
							<label for="lr-remember-me">Log out of all Nexstar properties</label>
						</div>
						<div class="lr-logout-buttons-wrapper">
							<button type="button" class="lr-button" id="lr-logout-confirm">Log out</button>
							<button type="button" class="lr-button lr-cancel" id="lr-logout-cancel">Cancel</button>
						</div>
					</div>
				</div>
				<div class="lr-modal-footer-logos">
																								<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-nexstar.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-cw.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-newsnation.png" alt="">
																														<img src="https://www.kron4.com/wp-content/plugins/login-registration/img/logo-the-hill.png" alt="">
															</div>
			</div>
		</div>
		<script class="wp-asset-manager nswv-ad-handler-js" type="text/javascript">!function(e){var t={};function n(r){if(t[r])return t[r].exports;var o=t[r]={i:r,l:!1,exports:{}};return e[r].call(o.exports,o,o.exports,n),o.l=!0,o.exports}n.m=e,n.c=t,n.d=function(e,t,r){n.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:r})},n.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},n.t=function(e,t){if(1&t&&(e=n(e)),8&t)return e;if(4&t&&"object"==typeof e&&e&&e.__esModule)return e;var r=Object.create(null);if(n.r(r),Object.defineProperty(r,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var o in e)n.d(r,o,function(t){return e[t]}.bind(null,o));return r},n.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return n.d(t,"a",t),t},n.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},n.p="/wp-content/themes/nexstar-wv/client/build/",n(n.s=308)}({107:function(e,t,n){"use strict";t.a=function(){window.googletag=window.googletag||{},window.googletag.cmd=googletag.cmd||[]}},308:function(e,t,n){e.exports=n(790)},790:function(e,t,n){"use strict";n.r(t);var r=n(107);function o(e,t){for(var n=0;n<t.length;n++){var r=t[n];r.enumerable=r.enumerable||!1,r.configurable=!0,"value"in r&&(r.writable=!0),Object.defineProperty(e,r.key,r)}}var i=function(){function e(){var t=this;!function(e,t){if(!(e instanceof t))throw new TypeError("Cannot call a class as a function")}(this,e),this.observer=null,this.watched={},this.paused={},this.maxRefreshes=9,this.refreshCounter={},window.addEventListener("focus",(function(){t.resumeAllTimers()})),window.addEventListener("blur",(function(){t.pauseAllTimers()})),this.observer=new IntersectionObserver((function(e){t.callback(e)}),{root:null,rootMargin:"0px",threshold:[.3,.5]})}var t,n,r;return t=e,(n=[{key:"callback",value:function(e){var t=this;e.forEach((function(e){var n=e.target.id;if(n in t.watched){var r=t.watched[n];e.isIntersecting&&e.intersectionRatio>=r.ratio?null===r.timerId&&(r.timerId=setTimeout((function(){document.hidden?t.clearTimer(n):(t.stopWatching(n),t.refreshCounter[n]+=1,window.dispatchEvent(new CustomEvent("nsDfpRefreshSingleSlot",{detail:{slotElementId:n}})))}),1e3*r.refreshSecs)):t.clearTimer(n)}}))}},{key:"startWatching",value:function(e,t,n,r){this.watched[e]={ratio:n,timerId:null,node:t,refreshSecs:r},this.observer.observe(t)}},{key:"stopWatching",value:function(e){var t=this.watched[e];clearTimeout(t.timerId),delete this.watched[e],this.observer.unobserve(t.node)}},{key:"clearTimer",value:function(e){var t=this.watched[e];clearTimeout(t.timerId),t.timerId=null}},{key:"observe",value:function(e,t){if(!(5>t||(e in this.refreshCounter||(this.refreshCounter[e]=0),this.refreshCounter[e]>=this.maxRefreshes))){var n=document.getElementById(e);if(n){var r=242e3<n.clientWidth*n.clientHeight?.3:.5;this.startWatching(e,n,r,t)}}}},{key:"pauseAllTimers",value:function(){var e=this;Object.keys(this.watched).forEach((function(t){e.paused[t]=e.watched[t],e.stopWatching(t)}))}},{key:"resumeAllTimers",value:function(){var e=this;Object.keys(this.paused).forEach((function(t){var n=e.paused[t],r=n.node,o=n.ratio,i=n.refreshSecs;e.startWatching(t,r,o,i),delete e.paused[t]}))}}])&&o(t.prototype,n),r&&o(t,r),e}();Object(r.a)();var a=new i;googletag.cmd.push((function(){var e=function(e,t,n){var r;try{r=e.slot[t].apply(e.slot,n)}catch(e){r="[unknown]"}return r},t=function(){var e=window.innerWidth||document.documentElement.clientWidth,t="mobile";768<e&&(t="tablet"),1024<e&&(t="desktop");var n=googletag.pubads().getTargeting("pagetype");return 1===n.length&&["index","subindex","story","mlite"].includes(n[0])||(n="other"),function(e,r){if(window.isAdRefreshEnabled&&window.adExclusionIds.length&&!window.adExclusionIds.includes(r)){var o,i=e.getTargeting("pos"),a=[n,i,t].join("/");return null!==(o=window.adRefreshConfig[a])&&void 0!==o&&o}return!1}}();googletag.pubads().addEventListener("slotRenderEnded",(function(n){if(n.slot){var r=n.slot,o=n.isEmpty,i=n.size,s=n.lineItemId,c=r.getSlotElementId(),d="NA";window.isAdSponsorshipEnabled&&(d=window.adExclusionIds.includes(s));var u=r.getTargeting("ad_rendercount"),l="AD SLOT RENDERED {\n  containerId: ".concat(c,",\n  isEmpty: ").concat(o,",\n  size: ").concat(i,",\n  adUnitPath: ").concat(e(n,"getAdUnitPath"),",\n  position: ").concat(e(n,"getTargeting",["pos"]),",\n  lineItemId: ").concat(s,", sponsorship=").concat(d,",\n  renderCount: ").concat(u,"\n}");if(window.setTimeout((function(){console.info(l)}),10),c.startsWith("acm-ad-tag-adhesion")&&!o){var f=document.getElementById(c).parentNode;f.classList.remove("pre-render"),f.parentNode.classList.remove("pre-render"),f.parentNode.querySelector(".close-btn-container").addEventListener("click",(function(e){e.preventDefault(),f.parentNode.remove()}),!1)}if(c.startsWith("acm-ad-tag-adhesion-adhesion")&&!o){var h=document.getElementById(c).parentNode,v=document.querySelector(".close-btn-container--mobile");v&&v.addEventListener("click",(function(){h.parentNode.remove()}),!1)}if(c.startsWith("acm-ad-tag-oop")&&!o&&document.body.classList.add("has-loaded-super-billboard-ad"),c&&!o&&i&&"function"==typeof document.getElementById(c).closest){var g=document.getElementById(c).closest(".ad-unit");if(g){var m=g.querySelector(".ad-unit__content > div[id^=acm]");if(m){var p=i[0],b=void 0===p?null:p,w=i[1],y=void 0===w?null:w;b&&y&&(m.setAttribute("width",b),m.setAttribute("height",y))}g.classList.add("ad-unit--is-rendered")}}var E=t(r,s);0<E&&a.observe(c,E)}}))}))}});
//# sourceMappingURL=ad-handler.bundle.min.js.map</script><link rel='stylesheet' id='nxst-vd-ovp-styles-css' href='https://www.kron4.com/wp-content/plugins/nxst-video-delivery/client/ovp/build/css/main.min.css?ver=1755197989' media='all' />
<script type="text/javascript" id="nexstar/login-registration/scripts/login/js-js-extra">
/* <![CDATA[ */
var login_registration = {"rest_urls":{"startSiteProcess":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/start-site-process","start_process":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/start-process","trusted_token_refresh":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/trusted-token-refresh","refresh_token":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/refresh-token","start_process_roku":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/start-process-roku","device":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/device","device\/token":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/device\/token","device\/validate":"https:\/\/www.kron4.com\/wp-json\/nxs-auth\/v1\/device\/validate"},"lr_api_key":"2dbf456e-d413-4246-8534-4571d5c9d35b","lr_sdk_app_name":"nexstar","app_to_app_key":"app-to-app-fHYbZC8qAqMVjvGk","cookie_name":"lr_access_token","debug_mode":"","sso_enabled":"on","sso_login_url":"https:\/\/my.nexstar.tv\/ssologin\/login","sso_set_token_url":"https:\/\/my.nexstar.tv\/ssologin\/setToken","magic_link_type":"passwordlesslogin","validation_timeout":"100","cookie_expiry_days":"90","start_site_process_nonce":"f1dae4d96a","home_url":"https:\/\/www.kron4.com","verification_url":"https:\/\/www.kron4.com","refresh_token_days_before_expiry":"7","refresh_token_enabled":"on","login_response_message_page_path":"\/login-response-message"};
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/login-registration/build/login-registration.e6cba00adbf619d2977e.js?ver=e6cba00adbf619d2977e" id="nexstar/login-registration/scripts/login/js-js" data-wp-strategy="defer"></script>
<script type="text/javascript" id="nexstar/login-registration/scripts/login/js-js-after">
/* <![CDATA[ */
window.NEXSTAR_LOGIN_REGISTRATION_SETTINGS = {"eventType":"nexstar\/login-registration\/status"};
/* ]]> */
</script>
<script type="text/javascript" id="nswv-common-js-js-extra">
/* <![CDATA[ */
var lakana = {"a9":{"aps":{"enabled":"1","deals":"1","pub_id":"3410"}},"ad_platforms":{"htlbid_network_enabled":"1","magnite_network_enabled":"0","magnite_url":"https:\/\/micro.rubiconproject.com\/prebid\/dynamic\/10043.js"},"ad_referral_source":{"social_sites":"12seconds.tv,\n4travel.jp,\nadvogato.org,\nameba.jp,\nanobii.com,\nanswers.yahoo.com,\nasmallworld.net,\navforums.com,\nbadoo.com,\nbebo.com,\nbiip.no,\nblackplanet.com,\nblog.seesaa.jp,\nblogspot.com,\nblomotion.jp,\nboards.qwant.com,\nbolt.com,\nbrightkite.com,\nbuzznet.com,\ncafemom.com,\ncare2.com,\nclassmates.com,\ncyworld.co.kr,\ndailymotion.com,\ndelicious.com,\ndeviantart.com,\ndigg.com,\ndiigo.com,\ndisqus.com,\ndraugiem.lv,\nl.facebook.com,\nwww.facebook.com,\nfaceparty.com,\nfc2.com,\nflickr.com,\nfotolog.com,\nfoursquare.com,\nfriendfeed.com,\nfriendsreunited.com,\nfubar.com,\ngaiaonline.com,\ngeni.com,\ngoodreads.com,\nplus.google.com,\ngrono.net,\nhabbo.com,\nhatena.ne.jp,\nhi5.com,\nhyves.nl,\nibibo.com,\nidenti.ca,\nt.ifeng.com,\ninstagram.com,\nintensedebate.com,\nirc-galleria.net,\njp.myspace.com,\nkaixin001.com,\nkakaku.com,\nlast.fm,\nwww.linkedin.com,\nlivejournal.com,\nlnkd.in,\nmeetup.com,\nmister-wong.com,\nmixi.jp,\nmixx.com,\nmouthshut.com,\nmp.weixin.qq.com,\nmultiply.com,\nmumsnet.com,\nmyheritage.com,\nmyspace.com,\nnasza-klasa.pl,\nmatome.naver.jp,\nnetlog.com,\nnetvibes.com,\nnextdoor.com,\nnicovideo.jp,\nning.com,\nodnoklassniki.ru,\nok.ru,\norkut.com,\npakila.jp,\nphotobucket.com,\npinterest.com,\npinterest.co.uk,\npinterest.ca,\npinterest.fr,\npinterest.es,\npinterest.de,\npinterest.se,\npinterest.pt,\npinterest.dk,\npinterest.ie,\npinterest.co.kr,\npinterest.ch,\npinterest.at,\npinterest.nz,\npinterest.ph,\npinterest.cl,\npinterest.hu,\npinterest.be,\npinterest.in,\npinterest.co,\nplurk.com,\npo.st,\nreddit.com,\nrenren.com,\nskyrock.com,\nslideshare.net,\nsmcb.jp,\nsmugmug.com,\nsnapchat.com,\nstumbleupon.com,\nt.co,\nt.ifeng.com,\nt.sina.com.cn,\nt.sohu.com,\ntabelog.com,\ntagged.com,\ntaringa.net,\nthefancy.com,\ntiktok.com,\ntoutiao.com,\ntripit.com,\ntrombi.com,\ntrytrend.jp,\ntumblr.com,\ntwitter.com,\nuhuru.jp,\nviadeo.com,\nvimeo.com,\nvk.com,\nwayn.com,\nweibo.com,\nwordpress.com,\nxanga.com,\nxing.com,\nanswers.yahoo.com,\nyammer.com,\nyaplog.jp,\nyelp.com,\nyelp.co.uk,\nyouku.com,\nyoutube.com,\nyozm.daum.net,\nyuku.com,\nzooomr.com,\nzhihu.com,\nm.badoo.com,\nm.blogspot.com,\nm.brightkite.com,\nm.classmates.com,\nm.cyworld.co.kr,\nm.dailymotion.com,\nm.deviantart.com,\nm.diigo.com,\nm.disqus.com,\nm.draugiem.lv,\nm.facebook.com,\nm.flickr.com,\nm.foursquare.com,\nm.fubar.com,\nm.gaiaonline.com,\nm.plus.google.com,\nm.hatena.ne.jp,\nm.hi5.com,\nm.ibibo.com,\nm.ifeng.com,\nm.instagram.com,\nm.irc-galleria.net,\nm.kaixin001.com,\nm.last.fm,\nm.linkedin.com,\nm.livejournal.com,\nm.mixi.jp,\nm.mixx.com,\nm.mouthshut.com,\nm.myheritage.com,\nm.mylife.com,\nm.myspace.com,\nm.nasza-klasa.pl,\nm.odnoklassniki.ru,\nm.ok.ru,\nm.reddit.com,\nm.renren.com,\nm.slideshare.net,\nm.smugmug.com,\nm.co,\nm.ifeng.com,\nm.qq.com,\nm.sina.com.cn,\nm.sohu.com,\nm.tagged.com,\nm.taringa.net,\nm.tiktok.com,\nm.toutiao.com,\nm.tripit.com,\nm.tumblr.com,\nm.twitter.com,\nm.vk.com,\nm.weibo.com,\nm.wordpress.com,\nm.xanga.com,\nm.xing.com,\nm.answers.yahoo.com,\nm.youku.com,\nm.youtube.com,\nm.yuku.com,\nm.zhihu.com,\nwww.12seconds.tv,\nwww.advogato.org,\nwww.anobii.com,\nwww.answers.yahoo.com,\nwww.asmallworld.net,\nwww.avforums.com,\nwww.badoo.com,\nwww.bebo.com,\nwww.blackplanet.com,\nwww.blogspot.com,\nwww.bolt.com,\nwww.brightkite.com,\nwww.buzznet.com,\nwww.cafemom.com,\nwww.care2.com,\nwww.classmates.com,\nwww.cyworld.co.kr,\nwww.dailymotion.com,\nwww.delicious.com,\nwww.deviantart.com,\nwww.digg.com,\nwww.diigo.com,\nwww.disqus.com,\nwww.draugiem.lv,\nwww.faceparty.com,\nwww.fc2.com,\nwww.flickr.com,\nwww.flixster.com,\nwww.fotolog.com,\nwww.foursquare.com,\nwww.friendsreunited.com,\nwww.fubar.com,\nwww.gaiaonline.com,\nwww.goodreads.com,\nwww.plus.google.com,\nwww.grono.net,\nwww.habbo.com,\nwww.hatena.ne.jp,\nwww.hi5.com,\nwww.hyves.nl,\nwww.ibibo.com,\nwww.identi.ca,\nwww.instagram.com,\nwww.intensedebate.com,\nwww.kaixin001.com,\nwww.kakaku.com,\nwww.last.fm,\nwww.livejournal.com,\nwww.meetup.com,\nwww.mister-wong.com,\nwww.mixi.jp,\nwww.mixx.com,\nwww.mouthshut.com,\nwww.multiply.com,\nwww.mumsnet.com,\nwww.myheritage.com,\nwww.myspace.com,\nwww.nasza-klasa.pl,\nwww.netlog.com,\nwww.netvibes.com,\nwww.nextdoor.com,\nwww.nicovideo.jp,\nwww.ning.com,\nwww.odnoklassniki.ru,\nwww.ok.ru,\nwww.orkut.com,\nwww.photobucket.com,\nwww.pinterest.com,\nwww.pinterest.co.uk,\nwww.pinterest.ca,\nwww.pinterest.fr,\nwww.pinterest.es,\nwww.pinterest.de,\nwww.pinterest.se,\nwww.pinterest.pt,\nwww.pinterest.dk,\nwww.pinterest.ie,\nwww.pinterest.co.kr,\nwww.pinterest.ch,\nwww.pinterest.at,\nwww.pinterest.nz,\nwww.pinterest.ph,\nwww.pinterest.cl,\nwww.pinterest.hu,\nwww.pinterest.be,\nwww.pinterest.in,\nwww.pinterest.co,\nwww.plurk.com,\nwww.po.st,\nwww.reddit.com,\nwww.renren.com,\nwww.skyrock.com,\nwww.slideshare.net,\nwww.smugmug.com,\nwww.snapchat.com,\nwww.stumbleupon.com,\nwww.t.ifeng.com,\nwww.tabelog.com,\nwww.tagged.com,\nwww.taringa.net,\nwww.thefancy.com,\nwww.tiktok.com,\nwww.toutiao.com,\nwww.tripit.com,\nwww.trombi.com,\nwww.tumblr.com,\nwww.twitter.com,\nwww.uhuru.jp,\nwww.viadeo.com,\nwww.vimeo.com,\nwww.vk.com,\nwww.wayn.com,\nwww.weibo.com,\nwww.wordpress.com,\nwww.xanga.com,\nwww.xing.com,\nwww.answers.yahoo.com,\nwww.yammer.com,\nwww.youku.com,\nwww.youtube.com,\nwww.zooomr.com,\nwww.zhihu.com,"},"adobe_analytics":{"enabled":"1","launch_library":"https:\/\/assets.adobedtm.com\/3f27c430a962\/d33d8acd711c\/launch-25e943fdd407.min.js","analytics_script":"https:\/\/segment.psg.nexstardigital.net\/adobeanalytics.js","tracking_server":"nexstar.data.adobedc.net","report_suite_id":"nexstarglobalprod","newsbreak_launch_library":"https:\/\/assets.adobedtm.com\/3f27c430a962\/0852aae22492\/launch-43352a2f5f64.min.js","media_edge_path":"https:\/\/edge.adobedc.net\/ee\/va\/v1\/","media_session_datastream_id":"2d3a9df0-344f-464e-8b3c-79141641d86e","ecid_from_adobe_demdex_endpoint":"https:\/\/dpm.demdex.net\/id?d_fieldgroup=MC&d_rtbd=json&d_ver=2&d_orgid=19020C7354766EB60A4C98A4@AdobeOrg","adobe_org_identity_cookie_name":"kndctr_19020C7354766EB60A4C98A4_AdobeOrg_identity"},"advertising":{"lazyload_status":"1","refresh_status":"1","lineitems_url":"https:\/\/htlbid.com\/v3\/nexstardigital.com\/lineitems.json"},"alert_types_switcher":{"enabled":"0"},"archive_widget_form":{"total_archive_widgets":"100"},"auto_refresh":{"landing_duration":"10","disable_homepage":"0"},"blimply":{"enabled":"0"},"blockthrough":{"enabled":"0"},"blueconic_enabled":"1","blueconic_prebid":{"publisher_id":"","status":"1"},"branding":{"footer_copyright":"\u00a9 1998 - [year] Nexstar Media Inc. | All Rights Reserved."},"browsi":{"enabled":"1","script_url":"https:\/\/cdn.browsiprod.com\/bootstrap\/bootstrap.js"},"civicscience":{"enabled":"1","below_post_placement":"1","survey_404_pages":"1","civic_science_keys":{"404_survey_id":"civsci-id-970186143","404_widget_id":"29244b88-4a11-6284-b57b-1b64cf8a9cbd","article_survey_id":"2122639739","article_widget_id":"82d19ca8-4f30-60f4-2562-28d5394c0c93","sidebar_survey_id":"304165588","sidebar_widget_id":"d570cf89-d697-0844-8df3-6f5daee77194"},"article_ad_unit":{"display_in_article_body":"1","ad_position_name":"mr3_ab","article_body_survey_id":"civsci-id-305934525","article_body_widget_id":"3f127ebd-287e-0b64-a901-d55ec286348a"}},"confiant":{"enabled":"1"},"copyright_text":"Copyright 2025 Nexstar Media Inc. All rights reserved. This material may not be published, broadcast, rewritten, or redistributed.","devcon":{"data_key":"31b9b552-f32e-4036-8364-726eb992b71d","status":"1","data_e":"5"},"freewheel":{"video_ad_tag":{"network_status":"1"},"mrm_pixel":{"network_status":"1"}},"gdpr_prebid_settings":{"enable":"1"},"gtm":{"id":"GTM-KJJZHXD"},"id":"1","index_exchange":{"script_url":""},"jetpack_form_autodeletion":{"days_autodelete":""},"liveblog":{"liveblog_ads":"0"},"liveblog_customization":{"schema":{"status_enable_custom_schema":"0"}},"liveramp":{"pid":"1262","prebid_status":"1","prebid_analytics_status":"1","ats_status":"1","ats_version":"2"},"login_page":{"status_password_reset_links_to_current_site":"0"},"magnite":{"pixel":{"network_status":"1"}},"nativo_enabled":"1","nativo_rewrite":{"nativo_rewrite_rule":"^sponsor-content(.*)?$","nativo_rewrite_path":""},"optimera":{"client_id":"67","status":"0"},"pair_id":{"status":"1"},"prebid":{"status":"1","script_url":"https:\/\/www.nxsttv.com\/wp-content\/themes\/nexstar\/client\/vendors\/prebid\/versions\/pbjs-7.46.0-20230523.js","video_status":"1"},"prebid_server":{"status":"1","amp_sync_pixel_status":"0"},"retrans":{"status":"1","api_url":"https:\/\/keepmystation.com\/"},"schema_org":{"video":"1"},"segment":{"segment_script_url":"https:\/\/segment.psg.nexstardigital.net\/segment.js","anvato_script_url":"https:\/\/segment.psg.nexstardigital.net\/anvato.js","newsbreak_script_url":"https:\/\/segment.psg.nexstardigital.net\/newsbreak.js","smartnews_script_url":"","segment_calls":"0","status":"1"},"send_to_news":{"enabled":"1"},"sign_up_link":{"enable":"1"},"site_footer":{"secondary_footer":[{"title":"Privacy Policy","onetrust_button":"0","link":"https:\/\/www.nexstar.tv\/privacy-policy\/","link_target":"_blank"},{"title":"Terms Of Use","onetrust_button":"0","link":"https:\/\/www.nexstar.tv\/terms-of-use\/","link_target":"_blank"},{"title":"FCC Applications","onetrust_button":"0","link":"https:\/\/www.nexstar.tv\/fcc-applications\/","link_target":"_blank"},{"title":"Public File Assistance Contact","onetrust_button":"0","link":"[home-url]\/contact-us"},{"title":"Onesignal Desktop","onetrust_button":"0","link":"[onesignal-custom-link]"},{"title":"The Hill","onetrust_button":"0","link":"https:\/\/www.thehill.com\/"},{"title":"NewsNation","onetrust_button":"0","link":"https:\/\/www.newsnationnow.com\/"},{"title":"BestReviews","onetrust_button":"0","link":"https:\/\/www.bestreviews.com\/"},{"title":"Content Licensing","onetrust_button":"0","link":"https:\/\/www.newsnationnow.com\/licensing-nexstars-local-and-national-television-news-footage\/"},{"title":"Nexstar Digital","onetrust_button":"0","link":"https:\/\/www.nexstardigital.com\/"},{"title":"Journalistic Integrity","onetrust_button":"0","link":"https:\/\/www.nexstar.tv\/corporate-social-responsibility\/journalistic-integrity\/"},{"title":"Sitemap","onetrust_button":"0","link":"[home-url]\/sitemap\/"}]},"springserve":{"pixel":{"network_status":"1"}},"taboola":{"enabled":"1","mobile_enabled":"1"},"teads":{"enabled":"0"},"uuid":"a6289d30-8810-420f-b327-035e1320873a","warning-edit-shared":{"wes_dialog_message":"","wes_acknowledgement":""},"wsi":{"cid":"878507589"},"external_partner_xml":{"external_partners":{"show_divider":0}},"privacy_policy":{"last_updated_date":"09\/30\/2025"}};
var nexstar = {"a9":{"status":"1","video_status":"1"},"adobe_analytics":{"enabled":"1","launch_library":"","media_edge_path":"","media_session_datastream_id":""},"advertising":{"refresh_status":"1","lazyload_status":"0"},"alert_banners":{"l10n":{"nexstar":{"label_sep":"\/"}},"settings":{"Watch Now":{"id":13001,"slug":"watch-now","term_name":"Watch Now","label":"Watch Now","color":"","background":"","summary_only":false,"url":"#","view_options":"number_of_areas","truncate":true,"location":"header","supports_custom_banner_image":false},"Weather Alerts":{"id":18,"slug":"weather-alerts","term_name":"Weather Alerts","label":"Weather Alerts","color":"","background":"","summary_only":false,"url":"https:\/\/www.kron4.com\/weather\/weather-alerts\/","view_options":"number_of_areas","truncate":true,"location":"header","supports_custom_banner_image":false},"Custom":{"id":12331,"slug":"custom","term_name":"Custom","label":"Programming Note","color":"#ffffff","background":"#dd3333","summary_only":false,"url":"https:\/\/www.kron4.com\/","view_options":"number_of_areas","truncate":true,"location":"header","supports_custom_banner_image":true},"Live Now":{"id":17,"slug":"live-now","term_name":"Live Now","label":"Live","color":"","background":"","summary_only":false,"url":"https:\/\/www.kron4.com\/","view_options":"number_of_areas","truncate":true,"location":"header","supports_custom_banner_image":true},"Breaking News":{"id":16,"slug":"breaking-news","term_name":"Breaking News","label":"BREAKING","color":"","background":"","summary_only":false,"url":"https:\/\/www.kron4.com\/","view_options":"number_of_areas","truncate":false,"location":"header","supports_custom_banner_image":false},"Closings":{"id":10007,"slug":"closings","term_name":"Closings","label":"Closings","color":"","background":"","summary_only":false,"url":"#","view_options":"number_of_areas","truncate":true,"location":"header","supports_custom_banner_image":false}},"is_dismissing_allowed":false,"message_dismissal_duration":43200,"message_dismissal_storage":"persistent"},"amp_publisher_logo":"","app_links":{"google_play_link":"https:\/\/play.google.com\/store\/apps\/details?id=com.nexstar.id3542","google_play_weather_link":"","ios_app_store_link":"https:\/\/itunes.apple.com\/us\/app\/kron-4\/id472672814","ios_app_store_weather_link":""},"article_bins":{"rest_endpoint":"https:\/\/www.kron4.com\/wp-json\/nexstar\/v1\/article-bin"},"auto_refresh":{"landing_duration":"60","disable_homepage":"0"},"bestreviews_widget_script":{"status":"0"},"blimply":{"disabled":"1"},"blockthrough":{"enabled":"1"},"blueconic_enabled":"1","blueconic_prebid":{"status":"0"},"blueconic_script_url":"https:\/\/blue.kron4.com\/script.js","branded_logo":"0","branded_logo_link":"","browsi":{"enabled":"1","script_id":"browsi-tag","script_pubKey":"nexstar","script_siteKey":"d_mapping","device_types":{"is_desktop":"0","is_tablet":"0","is_phone":"1"},"page_types":{"home page":"0","category":"0","article":"1"}},"call_letters":"KRON","civicscience":{"enabled":"1","right_rail_survey_categories":"1","survey_404_pages":"1","right_rail_survey_posts":"1","content_sources":{"local_market":"1","nexstar_media_wire":"1","associated_press":"1"},"civic_science_keys":{"404_survey_id":"1255967315","404_widget_id":"29244b88-4a11-6284-b57b-1b64cf8a9cbd","article_survey_id":"","article_widget_id":"","sidebar_survey_id":"","sidebar_widget_id":""},"article_ad_unit":{"display_in_article_body":"1","ad_position_name":"mr3_ab","article_body_survey_id":"","article_body_widget_id":""}},"confiant":{"script_url":"https:\/\/cdn.confiant-integrations.net\/Y2Nn8JmiAY8HpnF4sl5n7J71jaI\/gpt_and_prebid\/config.js","enabled":"1"},"continue_reading_cta":{"l10n":{"cta_text":"Continue Reading"},"breakpoint":768,"min_content_height":250},"copyright_start_year":"1998","copyright_string":"","dd_dcript_status":{"plugin_status":"0","remove_from_sharing":"1"},"devcon":{"status":"1"},"dfp":{"mobile_desktop_breakpoint":1024,"desktop_breakpoint":900,"register_event":"nsDfpSlotRendered","slots":{"adhesion":{"pos":"adhesion","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[320,50],"sizes":[[[1280,0],[[728,90]]],[[1024,0],[[728,90]]],[[768,0],[[728,90]]],[[480,0],[[320,50]]],[[0,0],[[320,50]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=4b4db8ee-1eaf-45fb-be0f-1a2d85428cbd&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"billboard1":{"pos":"billboard1","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[320,50],"sizes":[[[1280,0],[[728,90],[970,250],[970,90],[970,30]]],[[1024,0],[[728,90],[970,250],[970,90],[970,30]]],[[768,0],[[320,50]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=d7e681ab-b513-4d27-a0b8-5aa5c65aafae&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"billboard_sticky":{"pos":"billboard_sticky","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[320,50],"sizes":[[[1280,0],[[728,90],[970,90]]],[[1024,0],[[728,90],[970,90]]],[[768,0],[[320,50]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"exit":{"pos":"exit","is_companion":true,"is_oop":true,"refresh_on_resize":true,"size":[2,2],"sizes":[[[0,0],[[2,2]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"header-microbar":{"pos":"header-microbar","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[88,31],"sizes":[[[900,0],[[88,31]]],[[0,0],[]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"hover":{"pos":"hover","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[1,1],"sizes":[[[900,0],[[1,1]]],[[0,0],[]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"interstitial":{"pos":"interstitial","is_companion":true,"is_oop":true,"refresh_on_resize":true,"size":[300,250],"sizes":[[[0,0],[[300,250],[320,480],[336,280]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"leader_mr1":{"pos":"leader_mr1","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1152,0],[[728,90]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"btf"},"leader_mr2":{"pos":"leader_mr2","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1152,0],[[728,90]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"btf"},"leader_mr3":{"pos":"leader_mr3","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1152,0],[[728,90]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"btf"},"leader_mr4":{"pos":"leader_mr4","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1152,0],[[728,90]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"btf"},"leaderboard1":{"pos":"leaderboard1","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[320,50],"sizes":[[[1280,0],[[728,90]]],[[1024,0],[[728,90]]],[[768,0],[[728,90]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid"},"leaderboard2":{"pos":"leaderboard2","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[320,50],"sizes":[[[1280,0],[[728,90]]],[[1024,0],[[728,90]]],[[768,0],[[728,90]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid"},"leaderboard3":{"pos":"leaderboard3","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[320,50],"sizes":[[[1280,0],[[728,90],[970,250]]],[[1024,0],[[728,90],[970,250]]],[[768,0],[[728,90]]],[[641,0],[[320,50]]],[[0,0],[[320,50]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"btf"},"microbar":{"pos":"microbar","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[88,31],"sizes":[[[0,0],[[88,31]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid"},"mr0_ab":{"pos":"mr0_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr1":{"pos":"mr1","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250]]],[[1024,0],[[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=ce88e407-8ae9-4f59-9439-830fc34a4634&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"mr10_ab":{"pos":"mr10_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr11_ab":{"pos":"mr11_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr12_ab":{"pos":"mr12_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr13_ab":{"pos":"mr13_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr14_ab":{"pos":"mr14_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr15_ab":{"pos":"mr15_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr1_ab":{"pos":"mr1_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=38bb6819-8b59-4218-b593-1c8539262e10&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"mr1_mobile":{"pos":"mr1_mobile","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[900,0],[]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr2":{"pos":"mr2","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250]]],[[1024,0],[[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=cce3eaba-ad9f-41f8-a399-abcbce06954a&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"mr2_ab":{"pos":"mr2_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=cebdd7dc-2a05-4712-aade-bffbac51ea8d&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"mr3":{"pos":"mr3","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250]]],[[1024,0],[[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid"},"mr3_ab":{"pos":"mr3_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=30082404-c2e9-4c08-8021-93226f7ffe5f&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"mr4":{"pos":"mr4","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250]]],[[1024,0],[[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"mid"},"mr4_ab":{"pos":"mr4_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf","amp_rtc_urls":["https:\/\/amspbs.com\/openrtb2\/amp?tag_id=a430b18b-ff9b-4bda-984e-d57c4c7b2ac2&w=ATTR(width)&h=ATTR(height)&ms=ATTR(data-multi-size)&oh=ATTR(data-override-height)&ow=ATTR(data-override-width)&curl=CANONICAL_URL&slot=ATTR(data-slot)&timeout=TIMEOUT&targeting=TGT&consent_string=CONSENT_STRING&consent_type=CONSENT_METADATA(consentStringType)&gdpr_applies=CONSENT_METADATA(gdprApplies)&addtl_consent=CONSENT_METADATA(additionalConsent)"]},"mr5_ab":{"pos":"mr5_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr6_ab":{"pos":"mr6_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr7_ab":{"pos":"mr7_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr8_ab":{"pos":"mr8_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr9_ab":{"pos":"mr9_ab","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,250],[620,366]]],[[1024,0],[[300,250],[620,366]]],[[768,0],[[300,250],[325,204],[325,508]]],[[641,0],[[300,250],[325,204],[325,508]]],[[0,0],[[300,250],[325,204],[325,508]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr_combo1":{"pos":"mr_combo1","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,600],[300,250]]],[[1024,0],[[300,600],[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"mr_combo2":{"pos":"mr_combo2","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[300,250],"sizes":[[[1280,0],[[300,600],[300,250]]],[[1024,0],[[300,600],[300,250]]],[[768,0],[[300,250]]],[[641,0],[[300,250]]],[[0,0],[[300,250]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"btf"},"oop":{"pos":"oop","is_companion":true,"is_oop":true,"refresh_on_resize":true,"size":[1,1],"sizes":[[[0,0],[[1,1]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"},"sponsored":{"pos":"sponsored","is_companion":true,"is_oop":false,"refresh_on_resize":true,"size":[232,232],"sizes":[[[0,0],[[232,232]]]],"amp_multi_size":"","lazyload":false,"wx_targeting":[],"module_refreshable":false,"fold":"atf"}},"ab_test":{"min":1,"max":101,"storage_key":"ns.gpt.sessiontest"}},"extended_scroll":{"l10n":{"top_stories_title":"Top Stories","more_in_category_read_more":"Read the Full Article","more_in_category_title":"More Stories","more_stories_read_more":"Read more stories","more_stories_title":"More Stories"},"default_provider":"queried_object","max_blocks_per_snippet":2,"max_words_fallback_per_snippet":70,"num_top_stories_posts":20,"num_more_in_category_posts":0,"more_in_category_fields":["title","link","snippet","thumbnail","authors","date","read_more"],"num_more_stories_posts":8,"show_read_more_in_more_stories":true,"more_stories_read_more_link":"\/news\/","more_stories_fields":["title","thumbnail","articles"]},"footer_logo":"2132954","freewheel":{"video_ad_tag":{"video_ad_tag_url":"","slot_definitions":"","status":""},"amp":{"prevent_continuous_play":false},"mrm_pixel":{"status":"0","img_pixel_src":""}},"ga":{"id":""},"gtm":{"id":"GTM-KNNPZPH"},"home_url":"https:\/\/www.kron4.com\/","homepage":{"l10n":{"all_headlines_title":"All Headlines","hero_title":"Headlines","hero_read_more_title":"More Top Stories","headline_list_read_more_title":"View All %s","top_stories_title":"Top Stories","top_stories_read_more_title":"More Top Stories","top_story_label":"Top Story","watch":"Watch"},"default_hero_read_more_link":"https:\/\/www.kron4.com\/news\/","num_all_headlines_list_articles":6,"num_headline_lists":6,"num_headline_list_articles":5,"num_hero_articles":1,"num_top_stories_articles":6,"num_additional_top_stories_articles":0,"top_stories_articles_fields":["id","title","link","link_target","category","thumbnail","date_relative"],"top_stories_read_more_link":"https:\/\/www.kron4.com\/news\/","num_timeline_stories_articles":6,"num_topics_tabs":7,"num_shows_tabs":10,"topics_tabs_stack_until_bp":900,"num_articles_per_tab":3},"id":"11","lead_media":{"allowed_block_types":["core\/audio","core\/shortcode","lakana\/anvplayer","jetpack\/slideshow"],"video":{"autoplay":"1"}},"liveblog":{"liveblog_ads":"0"},"liveramp":{"prebid_status":"1","prebid_analytics_status":"1","ats_status":"1"},"logo":"2132954","magnite":{"pixel":{"status":"0","img_pixel_src":""}},"mobile_settings":{"read_more":"0"},"name":"KRON4","nativo_enabled":"1","navigation_background_image":"","navigation_background_image_mobile":"","nexstar_id":{"blueconic_deprioritization":"1","amp_uuid":"0","nexstar_id_script_url":"https:\/\/nxst.megpxs.com\/ndn.js"},"nielsen":{"app_id":"P4D4F9915-E46E-4B58-BCA6-DE3D1F253081","apn":"Anvato","sfcode":"dcr"},"nota_plugin_status":{"status":"1"},"nxst_hook_sniffer_plugin_status":{"status":"0"},"nxstory":{"enabled":"1"},"onesignal":{"enabled":"1","sdk_script_url":"https:\/\/cdn.onesignal.com\/sdks\/OneSignalSDK.js"},"onesignal_app":{"enabled":"1"},"optimera":{"status":"1"},"overwrite_copyright_text":{"value":""},"pair_id":{"status":"1"},"parent_call_letters":"KRON","permutive":{"enabled":"1","prebid_enabled":"0"},"prebid":{"status":"1","video_status":"0"},"prebid_server":{"status":"1","amp_sync_pixel_status":"0"},"primary_color":"#7d0200","redirect_guess_404":{"disable_guess_404":"0"},"related_posts":{"l10n":{"default_title":"Related Content"}},"retrans":{"status":"1"},"safe_redirect_manager":{"allowed_redirects":250},"section_fronts":{"l10n":{"headlines":"Headlines","more_headlines_title":"View All %s","top_stories_title":"Top Stories","watch":"Watch"},"default_provider":"queried_object","hero_read_more_link":"https:\/\/www.kron4.com\/news\/","num_headline_list_articles":6,"num_headline_lists":6,"num_hero_pages":1,"num_ranked_articles_per_page":7,"num_top_stories_pages":7,"top_stories_read_more_link":"https:\/\/www.kron4.com\/news\/","num_first_headline_list_articles":8,"num_last_headline_list_articles":10},"segment":{"segment_key":"o","segment_key_amp":"x","status":"1"},"send_to_news":{"url":"http:\/\/embed.sendtonews.com\/oembed\/?fk=63shfrMa&cid=6836&sound=off&format=json&offsetx=0&offsety=140&floatwidth=400&floatposition=top-right&float=on","enabled":"0"},"sidebar":{"l10n":{"dont_miss_title":"Don't Miss"},"num_dont_miss_articles":5},"sign_up_link":{"enable":"1","link":"https:\/\/nxslink.kron4.com\/join\/6p6\/signup?website_signup=true"},"social_links":{"email":"BreakingNews@kron4.com","facebook":"https:\/\/www.facebook.com\/KRON4\/","haystack":"https:\/\/www.haystack.tv\/channel\/kron\/","instagram":"https:\/\/www.instagram.com\/kron4tv\/","pinterest":"","rss":"https:\/\/www.kron4.com\/news\/app-feed","twitter":"https:\/\/www.twitter.com\/kron4news\/","youtube":"https:\/\/www.youtube.com\/channel\/UCVWQWc8PXy6Itt7YNrivOYw"},"springserve":{"pixel":{"status":"0","img_pixel_src":""}},"stationsite_ad_unit":{"ad_unit":""},"supernav":{"l10n":{"close_navigation":"Close Navigation","open_navigation":"Open Navigation","looking_for?":"What are you looking for?","primary_menu":"Primary Menu","toggle_menu":"Toggle Menu","top_stories":"Top Stories"},"max_depth":2,"nav_menu_location":"supernav","num_children_per_column":8,"num_columns":4,"num_columns_without_thumbnails":1,"num_posts_in_column_with_thumbnails":1,"num_posts_in_column_without_thumbnails":4,"post_type_feature":"supernav"},"syndication":{"canonical_home_url":""},"taboola":{"publisher_id":"nexstar-network","enabled":"1","enabled_homepage":"0","status_arena":"1"},"teads":{"status":"1"},"template_variables":{"l10n":{"article_date":"M j, Y \/ h:i A T","article_time_format":"h:i A T","article_list_by":"by %1$s %2$s %3$s","article_list_category":"%1$s \/ %2$s","author_by":"by: %s","author_sep":", ","infinite_button_text":"Load More","infinite_error_text":"Error loading articles","infinite_loading":"Loading...","more":"More","more_term":"More %s","next_page":"Next page","now_playing":"Now Playing","previous_page":"Previous page","posted":"Posted: %s","read_more_arrow":"Read More &raquo;","relative_date_format":"%s ago","search":"Search","sep":"\/","share_this_story":"Share this story","site_search":"Search","snippet_date":"M j, Y","sponsored_by":"Sponsored By","top_stories_from":"Top Stories From %s","updated":"Updated: %s","up_next":"Up Next","video":"Video","exit_sticky_player":"Exit sticky player","form_processing":"Processing...","form_message_sent":"Message Sent!","form_error":"Error","watch":"Watch"},"num_404_top_stories_articles":5},"unique_site_shortcode":{"identifier":"KRON"},"uuid":"abc69eb2-36c0-4172-b8a8-29cde72aece7","video_center":{"l10n":{"document_title":"Video Center","meta_description":"The latest videos from KRON4"},"num_bins":10,"num_videos_per_bin":12,"number_of_tabs":7,"tabs_stack_until_bp":900,"carousel_excluded_article_fields":["category","excerpt"]},"weather":{"city_name":"San Francisco","latitude":"37.78","longitude":"-122.42","zipcode":"94128"},"weather_alerts":{"l10n":{"loading_alerts":"Checking for current alerts","no_current_alerts":"There are no active weather alerts. Check back later."}},"wsi":{"cid":"878507589"}};
var nsApiSettings = {"root":"https:\/\/www.kron4.com\/wp-json\/","nonce":"ac397ef31e","versionString":"wp\/v2\/"};
var weatherAlerts = {"alert_types":["911 Telephone Outage Emergency","Administrative Message","Air Quality Alert","Air Stagnation Advisory","Ashfall Advisory","Ashfall Warning","Avalanche Warning","Avalanche Watch","Blizzard Warning","Blizzard Watch","Blowing Dust Advisory","Blowing Dust Warning","Brisk Wind Advisory","Child Abduction Emergency","Civil Danger Warning","Civil Emergency Message","Coastal Flood Advisory","Coastal Flood Statement","Coastal Flood Warning","Coastal Flood Watch","Dense Fog Advisory","Dense Smoke Advisory","Dust Advisory","Dust Storm Warning","Earthquake Warning","Excessive Heat Warning, Extreme Heat Warning, Heat Warning","Excessive Heat Watch","Extreme Cold Watch","Extreme Wind Warning","Fire Warning","Fire Weather Watch","Flash Flood Statement","Flash Flood Warning, Rainfall Warning","Flash Flood Watch","Flood Advisory","Flood Statement","Flood Warning","Flood Watch","Freeze Warning, Flash Freeze Warning","Freeze Watch","Freezing Fog Advisory","Freezing Rain Advisory","Freezing Spray Advisory","Frost Advisory","Gale Warning","Gale Watch","Hard Freeze Warning","Hard Freeze Watch","Hazardous Materials Warning","Hazardous Seas Warning","Hazardous Seas Watch","Heat Advisory","Heavy Freezing Spray Warning","Heavy Freezing Spray Watch","High Surf Advisory","High Surf Warning","High Wind Warning, Hurricane Force Wind Warning, Severe Wind Warning, Strong Wind Warning, Wreckhouse Wind Warning, Les Suetes Wind Warning, Wind Warning","High Wind Watch","Hurricane Force Wind Watch","Hurricane Warning, Typhoon Warning","Hurricane Watch, Typhoon Watch","Ice Storm Warning","Lake Effect Snow Advisory","Lake Effect Snow Warning","Lake Effect Snow Watch","Lake Wind Advisory","Lakeshore Flood Advisory","Lakeshore Flood Statement","Lakeshore Flood Warning","Lakeshore Flood Watch","Law Enforcement Warning","Local Area Emergency","Low Water Advisory","Marine Weather Statement","Nuclear Power Plant Warning","Radiological Hazard Warning","Red Flag Warning","Rip Current Statement","Severe Thunderstorm Warning","Severe Thunderstorm Watch","Shelter In Place Warning","Small Craft Advisory","Snow Squall Warning, Snowsquall Warning","Special Marine Warning","Special Weather Statement","Storm Surge Warning","Storm Surge Watch","Storm Warning","Storm Watch","Tornado Warning","Tornado Watch","Tropical Storm Warning","Tropical Storm Watch","Tsunami Advisory","Tsunami Warning","Tsunami Watch","Typhoon Local Statement","Volcano Warning","Wind Advisory","Wind Chill Advisory","Wind Chill Warning, Extreme Cold Warning","Wind Chill Watch","Winter Storm Warning, Snowfall Warning","Winter Storm Watch","Winter Weather Advisory","Winter Storm Warning","High Wind Warning"],"api_url":"https:\/\/weather.psg.nexstardigital.net\/service\/api\/v3\/alerts\/getLiveAlertsByCounties?counties=06075,06001,06081,06055,06097,06085,06013,06041,06095","fips":["06075","06001","06081","06055","06097","06085","06013","06041","06095"],"wales":""};
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/js/common.chunk.min.js?ver=5943385c5450731d1f79" id="nswv-common-js-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/js/global.bundle.min.js?ver=a38a4ca466dedd2c1153" id="nswv-global-js-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/themes/nexstar-wv/client/build/js/video-playlist.bundle.min.js?ver=e51693788eab90d1f597" id="nswv-video-playlist-js-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/themes/nexstar-wv/inc/truncate-featured-image-captions.js?ver=0.0.2" id="truncate-featured-image-captions-js"></script>
<script type="text/javascript" id="live-now-script-js-extra">
/* <![CDATA[ */
var liveNowScriptObject = {"homeUrl":"https:\/\/www.kron4.com"};
var liveNowScriptObject = {"homeUrl":"https:\/\/www.kron4.com"};
/* ]]> */
</script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/lakana/build/liveNow.js?ver=c3cf8a86" id="live-now-script-js" defer="defer" data-wp-strategy="defer"></script>
<script type="text/javascript" src="https://imasdk.googleapis.com/js/sdkloader/ima3.js?ver=1759244544" id="ima-sdk-js"></script>
<script type="text/javascript" src="https://imasdk.googleapis.com/pal/sdkloader/pal.js?ver=1759244544" id="pal-sdk-js"></script>
<script type="text/javascript" src="https://www.kron4.com/wp-content/plugins/nxst-video-delivery/client/ovp/build/js/main.bundle.min.js?ver=1759244544" id="nxst-vd-ovp-js-js"></script>
<script type="text/javascript" src="https://widgets.media.weather.com/wxwidget.loader.js?cid=878507589" id="wxwidget-loader-js"></script>

	
	
	
</body>
</html>
