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

    void CheckForFireEvent(GameState* currentState);
    bool IsExecuted() const;

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
void GameEvent<Args...>::CheckForFireEvent(GameState* currentState) {
	if (!_executed) {
		bool shouldExecute = true;
		for (EventCondition condition : _conditions) {
			switch (condition.comparitor) {
			case CondComparitor::LT:
				if (!(currentState->GetProperty(condition.key) < condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::GT:
				if (!(currentState->GetProperty(condition.key) > condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::EQ:
				if (!(currentState->GetProperty(condition.key) == condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::GTEQ:
				if (!(currentState->GetProperty(condition.key) >= condition.value)) {
					shouldExecute = false;
				}
				break;
			case CondComparitor::LTEQ:
				if (!(currentState->GetProperty(condition.key) <= condition.value)) {
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
bool GameEvent<Args...>::IsExecuted() const {
	return _executed;
}

#endif