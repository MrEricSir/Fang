# TestFeedURLNormalization test executable
qt_add_executable(tst_feedurlnormalization
    tst_feedurlnormalization.cpp
)

# Link Qt modules
target_link_libraries(tst_feedurlnormalization PRIVATE
    Qt6::Test
)

# Add to CTest
add_test(NAME FeedURLNormalization COMMAND tst_feedurlnormalization)
