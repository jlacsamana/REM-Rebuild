#include "GameState.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>

// define initial game values here
GameState::GameState() {
	properties["sanity"] = 100.0;
}

float GameState::GetProperty(std::string key) {
	return this->properties[key];
}

void GameState::SetProperty(std::string key, float newVal) {
	this->properties[key] = newVal;
}

void GameState::RegisterGameEvents(std::vector<GameEvent> events) {
	this->activeEvents = events;
}

void GameState::RegisterEvent(GameEvent event) {
	this->activeEvents.push_back(event);
}

void GameState::ExecuteEventEvalLoop() {
	for (GameEvent evt : this->activeEvents) {
		evt.CheckForFireEvent(this);
	}

	// clean-up 
	this->activeEvents.erase(
		std::remove_if(this->activeEvents.begin(), this->activeEvents.end(), [](const GameEvent& obj) {
			return obj.IsExecuted();
			}),
		this->activeEvents.end()
	);
}