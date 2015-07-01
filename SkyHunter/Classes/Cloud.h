#ifndef __CLOUD_H__
#define __CLOUD_H__

#include "cocos2d.h"
#include "Player.h"
namespace Components{
	class Cloud : public cocos2d::Sprite
	{

	public:
		CC_SYNTHESIZE(Actors::Player*, _target, Target);
		CC_SYNTHESIZE(int, _speed, Speed);
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
		CREATE_FUNC(Cloud);
	};
}
#endif //__CLOUD_H__
