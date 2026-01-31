# TestFangOPMLParser test executable
qt_add_executable(tst_testfangopmlparser
    tst_testfangopmlparser.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangopmlparser PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link Qt Test module
target_link_libraries(tst_testfangopmlparser PRIVATE
    Qt6::Test
    Qt6::Gui
)

# Add to CTest
add_test(NAME FangOPMLParser COMMAND tst_testfangopmlparser)
