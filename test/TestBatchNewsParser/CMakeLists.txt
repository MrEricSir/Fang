# TestBatchNewsParser test executable
qt_add_executable(tst_testbatchnewsparser
    tst_testbatchnewsparser.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.h
)

# Link shared test library (contains all common sources)
target_link_libraries(tst_testbatchnewsparser PRIVATE
    FangTestLib
    Qt6::Test
)

# Add to CTest
add_test(NAME BatchNewsParser COMMAND tst_testbatchnewsparser)
