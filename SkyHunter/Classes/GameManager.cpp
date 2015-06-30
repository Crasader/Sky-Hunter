#include "GameManager.h"


USING_NS_CC;
using namespace Levels;

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager() :_playerScore(0)
{
	
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

void GameManager::saveGame(int tag){
	if (tag > getNextLevel())
	{
		UserDefault::getInstance()->setIntegerForKey(LEVELKEY, tag);
	}
}

int GameManager::getNextLevel(){
	return UserDefault::getInstance()->getIntegerForKey(LEVELKEY, 0);
}

void GameManager::saveMaxScore(int score){
	UserDefault::getInstance()->setIntegerForKey(MAXSCOREKEY, score);
}

int GameManager::getMaxScore(){
	return UserDefault::getInstance()->getIntegerForKey(MAXSCOREKEY, 0);
}
