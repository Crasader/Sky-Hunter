#include "Level9.h"
#include "CustomAudioManager.h"

USING_NS_CC;


Scene* Level9::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level9::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level9::init()
{
	if (!Level3::init())
	{
		return false;
	}

	return true;
}

void Level9::initializeVariables(){
	Level3::initializeVariables();
	CustomAudioManager::getInstance()->stopAll();
	CustomAudioManager::getInstance()->playBackgroundSound("music/Fade.wav", true);
	setTag(9);//level9
	_bg->removeFromParent();
	setMediumAwakeSpeed(1);
	setHeightAwakeSpeed(1.5);
	_bg = new Background("fondo2");
	_bg->setParent(_gameBatchNode, BackgroundPos);
}