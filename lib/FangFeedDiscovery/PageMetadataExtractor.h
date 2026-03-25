#ifndef PAGEMETADATAEXTRACTOR_H
#define PAGEMETADATAEXTRACTOR_H

#include <QString>
#include <QUrl>

struct PageMetadata {
    QString title;
    QString description;
    QUrl imageUrl;
    QString author;
    QString lang;  // from <html lang="...">
};

class PageMetadataExtractor
{
public:
    static PageMetadata extract(const QString& xhtml);
};

#endif // PAGEMETADATAEXTRACTOR_H
