#ifndef FANGAPPLICATIONVIEWER_H
#define FANGAPPLICATIONVIEWER_H

#include "../qmlapplicationviewer/qmlapplicationviewer.h"

#include <QString>
#include <QTimer>
#include <QSettings>
#include <QShowEvent>

class FangApplicationViewer : public QmlApplicationViewer
{
    Q_OBJECT
public:
    explicit FangApplicationViewer(QWidget *parent = 0);
    
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
