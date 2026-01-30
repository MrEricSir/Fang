#ifndef RAWFEEDIMAGESIZEREWRITER_H
#define RAWFEEDIMAGESIZEREWRITER_H

#include <QObject>
#include <QList>

#include "../parser/RawNews.h"
#include "../FangObject.h"
#include "HTMLSanitizer.h"
#include "ImageGrabber.h"

/*!
    \brief Takes a "raw" HTML feed and processes it in the following ways:
             - Tidy'd into XHTML fragments
             - Image sizes are baked in
             - Javascript is stripped
             - Common social media buttons removed
             - Tracking pixels?  Nope.

    This class orchestrates the processing by delegating to:
      - HTMLSanitizer for HTML cleanup and XHTML conversion
      - ImageGrabber for fetching image dimensions
 */
class RawFeedRewriter : public FangObject
{
    Q_OBJECT
public:
    explicit RawFeedRewriter(QObject *parent = nullptr);


signals:
    /*!
        \brief We're done!  The feed you passed in as been modified.
     */
    void finished();

public slots:

    void rewrite(QList<RawNews*>* newsList);

    /*!
        \return The news list being processed.
     */
    inline QList<RawNews*>* getNewsList() { return newsList; }

private slots:
    void onImageGrabberFinished();

private:
    void finalizeAll();

    QList<RawNews*>* newsList;
    HTMLSanitizer sanitizer;
    ImageGrabber imageGrabber;
};

#endif // RAWFEEDIMAGESIZEREWRITER_H
