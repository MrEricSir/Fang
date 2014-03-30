#include "SimpleStateMachine.h"
#include <QMetaMethod>
#include <QMetaObject>
#include <QDebug>

SimpleStateMachine::SimpleStateMachine(QObject *parent) :
    QObject(parent),
    currentState(-1),
    receiver(NULL)
{
}

void SimpleStateMachine::setState(int state)
{
    if (currentState == state) {
        // Nothing to do.
        return;
    }
    
    // Make the switch.
    int oldState = currentState;
    currentState = state;
    
    // Find the method name.
    QPair<int, int> pair(oldState, currentState);
    if (!stateMap.contains(pair)) {
        // Default to -1 (all) state.
        pair = QPair<int, int>(-1, currentState);
        if (!stateMap.contains(pair)) {
            qDebug() << "State transition from " << oldState << " to " << currentState << " not avaliable!";
            Q_ASSERT(false);
        }
    }
    
    const char* method = stateMap[pair];
    ++method; // Skip first character.
    
    int methodNumber = methodNumber = receiver->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(method));
    //qDebug() << "Method #: " << methodNumber;
    Q_ASSERT(methodNumber > 0 || methodNumber == -1);
    
    // Emit the signal.
    emit stateChanged(oldState, currentState);
    
    // Run the method.
    QMetaMethod metaMethod = receiver->metaObject()->method(methodNumber);
    Q_ASSERT(metaMethod.isValid()); // Ensures the method exists.
    metaMethod.invoke(receiver);
}

void SimpleStateMachine::setReceiver(QObject *receiver)
{
    this->receiver = receiver;
}

void SimpleStateMachine::addStateChange(int from, int to, const char* method)
{
    stateMap.insert(QPair<int, int>(from, to), method);
}

void SimpleStateMachine::start(int initialState)
{
    currentState = initialState;
}
