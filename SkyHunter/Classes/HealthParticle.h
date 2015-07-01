#ifndef __HEALTHPARTICLE_H__
#define __HEALTHPARTICLE_H__

#include "cocos2d.h"
namespace Actors{
	class Player;
}
namespace Components{
	class HealthParticle : public cocos2d::Node
	{
	private:
		bool _initialized;
		cocos2d::ParticleSystemQuad* _particle;
	public:
		CC_SYNTHESIZE(float, _speed, Speed);
		CC_SYNTHESIZE(Actors:: Player*, _target, Target);
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
		CREATE_FUNC(HealthParticle);
		
	};
}

#endif //__HEALTHPARTICLE_H__

