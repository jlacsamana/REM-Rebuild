#include "TitleScene.h"

#include "ui/UIButton.h"
#include "ui/UIVBox.h"
#include "ui/UIImageView.h"
#include "ui/UILayoutParameter.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TitleSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    _btnLayout = ui::VBox::create();
    this->addChild(_btnLayout, 1);

    auto buttonLP = ui::LinearLayoutParameter::create();
    auto buttonMargin = ui::Margin(0.f, 0.f, 0.f, 10.f);
    buttonLP->setMargin(buttonMargin);

    _startButton = ui::Button::create(START_BUTTON_FILE_NAME);
    _startButton->addTouchEventListener(CC_CALLBACK_1(TitleScene::menuStartCallback, this));
    _startButton->setLayoutParameter(buttonLP);
    _btnLayout->addChild(_startButton);

    _quitButton = ui::Button::create(QUIT_BUTTON_FILE_NAME);
    _quitButton->addTouchEventListener(CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
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

    auto mouseEventListener = EventListenerMouse::create();
    mouseEventListener->onMouseMove = CC_CALLBACK_1(TitleScene::mouseMoveCallback, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEventListener, this);
    
    return true;
}

void TitleScene::mouseMoveCallback(EventMouse* event) {
    Point mousePosition = Point(event->getCursorX() - _btnLayout->getPositionX(),
        event->getCursorY()-_btnLayout->getPositionY());

    std::string& startButtonFile = _startButton->getNormalFile().file;
    bool hoveredStart = _startButton->getBoundingBox().containsPoint(mousePosition);
    if (hoveredStart && startButtonFile != HOVER_START_BUTTON_FILE_NAME)
    {
        _startButton->loadTextureNormal(HOVER_START_BUTTON_FILE_NAME);
    }
    else if (!hoveredStart && startButtonFile != START_BUTTON_FILE_NAME)
    {
        _startButton->loadTextureNormal(START_BUTTON_FILE_NAME);
    }

    std::string& quitButtonFile = _quitButton->getNormalFile().file;
    bool hoveredQuit = _quitButton->getBoundingBox().containsPoint(mousePosition);
    if (hoveredQuit && quitButtonFile != HOVER_QUIT_BUTTON_FILE_NAME)
    {
        _quitButton->loadTextureNormal(HOVER_QUIT_BUTTON_FILE_NAME);
    }
    else if (!hoveredQuit && quitButtonFile != QUIT_BUTTON_FILE_NAME)
    {
        _quitButton->loadTextureNormal(QUIT_BUTTON_FILE_NAME);
    }
}

void TitleScene::menuStartCallback(cocos2d::Ref* pSender)
{
    // go next scene!
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}