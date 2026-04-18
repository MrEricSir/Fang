# TestRawFeedRewriter test executable (uses TidyLib)
qt_add_executable(tst_rawfeedrewriter
    tst_rawfeedrewriter.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    # App-level sources
    ${CMAKE_SOURCE_DIR}/src/utilities/RawFeedRewriter.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/RawFeedRewriter.h
    ${CMAKE_SOURCE_DIR}/src/utilities/HTMLSanitizer.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/HTMLSanitizer.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_rawfeedrewriter PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_rawfeedrewriter PRIVATE
    FangTestLib
    FangFeedDiscovery
    QTidyLibClassic
    Qt6::Test
    Qt6::Network
    Qt6::Gui
    Qt6::Svg
)

# Add to CTest
add_test(NAME RawFeedRewriter COMMAND tst_rawfeedrewriter)
