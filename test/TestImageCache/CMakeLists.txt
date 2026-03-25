# TestImageCache test executable
qt_add_executable(tst_imagecache
    tst_imagecache.cpp
)

# Link shared test library and Qt modules
target_link_libraries(tst_imagecache PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
    Qt6::Gui
)

# Add to CTest
add_test(NAME ImageCache COMMAND tst_imagecache)
