#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDateTime>
#include <QStringList>
#include <QQmlFileSelector>
#include <QIcon>
#include <QProcessEnvironment>
#include <QDebug>

#include "FangApp.h"

#include "models/FeedValidator.h"
#include "models/FangSettings.h"
#include "models/NewsFeedInteractor.h"
#include "models/ListModel.h"
#include "models/OPMLInteractor.h"

#include "network/FangQQmlNetworkAccessManagerFactory.h"

#include "db/DB.h"

#include <QSingleInstanceCheck/QSingleInstanceCheck.h>

#include "FangObject.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    // Only run one Fang at a time, fellas.
    QSingleInstanceCheck single("FangNewsReader");
    if (single.isAlreadyRunning()) {
        qDebug() << "Fang is already running";
        single.notify();
        return -1;
    }

    qmlRegisterType<FeedValidator>("Fang", 1, 0, "FeedValidator");
    qmlRegisterType<FangSettings>("Fang", 1, 0, "FangSettings");
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
    
    int ret = 0;

    // Wrap our application in a code block to (slightly) simplify cleanup,
    {
        QQmlApplicationEngine* engine = new QQmlApplicationEngine();
        engine->setNetworkAccessManagerFactory(new FangQQmlNetworkAccessManagerFactory());
        QQmlFileSelector selector(engine); // For platform-specific QML files

        // Set QML file selectors.
        QStringList selectors;

#ifndef QT_WEBVIEW_WEBENGINE_BACKEND
        // Add a selector indicating we need Qt's native WebView
        selectors << "webview";
#endif // QT_WEBVIEW_WEBENGINE_BACKEND

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
        selectors << "mobile";
#endif

        if (selectors.count()) {
            selector.setExtraSelectors(selectors);
        }

        // Init app.
        FangApp fang(&app, engine, &single);
        fang.init();

        // Run app.
        ret = app.exec();

        // Delete QML layer.
        delete engine;
    }

    // Make sure the database is shut down.
    delete DB::instance();

    // Leak check.
    FangObject::printRemainingObjects();

    return ret;
}
