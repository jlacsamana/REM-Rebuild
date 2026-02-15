#include "TitleScene.h"
#include "GameScene.h"
#include "Components/HoverableButton.h"
#include "ui/UIVBox.h"
#include "ui/UIImageView.h"
#include "ui/UILayoutParameter.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

USING_NS_CC;

Scene *TitleScene::createScene()
{
    return TitleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TitleSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    _btnLayout = ui::VBox::create();
    this->addChild(_btnLayout, 1);

    auto buttonLP = ui::LinearLayoutParameter::create();
    auto buttonMargin = ui::Margin(0.f, 0.f, 0.f, 10.f);
    buttonLP->setMargin(buttonMargin);

    _startButton = HoverableButton::create(
        START_BUTTON_FILE_NAME,
        HOVER_START_BUTTON_FILE_NAME,
        CC_CALLBACK_1(TitleScene::menuStartCallback, this));
    _startButton->setLayoutParameter(buttonLP);
    _btnLayout->addChild(_startButton);

    _quitButton = HoverableButton::create(
        QUIT_BUTTON_FILE_NAME,
        HOVER_QUIT_BUTTON_FILE_NAME,
        CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
    _quitButton->setLayoutParameter(buttonLP);
    _btnLayout->addChild(_quitButton);

    float layoutWidth = std::max(_startButton->getContentSize().width, _quitButton->getContentSize().width);
    float layoutHeight = _startButton->getContentSize().height + _quitButton->getContentSize().height + buttonMargin.bottom;
    float yOffsetRatio = 0.3f;

    _btnLayout->setPosition(Vec2(
        visibleSize.width / 2 - layoutWidth / 2,
        visibleSize.height * yOffsetRatio + layoutHeight / 2));

    auto background = ui::ImageView::create("final/title.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    this->addChild(background, 0);

    return true;
}

void TitleScene::menuStartCallback(cocos2d::Ref *pSender)
{
    auto newGame = GameScene::createScene();
    Director::getInstance()->replaceScene(newGame);
}

void TitleScene::menuCloseCallback(Ref *pSender)
{
    Director::getInstance()->end();
}