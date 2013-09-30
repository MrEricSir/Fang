#include "FangApplicationViewer.h"

#include <QDebug>

FangApplicationViewer::FangApplicationViewer(QWidget *parent) :
    QmlApplicationViewer(parent),
    saveTimer(),
    settings(),
    maximizeOnStart(false)
{
    saveTimer.setSingleShot(true);
    connect(&saveTimer, SIGNAL(timeout()), this, SLOT(onSaveTimeout()));
}

void FangApplicationViewer::displayWindow()
{
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
    QmlApplicationViewer::moveEvent(event);
}

void FangApplicationViewer::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    updateWindowSettings();
    emit windowResized();
    QmlApplicationViewer::resizeEvent(event);
}

void FangApplicationViewer::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event);
    updateWindowSettings();
    QmlApplicationViewer::closeEvent(event);
}

void FangApplicationViewer::onSaveTimeout()
{
    // Perform the save.
    settings.beginGroup("FangWindow");
    
    settings.setValue("maximized", isMaximized());
    if (!isMaximized()) {
        settings.setValue("pos", pos());
        settings.setValue("size", size());
    }
    
    settings.endGroup();
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
    
    move(settings.value("pos", pos()).toPoint());
    resize(settings.value("size", size()).toSize());
    if (settings.value("maximized", isMaximized()).toBool())
        maximizeOnStart = true;
    
    settings.endGroup();
}
