#include <QString>
#include <QTest>
#include <QSignalSpy>
#include <QUuid>

#include "../../src/utilities/SingleInstanceCheck.h"

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
    SingleInstanceCheck* check = new SingleInstanceCheck(id);

    // First instance should not be "already running"
    QVERIFY(!check->isAlreadyRunning());

    delete check;
}

// Test that a second instance is detected.
void TestSingleInstanceCheck::testSecondInstance()
{
    QString id = generateUniqueID();
    SingleInstanceCheck* first = new SingleInstanceCheck(id);

    QVERIFY(!first->isAlreadyRunning());

    // Create second instance with same ID
    SingleInstanceCheck* second = new SingleInstanceCheck(id);

    // Second instance should detect the first
    QVERIFY(second->isAlreadyRunning());

    delete second;
    delete first;
}

// Test that notify() from second instance triggers notified() on first
void TestSingleInstanceCheck::testNotifyFromSecondInstance()
{
    QString id = generateUniqueID();
    SingleInstanceCheck* first = new SingleInstanceCheck(id);
    QSignalSpy spy(first, &SingleInstanceCheck::notified);

    QVERIFY(!first->isAlreadyRunning());

    // Create second instance
    SingleInstanceCheck* second = new SingleInstanceCheck(id);
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

    SingleInstanceCheck* check1 = new SingleInstanceCheck(id1);
    SingleInstanceCheck* check2 = new SingleInstanceCheck(id2);

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
    SingleInstanceCheck* first = new SingleInstanceCheck(id);
    QSignalSpy spy(first, &SingleInstanceCheck::notified);

    SingleInstanceCheck* second = new SingleInstanceCheck(id);
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

#include "tst_testsingleinstancecheck.moc"
