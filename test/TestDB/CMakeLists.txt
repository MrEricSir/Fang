# TestDB test executable
qt_add_executable(tst_db
    tst_db.cpp
    # Database
    ${CMAKE_SOURCE_DIR}/src/db/DB.cpp
    # Base classes
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/db/DB.h
    # Resources (SQL migration files)
    ${CMAKE_SOURCE_DIR}/Resources.qrc
)

# Add include directories
target_include_directories(tst_db PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_db PRIVATE
    FangTestLib
    Qt6::Test
    Qt6::Sql
)

# Add to CTest
add_test(NAME DB COMMAND tst_db)
