#ifndef SITEMAPPARSER_H
#define SITEMAPPARSER_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QUrl>

#include "../FangObject.h"

struct SitemapEntry {
    QUrl url;
    QDateTime lastmod;         // from <lastmod>, may be invalid
    QString newsTitle;         // from <news:title>, may be empty
    QDateTime publicationDate; // from <news:publication_date>, may be invalid
    QString language;          // from <news:language>, e.g. "en", "eng"
    QString publicationName;   // from <news:name>, e.g. "Associated Press"
    QUrl imageUrl;             // from <image:loc>, may be empty
};

struct SubSitemap {
    QUrl url;
    QDateTime lastmod; // may be invalid
};

class SitemapParser : public FangObject
{
    Q_OBJECT
public:
    enum SitemapType { UrlSet, SitemapIndex, Invalid };

    explicit SitemapParser(QObject* parent = nullptr);

    SitemapType parse(const QString& xml);

    QList<SitemapEntry> entries() const { return _entries; }
    QList<SubSitemap> subSitemaps() const { return _subSitemaps; }
    bool hasNewsEntries() const { return _hasNewsEntries; }

private:
    void parseUrlSet(class QXmlStreamReader& xml);
    void parseSitemapIndex(class QXmlStreamReader& xml);

    QList<SitemapEntry> _entries;
    QList<SubSitemap> _subSitemaps;
    bool _hasNewsEntries;
};

#endif // SITEMAPPARSER_H
