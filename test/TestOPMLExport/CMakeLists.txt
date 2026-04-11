# TestOPMLExport test executable
qt_add_executable(tst_opmlexport
    tst_opmlexport.cpp
)

# Link Qt modules
target_link_libraries(tst_opmlexport PRIVATE
    FangFeedParser
    Qt6::Test
)

# Add to CTest
add_test(NAME OPMLExport COMMAND tst_opmlexport)
