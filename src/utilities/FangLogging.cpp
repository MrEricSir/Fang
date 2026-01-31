#include "FangLogging.h"

// Define logging categories
// In debug builds, these output at QtDebugMsg level
// In release builds, they're disabled except for warnings/critical

#ifdef QT_DEBUG
Q_LOGGING_CATEGORY(logApp, "fang.app", QtDebugMsg)
Q_LOGGING_CATEGORY(logDb, "fang.db", QtDebugMsg)
Q_LOGGING_CATEGORY(logModel, "fang.model", QtDebugMsg)
Q_LOGGING_CATEGORY(logOperation, "fang.operation", QtDebugMsg)
Q_LOGGING_CATEGORY(logParser, "fang.parser", QtDebugMsg)
Q_LOGGING_CATEGORY(logNetwork, "fang.network", QtDebugMsg)
Q_LOGGING_CATEGORY(logRewriter, "fang.rewriter", QtDebugMsg)
Q_LOGGING_CATEGORY(logServer, "fang.server", QtDebugMsg)
Q_LOGGING_CATEGORY(logUtility, "fang.utility", QtDebugMsg)
Q_LOGGING_CATEGORY(logFavicon, "fang.favicon", QtDebugMsg)
Q_LOGGING_CATEGORY(logWebPage, "fang.webpage", QtDebugMsg)
Q_LOGGING_CATEGORY(logMock, "fang.mock", QtDebugMsg)
#else
Q_LOGGING_CATEGORY(logApp, "fang.app", QtWarningMsg)
Q_LOGGING_CATEGORY(logDb, "fang.db", QtWarningMsg)
Q_LOGGING_CATEGORY(logModel, "fang.model", QtWarningMsg)
Q_LOGGING_CATEGORY(logOperation, "fang.operation", QtWarningMsg)
Q_LOGGING_CATEGORY(logParser, "fang.parser", QtWarningMsg)
Q_LOGGING_CATEGORY(logNetwork, "fang.network", QtWarningMsg)
Q_LOGGING_CATEGORY(logRewriter, "fang.rewriter", QtWarningMsg)
Q_LOGGING_CATEGORY(logServer, "fang.server", QtWarningMsg)
Q_LOGGING_CATEGORY(logUtility, "fang.utility", QtWarningMsg)
Q_LOGGING_CATEGORY(logFavicon, "fang.favicon", QtWarningMsg)
Q_LOGGING_CATEGORY(logWebPage, "fang.webpage", QtWarningMsg)
Q_LOGGING_CATEGORY(logMock, "fang.mock", QtWarningMsg)
#endif
