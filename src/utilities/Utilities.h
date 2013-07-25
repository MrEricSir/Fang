#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QObject>
#include <QDebug>

class Utilities
{
public:
    Utilities();
    
    static QString htmlify(const QString &content);
};

#endif // UTILITIES_H
