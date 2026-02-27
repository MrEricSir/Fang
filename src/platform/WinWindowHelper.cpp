#include "WinWindowHelper.h"
#include "../models/FangSettings.h"

#include <QApplication>
#include <QScreen>

#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>

WinWindowHelper::WinWindowHelper(QQuickWindow* window, FangSettings* settings, FangObject* parent)
    : FangObject(parent)
    , m_window(window)
    , m_settings(settings)
    , m_hwnd(reinterpret_cast<void*>(window->winId()))
{
    HWND hwnd = reinterpret_cast<HWND>(m_hwnd);

    // Calculate metrics first — needed before any frame work.
    updateMetrics();

    // Install the event filter.
    QApplication::instance()->installNativeEventFilter(this);

    // Minimal frame extension so DWM keeps the window shadow.
    MARGINS margins = {0, 0, 1, 0};
    DwmExtendFrameIntoClientArea(hwnd, &margins);

    // Sync dark mode with app theme.
    updateDarkMode();

    // Force a frame recalculation. This triggers WM_NCCALCSIZE which we handle to remove
    // the default title bar.
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

    // Recalculate metrics when monitor changes.
    connect(m_window, &QWindow::screenChanged, this, &WinWindowHelper::updateMetrics);

    // Update dark mode when app theme changes.
    connect(m_settings, &FangSettings::currentStyleChanged, this, &WinWindowHelper::updateDarkMode);
}

WinWindowHelper::~WinWindowHelper()
{
    QApplication::instance()->removeNativeEventFilter(this);
}

int WinWindowHelper::titleBarHeight() const
{
    return qRound(m_titleBarHeight / m_window->devicePixelRatio());
}

int WinWindowHelper::captionHeight() const
{
    return qRound(m_captionHeight / m_window->devicePixelRatio());
}

int WinWindowHelper::buttonWidth() const
{
    return qRound(m_buttonWidth / m_window->devicePixelRatio());
}

void WinWindowHelper::updateMetrics()
{
    HWND hwnd = reinterpret_cast<HWND>(m_hwnd);
    UINT dpi = GetDpiForWindow(hwnd);

    int frame_x = GetSystemMetricsForDpi(SM_CXFRAME, dpi);
    int frame_y = GetSystemMetricsForDpi(SM_CYFRAME, dpi);
    int padding  = GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);

    m_resizeBorderWidth  = frame_x + padding;
    m_resizeBorderHeight = frame_y + padding;
    m_captionHeight      = GetSystemMetricsForDpi(SM_CYCAPTION, dpi);
    m_buttonWidth        = MulDiv(46, dpi, 96);

    int newHeight = m_resizeBorderHeight + m_captionHeight;
    if (newHeight != m_titleBarHeight) {
        m_titleBarHeight = newHeight;
        emit titleBarHeightChanged();
    }
}

void WinWindowHelper::updateDarkMode()
{
    HWND hwnd = reinterpret_cast<HWND>(m_hwnd);
    BOOL dark = (m_settings->getCurrentStyle() == "DARK") ? TRUE : FALSE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
}

bool WinWindowHelper::nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result)
{
    if (eventType != "windows_generic_MSG" || !result)
        return false;

    MSG* msg = static_cast<MSG*>(message);

    // Only handle messages for our window.
    if (msg->hwnd != reinterpret_cast<HWND>(m_hwnd))
        return false;

    switch (msg->message) {

    // ── Remove the default title bar ────────────────────────────────────
    case WM_NCCALCSIZE: {
        if (msg->wParam == TRUE) {
            NCCALCSIZE_PARAMS* params = reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);

            // When maximized, inset by the frame thickness so content isn't
            // clipped behind the screen edge.
            if (IsZoomed(msg->hwnd)) {
                params->rgrc[0].top    += m_resizeBorderHeight;
                params->rgrc[0].left   += m_resizeBorderWidth;
                params->rgrc[0].right  -= m_resizeBorderWidth;
                params->rgrc[0].bottom -= m_resizeBorderHeight;
            }

            // Return 0 — removes the default title bar.
            *result = 0;
            return true;
        }
        break;
    }

    // ── Hit testing: caption buttons, resize edges, client area ────────
    case WM_NCHITTEST: {
        POINT cursor = {GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)};
        ScreenToClient(msg->hwnd, &cursor);

        RECT rc;
        GetClientRect(msg->hwnd, &rc);

        bool isMaximized = IsZoomed(msg->hwnd);
        int tbHeight = isMaximized ? m_captionHeight : m_titleBarHeight;

        // Caption buttons (top-right) — return HTCLIENT so QML handles
        // interaction.  Must check before resize edges to avoid HTTOPRIGHT.
        int buttonsWidth = m_buttonWidth * 3;
        int buttonZoneLeft = rc.right - buttonsWidth;
        if (cursor.y < tbHeight && cursor.x >= buttonZoneLeft) {
            *result = HTCLIENT;
            return true;
        }

        // Resize edges (only when not maximized).
        if (!isMaximized) {
            bool onLeft   = cursor.x < m_resizeBorderWidth;
            bool onRight  = cursor.x >= (rc.right - m_resizeBorderWidth);
            bool onTop    = cursor.y < m_resizeBorderHeight;
            bool onBottom = cursor.y >= (rc.bottom - m_resizeBorderHeight);

            if (onTop && onLeft)     { *result = HTTOPLEFT;     return true; }
            if (onTop && onRight)    { *result = HTTOPRIGHT;    return true; }
            if (onBottom && onLeft)  { *result = HTBOTTOMLEFT;  return true; }
            if (onBottom && onRight) { *result = HTBOTTOMRIGHT; return true; }
            if (onLeft)              { *result = HTLEFT;        return true; }
            if (onRight)             { *result = HTRIGHT;       return true; }
            if (onTop)               { *result = HTTOP;         return true; }
            if (onBottom)            { *result = HTBOTTOM;      return true; }
        }

        // Everything else is client area — QML handles drag via startSystemMove().
        *result = HTCLIENT;
        return true;
    }

    // ── Constrain maximized size to work area (taskbar stays visible) ──
    case WM_GETMINMAXINFO: {
        MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(msg->lParam);
        HMONITOR monitor = MonitorFromWindow(msg->hwnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi;
        mi.cbSize = sizeof(mi);
        if (GetMonitorInfo(monitor, &mi)) {
            mmi->ptMaxPosition.x = mi.rcWork.left - mi.rcMonitor.left;
            mmi->ptMaxPosition.y = mi.rcWork.top  - mi.rcMonitor.top;
            mmi->ptMaxSize.x     = mi.rcWork.right  - mi.rcWork.left;
            mmi->ptMaxSize.y     = mi.rcWork.bottom - mi.rcWork.top;
        }
        // Fall through so Qt can enforce minimumWidth/minimumHeight.
        break;
    }

    // ── DPI changed: recalculate metrics ───────────────────────────────
    case WM_DPICHANGED: {
        updateMetrics();
        break;  // Let Qt handle the rest of the DPI change.
    }

    } // switch

    return false;
}
