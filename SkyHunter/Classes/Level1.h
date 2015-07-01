#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "BaseGameLayer.h"

namespace Levels{

	/**
	@brief  nivel 1 de nuestro juego
	*/
	class Level1 : public BaseGameLayer
	{

	private:
		/**
		@brief  metodo que activa los anemigos del pool de enemigos
		*/
		void awakeEnemy();

		/**
		@brief  metodo que crea la accion que ejecutara el awakeEnemy cada cierto tiempo
		*/
		void awakeEnemyScheduler();

		/**
		@brief  metodo que verifica colisiones entre los enemigos del pool de enemigos y el player
		*/
		void checkCollisions();

		/**
		@brief  metodo encargado de inicializar al player y los enemigos
		*/
		void initActors();

		/**
		@brief  lanza las acciones como awakeEnemyScheduler o el update
		*/
		void scheduleActions();


	protected:
		/**
		@brief  inicializa variables globales del nievel como el player o el fondo de pantalla
		*/
		virtual void initializeVariables();

		/**
		@brief  sobrecarga las acciones a ejecutar para volver a jugar el nivel
		*/
		virtual void respawnButtonAction();


		/**
		@brief  sobrecarga las acciones a ejecutar para pausar el nivel
		*/
		virtual void pauseButtonAction();


		/**
		@brief  sobrecarga las acciones a ejecutar para resumir el nivel
		*/
		virtual void playButtonAction();

	public:
		CC_SYNTHESIZE(float, _awakeSpeed, AwakeSpeed);

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

		/**
		@brief  crea una escena a partir de esta capa.
		*/
		static cocos2d::Scene* createScene();

		// implementa el metodo  "static create()" 
		CREATE_FUNC(Level1);
	};
}

#endif // __LEVEL1_SCENE_H__
