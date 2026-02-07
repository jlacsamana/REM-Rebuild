#pragma once

#ifndef __GAMEWORLD_SCENE_H__

#define __GAMEWORLD_SCENE_H__


#include "cocos2d.h"
#include "data/GameState.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float dt);

    CREATE_FUNC(GameScene);

   
private:
    GameState _gameState;
};






#endif // __GAMEWORLD_SCENE_H__ 