#include "DB.h"

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QStandardPaths>
#include <QSqlError>

DB* DB::_instance = NULL;

DB::DB(QObject *parent) :
    QObject(parent)
{
    init();
}

DB *DB::instance()
{
    if (_instance == NULL)
        _instance = new DB();
    
    return _instance;
}

void DB::init()
{
    // Find out where our data storage should go.
    QStringList list = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation);
    if (list.size() == 0) {
        qDebug() << "Qt couldn't find a data folder!";
        return;
    }
    
    // Create data dir if it doesn't exist.
    QString sDir = list.at(0);
    QDir dataDirectory(sDir);
    if (!dataDirectory.exists()) {
        qDebug() << "Need to create config path: " << sDir;
        dataDirectory.mkpath(sDir);
    }
    
    // Open (or create) our SQLite database.
    QFile dbFile(sDir + "/fang.sqlite");
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(dbFile.fileName());
    if (!_db.open()) {
        qDebug() << "Could not create database.";
        return;
    }
    
    
    QSqlQuery q(db());
    
    // Set database mode.
    executeSimpleQuery("PRAGMA journal_mode = WAL");
    executeSimpleQuery("PRAGMA synchronous = 1");
    
    // Enable foreign keys.
    executeSimpleQuery("PRAGMA foreign_keys = ON");
    
    // Create/upgrade schema.
    upgrade();
}

bool DB::executeSimpleQuery(QString query)
{
    QSqlQuery q(db());
    
    // Set database mode.
    if (!q.exec(query)) {
        qDebug() << q.lastError().text();
        
        return false;
    }
    
    return true;
}

int DB::getSchemaVersion()
{
    QSqlQuery q(db());
    q.exec("PRAGMA user_version");
    
    // SQLite should auto-init value to zero, but just in case...
    if (!q.next())
        return 0;
    
    return q.value(0).toInt();
}

void DB::setSchemaVersion(int version)
{
    // QSql can't handle PRAGMAs in prepared statements,
    // so this may look a little whack.
    QString statement;
    QTextStream output(&statement);
    output << "PRAGMA user_version = " << version;
    
    QSqlQuery q(db());
    if (!q.exec(statement)) {
        qDebug() << "Couldn't set DB version to " << version;
        qDebug() << "Error: " << q.lastError().text();
    }
}

void DB::upgrade()
{
    int initialVersion = getSchemaVersion();
    int nextVersion = initialVersion + 1;
    while(true) {
        QString filename;
        QTextStream output(&filename);
        output << ":/sql/" << nextVersion << ".sql";
        QFile schemaFile(filename);
        if (!schemaFile.exists())
            break; // We're up to date!
        
        // Do the upgrade.
        if (!executeSqlFile(schemaFile))
            return; // BAIL!
        
        setSchemaVersion(nextVersion);
        nextVersion++;
    }
}

bool DB::executeSqlFile(QFile& sqlFile)
{
    if (!sqlFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file: " << sqlFile.fileName();
        return false;
    }
    
    // Read file.
    QTextStream input(&sqlFile);
    QString entireFile = "";
    QString line;
    while(!input.atEnd()) {
        line = input.readLine().trimmed();
        
        // Ignore comments and whitespace.
        if (line.startsWith("--") || line.isEmpty()) 
            continue;
        
        entireFile += line;
    }
    
    sqlFile.close();
    
    // Split the file by semi-colons.  (SQLite cannot execute multiple
    // statements in one exec.)
    QStringList statements = entireFile.split(";");
    
    // Execute each statement.
    QString s;
    foreach(s, statements) {
        s = s.trimmed();
        if (s.isEmpty())
            continue; // Ignore empty lines.
        
        QSqlQuery q(db());
        if (!q.exec(s)) {
            qDebug() << "Could not execute sql statement: " << q.lastError().text();
            qDebug() << s;
            return false;
        }
    }
    
    // Great success!
    return true;
}
