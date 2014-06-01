#ifndef OPMLINTERACTOR_H
#define OPMLINTERACTOR_H

#define OPML_FILENAME_FILTER "OPML files (*.opml)"

#include <QQuickItem>
#include <QFileDialog>
#include <QString>

#include "../parser/OPMLParser.h"

/**
 * @brief Handles interaction with the QML dialogs for OPML import/export.
 * 
 * Elaine: Art Vandelay? This is my boyfriend?
 *  Jerry: That's your boyfriend.
 * Elaine: What does he do?
 *  Jerry: He's an importer.
 * Elaine: Just imports? No exports?
 *  Jerry: He's an importer-exporter. Okay?
 */
class OPMLInteractor : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(OPMLInteractor)
    
    Q_PROPERTY(QString importError READ importErrorString) // For notify, use importFinished()
public:
    explicit OPMLInteractor(QQuickItem *parent = 0);
    
signals:
    
    // File import has started.
    void importStarted();
    
    // File import has completed.
    void importFinished();
    
    // File export has completed.
    void exportFinished();
    
public:
    
    // Opens file import dialog.
    Q_INVOKABLE void importFile();
    
    // Confirms the import options.
    Q_INVOKABLE void confirmImport();
    
    // Opens file export dialog.
    Q_INVOKABLE void exportFile();
    
    // Returns the feed list from an import operation.
    Q_INVOKABLE QList<RawFeed*> getFeedList() { return parser.getFeedList(); }
    
private slots:
    // User selected an OPML file to import.
    void onImportFileSelected(const QString& file);
    
    // User selected where to write our OPML file.
    void onExportFileSelected(const QString& file);
    
    // When any dialog is closed.
    void onDialogClosed();
    
    // The OPMLParser is done, my good sir.
    void onParserDone();
    
    // Returns the error string, if there is one.
    QString importErrorString();
    
private:
    
    QFileDialog importDialog;
    QFileDialog exportDialog;
    OPMLParser parser;
};

#endif // OPMLINTERACTOR_H
