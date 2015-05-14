#include "GameManager.h"


USING_NS_CC;

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
	_nextLevel = -1;
}


GameManager::~GameManager()
{
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
	if (_nextLevel != -1){
		//obtengo el ultimo nivel completado
		_nextLevel = UserDefault::getInstance()->getIntegerForKey(LEVELKEY, 0);
		//calculo el siguiente nivel
		_nextLevel++;
	}
	return _nextLevel;
}
