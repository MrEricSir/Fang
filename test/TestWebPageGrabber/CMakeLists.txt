# TestWebPageGrabber test executable (uses TidyLib)
qt_add_executable(tst_testwebpagegrabber
    tst_testwebpagegrabber.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
)

# Include directories for FangLogging.h
target_include_directories(tst_testwebpagegrabber PRIVATE
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Compile definitions for test data paths
target_compile_definitions(tst_testwebpagegrabber PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link TidyLib and Qt modules
target_link_libraries(tst_testwebpagegrabber PRIVATE
    TidyLib
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME WebPageGrabber COMMAND tst_testwebpagegrabber)
