#ifndef GAMEEVENT_H  // Header Guards
#define GAMEEVENT_H


#include <functional>
#include <vector>
#include "EventCondition.h"

class GameState;

class GameEvent {
public:
    // Much cleaner syntax
    GameEvent(std::function<void()> eventCallback, std::vector<EventCondition> conditions);
    void CheckForFireEvent(GameState* currentState);


private:
    std::function<void()> callbackToExecute;
    std::vector<EventCondition> conditions;
    bool executed;
};
#endif