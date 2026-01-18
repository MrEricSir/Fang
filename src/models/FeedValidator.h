#ifndef FEEDVALIDATOR_H
#define FEEDVALIDATOR_H

#include <QQuickItem>
#include <QObject>
#include <QUrl>
#include <QVariantList>

#include "../utilities/FeedDiscovery.h"

/**
 * @brief Initially this class was for validating feed URLs, but has now outgrown that to handle
 *        adding and removing feeds and folders.
 */
class FeedValidator : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(FeedValidator)

    Q_PROPERTY(bool validating READ validating NOTIFY validatingChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QVariantList discoveredFeeds READ discoveredFeeds NOTIFY discoveredFeedsChanged)
    Q_PROPERTY(int feedCount READ feedCount NOTIFY feedCountChanged)
    Q_PROPERTY(int feedsToAddCount READ feedsToAddCount NOTIFY feedsToAddCountChanged)
    
public:
    explicit FeedValidator(QQuickItem *parent = nullptr);
    virtual ~FeedValidator() {}
    
    inline bool validating() { return _validating; }
    inline QString url() { return _url; }
    QVariantList discoveredFeeds();
    int feedCount();
    int feedsToAddCount();
    void setUrl(QString url);

public slots:
    // Performs the URL check.
    // Set the URL, then call this and wait for validationComplete().
    void check();

    // Set whether a specific feed (by index) is selected for adding
    void setFeedSelected(int index, bool selected);

    // Set the title for a specific feed (by index)
    void setFeedTitle(int index, QString title);

    // If check was OK, call this to add the selected feed(s)!
    void addFeed();
    
signals:
    void urlChanged(QString url);
    void validatingChanged(bool validating);
    void discoveredFeedsChanged();
    void feedCountChanged();
    void feedsToAddCountChanged();
    void validationComplete(bool result, QString errorString);

private slots:
    // Feed discovered!  Yay!
    void onFeedDiscoveryDone(FeedDiscovery *discovery);

private:
    struct FeedInfo {
        QString url;
        QString title;
        bool selected;
        int discoveryIndex;  // Index in FeedDiscovery's list
    };

    bool _validating;
    QString _url;
    QList<FeedInfo> _feeds;

    FeedDiscovery feedDiscovery;
};

QML_DECLARE_TYPE(FeedValidator)

#endif // FEEDVALIDATOR_H
