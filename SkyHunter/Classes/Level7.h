#ifndef __LEVEL7_SCENE_H__
#define __LEVEL7_SCENE_H__

#include "Level1.h"


namespace Levels{
	/**
	@brief  nivel 7 de nuestro juego
	*/
	class Level7 : public Level1
	{

	protected:
		/**
		@brief  inicializa variables globales del nievel como el player o el fondo de pantalla
		*/
		virtual void initializeVariables();

	public:
		/**
		@brief  Metodo sobrecargado de Layer que se ejecuta al llamar al metodo
		create estatico para inicializar la capa
		@return true    Inicializacion correcta
		@return false   Inicializacion fallida
		*/
		virtual bool init();

		/**
		@brief  crea una escena a partir de esta capa.
		*/
		static cocos2d::Scene* createScene();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(Level7);
	};
}

#endif // __LEVEL7_SCENE_H__