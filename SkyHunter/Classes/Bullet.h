#ifndef __BULLET_H__
#define __BULLET_H__


#include "cocos2d.h"

class Player;
class BasicEnemy;


class Bullet :public cocos2d::Sprite
{
private:
	enum Type { ENEMY_BULLET = 0, PLAYER_BULLET = 1 };
	cocos2d::Vector<BasicEnemy*>  _playerTargets;
	CC_SYNTHESIZE(Type, _type, Type);

public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(Player*, _enemyTarget, EnemyTarget);

	void setPlayerTargets(const cocos2d::Vector<BasicEnemy*>& targets){ _playerTargets = targets; };
	virtual void update(float dt);


	static Bullet* createEnemyBullet();
	static Bullet *createPlayerBullet();

	virtual bool init();
};

#endif //__BULLET_H__

