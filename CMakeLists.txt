cmake_minimum_required(VERSION 3.16)

project(Fang VERSION 0.2.0 LANGUAGES CXX C)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt-specific settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 modules
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Qml
    Quick
    QuickControls2
    Widgets
    Network
    Sql
    Svg
    WebSockets
    HttpServer
    Test
    Gui
)

# Optional WebEngineQuick module
find_package(Qt6 COMPONENTS WebEngineQuick)

# Version management
if(DEFINED ENV{BUILD_NUMBER})
    set(BUILD_NUMBER $ENV{BUILD_NUMBER})
else()
    set(BUILD_NUMBER "-1")
endif()

set(APP_VERSION "0.2.${BUILD_NUMBER}")
file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/APP_VERSION" "${APP_VERSION}")

# Add TidyLib subdirectory
add_subdirectory(tidylib)

# Main application target
qt_add_executable(Fang
    # Sources from Fang.pro
    src/main.cpp
    src/models/FolderFeedItem.cpp
    src/models/ListModel.cpp
    src/models/NewsFeedInteractor.cpp
    src/models/NewsItem.cpp
    src/models/FeedItem.cpp
    src/models/NewsList.cpp
    src/operations/BookmarkOperation.cpp
    src/operations/DBOperationSynchronous.cpp
    src/operations/InsertFolderOperation.cpp
    src/operations/LoadFolderOperation.cpp
    src/operations/LoadNewsOperation.cpp
    src/operations/MarkAllReadOrUnreadOperation.cpp
    src/operations/UpdateFeedURLOperation.cpp
    src/parser/RawFeed.cpp
    src/parser/RawNews.cpp
    src/FangApp.cpp
    src/operations/OperationManager.cpp
    src/operations/Operation.cpp
    src/operations/UpdateFeedOperation.cpp
    src/utilities/Utilities.cpp
    src/operations/LoadAllFeedsOperation.cpp
    src/db/DB.cpp
    src/operations/DBOperation.cpp
    src/models/FeedValidator.cpp
    src/operations/AddFeedOperation.cpp
    src/operations/RemoveFeedOperation.cpp
    src/utilities/FaviconGrabber.cpp
    src/operations/SetBookmarkOperation.cpp
    src/utilities/WebPageGrabber.cpp
    src/operations/FaviconUpdateOperation.cpp
    src/models/AllNewsFeedItem.cpp
    src/utilities/ImageGrabber.cpp
    src/operations/UpdateTitleOperation.cpp
    src/parser/ParserInterface.cpp
    src/models/FangSettings.cpp
    src/utilities/RawFeedRewriter.cpp
    src/operations/LoadAllNewsOperation.cpp
    src/utilities/UnreadCountReader.cpp
    src/operations/UpdateOrdinalsOperation.cpp
    src/utilities/NetworkUtilities.cpp
    src/parser/OPMLParser.cpp
    src/utilities/SimpleStateMachine.cpp
    src/utilities/FeedDiscovery.cpp
    src/models/OPMLInteractor.cpp
    src/utilities/OPMLExport.cpp
    src/utilities/BatchFeedDiscovery.cpp
    src/FangObject.cpp
    src/parser/ParserXMLWorker.cpp
    src/network/FangNetworkAccessManager.cpp
    src/network/FangQQmlNetworkAccessManagerFactory.cpp
    src/notifications/NotificationBase.cpp
    src/utilities/SingleInstanceCheck.cpp
    src/operations/SetPinOperation.cpp
    src/models/PinnedFeedItem.cpp
    src/operations/LoadPinnedNewsOperation.cpp
    src/models/LisvelFeedItem.cpp
    src/operations/LisvelLoadNewsOperation.cpp
    src/operations/ExpireNewsOperation.cpp
    src/operations/SetDBSettingOperation.cpp
    src/db/DBSettings.cpp
    src/operations/GetAllDBSettingsOperation.cpp
    src/parser/NewsParser.cpp
    src/utilities/SimpleHTTPDownloader.cpp
    src/server/WebSocketServer.cpp
    src/server/WebServer.cpp

    # Headers from Fang.pro
    src/models/DBObject.h
    src/models/FolderFeedItem.h
    src/models/ListModel.h
    src/models/NewsFeedInteractor.h
    src/models/NewsItem.h
    src/models/FeedItem.h
    src/models/NewsList.h
    src/operations/BookmarkOperation.h
    src/operations/DBOperationSynchronous.h
    src/operations/InsertFolderOperation.h
    src/operations/LoadFolderOperation.h
    src/operations/LoadNewsOperation.h
    src/operations/MarkAllReadOrUnreadOperation.h
    src/operations/UpdateFeedURLOperation.h
    src/parser/RawFeed.h
    src/parser/RawNews.h
    src/FangApp.h
    src/operations/OperationManager.h
    src/operations/Operation.h
    src/operations/UpdateFeedOperation.h
    src/utilities/Utilities.h
    src/operations/LoadAllFeedsOperation.h
    src/db/DB.h
    src/operations/DBOperation.h
    src/models/FeedValidator.h
    src/operations/AddFeedOperation.h
    src/operations/RemoveFeedOperation.h
    src/utilities/FaviconGrabber.h
    src/operations/SetBookmarkOperation.h
    src/utilities/WebPageGrabber.h
    src/operations/FaviconUpdateOperation.h
    src/models/AllNewsFeedItem.h
    src/utilities/ImageGrabber.h
    src/operations/UpdateTitleOperation.h
    src/parser/ParserInterface.h
    src/models/FangSettings.h
    src/utilities/RawFeedRewriter.h
    src/operations/LoadAllNewsOperation.h
    src/utilities/UnreadCountReader.h
    src/operations/UpdateOrdinalsOperation.h
    src/utilities/NetworkUtilities.h
    src/parser/OPMLParser.h
    src/utilities/SimpleStateMachine.h
    src/utilities/FeedDiscovery.h
    src/models/OPMLInteractor.h
    src/utilities/OPMLExport.h
    src/utilities/BatchFeedDiscovery.h
    src/FangObject.h
    src/parser/ParserXMLWorker.h
    src/network/FangNetworkAccessManager.h
    src/network/FangQQmlNetworkAccessManagerFactory.h
    src/notifications/NotificationBase.h
    src/utilities/SingleInstanceCheck.h
    src/operations/SetPinOperation.h
    src/models/PinnedFeedItem.h
    src/operations/LoadPinnedNewsOperation.h
    src/models/LisvelFeedItem.h
    src/operations/LisvelLoadNewsOperation.h
    src/operations/ExpireNewsOperation.h
    src/operations/SetDBSettingOperation.h
    src/db/DBSettings.h
    src/operations/GetAllDBSettingsOperation.h
    src/db/DBSettingsKey.h
    src/parser/NewsParser.h
    src/utilities/SimpleHTTPDownloader.h
    src/server/WebSocketServer.h
    src/server/WebServer.h

    # Resource files (AUTORCC handles these)
    Resources.qrc
    qml/qml.qrc
    qml/images/images.qrc
    html/html.qrc
)

