# TestFeedOperations test executable
qt_add_executable(tst_feedoperations
    tst_feedoperations.cpp
    # Utilities
    ${CMAKE_SOURCE_DIR}/src/utilities/Utilities.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/UnreadCountReader.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities/UnreadCountReader.h
    # Core
    ${CMAKE_SOURCE_DIR}/src/db/DB.cpp
    # Models
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/FolderFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/AllNewsFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/PinnedFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    # Operations
    ${CMAKE_SOURCE_DIR}/src/operations/AsyncOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/SyncOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/OperationManager.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/SetDBSettingOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/GetAllDBSettingsOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/UpdateTitleOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/UpdateFeedURLOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/SetFolderOpenOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/SetPinOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/InsertFolderOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/ExpireNewsOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/ReloadNewsOperation.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/FolderFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/AllNewsFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/PinnedFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsPosition.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
    ${CMAKE_SOURCE_DIR}/src/db/DB.h
    ${CMAKE_SOURCE_DIR}/src/operations/AsyncOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/SyncOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/OperationManager.h
    ${CMAKE_SOURCE_DIR}/src/operations/SetDBSettingOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/GetAllDBSettingsOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/UpdateTitleOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/UpdateFeedURLOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/SetFolderOpenOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/SetPinOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/InsertFolderOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/ExpireNewsOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/ReloadNewsOperation.h
)

# Add include directories
target_include_directories(tst_feedoperations PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_feedoperations PRIVATE
    FangTestLib
    FangFeedParser
    Qt6::Test
    Qt6::Sql
)

# Add to CTest
add_test(NAME FeedOperations COMMAND tst_feedoperations)
