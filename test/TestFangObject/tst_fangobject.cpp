#include <QtTest>
#include <QDebug>
#include "../../src/FangObject.h"

// For capturing log output
static QStringList capturedMessages;
static QtMessageHandler originalHandler = nullptr;

void testMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);
    capturedMessages.append(msg);
}

// Helper class for testing
class TestObject : public FangObject
{
    Q_OBJECT
public:
    explicit TestObject(QObject *parent = nullptr) : FangObject(parent) {}
};

// Another helper class with a different name for testing class name output
class AnotherTestObject : public FangObject
{
    Q_OBJECT
public:
    explicit AnotherTestObject(QObject *parent = nullptr) : FangObject(parent) {}
};

class TestFangObject : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();

    // Test cases
    void testConstructorAndDestructor();
    void testStackAllocation();
    void testHeapAllocationWithDeletion();
    void testHeapAllocationWithoutDeletion();
    void testParentChildHierarchy();
    void testParentDeletesChildren();
    void testMultipleChildrenDeleted();
    void testLeakDetectionAfterCleanup();

    // printRemainingObjects tests
    void testPrintRemainingObjects_emptyOutput();
    void testPrintRemainingObjects_withObjects();
    void testPrintRemainingObjects_showsClassNames();
};

void TestFangObject::initTestCase()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    // Verify we can call the getter
    int count = FangObject::getRemainingObjectCount();
    Q_UNUSED(count);
#endif
}

void TestFangObject::init()
{
    // Nothing needed - each test manages its own objects
}

void TestFangObject::cleanup()
{
    // Nothing needed - each test cleans up its own objects
}

void TestFangObject::testConstructorAndDestructor()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    // Create and immediately delete an object
    FangObject* obj = new FangObject();
    QVERIFY(obj != nullptr);

    // Count should increase by 1
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 1);

    delete obj;

    // After deletion, count should return to initial
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testStackAllocation()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    {
        // Object on stack - should be automatically cleaned up
        FangObject stackObj;
        QVERIFY(stackObj.parent() == nullptr);

        // While in scope, count should be 1 more than initial
        QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 1);
    } // stackObj destroyed here

    // After scope exit, object should be removed from tracking
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testHeapAllocationWithDeletion()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    FangObject* obj1 = new FangObject();
    FangObject* obj2 = new FangObject();
    FangObject* obj3 = new FangObject();

    // Count should increase by 3
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 3);

    // Delete all objects
    delete obj1;
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 2);

    delete obj2;
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 1);

    delete obj3;
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testHeapAllocationWithoutDeletion()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    // Intentionally leak objects to test leak detection
    FangObject* leak1 = new FangObject();
    FangObject* leak2 = new FangObject();

    // Should report 2 leaked objects
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 2);

    // Cleanup for this test
    delete leak1;
    delete leak2;

    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testParentChildHierarchy()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    FangObject* parent = new FangObject();
    FangObject* child = new FangObject(parent);

    // Verify parent-child relationship
    QVERIFY(child->parent() == parent);
    QCOMPARE(parent->children().count(), 1);
    QVERIFY(parent->children().contains(child));

    // Should have 2 objects tracked (parent + child)
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 2);

    delete parent;
    // Child should be automatically deleted by Qt's parent-child mechanism

    // All objects should be cleaned up
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testParentDeletesChildren()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    FangObject* parent = new FangObject();
    FangObject* child1 = new FangObject(parent);
    FangObject* child2 = new FangObject(parent);
    FangObject* child3 = new FangObject(parent);

    Q_UNUSED(child1);
    Q_UNUSED(child2);
    Q_UNUSED(child3);

    QCOMPARE(parent->children().count(), 3);

    // Should have 4 objects tracked (1 parent + 3 children)
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 4);

    // Delete parent - should delete all children
    delete parent;

    // All objects should be cleaned up
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testMultipleChildrenDeleted()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    FangObject* parent = new FangObject();

    // Create multiple levels of hierarchy
    FangObject* child1 = new FangObject(parent);
    FangObject* child2 = new FangObject(parent);
    FangObject* grandchild1 = new FangObject(child1);
    FangObject* grandchild2 = new FangObject(child1);
    FangObject* grandchild3 = new FangObject(child2);

    Q_UNUSED(grandchild1);
    Q_UNUSED(grandchild2);
    Q_UNUSED(grandchild3);

    QCOMPARE(parent->children().count(), 2);
    QCOMPARE(child1->children().count(), 2);
    QCOMPARE(child2->children().count(), 1);

    // Should have 6 total objects (1 parent + 2 children + 3 grandchildren)
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 6);

    // Delete parent - should cascade delete all descendants
    delete parent;

    // All objects should be cleaned up
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testLeakDetectionAfterCleanup()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    // Allocate objects
    FangObject* obj1 = new FangObject();
    FangObject* obj2 = new FangObject();
    FangObject* obj3 = new FangObject();

    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 3);

    // Delete some but not all
    delete obj1;
    delete obj3;
    // obj2 is still allocated

    // Should have 1 remaining object
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 1);

    // Cleanup the remaining object
    delete obj2;

    // Now should be clean
    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testPrintRemainingObjects_emptyOutput()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    // Only run this test if we start with no objects (or known count)
    // This ensures a clean baseline for testing output

    // Install custom message handler
    capturedMessages.clear();
    originalHandler = qInstallMessageHandler(testMessageHandler);

    // Call with no additional objects created
    FangObject::printRemainingObjects();

    // Restore original handler
    qInstallMessageHandler(originalHandler);

    // Verify output contains the expected header
    bool foundHeader = false;
    bool foundCount = false;
    for (const QString& msg : capturedMessages) {
        if (msg.contains("FangObject leak check")) {
            foundHeader = true;
        }
        if (msg.contains("Remaining objects:")) {
            foundCount = true;
            // Verify the count matches what we expect
            QVERIFY(msg.contains(QString::number(initialCount)));
        }
    }

    QVERIFY(foundHeader);
    QVERIFY(foundCount);
