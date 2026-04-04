# TestDB test executable
qt_add_executable(tst_db
    tst_db.cpp
    # Database
    ${CMAKE_SOURCE_DIR}/src/db/DB.cpp
    # Utilities
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Base classes
    ${CMAKE_SOURCE_DIR}/src/utilities/QObjectLeakTracker.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/db/DB.h
    ${CMAKE_SOURCE_DIR}/src/utilities/QObjectLeakTracker.h
    # Resources (SQL migration files)
    ${CMAKE_SOURCE_DIR}/Resources.qrc
)

# Add include directories
target_include_directories(tst_db PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_db PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::CorePrivate
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME DB COMMAND tst_db)
