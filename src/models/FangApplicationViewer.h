#ifndef FANGAPPLICATIONVIEWER_H
#define FANGAPPLICATIONVIEWER_H

#include "../qtquick2applicationviewer/qtquick2applicationviewer.h"

#include <QString>
#include <QTimer>
#include <QSettings>
#include <QShowEvent>

class FangApplicationViewer : public QtQuick2ApplicationViewer
{
    Q_OBJECT
public:
    explicit FangApplicationViewer(QWindow *parent = 0);
    
public slots:
    
    /**
     * @brief Launches the window.
     */
    void displayWindow();
    
signals:
    /**
     * @brief Fired when the main window is resized.
     */
    void windowResized();
    
protected:
    // Listen to window events from subclass.
    virtual void moveEvent(QMoveEvent * event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    
private slots:
    /**
     * @brief This is what performs the save.
     */
    void onSaveTimeout();
    
    /**
     * @brief Quick way to find out of the window is maximized.
     * @return 
     */
    bool isMaximized();
    
private:
    /**
     * @brief Starts the window update timer.
     */
    void updateWindowSettings();
    
    /**
     * @brief Loads the window settings.  Called by displayWindow()
     */
    void restoreWindowSettings();
    
    QTimer saveTimer;
    QSettings settings;
    bool maximizeOnStart;
};

#endif // FANGAPPLICATIONVIEWER_H
