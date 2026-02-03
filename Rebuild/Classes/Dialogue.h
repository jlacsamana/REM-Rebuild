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
};

#endif // __DIALOGUE_H__
