#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__

#include "cocos2d.h"
namespace Components{
	class Blizzard : public cocos2d::Node
	{
	private:
		cocos2d::Size _visibleSize;
		bool _initialized;
		cocos2d::Vector<cocos2d::ParticleSystemQuad* > _snow;
		int _snowIndex;
		int _maxSnowParticles;
		/**
		@brief  crea la accion que llama a positioningParticle cada cierto tiempo
		*/
		void scheduleBlizzard();
		/**
		@brief  Activa las particulas que hacen las veces de nieve
		*/
		void positioningParticle();
	public:
		CC_SYNTHESIZE(float, _speed, Speed);
		/**
		@brief metodo que se ejecuta en cada frame del juego y que movera a una cierta velocidad el fondo de pantalla
		@param dt tiempo transcurrido desde la ultima ejecucion
		*/
		void update(float dt);
		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(Blizzard);
	};
}

#endif //__BLIZZARD_H__