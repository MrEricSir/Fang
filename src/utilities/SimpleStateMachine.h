#ifndef SIMPLESTATEMACHINE_H
#define SIMPLESTATEMACHINE_H

#include <QObject>
#include <QMap>
#include <QPair>

/**
 * @brief This class provides a stupidly simple state machine with few dependencies.
 * To use:
 * 
 * // Set up your states as enums, like this:
 * enum MyStates {
 *   START,
 *   STATE_A,
 *   STATE_B,
 *   COMPLETE
 * };
 * 
 * // Transitions are handled via slots on an object you provide.
 * SimpleStateMachine machine;
 * machine.setReceiver(myObject); // Object the slots will be called on.
 * machine.addStateChange(START, STATE_A, SLOT(startToStateA()));
 * machine.addStateChange(START, STATE_B, SLOT(startToStateB()));
 * machine.addStateChange(STATE_A, STATE_B, SLOT(stateAToStateB()));
 * // ... etc.
 * 
 * // To switch from any state to a specific state, use -1
 * machine.addStateChange(-1, COMPLETE, SLOT(onComplete()));
 * 
 * // Set the start state, then call setState() as needed.
 * machine.start(START);
 * // ...
 * machine.setState(STATE_B);
 * 
 * 
 * That's it!
 */
class SimpleStateMachine : public QObject
{
    Q_OBJECT
    
public:
    explicit SimpleStateMachine(QObject *parent = 0);
    
signals:
    /**
     * @brief Signals a state change.  This is called before the slot.
     * @param from Previous state.
     * @param to   New state.
     */
    void stateChanged(int from, int to);
    
public slots:
    /**
     * @brief Causes a state change, assuming state != getState().  If there is no path
     * from the previous state to this state, an assert will trigger.
     * @param state
     */
    void setState(int state);
    
    /**
     * @return Current state.
     */
    int getState() { return currentState; }
    
public:
    
    /**
     * @brief Sets the object that will receive the slot calls.
     * @param receiver
     */
    void setReceiver(QObject *receiver);
    
    /**
     * @brief Sets a slot to be executed when the state changes from one state to
     * another.
     * @param from    Previous state
     * @param to      New state
     * @param method  A valid SLOT() on the receiving object.
     */
    void addStateChange(int from, int to, const char* method);
    
    /**
     * @brief Sets the initial state. No slots are triggered.
     * @param initialState
     */
    void start(int initialState);
    
private:
    // The state.
    int currentState;
    
    // The receiving object for the slots.
    QObject *receiver;
    
    // Maps a (from, to) state pair to a slot name.
    QMap<QPair<int, int>, const char*> stateMap;
};

#endif // SIMPLESTATEMACHINE_H
