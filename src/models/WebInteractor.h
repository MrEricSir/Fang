#ifndef WEBINTERACTOR_H
#define WEBINTERACTOR_H

#include <QQuickItem>
#include <QString>

#include "FeedItem.h"
#include "NewsItem.h"
#include "../operations/OperationManager.h"
#include "../operations/Operation.h"
#include "../operations/UpdateOrdinalsOperation.h"

/**
 * @brief Passes news between the JavaScript and C++ layers, yo.
 */
class WebInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(WebInteractor)
    
    Q_PROPERTY(qint32 specialFeedCount READ specialFeedCount NOTIFY specialFeedCountChanged)
    Q_PROPERTY(bool loadInProgress READ loadInProgress NOTIFY onIsLoadInProgressChanged)
    Q_PROPERTY(int windowHeight READ getWindowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)


public:
    explicit WebInteractor(QQuickItem *parent = 0);
    virtual ~WebInteractor() {}
    
    /**
     * @brief The stuff the interactor needs to do its job properly.
     * @param manager
     * @param feedList
     */
    void init(OperationManager* manager, ListModel *feedList);


    // Returns the number of special feeds.
    qint32 specialFeedCount();

    // Returns true if a news load is in progress.
    bool loadInProgress();

    // Returns the window height.
    int getWindowHeight() { return windowHeight; }

    // Sets the window height.
    void setWindowHeight(int windowHeight);


signals:

    /**
     * @brief The number of special feeds in the feed list has changed.
     */
    void specialFeedCountChanged();

    /**
     * @brief News is being loaded, or the load just ended. YAY!
     */
    void onIsLoadInProgressChanged();

    // The window height changed!
    void windowHeightChanged();

public slots:

    // The order of the feed list changed!  Better record that.
    Q_INVOKABLE void orderChanged();
    
    // Refreshes the current feed.
    Q_INVOKABLE void refreshCurrentFeed();
    
private:
    // Op man!
    OperationManager* manager;
    
    // Pointer to the global feed list.
    ListModel *feedList;

    int windowHeight;
};

#endif // WEBINTERACTOR_H
