#include "Components/Dialogue.h"
#include "Components/HoverableButton.h"
#include "GameScene.h"
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
    log("laptop clicked");
}

void GameScene::bookClickCallback(Ref* pSender)
{
    log("book clicked");
}

void GameScene::canClickCallback(Ref* pSender)
{
    log("can clicked");

    double currentSanity = this->_gameState.GetProperty("sanity");
    this->_gameState.SetProperty("sanity", currentSanity - 10);
    log("new sanity %f", this->_gameState.GetProperty("sanity"));

    // run game event checker here
    this->_gameState.ExecuteEventEvalLoop();
}

void GameScene::setButtonsEnabled(bool enabled)
{
    _laptopButton->setEnabled(enabled);
    _bookButton->setEnabled(enabled);
    _canButton->setEnabled(enabled);
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
    _gameState = GameState::GameState();

    auto testGameEvt = std::unique_ptr<BaseGameEvent>(new GameEvent<>(
        TestGameEventCallback,
        {EventCondition{"sanity", CondComparitor::LTEQ, 0}}));
    _gameState.RegisterEvent(testGameEvt);

    _gameState.RegisterEvent(
        std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
            CreateDialogueCallback,
            { EventCondition{"sanity", CondComparitor::LTEQ, 75} },
            this, 
            "75 sanity")));
    _gameState.RegisterEvent(
        std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
            CreateDialogueCallback,
            { EventCondition{"sanity", CondComparitor::LTEQ, 50} },
            this,
            "50 sanity")));
    _gameState.RegisterEvent(
        std::unique_ptr<BaseGameEvent>(new GameEvent<GameScene*, std::string>(
            CreateDialogueCallback,
            { EventCondition{"sanity", CondComparitor::LTEQ, 25} },
            this,
            "25 sanity")));

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

