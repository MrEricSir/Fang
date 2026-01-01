# TestOPMLExport test executable
qt_add_executable(tst_opmlexport
    tst_opmlexport.cpp
    # OPML Export
    ${CMAKE_SOURCE_DIR}/src/utilities/OPMLExport.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/OPMLExport.h
    # Models
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
)

# Add include directories
target_include_directories(tst_opmlexport PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_opmlexport PRIVATE
    Qt6::Test
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME OPMLExport COMMAND tst_opmlexport)
