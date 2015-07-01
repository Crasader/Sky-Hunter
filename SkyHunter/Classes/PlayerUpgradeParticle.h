
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
		/**
		@brief  Metodo para indicar si se debe renderizar el nodo o no
		@param visible si true se renderica, si false, no.
		*/
		virtual void setVisible(bool visible);
		/**
		@brief  Metodo llamado por el game loop de cocos en cada frame
		@param dt tiempo  transcurrido desde la ultima ejecucion
		*/
		virtual void update(float dt);

		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(PlayerUpgradeParticle);
	};
}
#endif //__PLAYERUPGRADEPARTICLE_H__