#include "MainMenuLayer.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"
#include "SelectMenuLayer.h"
#include "OptionsLayer.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"




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
	//init function
	initFunctions(_functions);

	//lanza automaticamente el siguiente nivel a jugar
	auto startButton = Button::create("start0", "start1", "start1", Widget::TextureResType::PLIST);
	startButton->setAnchorPoint(Point(0.5, 1));
	startButton->setPosition(Vec2(_visibleSize.width*0.5, _visibleSize.height - (90 * getScaleY())));
	if (GameManager::getInstance()->getNextLevel() == NUM_LEVELS)
	{
		startButton->addClickEventListener(_functions.at(NUM_LEVELS - 1));
	}
	else
	{
		startButton->addClickEventListener(_functions.at(GameManager::getInstance()->getNextLevel()));
	}
	addChild(startButton);

	//lanza el menu de lseleccion de nivel
	auto nextHeight = startButton->getPositionY() - startButton->getBoundingBox().size.height - (30 * getScaleY());
	auto selectButton = Button::create("select0", "select1", "select1", Widget::TextureResType::PLIST);
	selectButton->setAnchorPoint(Point(0.5, 1));
	selectButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::selectMenuButton, this));
	selectButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(selectButton);

	//lanza las opciones para ajustar volumen y otras configuraciones
	nextHeight = selectButton->getPositionY() - selectButton->getBoundingBox().size.height - (30 * getScaleY());
	auto optionsButton = Button::create("options0", "options1", "options1", Widget::TextureResType::PLIST);
	optionsButton->setAnchorPoint(Point(0.5, 1));
	optionsButton->addClickEventListener(CC_CALLBACK_0(MainMenuLayer::optionsButton, this));
	optionsButton->setPosition(Point(startButton->getPositionX(), nextHeight));
	addChild(optionsButton);

	return true;
}



void MainMenuLayer::selectMenuButton(){
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, SelectMenuLayer::createScene()));
}

void MainMenuLayer::optionsButton(){
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, OptionsLayer::createScene()));
}



void MainMenuLayer::initFunctions(std::vector<std::function<void(Ref*)>>& functions){
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton1, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton2, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton3, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton4, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton5, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton6, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton7, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton8, this));
	functions.push_back(CC_CALLBACK_0(MainMenuLayer::actionButton9, this));
}

void MainMenuLayer::actionButton1(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level1::createScene())); }
void MainMenuLayer::actionButton2(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level2::createScene())); }
void MainMenuLayer::actionButton3(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level3::createScene())); }
void MainMenuLayer::actionButton4(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level4::createScene())); }
void MainMenuLayer::actionButton5(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level5::createScene())); }
void MainMenuLayer::actionButton6(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level6::createScene())); }
void MainMenuLayer::actionButton7(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level7::createScene())); }
void MainMenuLayer::actionButton8(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level8::createScene())); }
void MainMenuLayer::actionButton9(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, Level9::createScene())); }
