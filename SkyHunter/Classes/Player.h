#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
private:
	Player();
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
	CREATE_FUNC(Player);
	virtual bool init();
	virtual ~Player();
	void update(float dt);
};

#endif //__PLAYER_H__

