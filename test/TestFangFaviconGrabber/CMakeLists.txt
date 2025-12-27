# TestFangFaviconGrabber test executable (uses TidyLib)
qt_add_executable(tst_testfangfavicongrabbertest
    tst_testfangfavicongrabbertest.cpp
    # Mock network manager for offline testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/FaviconGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleStateMachine.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/utilities/FaviconGrabber.h
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleStateMachine.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
)

# Include directories for FangLogging.h
target_include_directories(tst_testfangfavicongrabbertest PRIVATE
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangfavicongrabbertest PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
)

# Link TidyLib and Qt modules
target_link_libraries(tst_testfangfavicongrabbertest PRIVATE
    TidyLib
    Qt6::Test
    Qt6::Network
    Qt6::Gui
)

# Add to CTest
add_test(NAME FangFaviconGrabber COMMAND tst_testfangfavicongrabbertest)
