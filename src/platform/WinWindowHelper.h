#ifndef WINWINDOWHELPER_H
#define WINWINDOWHELPER_H

#include <QAbstractNativeEventFilter>
#include <QQuickWindow>

#include "../FangObject.h"

class FangSettings;

class WinWindowHelper : public FangObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
    Q_PROPERTY(int titleBarHeight READ titleBarHeight NOTIFY titleBarHeightChanged)
    Q_PROPERTY(int captionHeight READ captionHeight NOTIFY titleBarHeightChanged)
    Q_PROPERTY(int buttonWidth READ buttonWidth NOTIFY titleBarHeightChanged)

public:
    explicit WinWindowHelper(QQuickWindow* window, FangSettings* settings, FangObject* parent = nullptr);
    ~WinWindowHelper() override;

    int titleBarHeight() const;   // resize border + caption, logical px
    int captionHeight() const;    // caption only, logical px
    int buttonWidth() const;      // single button width, logical px

    bool nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) override;

signals:
    void titleBarHeightChanged();

private:
    void updateMetrics();
    void updateDarkMode();

    QQuickWindow* m_window;
    FangSettings* m_settings;
    void* m_hwnd;  // HWND

    // Cached DPI-aware metrics (physical pixels).
    int m_resizeBorderWidth = 0;
    int m_resizeBorderHeight = 0;
    int m_captionHeight = 0;
    int m_titleBarHeight = 0;
    int m_buttonWidth = 0;
};

#endif // WINWINDOWHELPER_H
