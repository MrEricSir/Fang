# TestWebRetryPolicy test executable
qt_add_executable(tst_webretrypolicy
    tst_webretrypolicy.cpp
)

# Link libraries
target_link_libraries(tst_webretrypolicy PRIVATE
    QWebDownload
    Qt6::Test
)

# Add to CTest
add_test(NAME WebRetryPolicy COMMAND tst_webretrypolicy)
