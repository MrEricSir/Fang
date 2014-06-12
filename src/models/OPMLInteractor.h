#ifndef OPMLINTERACTOR_H
#define OPMLINTERACTOR_H

#define OPML_FILENAME_FILTER "OPML files (*.opml)"

#include <QQuickItem>
#include <QFileDialog>
#include <QString>

#include "../parser/OPMLParser.h"
#include "../parser/RawFeed.h"
#include "ListModel.h"
#include "FeedItem.h"
#include "../utilities/BatchFeedDiscovery.h"

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
    
    // Import error string (only after importInProgress becomes false!)
    Q_PROPERTY(QString importError READ importErrorString NOTIFY importFinished)
    
    // OPML import is in progress.
    Q_PROPERTY(bool importInProgress READ importInProgress NOTIFY importInProgressChanged)
    
    // Feed validation in progress.
    Q_PROPERTY(bool validationInProgress READ validationInProgress NOTIFY validationInProgressChanged)
    
    // True if at least one feed is selected.
    Q_PROPERTY(bool isAnyFeedSelected READ isAnyFeedSelected NOTIFY isAnyFeedSelectedChanged)
    
public:
    explicit OPMLInteractor(QQuickItem *parent = 0);
    
signals:
    
    // Ready to start!  Just call importStart();
    void importReady();
    
    // File import has started.
    void importStarted();
    
    // File import has completed.
    void importFinished();
    
    void importInProgressChanged();
    
    // File export has completed.
    void exportFinished();
    
    // Validation of feeds has begun or ended.
    void validationInProgressChanged();
    
    // At least one feed selected/unselected.
    void isAnyFeedSelectedChanged();
    
public:
    
    // Opens file import dialog.
    Q_INVOKABLE void importFile();
    
    // Begin the import.
    Q_INVOKABLE void importStart();
    
    // Confirms the import options.
    Q_INVOKABLE void confirmImport();
    
    // Opens file export dialog.
    Q_INVOKABLE void exportFile();
    
    // Add the selected feeds.
    Q_INVOKABLE void addSelected();
    
    // Whether or not import is in progress.
    bool importInProgress() { return _importInProgress; }
    
    // Whether or not we're validating all of your feeds.
    bool validationInProgress() { return _validationInProgress; }
    
    // Whether or not at least one feed is currently selected.
    bool isAnyFeedSelected() { return _isAnyFeedSelected; }
    
private slots:
    
    // User selected an OPML file to import.
    void onImportFileSelected(const QString& file);
    
    // User selected where to write our OPML file.
    void onExportFileSelected(const QString& file);
    
    // When any dialog is closed.
    void onDialogClosed();
    
    // The OPMLParser is done, my good sir.
    void onParserDone();
    
    // Batch feed discovery is complete.
    void onBatchFeedDiscoveryDone();
    
    // Returns the error string, if there is one.
    QString importErrorString();
    
    // Starts validation of the feed list.
    void startValidation(ListModel* importList);
    
    // The import list had a data change.
    void onImportListDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    
private:
    
    QFileDialog importDialog;
    QFileDialog exportDialog;
    OPMLParser parser;
    bool _importInProgress;
    bool _validationInProgress;
    BatchFeedDiscovery batchFeedDiscovery;
    QString filename;
    bool _isAnyFeedSelected;
};

#endif // OPMLINTERACTOR_H
