#include "FeedValidator.h"
#include "../FangApp.h"
#include "../utilities/FangLogging.h"

FeedValidator::FeedValidator(QQuickItem *parent) :
    QQuickItem(parent),
    _validating(false),
    _url("")
{
    connect(&feedDiscovery, &FeedDiscovery::done, this, &FeedValidator::onFeedDiscoveryDone);
}

void FeedValidator::check()
{
    // Signal start.
    _validating = true;
    emit validatingChanged(_validating);
    
    // DO IT.
    feedDiscovery.checkFeed(_url);
}

QVariantList FeedValidator::discoveredFeeds()
{
    // Build a list of all feeds found. We're using an index-based loop here as we
    // need the index to refer to the feed later.
    QVariantList result;
    for (int i = 0; i < _feeds.count(); i++) {
        const FeedInfo& info = _feeds[i];
        QVariantMap feedMap;
        feedMap["url"] = info.url;
        feedMap["title"] = info.title;
        feedMap["selected"] = info.selected;
        feedMap["index"] = i;
        result.append(feedMap);
    }
    return result;
}

int FeedValidator::feedCount()
{
    return _feeds.count();
}

int FeedValidator::feedsToAddCount()
{
    int count = 0;
    for (const FeedInfo& feedInfo : _feeds) {
        if (feedInfo.selected && !feedInfo.title.isEmpty()) {
            count++;
        }
    }
    return count;
}

void FeedValidator::setFeedSelected(int index, bool selected)
{
    if (index >= 0 && index < _feeds.count()) {
        _feeds[index].selected = selected;
        emit feedsToAddCountChanged();
    } else {
        qCWarning(logModel) << "setFeedSelected: No feed found for index: " << index;
    }
}

void FeedValidator::setFeedTitle(int index, QString title)
{
    if (index >= 0 && index < _feeds.count()) {
        _feeds[index].title = title;
        emit feedsToAddCountChanged();
    } else {
        qCWarning(logModel) << "setFeedTitle: No feed found for index: " << index;
    }
}

void FeedValidator::addFeeds()
{
    // Add all selected feeds
    QList<FeedDiscovery::DiscoveredFeed> discovered = feedDiscovery.discoveredFeeds();

    for (const FeedInfo& feedInfo : _feeds) {
        if (feedInfo.selected) {
            if (feedInfo.discoveryIndex >= 0 && feedInfo.discoveryIndex < discovered.count()) {
                RawFeed* feed = discovered[feedInfo.discoveryIndex].feed;
                if (feed) {
                    feed->title = feedInfo.title;
                    FangApp::instance()->addFeed(feedInfo.url, feed, true);
                }
            }
        }
    }
}

void FeedValidator::setUrl(QString url)
{
    if (url == _url) {
        return;
    }

    _url = url;
    emit urlChanged(_url);
}

void FeedValidator::onFeedDiscoveryDone(FeedDiscovery* discovery)
{
    Q_UNUSED(discovery);

    // Validation is done.
    _validating = false;
    emit validatingChanged(_validating);

    // Clear previous feeds.
    _feeds.clear();

    if (!feedDiscovery.error()) {
        // Add all discovered feeds to our list.
        QList<FeedDiscovery::DiscoveredFeed> discovered = feedDiscovery.discoveredFeeds();
        for (int i = 0; i < discovered.count(); i++) {
            const FeedDiscovery::DiscoveredFeed& df = discovered[i];
            if (df.validated && df.feed) {
                FeedInfo info;
                info.url = df.url.toString();
                info.title = df.feed->title.isEmpty() ? df.url.toString() : df.feed->title;
                info.selected = (i == 0);  // Only the first one is selected by default.
                info.discoveryIndex = i;
                _feeds.append(info);
            }
        }

        // Emit signals to refresh QML.
        emit discoveredFeedsChanged();
        emit feedCountChanged();
        emit feedsToAddCountChanged();
    }

    // Completion!
    emit validationComplete(!feedDiscovery.error(), feedDiscovery.errorString());
}

