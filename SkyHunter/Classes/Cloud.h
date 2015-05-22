#ifndef __CLOUD_H__
#define __CLOUD_H__

#include "cocos2d.h"
#include "Player.h"
class Cloud : public cocos2d::Sprite
{

public:
	CC_SYNTHESIZE(Player*, _target, Target);
	CC_SYNTHESIZE(int, _speed, Speed);
	virtual void update(float dt);
	virtual bool init();
	CREATE_FUNC(Cloud);
};
#endif //__CLOUD_H__
