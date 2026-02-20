# TestSearchOperation test executable
qt_add_executable(tst_searchoperation
    tst_searchoperation.cpp
    # Utilities
    ${CMAKE_SOURCE_DIR}/src/utilities/FangLogging.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/Utilities.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/UnreadCountReader.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/UnreadCountReader.h
    # Core
    ${CMAKE_SOURCE_DIR}/src/FangObject.cpp
    ${CMAKE_SOURCE_DIR}/src/db/DB.cpp
    # Models
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/SearchFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    # Operations
    ${CMAKE_SOURCE_DIR}/src/operations/AsyncOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/SyncOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/OperationManager.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/LoadNewsOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/LisvelLoadNewsOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/SearchNewsOperation.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/SearchFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsPosition.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/db/DB.h
    ${CMAKE_SOURCE_DIR}/src/operations/AsyncOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/SyncOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/OperationManager.h
    ${CMAKE_SOURCE_DIR}/src/operations/LoadNewsOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/LisvelLoadNewsOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/SearchNewsOperation.h
)

# Add include directories
target_include_directories(tst_searchoperation PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_searchoperation PRIVATE
    Qt6::Test
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME SearchOperation COMMAND tst_searchoperation)
