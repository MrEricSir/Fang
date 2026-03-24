# Shared test library - compiles common sources once for all tests
# This significantly reduces build time by avoiding duplicate compilation

add_library(FangTestLib STATIC
    # Core infrastructure (used by almost every test)
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp

    # Network stack (used by most tests)
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/BatchDownloadCore.cpp

    # Parser infrastructure (used by parser/feed tests)
    ${CMAKE_SOURCE_DIR}/src/parser/FeedSource.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/FeedFetcher.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/BatchFeedFetcher.cpp

    # Sitemap support
    ${CMAKE_SOURCE_DIR}/src/utilities/PageMetadataExtractor.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NewsSitemapSynthesizer.cpp

    # Utilities (used by multiple tests)
    ${CMAKE_SOURCE_DIR}/src/network/NetworkDownloadCore.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/ImageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/ImageCache.cpp
    # NOTE: FeedDiscovery is NOT included here because it uses QSimpleStateMachine
    # Tests that need FeedDiscovery should compile it directly to avoid duplicate MOC symbols
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
    FangFeedParser
    TidyLib
    Qt6::Concurrent
    Qt6::Core
    Qt6::Network
    Qt6::Gui
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
