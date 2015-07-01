

#ifndef __HEIGHTENEMY_H__
#define __HEIGHTENEMY_H__

#include "BasicEnemy.h"

namespace Actors{
	class HeightEnemy : public BasicEnemy
	{
	protected:
		virtual void createBullets();
	public:
		HeightEnemy();
		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(HeightEnemy);



	};
}
#endif //__HEIGHTENEMY_H__