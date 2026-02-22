#include "Components/Dialogue.h"
#include "Components/HoverableButton.h"
#include "GameScene.h"
#include "LaptopScene.h"
#include "Models/GameEvent.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UILayoutParameter.h"
#include "ui/UIVBox.h"

#include "editor-support/cocostudio/CocosStudioExtension.h"

USING_NS_CC;

// Game event Callbacks
static void TestGameEventCallback()
{
    log("Sanity is at zero now");
    Director::getInstance()->end();
}

static void CreateDialogueCallback(GameScene* scene, std::string text)
{
    scene->createDialogue(text);
}

GameScene::GameScene() :
    _activeDialogue(nullptr),
    _laptopButton(false),
    _bookButton(nullptr),
    _canButton(nullptr)
{
}

GameScene::~GameScene()
{
}

void GameScene::laptopClickCallback(Ref* pSender)
{
    double laptopInteractions = _gameState.getProperty(GameState::KEY_LAPTOP_INTERACTIONS);
    log("laptop clicked %f", laptopInteractions);

    if (laptopInteractions < 4)
    {
        _gameState.incrementProperty(GameState::KEY_LAPTOP_INTERACTIONS, 1);
        auto laptopScene = LaptopScene::createScene(laptopInteractions);
        auto transScene = TransitionFade::create(0.5, laptopScene, Color3B(0, 0, 0));
        Director::getInstance()->pushScene(transScene);
    }
}

void GameScene::bookClickCallback(Ref* pSender)
{
    log("book clicked");
}

void GameScene::canClickCallback(Ref* pSender)
{
    double canInteractions = _gameState.getProperty(GameState::KEY_CAN_INTERACTIONS);
    log("can clicked %f", canInteractions);

    if (canInteractions < 3)
    {
        _gameState.incrementProperty(GameState::KEY_SANITY, -10);
    }
    else
    {
        _gameState.registerEvent(
            std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
                CreateDialogueCallback,
                { EventCondition{"can_interactions", CondComparitor::GTEQ, 4} },
                this,
                "None left...")));
    }
    _gameState.incrementProperty(GameState::KEY_CAN_INTERACTIONS, 1);

    // run game event checker here
    _gameState.executeEventEvalLoop();
}

void GameScene::setButtonsEnabled(bool enabled)
{
    _laptopButton->setEnabled(enabled);
    _bookButton->setEnabled(enabled);
    _canButton->setEnabled(enabled);
}

void GameScene::initGameEvents()
{
    _gameState.registerEvent(
        std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
            CreateDialogueCallback,
            { EventCondition{"can_interactions", CondComparitor::EQ, 1} },
            this,
            "I feel a bit more awake")));

    _gameState.registerEvent(
        std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
            CreateDialogueCallback,
            { EventCondition{"can_interactions", CondComparitor::EQ, 2} },
            this,
            "This is helping... just a little. But I'm a bit shaky.")));

    _gameState.registerEvent(
        std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
            CreateDialogueCallback,
            { EventCondition{"can_interactions", CondComparitor::EQ, 3} },
            this,
            "That was my last sip.")));
}

//
Scene *GameScene::createScene()
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
    _gameState = GameState();
    initGameEvents();

    auto testGameEvt = std::unique_ptr<BaseGameEvent>(new GameEvent<>(
        TestGameEventCallback,
        {EventCondition{"sanity", CondComparitor::LTEQ, 0}}));
    _gameState.registerEvent(testGameEvt);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto screenCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    auto background = ui::ImageView::create("final/final_bg.png");
    background->setPosition(screenCenter);
    this->addChild(background, 0);

    // Setting up main action buttons
    _laptopButton = HoverableButton::create(
        LAPTOP_BUTTON_FILE_NAME,
        HOVER_LAPTOP_BUTTON_FILE_NAME,
        CC_CALLBACK_1(GameScene::laptopClickCallback, this));
    _bookButton = HoverableButton::create(
        BOOK_BUTTON_FILE_NAME,
        HOVER_BOOK_BUTTON_FILE_NAME,
        CC_CALLBACK_1(GameScene::bookClickCallback, this));
    _canButton = HoverableButton::create(
        CAN_BUTTON_FILE_NAME,
        HOVER_CAN_BUTTON_FILE_NAME,
        CC_CALLBACK_1(GameScene::canClickCallback, this));
    _laptopButton->setPosition(Vec2(screenCenter.x - 525, screenCenter.y - 100));
    _bookButton->setPosition(Vec2(screenCenter.x + 125, screenCenter.y - 230));
    _canButton->setPosition(Vec2(screenCenter.x + 650, screenCenter.y - 100));
    addChild(_laptopButton, 1);
    addChild(_bookButton, 1);
    addChild(_canButton, 1);

    this->scheduleUpdate();
    return true;
}

void GameScene::createDialogue(const std::string text)
{
    _activeDialogue = Dialogue::create(text);
    this->addChild(_activeDialogue, 1);
    setButtonsEnabled(false);
}

void GameScene::update(float dt)
{
    // Remove dialogue after it has been dismissed
    if (_activeDialogue && !_activeDialogue->isActive())
    {
        _activeDialogue->removeFromParent();
        _activeDialogue = nullptr;
        setButtonsEnabled(true);
    }
}

