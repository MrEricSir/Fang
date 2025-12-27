# TestFangFeedDiscovery test executable (uses TidyLib)
qt_add_executable(tst_testfangfeeddiscovery
    tst_testfangfeeddiscovery.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleStateMachine.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/utilities/FeedDiscovery.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleStateMachine.h
    ${CMAKE_SOURCE_DIR}/src/utilities/WebPageGrabber.h
    ${CMAKE_SOURCE_DIR}/src/parser/OPMLParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/utilities/SimpleHTTPDownloader.h
    ${CMAKE_SOURCE_DIR}/src/utilities/NetworkUtilities.h
)

# Compile definitions for test data paths
target_compile_definitions(tst_testfangfeeddiscovery PRIVATE
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}/"
    PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

# Link TidyLib and Qt modules
target_link_libraries(tst_testfangfeeddiscovery PRIVATE
    TidyLib
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME FangFeedDiscovery COMMAND tst_testfangfeeddiscovery)
