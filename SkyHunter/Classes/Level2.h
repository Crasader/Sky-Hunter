#ifndef __LEVEL2_SCENE_H__
#define __LEVEL2_SCENE_H__
#include "BaseGameLayer.h"

namespace Components{
	class HealthParticle;
	class PlayerUpgradeParticle;
}

namespace Levels{
	/**
	@brief  nivel 2 de nuestro juego
	*/
	class Level2 : public BaseGameLayer
	{

	private:
		/**
		@brief  Identificadores para las acciones de despertar enemigos
		*/
		enum ActionScheduler { BasicScheduler, MediumScheduler };
		Components::HealthParticle* _health;
		Components::PlayerUpgradeParticle * _upgrade;
		bool _mediumSchedulerRunning;

		//enemigos de nivel medio
		int _numMediumEnemies;
		int _mediumEnemyIndex;

		/**
		@brief  metodo que activa los anemigos basicos del pool de enemigos
		*/
		void awakeBasicEnemy();

		/**
		@brief  metodo que crea la accion que ejecutara el awakeBasicEnemy cada cierto tiempo
		*/
		void awakeBasicEnemyScheduler();

		/**
		@brief  metodo que activa los anemigos medios del pool de enemigos
		*/
		void awakeMediumEnemy();

		/**
		@brief  metodo que crea la accion que ejecutara el awakeMediumEnemy cada cierto tiempo
		*/
		void awakeMediumEnemyScheduler();

		/**
		@brief  metodo que verifica colisiones entre los enemigos del pool de enemigos y el player
		*/
		void checkCollisions();

		/**
		@brief  metodo encargado de inicializar al player y los enemigos
		*/
		void initActors();

		/**
		@brief  lanza las acciones como el update
		*/
		void scheduleActions();

		/**
		@brief  lanza cada cierto tiempo un actualizador de salud
		*/
		void launchHealth();

		/**
		@brief  lanza cada cierto tiempo un actualizador de municion
		*/
		void launchUpgrade();

		/**
		@brief  activa el lanzamiento de enemigos medios y desactiva el de enemigos basicos
		*/
		void launchMediumEnemies();

		/**
		@brief  lanza las acciones como el launchUpgrade
		*/
		void schduleUpgrades();

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
		CC_SYNTHESIZE(float, _basicAwakeSpeed, BasicAwakeSpeed);
		CC_SYNTHESIZE(float, _mediumAwakeSpeed, MediumAwakeSpeed);
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
		CREATE_FUNC(Level2);
	};
}
#endif // __LEVEL2_SCENE_H__