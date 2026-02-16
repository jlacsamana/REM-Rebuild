#include "HoverableButton.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

HoverableButton::HoverableButton()
{
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

    loadTextureNormal(idleImgPath);
    addTouchEventListener(callback);

    auto mouseEventListener = EventListenerMouse::create();
    mouseEventListener->onMouseMove = CC_CALLBACK_1(HoverableButton::mouseMoveCallback, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEventListener, this);

    return true;
}

void HoverableButton::mouseMoveCallback(EventMouse* event)
{
    Point mousePosition = Point(event->getCursorX(), event->getCursorY());
    auto camera = Camera::getVisitingCamera();
    bool isHovered = hitTest(mousePosition, camera, nullptr);

    std::string& curImgPath = getNormalFile().file;
    if (isHovered && curImgPath != _hoverImgPath)
    {
        loadTextureNormal(_hoverImgPath);
    }
    else if (!isHovered && curImgPath != _idleImgPath)
    {
        loadTextureNormal(_idleImgPath);
    }
}