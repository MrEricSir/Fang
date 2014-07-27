#ifndef SINGLEINSTANCECHECK_H
#define SINGLEINSTANCECHECK_H

#include <QSharedMemory>
#include <QString>
#include <QWindow>
#include <QSettings>

class SingleInstanceCheck
{
public:
    SingleInstanceCheck(QString uniqueID, QString settingsGroup);
    
    virtual ~SingleInstanceCheck();
    
    /**
     * @brief isAlreadyRunning
     * @return 
     */
    bool isAlreadyRunning();
    
    /**
     * @brief Sets or clears the saved window ID.
     * @param Either the program's main window, or null.
     */
    void setWindow(QWindow* window = NULL);
    
private:
    WId checkWindow();
    
    QSharedMemory sharedMemory;
    QSettings settings;
    QString uniqueID;
    QString settingsGroup;
    bool isFirst;
};

#endif // SINGLEINSTANCECHECK_H
