#ifndef FANGLOGGING_H
#define FANGLOGGING_H

#include <QLoggingCategory>

// Logging categories for different subsystems
// Usage: qCDebug(logFavicon) << "message";

Q_DECLARE_LOGGING_CATEGORY(logFavicon)
Q_DECLARE_LOGGING_CATEGORY(logWebPage)
Q_DECLARE_LOGGING_CATEGORY(logMock)

#endif // FANGLOGGING_H
