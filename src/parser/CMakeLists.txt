add_library(FangFeedParser STATIC
    FeedParserLogging.cpp
    FeedParserLogging.h
    RawFeed.cpp
    RawFeed.h
    RawNews.cpp
    RawNews.h
    RSSAtomParser.cpp
    RSSAtomParser.h
    JSONFeedParser.cpp
    JSONFeedParser.h
    FeedParser.cpp
    FeedParser.h
    SitemapParser.cpp
    SitemapParser.h
)

target_include_directories(FangFeedParser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FangFeedParser PUBLIC
    Qt6::Core
)
