#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__
#include "cocos2d.h"
#define LEVELKEY "level"
#define BGVOLUMEKEY "bgvolume"
#define EFFECTSVOLUMEKEY "effectvolume"
#define MAXSCOREKEY "maxscore"

namespace Levels{

	/**
	@brief  singleton encargado de mantener el estado del juego y guardar en persistencia los niveles superados
	*/
	class GameManager
	{
	private:
		GameManager();
		~GameManager();
		static GameManager* _instance;
		GameManager(GameManager const&) = delete;// copy constructor is private
		void operator=(GameManager const&) = delete;// assignment operator is private


	public:
		CC_SYNTHESIZE(int, _bgVolume, BgVolume);
		CC_SYNTHESIZE(int, _effectsVolume, EffectsVolume);
		CC_SYNTHESIZE(int, _playerScore, PlayerScore);

		/**
		@brief  este metodo guarda en persistencia los ajustes de este singleton
		*/
		void saveSetting();

		/**
		@brief  este metodo guarda en persistencia la puntuacion maxima
		@param score la puntuacion
		*/
		void saveMaxScore(int score);

		/**
		@brief  retorna la puntuacion maima guardada en persistencia o 0 si no hay nada guardado
		 @return la puntuacion
		*/
		int getMaxScore();
		static GameManager* getInstance();

		/**
		@brief  este metodo guarda en persistencia el numero del siguiente nivel a jugar
		@param tag del nivel superado
		*/
		void saveGame(int tag);

		/**
		@brief  retorna el numero del siguiente nivel a jugar
		@return el numero del nivel
		*/
		int getNextLevel();

	};
}

#endif //__GAMEMANAGER_H__;
