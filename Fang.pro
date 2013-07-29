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
    src/models/FangWebView.cpp \
    src/models/NewsWeb.cpp \
    src/operations/LoadAllFeedsOperation.cpp \
    src/db/DB.cpp \
    src/models/MouseWheelArea.cpp \
    src/operations/DBOperation.cpp \
    src/models/FeedValidator.cpp \
    src/operations/AddFeedOperation.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(src/qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/Fang/FeedTitleDelegate.qml \
    html/NewsPage.html \
    sql/1.sql \
    qml/Fang/SidebarButton.qml

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
    src/models/FangWebView.h \
    src/models/NewsWeb.h \
    src/operations/LoadAllFeedsOperation.h \
    src/db/DB.h \
    src/models/MouseWheelArea.h \
    src/operations/DBOperation.h \
    src/models/FeedValidator.h \
    src/operations/AddFeedOperation.h
