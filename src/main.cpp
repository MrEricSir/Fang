#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDateTime>

#if defined(Q_OS_MAC)
#include <QtSvg> // Required for OS X SVG support (yes, really.)
#endif

// The qmake file decides if we need WebEngine
#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
#include <QtWebEngine>
#endif // QT_WEBVIEW_WEBENGINE_BACKEND

#include "FangApp.h"

#include "models/FeedValidator.h"
#include "models/FangSettings.h"
#include "models/QMLNewsInteractor.h"
#include "models/ListModel.h"
#include "models/OPMLInteractor.h"

#include "network/FangQQmlNetworkAccessManagerFactory.h"

#include "db/DB.h"

#include "utilities/SingleInstanceCheck.h"

#include "FangObject.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qmlRegisterType<FeedValidator>("Fang", 1, 0, "FeedValidator");
    qmlRegisterType<FangSettings>("Fang", 1, 0, "FangSettings");
    qmlRegisterType<QMLNewsInteractor>("Fang", 1, 0, "QMLNewsInteractor");
    qmlRegisterType<ListItem>("Fang", 1, 0, "ListItem");
    qmlRegisterType<OPMLInteractor>("Fang", 1, 0, "OPMLInteractor");
    
    QApplication app(argc, argv);
    app.setOrganizationName("EricSoft");
    app.setOrganizationDomain("EricSoft.com");
    app.setApplicationName("Fang");
    app.setApplicationVersion(APP_VERSION);

#ifdef QT_WEBVIEW_WEBENGINE_BACKEND
    QtWebEngine::initialize();
#endif // QT_WEBVIEW_WEBENGINE_BACKEND
    
    // Only run one Fang at a time, fellas.
    SingleInstanceCheck single("FangNewsReader", "FangSettings");
    if (single.isAlreadyRunning()) {
        return -1;
    }
    
    int ret = 0;
    QQmlApplicationEngine engine;
    engine.setNetworkAccessManagerFactory(new FangQQmlNetworkAccessManagerFactory());
    
    // Use a code block to ensure FangApp is deleted.
    {
        FangApp fang(&app, &engine, &single);
        fang.init();
    
        ret = app.exec();
    }
    
    // Make sure the database is shut down.
    delete DB::instance();
    
    FangObject::printRemainingObjects();
    
    return ret;
}
