# TestBatchFeedFetcher test executable
qt_add_executable(tst_batchfeedfetcher
    tst_batchfeedfetcher.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.cpp
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.h
)

# Link shared test library (contains all common sources)
target_link_libraries(tst_batchfeedfetcher PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME BatchFeedFetcher COMMAND tst_batchfeedfetcher)
