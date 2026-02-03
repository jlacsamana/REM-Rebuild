#include "Dialogue.h"

#include "ui/UIText.h"
#include "ui/UILayout.h"

Dialogue::Dialogue()
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

    float margin = 20.0f;
    float padding = 200.0f;
    auto background = Sprite::create("UI/dialog_bubble_regular.png");
    background->setAnchorPoint(Vec2(0.5, 0));
    background->setPosition(Vec2(visibleSize.width/2, margin));

    auto label = Label::createWithTTF(textContent, "fonts/Tox Typewriter.ttf", 25.0f);
    label->setWidth(background->getContentSize().width - 2 * padding);
    label->enableWrap(true);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(Vec2(padding, background->getContentSize().height/2));
    background->addChild(label, 1);


    addProtectedChild(background);

    return true;
}
