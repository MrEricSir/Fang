# TestSingleInstanceCheck test executable
qt_add_executable(tst_testsingleinstancecheck
    tst_testsingleinstancecheck.cpp
    # Source files under test
    ${CMAKE_SOURCE_DIR}/src/utilities/SingleInstanceCheck.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SingleInstanceCheck.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

# Include directories
target_include_directories(tst_testsingleinstancecheck PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Link libraries
target_link_libraries(tst_testsingleinstancecheck PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Network
    Qt6::Gui
)

# Add to CTest
add_test(NAME SingleInstanceCheck COMMAND tst_testsingleinstancecheck)
