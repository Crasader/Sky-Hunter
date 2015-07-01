
#ifndef __PLAYERBULLETx2_H__
#define __PLAYERBULLETx2_H__

#include "PlayerBullet.h"

namespace Actors{
	class PlayerBulletx2 :public PlayerBullet
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
		CREATE_FUNC(PlayerBulletx2);

	};
}
#endif //__PLAYERBULLETx2_H__
