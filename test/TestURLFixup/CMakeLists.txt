# TestURLFixup test executable
qt_add_executable(tst_urlfixup
    tst_urlfixup.cpp
)

# Link libraries
target_link_libraries(tst_urlfixup PRIVATE
    FangFeedDiscovery
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME URLFixup COMMAND tst_urlfixup)
