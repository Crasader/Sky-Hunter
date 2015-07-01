#ifndef __BASEGAMELAYER_H__
#define __BASEGAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Background.h"



namespace Levels{


	/**
	@brief  De esta clase de derivaran el resto de niveles, contienen componentes comunes como la interfaz de usuario o el player.
	*/
	class BaseGameLayer : public cocos2d::Layer
	{
	private:
		int _completionPercentage;
		bool isLevelComplete;
		std::ostringstream _ostr;
		cocos2d::ui::Button* _pauseButton;
		cocos2d::ui::Button* _respawnButton;
		cocos2d::ui::Button* _playButton;
		cocos2d::ui::Button* _backButton;
		cocos2d::Sprite* _healthBar;
		cocos2d::Label* _scoreLabel;
		cocos2d::Label* _completionPercentageLabel;

		/**
		@brief  crea el indicador de salud y lo incluye en la escena
		*/
		void createHealthIndicator();

		/**
		@brief  crea los labels de puntuacion y porcentaje de nivel completado
		*/
		void createScoreAndPercentageLabels();

		/**
		@brief  crea los botones de pause y play
		*/
		void createPauseAndResumeButtons();

		/**
		@brief  crea el boton de volver a jugar nivel
		*/
		void createRespawnButton();

		/**
		@brief  muestra letras en pantalla y lanza levelCompleteActionsHelper cuando el jugador gana el nivel
		*/
		void levelCompleteActions();

		/**
		@brief  lanza el menu de seleccion de nivel
		*/
		void levelCompleteActionsHelper();

	protected:
		enum RenderOrder { BackgroundPos, ForegroundPos, UIPos };
		//enemigos totales
		int _numEnemies;
		int _enemyIndex;
		//pool total de enemigos
		cocos2d::Vector<Actors::BasicEnemy*> _enemyPool;

		Actors::Player* _player;

		Components::Background* _bg;
		int _scoreToCompleTheLevel;
		cocos2d::Size _visibleSize;
		cocos2d::SpriteBatchNode* _gameBatchNode;

		/**
		@brief  pone el player en su estado original
		*/
		virtual void resetPlayer();

		/**
		@brief  acciones ejecutadas por el boton de volver a jugar
		*/
		virtual void respawnButtonAction();

		/**
		@brief  acciones ejecutadas por el boton de pausa
		*/
		virtual void pauseButtonAction();

		/**
		@brief  acciones ejecutadas por el boton de play
		*/
		virtual void playButtonAction();

		/**
		@brief  acciones ejecutadas por el boton de volver atras
		*/
		virtual void actionButtonBack();

	public:
		virtual ~BaseGameLayer();

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
		CREATE_FUNC(BaseGameLayer);
	};
}
#endif //__BASEGAMELAYER_H__

