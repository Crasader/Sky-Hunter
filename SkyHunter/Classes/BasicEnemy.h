#ifndef __BASICENEMY_H__
#define __BASICENEMY_H__

#include "cocos2d.h"

class BasicEnemy : public cocos2d::Sprite
{
private:
	BasicEnemy();
	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _explosionAnimation;

	void createIdleAnimation();
	void createExplosionAnimation();

public:
	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};

	CC_SYNTHESIZE(Animations, _currentAnimation, CurrentAnimation);
	CC_SYNTHESIZE(float, _speed, Speed);
	CREATE_FUNC(BasicEnemy);
	virtual bool init();
	virtual ~BasicEnemy();
	void update(float dt);
};

#endif //__BASICENEMY_H__

