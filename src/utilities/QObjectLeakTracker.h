#ifndef QOBJECTLEAKTRACKER_H
#define QOBJECTLEAKTRACKER_H

#include <QMap>
#include <QString>
#include <QtGlobal>

#ifdef QT_DEBUG // Debug builds


class QObjectLeakTracker
{
public:
    static void install();
    static void printRemaining();
    static int remainingCount();
    static QMap<QString, int> snapshot();
    static void addPrefix(const QString &prefix);
    static qint64 totalCreated();
    static qint64 totalDestroyed();

    // Helper that records created/destroyed counts within a code block.
    class Scope
    {
    public:
        Scope();
        qint64 created() const;
        qint64 destroyed() const;

    private:
        qint64 createdAtStart;
        qint64 destroyedAtStart;
    };
};

#define FANG_NO_ALLOC_SCOPE() QObjectLeakTracker::Scope _fangAllocScope
#define FANG_ASSERT_NO_ALLOC() Q_ASSERT(_fangAllocScope.created() == 0)

#else // Release builds

class QObjectLeakTracker
{
public:
    static inline void install() {}
    static inline void printRemaining() {}
    static inline int remainingCount() { return 0; }
    static inline QMap<QString, int> snapshot() { return {}; }
    static inline void addPrefix(const QString &) {}
    static inline qint64 totalCreated() { return 0; }
    static inline qint64 totalDestroyed() { return 0; }

    class Scope
    {
    public:
        Scope() = default;
        qint64 created() const { return 0; }
        qint64 destroyed() const { return 0; }
    };
};

#define FANG_NO_ALLOC_SCOPE() do {} while (0)
#define FANG_ASSERT_NO_ALLOC() do {} while (0)

#endif // QT_DEBUG

#endif // QOBJECTLEAKTRACKER_H
