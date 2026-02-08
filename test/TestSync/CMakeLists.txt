# TestSync - Unit tests for sync functionality

qt_add_executable(tst_sync
    tst_sync.cpp
    MockCloudStorageProvider.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/CloudStorageProvider.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/SyncData.cpp
)

target_include_directories(tst_sync PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(tst_sync PRIVATE
    Qt6::Core
    Qt6::Test
    Qt6::Network
)

# Enable coverage if configured
if(ENABLE_COVERAGE)
    target_compile_options(tst_sync PRIVATE --coverage -O0 -g)
    target_link_options(tst_sync PRIVATE --coverage)
endif()

add_test(NAME tst_sync COMMAND tst_sync)
