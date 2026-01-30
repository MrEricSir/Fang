#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <QDebug>

//
// Error handling.
//

/*!
    \brief Validate condition and return a value if it fails.

    Examples:
      FANG_REQUIRE(feed != nullptr, false);
      FANG_REQUIRE(index >= 0, -1);
 */
#define FANG_REQUIRE(condition, returnValue) \
    do { \
        if (!(condition)) { \
            qCritical() << "Ccondition failed:" << #condition \
                       << "at" << __FILE__ << ":" << __LINE__; \
            return returnValue; \
        } \
    } while (0)

/*!
    \brief Validate condition and return early if it fails (for void functions.)

    Example:
      FANG_REQUIRE_VOID(operation != nullptr);
 */
#define FANG_REQUIRE_VOID(condition) \
    do { \
        if (!(condition)) { \
            qCritical() << "Condition failed:" << #condition \
                       << "at" << __FILE__ << ":" << __LINE__; \
            return; \
        } \
    } while (0)

/*!
    \brief Validate condition and log error if it fails, then continue.

    Example:
      FANG_CHECK(isValid, "Data validation failed");
 */
#define FANG_CHECK(condition, message) \
    do { \
        if (!(condition)) { \
            qCritical() << message << "at" << __FILE__ << ":" << __LINE__; \
        } \
    } while (0)

/*!
    \brief Mark code as intentionally unreachable. Useful for default in switches, etc.
    Example:
      default:
          FANG_UNREACHABLE("Unhandled enum value");
          return fallbackValue;
 */
#define FANG_UNREACHABLE(message) \
    do { \
        qCritical() << "Unreachable code:" << message \
                   << "at" << __FILE__ << ":" << __LINE__; \
        Q_UNREACHABLE(); \
    } while (0)

#endif // ERRORHANDLING_H
