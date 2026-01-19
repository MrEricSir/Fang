# TestFangObject test executable
qt_add_executable(tst_fangobject
    tst_fangobject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

target_include_directories(tst_fangobject PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(tst_fangobject PRIVATE
    Qt6::Test
    Qt6::Core
)

# Enable leak checking for this test (only in Debug builds)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(tst_fangobject PRIVATE QT_DEBUG)
endif()

add_test(NAME FangObject COMMAND tst_fangobject)
