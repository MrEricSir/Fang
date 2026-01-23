# TestFangFeedDiscovery test executable
qt_add_executable(tst_testfangfeeddiscovery
    tst_testfangfeeddiscovery.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.h
    ${CMAKE_SOURCE_DIR}/test/MockWebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/test/MockBatchNewsParser.h
    # FeedDiscovery (not in FangTestLib to avoid duplicate MOC symbols for QSimpleStateMachine)
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.h
    # Additional sources
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangfeeddiscovery PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
    PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link shared test library and Qt modules
target_link_libraries(tst_testfangfeeddiscovery PRIVATE
    FangTestLib
    QSimpleStateMachine::QSimpleStateMachine
    Qt6::Test
)

# Add to CTest
add_test(NAME FangFeedDiscovery COMMAND tst_testfangfeeddiscovery)
