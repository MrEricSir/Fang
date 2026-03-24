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
    ${CMAKE_SOURCE_DIR}/src/parser/FeedFetcher.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/FeedFetcher.h
    ${CMAKE_SOURCE_DIR}/src/parser/FeedSource.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/FeedSource.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
)

# Include directories
target_include_directories(tst_updatechecker PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/network
    ${CMAKE_SOURCE_DIR}/test
)

# Compile definitions
target_compile_definitions(tst_updatechecker PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
    PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    APP_VERSION="${APP_VERSION}"
    UPDATECHECKER_NO_FANGAPP
)

# Link Qt Test and Network modules
target_link_libraries(tst_updatechecker PRIVATE
    FangFeedParser
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME UpdateChecker COMMAND tst_updatechecker)
