#include "GameState.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// define initial game values here
GameState::GameState() {
	_properties["sanity"] = 100.0;
}

float GameState::GetProperty(std::string key) {
	return _properties[key];
}

void GameState::SetProperty(std::string key, float newVal) {
	_properties[key] = newVal;
}

void GameState::RegisterEvent(std::unique_ptr<BaseGameEvent>& event) {
	_activeEvents.push_back(std::move(event));
}

void GameState::ExecuteEventEvalLoop() {
	for (auto &event : _activeEvents) {
		event->CheckForFireEvent(this);
	}

	// clean-up 
	_activeEvents.erase(
		std::remove_if(_activeEvents.begin(), _activeEvents.end(), [](auto& event) {
			return event->IsExecuted();
			}),
		_activeEvents.end()
	);
}