#include "FeedParserLogging.h"

#ifdef QT_DEBUG
Q_LOGGING_CATEGORY(logFeedParser, "fang.feedparser", QtDebugMsg)
#else
Q_LOGGING_CATEGORY(logFeedParser, "fang.feedparser", QtWarningMsg)
#endif
