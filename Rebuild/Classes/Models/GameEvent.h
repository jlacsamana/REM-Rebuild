#ifndef GAMEEVENT_H  // Header Guards
#define GAMEEVENT_H

#include "BaseGameEvent.h"
#include "Models/EventCondition.h"
#include <functional>
#include <memory>
#include <tuple>
#include <vector>

template <class... Args>
class GameEvent : public BaseGameEvent {
public:
    GameEvent(
        std::function<void(Args...)> eventCallback,
        std::vector<EventCondition> conditions,
        Args... args);

	~GameEvent();

    void checkForFireEvent(GameState* currentState);
    bool isExecuted() const;

private:
    std::function<void(Args...)> _callbackToExecute;
	std::vector<EventCondition> _conditions;
	std::tuple<Args...> _args;
    bool _executed;
};

template <class... Args>
GameEvent<Args...>::GameEvent(
	std::function<void(Args...)> eventCallback,
	std::vector<EventCondition> conditions,
	Args... args) :
	_callbackToExecute(eventCallback),
	_conditions(conditions),
	_args(std::make_tuple(args...)),
	_executed(false)
{
}

template<class ...Args>
inline GameEvent<Args...>::~GameEvent()
{
}

template <class... Args>
void GameEvent<Args...>::checkForFireEvent(GameState* currentState) {
	if (!_executed) {
		bool shouldExecute = true;
		for (EventCondition condition : _conditions) {
			switch (condition.comparitor) {
			case CondComparitor::LT:
				if (!(currentState->getProperty(condition.key) < condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::GT:
				if (!(currentState->getProperty(condition.key) > condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::EQ:
				if (!(currentState->getProperty(condition.key) == condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::GTEQ:
				if (!(currentState->getProperty(condition.key) >= condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::LTEQ:
				if (!(currentState->getProperty(condition.key) <= condition.value)) {
					shouldExecute = false;
				}
				break;
			}
		}

		if (shouldExecute) {
			std::apply(_callbackToExecute, _args);
			_executed = true;
		}
	}
}

template <class... Args>
bool GameEvent<Args...>::isExecuted() const {
	return _executed;
}

#endif
