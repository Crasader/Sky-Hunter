#ifndef __ENEMYBULLET_H__
#define __ENEMYBULLET_H__

#include "cocos2d.h"

	

namespace Actors{
	class Player;
	/**
	@brief  bala de los enemigos
	*/
	class EnemyBullet : public cocos2d::Sprite
	{
	public:
		CC_SYNTHESIZE(float, _speed, Speed);
		CC_SYNTHESIZE(Player*, _enemyTarget, EnemyTarget);

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
		CREATE_FUNC(EnemyBullet);
	};
}
#endif //__ENEMYBULLET_H__

