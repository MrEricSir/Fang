# Shared test library - compiles common sources once for all tests
# This significantly reduces build time by avoiding duplicate compilation

add_library(FangTestLib STATIC
    # Core infrastructure (used by almost every test)
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h

    # Network stack (used by most tests)
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.h
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.cpp
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.h

    # Parser infrastructure (used by parser/feed tests)
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.h
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.h
    ${CMAKE_SOURCE_DIR}/src/parser/BatchNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/BatchNewsParser.h

    # Utilities (used by multiple tests)
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.h
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.h
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/utilities/QSimpleStateMachine.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.h
)

# Include directories
target_include_directories(FangTestLib PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/network
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/external/tidylib/include
)

# Link required libraries
target_link_libraries(FangTestLib PUBLIC
    TidyLib
    Qt6::Core
    Qt6::Network
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
