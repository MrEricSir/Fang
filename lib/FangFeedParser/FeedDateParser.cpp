#include "FeedDateParser.h"
#include <QMap>
#include <QtCore/qtimezone.h>

QDateTime FeedDateParser::dateFromFeedString(const QString& _timestamp)
{
    QDateTime ret; // Defaults to invalid timestamp.

    // Come up with a few versions of the time stamp.
    QString timestamp = _timestamp.trimmed();
    yearFix(timestamp); // IMPORTANT: Must be done *before* weekday name is shaved.
    shaveWeekdayName(timestamp);
    monthMassager(timestamp);
    QString timestamps[] = {
        timestamp,
        timestamp.left(timestamp.lastIndexOf(" ")).trimmed(),
        timestamp.left(timestamp.lastIndexOf(".")).trimmed(),
        timestamp.left(timestamp.lastIndexOf("-")).trimmed(),
        timestamp.left(timestamp.lastIndexOf("+")).trimmed(),

        "" // must be last
    };

    // Date time.  Comes in many (ugh) different formats.
    const QString dateFormats[] = {
        // Most typical RSS format
        // Example: Tue, 02 Jul 2013 01:01:24 +0000 or Sun, 13 Oct 2013 19:15:29  PST
        // But Fang shaves off weekday names (see above), because they're useless and are often screwed up.
        "dd MMM yyyy hh:mm:ss",

        // One-digit minutes (yes, this happens.)
        "dd MMM yyyy hh:m:ss",

        // Same as above, but with full months.
        "dd MMMM yyyy hh:mm:ss",

        // Full month, one digit minutes.
        "dd MMMM yyyy hh:m:ss",

        // Also same as above, but with potentially single-digit days. (Used by "The Hindu".)
        "d MMM yyyy hh:mm:ss",

        // RFC 3339, normally used by Atom.
        // Example: 2013-08-07T16:47:54Z
        "yyyy-MM-ddThh:mm:ssZ",

        // Variant of the above without the trailing Z.
        // Example: 2012-05-30T19:46:42
        "yyyy-MM-ddThh:mm:ss",

        // Variant of the above without seconds OR a trailing Z.
        // Example: 2012-05-30T19:46
        "yyyy-MM-ddThh:mm",

        // Format used by some Chinese site.
        // Example: 2014-02-27 08:26:16.995
        "yyyy-MM-dd hh:mm:ss",

        // "Lokmat" uses this custom format.  I provide a single-spaced version for sanity's sake.
        // Example: 25-02-2014  01:08:10
        "dd-MM-yyyy  hh:mm:ss",
        "dd-MM-yyyy hh:mm:ss",


        "" // must be last!
    };

    // Iterate over date formats.
    int i = 0;
    while (!ret.isValid() && !dateFormats[i].isEmpty()) {
        const QString& format = dateFormats[i];

        // Try each format against each possible manipulated timestamp.
        int j = 0;
        while (!ret.isValid() && !timestamps[j].isEmpty()) {
            QString& ts = timestamps[j];
            ret = QDateTime::fromString(ts, format);

            j++;
        }

        i++;
    }

    // Check if there's a time-based adjustment and/or timezone.
    // First try numeric offsets in the format of -hhmm, +hhmm, -hh:mm, or +hh:mm.
    int lastPlus = timestamp.lastIndexOf("+");
    int lastMinus = timestamp.lastIndexOf("-");
    if (lastPlus > 3 || lastMinus > 3) {
        // We have a plus or a minus.
        int signPos = lastPlus > 3 ? lastPlus : lastMinus;
        QString sAdjustment = timestamp.right(timestamp.length() - signPos);
        sAdjustment = sAdjustment.trimmed();

        // Check for an hour/minute adjustment, in the format of -hhmm or +hhmm
        // OR in the format of -hh:mm or +hh:mm
        if ((sAdjustment.length() == 5 || sAdjustment.length() == 6) &&
                (sAdjustment.startsWith("+") || sAdjustment.startsWith("-"))) {
            int adjustment = 0; // Adjustment in minutes.
            bool containsCol = sAdjustment.contains(':');
            bool isNum = false;
            int hours = 0;
            int minutes = 0;

            QString sNumber = sAdjustment.right(containsCol ? 5 : 4); // Skip + or -
            // YES!  We've got an adjustment!
            hours = sNumber.left(2).toInt(&isNum);
            if (isNum) {
                minutes = sNumber.right(2).toInt(&isNum);
            }

            // Looks like we're good!
            if (isNum) {
                // Condense down to minutes.
                minutes += (hours * 60);
                adjustment = sAdjustment.startsWith("-") ? minutes : -minutes;

                // Add in our adjustment if we need it.
                ret = ret.addSecs(adjustment * 60 /* seconds */);
            }
        }
    }

    // Three-letter timezone abbreviations (UTC offset in minutes).
    static const QMap<QString, int> tzOffsets = {
        {"GMT",    0}, {"UTC",    0},
        {"EST", -300}, {"EDT", -240},
        {"CST", -360}, {"CDT", -300},
        {"MST", -420}, {"MDT", -360},
        {"PST", -480}, {"PDT", -420}
    };

    // Check if the timestamp ends with a known abbreviation.
    QString lastWord = timestamp.section(' ', -1).trimmed().toUpper();
    if (tzOffsets.contains(lastWord)) {
        int offsetMinutes = tzOffsets.value(lastWord);
        ret = ret.addSecs(-offsetMinutes * 60);
    }

    // All times are (supposedly) in UTC.
    ret.setTimeZone(QTimeZone::UTC);

    return ret;
}


