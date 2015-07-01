

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
		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(PlayerUpgradeParticle2);
	};
}

#endif //__PLAYERUPGRADEPARTICLE2_H__

