# TestDatabaseOperations test executable
qt_add_executable(tst_databaseoperations
    tst_databaseoperations.cpp
)

# Link Qt modules
target_link_libraries(tst_databaseoperations PRIVATE
    Qt6::Test
    Qt6::Sql
    Qt6::Gui
)

# Add to CTest
add_test(NAME DatabaseOperations COMMAND tst_databaseoperations)
