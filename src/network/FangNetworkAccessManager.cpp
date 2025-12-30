#include "FangNetworkAccessManager.h"
#include "ResilientNetworkReply.h"
#include "NetworkStateMonitor.h"
#include "../utilities/FangLogging.h"

#include <QNetworkDiskCache>
#include <QStandardPaths>

FangNetworkAccessManager::FangNetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this);
    QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    diskCache->setCacheDirectory(cacheDir);
    if (!cacheDir.isEmpty())
        setCache(diskCache);

    // Set up our circuit breaker.
    NetworkStateMonitor& monitor = NetworkStateMonitor::instance();
    connect(&monitor, &NetworkStateMonitor::circuitOpened,
            this, &FangNetworkAccessManager::onCircuitOpened);
    connect(&monitor, &NetworkStateMonitor::circuitClosed,
            this, &FangNetworkAccessManager::onCircuitClosed);

    qCDebug(logNetwork) << "FangNetworkAccessManager initialized with resilience features";
}

QNetworkReply* FangNetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest& request, QIODevice* outgoingData)
{
    QNetworkRequest& req = const_cast<QNetworkRequest&>(request);
    
#ifdef QT_DEBUG
    // In debug mode, WebKit doesn't like Vine's headers.
    //
    // TODO: Revisit when WebKit is upgraded in Qt.
    //
    // https://github.com/MrEricSir/Fang/issues/77
    // https://bugs.webkit.org/show_bug.cgi?id=129081
    if (req.url().host() == "vine.co") {
        req.setUrl(QUrl("http://0.0.0.0"));
    }
#endif // QT_DEBUG
    
    // This SHOULD be the default, but just in case.
    req.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                          QNetworkRequest::PreferNetwork);
    
    // We have to pretend to be Firefox in order for some stupid servers to speak with us.
    req.setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
    
    // Required for blogs.gnome.org.
    req.setRawHeader("Accept",
                         "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

    return QNetworkAccessManager::createRequest(op, req, outgoingData);
}

ResilientNetworkReply* FangNetworkAccessManager::createResilientGet(
    const QNetworkRequest& request,
    const NetworkRetryPolicy& policy)
{
    auto* resilientReply = new ResilientNetworkReply(
        this,
        request,
        QNetworkAccessManager::GetOperation,
        policy,
        this
    );

    // Monitor network state metrics.
    connect(resilientReply, &ResilientNetworkReply::finished, this, [=]() {
        NetworkStateMonitor::instance().recordSuccess();
        qCDebug(logNetwork) << "Resilient request succeeded: " << request.url();
    });

    connect(resilientReply, &ResilientNetworkReply::failed, this, [=](QNetworkReply::NetworkError error) {
        NetworkStateMonitor::instance().recordFailure();
        qCWarning(logNetwork) << "Resilient request failed: " << request.url()
                              << "Error: " << error;
    });

    return resilientReply;
}

ResilientNetworkReply* FangNetworkAccessManager::createResilientHead(
    const QNetworkRequest& request,
    const NetworkRetryPolicy& policy)
{
    auto* resilientReply = new ResilientNetworkReply(
        this,
        request,
        QNetworkAccessManager::HeadOperation,
        policy,
        this
    );

    // Monitor network state metrics.
    connect(resilientReply, &ResilientNetworkReply::finished, this, [=]() {
        NetworkStateMonitor::instance().recordSuccess();
    });

    connect(resilientReply, &ResilientNetworkReply::failed, this, [=](QNetworkReply::NetworkError) {
        NetworkStateMonitor::instance().recordFailure();
    });

    return resilientReply;
}

bool FangNetworkAccessManager::isCircuitOpen() const
{
    return NetworkStateMonitor::instance().circuitState() == NetworkStateMonitor::Open;
}

float FangNetworkAccessManager::networkFailureRate() const
{
    return NetworkStateMonitor::instance().failureRate();
}

void FangNetworkAccessManager::onCircuitOpened()
{
    qCWarning(logNetwork) << "Circuit breaker OPENED - blocking new network requests";
    emit circuitBreakerOpened();
}

void FangNetworkAccessManager::onCircuitClosed()
{
    qCInfo(logNetwork) << "Circuit breaker CLOSED - resuming network requests";
    emit circuitBreakerClosed();
}
