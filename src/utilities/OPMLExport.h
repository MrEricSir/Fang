#ifndef OPMLEXPORT_H
#define OPMLEXPORT_H

#include <QString>

#include "../models/ListModel.h"

/**
 * @brief Exports a given feed list to 
 * 
 * That's all.  Nothing more to see here, sir.
 */
class OPMLExport
{
public:
    OPMLExport();
    
    static void save(const QString &file, ListModel* feedList);
};

#endif // OPMLEXPORT_H
