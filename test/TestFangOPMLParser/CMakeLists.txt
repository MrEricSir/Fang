# TestFangOPMLParser test executable
qt_add_executable(tst_testfangopmlparser
    tst_testfangopmlparser.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangopmlparser PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_testfangopmlparser PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME FangOPMLParser COMMAND tst_testfangopmlparser)
