#ifndef FANGLOGGING_H
#define FANGLOGGING_H

#include <QLoggingCategory>

/*!
    \brief Logging categories for different subsystems.

    Usage: qCDebug(logNetwork) << "message";

    Categories can be enabled/disabled at runtime via QT_LOGGING_RULES.
    See README.md for details.
 */

Q_DECLARE_LOGGING_CATEGORY(logApp)
Q_DECLARE_LOGGING_CATEGORY(logDb)
Q_DECLARE_LOGGING_CATEGORY(logModel)
Q_DECLARE_LOGGING_CATEGORY(logOperation)
Q_DECLARE_LOGGING_CATEGORY(logParser)
Q_DECLARE_LOGGING_CATEGORY(logNetwork)
Q_DECLARE_LOGGING_CATEGORY(logRewriter)
Q_DECLARE_LOGGING_CATEGORY(logServer)
Q_DECLARE_LOGGING_CATEGORY(logUtility)
Q_DECLARE_LOGGING_CATEGORY(logFavicon)
Q_DECLARE_LOGGING_CATEGORY(logWebPage)
Q_DECLARE_LOGGING_CATEGORY(logMock)

#endif // FANGLOGGING_H
