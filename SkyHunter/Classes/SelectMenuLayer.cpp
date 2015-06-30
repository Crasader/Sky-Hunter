#include "SelectMenuLayer.h"
#include "GameManager.h"
#include "MainMenuLayer.h"


USING_NS_CC;
using namespace ui;
using namespace Menus;
using namespace Levels;

Scene* SelectMenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMenuLayer::create();
	scene->addChild(layer);
	return scene;
}


bool SelectMenuLayer::init(){
	if (!BaseMenuLayer::init()){
		return false;
	}

	std::vector<std::function<void(Ref*)>> functions;
	cocos2d::Vector<Button*> buttons;

	initFunctions(functions);
	//inserta los botones a la escena
	initButtons(buttons, functions);

	//mira los niveles que estan disponibles
	for (int i = 0; i < NUM_LEVELS; i++){
		if (i>GameManager::getInstance()->getNextLevel()) break;
		//habilita el boton
		buttons.at(i)->setEnabled(true);
		//muestra la imagen de boton habilitado
		buttons.at(i)->setBright(true);
	}

	//crear boton de volver
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
			//deshabilit
			bt->setEnabled(false);
			//muestra imagen de boton deshabilitado
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


