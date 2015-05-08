#include "Background.h"

using namespace cocos2d;

Background::Background() :_speed(150){
	_screen = Director::getInstance()->getVisibleSize();
	_bgPart1 = Sprite::create("fondo.png");
	_bgPart2 = Sprite::create("fondo.png");
	_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
	_bgPart2->setPosition(_screen.width*0.5, _screen.height*0.5 + _screen.height);
	addChild(_bgPart1);
	addChild(_bgPart2);
}


void Background::update(float dt){
	Background::_bgPart1->setPositionY(_bgPart1->getPositionY() - _speed*dt);
	Background::_bgPart2->setPositionY(_bgPart2->getPositionY() - _speed*dt);
	if (_bgPart1->getPositionY() <= -(_screen.height*0.5)){
		_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
		_bgPart2->setPosition(_screen.width*0.5, _screen.height*0.5 + _screen.height);
	}
}

Background::~Background()
{
}
