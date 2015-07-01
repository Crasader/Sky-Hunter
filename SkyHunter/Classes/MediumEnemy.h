#ifndef __MEDIUMENEMY_H__
#define __MEDIUMENEMY_H__

#include "BasicEnemy.h"

namespace Actors{
	class MediumEnemy : public BasicEnemy
	{

	public:
		MediumEnemy();
		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(MediumEnemy);
	};
}
#endif
