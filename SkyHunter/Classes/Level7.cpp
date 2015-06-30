#include "Level7.h"
#include "CustomAudioManager.h"
#include "Blizzard.h"

USING_NS_CC;
using namespace Levels;
using namespace Actors;
using namespace Components;




Scene* Level7::createScene()
{
	auto scene = Scene::create();
	auto layer = Level7::create();
	scene->addChild(layer);
	return scene;
}


bool Level7::init()
{
	if (!Level1::init())
	{
		return false;
	}

	return true;
}

void Level7::initializeVariables(){
	Level1::initializeVariables();
	CustomAudioManager::getInstance()->stopAll();
	CustomAudioManager::getInstance()->playBackgroundSound("music/Fade.wav", true);
	setTag(7);//level7
	_bg->removeFromParent();
	setAwakeSpeed(0.5f);
	_bg = new Background("fondo2");
	_bg->setParent(_gameBatchNode, BackgroundPos);
}



