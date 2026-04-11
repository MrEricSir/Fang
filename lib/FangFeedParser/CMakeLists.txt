add_library(FangFeedParser STATIC
    FeedParserLogging.cpp
    FeedParserLogging.h
    FeedFetchResult.h
    FeedParseError.h
    FeedParseResult.cpp
    FeedParseResult.h
    RawFeed.h
    RawNews.cpp
    RawNews.h
    RSSAtomParser.cpp
    RSSAtomParser.h
    FeedDateParser.cpp
    FeedDateParser.h
    JSONFeedParser.cpp
    JSONFeedParser.h
    FeedParser.cpp
    FeedParser.h
    OPMLParser.cpp
    OPMLParser.h
    OPMLExport.cpp
    OPMLExport.h
)

target_include_directories(FangFeedParser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FangFeedParser PUBLIC
    Qt6::Core
)
