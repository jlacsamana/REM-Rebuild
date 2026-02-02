/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TITLEWORLD_SCENE_H__
#define __TITLEWORLD_SCENE_H__

#include "cocos2d.h"

#include "ui/UIButton.h"
#include "ui/UIVBox.h"

USING_NS_CC;

class TitleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void mouseMoveCallback(EventMouse* event);

    void menuStartCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
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

#endif // __TITLEWORLD_SCENE_H__
