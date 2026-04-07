# TestLisvelFeedItem test executable
qt_add_executable(tst_lisvelfeeditem
    tst_lisvelfeeditem.cpp
    # Models
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
)

# Add include directories
target_include_directories(tst_lisvelfeeditem PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_lisvelfeeditem PRIVATE
    FangTestLib
    FangFeedParser
    Qt6::Test
    Qt6::Sql
)

# Add to CTest
add_test(NAME LisvelFeedItem COMMAND tst_lisvelfeeditem)
