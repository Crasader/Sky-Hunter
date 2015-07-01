

#ifndef __PLAYERBULLETx3_H__
#define __PLAYERBULLETx3_H__

#include "PlayerBullet.h"

namespace Actors{
	class PlayerBulletx3 :public PlayerBullet
	{
	public:
		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(PlayerBulletx3);

	};
}
#endif //__PLAYERBULLETx3_H__