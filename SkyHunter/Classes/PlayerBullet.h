#ifndef __PLAYERBULLET_H__
#define __PLAYERBULLET_H__
#include "cocos2d.h"

#include "BasicEnemy.h"
namespace Actors{
	class PlayerBullet :public cocos2d::Sprite
	{
	private:
		cocos2d::Vector<BasicEnemy*>  _playerTargets;
	protected:
		int _damage;
	public:
		CC_SYNTHESIZE(float, _speed, Speed);

		/**
		@brief  indica a las balas cuales son los enemigos
		@param targets una referencia a un vector de enemigos
		*/
		void setPlayerTargets(const cocos2d::Vector<BasicEnemy*>& targets){ _playerTargets = targets; };

		/**
		@brief  Metodo que se ejecuta para reproducir el sonido de un disparo
		*/
		virtual void playShootSound();

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
		CREATE_FUNC(PlayerBullet);
	};
}
#endif //__PLAYERBULLET_H__