# Include directories
target_include_directories(Fang PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compile definitions
target_compile_definitions(Fang PRIVATE
    BUILD_NUMBER="${BUILD_NUMBER}"
    APP_VERSION="${APP_VERSION}"
)

# Link libraries
target_link_libraries(Fang PRIVATE
    TidyLib
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::Svg
    Qt6::WebSockets
    Qt6::HttpServer
)

# Optional WebEngineQuick
if(TARGET Qt6::WebEngineQuick)
    target_link_libraries(Fang PRIVATE Qt6::WebEngineQuick)
    target_compile_definitions(Fang PRIVATE QT_WEBVIEW_WEBENGINE_BACKEND)
endif()

# Platform-specific code - macOS
if(APPLE)
    target_sources(Fang PRIVATE
        src/notifications/NotificationMac.h
        src/notifications/NotificationMac.mm
    )

    target_link_options(Fang PRIVATE -Wl,-dead_strip)

    # Configure macOS bundle
    set(FULL_VERSION "${APP_VERSION}")
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
        ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
        @ONLY
    )

    set_target_properties(Fang PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
        MACOSX_BUNDLE_ICON_FILE mac.icns
    )

    set_source_files_properties(icons/mac.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
endif()

# Platform-specific code - Windows
if(WIN32)
    target_sources(Fang PRIVATE
        src/notifications/NotificationWindows.h
        src/notifications/NotificationWindows.cpp
        win32.rc
    )
endif()

# Platform-specific code - Android
if(ANDROID)
    set_target_properties(Fang PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
    )

    add_custom_command(TARGET Fang PRE_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/androidDeploy.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Preparing Android HTML assets"
    )
endif()

# Enable testing and add test subdirectory
enable_testing()
add_subdirectory(test)

# Installation
include(GNUInstallDirs)

install(TARGETS Fang
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt 6.3+ deployment
if(QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_generate_deploy_app_script(
        TARGET Fang
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()
