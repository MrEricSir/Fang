# TestBatchFeedDiscovery test executable
qt_add_executable(tst_testbatchfeeddiscovery
    tst_testbatchfeeddiscovery.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.h
    ${CMAKE_SOURCE_DIR}/test/MockBatchWebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/test/MockBatchNewsParser.h
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchFeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchFeedDiscovery.h
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchWebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchWebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleStateMachine.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleStateMachine.h
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.h
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
    ${CMAKE_SOURCE_DIR}/src/parser/BatchNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/BatchNewsParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.h
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.h
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.cpp
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.h
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
    TidyLib
    Qt6::Test
    Qt6::Core
    Qt6::Network
)

# Add to CTest
add_test(NAME BatchFeedDiscovery COMMAND tst_testbatchfeeddiscovery)
