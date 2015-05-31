#include "SelectMenuLayer.h"
#include "GameManager.h"
#include "MainMenuLayer.h"


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

	initFunctions(functions);
	//add buttons to scene
	initButtons(buttons, functions);

	//check available levels
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




void SelectMenuLayer::actionButtonBack()
{ 
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, MainMenuLayer::createScene()));
}


