#ifndef __TOUCHCONTROLLER_H__
#define __TOUCHCONTROLLER_H__
#include "cocos2d.h"
namespace Actors{
	class TouchController : public cocos2d::Sprite
	{
	private:
		struct  Controller {
			bool left;
			bool right;
			bool up;
			bool upLeft;
			bool upRight;
			bool down;
			bool downLeft;
			bool downRight;
		};

		cocos2d::Point _tap;
		Controller _controller;

		/**
		@brief  pone a false todos los flags de la estructura Controller
		*/
		void resetTouchController();

	public:
		
		Controller getController(){ return _controller; }

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
		CREATE_FUNC(TouchController);

	protected:
		//touch call backs
		virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
		virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
		virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	};
}
#endif //__TOUCHCONTROLLER_H__

