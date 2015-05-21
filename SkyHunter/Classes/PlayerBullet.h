#ifndef __PLAYERBULLET_H__
#define __PLAYERBULLET_H__
#include "cocos2d.h"

#include "BasicEnemy.h"

class PlayerBullet :public cocos2d::Sprite
{
private:
	cocos2d::Vector<BasicEnemy*>  _playerTargets;
protected:
	int _damage;
public:
	CC_SYNTHESIZE(float, _speed, Speed);
	void setPlayerTargets(const cocos2d::Vector<BasicEnemy*>& targets){ _playerTargets = targets; };
	virtual void update(float dt);
	virtual void playShootSound();
	CREATE_FUNC(PlayerBullet);
	virtual bool init();

};
#endif //__PLAYERBULLET_H__
