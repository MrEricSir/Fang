# TestSearch test executable
qt_add_executable(tst_search
    tst_search.cpp
)

# Link Qt modules
target_link_libraries(tst_search PRIVATE
    Qt6::Test
    Qt6::Sql
    Qt6::Gui
)

# Add to CTest
add_test(NAME Search COMMAND tst_search)
