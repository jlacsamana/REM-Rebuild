#include <functional>
#include <vector>
#include "EventCondition.h"

class GameEvent {
public:
    // Much cleaner syntax
    GameEvent(std::function<void(int)> eventCallback);

private:
    std::function<void(int)> callbackToExecute;
    std::vector<EventCondition> conditions;
};