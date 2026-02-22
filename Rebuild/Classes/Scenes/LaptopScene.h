#ifndef __LAPTOP_SCENE_H__
#define __LAPTOP_SCENE_H__

#include "cocos2d.h"

#include "GameScene.h"
#include "ui/UIImageView.h"

USING_NS_CC;

class LaptopScene : public Scene
{
public:
    static Scene* createScene(int laptopInteractionNum);
    static Scene* create(int laptopInteractionNum);
    bool init(int laptopInteractionNum);

    void backToGameScene();
    void subInteraction(Ref* pSender);

private:
    ui::ImageView* _background;

    int _primaryInteractNum;
    int _secondaryInteractNum;

    const int SUB_INTERACTIONS[4] = {2, 0, 1, 1};
    const int LAST_PRIMARY_INTERACT_NUM = 3;
    const std::string BACKGROUND_PATH = "final/zoomed_laptop_states/interaction_";

    void updateImage();
};

#endif // __LAPTOP_SCENE_H__

