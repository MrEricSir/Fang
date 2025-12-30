# TestResilientNetworkReply test executable
qt_add_executable(tst_resilientnetworkreply
    tst_resilientnetworkreply.cpp
    # Mock network manager for testing
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.cpp
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.h
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
)

# Include directories for FangLogging.h
target_include_directories(tst_resilientnetworkreply PRIVATE
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Link Qt modules
target_link_libraries(tst_resilientnetworkreply PRIVATE
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME ResilientNetworkReply COMMAND tst_resilientnetworkreply)
