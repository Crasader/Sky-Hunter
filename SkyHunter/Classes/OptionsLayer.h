
#ifndef __OPTIONSLAYER_H__
#define __OPTIONSLAYER_H__

#define NUM_LEVELS 9

#include "BaseMenuLayer.h"
#include "ui/CocosGUI.h"

namespace Menus{


	/**
	@brief  Capa que representa el menu de opciones
	*/
	class OptionsLayer : public BaseMenuLayer
	{
	private:
		std::ostringstream _ostr;
		cocos2d::ui::Slider* _effectsVolume;
		cocos2d::ui::Slider* _backGroundVolume;
		cocos2d::Label* _backGroundVolumeLabel;
		cocos2d::Label * _effectsVolumeLabel;

	private:
		/**
		@brief  Accion a ejecutar por el boton de volver atras que debe lanzar el menu principal
		*/
		void actionButtonBack();
		/**
		@brief  Accion a ejecutada cada vez que el valor del slider varia
		*/
		void actionBackGroundVolumeSlider();

		/**
		@brief  Accion a ejecutada cada vez que el valor del slider varia
		*/
		void actionEffectsVolumeSlider();

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
		CREATE_FUNC(OptionsLayer);
	};
}

#endif //__OPTIONSLAYER_H__