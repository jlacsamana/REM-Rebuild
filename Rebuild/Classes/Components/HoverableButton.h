#ifndef __HOVERABLE_BUTTON_H__
#define __HOVERABLE_BUTTON_H__

#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ui/UIButton.h"

USING_NS_CC;

class HoverableButton : public ui::Button
{
public:
	HoverableButton();
	~HoverableButton();

	static HoverableButton *create(
		const std::string &idleImgPath,
		const std::string &hoverImgPath,
		const ccWidgetClickCallback &callback);

	bool init(
		const std::string &idleImgPath,
		const std::string &hoverImgPath,
		const ccWidgetClickCallback &callback);

	void mouseMoveCallback(EventMouse* event);

	void setEnabled(bool enabled);

private:
	std::string _idleImgPath;
	std::string _hoverImgPath;
};

#endif // __HOVERABLE_BUTTON_H__
