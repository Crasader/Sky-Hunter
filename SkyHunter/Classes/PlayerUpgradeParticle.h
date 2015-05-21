
#ifndef __PLAYERUPGRADEPARTICLE_H__
#define __PLAYERUPGRADEPARTICLE_H__

#include "cocos2d.h"
#include "Player.h"
#include "PlayerBulletx2.h"

class PlayerUpgradeParticle : public cocos2d::Node
{
private:
	bool _initialized;
	cocos2d::ParticleSystemQuad* _particle;
protected:
	virtual PlayerBulletx2* createBullet();

public:
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(Player*, _target, Target);
	virtual void update(float dt);
	virtual void setVisible(bool visible);
	virtual bool init();
	CREATE_FUNC(PlayerUpgradeParticle);
};

#endif //__PLAYERUPGRADEPARTICLE_H__