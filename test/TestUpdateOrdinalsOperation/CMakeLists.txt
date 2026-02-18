# TestUpdateOrdinalsOperation test executable
qt_add_executable(tst_updateordinalsoperation
    tst_updateordinalsoperation.cpp
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
    ${CMAKE_SOURCE_DIR}/src/models/FolderFeedItem.cpp
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.cpp
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.cpp
    # Operations
    ${CMAKE_SOURCE_DIR}/src/operations/Operation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperation.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperationSynchronous.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/OperationManager.cpp
    ${CMAKE_SOURCE_DIR}/src/operations/UpdateOrdinalsOperation.cpp
    # Headers for AUTOMOC
    ${CMAKE_SOURCE_DIR}/src/models/FeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/LisvelFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/FolderFeedItem.h
    ${CMAKE_SOURCE_DIR}/src/models/ListModel.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsList.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsItem.h
    ${CMAKE_SOURCE_DIR}/src/models/NewsPosition.h
    ${CMAKE_SOURCE_DIR}/src/models/DBObject.h
    ${CMAKE_SOURCE_DIR}/src/FangObject.h
    ${CMAKE_SOURCE_DIR}/src/db/DB.h
    ${CMAKE_SOURCE_DIR}/src/operations/Operation.h
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperation.h
    ${CMAKE_SOURCE_DIR}/src/operations/DBOperationSynchronous.h
    ${CMAKE_SOURCE_DIR}/src/operations/OperationManager.h
    ${CMAKE_SOURCE_DIR}/src/operations/UpdateOrdinalsOperation.h
)

# Add include directories
target_include_directories(tst_updateordinalsoperation PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Link Qt modules
target_link_libraries(tst_updateordinalsoperation PRIVATE
    Qt6::Test
    Qt6::Gui
    Qt6::Sql
)

# Add to CTest
add_test(NAME UpdateOrdinalsOperation COMMAND tst_updateordinalsoperation)
