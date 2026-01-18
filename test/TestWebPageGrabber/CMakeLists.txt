# TestWebPageGrabber test executable
qt_add_executable(tst_testwebpagegrabber
    tst_testwebpagegrabber.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
)

# Compile definitions for test data paths
target_compile_definitions(tst_testwebpagegrabber PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_testwebpagegrabber PRIVATE
    FangTestLib
    Qt6::Test
)

# Add to CTest
add_test(NAME WebPageGrabber COMMAND tst_testwebpagegrabber)
