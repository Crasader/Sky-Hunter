#ifndef __MAINMENULAYER_H__
#define __MAINMENULAYER_H__

#include "BaseMenuLayer.h"
namespace Menus{

	/**
	@brief  Capa que representa el menu principal del juego
	*/
	class MainMenuLayer :public BaseMenuLayer
	{
	private:

		/**
		@brief  metodo encargado de lanzar el menu de seleccion de nivel
		*/
		void selectMenuButton();

		/**
		@brief  metodo encargado de lanzar el menu de opciones
		*/
		void optionsButton();

		/**
		@brief  metodo encargado de lanzar el nivel 1 del juego
		*/
		void actionButton1();

		/**
		@brief  metodo encargado de lanzar el nivel 2 del juego
		*/
		void actionButton2();

		/**
		@brief  metodo encargado de lanzar el nivel 3 del juego
		*/
		void actionButton3();

		/**
		@brief  metodo encargado de lanzar el nivel 4 del juego
		*/
		void actionButton4();

		/**
		@brief  metodo encargado de lanzar el nivel 5 del juego
		*/
		void actionButton5();

		/**
		@brief  metodo encargado de lanzar el nivel 6 del juego
		*/
		void actionButton6();

		/**
		@brief  metodo encargado de lanzar el nivel 7 del juego
		*/
		void actionButton7();

		/**
		@brief  metodo encargado de lanzar el nivel 8 del juego
		*/
		void actionButton8();

		/**
		@brief  metodo encargado de lanzar el nivel 9 del juego
		*/
		void actionButton9();

	protected:

		/**
		@brief  metodo encargado de inicializar un vector con punteros a las funciones encargadas de lanzar los niveles
		@param  la referencia al vector que queremos inicializar
		*/
		void initFunctions(std::vector<std::function<void(Ref*)>>& functions);

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
		CREATE_FUNC(MainMenuLayer);
	};
}

#endif //__MAINMENULAYER_H__

