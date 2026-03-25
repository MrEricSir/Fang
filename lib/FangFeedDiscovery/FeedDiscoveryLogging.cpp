#include "FeedDiscoveryLogging.h"

#ifdef QT_DEBUG
Q_LOGGING_CATEGORY(logFeedDiscovery, "fang.feeddiscovery", QtDebugMsg)
#else
Q_LOGGING_CATEGORY(logFeedDiscovery, "fang.feeddiscovery", QtWarningMsg)
#endif
