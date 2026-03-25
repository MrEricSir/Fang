add_library(FangFeedDiscovery STATIC
    FeedDiscoveryLogging.cpp
    FeedDiscoveryLogging.h
    FeedSource.cpp
    FeedSource.h
    FeedFetchResult.h
    FeedFetcher.cpp
    FeedFetcher.h
    BatchFeedFetcher.cpp
    BatchFeedFetcher.h
    FeedDiscovery.cpp
    FeedDiscovery.h
    WebPageGrabber.cpp
    WebPageGrabber.h
    PageMetadataExtractor.cpp
    PageMetadataExtractor.h
    NewsSitemapSynthesizer.cpp
    NewsSitemapSynthesizer.h
    NetworkDownloadCore.cpp
    NetworkDownloadCore.h
    NetworkRetryPolicy.cpp
    NetworkRetryPolicy.h
    FangNetworkAccessManager.cpp
    FangNetworkAccessManager.h
    NetworkUtilities.cpp
    NetworkUtilities.h
)

# QSimpleStateMachine is header-only with Q_OBJECT. Generate its MOC exactly once
# here, and suppress AUTOMOC so it doesn't also generate a duplicate.
set_source_files_properties(
    ${CMAKE_SOURCE_DIR}/external/QSimpleStateMachine/include/QSimpleStateMachine/QSimpleStateMachine.h
    PROPERTIES SKIP_AUTOMOC TRUE
)
qt_wrap_cpp(QSSM_MOC_SRCS
    ${CMAKE_SOURCE_DIR}/external/QSimpleStateMachine/include/QSimpleStateMachine/QSimpleStateMachine.h
    TARGET FangFeedDiscovery
)
target_sources(FangFeedDiscovery PRIVATE ${QSSM_MOC_SRCS})

target_include_directories(FangFeedDiscovery PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FangFeedDiscovery PUBLIC
    FangFeedParser
    Qt6::Core
    Qt6::Network
    TidyLib
    QSimpleStateMachine::QSimpleStateMachine
)
