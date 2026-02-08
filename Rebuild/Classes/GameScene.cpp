#include "GameScene.h"
#include "ui/UIButton.h"
#include "ui/UIVBox.h"
#include "ui/UIImageView.h"
#include "ui/UILayoutParameter.h"

#include "editor-support/cocostudio/CocosStudioExtension.h"
USING_NS_CC;

// Game event Callbacks
static void TestGameEventCallback() {
    log("Sanity is at zero now");
}

// Callbacks
void GameScene::TestCallback(cocos2d::Ref* pSender)
{
    double currentSanity = this->_gameState.GetProperty("sanity");
    this->_gameState.SetProperty("sanity", currentSanity - 10);
    log("new sanity %f", this->_gameState.GetProperty("sanity"));

    // run game event checker here
    this->_gameState.ExecuteEventEvalLoop();
}


//
Scene* GameScene::createScene()
{
    return GameScene::create();
}



bool GameScene::init()
{
    if (!Scene::init())

    {

        return false;

    }

    // create game state with initial values
    _gameState = GameState::GameState();

    
    auto testGameEvt = GameEvent(TestGameEventCallback, { EventCondition{"sanity", CondComparitor::LTEQ, 0} });
    _gameState.RegisterEvent(testGameEvt);

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto background = ui::ImageView::create("final/final_all_full.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    this->addChild(background, 0);


    _btnLayout = ui::VBox::create();
    this->addChild(_btnLayout, 1);

    auto buttonLP = ui::LinearLayoutParameter::create();
    auto buttonMargin = ui::Margin(0.f, 0.f, 0.f, 10.f);
    buttonLP->setMargin(buttonMargin);

    testBtn = ui::Button::create(START_BUTTON_FILE_NAME);
    testBtn->addClickEventListener(CC_CALLBACK_1(GameScene::TestCallback, this));
    testBtn->setLayoutParameter(buttonLP);
    _btnLayout->addChild(testBtn);

    float layoutWidth = std::max(testBtn->getContentSize().width, 0.0f);
    float layoutHeight = testBtn->getContentSize().height + buttonMargin.bottom;
    float yOffsetRatio = 0.3f;

    _btnLayout->setPosition(Vec2(
        visibleSize.width / 2 - layoutWidth / 2,
        visibleSize.height * yOffsetRatio + layoutHeight / 2));

    this->scheduleUpdate();
    return true;

}

void GameScene::update(float dt) {

}

