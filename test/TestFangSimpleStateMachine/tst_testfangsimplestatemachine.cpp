#include <QString>
#include <QTest>
#include <QSignalSpy>

#include "../../src/utilities/SimpleStateMachine.h"

class TestFangSimpleStateMachine : public QObject
{
    Q_OBJECT
    
public:
    
    enum MyStates {
        START,
        STATE_A,
        STATE_B,
        COMPLETE
    };
    
    TestFangSimpleStateMachine();
    
signals:
    void done();
    
public slots:
    void onStateA();
    void onStateB();
    void onStateComplete();
    
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    
    
private:
    SimpleStateMachine machine;
    int stateCounter;
};

TestFangSimpleStateMachine::TestFangSimpleStateMachine()
{
    stateCounter = 0;
    
    machine.setReceiver(this);
    machine.addStateChange(START, STATE_A, SLOT(onStateA()));
    machine.addStateChange(STATE_A, STATE_B, SLOT(onStateB()));
    machine.addStateChange(-1, COMPLETE, SLOT(onStateComplete()));
}

void TestFangSimpleStateMachine::initTestCase()
{
}

void TestFangSimpleStateMachine::cleanupTestCase()
{
}

void TestFangSimpleStateMachine::onStateA()
{
    qDebug() << "Moved to state a.";
    stateCounter++;
}

void TestFangSimpleStateMachine::onStateB()
{
    qDebug() << "Moved to state b.";
    stateCounter++;
}

void TestFangSimpleStateMachine::onStateComplete()
{
    qDebug() << "Final state!";
    stateCounter++;
    
    emit done();
}

void TestFangSimpleStateMachine::testCase1()
{
    QSignalSpy spy(this, SIGNAL(done()));
    
    machine.start(START);
    machine.setState(STATE_A);
    machine.setState(STATE_B);
    machine.setState(COMPLETE);
    
    // Wait for the signal!
    QCOMPARE(spy.count(), 1);
    
    QVERIFY2(stateCounter == 3, "Wrong state count!");
}

QTEST_APPLESS_MAIN(TestFangSimpleStateMachine)

#include "tst_testfangsimplestatemachine.moc"
