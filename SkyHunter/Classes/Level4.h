#ifndef __LEVEL4_SCENE_H__
#define __LEVEL4_SCENE_H__

#include "BaseGameLayer.h"
#include "Cloud.h"

namespace Components{
	class Blizzard;
}

namespace Levels{

	/**
	@brief  nivel 4 de nuestro juego
	*/
	class Level4 : public BaseGameLayer
	{

	private:
		Components::Blizzard* blizz;
		int CLOUDS_TAG = 0;
		cocos2d::Action* _cloudsScheduler;
		const int _cloudsPerRow = 6;
		int _numOfClouds;
		int _cloudIndex;

		cocos2d::Vector<Components::Cloud* > _clouds;
		std::vector<bool> _isPositionFree;


		/**
		@brief  metodo que verifica colisiones entre los enemigos del pool de enemigos y el player
		*/
		void checkCollisions();

		/**
		@brief  lanza las acciones como el update
		*/
		void scheduleActions();

		/**
		@brief  metodo encargado de inicializar al player y los enemigos
		*/
		void initActors();

		/**
		@brief  inicializa el pool de nubes
		*/
		void initClouds();

		/**
		@brief  metodo que activa filas de nubes
		*/
		void cloudPositioner();

		/**
		@brief  metodo que crea la accion que ejecutara el cloudPositioner cada cierto tiempo
		*/
		void cloudScheduler();

		/**
		@brief  metodo que activa los anemigos del pool de enemigos
		*/
		void awakeEnemy();

		/**
		@brief  metodo que crea la accion que ejecutara el awakeEnemy cada cierto tiempo
		*/
		void awakeEnemyScheduler();

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
		CREATE_FUNC(Level4);
	};
}

#endif // __LEVEL4_SCENE_H__