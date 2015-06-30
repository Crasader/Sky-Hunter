#include "Level9.h"
#include "CustomAudioManager.h"

USING_NS_CC;
using namespace Levels;
using namespace Actors;
using namespace Components;

Scene* Level9::createScene()
{
	auto scene = Scene::create();
	auto layer = Level9::create();
	scene->addChild(layer);
	return scene;
}


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
	setMediumAwakeSpeed(1.5);
	setHeightAwakeSpeed(1.5);
	_bg = new Background("fondo2");
	_bg->setParent(_gameBatchNode, BackgroundPos);
}