TEMPLATE = app

QT += network sql quick svg websockets

QT -= sensors

qtHaveModule(webengine) {
    QT += webengine
    DEFINES += QT_WEBVIEW_WEBENGINE_BACKEND
}

# Resource files
# Qt zips these and stashes them inside the executable.
RESOURCES += Resources.qrc \
    qml/qml.qrc \
    qml/images/images.qrc \
    html/html.qrc

# Default rules for deployment.
include(deployment.pri)

# TidyLib
include(tidylib/tidylib.pri)

android {
    # Create Android version of html file.
    QMAKE_PRE_LINK += $$_PRO_FILE_PWD_/androidDeploy.sh

    # Android assets for WebView
    # Open with file:///android_asset/your_file
    DEPLOY_HTML.files += html/*
    DEPLOY_HTML.path = /assets

    DEPLOY_IMG.files += qml/images/*
    DEPLOY_IMG.path = /assets/qml/images

    INSTALLS += DEPLOY_IMG DEPLOY_HTML
}

# Fang version
# From: http://www.openguru.com/2009/11/qt-best-way-to-set-application-version.html
VERSION = 0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Release build folder (for consistency on TeamCity)
release: DESTDIR = build-$$QMAKE_HOST.os-$$QMAKE_HOST.arch/release
debug:   DESTDIR = build-$$QMAKE_HOST.os-$$QMAKE_HOST.arch/debug
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

# Windows icon
RC_FILE = win32.rc

# Mac icon
ICON = icons/mac.icns

# Mac Info.plist bundle info
QMAKE_INFO_PLIST = Info.plist

SOURCES += src/main.cpp \
    src/models/ListModel.cpp \
    src/models/NewsItem.cpp \
    src/models/FeedItem.cpp \
    src/parser/RawFeed.cpp \
    src/parser/RawNews.cpp \
    src/FangApp.cpp \
    src/operations/OperationManager.cpp \
    src/operations/Operation.cpp \
    src/operations/UpdateFeedOperation.cpp \
    src/utilities/Utilities.cpp \
    src/operations/LoadAllFeedsOperation.cpp \
    src/db/DB.cpp \
    src/operations/DBOperation.cpp \
    src/models/FeedValidator.cpp \
    src/operations/AddFeedOperation.cpp \
    src/operations/RemoveFeedOperation.cpp \
    src/utilities/FaviconGrabber.cpp \
    src/operations/SetBookmarkOperation.cpp \
    src/utilities/WebPageGrabber.cpp \
    src/operations/FaviconUpdateOperation.cpp \
    src/models/AllNewsFeedItem.cpp \
    src/utilities/ImageGrabber.cpp \
    src/operations/UpdateTitleOperation.cpp \
    src/parser/ParserInterface.cpp \
    src/models/FangSettings.cpp \
    src/operations/LoadNews.cpp \
    src/utilities/RawFeedRewriter.cpp \
    src/operations/LoadAllNewsOperation.cpp \
    src/utilities/UnreadCountReader.cpp \
    src/operations/UpdateOrdinalsOperation.cpp \
    src/utilities/NetworkUtilities.cpp \
    src/parser/OPMLParser.cpp \
    src/utilities/SimpleStateMachine.cpp \
    src/utilities/FeedDiscovery.cpp \
    src/models/OPMLInteractor.cpp \
    src/utilities/OPMLExport.cpp \
    src/utilities/BatchFeedDiscovery.cpp \
    src/FangObject.cpp \
    src/parser/ParserXMLWorker.cpp \
    src/network/FangNetworkAccessManager.cpp \
    src/network/FangQQmlNetworkAccessManagerFactory.cpp \
    src/notifications/NotificationBase.cpp \
    src/utilities/SingleInstanceCheck.cpp \
    src/operations/SetPinOperation.cpp \
    src/models/PinnedFeedItem.cpp \
    src/operations/LoadPinnedNewsOperation.cpp \
    src/models/LisvelFeedItem.cpp \
    src/operations/LisvelLoadNewsOperation.cpp \
    src/operations/ExpireNewsOperation.cpp \
    src/operations/SetDBSettingOperation.cpp \
    src/db/DBSettings.cpp \
    src/operations/GetAllDBSettingsOperation.cpp \
    src/parser/NewsParser.cpp \
    src/utilities/SimpleHTTPDownloader.cpp \
    src/models/NewsWebSocketServer.cpp \
    src/models/QMLNewsInteractor.cpp
	
HEADERS += \
    src/models/ListModel.h \
    src/models/NewsItem.h \
    src/models/FeedItem.h \
    src/parser/RawFeed.h \
    src/parser/RawNews.h \
    src/FangApp.h \
    src/operations/OperationManager.h \
    src/operations/Operation.h \
    src/operations/UpdateFeedOperation.h \
    src/utilities/Utilities.h \
    src/operations/LoadAllFeedsOperation.h \
    src/db/DB.h \
    src/operations/DBOperation.h \
    src/models/FeedValidator.h \
    src/operations/AddFeedOperation.h \
    src/operations/RemoveFeedOperation.h \
    src/utilities/FaviconGrabber.h \
    src/operations/SetBookmarkOperation.h \
    src/utilities/WebPageGrabber.h \
    src/operations/FaviconUpdateOperation.h \
    src/models/AllNewsFeedItem.h \
    src/utilities/ImageGrabber.h \
    src/operations/UpdateTitleOperation.h \
    src/parser/ParserInterface.h \
    src/models/FangSettings.h \
    src/operations/LoadNews.h \
    src/utilities/RawFeedRewriter.h \
    src/operations/LoadAllNewsOperation.h \
    src/utilities/UnreadCountReader.h \
    src/operations/UpdateOrdinalsOperation.h \
    src/utilities/NetworkUtilities.h \
    src/parser/OPMLParser.h \
    src/utilities/SimpleStateMachine.h \
    src/utilities/FeedDiscovery.h \
    src/models/OPMLInteractor.h \
    src/utilities/OPMLExport.h \
    src/utilities/BatchFeedDiscovery.h \
    src/FangObject.h \
    src/parser/ParserXMLWorker.h \
    src/network/FangNetworkAccessManager.h \
    src/network/FangQQmlNetworkAccessManagerFactory.h \
    src/notifications/NotificationBase.h \
    src/utilities/SingleInstanceCheck.h \
    src/operations/SetPinOperation.h \
    src/models/PinnedFeedItem.h \
    src/operations/LoadPinnedNewsOperation.h \
    src/models/LisvelFeedItem.h \
    src/operations/LisvelLoadNewsOperation.h \
    src/operations/ExpireNewsOperation.h \
    src/operations/SetDBSettingOperation.h \
    src/db/DBSettings.h \
    src/operations/GetAllDBSettingsOperation.h \
    src/db/DBSettingsKey.h \
    src/parser/NewsParser.h \
    src/utilities/SimpleHTTPDownloader.h \
    src/models/NewsWebSocketServer.h \
    src/models/QMLNewsInteractor.h

mac {
    QT += macextras
    HEADERS += src/notifications/NotificationMac.h
    SOURCES += src/notifications/NotificationMac.cpp
}

win32 {
    HEADERS += src/notifications/NotificationWindows.h
    SOURCES += src/notifications/NotificationWindows.cpp
}


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

OTHER_FILES +=

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

