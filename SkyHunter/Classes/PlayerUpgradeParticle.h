
#ifndef __PLAYERUPGRADEPARTICLE_H__
#define __PLAYERUPGRADEPARTICLE_H__

#include "cocos2d.h"
#include "Player.h"
#include "PlayerBulletx2.h"
namespace Components{
	class PlayerUpgradeParticle : public cocos2d::Node
	{
	protected:
		bool _initialized;
		cocos2d::ParticleSystemQuad* _particle;
		virtual Actors::PlayerBullet* createBullet();


	public:
		CC_SYNTHESIZE(float, _speed, Speed);
		CC_SYNTHESIZE(Actors::Player*, _target, Target);
		virtual void update(float dt);
		virtual void setVisible(bool visible);
		virtual bool init();
		CREATE_FUNC(PlayerUpgradeParticle);
	};
}
#endif //__PLAYERUPGRADEPARTICLE_H__