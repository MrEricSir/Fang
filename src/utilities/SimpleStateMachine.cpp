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
    Q_ASSERT(stateMap.contains(pair));
    const char* method = stateMap[pair];
    ++method; // Skip first character.
    
    int methodNumber = methodNumber = receiver->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(method));
    //qDebug() << "Method #: " << methodNumber;
    Q_ASSERT(methodNumber > 0);
    
    // Emit the signal.
    emit stateChanged(oldState, currentState);
    
    // Run the method.
    QMetaMethod metaMethod = receiver->metaObject()->method(methodNumber);
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
