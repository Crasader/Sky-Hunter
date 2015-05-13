#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"



class Background 
{

private:
	bool _initialiced;
	cocos2d::Size _screen;
	cocos2d::Sprite* _bgPart1;
	cocos2d::Sprite* _bgPart2;

public:
	virtual void setParent(cocos2d::Node* parent);
	void update(float dt);
	~Background();
	CC_SYNTHESIZE(float, _speed, Speed);
	Background();
};

#endif //__BACKGROUND_H__

