#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "cocos2d.h"
#include "TouchController.h"
#include "PlayerBullet.h"

#define MAX_HEALTH 3



namespace Actors{
	class BasicEnemy;
	class Player : public cocos2d::Sprite
	{
	public:
		enum Animations
		{
			IDLE = 0, EXPLOSION = 1
		};

	private:
		cocos2d::ParticleSystemQuad* _hitEffect;
		int _health;
		int SHOOT_TAG = 3;
		bool _initialiced;
		cocos2d::Vector<PlayerBullet*> _bulletPool;
		cocos2d::Vector<BasicEnemy*>  _targets;

		int _numBullets;
		int _bulletIndex;
		
		TouchController* _controller;
		Animations _currentAnimation;

		cocos2d::Action* _idleAnimation;
		cocos2d::Action* _explosionAnimation;
		cocos2d::Action* _shoot;

	private:
		/**
		@brief  crea la animacion por defecto
		*/
		void createIdleAnimation();

		/**
		@brief  crea la animacion de explotar
		*/
		void createExplosionAnimation();
		/**
		@brief  activa las balas del pool de balas
		*/
		void shoot();
		/**
		@brief  crea la accion que ejecutara cada cierto tiempo el metodo shoot
		*/
		void scheduleShoot();
	public:
		CC_SYNTHESIZE(float, _speed, Speed);
		const int getHealth(){ return _health; };
		void setHealth(int health);
		Player();

		/**
		@brief  actualiza la municion del player
		@param create funcion de creacion del nuevo tipo de municion
		*/
		void updateBullets(const std::function<PlayerBullet*()>& create);

		/**
		@brief  modifica el nodo padre de este nodo
		@param parent el nuevo padre del nodo
		*/
		virtual void setParent(Node* parent);

		/**
		@brief  efectos ejecutados cuando el player es golpeado como los sonidos o particulas
		*/
		void runHitEffect();
		

		/**
		@brief  le indica al player cuales son sus adversarios
		@param target una referencia a un vector de enemigos
		*/
		void setTargets(const cocos2d::Vector<BasicEnemy*>& targets);

		/**
		@brief  hace que se ejecute una u otra animacion
		@param anim el identificador de la animacion
		*/
		void setCurrentAnimation(Animations anim);

		/**
		@brief  retorna el identificador de la aimacion que se esta ejecutando
		@return el identificador de la animacion
		*/
		const Animations getCurrentAnimation(){ return  _currentAnimation; }

		/**
		@brief  pausa al player y todas sus acciones
		*/
		virtual void pause();

		/**
		@brief  reactiva al player
		*/
		virtual void resume();

		/**
		@brief  pone el player en su estado original
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
		CREATE_FUNC(Player);

		
	};
}
#endif //__PLAYER_H__

