# TestUpdateChecker test executable
qt_add_executable(tst_updatechecker
    tst_updatechecker.cpp
    # Mocks
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.cpp
    ${CMAKE_SOURCE_DIR}/test/MockFeedSource.h
    ${CMAKE_SOURCE_DIR}/test/MockFangSettings.h
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/UpdateChecker.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/UpdateChecker.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SettingsInterface.h
)

# Include directories
target_include_directories(tst_updatechecker PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/test
)

# Compile definitions
target_compile_definitions(tst_updatechecker PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
    PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    APP_VERSION="${APP_VERSION}"
    UPDATECHECKER_NO_FANGAPP
)

# Link shared test library and Qt modules
target_link_libraries(tst_updatechecker PRIVATE
    FangTestLib
    FangFeedDiscovery
    Qt6::Test
)

# Add to CTest
add_test(NAME UpdateChecker COMMAND tst_updatechecker)
