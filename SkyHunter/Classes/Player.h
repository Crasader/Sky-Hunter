#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "cocos2d.h"
#include "TouchController.h"
#include "PlayerBullet.h"

#define MAX_HEALTH 3

class BasicEnemy;


class Player : public cocos2d::Sprite
{
public:
	enum Animations
	{
		IDLE = 0, EXPLOSION = 1
	};

private:
	Node* _parent;
	cocos2d::ParticleSystemQuad* _hitEffect;
	int _health;
	int SHOOT_TAG = 3;
	bool _initialiced;
	cocos2d::Vector<PlayerBullet*> _bulletPool;
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
	void updateBullets(const std::function<PlayerBullet*()>& create);
	void reset();
	virtual void setParent(Node* parent);
	void setTargets(const cocos2d::Vector<BasicEnemy*>& targets);
	void setCurrentAnimation(Animations anim);
	const Animations getCurrentAnimation(){ return  _currentAnimation; }

	virtual void setVisible(bool visible);
	virtual void pause();
	virtual void resume();
	virtual bool init();
	virtual void update(float dt);

	const int getHealth(){ return _health; };
	void setHealth(int health);

	
	Player();
	
	void runHitEffect();


};

#endif //__PLAYER_H__

