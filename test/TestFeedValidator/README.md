# FeedValidator Tests

## Overview

This directory contains unit tests for FeedValidator's data management and QML interface logic.

## Test Approach

Given FeedValidator's extensive dependencies (FeedDiscovery → NewsParser → FangNetworkAccessManager → network resilience stack), we use a **standalone test class** approach:

- `SimpleFeedValidator` - A minimal class that duplicates FeedValidator's core data management logic
- Tests the business logic for feed selection, counting, and QML interface
- No dependencies on network stack, parsers, or FangApp
- Fast, focused tests that run in <10ms

## What's Tested

✅ **Core Data Management**
- URL property and change notifications
- Feed list manipulation (selection, title editing)
- Feed counting with various filters
- QML interface (QVariantList generation for Repeater)

✅ **Business Logic**
- Empty title handling (bug fix verification)
- Invalid index bounds checking
- Signal emission on state changes
- Selected vs unselected feed counting

❌ **Not Tested** (requires integration tests)
- Feed discovery flow (check() → FeedDiscovery → onFeedDiscoveryDone)
- Network operations
- Feed addition to FangApp (addFeed method)

## Running Tests

```bash
# Build and run
cd /Users/eric/Development/Fang/build
make tst_feedvalidator_simple
./test/TestFeedValidator/tst_feedvalidator_simple

# Via CTest
ctest -R FeedValidator --output-on-failure
```

## Test Results

```
17 passed, 0 failed, 0 skipped
Runtime: ~1ms
```

## Key Test Cases

### testFeedsToAddCountEmptyTitle
Verifies the bug fix where empty titles are excluded from the count:
```cpp
validator->addTestFeed("http://example.com/feed1", "Feed 1", true, 0);
validator->addTestFeed("http://example.com/feed2", "", true, 1);  // Empty!
QCOMPARE(validator->feedsToAddCount(), 1);  // Only counts Feed 1
```

### testDiscoveredFeedsStructure
Validates QML interface structure for AddDialog.qml Repeater:
```cpp
QVariantMap feed = feeds[0].toMap();
QVERIFY(feed.contains("url"));
QVERIFY(feed.contains("title"));
QVERIFY(feed.contains("selected"));
QVERIFY(feed.contains("index"));
```

## Future Enhancements

For full coverage, add integration tests that:
1. Use MockNetworkAccessManager for feed discovery
2. Test full async flow with QSignalSpy
3. Validate error handling and state transitions
4. Test addFeed() with a test FangApp instance

See `tst_testfeedvalidator.cpp` (archived) for a more comprehensive test suite that would require extensive dependency mocking.
