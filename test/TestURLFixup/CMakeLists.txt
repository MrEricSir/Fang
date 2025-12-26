# TestURLFixup test executable
qt_add_executable(tst_urlfixup
    tst_urlfixup.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.h
)

# Link Qt modules
target_link_libraries(tst_urlfixup PRIVATE
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME URLFixup COMMAND tst_urlfixup)
