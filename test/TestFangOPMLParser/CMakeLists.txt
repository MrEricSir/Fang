# TestOPMLParser test executable
qt_add_executable(tst_opmlparser
    tst_opmlparser.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_opmlparser PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_opmlparser PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME OPMLParser COMMAND tst_opmlparser)
