#ifndef BASE_GAME_EVENT_H  
#define BASE_GAME_EVENT_H

class GameState;

class BaseGameEvent {
public:
    virtual ~BaseGameEvent() = default;

    virtual void CheckForFireEvent(GameState* currentState) = 0;
    virtual bool IsExecuted() const = 0;
};
#endif