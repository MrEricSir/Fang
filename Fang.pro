# Add more folders to ship with the application, here
folder_01.source = qml/Fang
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# For Fang we'll need QtCore, the network, and the built-in SQLite database.
QT       += core network sql webkit webkitwidgets

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/models/ListModel.cpp \
    src/models/NewsItem.cpp \
    src/models/FeedItem.cpp \
    src/parser/Parser.cpp \
    src/parser/RawFeed.cpp \
    src/parser/RawNews.cpp \
    src/FangApp.cpp \
    src/operations/OperationManager.cpp \
    src/operations/Operation.cpp \
    src/operations/UpdateFeedOperation.cpp \
    src/utilities/Utilities.cpp \
    src/operations/LoadAllFeedsOperation.cpp \
    src/db/DB.cpp \
    src/models/MouseWheelArea.cpp \
    src/operations/DBOperation.cpp \
    src/models/FeedValidator.cpp \
    src/operations/AddFeedOperation.cpp \
    src/operations/RemoveFeedOperation.cpp \
    src/utilities/FaviconGrabber.cpp \
    src/operations/SetBookmarkOperation.cpp \
    src/utilities/WebPageGrabber.cpp \
    src/operations/FaviconUpdateOperation.cpp \
    src/models/FangApplicationViewer.cpp \
    src/models/AllNewsFeedItem.cpp \
    src/utilities/WebImageSizeRewriter.cpp \
    src/utilities/ImageGrabber.cpp \
    src/operations/UpdateTitleOperation.cpp \
    src/parser/ParserInterface.cpp \
    src/parser/BackgroundParser.cpp \
    src/parser/BackgroundParserThread.cpp \
    src/models/FangSettings.cpp \
    src/models/WebInteractor.cpp \
    src/operations/LoadNews.cpp \
    src/utilities/RawFeedRewriter.cpp \
    src/operations/LoadAllNewsOperation.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(src/qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/Fang/FeedTitleDelegate.qml \
    html/NewsPage.html \
    sql/1.sql \
    qml/Fang/SidebarButton.qml \
    html/jquery-2.0.3.js \
    html/fang.js

RESOURCES += \
    Resources.qrc

HEADERS += \
    src/models/ListModel.h \
    src/models/NewsItem.h \
    src/models/FeedItem.h \
    src/parser/Parser.h \
    src/parser/RawFeed.h \
    src/parser/RawNews.h \
    src/FangApp.h \
    src/operations/OperationManager.h \
    src/operations/Operation.h \
    src/operations/UpdateFeedOperation.h \
    src/utilities/Utilities.h \
    src/operations/LoadAllFeedsOperation.h \
    src/db/DB.h \
    src/models/MouseWheelArea.h \
    src/operations/DBOperation.h \
    src/models/FeedValidator.h \
    src/operations/AddFeedOperation.h \
    src/operations/RemoveFeedOperation.h \
    src/utilities/FaviconGrabber.h \
    src/operations/SetBookmarkOperation.h \
    src/utilities/WebPageGrabber.h \
    src/operations/FaviconUpdateOperation.h \
    src/models/FangApplicationViewer.h \
    src/models/AllNewsFeedItem.h \
    src/utilities/WebImageSizeRewriter.h \
    src/utilities/ImageGrabber.h \
    src/operations/UpdateTitleOperation.h \
    src/parser/ParserInterface.h \
    src/parser/BackgroundParser.h \
    src/parser/BackgroundParserThread.h \
    src/models/FangSettings.h \
    src/models/WebInteractor.h \
    src/operations/LoadNews.h \
    src/utilities/RawFeedRewriter.h \
    src/operations/LoadAllNewsOperation.h
