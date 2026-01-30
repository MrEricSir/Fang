# TestImageGrabber test executable
qt_add_executable(tst_imagegrabber
    tst_imagegrabber.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
)

# Link shared test library and Qt modules
target_link_libraries(tst_imagegrabber PRIVATE
    FangTestLib
    Qt6::Test
    Qt6::Gui
)

# Add to CTest
add_test(NAME ImageGrabber COMMAND tst_imagegrabber)
