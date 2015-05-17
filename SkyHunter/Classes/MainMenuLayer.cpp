#include "MainMenuLayer.h"
#include "GameLayer.h"
#include "SelectMenuLayer.h"
#include "OptionsLayer.h"
#include "ui/CocosGUI.h"



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


bool MainMenuLayer::init(){
	if (!BaseMenuLayer::init()){
		return false;
	}
	//start next level
	auto startButton = Button::create("start0", "start1","start1",Widget::TextureResType::PLIST);
	startButton->setAnchorPoint(Point(0.5, 1));
	startButton->setPosition(Vec2(_visibleSize.width*0.5, _visibleSize.height - (60 * getScaleY())));
	startButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::startButtonAction, this));
	addChild(startButton);
	
	//selectLEvel
	auto nextHeight = startButton->getPositionY() - startButton->getBoundingBox().size.height - (30 * getScaleY());
	auto selectButton = Button::create("select0", "select1", "select1", Widget::TextureResType::PLIST);
	selectButton->setAnchorPoint(Point(0.5, 1));
	selectButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::selectMenuButton, this));
	selectButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(selectButton);

	//Arcade mode
	nextHeight = selectButton->getPositionY() - selectButton->getBoundingBox().size.height - (30 * getScaleY());
	auto arcadeButton = Button::create("arcade0", "arcade1", "arcade1",Widget::TextureResType::PLIST);
	arcadeButton->setAnchorPoint(Point(0.5, 1));
	arcadeButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::arcadeButton, this));
	arcadeButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(arcadeButton);

	//options to set volume of
	nextHeight = arcadeButton->getPositionY() - arcadeButton->getBoundingBox().size.height - (30 * getScaleY());
	auto optionsButton = Button::create("options0", "options1", "options1", Widget::TextureResType::PLIST);
	optionsButton->setAnchorPoint(Point(0.5, 1));
	optionsButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::optionsButton, this));
	optionsButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(optionsButton);

	return true;
}

void MainMenuLayer::startButtonAction(){
	Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameLayer::createScene()));
}

void MainMenuLayer::selectMenuButton(){
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, SelectMenuLayer::createScene()));
}

void MainMenuLayer::optionsButton(){
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, OptionsLayer::createScene()));
}

void MainMenuLayer::arcadeButton(){
	Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameLayer::createScene()));
}

