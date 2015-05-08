#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include "cocos2d.h"



 class Background : public cocos2d::Node
{

private:
	CC_SYNTHESIZE(float, _speed, Speed);
	cocos2d::Size _screen;
	cocos2d::Sprite* _bgPart1;
	cocos2d::Sprite* _bgPart2;
	Background();

public:
	void update(float dt);
	~Background();
	CREATE_FUNC(Background);
};

#endif //__BACKGROUND_H__

