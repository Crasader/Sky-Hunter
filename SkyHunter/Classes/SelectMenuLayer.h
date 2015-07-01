
#ifndef __SELECTMENULAYER_H__
#define __SELECTMENULAYER_H__

#define NUM_LEVELS 9

#include "MainMenuLayer.h"
#include "ui/CocosGUI.h"

namespace Menus{
	/**
	@brief  Capa que representa el menu de seleccion de nivel
	*/
	class SelectMenuLayer : public MainMenuLayer
	{
	private:
		std::ostringstream _ostr;

		/**
		@brief  metodo que se ejecuta por el boton de volver atras y lanza el menu principal
		*/
		void actionButtonBack();

		/**
		@brief  metodo que carga los botones en la escena asignandoles segun su numero, el nivel que deben lanzar.
		@param  vector: el vector de botones que desamos inicializar
		@param  functions: el vector que contiene las funciones a asignar a los botones.
		*/
		void initButtons(cocos2d::Vector<cocos2d::ui::Button*>& vector, std::vector<std::function<void(Ref*)>>& functions);

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
		CREATE_FUNC(SelectMenuLayer);
	};
}

#endif //__MAINMENULAYER_H__