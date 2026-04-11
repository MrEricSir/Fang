# TestBatchFeedDiscovery test executable
qt_add_executable(tst_testbatchfeeddiscovery
    tst_testbatchfeeddiscovery.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.cpp
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.h
    ${CMAKE_SOURCE_DIR}/test/MockWebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/test/MockBatchFeedFetcher.h
    # App-level sources
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchFeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/BatchFeedDiscovery.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
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
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME BatchFeedDiscovery COMMAND tst_testbatchfeeddiscovery)
