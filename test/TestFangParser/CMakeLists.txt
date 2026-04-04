# TestFeedParser test executable
qt_add_executable(tst_feedparser
    tst_feedparser.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
)

# Include directories
target_include_directories(tst_feedparser PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/test
)

# Compile definitions for test data paths
target_compile_definitions(tst_feedparser PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
    PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link libraries
target_link_libraries(tst_feedparser PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME FeedParser COMMAND tst_feedparser)
