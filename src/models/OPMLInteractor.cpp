#include "OPMLInteractor.h"

#include <QDir>

#include "../FangApp.h"
#include "../utilities/FangLogging.h"
#include "../utilities/Utilities.h"
#include "../utilities/OPMLExport.h"
#include "../utilities/ErrorHandling.h"

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
    connect(&importDialog, &QFileDialog::finished, this, &OPMLInteractor::onDialogClosed);
    connect(&importDialog, &QFileDialog::fileSelected, this, &OPMLInteractor::onImportFileSelected);
    
    // Setup export dialog.
    exportDialog.setAcceptMode(QFileDialog::AcceptSave);
    exportDialog.setFileMode(QFileDialog::AnyFile);
    exportDialog.setNameFilter(OPML_FILENAME_FILTER);
    exportDialog.setDirectory(QDir::home());
    connect(&exportDialog, &QFileDialog::finished, this, &OPMLInteractor::onDialogClosed);
    connect(&exportDialog, &QFileDialog::fileSelected, this, &OPMLInteractor::onExportFileSelected);
    
    // Setup parser.
    connect(&parser, &OPMLParser::done, this, &OPMLInteractor::onParserDone);
    
    // Setup batch feed discovery.
    connect(&batchFeedDiscovery, &BatchFeedDiscovery::done, this, &OPMLInteractor::onBatchFeedDiscoveryDone);
    
    // Setup feed list.
    // dataChanged
    connect(FangApp::instance()->getImportList(), &ListModel::dataChanged,
            this, &OPMLInteractor::onImportListDataChanged);
}

OPMLInteractor::~OPMLInteractor()
{
    clear();
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
    
    // Nuke the existing global batch import list.
    ListModel* importList = FangApp::instance()->getImportList();
    while (importList->count() > 0) {
        FeedItem* item = qobject_cast<FeedItem*>(importList->takeRow(0));
        delete item; // Need to delete the items themselves.
    }
    
    // Clear internal map.
    clear();
    
    qCDebug(logModel) << "Import: " << filename;
    parser.parseFile(filename);
}

void OPMLInteractor::confirmImport()
{
    qCDebug(logModel) << "Import confirm: TODO";
}

void OPMLInteractor::exportFile()
{
    exportDialog.exec();
}

void OPMLInteractor::addSelected()
{
    bool first = true;
    ListModel* importList = FangApp::instance()->getImportList();
    for (int i = 0; i < importList->count(); i++) {
        FeedItem* item = qobject_cast<FeedItem*>(importList->row(i));
        if (!item->getIsSelected()) {
            continue;
        }
        
        qCDebug(logModel) << "Add feed " << item->getTitle() << " " << item->getURL();
        
        // Add it!
        FangApp::instance()->addFeed(item->getURL().toString(), feedToRaw[item], first);
        first = false;
    }
}

void OPMLInteractor::onImportFileSelected(const QString &file)
{
    filename = file;
    importReady();
}

void OPMLInteractor::onExportFileSelected(const QString &file)
{
    qCDebug(logModel) << "Export: " << file;
    bool res = OPMLExport::save(file, FangApp::instance()->getFeedList());
    if (!res) {
        qCWarning(logModel) << "Error: unable to write file.";
    }
}

void OPMLInteractor::onDialogClosed()
{
    FangApp::instance()->focusApp();
}

void OPMLInteractor::onParserDone()
{
    qCDebug(logModel) << "Parser done! Result: " << importErrorString();
    
    // Convert parser's feed list to "actual" feed items
    // (for data representation purposes)
    QList<RawFeed*> list = parser.getFeedList();
    
    // Grab the global batch import list.
    ListModel* importList = FangApp::instance()->getImportList();
    
    // Convert and append our news items.
    for (RawFeed* rawFeed : list) {
        FeedItem* feedItem = Utilities::feedItemFromRaw(rawFeed, 0, rawFeed->url.toString(), nullptr);
        feedToRaw.insert(feedItem, rawFeed);
        importList->appendRow(feedItem);
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
        FANG_UNREACHABLE("Unknown OPML parser error code");
        return "Unknown error";
    }
    
    return "Unknown error";
}

void OPMLInteractor::startValidation(ListModel* importList)
{
    _validationInProgress = true;
    emit validationInProgressChanged();
    
    batchFeedDiscovery.checkFeedList(importList);
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

void OPMLInteractor::clear()
{
    for (RawFeed* raw : feedToRaw) {
        raw->deleteLater();
    }
    
    feedToRaw.clear();
}
