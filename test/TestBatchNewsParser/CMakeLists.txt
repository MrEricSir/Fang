# TestBatchNewsParser test executable
qt_add_executable(tst_testbatchnewsparser
    tst_testbatchnewsparser.cpp
    # Mock objects for testing
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNewsParser.h
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/parser/BatchNewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/BatchNewsParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/NewsParser.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserInterface.h
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/ParserXMLWorker.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawFeed.h
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/RawNews.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.h
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.cpp
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
)

# Include directories
target_include_directories(tst_testbatchnewsparser PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/parser
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Link libraries
target_link_libraries(tst_testbatchnewsparser PRIVATE
    TidyLib
    Qt6::Test
    Qt6::Core
    Qt6::Network
)

# Add to CTest
add_test(NAME BatchNewsParser COMMAND tst_testbatchnewsparser)
