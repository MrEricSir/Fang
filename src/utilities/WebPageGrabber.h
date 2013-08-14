#ifndef WEBPAGEGRABBER_H
#define WEBPAGEGRABBER_H

#include <QObject>
#include <QWebView>
#include <QWebPage>
#include <QString>

/**
 * @brief Loads a web page at a given URL and signals with the page when done.
 */
class WebPageGrabber : public QObject
{
    Q_OBJECT
public:
    explicit WebPageGrabber(QObject *parent = 0);
    
signals:
    
    void ready(QWebPage* page);
    
public slots:
    
    void load(const QUrl& url);
    void load(const QString& htmlString, const QUrl& baseUrl = QUrl());
    
private slots:
    
    void onLoadFinished(bool ok);
    void onUrlChanged(const QUrl& url);
    
private:
    QWebView webView;
    
};

#endif // WEBPAGEGRABBER_H
