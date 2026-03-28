#ifndef FEEDDATEPARSER_H
#define FEEDDATEPARSER_H

#include <QDateTime>
#include <QString>

/*!
   \brief The FeedDateParser static utility class is used to massage
    non-compliant datetime strings in RSS feeds into a QDateTime object.
 */
class FeedDateParser
{
public:
    static QDateTime dateFromFeedString(const QString& timestamp);

private:
    static void yearFix(QString& timestamp);
    static void shaveWeekdayName(QString& timestamp);
    static void monthMassager(QString& timestamp);
};

#endif // FEEDDATEPARSER_H
