#ifndef __BASICENEMY_H__
#define __BASICENEMY_H__


#include "cocos2d.h"
#include "EnemyBullet.h"


namespace Actors{
	class Player;

	/**
	@brief  enemigo basico de nuestro juego, de el se derivan el resto de enemigos
	*/
	class BasicEnemy : public cocos2d::Sprite
	{

	public:
		int ENEMY_HEALTH;
		enum Animations
		{
			IDLE = 0, EXPLOSION = 1
		};

	protected:
		int SHOOT_TAG = 3;
		bool _initialiced;
		int _bulletIndex;
		float _shootFrequencySeconds;
		int _numBullets;
		Animations _currentAnimation;
		cocos2d::Action* _idleAnimation;
		cocos2d::Action* _explosionAnimation;
		cocos2d::Action* _shoot;
		cocos2d::Vector<EnemyBullet*> _bulletPool;

	protected:
		/**
		@brief  crea la animacion por defecto
		@param spriteName nombre del sprite
		@param numberOfFrames numero de frames de la aniamcion
		*/
		void createIdleAnimation(std::string spriteName, int numberOfFrames);

		/**
		@brief  crea la animacion de explotar
		@param spriteName nombre del sprite
		@param numberOfFrames numero de frames de la aniamcion
		*/
		void createExplosionAnimation(std::string spriteName, int numberOfFrames);

		/**
		@brief  define un comportamiento para el enemigo, en este caso ir ahacia la parte inferior de la pantalla
		*/
		virtual void behaviour(float dt);

		/**
		@brief  crea las balas del enemigo y las incopora al pool y a la escena
		*/
		virtual void createBullets();

		/**
		@brief  activa las balas del pool de balas
		*/
		void shoot();
		/**
		@brief  crea la accion que ejecutara cada cierto tiempo el metodo shoot
		*/
		void scheduleShoot();


	public:
		BasicEnemy();
		CC_SYNTHESIZE(int, _health, Health);
		CC_SYNTHESIZE(float, _speed, Speed);
		CC_SYNTHESIZE(int, _value, Value);
		
		/**
		@brief  modifica el nodo padre de este nodo
		@param parent el nuevo padre del nodo
		*/
		virtual void setParent(Node* parent);

		/**
		@brief  le indica al enemigo cual es su adversario
		@param target un puntero al player
		*/
		void setTarget(Player* target);

		/**
		@brief  hace que se ejecute una u otra animacion
		@param anim el identificador de la animacion
		*/
		void setCurrentAnimation(Animations anim);

		/**
		@brief  retorna el identificador de la aimacion que se esta ejecutando
		@return el identificador de la animacion
		*/
		Animations getCurrentAnimation(){ return  _currentAnimation; }

		/**
		@brief  pausa al enemigo y todas sus acciones
		*/
		virtual void pause();

		/**
		@brief  reactiva al enemigo
		*/
		virtual void resume();

		/**
		@brief  pone el enemigo en su estado original
		*/
		void reset();


		/**
		@brief  Metodo para indicar si se debe renderizar el nodo o no
		@param visible si true se renderica, si false, no.
		*/
		virtual void setVisible(bool visible);
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
		CREATE_FUNC(BasicEnemy);
	};
}

#endif //__BASICENEMY_H__

