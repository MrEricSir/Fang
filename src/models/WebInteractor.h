#ifndef WEBINTERACTOR_H
#define WEBINTERACTOR_H

#include <QQuickItem>
#include <QString>

#include "FeedItem.h"
#include "NewsItem.h"
#include "FangSettings.h"
#include "../operations/OperationManager.h"
#include "../operations/Operation.h"
#include "../operations/LoadNews.h"
#include "../operations/LoadAllNewsOperation.h"
#include "../operations/LoadPinnedNewsOperation.h"
#include "../operations/UpdateOrdinalsOperation.h"

/**
 * @brief Passes news between the JavaScript and C++ layers, yo.
 */
class WebInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(WebInteractor)
    
    Q_PROPERTY(qint32 specialFeedCount READ specialFeedCount NOTIFY specialFeedCountChanged)


public:
    explicit WebInteractor(QQuickItem *parent = 0);
    virtual ~WebInteractor() {}
    
    /**
     * @brief The stuff the interactor needs to do its job properly.
     * @param manager
     * @param feedList
     * @param fangSettings
     */
    void init(OperationManager* manager, ListModel *feedList, FangSettings *fangSettings);


    // Returns the number of special feeds.
    qint32 specialFeedCount();
    
signals:
    
    /**
     * @brief The style has changed in FangSettings, so the news viewer needs to refresh its css.
     */
    void styleChanged();
    
    /**
     * @brief The font size has changed, so to a jump to bookmark.
     */
    void fontSizeChanged();

    /**
     * @brief The number of special feeds in the feed list has changed.
     */
    void specialFeedCountChanged();
    
public slots:

    // The order of the feed list changed!  Better record that.
    Q_INVOKABLE void orderChanged();
    
    // Refreshes the current feed.
    Q_INVOKABLE void refreshCurrentFeed();
    
private slots:
    
    // Alert us to style changes.
    void onStyleChanged(QString style);
    
    // Alert us to font size changes.
    void onFontSizeChanged(QString font);
    
private:
    // Op man!
    OperationManager* manager;
    
    // Pointer to the global feed list.
    ListModel *feedList;
    
    // Pointer to the global settings object.
    FangSettings *fangSettings;
};

#endif // WEBINTERACTOR_H
