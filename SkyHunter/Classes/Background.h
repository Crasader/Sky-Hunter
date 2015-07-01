#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "cocos2d.h"


namespace Components{
	/**
	@brief  fondo de pantalla empleado en todos los niveles del juego. Mueve una imagen de fondo para dar efecto de movimiento al jeugo
	*/
	class Background
	{

	private:
		cocos2d::Node* _parent;
		int _pos;
		bool _initialiced;
		cocos2d::Size _screen;
		cocos2d::Sprite* _bgPart1;
		cocos2d::Sprite* _bgPart2;


	public:
		~Background();
		CC_SYNTHESIZE(float, _speed, Speed);
		/**
		@brief elimina los sprites del fondo de la escena
		*/
		void removeFromParent();

		/**
		@brief inserta el fondo en la escena
		@param parent nodo padre del fondo
		@param pos psoicion z de dibujado
		*/
		virtual void setParent(cocos2d::Node* parent, int pos);

		/**
		@brief metodo que se ejecuta en cada frame del juego y que movera a una cierta velocidad el fondo de pantalla
		@param dt tiempo transcurrido desde la ultima ejecucion
		*/
		void update(float dt);
		

		/**
		@brief cambia la imagen del fondo de pantalla
		*/
		void setSptite(std::string part1);

		/**
		@brief constructor de la clase
		@param nombre del fichero que sera el fondo de pantalla
		*/
		Background(std::string spritename);
	};
}

#endif //__BACKGROUND_H__

