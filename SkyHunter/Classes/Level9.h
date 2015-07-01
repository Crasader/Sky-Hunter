#ifndef __LEVEL9_SCENE_H__
#define __LEVEL9_SCENE_H__

#include "Level3.h"


namespace Levels{
	/**
	@brief  nivel 9 de nuestro juego
	*/
	class Level9 : public Level3
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
		CREATE_FUNC(Level9);
	};
}

#endif // __LEVEL1_SCENE_H__