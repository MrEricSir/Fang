# TestNetworkDownloadCore test executable
qt_add_executable(tst_networkdownloadcore
    tst_networkdownloadcore.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
)

# Link shared test library and Qt modules
target_link_libraries(tst_networkdownloadcore PRIVATE
    FangTestLib
    Qt6::Test
)

# Add to CTest
add_test(NAME NetworkDownloadCore COMMAND tst_networkdownloadcore)
