#ifndef __BACKGROUND3PARTS_H__
#define __BACKGROUND3PARTS_H__

#include "cocos2d.h"
namespace Components{
	class BackGround3Parts
	{

	private:
		bool _initialiced;
		cocos2d::Size _screen;
		cocos2d::Sprite* _bgPart1;
		cocos2d::Sprite* _bgPart2;
		cocos2d::Sprite* _bgPart3;
		cocos2d::Sprite* _bgPart4;
		cocos2d::Sprite* _bgPart5;


	public:
		BackGround3Parts();
		~BackGround3Parts();
		CC_SYNTHESIZE(float, _speed, Speed);

		/**
		@brief inserta el fondo en la escena
		@param parent nodo padre del fondo
		@param pos psoicion z de dibujado
		*/
		virtual void setParent(cocos2d::Node* parent);
		/**
		@brief metodo que se ejecuta en cada frame del juego y que movera a una cierta velocidad el fondo de pantalla
		@param dt tiempo transcurrido desde la ultima ejecucion
		*/
		void update(float dt);


		
	};
}

#endif //__BACKGROUND3PARTS_H__