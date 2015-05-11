#ifndef __BULLET_H__
#define __BULLET_H__


#include "cocos2d.h"


class Bullet :public cocos2d::Sprite
{
private:
	enum Type { ENEMY_BULLET = 0, PLAYER_BULLET = 1 };
	CC_SYNTHESIZE(Type, _type, Type);

public:
	CC_SYNTHESIZE(float, _speed, Speed);
	virtual void update(float dt);


	static Bullet* createEnemyBullet();
	static Bullet *createPlayerBullet();

	virtual bool initWithFile(const std::string& filename);
};

#endif //__BULLET_H__

