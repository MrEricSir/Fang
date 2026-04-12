add_library(QWebDownload STATIC
    WebDownloadLogging.cpp
    WebDownloadLogging.h
    QWebDownload.cpp
    QWebDownload.h
    WebRetryPolicy.cpp
    WebRetryPolicy.h
    QBatchWebDownload.cpp
    QBatchWebDownload.h
    WebUtilities.cpp
    WebUtilities.h
)

target_include_directories(QWebDownload PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(QWebDownload PUBLIC
    Qt6::Core
    Qt6::Network
)
