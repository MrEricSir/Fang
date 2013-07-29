#ifndef DB_H
#define DB_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>

/**
 * @brief Singleton database for DB.
 */
class DB : public QObject
{
    Q_OBJECT
public:
    explicit DB(QObject *parent = 0);
    
signals:
    
public slots:
    
    // Creates/returns singleton instance.
    static DB* instance();
    
    inline QSqlDatabase db() { return _db; }
    
private:
    /**
     * @brief Performs DB init. Called by c'tor.
     */
    void init();
    
    /**
     * @brief Returns the version of our schema.
     * Called by upgrade()
     * @return 0 for no schema, 1 or greater for schema version.
     */
    int getSchemaVersion();
    
    /**
     * @brief Updates the version of the database. 
     * Called by upgrade()
     * @param version 1..n
     */
    void setSchemaVersion(int version);
    
    /** 
     *Creates and/or upgrades database, if necessary.
     * Assumes "sql/[1..n].sql" files exist, where 1.sql creates the
     * initial schema, and each version through n is run sequentially to
     * update to version n.
     */
    void upgrade();
    
    /**
     * @brief Runs a SQL file on our database.
     * @param sqlFile Text file containing SQL code.
     */
    bool executeSqlFile(QFile& sqlFile);
    
    // Static instance.
    static DB* _instance;
    
    // Database object.
    QSqlDatabase _db;
};


#endif // DB_H
