
#ifndef __SELECTMENULAYER_H__
#define __SELECTMENULAYER_H__

#define NUM_LEVELS 9

#include "BaseMenuLayer.h"
#include "ui/CocosGUI.h"


class SelectMenuLayer : public BaseMenuLayer
{
private:
	
	std::ostringstream _ostr;
	void actionButton1();
	void actionButton2();
	void actionButton3();
	void actionButton4();
	void actionButton5();
	void actionButton6();
	void actionButton7();
	void actionButton8();
	void actionButton9();
	void actionButtonBack();

	void initfunctions(std::vector<std::function<void(Ref*)>>& functions);
	void initButtons(cocos2d::Vector<cocos2d::ui::Button*>& vector, std::vector<std::function<void(Ref*)>>& functions);


public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	// implement the "static create()" method manually
	CREATE_FUNC(SelectMenuLayer);
};

#endif //__MAINMENULAYER_H__