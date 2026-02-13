#ifndef GAMESTATE_H  // Header Guards
#define GAMESTATE_H
#include <unordered_map>
#include <string>
#include "GameEvent.h"


class GameState {
public:
	GameState();
	float GetProperty(std::string key);
	void SetProperty(std::string key, float newVal);
	void RegisterGameEvents(std::vector<GameEvent> events);
	void RegisterEvent(GameEvent event);
	void ExecuteEventEvalLoop();

private:
	std::unordered_map<std::string, float> properties;
	std::vector<GameEvent> activeEvents;



};
#endif