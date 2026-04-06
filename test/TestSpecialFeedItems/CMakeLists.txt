# TestSpecialFeedItems test executable
qt_add_executable(tst_specialfeeditems
    tst_specialfeeditems.cpp
    # Utilities
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    # Models
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/PinnedFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/AllNewsFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/SearchFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FolderFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/PinnedFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/AllNewsFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/SearchFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/FolderFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
)

# Add include directories
target_include_directories(tst_specialfeeditems PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_specialfeeditems PRIVATE
    FangFeedParser
    QObjectLeakTracker
    Qt6::Test
    Qt6::Core
    Qt6::CorePrivate
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME SpecialFeedItems COMMAND tst_specialfeeditems)
