#ifndef __DIALOGUE_H__
#define __DIALOGUE_H__

#include "cocos2d.h"

#include "ui/UIWidget.h"
#include "ui/UIVBox.h"

USING_NS_CC;

class Dialogue : public ui::Widget
{
public: 
	Dialogue();
	~Dialogue();

	static Dialogue* create(const std::string & textContent);

	bool init(const std::string& textContent);

	void dismiss(EventMouse* event);

private:
	const float MARGIN = 20.0f;
	const float PADDING = 200.0f;
	const float FONT_SIZE = 25;

	const std::string BG_PATH = "UI/dialog_bubble_regular.png";
	const std::string FONT_PATH = "fonts/Tox Typewriter.ttf";
};

#endif // __DIALOGUE_H__
