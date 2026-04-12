# Shared test library - compiles common sources once for all tests
# This significantly reduces build time by avoiding duplicate compilation

add_library(FangTestLib STATIC
    # Core infrastructure (used by almost every test)
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp

    # App-level sources used by multiple tests
    ${CMAKE_SOURCE_DIR}/src/utilities/ImageGrabber.cpp
)

# Include directories
# NOTE: Library include dirs are added directly (not via linking FangFeedDiscovery)
# to avoid AUTOMOC generating duplicate MOC symbols for QSimpleStateMachine.
# Tests that need FangFeedDiscovery symbols must link it explicitly.
target_include_directories(FangTestLib PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/network
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/lib/QWebDownload
    ${CMAKE_SOURCE_DIR}/lib/FangFeedDiscovery
    ${CMAKE_SOURCE_DIR}/lib/FangFeedParser
    ${CMAKE_SOURCE_DIR}/external/tidylib/include
)

# Link required libraries
target_link_libraries(FangTestLib PUBLIC
    QImageCache
    QObjectLeakTracker
    Qt6::Concurrent
    Qt6::Core
    Qt6::CorePrivate
    Qt6::Network
    Qt6::Gui
    Qt6::Svg
)

# Precompiled headers for Qt (optimization #2)
# This speeds up compilation by precompiling frequently-used Qt headers
target_precompile_headers(FangTestLib PUBLIC
    <QObject>
    <QString>
    <QList>
    <QMap>
    <QUrl>
    <QByteArray>
    <QNetworkAccessManager>
    <QNetworkRequest>
    <QNetworkReply>
    <QTimer>
    <QDebug>
)
