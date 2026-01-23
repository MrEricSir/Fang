# TestFangSimpleStateMachine test executable
qt_add_executable(tst_testfangsimplestatemachine
    tst_testfangsimplestatemachine.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/utilities/QSimpleStateMachine.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangsimplestatemachine PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link Qt Test module
target_link_libraries(tst_testfangsimplestatemachine PRIVATE
    Qt6::Test
)

# Add to CTest
add_test(NAME FangSimpleStateMachine COMMAND tst_testfangsimplestatemachine)
