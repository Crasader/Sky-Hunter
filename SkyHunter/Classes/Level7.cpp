#include "Level7.h"
#include "CustomAudioManager.h"
#include "Blizzard.h"

USING_NS_CC;




Scene* Level7::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level7::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
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