#endif
}

void TestFangObject::testPrintRemainingObjects_withObjects()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    // Create some objects
    FangObject* obj1 = new FangObject();
    FangObject* obj2 = new FangObject();

    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 2);

    // Install custom message handler
    capturedMessages.clear();
    originalHandler = qInstallMessageHandler(testMessageHandler);

    // Call printRemainingObjects
    FangObject::printRemainingObjects();

    // Restore original handler
    qInstallMessageHandler(originalHandler);

    // Verify output shows correct count
    bool foundCorrectCount = false;
    for (const QString& msg : capturedMessages) {
        if (msg.contains("Remaining objects:") &&
            msg.contains(QString::number(initialCount + 2))) {
            foundCorrectCount = true;
        }
    }

    QVERIFY(foundCorrectCount);

    // Cleanup
    delete obj1;
    delete obj2;

    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

void TestFangObject::testPrintRemainingObjects_showsClassNames()
{
#ifdef FANG_OBJECT_LEAK_CHECK
    int initialCount = FangObject::getRemainingObjectCount();

    // Create objects of different types
    TestObject* testObj1 = new TestObject();
    TestObject* testObj2 = new TestObject();
    AnotherTestObject* anotherObj = new AnotherTestObject();

    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount + 3);

    // Install custom message handler
    capturedMessages.clear();
    originalHandler = qInstallMessageHandler(testMessageHandler);

    // Call printRemainingObjects
    FangObject::printRemainingObjects();

    // Restore original handler
    qInstallMessageHandler(originalHandler);

    // Verify output contains class names
    bool foundTestObject = false;
    bool foundAnotherTestObject = false;

    for (const QString& msg : capturedMessages) {
        if (msg.contains("TestObject")) {
            foundTestObject = true;
        }
        if (msg.contains("AnotherTestObject")) {
            foundAnotherTestObject = true;
        }
    }

    QVERIFY(foundTestObject);
    QVERIFY(foundAnotherTestObject);

    // Cleanup
    delete testObj1;
    delete testObj2;
    delete anotherObj;

    QCOMPARE(FangObject::getRemainingObjectCount(), initialCount);
#endif
}

QTEST_MAIN(TestFangObject)
#include "tst_fangobject.moc"
