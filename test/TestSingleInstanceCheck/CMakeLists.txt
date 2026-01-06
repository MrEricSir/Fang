# TestQSingleInstanceCheck test executable
qt_add_executable(tst_testqsingleinstancecheck
    tst_testqsingleinstancecheck.cpp
    # Source files under test
    ${CMAKE_SOURCE_DIR}/src/utilities/QSingleInstanceCheck.h
)

# Include directories
target_include_directories(tst_testqsingleinstancecheck PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Link libraries
target_link_libraries(tst_testqsingleinstancecheck PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Network
    Qt6::Gui
)

# Add to CTest
add_test(NAME QSingleInstanceCheck COMMAND tst_testqsingleinstancecheck)
