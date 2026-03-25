# TestFangFaviconGrabber test executable
qt_add_executable(tst_testfangfavicongrabbertest
    tst_testfangfavicongrabbertest.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    # App-level sources
    ${CMAKE_SOURCE_DIR}/src/utilities/FaviconGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FaviconGrabber.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangfavicongrabbertest PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_testfangfavicongrabbertest PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME FangFaviconGrabber COMMAND tst_testfangfavicongrabbertest)
