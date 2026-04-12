# Coverage flags for all test executables
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Shared test library (compiled once, used by all tests)
add_subdirectory(FangTestLib)

# Test suite
add_subdirectory(TestImageGrabber)
add_subdirectory(TestFangParser)
add_subdirectory(TestFangFaviconGrabber)
add_subdirectory(TestFangFeedDiscovery)
add_subdirectory(TestBatchFeedDiscovery)
add_subdirectory(TestBatchFeedFetcher)
add_subdirectory(TestFangOPMLParser)
add_subdirectory(TestOPMLExport)
add_subdirectory(TestRawFeedRewriter)
add_subdirectory(TestFeedURLNormalization)
add_subdirectory(TestUpdateChecker)
add_subdirectory(TestWebPageGrabber)

# Database tests
add_subdirectory(TestDB)
add_subdirectory(TestDatabaseOperations)
add_subdirectory(TestSearch)

# Operation tests
add_subdirectory(TestUpdateOrdinalsOperation)
add_subdirectory(TestSearchOperation)
add_subdirectory(TestFeedOperations)
add_subdirectory(TestLoadNewsOperation)

# Model tests
add_subdirectory(TestLeakTracker)
add_subdirectory(TestFangSettings)
add_subdirectory(TestFeedItem)
add_subdirectory(TestListModel)
add_subdirectory(TestSpecialFeedItems)
add_subdirectory(TestFeedValidator)
add_subdirectory(TestLisvelFeedItem)
add_subdirectory(TestNewsItem)
add_subdirectory(TestNewsList)

# Integration tests
add_subdirectory(TestBookmarkIntegration)
add_subdirectory(TestWebServer)

# Utility tests
add_subdirectory(TestFileLogging)
add_subdirectory(TestImageCache)
