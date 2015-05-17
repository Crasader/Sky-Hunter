#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__

#include "BaseMenuLayer.h"

class MainMenuLayer :public BaseMenuLayer
{
private:
	void startButtonAction();
	void selectMenuButton();
	void optionsButton();
	void arcadeButton();
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuLayer);
};

#endif //__MAINMENULAYER_H__