void FeedDateParser::yearFix(QString& timestamp)
{
    // If the timestamp is something like this:
    // Tue, 02 Jul 13 [etc]
    // We want to make it something like this:
    // Tue, 02 Jul 2013 [etc]
    if (timestamp.length() == 0 || !timestamp[0].isLetter()) {
        return; // Early exit.
    }

    bool seenWeekday = false;
    bool seenDay = false;
    bool seenMonth = false;
    bool seenYear = false;
    bool hitSpace = true; // This controls whether or not we examine the character.
    int charsInYear = 0;
    for (int i = 0; i < timestamp.length(); i++) {
        if (hitSpace && (timestamp[i].isLetter() || timestamp[i] == ',')) {
            hitSpace = false; // reset

            if (!seenWeekday) {
                seenWeekday = true;
            } else if (!seenMonth) {
                seenMonth = true;
            }
        } else if (hitSpace && (timestamp[i].isDigit())) {
            hitSpace = false; // reset

            if (!seenDay) {
                seenDay = true;
            } else if (!seenYear) {
                seenYear = true;
            }
        } else if (timestamp[i].isSpace()) {
            if (seenYear) {
                // Here's where we find out if we can leave yet.
                if (charsInYear != 2) {
                    break; // Early exit!
                } else {
                    // Sigh... okay, now we have to back up and insert a "20".
                    // Currently we're here: [Tue, 02 Jul 13 ]
                    timestamp = timestamp.insert(i - 2, "20");
                    return; // YAY! WE DID IT!
                }
            } else {
                hitSpace = true;
            }
        }

        if (seenYear) {
            ++charsInYear;
        }
    }
}


void FeedDateParser::shaveWeekdayName(QString& timestamp)
{
    // NOTE:
    // By the time we've reached this method, the timestamp has
    // already been trimmed, and we've made sure the year has four digits.

    int comma = timestamp.indexOf(',');
    if (comma < 0) {
        return; // Early exit.
    }

    // Remove up to and including the comma itself.
    timestamp = timestamp.remove(0, comma + 1).trimmed();
}

void FeedDateParser::monthMassager(QString& timestamp)
{
    // Add new ones as they're encountered.
    timestamp = timestamp.replace("Sept ", "Sep ");
}
