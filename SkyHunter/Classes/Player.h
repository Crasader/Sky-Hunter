#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "TouchController.h"
#include "Bullet.h"

class Player : public cocos2d::Sprite
{
private:
	bool _initialiced;
	cocos2d::Vector<Bullet*> _bulletPool;
	int _numBullets;
	int _bulletIndex;
	void shoot();
	void scheduleShoot();

	Player();
	cocos2d::Vector<Sprite *> _bullets;
	TouchController* _controller;
	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _explosionAnimation;

	void createIdleAnimation();
	void createExplosionAnimation();

public:
	
	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};
	virtual void setParent(Node* parent);
	CC_SYNTHESIZE(Animations, _currentAnimation, CurrentAnimation);
	CC_SYNTHESIZE(float, _speed, Speed);
	CREATE_FUNC(Player);
	virtual bool init();
	virtual ~Player();
	void update(float dt);
};

#endif //__PLAYER_H__

