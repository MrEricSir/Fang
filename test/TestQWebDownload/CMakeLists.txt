# TestQWebDownload test executable
qt_add_executable(tst_qwebdownload
    tst_qwebdownload.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
)

# Link shared test library and Qt modules
target_link_libraries(tst_qwebdownload PRIVATE
    FangTestLib
    QWebDownload
    Qt6::Test
)

# Add to CTest
add_test(NAME QWebDownload COMMAND tst_qwebdownload)
