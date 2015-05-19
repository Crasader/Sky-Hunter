#include "OptionsLayer.h"
#include "GameManager.h"
#include "MainMenuLayer.h"

USING_NS_CC;
using namespace ui;


Scene* OptionsLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OptionsLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool OptionsLayer::init(){
	if (!BaseMenuLayer::init()){
		return false;
	}
	int marginX = 50 * getScaleX();
	int marginY = _visibleSize.height - 100 * getScaleY();


	//Background volumen options Componentes
	_backGroundVolumeLabel = Label::createWithTTF("0", "fonts/arial.ttf", 16);
	_backGroundVolumeLabel->setAnchorPoint(Point(0, 1));
	_backGroundVolumeLabel->setTextColor(Color4B::BLACK);
	_ostr << GameManager::getInstance()->getBgVolume();
	_backGroundVolumeLabel->setString("Background volume: " + _ostr.str());
	_ostr.str("");
	_backGroundVolumeLabel->setPosition(Point(marginX, marginY));
	addChild(_backGroundVolumeLabel);


	_backGroundVolume = Slider::create();
	_backGroundVolume->loadBarTexture("Slider_Back", Widget::TextureResType::PLIST);
	_backGroundVolume->loadSlidBallTextures("SliderNode_Normal", "SliderNode_Press", "SliderNode_Disable", Widget::TextureResType::PLIST);
	_backGroundVolume->loadProgressBarTexture("Slider_PressBar", Widget::TextureResType::PLIST);
	_backGroundVolume->setAnchorPoint(Point(0, 1));
	marginY -= 5 * getScaleY() + _backGroundVolumeLabel->getBoundingBox().size.height;
	_backGroundVolume->setPosition(Point(marginX, marginY));
	_backGroundVolume->setPercent(GameManager::getInstance()->getBgVolume());
	_backGroundVolume->addEventListener(CC_CALLBACK_0(OptionsLayer::actionBackGroundVolumeSlider, this));
	addChild(_backGroundVolume);

	//Effects volumen options Componentes
	_effectsVolumeLabel = Label::createWithTTF("0", "fonts/arial.ttf", 16);
	_ostr << GameManager::getInstance()->getEffectsVolume();
	_effectsVolumeLabel->setString("Effects volume: " + _ostr.str());
	_ostr.str("");
	_effectsVolumeLabel->setTextColor(Color4B::BLACK);
	_effectsVolumeLabel->setAnchorPoint(Point(0, 1));
	marginY -= 50 * getScaleY() + _backGroundVolume->getBoundingBox().size.height;
	_effectsVolumeLabel->setPosition(Point(marginX, marginY));
	addChild(_effectsVolumeLabel);


	_effectsVolume = Slider::create();
	_effectsVolume->loadBarTexture("Slider_Back", Widget::TextureResType::PLIST);
	_effectsVolume->loadSlidBallTextures("SliderNode_Normal", "SliderNode_Press", "SliderNode_Disable", Widget::TextureResType::PLIST);
	_effectsVolume->loadProgressBarTexture("Slider_PressBar", Widget::TextureResType::PLIST);
	_effectsVolume->setAnchorPoint(Point(0, 1));
	marginY -= 5 * getScaleY() + _effectsVolumeLabel->getBoundingBox().size.height;
	_effectsVolume->setPosition(Point(marginX, marginY));
	_effectsVolume->setPercent(GameManager::getInstance()->getEffectsVolume());
	_effectsVolume->addEventListener(CC_CALLBACK_0(OptionsLayer::actionEffectsVolumeSlider, this));
	addChild(_effectsVolume);



	//crete back button
	auto backBt = Button::create("back0", "back1", "back1", Widget::TextureResType::PLIST);
	backBt->setAnchorPoint(Point(0, 0.5));
	backBt->addClickEventListener(CC_CALLBACK_0(OptionsLayer::actionButtonBack, this));
	backBt->setPosition(Point(42.5* getScaleX(), 50 * getScaleY()));
	addChild(backBt);
	return true;
}

void OptionsLayer::actionBackGroundVolumeSlider(){
	_ostr << _backGroundVolume->getPercent();
	_backGroundVolumeLabel->setString("Background volume: " + _ostr.str());
	_ostr.str("");
	GameManager::getInstance()->setBgVolume(_backGroundVolume->getPercent());
}
void OptionsLayer::actionEffectsVolumeSlider(){
	_ostr << _effectsVolume->getPercent();
	_effectsVolumeLabel->setString("Effects volume: " + _ostr.str());
	_ostr.str("");
	GameManager::getInstance()->setEffectsVolume(_effectsVolume->getPercent());
}

void OptionsLayer::actionButtonBack()
{
	GameManager::getInstance()->saveSetting();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, MainMenuLayer::createScene()));
}

