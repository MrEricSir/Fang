# TestNetworkRetryPolicy test executable
qt_add_executable(tst_networkretrypolicy
    tst_networkretrypolicy.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
)

# Link Qt modules
target_link_libraries(tst_networkretrypolicy PRIVATE
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME NetworkRetryPolicy COMMAND tst_networkretrypolicy)
