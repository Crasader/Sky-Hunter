#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "TouchController.h"

class Bullet;

class BasicEnemy;


class Player : public cocos2d::Sprite
{


public:

	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};

	virtual void setParent(Node* parent);
	void setTargets(cocos2d::Vector<BasicEnemy*>& targets);
	void setCurrentAnimation(Animations anim);
	Animations getCurrentAnimation(){ return  _currentAnimation; }

	virtual void setVisible(bool bVisible);
	CC_SYNTHESIZE(float, _speed, Speed);
	CREATE_FUNC(Player);
	virtual bool init();
	virtual ~Player();
	Player();
	void update(float dt);

private:
	int SHOOT_TAG = 3;
	bool _initialiced;
	cocos2d::Vector<Bullet*> _bulletPool;
	cocos2d::Vector<BasicEnemy*>  _targets;
	int _numBullets;
	int _bulletIndex;
	void shoot();
	void scheduleShoot();

	
	TouchController* _controller;
	Animations _currentAnimation;
	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _explosionAnimation;
	cocos2d::Action* _shoot;

	void createIdleAnimation();
	void createExplosionAnimation();
};

#endif //__PLAYER_H__

