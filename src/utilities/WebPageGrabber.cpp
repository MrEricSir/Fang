#include "WebPageGrabber.h"
#include "Utilities.h"
#include <QDebug>
#include <QWebFrame>
#include <QWebPage>
#include <QWebElement>

WebPageGrabber::WebPageGrabber(QObject *parent) :
    QObject(parent)
{
    Utilities::addNetworkAccessManagerCache(webView.page()->networkAccessManager());
    webView.page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, false); // No scripts.
    webView.page()->settings()->setAttribute(QWebSettings::AutoLoadImages, false); // No imgs
    
    connect(webView.page()->mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    connect(webView.page()->mainFrame(), SIGNAL(urlChanged(QUrl)), this, SLOT(onUrlChanged(QUrl)));
}

void WebPageGrabber::load(const QUrl &url)
{
    if (url.isRelative())
        emit ready(NULL); // We don't take kindly to relative paths (fix for crash bug)
    else
        webView.load(url);
}

void WebPageGrabber::onLoadFinished(bool ok)
{
    if (!ok)
        return; // It happens!
    
    bool done = true;
    
    // That's so meta.
    // Figure out if we're going to refresh, and if we are, we ain't done.
    QWebElementCollection metas = webView.page()->mainFrame()->documentElement().findAll("meta");
    foreach (QWebElement meta, metas) {
        // So the meta tag to refresh immediately has to be something like this:
        // <meta http-equiv="refresh" content="0;http://www.example.com">
        if (meta.hasAttribute("http-equiv") && meta.attribute("http-equiv").toLower() == "refresh"
                && meta.attribute("content").startsWith("0;")) {
            //qDebug() << "Content: " << meta.attribute("content");
            done = false;
        }
    }
    
    if (done)
        emit ready(webView.page());
}

void WebPageGrabber::onUrlChanged(const QUrl& url)
{
    Q_UNUSED(url);
    //qDebug() << "URL is now: " << url;
}
