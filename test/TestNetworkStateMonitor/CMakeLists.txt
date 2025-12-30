# TestNetworkStateMonitor test executable
qt_add_executable(tst_networkstatemonitor
    tst_networkstatemonitor.cpp
    # Shared sources from main project
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Include corresponding headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/network/NetworkStateMonitor.h
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.h
)

# Include directories for FangLogging.h
target_include_directories(tst_networkstatemonitor PRIVATE
    ${CMAKE_SOURCE_DIR}/src/utilities
)

# Link Qt modules
target_link_libraries(tst_networkstatemonitor PRIVATE
    Qt6::Test
    Qt6::Network
)

# Add to CTest
add_test(NAME NetworkStateMonitor COMMAND tst_networkstatemonitor)
