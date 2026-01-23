#ifndef QSIMPLESTATEMACHINE_H
#define QSIMPLESTATEMACHINE_H

#include <QDebug>
#include <QObject>
#include <QMap>
#include <QPair>
#include <functional>

/*!
 * \brief This class provides a stupidly simple state machine with few dependencies.
 *
 * // Set up your states as enums, like this:
 * enum MyStates {
 *   START,
 *   STATE_A,
 *   STATE_B,
 *   COMPLETE
 * };
 *
 * // Transitions are handled via callbacks.
 * QSimpleStateMachine machine;
 * machine.addStateChange(START, STATE_A, [this]() { startToStateA(); });
 * machine.addStateChange(START, STATE_B, [this]() { startToStateB(); });
 * machine.addStateChange(STATE_A, STATE_B, [this]() { stateAToStateB(); });
 * // ... etc.
 *
 * // To switch from any state to a specific state, use -1
 * machine.addStateChange(-1, COMPLETE, [this]() { onComplete(); });
 *
 * // Set the start state, then call setState() as needed.
 * machine.start(START);
 * // ...
 * machine.setState(STATE_B);
 *
 *
 * That's it!
 */
class QSimpleStateMachine : public QObject
{
    Q_OBJECT
    
public:
    explicit inline QSimpleStateMachine(QObject *parent = nullptr) :
        QObject(parent),
        currentState(-1)
    {
    }

    /*!
     * Starts the state machine with the provided initial state; does not trigger any callbacks.
     */
    inline void start(int initialState)
    {
        currentState = initialState;
    }

    /*!
     * Causes a state change, assuming state != getState().  If there is no path
     * from the previous state to this state, a critical error will be logged.
     */
    inline void setState(int state)
    {
        if (currentState == state) {
            // Nothing to do.
            return;
        }

        // Make the switch.
        int oldState = currentState;
        currentState = state;

        // Find the callback.
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

        // Emit the signal.
        emit stateChanged(oldState, currentState);

        // Run the callback.
        const std::function<void()>& callback = stateMap[pair];
        if (callback) {
            callback();
        } else {
            qCritical() << "SimpleStateMachine: Callback for transition" << oldState
                        << "->" << currentState << "is null";
        }
    }
    
    /*!
     * Returns the current state.
     */
    inline int getState() { return currentState; }

    /*!
     * Sets a callback to be executed when the state changes from one state to
     * another. The callback can be any std::function that matches the parameter type.
     */
    inline void addStateChange(int from, int to, std::function<void()> callback)
    {
        stateMap.insert(QPair<int, int>(from, to), callback);
    }

signals:
    /**
     * Signals a state change from one state to another.
     */
    void stateChanged(int from, int to);

private:
    // The state.
    int currentState;

    // Maps a (from, to) state pair to a callback function.
    QMap<QPair<int, int>, std::function<void()>> stateMap;
};

#endif // QSIMPLESTATEMACHINE_H
