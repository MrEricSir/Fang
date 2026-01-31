#ifndef SETTINGSINTERFACE_H
#define SETTINGSINTERFACE_H

#include <QString>

/*!
    \brief Interface for settings needed by UpdateChecker.

    This allows UpdateChecker to work with both the real FangSettings
    and a mock for testing.
 */
class SettingsInterface
{
public:
    virtual ~SettingsInterface() = default;
    virtual QString getLastSeenVersion() = 0;
};

#endif // SETTINGSINTERFACE_H
