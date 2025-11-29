#include "WebServer.h"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QUrl>

#include "../FangApp.h"
#include "../utilities/NetworkUtilities.h"

WebServer::WebServer(QObject *parent) :
    FangObject(parent)
{
    qDebug() << "Launching WebServer...";

    tcpServer = new QTcpServer(this);

    // Listen for incoming connections!
    if (!tcpServer->listen(QHostAddress::LocalHost, 2844)) {
        qDebug() << "WebServer: TCP server unable to listen";

        // TODO: Throw an exception?
    }

    if (!server.bind(tcpServer)) {
        qDebug() << "WebServer: Unable to bind to TCP server";

        // TODO: Throw an exception?
    }

    // Needed for CORS due to qrc file paths.
    server.addAfterRequestHandler(&server, [](const QHttpServerRequest &, QHttpServerResponse &response) {
        auto headers = response.headers();
        headers.append(QHttpHeaders::WellKnownHeader::AccessControlAllowOrigin, "*");
        response.setHeaders(std::move(headers));
    });

    server.route("/api/open_link", QHttpServerRequest::Method::Post, this, [] (const QHttpServerRequest &request) {
        QJsonObject json = QJsonDocument::fromJson(request.body()).object();
        QString url = json.value("url").toString();
        //qDebug() << "Open URL:" << url;

        QString urlFixed = NetworkUtilities::urlFixup(url);
        QDesktopServices::openUrl(QUrl(urlFixed));
        return "";
    });

    server.route("/api/set_bookmark/<arg>", this, [] (qlonglong newsID) {
        FangApp::instance()->setBookmark(newsID);
        return "";
    });

    server.route("/api/force_bookmark/<arg>", this, [] (qlonglong newsID) {
        FangApp::instance()->setBookmark(newsID, true);
        return "";
    });

    server.route("/api/pin/<arg>", this, [] (qlonglong newsID) {
        FangApp::instance()->setPin(newsID, true);
        return "";
    });

    server.route("/api/unpin/<arg>", this, [] (qlonglong newsID) {
        FangApp::instance()->setPin(newsID, false);
        return "";
    });

}
