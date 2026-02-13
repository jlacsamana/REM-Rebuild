#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

#include "ui/UIButton.h"
#include "ui/UIVBox.h"

USING_NS_CC;

class TitleScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    void mouseMoveCallback(EventMouse* event);

    void menuStartCallback(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);

private:
    ui::Button* _startButton;
    ui::Button* _quitButton;
    ui::VBox* _btnLayout;

    const char* START_BUTTON_FILE_NAME = "UI/default/startGame.png";
    const char* HOVER_START_BUTTON_FILE_NAME = "UI/hover/startGameHover.png";

    const char* QUIT_BUTTON_FILE_NAME = "UI/default/quitGame.png";
    const char* HOVER_QUIT_BUTTON_FILE_NAME = "UI/hover/quitGameHover.png";
};

#endif // __TITLE_SCENE_H__
