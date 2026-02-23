cmake_minimum_required(VERSION 3.16)

# Version
project(Fang VERSION 0.2.11 LANGUAGES CXX C)
# Set suffix to:
# "-beta.1"  Beta
# "-rc.1"    Release candidate
# ""         Release
set(VERSION_SUFFIX "-beta.1")

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage option - enabled by default for Debug builds when lcov is available
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Check if lcov is available
    find_program(LCOV_AVAILABLE lcov)
    if(LCOV_AVAILABLE)
        option(ENABLE_COVERAGE "Enable code coverage" ON)
    else()
        option(ENABLE_COVERAGE "Enable code coverage" OFF)
    endif()
else()
    option(ENABLE_COVERAGE "Enable code coverage" OFF)
endif()

# Parallel compilation settings
# Automatically use all available CPU cores for faster builds
if(NOT DEFINED CMAKE_BUILD_PARALLEL_LEVEL)
    include(ProcessorCount)
    ProcessorCount(CPU_CORES)
    if(CPU_CORES GREATER 0)
        set(CMAKE_BUILD_PARALLEL_LEVEL ${CPU_CORES})
        message(STATUS "Parallel build enabled with ${CPU_CORES} cores")
    endif()
endif()

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
    Test
    Gui
    HttpServer
)

# Optional modules
find_package(Qt6 COMPONENTS WebEngineQuick)


if(DEFINED ENV{BUILD_NUMBER})
    set(BUILD_NUMBER $ENV{BUILD_NUMBER})
    set(APP_VERSION "${PROJECT_VERSION}.${BUILD_NUMBER}${VERSION_SUFFIX}")
else()
    set(APP_VERSION "${PROJECT_VERSION}${VERSION_SUFFIX}")
endif()

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/APP_VERSION" "${APP_VERSION}")

# Add TidyLib subdirectory
add_subdirectory(external/tidylib)

# Add QSingleInstanceCheck directory
add_subdirectory(external/QSingleInstanceCheck)

# Add QSimpleStateMachine directory
add_subdirectory(external/QSimpleStateMachine)

# Add QMLRearrangeableTreeView directory
add_subdirectory(external/QMLRearrangeableTreeView)

