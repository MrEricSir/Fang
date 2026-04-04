# TestLeakTracker test executable
qt_add_executable(tst_leaktracker
    tst_leaktracker.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/QObjectLeakTracker.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/QObjectLeakTracker.h
)

target_include_directories(tst_leaktracker PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(tst_leaktracker PRIVATE
    FangFeedParser
    Qt6::Test
    Qt6::Core
    Qt6::CorePrivate
)

# Enable leak checking for this test (only in Debug builds)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(tst_leaktracker PRIVATE QT_DEBUG)
endif()

add_test(NAME LeakTracker COMMAND tst_leaktracker)
