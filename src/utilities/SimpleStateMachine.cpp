#include "SimpleStateMachine.h"
#include "ErrorHandling.h"
#include <QMetaMethod>
#include <QMetaObject>
#include <QDebug>

SimpleStateMachine::SimpleStateMachine(QObject *parent) :
    FangObject(parent),
    currentState(-1),
    receiver(nullptr)
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
            qCritical() << "SimpleStateMachine: State transition from" << oldState
                        << "to" << currentState << "not defined";
            return;
        }
    }

    const char* method = stateMap[pair];
    ++method; // Skip first character.

    int methodNumber = receiver->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(method));
    if (methodNumber < 0 && methodNumber != -1) {
        qCritical() << "SimpleStateMachine: Invalid method number" << methodNumber;
        return;
    }

    // Emit the signal.
    emit stateChanged(oldState, currentState);

    // Run the method.
    QMetaMethod metaMethod = receiver->metaObject()->method(methodNumber);
    if (!metaMethod.isValid()) {
        qCritical() << "SimpleStateMachine: Invalid meta method for" << method;
        return;
    }
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
