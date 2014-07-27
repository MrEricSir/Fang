#include "SingleInstanceCheck.h"
#include <QDebug>

#define FANG_SETTINGS_WINDOW_ID "windowID"

SingleInstanceCheck::SingleInstanceCheck(QString uniqueID, QString settingsGroup) :
    uniqueID(uniqueID), settingsGroup(settingsGroup), isFirst(false)
{
}

SingleInstanceCheck::~SingleInstanceCheck()
{
#if defined(Q_OS_WIN)
    if (isFirst) {
        // Delete the setting!
        settings.beginGroup(settingsGroup);
        settings.remove(FANG_SETTINGS_WINDOW_ID);
        settings.endGroup();
    }
#endif
}

bool SingleInstanceCheck::isAlreadyRunning()
{
#if defined(Q_OS_WIN)
    sharedMemory.setKey(uniqueID);
    if (sharedMemory.create(1)) {
        // We're the first ones here!
        isFirst = true;
        return false;
    } else {
        qDebug() << "Fang is already running!";
        isFirst = false;
        
        // Already running.  Try to find the window
        // and focus on it.
        WId id = checkWindow();
        if (id > 0) {
            QWindow::fromWinId(id)->requestActivate();
        }
        
        return true;
    }
#else
    isFirst = false;
    return false;
#endif
}

void SingleInstanceCheck::setWindow(QWindow* window)
{
    Q_UNUSED(window);
#if defined(Q_OS_WIN)
    // Convert the window ID to the most bigass number possible.
    qulonglong windowID = window ? (qulonglong)window->winId() : 0;
            
    settings.beginGroup(settingsGroup);
    settings.setValue(FANG_SETTINGS_WINDOW_ID, windowID);
    settings.endGroup();
#endif
}

WId SingleInstanceCheck::checkWindow()
{
    settings.beginGroup(settingsGroup);
    // Zero is default.
    qulonglong windowID = settings.value(FANG_SETTINGS_WINDOW_ID).toULongLong();
    settings.endGroup();
    
    return (WId) windowID;
}