# Main application target
qt_add_executable(Fang WIN32
    # Sources
    src/main.cpp
    src/models/FolderFeedItem.cpp
    src/models/ListModel.cpp
    src/models/NewsFeedInteractor.cpp
    src/models/NewsItem.cpp
    src/models/FeedItem.cpp
    src/models/NewsList.cpp
    src/operations/BookmarkOperation.cpp
    src/operations/AsyncOperation.cpp
    src/operations/SyncOperation.cpp
    src/operations/InsertFolderOperation.cpp
    src/operations/LoadFolderOperation.cpp
    src/operations/LoadNewsOperation.cpp
    src/operations/MarkAllReadOrUnreadOperation.cpp
    src/operations/UpdateFeedURLOperation.cpp
    src/parser/RawFeed.cpp
    src/parser/RawNews.cpp
    src/FangApp.cpp
    src/operations/OperationManager.cpp
    src/operations/UpdateFeedOperation.cpp
    src/utilities/Utilities.cpp
    src/operations/LoadAllFeedsOperation.cpp
    src/db/DB.cpp
    src/operations/DBOperation.cpp
    src/models/FeedValidator.cpp
    src/operations/AddFeedOperation.cpp
    src/operations/RemoveFeedOperation.cpp
    src/utilities/FaviconGrabber.cpp
    src/utilities/FangLogging.cpp
    src/operations/SetBookmarkOperation.cpp
    src/operations/SetFolderOpenOperation.cpp
    src/operations/ReloadNewsOperation.cpp
    src/utilities/WebPageGrabber.cpp
    src/operations/FaviconUpdateOperation.cpp
    src/models/AllNewsFeedItem.cpp
    src/utilities/ImageGrabber.cpp
    src/operations/UpdateTitleOperation.cpp
    src/parser/ParserInterface.cpp
    src/models/FangSettings.cpp
    src/utilities/RawFeedRewriter.cpp
    src/utilities/HTMLSanitizer.cpp
    src/operations/LoadAllNewsOperation.cpp
    src/utilities/UnreadCountReader.cpp
    src/operations/UpdateOrdinalsOperation.cpp
    src/utilities/NetworkUtilities.cpp
    src/parser/OPMLParser.cpp
    src/utilities/FeedDiscovery.cpp
    src/utilities/UpdateChecker.cpp
    src/models/OPMLInteractor.cpp
    src/utilities/OPMLExport.cpp
    src/utilities/BatchFeedDiscovery.cpp
    src/FangObject.cpp
    src/parser/ParserXMLWorker.cpp
    src/network/FangNetworkAccessManager.cpp
    src/network/FangQQmlNetworkAccessManagerFactory.cpp
    src/network/NetworkRetryPolicy.cpp
    src/network/BatchDownloadCore.cpp
    src/notifications/Notification.cpp
    src/operations/SetPinOperation.cpp
    src/models/PinnedFeedItem.cpp
    src/models/SearchFeedItem.cpp
    src/operations/LoadPinnedNewsOperation.cpp
    src/models/LisvelFeedItem.cpp
    src/operations/LisvelLoadNewsOperation.cpp
    src/operations/SearchNewsOperation.cpp
    src/operations/ExpireNewsOperation.cpp
    src/operations/SetDBSettingOperation.cpp
    src/db/DBSettings.cpp
    src/db/DBSettingsInterface.cpp
    src/operations/GetAllDBSettingsOperation.cpp
    src/parser/BatchNewsParser.h
    src/parser/BatchNewsParser.cpp
    src/parser/NewsParser.cpp
    src/network/NetworkDownloadCore.cpp
    src/server/WebSocketServer.cpp
    src/server/WebServer.cpp

    # Headers
    src/models/DBObject.h
    src/models/FolderFeedItem.h
    src/models/ListModel.h
    src/models/NewsFeedInteractor.h
    src/models/NewsItem.h
    src/models/FeedItem.h
    src/models/NewsList.h
    src/operations/BookmarkOperation.h
    src/operations/AsyncOperation.h
    src/operations/SyncOperation.h
    src/operations/InsertFolderOperation.h
    src/operations/LoadFolderOperation.h
    src/operations/LoadNewsOperation.h
    src/operations/MarkAllReadOrUnreadOperation.h
    src/operations/UpdateFeedURLOperation.h
    src/parser/RawFeed.h
    src/parser/RawNews.h
    src/FangApp.h
    src/operations/OperationManager.h
    src/operations/UpdateFeedOperation.h
    src/utilities/Utilities.h
    src/operations/LoadAllFeedsOperation.h
    src/db/DB.h
    src/operations/DBOperation.h
    src/models/FeedValidator.h
    src/operations/AddFeedOperation.h
    src/operations/RemoveFeedOperation.h
    src/utilities/FaviconGrabber.h
    src/utilities/FangLogging.h
    src/operations/SetBookmarkOperation.h
    src/operations/SetFolderOpenOperation.h
    src/operations/ReloadNewsOperation.h
    src/utilities/WebPageGrabber.h
    src/operations/FaviconUpdateOperation.h
    src/models/AllNewsFeedItem.h
    src/utilities/ImageGrabber.h
    src/operations/UpdateTitleOperation.h
    src/parser/ParserInterface.h
    src/models/FangSettings.h
    src/utilities/RawFeedRewriter.h
    src/utilities/HTMLSanitizer.h
    src/operations/LoadAllNewsOperation.h
    src/utilities/UnreadCountReader.h
    src/operations/UpdateOrdinalsOperation.h
    src/utilities/NetworkUtilities.h
    src/parser/OPMLParser.h
    src/utilities/FeedDiscovery.h
    src/models/OPMLInteractor.h
    src/utilities/OPMLExport.h
    src/utilities/BatchFeedDiscovery.h
    src/FangObject.h
    src/parser/ParserXMLWorker.h
    src/network/FangNetworkAccessManager.h
    src/network/FangQQmlNetworkAccessManagerFactory.h
    src/network/NetworkRetryPolicy.h
    src/network/NetworkDownloadCore.h
    src/network/BatchDownloadCore.h
    src/notifications/Notification.h

    src/operations/SetPinOperation.h
    src/models/PinnedFeedItem.h
    src/models/SearchFeedItem.h
    src/operations/LoadPinnedNewsOperation.h
    src/models/LisvelFeedItem.h
    src/operations/LisvelLoadNewsOperation.h
    src/operations/SearchNewsOperation.h
    src/operations/ExpireNewsOperation.h
    src/operations/SetDBSettingOperation.h
    src/db/DBSettings.h
    src/db/DBSettingsInterface.h
    src/operations/GetAllDBSettingsOperation.h
    src/db/DBSettingsKey.h
    src/parser/BatchNewsParser.h
    src/parser/NewsParser.h
    src/server/WebSocketServer.h
    src/server/WebServer.h

    # Resource files
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

# Enable warnings as errors
set_property(TARGET Fang PROPERTY COMPILE_WARNING_AS_ERROR ON)

# Link libraries
target_link_libraries(Fang PRIVATE
    TidyLib
    QSingleInstanceCheck
    QSimpleStateMachine::QSimpleStateMachine
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
    rearrangeabletreeview
    rearrangeabletreeviewplugin
)

# Optional WebEngineQuick
if(TARGET Qt6::WebEngineQuick)
    target_link_libraries(Fang PRIVATE Qt6::WebEngineQuick)
    target_compile_definitions(Fang PRIVATE QT_WEBVIEW_WEBENGINE_BACKEND)
endif()

# Precompiled headers for faster compilation
# These are the most frequently included Qt headers across the project
target_precompile_headers(Fang PRIVATE
    <QObject>
    <QString>
    <QList>
    <QMap>
    <QUrl>
    <QByteArray>
    <QVariant>
    <QNetworkAccessManager>
    <QNetworkRequest>
    <QNetworkReply>
    <QTimer>
    <QDebug>
    <QQmlApplicationEngine>
    <QQuickItem>
)

# Platform: macOS
if(APPLE)
    target_sources(Fang PRIVATE
        icons/mac.icns
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

# Platform: Windows
if(WIN32)
    target_sources(Fang PRIVATE
        win32.rc
    )
endif()

# Platform: Android
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

# Coverage support
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Code coverage enabled")

        # Add coverage flags to main target
        target_compile_options(Fang PRIVATE --coverage -O0 -g)
        target_link_options(Fang PRIVATE --coverage)

        # Add custom target for coverage report generation
        find_program(LCOV_PATH lcov)
        find_program(GENHTML_PATH genhtml)

        if(LCOV_PATH AND GENHTML_PATH)
            add_custom_target(fang-coverage
                # Reset coverage counters
                COMMAND ${LCOV_PATH} --directory . --zerocounters

                # Run tests
                COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure

                # Capture coverage data
                COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info --ignore-errors inconsistent,format,gcov,unsupported,unused

                # Remove system and test files from coverage
                COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/Qt/*' '*/test/*' '*_autogen/*' '*/tidylib/*' --output-file coverage.info.cleaned --ignore-errors inconsistent,format,gcov,unsupported,unused

                # Generate HTML report
                COMMAND ${GENHTML_PATH} coverage.info.cleaned --output-directory coverage_html --ignore-errors inconsistent,format,unused

                # Print summary
                COMMAND ${LCOV_PATH} --list coverage.info.cleaned --ignore-errors inconsistent,format,gcov,unsupported,unused

                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating coverage report"
            )

            # Add a lightweight target to generate HTML from existing coverage data
            add_custom_target(fang-coverage-html
                # Capture coverage data
                COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
                    --ignore-errors inconsistent,format,gcov,unsupported,unused

                # Remove system and test files
                COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/Qt/*' '*/test/*' '*_autogen/*' '*/tidylib/*'
                    --output-file coverage.info.cleaned
                    --ignore-errors inconsistent,format,gcov,unsupported,unused

                # Generate HTML report
                COMMAND ${GENHTML_PATH} coverage.info.cleaned --output-directory coverage_html
                    --ignore-errors inconsistent,format,unused

                # Print location and try to open in browser
                COMMAND ${CMAKE_COMMAND} -E echo ""
                COMMAND ${CMAKE_COMMAND} -E echo "======================================================================"
                COMMAND ${CMAKE_COMMAND} -E echo "Coverage report: ${CMAKE_BINARY_DIR}/coverage_html/index.html"
                COMMAND ${CMAKE_COMMAND} -E echo "======================================================================"
                COMMAND ${CMAKE_COMMAND} -E echo ""

                # Try to open in default browser (best effort, may not work from all contexts)
                COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Opening in browser..."
                COMMAND open ${CMAKE_BINARY_DIR}/coverage_html/index.html || xdg-open ${CMAKE_BINARY_DIR}/coverage_html/index.html || ${CMAKE_COMMAND} -E echo "Note: Could not open browser automatically. Use the link above."

                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMENT "Generating HTML coverage report and opening in browser"
            )

            message(STATUS "Coverage target 'coverage' available - run: make coverage (runs tests + generates HTML)")
            message(STATUS "Coverage target 'coverage-html' available - run: make coverage-html (generates HTML from existing test data)")
        else()
            message(WARNING "lcov or genhtml not found - coverage target not available")
        endif()
    else()
        message(WARNING "Coverage only supported with GCC or Clang")
    endif()
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
