#include "GameManager.h"


USING_NS_CC;

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager() :_playerScore(0)
{
	_nextLevel = UserDefault::getInstance()->getIntegerForKey(LEVELKEY, 0);
	_bgVolume = UserDefault::getInstance()->getIntegerForKey(BGVOLUMEKEY, 30);
	_effectsVolume = UserDefault::getInstance()->getIntegerForKey(EFFECTSVOLUMEKEY, 40);
}


GameManager::~GameManager()
{
}

void GameManager::saveSetting(){
	UserDefault::getInstance()->setIntegerForKey(BGVOLUMEKEY, _bgVolume);
	UserDefault::getInstance()->setIntegerForKey(EFFECTSVOLUMEKEY, _effectsVolume);
}

GameManager*  GameManager::getInstance(){

	if (!_instance){
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::saveGame(){
	_nextLevel = UserDefault::getInstance()->getIntegerForKey(LEVELKEY, 0);
	//gurardo nivel completado
	UserDefault::getInstance()->setIntegerForKey(LEVELKEY, _nextLevel);
	//calculo siguietne nivel
	_nextLevel++;
}

int GameManager::getNextLevel(){
	return _nextLevel;
}
