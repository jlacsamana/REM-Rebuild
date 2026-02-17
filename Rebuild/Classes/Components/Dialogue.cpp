#include "Dialogue.h"

#include "ui/UIText.h"
#include "ui/UILayout.h"

Dialogue::Dialogue():
    _isActive(true)
{
}

Dialogue::~Dialogue()
{
}

Dialogue* Dialogue::create(const std::string& textContent)
{
    Dialogue* dlg = new (std::nothrow) Dialogue;
    if (dlg && dlg->init(textContent))
    {
        dlg->autorelease();
        return dlg;
    }
    CC_SAFE_DELETE(dlg);
    return nullptr;
}

bool Dialogue::init(const std::string& textContent)
{
    if (!Widget::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto background = Sprite::create(BG_PATH);
    background->setAnchorPoint(Vec2(0.5, 0));
    background->setPosition(Vec2(visibleSize.width/2, MARGIN));

    auto mouseEventListener = EventListenerMouse::create();
    mouseEventListener->onMouseDown = CC_CALLBACK_1(Dialogue::deactivate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEventListener, this);

    auto label = Label::createWithTTF(textContent, FONT_PATH, FONT_SIZE);
    label->setWidth(background->getContentSize().width - 2 * PADDING);
    label->enableWrap(true);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(Vec2(PADDING, background->getContentSize().height/2));
    background->addChild(label, 1);

    addProtectedChild(background);

    return true;
}

bool Dialogue::isActive()
{
    return _isActive;
}

void Dialogue::deactivate(EventMouse* event)
{
    _isActive = false;
}
