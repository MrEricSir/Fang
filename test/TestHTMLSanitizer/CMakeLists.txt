# TestHTMLSanitizer test executable
qt_add_executable(tst_htmlsanitizer
    tst_htmlsanitizer.cpp
    # App-level sources
    ${CMAKE_SOURCE_DIR}/src/utilities/HTMLSanitizer.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/HTMLSanitizer.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_htmlsanitizer PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link shared test library and Qt modules
target_link_libraries(tst_htmlsanitizer PRIVATE
    FangTestLib
    FangFeedDiscovery
    QTidyLibClassic
    Qt6::Test
    Qt6::Network
    Qt6::Gui
    Qt6::Svg
)

# Add to CTest
add_test(NAME HTMLSanitizer COMMAND tst_htmlsanitizer)
