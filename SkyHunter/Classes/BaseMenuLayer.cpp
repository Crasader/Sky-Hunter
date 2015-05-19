#include "BaseMenuLayer.h"
#include "Level1.h"

USING_NS_CC;

Scene* BaseMenuLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BaseMenuLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
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

	//we want 3 rows and 3 columns 3*3=NUM_LEVELS
	//create node with texture info & init TextureCache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainMenu.plist", "mainMenu.png");
	_gameBatchNode = SpriteBatchNode::create("mainMenu.png");
	addChild(_gameBatchNode);
	_visibleSize = Director::getInstance()->getVisibleSize();

	//bg
	_bg = new BackGround3Parts();
	_bg->setSpeed(30);
	_bg->setParent(_gameBatchNode);



	scheduleUpdate();
	return true;
}


void BaseMenuLayer::update(float dt){
	_bg->update(dt);
}



