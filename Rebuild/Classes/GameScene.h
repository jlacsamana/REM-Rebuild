#pragma once

#ifndef __GAMEWORLD_SCENE_H__
#define __GAMEWORLD_SCENE_H__


#include "cocos2d.h"
#include "data/GameState.h"

#include "ui/UIButton.h"
#include "ui/UIVBox.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float dt);

    void TestCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);

   
private:
    GameState _gameState;
    ui::Button* testBtn;
    ui::VBox* _btnLayout;

    const char* START_BUTTON_FILE_NAME = "UI/default/startGame.png";
    const char* HOVER_START_BUTTON_FILE_NAME = "UI/hover/startGameHover.png";
};

#endif // __GAMEWORLD_SCENE_H__ 