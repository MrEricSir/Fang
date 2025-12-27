#include "FangLogging.h"

// Define logging categories
// In debug builds, these output at QtDebugMsg level
// In release builds, they're disabled (QtInfoMsg level means debug messages won't show)

#ifdef QT_DEBUG
Q_LOGGING_CATEGORY(logFavicon, "fang.favicon", QtDebugMsg)
Q_LOGGING_CATEGORY(logWebPage, "fang.webpage", QtDebugMsg)
Q_LOGGING_CATEGORY(logMock, "fang.mock", QtDebugMsg)
#else
Q_LOGGING_CATEGORY(logFavicon, "fang.favicon", QtInfoMsg)
Q_LOGGING_CATEGORY(logWebPage, "fang.webpage", QtInfoMsg)
Q_LOGGING_CATEGORY(logMock, "fang.mock", QtInfoMsg)
#endif
