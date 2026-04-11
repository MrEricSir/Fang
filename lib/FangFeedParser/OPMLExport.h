#ifndef OPMLEXPORT_H
#define OPMLEXPORT_H

#include <QList>
#include <QString>

#include "RawFeed.h"

/*!
    \brief Exports a given feed list to an OPML file.

    That's all.  Nothing more to see here, sir.
 */
class OPMLExport
{
public:
    static bool save(const QString &file, const QList<RawFeed*>& feeds);
};

#endif // OPMLEXPORT_H
