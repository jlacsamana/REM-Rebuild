
#include "LaptopScene.h"
#include "Components/HoverableButton.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

USING_NS_CC;

Scene *LaptopScene::createScene(int laptopInteractionNum)
{
    return LaptopScene::create(laptopInteractionNum);
}

Scene* LaptopScene::create(int laptopInteractionNum)
{
    LaptopScene* scene = new (std::nothrow) LaptopScene();
    if (scene && scene->init(laptopInteractionNum))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        CC_SAFE_DELETE(scene);
        return nullptr;
    }
}

bool LaptopScene::init(int laptopInteractionNum)
{
    if (!Scene::init())
    {
        return false;
    }
    _primaryInteractNum = laptopInteractionNum;
    _secondaryInteractNum = 0;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    _background = ui::ImageView::create();
    _background->setTouchEnabled(true);
    updateImage();
    _background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _background->setScaleX(visibleSize.width / _background->getContentSize().width);
    _background->setScaleY(visibleSize.height / _background->getContentSize().height);
    _background->addClickEventListener(CC_CALLBACK_1(LaptopScene::subInteraction, this));

    this->addChild(_background, 0);

    return true;
}

void LaptopScene::updateImage()
{
    std::stringstream bgFileSS;
    bgFileSS << BACKGROUND_PATH_PREFIX << (_primaryInteractNum + 1) << 
        "_" << _secondaryInteractNum << ".png";
    _background->loadTexture(bgFileSS.str());
}

void LaptopScene::backToGameScene()
{
    auto director = Director::getInstance();
    auto gameScene = director->popScene();
    auto transScene = TransitionFade::create(0.5, gameScene, Color3B(0, 0, 0));
    director->replaceScene(transScene);
}

void LaptopScene::subInteraction(Ref* pSender)
{
    log("secondayInteraction %d", _secondaryInteractNum);
    if (_secondaryInteractNum < SUB_INTERACTIONS[_primaryInteractNum])
    {
        _secondaryInteractNum++;
        updateImage();
    }
    // Game ends on last laptop interaction
    else if (_primaryInteractNum == LAST_PRIMARY_INTERACT_NUM)
    {
        auto director = Director::getInstance();
        director->end();
    }
    else
    {
        backToGameScene();
    }
}
