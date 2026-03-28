# TestNetworkRetryPolicy test executable
qt_add_executable(tst_networkretrypolicy
    tst_networkretrypolicy.cpp
)

# Link libraries
target_link_libraries(tst_networkretrypolicy PRIVATE
    FangFeedDiscovery
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME NetworkRetryPolicy COMMAND tst_networkretrypolicy)
