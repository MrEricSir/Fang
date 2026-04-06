# TestLeakTracker test executable
qt_add_executable(tst_leaktracker
    tst_leaktracker.cpp
)

target_link_libraries(tst_leaktracker PRIVATE
    QObjectLeakTracker
    Qt6::Test
    Qt6::CorePrivate
)

# Enable leak checking for this test (only in Debug builds)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(tst_leaktracker PRIVATE QT_DEBUG)
endif()

add_test(NAME LeakTracker COMMAND tst_leaktracker)
