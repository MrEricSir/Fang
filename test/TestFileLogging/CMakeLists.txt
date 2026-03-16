# TestFileLogging test executable
qt_add_executable(tst_filelogging
    tst_filelogging.cpp
)

target_link_libraries(tst_filelogging PRIVATE
    FangTestLib
    Qt6::Test
)

add_test(NAME FileLogging COMMAND tst_filelogging)
