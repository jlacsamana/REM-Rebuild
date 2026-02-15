#include "HoverableButton.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

HoverableButton::HoverableButton()
{
    _button = nullptr;
}

HoverableButton::~HoverableButton()
{
}

HoverableButton *HoverableButton::create(
    const std::string &idleImgPath,
    const std::string &hoverImgPath,
    const ccWidgetTouchCallback &callback)
{
    HoverableButton *dlg = new (std::nothrow) HoverableButton;
    if (dlg && dlg->init(idleImgPath, hoverImgPath, callback))
    {
        dlg->autorelease();
        return dlg;
    }
    CC_SAFE_DELETE(dlg);
    return nullptr;
}

bool HoverableButton::init(
    const std::string &idleImgPath,
    const std::string &hoverImgPath,
    const ccWidgetTouchCallback& callback)
{
    if (!Widget::init())
    {
        return false;
    }

    _idleImgPath = idleImgPath;
    _hoverImgPath = hoverImgPath;

    _button = ui::Button::create(idleImgPath);
    _button->setAnchorPoint(Vec2(0.0f, 0.0f));
    _button->addTouchEventListener(callback);

    setContentSize(_button->getContentSize());
    addProtectedChild(_button);

    auto mouseEventListener = EventListenerMouse::create();
    mouseEventListener->onMouseMove = CC_CALLBACK_1(HoverableButton::mouseMoveCallback, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEventListener, this);

    return true;
}

void HoverableButton::mouseMoveCallback(EventMouse* event)
{
    Point mousePosition = Point(event->getCursorX(), event->getCursorY());
    Rect globalBox = RectApplyAffineTransform(
        _button->getBoundingBox(), _button->getNodeToWorldAffineTransform());
    bool isHovered = globalBox.containsPoint(mousePosition);

    std::string& curImgPath = _button->getNormalFile().file;
    if (isHovered && curImgPath != _hoverImgPath)
    {
        _button->loadTextureNormal(_hoverImgPath);
    }
    else if (!isHovered && curImgPath != _idleImgPath)
    {
        _button->loadTextureNormal(_idleImgPath);
    }
}