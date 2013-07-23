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

QT       += core network

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/models/ListModel.cpp \
    src/models/NewsItem.cpp \
    src/models/FeedItem.cpp \
    src/parser/Parser.cpp \
    src/parser/RawFeed.cpp \
    src/parser/RawNews.cpp \
    src/FangApp.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(src/qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/Fang/FeedTitleDelegate.qml

RESOURCES += \
    Resources.qrc

HEADERS += \
    src/models/ListModel.h \
    src/models/NewsItem.h \
    src/models/FeedItem.h \
    src/parser/Parser.h \
    src/parser/RawFeed.h \
    src/parser/RawNews.h \
    src/FangApp.h
