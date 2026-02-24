#import <Cocoa/Cocoa.h>
#include <QQuickWindow>

static void applyTitleBarSettings(NSWindow *nsWindow)
{
    nsWindow.styleMask |= NSWindowStyleMaskFullSizeContentView;
    nsWindow.titlebarAppearsTransparent = YES;
    nsWindow.titleVisibility = NSWindowTitleHidden;
}

void configureTransparentTitleBar(QQuickWindow *window)
{
    if (!window) {
        return;
    }

    NSView *nativeView = reinterpret_cast<NSView *>(window->winId());
    NSWindow *nsWindow = [nativeView window];

    applyTitleBarSettings(nsWindow);

    // Re-apply after window state changes (maximize/restore can reset these).
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    for (NSNotificationName name in @[
        NSWindowDidResizeNotification,
        NSWindowDidDeminiaturizeNotification,
        NSWindowDidChangeScreenNotification
    ]) {
        [center addObserverForName:name
                            object:nsWindow
                             queue:[NSOperationQueue mainQueue]
                        usingBlock:^(NSNotification *) {
            applyTitleBarSettings(nsWindow);
        }];
    }
}
