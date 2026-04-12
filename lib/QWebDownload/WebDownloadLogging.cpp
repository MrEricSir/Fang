#include "WebDownloadLogging.h"

#ifdef QT_DEBUG
Q_LOGGING_CATEGORY(logWebDownload, "fang.webdownload", QtDebugMsg)
#else
Q_LOGGING_CATEGORY(logWebDownload, "fang.webdownload", QtWarningMsg)
#endif
