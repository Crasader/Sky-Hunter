#ifndef __ENEMYBULLET_H__
#define __ENEMYBULLET_H__

#include "cocos2d.h"

class Player;

class EnemyBullet : public cocos2d::Sprite
{
public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(Player*, _enemyTarget, EnemyTarget);
	CREATE_FUNC(EnemyBullet);
	virtual void update(float dt);
	virtual bool init();
};

#endif //__ENEMYBULLET_H__

