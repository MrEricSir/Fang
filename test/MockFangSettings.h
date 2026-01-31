#ifndef MOCKFANGSETTINGS_H
#define MOCKFANGSETTINGS_H

#include <QString>
#include "../src/utilities/SettingsInterface.h"

/*!
    \brief Mock version of FangSettings for testing UpdateChecker.

    Implements SettingsInterface to provide the getLastSeenVersion() method
    that UpdateChecker needs.
 */
class MockFangSettings : public SettingsInterface
{
public:
    MockFangSettings() : _lastSeenVersion() {}
    virtual ~MockFangSettings() = default;

    QString getLastSeenVersion() override { return _lastSeenVersion; }
    void setLastSeenVersion(const QString& s) { _lastSeenVersion = s; }

private:
    QString _lastSeenVersion;
};

#endif // MOCKFANGSETTINGS_H
