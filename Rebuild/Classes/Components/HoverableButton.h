#ifndef __HOVERABLE_BUTTON_H__
#define __HOVERABLE_BUTTON_H__

#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ui/UIButton.h"

USING_NS_CC;

class HoverableButton : public ui::Widget
{
public:
	HoverableButton();
	~HoverableButton();

	static HoverableButton *create(
		const std::string &idleImgPath,
		const std::string &hoverImgPath,
		const ccWidgetTouchCallback &callback);

	bool init(
		const std::string &idleImgPath,
		const std::string &hoverImgPath,
		const ccWidgetTouchCallback &callback);

	void mouseMoveCallback(EventMouse* event);

private:
	ui::Button* _button;

	std::string _idleImgPath;
	std::string _hoverImgPath;
};

#endif // __HOVERABLE_BUTTON_H__
