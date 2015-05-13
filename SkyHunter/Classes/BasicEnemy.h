#ifndef __BASICENEMY_H__
#define __BASICENEMY_H__

#include "cocos2d.h"

class Bullet;

class Player;

class BasicEnemy : public cocos2d::Sprite
{


public:
	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};

	virtual void setParent(Node* parent);

	void setTarget(Player* target);


	void setCurrentAnimation(Animations anim);
	Animations getCurrentAnimation(){ return  _currentAnimation; }


	CC_SYNTHESIZE(float, _speed, Speed);
	CREATE_FUNC(BasicEnemy);
	virtual bool init();
	virtual ~BasicEnemy();
	BasicEnemy();
	void update(float dt);
	virtual void setVisible(bool bVisible);


private:
	int SHOOT_TAG = 3;
	bool _initialiced;
	cocos2d::Vector<Bullet*> _bulletPool;
	int _numBullets;
	int _bulletIndex;
	void shoot();
	void scheduleShoot();

	Player* _target;

	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _explosionAnimation;
	cocos2d::Action* _shoot;

	Animations _currentAnimation;

	void createIdleAnimation();
	void createExplosionAnimation();

};

#endif //__BASICENEMY_H__

