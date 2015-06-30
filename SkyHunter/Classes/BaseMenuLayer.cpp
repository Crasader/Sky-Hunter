#include "BaseMenuLayer.h"
#include "Level1.h"

USING_NS_CC;
using namespace Menus;
using namespace Components;

Scene* BaseMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = BaseMenuLayer::create();
	scene->addChild(layer);
	return scene;
}

BaseMenuLayer::BaseMenuLayer()
{
}


BaseMenuLayer::~BaseMenuLayer()
{
	CC_SAFE_DELETE(_bg);
}
bool BaseMenuLayer::init(){
	if (!Layer::init()){
		return false;
	}
	//crea el nodeo que contiene la informacion de la textura y el descriptor
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainMenu.plist", "mainMenu.png");
	_gameBatchNode = SpriteBatchNode::create("mainMenu.png");
	addChild(_gameBatchNode);
	_visibleSize = Director::getInstance()->getVisibleSize();

	//fondo de pantalla
	_bg = new BackGround3Parts();
	_bg->setSpeed(30);
	_bg->setParent(_gameBatchNode);



	scheduleUpdate();
	return true;
}


void BaseMenuLayer::update(float dt){
	_bg->update(dt);
}



