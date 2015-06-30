#include "Level8.h"
#include "CustomAudioManager.h"

USING_NS_CC;
using namespace Levels;


Scene* Level8::createScene()
{
	auto scene = Scene::create();
	auto layer = Level8::create();
	scene->addChild(layer);
	return scene;
}

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
	_bg = new Components::Background("fondo2");
	_bg->setParent(_gameBatchNode, BackgroundPos);
}



