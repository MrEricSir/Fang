# TestFangNetworkIntegration test executable
qt_add_executable(tst_fangnetworkintegration
    tst_fangnetworkintegration.cpp
    # Mock infrastructure
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/test/MockNetworkAccessManager.h
    # Network resilience sources
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.cpp
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.cpp
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/network/FangNetworkAccessManager.h
    ${CMAKE_SOURCE_DIR}/src/network/ResilientNetworkReply.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkRetryPolicy.h
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

# Add include directories for headers
target_include_directories(tst_fangnetworkintegration PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Link Qt modules
target_link_libraries(tst_fangnetworkintegration PRIVATE
    Qt6::Test
    Qt6::Network
    Qt6::Gui
)

# Add to CTest
add_test(NAME FangNetworkIntegration COMMAND tst_fangnetworkintegration)
