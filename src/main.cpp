#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QStringList>
#include <QIcon>
#include <QProcessEnvironment>
#include <QDebug>

#include "FangApp.h"
#include "utilities/FangLogging.h"

#include "models/FeedValidator.h"
#include "models/NewsFeedInteractor.h"
#include "models/ListModel.h"
#include "models/OPMLInteractor.h"

#include "db/DB.h"

#include <QSingleInstanceCheck/QSingleInstanceCheck.h>

#include "utilities/QObjectLeakTracker.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QObjectLeakTracker::install();

    // Register class name prefixes for leak report filtering.
    for (const char *p : {
        "Add", "AllNews", "Async", "Batch", "Bookmark", "Browser",
        "DB", "Expire", "Fang", "FaviconGrabber", "FaviconUpdate", "Feed", "Folder",
        "GetAll", "HTML", "Image", "Insert", "List", "Lisvel",
        "Load", "MarkAll", "Network", "News", "Notification",
        "OPML", "Operation", "Pinned", "QAutoStart", "QSimple",
        "QSingle", "Raw", "Reload", "Remove", "Search", "Set",
        "Sync", "Update", "Web", "Win", "Xml"
    }) {
        QObjectLeakTracker::addPrefix(p);
    }

    qmlRegisterType<FeedValidator>("Fang", 1, 0, "FeedValidator");
    qmlRegisterType<NewsFeedInteractor>("Fang", 1, 0, "NewsFeedInteractor");
    qmlRegisterType<ListItem>("Fang", 1, 0, "ListItem");
    qmlRegisterType<OPMLInteractor>("Fang", 1, 0, "OPMLInteractor");

    // Prevent graphical stutter/tearing on WebEngineView.
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    // Use native rendering for fonts.
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
    
    QApplication app(argc, argv);
    app.setOrganizationName("EricGregory");
    app.setOrganizationDomain("GetFang.com");
    app.setApplicationName("Fang");
    app.setApplicationVersion(APP_VERSION);
    app.setWindowIcon(QIcon(":/qml/images/full_icon.png"));

    initFileLogging();

    // Gets feed URL from command-line arguments. Intended for opening feeds on Windows and Linux
    QString pendingFeedUrl;
    for (int i = 1; i < argc; ++i) {
        QString arg = QString::fromLocal8Bit(argv[i]);
        if (arg.startsWith("feed://") || arg.startsWith("feeds://") || arg.startsWith("feed:")) {
            pendingFeedUrl = arg;
            break;
        }
    }

    // Only run one Fang at a time, fellas. Must be run after creating QApplication.
    QSingleInstanceCheck single("FangNewsReader");
    if (single.isAlreadyRunning()) {
        qDebug() << "Fang is already running";
        if (!pendingFeedUrl.isEmpty()) {
            single.notify(QStringList{pendingFeedUrl});
        } else {
            single.notify();
        }
        return -1;
    }
    
    int ret = 0;

    // The main startup sequence lives in this code block for easier cleanup.
    {
        FangApp fang(&app, &single);

        if (!pendingFeedUrl.isEmpty()) {
            fang.setPendingFeedUrl(pendingFeedUrl);
        }

        // Init the app (creates engine, loads feeds, loads QML).
        fang.init();

        // Run the app.
        ret = app.exec();
    }

    // Make sure the database is shut down.
    delete DB::instance();

    // Leak check.
    QObjectLeakTracker::printRemaining();

    return ret;
}
