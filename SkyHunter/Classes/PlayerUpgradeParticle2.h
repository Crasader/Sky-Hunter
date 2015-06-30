

#ifndef __PLAYERUPGRADEPARTICLE2_H__
#define __PLAYERUPGRADEPARTICLE2_H__


#include "PlayerUpgradeParticle.h"
#include "PlayerBulletx3.h"

namespace Components{
	class PlayerUpgradeParticle2 : public PlayerUpgradeParticle
	{
	protected:
		virtual Actors::PlayerBullet* createBullet();

	public:
		virtual bool init();
		CREATE_FUNC(PlayerUpgradeParticle2);
	};
}

#endif //__PLAYERUPGRADEPARTICLE2_H__

