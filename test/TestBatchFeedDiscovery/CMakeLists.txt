# TestBatchFeedDiscovery test executable
qt_add_executable(tst_testbatchfeeddiscovery
    tst_testbatchfeeddiscovery.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.cpp
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.h
    ${CMAKE_SOURCE_DIR}/test/MockWebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/test/MockBatchFeedFetcher.h
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchFeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchFeedDiscovery.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.h
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkDownloadCore.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkDownloadCore.h
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
    ${CMAKE_SOURCE_DIR}/src/parser/BatchFeedFetcher.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/BatchFeedFetcher.h
    ${CMAKE_SOURCE_DIR}/src/parser/FeedFetcher.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/FeedFetcher.h
    ${CMAKE_SOURCE_DIR}/src/parser/FeedSource.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/FeedSource.h
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
    ${CMAKE_SOURCE_DIR}/src/utilities/NewsSitemapSynthesizer.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NewsSitemapSynthesizer.h
    ${CMAKE_SOURCE_DIR}/src/utilities/PageMetadataExtractor.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/PageMetadataExtractor.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
)

# Include directories
target_include_directories(tst_testbatchfeeddiscovery PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/src/models
)

# Link libraries
target_link_libraries(tst_testbatchfeeddiscovery PRIVATE
    FangFeedParser
    TidyLib
    QSimpleStateMachine::QSimpleStateMachine
    Qt6::Test
    Qt6::Core
    Qt6::Network
)

# Add to CTest
add_test(NAME BatchFeedDiscovery COMMAND tst_testbatchfeeddiscovery)
