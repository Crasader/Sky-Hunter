#include "MainMenuLayer.h"
#include "ui/CocosGUI.h"
#include "GameLayer.h"


USING_NS_CC;
using namespace ui;


Scene* MainMenuLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

MainMenuLayer::MainMenuLayer()
{
}


MainMenuLayer::~MainMenuLayer()
{
}

bool MainMenuLayer::init(){
	if (!Layer::init()){
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//create node with texture info & init TextureCache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainMenu.plist", "mainMenu.png");
	SpriteBatchNode* gameBatchNode = SpriteBatchNode::create("mainMenu.png");
	addChild(gameBatchNode);

	//bg
	_bg = new BackGround3Parts();
	_bg->setSpeed(30);	
	_bg->setParent(gameBatchNode);
	
	//start next level
	auto startButton = Button::create("start0", "start1","start1",Widget::TextureResType::PLIST);
	startButton->setAnchorPoint(Point(0.5, 1));
	startButton->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height-(60*getScaleY())));
	startButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::startButtonAction, this));
	addChild(startButton);
	
	//selectLEvel
	auto nextHeight = startButton->getPositionY() - startButton->getBoundingBox().size.height - (30 * getScaleY());
	auto selectButton = Button::create("select0", "select1", "select1", Widget::TextureResType::PLIST);
	selectButton->setAnchorPoint(Point(0.5, 1));
	selectButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(selectButton);

	//Arcade mode
	nextHeight = selectButton->getPositionY() - selectButton->getBoundingBox().size.height - (30 * getScaleY());
	auto arcadeButton = Button::create("arcade0", "arcade1", "arcade1",Widget::TextureResType::PLIST);
	arcadeButton->setAnchorPoint(Point(0.5, 1));
	arcadeButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(arcadeButton);

	//options to set volume of
	nextHeight = arcadeButton->getPositionY() - arcadeButton->getBoundingBox().size.height - (30 * getScaleY());
	auto optionsButton = Button::create("options0", "options1", "options1", Widget::TextureResType::PLIST);
	optionsButton->setAnchorPoint(Point(0.5, 1));
	optionsButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(optionsButton);

	scheduleUpdate();
	return true;
}

void MainMenuLayer::startButtonAction(){
	//Director::getInstance()->replaceScene(TransitionFlipX::create(1,GameLayer::createScene()));
	//Director::getInstance()->replaceScene(TransitionSlideInT::create(1, GameLayer::createScene()));
	Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameLayer::createScene()));
}

void MainMenuLayer::update(float dt){
	_bg->update(dt);
}
