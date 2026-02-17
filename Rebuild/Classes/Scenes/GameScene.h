#pragma once

#ifndef __GAMEWORLD_SCENE_H__
#define __GAMEWORLD_SCENE_H__

#include "cocos2d.h"
#include "Models/GameState.h"

#include "Components/HoverableButton.h"
#include "Components/Dialogue.h"
#include "ui/UIButton.h"
#include "ui/UIVBox.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{

public:
    GameScene();
    ~GameScene();

    static cocos2d::Scene *createScene();

    virtual bool init();

    virtual void update(float dt);

    void laptopClickCallback(Ref* pSender);
    void bookClickCallback(Ref* pSender);
    void canClickCallback(Ref* pSender);

    void setButtonsEnabled(bool enabled);

    CREATE_FUNC(GameScene);

private:
    GameState _gameState;

    Dialogue* _activeDialogue;

    HoverableButton* _laptopButton;
    HoverableButton* _bookButton;
    HoverableButton* _canButton;

    const std::string LAPTOP_BUTTON_FILE_NAME = "final/final_laptop.png";
    const std::string HOVER_LAPTOP_BUTTON_FILE_NAME = "final/final_laptop_hover.png";
    const std::string BOOK_BUTTON_FILE_NAME = "final/final_book.png";
    const std::string HOVER_BOOK_BUTTON_FILE_NAME = "final/final_book_hover.png";
    const std::string CAN_BUTTON_FILE_NAME = "final/final_redCow.png";
    const std::string HOVER_CAN_BUTTON_FILE_NAME = "final/final_redCow_hover.png";
};

#endif // __GAMEWORLD_SCENE_H__