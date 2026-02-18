#ifndef GAMESTATE_H  // Header Guards
#define GAMESTATE_H
#include "BaseGameEvent.h"
#include <memory>
#include <string>
#include <unordered_map>

class GameState {
public:
	GameState();
	float GetProperty(std::string key);
	void SetProperty(std::string key, float newVal);
	void RegisterEvent(std::unique_ptr<BaseGameEvent>& event);
	void ExecuteEventEvalLoop();

private:
	std::unordered_map<std::string, float> _properties;
	std::vector<std::unique_ptr<BaseGameEvent>> _activeEvents;
};
#endif