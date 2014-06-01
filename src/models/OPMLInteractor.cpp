#include "OPMLInteractor.h"

#include <QDir>
#include <QDebug>

#include "../FangApp.h"
#include "../utilities/OPMLExport.h"

OPMLInteractor::OPMLInteractor(QQuickItem *parent) :
    QQuickItem(parent)
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
}

void OPMLInteractor::importFile()
{
    importDialog.exec();
}

void OPMLInteractor::confirmImport()
{
    qDebug() << "Import confirm: TODO";
}

void OPMLInteractor::exportFile()
{
    exportDialog.exec();
}

void OPMLInteractor::onImportFileSelected(const QString &file)
{
    qDebug() << "Import: " << file;
    parser.parseFile(file);
    emit importStarted();
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
    emit importFinished();
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
