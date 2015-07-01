#ifndef __ENEMYBULLETSMART_H__
#define __ENEMYBULLETSMART_H__

#include "EnemyBullet.h"
namespace Actors{
	/**
	@brief  bala inteligente usada por los enemigos
	*/
	class EnemyBulletSmart : public EnemyBullet
	{
	private:
		cocos2d::Point _targetPosition;

	public:

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
		/**
		@brief  Metodo para indicar si se debe renderizar el nodo o no
		@param visible si true se renderica, si false, no.
		*/
		virtual void setVisible(bool visible);

	};
}

#endif //__ENEMYBULLETSMART_H__