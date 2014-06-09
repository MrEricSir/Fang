#include "OPMLInteractor.h"

#include <QDir>
#include <QDebug>

#include "../FangApp.h"
#include "../utilities/Utilities.h"
#include "../utilities/OPMLExport.h"

OPMLInteractor::OPMLInteractor(QQuickItem *parent) :
    QQuickItem(parent),
    _importInProgress(false),
    _validationInProgress(false),
    _isAnyFeedSelected(false)
{
    // Setup import dialog.
    importDialog.setAcceptMode(QFileDialog::AcceptOpen);
    importDialog.setFileMode(QFileDialog::ExistingFile);
    importDialog.setNameFilter(OPML_FILENAME_FILTER);
    importDialog.setDirectory(QDir::home());
    connect(&importDialog, SIGNAL(finished(int)), this, SLOT(onDialogClosed()));
    connect(&importDialog, SIGNAL(fileSelected(const QString&)),
            this, SLOT(onImportFileSelected(const QString&)));
    
    // Setup export dialog.
    exportDialog.setAcceptMode(QFileDialog::AcceptSave);
    exportDialog.setFileMode(QFileDialog::AnyFile);
    exportDialog.setNameFilter(OPML_FILENAME_FILTER);
    exportDialog.setDirectory(QDir::home());
    connect(&exportDialog, SIGNAL(finished(int)), this, SLOT(onDialogClosed()));
    connect(&exportDialog, SIGNAL(fileSelected(const QString&)),
            this, SLOT(onExportFileSelected(const QString&)));
    
    // Setup parser.
    connect(&parser, SIGNAL(done()), this, SLOT(onParserDone()));
    
    // Setup batch feed discovery.
    connect(&batchFeedDiscovery, SIGNAL(done()), this, SLOT(onBatchFeedDiscoveryDone()));
    
    // Setup feed list.
    // dataChanged
    connect(FangApp::instance()->getImportList(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(onImportListDataChanged(QModelIndex,QModelIndex)));
}

void OPMLInteractor::importFile()
{
    importDialog.exec();
}

void OPMLInteractor::importStart()
{
    _importInProgress = true;
    emit importStarted();
    emit importInProgressChanged();
    
    // Nuke the global batch import list.
    ListModel* importList = FangApp::instance()->getImportList();
    while (importList->count() > 0) {
        FeedItem* item = qobject_cast<FeedItem*>(importList->takeRow(0));
        delete item; // Need to delete the items themselves.
    }
    
    qDebug() << "Import: " << filename;
    parser.parseFile(filename);
}

void OPMLInteractor::confirmImport()
{
    qDebug() << "Import confirm: TODO";
}

void OPMLInteractor::exportFile()
{
    exportDialog.exec();
}

void OPMLInteractor::addSelected()
{
    ListModel* importList = FangApp::instance()->getImportList();
    for (int i = 0; i < importList->count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(importList->row(i));
        if (!item->getIsSelected())
            continue;
        
        //qDebug() << "Add feed " << item->getTitle() << " " << item->getURL();
        
        // Add it!
        FangApp::instance()->addFeed(item->getURL(), item->getTitle());
    }
}

void OPMLInteractor::onImportFileSelected(const QString &file)
{
    filename = file;
    importReady();
}

void OPMLInteractor::onExportFileSelected(const QString &file)
{
    qDebug() << "Export: " << file;
    OPMLExport::save(file, FangApp::instance()->getFeedList());
}

void OPMLInteractor::onDialogClosed()
{
    FangApp::instance()->focusApp();
}

void OPMLInteractor::onParserDone()
{
    qDebug() << "Parser done! Result: " << importErrorString();
    
    // Convert parser's feed list to "actual" feed items
    // (for data representation purposes)
    QList<RawFeed*> list = parser.getFeedList();
    
    // Grab the global batch import list.
    ListModel* importList = FangApp::instance()->getImportList();
    
    // Convert and append our news items.
    foreach (RawFeed* rawFeed, list) {
        importList->appendRow(Utilities::feedItemFromRaw(rawFeed, 0, this));
    }
    
    _importInProgress = false;
    emit importFinished();
    emit importInProgressChanged();
    
    // Validate!
    startValidation(importList);
}

void OPMLInteractor::onBatchFeedDiscoveryDone()
{
    _validationInProgress = false;
    emit validationInProgressChanged();
}

QString OPMLInteractor::importErrorString()
{
    ParserInterface::ParseResult result = parser.getResult();
    switch (result) {
    case ParserInterface::OK:
        return "";
    case ParserInterface::FILE_ERROR:
        return "Could not access or read file";
    case ParserInterface::PARSE_ERROR:
        return "File is not an OPML feed list";
    case ParserInterface::EMPTY_DOCUMENT:
        return "OPML file did not contain any feeds";
    default:
        Q_ASSERT(false); // Forgot to handle this error. Jerk.
    }
    
    return "Unknown error";
}

void OPMLInteractor::startValidation(ListModel* importList)
{
    _validationInProgress = true;
    emit validationInProgressChanged();
    
    batchFeedDiscovery.checkFeedList(importList, 2);
}

void OPMLInteractor::onImportListDataChanged(const QModelIndex& topLeft,
                                             const QModelIndex& bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
    
    bool anySelected = false;
    ListModel* importList = FangApp::instance()->getImportList();
    
    // Iterate over this section of the list.
    for (int i = 0; i < importList->count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(importList->row(i));
         if (item->getIsSelected()) {
             // We got one!  Might as well stop here.
             anySelected = true;
             break;
         }
    }
    
    // It CHANGED.
    if (_isAnyFeedSelected != anySelected) {
        _isAnyFeedSelected = anySelected;
        emit isAnyFeedSelectedChanged();
    }
}
