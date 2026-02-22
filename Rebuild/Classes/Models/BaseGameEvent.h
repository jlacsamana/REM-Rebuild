#ifndef BASE_GAME_EVENT_H  
#define BASE_GAME_EVENT_H

class GameState;

class BaseGameEvent {
public:
    virtual ~BaseGameEvent() = default;

    virtual void checkForFireEvent(GameState* currentState) = 0;
    virtual bool isExecuted() const = 0;
};
#endif