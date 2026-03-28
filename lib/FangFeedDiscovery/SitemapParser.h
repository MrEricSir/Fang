#ifndef SITEMAPPARSER_H
#define SITEMAPPARSER_H

#include <QByteArray>
#include <QDateTime>
#include <QList>
#include <QString>
#include <QUrl>

class QXmlStreamReader;

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

class SitemapParser
{
public:
    enum SitemapType { UrlSet, SitemapIndex, Invalid };

    SitemapParser();

    SitemapType parse(const QString& xml);
    SitemapType parse(const QByteArray& data);

    QList<SitemapEntry> entries() const { return _entries; }
    QList<SubSitemap> subSitemaps() const { return _subSitemaps; }
    bool hasNewsEntries() const { return _hasNewsEntries; }

private:
    SitemapType parseImpl(QXmlStreamReader& reader);
    void parseUrlSet(QXmlStreamReader& xml);
    void parseSitemapIndex(QXmlStreamReader& xml);

    QList<SitemapEntry> _entries;
    QList<SubSitemap> _subSitemaps;
    bool _hasNewsEntries;
};

#endif // SITEMAPPARSER_H
