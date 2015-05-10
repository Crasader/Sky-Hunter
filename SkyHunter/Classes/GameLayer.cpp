#include "GameLayer.h"


USING_NS_CC;

Scene* GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//create bg
	_bg = Background::create();
	addChild(_bg);

	//create player
	_player = Player::create();
	_player->setPosition(visibleSize.width*0.5, visibleSize.height*0.3);
	addChild(_player);

	auto enemy = BasicEnemy::create();
	enemy->setPosition(visibleSize.width*0.5, visibleSize.height*0.8);
	addChild(enemy);

	//start game loop
	this->schedule(schedule_selector(GameLayer::update));
	return true;
}


void GameLayer::update(float dt){
	_bg->update(dt);
	_player->update(dt);
}

