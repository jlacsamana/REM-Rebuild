#pragma once

#ifndef __GAMEWORLD_SCENE_H__

#define __GAMEWORLD_SCENE_H__


#include "cocos2d.h"


USING_NS_CC;





class GameScene : public cocos2d::Scene
{

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
};



#endif // __GAMEWORLD_SCENE_H__ 