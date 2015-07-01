#ifndef __BASEMENULAYER_H__
#define __BASEMENULAYER_H__

#include "BackGround3Parts.h"
#include "cocos2d.h"
namespace Menus{

	/**
	@brief  De esta clase de derivaran el resto de menus.
	*/
	class BaseMenuLayer :public cocos2d::Layer
	{
	protected:
		Components::BackGround3Parts* _bg;
		cocos2d::Size _visibleSize;
		cocos2d::SpriteBatchNode* _gameBatchNode;

	public:
		BaseMenuLayer();
		virtual ~BaseMenuLayer();

		/**
		@brief  Metodo llamado por el game loop de cocos en cada frame
		*/
		virtual void update(float dt);


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
		CREATE_FUNC(BaseMenuLayer);
	};
}

#endif

