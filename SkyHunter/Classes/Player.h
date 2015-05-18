#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "cocos2d.h"
#include "TouchController.h"
#define MAX_HEALTH 3

class Bullet;
class BasicEnemy;

class Player : public cocos2d::Sprite
{
public:
	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};

private:
	cocos2d::ParticleSystemQuad* _hitEffect;
	int _health;
	int SHOOT_TAG = 3;
	bool _initialiced;
	cocos2d::Vector<Bullet*> _bulletPool;
	cocos2d::Vector<BasicEnemy*>  _targets;

	int _numBullets;
	int _bulletIndex;
	void shoot();
	


	TouchController* _controller;
	Animations _currentAnimation;

	cocos2d::Action* _idleAnimation;
	cocos2d::Action* _explosionAnimation;
	cocos2d::Action* _shoot;

	void createIdleAnimation();
	void createExplosionAnimation();
	void scheduleShoot();
public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CREATE_FUNC(Player);

	void reset();
	virtual void setParent(Node* parent);
	void setTargets(const cocos2d::Vector<BasicEnemy*>& targets);
	void setCurrentAnimation(Animations anim);
	const Animations getCurrentAnimation(){ return  _currentAnimation; }

	virtual void setVisible(bool bVisible);
	virtual void pause();
	virtual void resume();

	const int getHealth(){ return _health; };
	void setHealth(int health);



	virtual bool init();
	virtual ~Player();
	Player();
	void update(float dt);
	void runHitEffect();


};

#endif //__PLAYER_H__

