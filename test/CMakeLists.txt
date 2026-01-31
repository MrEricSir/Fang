# Coverage flags for all test executables
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Shared test library (compiled once, used by all tests)
add_subdirectory(FangTestLib)

# Test suite
add_subdirectory(TestImageGrabber)
add_subdirectory(TestNetworkDownloadCore)
add_subdirectory(TestFangParser)
add_subdirectory(TestFangFaviconGrabber)
add_subdirectory(TestFangFeedDiscovery)
add_subdirectory(TestBatchFeedDiscovery)
add_subdirectory(TestBatchNewsParser)
add_subdirectory(TestFangOPMLParser)
add_subdirectory(TestOPMLExport)
add_subdirectory(TestRawFeedRewriter)
add_subdirectory(TestURLFixup)
add_subdirectory(TestUpdateChecker)
add_subdirectory(TestWebPageGrabber)

# Database tests
add_subdirectory(TestDatabaseOperations)

# Model tests
add_subdirectory(TestFangObject)
add_subdirectory(TestFeedItem)
add_subdirectory(TestFeedValidator)
add_subdirectory(TestNewsItem)
add_subdirectory(TestNewsList)

# Network tests
add_subdirectory(TestNetworkRetryPolicy)
