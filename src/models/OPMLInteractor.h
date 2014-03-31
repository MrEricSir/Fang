#ifndef OPMLINTERACTOR_H
#define OPMLINTERACTOR_H

#define OPML_FILENAME_FILTER "OPML files (*.opml)"

#include <QQuickItem>
#include <QFileDialog>
#include <QString>

class OPMLInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(OPMLInteractor)
public:
    explicit OPMLInteractor(QQuickItem *parent = 0);
    
signals:
    
    void importStarted();
    void exportFinished();
    
public:
    
    Q_INVOKABLE void importFile();
    
    Q_INVOKABLE void exportFile();
    
private slots:
    // User selected an OPML file to import.
    void onImportFileSelected(const QString& file);
    
    // User selected where to write our OPML file.
    void onExportFileSelected(const QString& file);
    
    // When any dialog is closed.
    void onDialogClosed();
    
private:
    
    QFileDialog importDialog;
    QFileDialog exportDialog;
};

#endif // OPMLINTERACTOR_H
