#include "GameEvent.h"
#include "EventCondition.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"
#include "GameState.h"
USING_NS_CC;

GameEvent::GameEvent(std::function<void()> eventCallback, std::vector<EventCondition> conditions)
{
	this->executed = false;
	this->callbackToExecute = eventCallback;
	this->conditions = conditions;
}

void GameEvent::CheckForFireEvent(GameState* currentState) {
	if (!this->executed) {
		bool shouldExecute = true;
		for (EventCondition condition : this->conditions) {
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
			this->callbackToExecute();
			this->executed = true;
		}
	}
}