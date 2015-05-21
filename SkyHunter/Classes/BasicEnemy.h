#ifndef __BASICENEMY_H__
#define __BASICENEMY_H__
#define ENEMY_HEALTH 1

#include "cocos2d.h"
#include "EnemyBullet.h"

class Player;

class BasicEnemy : public cocos2d::Sprite
{

public:
	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};

private:
	int SHOOT_TAG = 3;
	bool _initialiced;
	int _bulletIndex;
	void shoot();
	void createBullets();
	

	

protected:
	float _shootFrequencySeconds;
	int _numBullets;
	void scheduleShoot();
	Animations _currentAnimation;
	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _explosionAnimation;
	cocos2d::Action* _shoot;
	cocos2d::Vector<EnemyBullet*> _bulletPool;
	Player* _target;
	virtual void createIdleAnimation();
	virtual void createExplosionAnimation();
	virtual void behaviour(float dt);


public:
	void reset();
	virtual void setParent(Node* parent);
	void setTarget(Player* target);


	void setCurrentAnimation(Animations anim);
	Animations getCurrentAnimation(){ return  _currentAnimation; }
	CC_SYNTHESIZE(int, _health, Health);
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(int, _value, Value);
	CREATE_FUNC(BasicEnemy);
	virtual bool init();
	BasicEnemy();
	virtual void update(float dt);
	virtual void pause();
	virtual void resume();
	virtual void setVisible(bool visible);
};

#endif //__BASICENEMY_H__

