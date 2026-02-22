#include "GameState.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// define initial game values here
GameState::GameState() {
	_properties[KEY_SANITY] = 100.0;
	_properties[KEY_CAN_INTERACTIONS] = 0;
	_properties[KEY_LAPTOP_INTERACTIONS] = 0;
}

float GameState::getProperty(std::string key) {
	return _properties[key];
}

void GameState::setProperty(std::string key, float newVal) {
	_properties[key] = newVal;
}

void GameState::incrementProperty(std::string key, float delta)
{
	_properties[key] += delta;
}

void GameState::registerEvent(std::unique_ptr<BaseGameEvent>& event) {
	_activeEvents.push_back(std::move(event));
}

void GameState::executeEventEvalLoop() {
	for (auto &event : _activeEvents) {
		event->checkForFireEvent(this);
	}

	// clean-up 
	_activeEvents.erase(
		std::remove_if(_activeEvents.begin(), _activeEvents.end(), [](auto& event) {
			return event->isExecuted();
			}),
		_activeEvents.end()
	);
}