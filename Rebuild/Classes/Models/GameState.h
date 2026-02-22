#ifndef GAMESTATE_H // Header Guards
#define GAMESTATE_H
#include "BaseGameEvent.h"
#include <memory>
#include <string>
#include <unordered_map>

class GameState
{
public:
	GameState();
	float getProperty(std::string key);
	void setProperty(std::string key, float newVal);
	void incrementProperty(std::string key, float delta);
	void registerEvent(std::unique_ptr<BaseGameEvent> &event);
	void executeEventEvalLoop();

	inline static const std::string KEY_SANITY = "sanity";
	inline static const std::string KEY_CAN_INTERACTIONS = "can_interactions";

private:
	std::unordered_map<std::string, float> _properties;
	std::vector<std::unique_ptr<BaseGameEvent>> _activeEvents;
};
#endif
