# FangTestLib - Shared Test Library

## Purpose

This library contains commonly-used source files that are compiled **once** and linked into multiple test executables. This significantly reduces build time by avoiding duplicate compilation.

## What's Included

### Core Infrastructure
- `FangObject` - Base class for most Fang objects
- `FangLogging` - Logging utilities

### Network Stack
- `FangNetworkAccessManager` - Custom network manager with resilience
- `NetworkRetryPolicy` - Retry strategy for network requests
- `NetworkStateMonitor` - Circuit breaker implementation
- `ResilientNetworkReply` - Network reply with retry logic

### Parser Infrastructure
- `ParserInterface` - Base parser interface
- `ParserXMLWorker` - XML parsing worker
- `NewsParser` - RSS/Atom feed parser
- `RawFeed` / `RawNews` - Feed data structures
- `BatchNewsParser` - Concurrent feed parsing

### Utilities
- `SimpleHTTPDownloader` - HTTP download utility
- `NetworkUtilities` - Network helper functions
- `WebPageGrabber` - HTML page fetcher (uses TidyLib)
- `SimpleStateMachine` - State machine implementation
- `FeedDiscovery` - Feed discovery from URLs

## Precompiled Headers

This library uses precompiled headers for commonly-used Qt headers, which speeds up compilation:
- `<QObject>`, `<QString>`, `<QList>`, etc.
- `<QNetworkAccessManager>`, `<QNetworkRequest>`, `<QNetworkReply>`

## How to Use in Tests

Instead of compiling all sources individually:

**Before:**
```cmake
qt_add_executable(tst_mytest
    tst_mytest.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    # ... 20+ more source files
)

target_link_libraries(tst_mytest PRIVATE
    TidyLib
    Qt6::Test
    Qt6::Core
    Qt6::Network
)
```

**After:**
```cmake
qt_add_executable(tst_mytest
    tst_mytest.cpp
    # Only test-specific sources
)

target_link_libraries(tst_mytest PRIVATE
    FangTestLib  # Contains all common sources
    Qt6::Test
)
```

## Build Time Savings

**Before**: Each test compiled common sources independently
- TestBatchNewsParser: 23 source files
- TestFangFeedDiscovery: 15 source files
- TestWebPageGrabber: 8 source files
- **Total**: ~50+ duplicate compilations

**After**: Common sources compiled once in FangTestLib
- **Estimated savings**: 30-50% reduction in test build time

## Adding New Shared Sources

If you find a source file being compiled in 3+ tests, add it to `FangTestLib/CMakeLists.txt`:

1. Add the .cpp and .h files to the library
2. Update include directories if needed
3. Remove those files from individual test CMakeLists.txt
4. Link tests against FangTestLib

## Dependencies

This library automatically provides:
- `TidyLib` (for HTML parsing)
- `Qt6::Core`
- `Qt6::Network`

Tests only need to link against `FangTestLib` and `Qt6::Test`.
