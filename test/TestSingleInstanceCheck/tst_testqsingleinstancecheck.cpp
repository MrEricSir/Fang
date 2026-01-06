#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QUuid>

#include "../../src/utilities/QSingleInstanceCheck.h"

class TestSingleInstanceCheck : public QObject
{
    Q_OBJECT

public:
    TestSingleInstanceCheck();

private slots:
    void cleanup();

    // Test cases
    void testFirstInstance();
    void testSecondInstance();
    void testNotifyFromSecondInstance();
    void testUniqueIDsIndependent();
    void testMultipleNotifications();

private:
    QString generateUniqueID();
};

TestSingleInstanceCheck::TestSingleInstanceCheck()
{
}

void TestSingleInstanceCheck::cleanup()
{
    // Small delay to ensure shared memory is released
    QTest::qWait(100);
}

QString TestSingleInstanceCheck::generateUniqueID()
{
    // Generate a unique ID for each test to avoid conflicts
    return QUuid::createUuid().toString();
}

// Test that the first instance is detected.
void TestSingleInstanceCheck::testFirstInstance()
{
    QString id = generateUniqueID();
    QSingleInstanceCheck* check = new QSingleInstanceCheck(id);

    // First instance should not be "already running"
    QVERIFY(!check->isAlreadyRunning());

    delete check;
}

// Test that a second instance is detected.
void TestSingleInstanceCheck::testSecondInstance()
{
    QString id = generateUniqueID();
    QSingleInstanceCheck* first = new QSingleInstanceCheck(id);

    QVERIFY(!first->isAlreadyRunning());

    // Create second instance with same ID
    QSingleInstanceCheck* second = new QSingleInstanceCheck(id);

    // Second instance should detect the first
    QVERIFY(second->isAlreadyRunning());

    delete second;
    delete first;
}

// Test that notify() from second instance triggers notified() on first
void TestSingleInstanceCheck::testNotifyFromSecondInstance()
{
    QString id = generateUniqueID();
    QSingleInstanceCheck* first = new QSingleInstanceCheck(id);
    QSignalSpy spy(first, &QSingleInstanceCheck::notified);

    QVERIFY(!first->isAlreadyRunning());

    // Create second instance
    QSingleInstanceCheck* second = new QSingleInstanceCheck(id);
    QVERIFY(second->isAlreadyRunning());

    // Notify from second instance
    second->notify();

    // First instance should receive the notification
    QVERIFY(spy.wait(5000));
    QCOMPARE(spy.count(), 1);

    delete second;
    delete first;
}

// Test that different unique IDs don't interfere with each other
void TestSingleInstanceCheck::testUniqueIDsIndependent()
{
    QString id1 = generateUniqueID();
    QString id2 = generateUniqueID();

    QSingleInstanceCheck* check1 = new QSingleInstanceCheck(id1);
    QSingleInstanceCheck* check2 = new QSingleInstanceCheck(id2);

    // Both should be first instances since they have different IDs
    QVERIFY(!check1->isAlreadyRunning());
    QVERIFY(!check2->isAlreadyRunning());

    delete check2;
    delete check1;
}

// Test multiple notifications from second instance
void TestSingleInstanceCheck::testMultipleNotifications()
{
    QString id = generateUniqueID();
    QSingleInstanceCheck* first = new QSingleInstanceCheck(id);
    QSignalSpy spy(first, &QSingleInstanceCheck::notified);

    QSingleInstanceCheck* second = new QSingleInstanceCheck(id);
    QVERIFY(second->isAlreadyRunning());

    // Send multiple notifications
    second->notify();
    second->notify();
    second->notify();

    // Wait for all notifications
    QTest::qWait(500);

    // Should have 3 notifications
    QCOMPARE(spy.count(), 3);

    delete second;
    delete first;
}

QTEST_MAIN(TestSingleInstanceCheck)

#include "tst_testqsingleinstancecheck.moc"
