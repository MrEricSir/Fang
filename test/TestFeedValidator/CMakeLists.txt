# Simple FeedValidator test - tests data management logic only
# Does not require FeedDiscovery, network stack, or FangApp

qt_add_executable(tst_feedvalidator_simple
    tst_feedvalidator_simple.cpp
)

target_include_directories(tst_feedvalidator_simple PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/models
)

target_link_libraries(tst_feedvalidator_simple PRIVATE
    Qt6::Test
    Qt6::Core
)

add_test(NAME FeedValidatorSimple COMMAND tst_feedvalidator_simple)
