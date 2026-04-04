# TestFaviconGrabber test executable
qt_add_executable(tst_favicongrabber
    tst_favicongrabber.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    # App-level sources
    ${CMAKE_SOURCE_DIR}/src/utilities/FaviconGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FaviconGrabber.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_favicongrabber PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_favicongrabber PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME FaviconGrabber COMMAND tst_favicongrabber)
