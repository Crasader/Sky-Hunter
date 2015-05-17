#include "SelectMenuLayer.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "MainMenuLayer.h"

#define func SelectMenuLayer::actionButton


USING_NS_CC;
using namespace ui;

Scene* SelectMenuLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectMenuLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool SelectMenuLayer::init(){
	if (!BaseMenuLayer::init()){
		return false;
	}

	std::vector<std::function<void(Ref*)>> functions;
	cocos2d::Vector<Button*> buttons;

	initfunctions(functions);
	//buttons
	initButtons(buttons, functions);

	//check avilabel levels
	for (int i = 0; i < NUM_LEVELS; i++){
		if (i>GameManager::getInstance()->getNextLevel()) break;
		//enable button
		buttons.at(i)->setEnabled(true);
		//show enable image
		buttons.at(i)->setBright(true);
	}

	//crete back button
	auto backBt = Button::create("back0", "back1", "back1", Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Point(0, 0.5));
	backBt->addClickEventListener(CC_CALLBACK_0(SelectMenuLayer::actionButtonBack, this));
	backBt->setPosition(Point(42.5* getScaleX(), 50 * getScaleY()));
	addChild(backBt);

	return true;
}

void SelectMenuLayer::initButtons(cocos2d::Vector<Button*>& buttons, std::vector<std::function<void(Ref*)>>& functions){
	int tag = 1;
	int sizeY = 0;
	int sizeX = 0;
	int marginX = 42.5* getScaleX();
	int marginY = _visibleSize.height - 100 * getScaleY();
	for (int i = 0; i < NUM_LEVELS / 3; i++){
		for (int j = 0; j < NUM_LEVELS / 3; j++){
			auto bt = Button::create("level_unlock0", "level_unlock1", "level_lock", Widget::TextureResType::PLIST);
			//disable
			bt->setEnabled(false);
			//show disable image
			bt->setBright(false);
			bt->addClickEventListener(functions.at(tag - 1));
			bt->setTag(tag); _ostr << tag; tag++;
			bt->setTitleText(_ostr.str()); _ostr.str("");
			bt->setTitleFontSize(18);
			bt->setAnchorPoint(Point(0, 0.5));
			bt->setPosition(Point(marginX, marginY));
			sizeX = bt->getBoundingBox().size.width;
			sizeY = bt->getBoundingBox().size.height;
			marginX += 42.5* getScaleX() + sizeX;
			buttons.pushBack(bt);
			addChild(bt);
		}
		marginX = 42.5* getScaleX();
		marginY -= (42.5 * getScaleY() + sizeY);
	}
}


void SelectMenuLayer::initfunctions(std::vector<std::function<void(Ref*)>>& functions){
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton1, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton2, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton3, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton4, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton5, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton6, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton7, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton8, this));
	functions.push_back(CC_CALLBACK_0(SelectMenuLayer::actionButton9, this));
}

void SelectMenuLayer::actionButton1(){ Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameLayer::createScene())); }
void SelectMenuLayer::actionButton2(){/*TODO*/}
void SelectMenuLayer::actionButton3(){/*TODO*/ }
void SelectMenuLayer::actionButton4(){/*TODO*/ }
void SelectMenuLayer::actionButton5(){/*TODO*/ }
void SelectMenuLayer::actionButton6(){/*TODO*/ }
void SelectMenuLayer::actionButton7(){/*TODO*/ }
void SelectMenuLayer::actionButton8(){/*TODO*/ }
void SelectMenuLayer::actionButton9(){/*TODO*/ }

void SelectMenuLayer::actionButtonBack()
{ 
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, MainMenuLayer::createScene()));
}


