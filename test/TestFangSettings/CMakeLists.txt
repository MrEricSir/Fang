# TestFangSettings test executable
qt_add_executable(tst_fangsettings
    tst_fangsettings.cpp
    # Mocks
    ${CMAKE_SOURCE_DIR}/test/MockDBSettings.h
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/models/FangSettings.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FangSettings.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SettingsInterface.h
    ${CMAKE_SOURCE_DIR}/src/db/DBSettingsInterface.h
    ${CMAKE_SOURCE_DIR}/src/db/DBSettingsKey.h
    ${CMAKE_SOURCE_DIR}/src/utilities/ErrorHandling.h
)

# Include directories
target_include_directories(tst_fangsettings PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/models
    ${CMAKE_SOURCE_DIR}/src/db
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/test
)

# Compile definitions
target_compile_definitions(tst_fangsettings PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
    PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link Qt modules
target_link_libraries(tst_fangsettings PRIVATE
    Qt6::Test
    Qt6::Quick
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME FangSettings COMMAND tst_fangsettings)
