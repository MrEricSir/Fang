#include "FangApplicationViewer.h"

#include <QDebug>

FangApplicationViewer::FangApplicationViewer(QWindow *parent) :
    QtQuick2ApplicationViewer(parent),
    saveTimer(),
    settings(),
    maximizeOnStart(false)
{
    saveTimer.setSingleShot(true);
    connect(&saveTimer, SIGNAL(timeout()), this, SLOT(onSaveTimeout()));
}

void FangApplicationViewer::displayWindow()
{
    // Set the icon!
    setIcon(QIcon(":/icons/icon_circle.svg"));
    
    restoreWindowSettings();
    
    if (maximizeOnStart)
        showMaximized();
    else
        showExpanded();
}

void FangApplicationViewer::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
    updateWindowSettings();
    QtQuick2ApplicationViewer::moveEvent(event);
}

void FangApplicationViewer::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updateWindowSettings();
    emit windowResized();
    QtQuick2ApplicationViewer::resizeEvent(event);
}

void FangApplicationViewer::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event);
    updateWindowSettings();
   // QtQuick2ApplicationViewer::closeEvent(event);
}

void FangApplicationViewer::onSaveTimeout()
{
    // Perform the save.
    settings.beginGroup("FangWindow");
    
    settings.setValue("maximized", isMaximized());
    if (!isMaximized()) {
        settings.setValue("pos", position());
        settings.setValue("size", size());
    }
    
    settings.endGroup();
}

bool FangApplicationViewer::isMaximized()
{
    return (windowState() & Qt::WindowMaximized) > 0;
}

void FangApplicationViewer::updateWindowSettings()
{
    saveTimer.start(200); // Wait 200 ms after last event.
}

void FangApplicationViewer::restoreWindowSettings()
{
    settings.beginGroup("FangWindow");
    
    if (!settings.contains("maximized")) {
        resize(QSize(800, 600)); // default size
        
        settings.endGroup();
        return; // No settings yet.
    }
    
    setPosition(settings.value("pos", position()).toPoint());
    resize(settings.value("size", size()).toSize());
    if (settings.value("maximized", QVariant(false)).toBool())
        maximizeOnStart = true;
    
    settings.endGroup();
}
