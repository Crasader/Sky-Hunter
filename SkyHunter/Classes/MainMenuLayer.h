#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__

#include "cocos2d.h"
#include "BackGround3Parts.h"

class MainMenuLayer :public cocos2d::Layer
{
private:
	void startButtonAction();
	BackGround3Parts* _bg;
public:
	MainMenuLayer();
	~MainMenuLayer();
	void update(float dt);
	virtual bool init();
	static cocos2d::Scene* createScene();
	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuLayer);
};

#endif //__MAINMENULAYER_H__

