# TestNewsItem test executable
qt_add_executable(tst_newsitem
    tst_newsitem.cpp
    # Utilities
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Models
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

# Add include directories
target_include_directories(tst_newsitem PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_newsitem PRIVATE
    Qt6::Test
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME NewsItem COMMAND tst_newsitem)
