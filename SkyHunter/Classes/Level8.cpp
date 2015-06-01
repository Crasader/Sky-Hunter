#include "Level8.h"
#include "CustomAudioManager.h"

USING_NS_CC;


Scene* Level8::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level8::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level8::init()
{
	if (!Level2::init())
	{
		return false;
	}


	return true;
}

void Level8::initializeVariables(){
	Level2::initializeVariables();
	CustomAudioManager::getInstance()->stopAll();
	CustomAudioManager::getInstance()->playBackgroundSound("music/Fade.wav", true);
	setTag(8);//level8
	_bg->removeFromParent();
	setMediumAwakeSpeed(1);
	setBasicAwakeSpeed(0.5);
	_bg = new Background("fondo2");
	_bg->setParent(_gameBatchNode, BackgroundPos);
}



