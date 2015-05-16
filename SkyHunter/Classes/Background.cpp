#include "Background.h"

using namespace cocos2d;

Background::Background() :_speed(150), _initialiced(false){
	_screen = Director::getInstance()->getVisibleSize();
	_bgPart1 = Sprite::createWithSpriteFrameName("fondo");
	_bgPart1->retain();
	_bgPart2 = Sprite::createWithSpriteFrameName("fondo");
	_bgPart2->retain();
	_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
	_bgPart2->setPosition(_screen.width*0.5, _screen.height*0.5 + _screen.height - 1);
}

void Background::setSptitePart1(std::string part1){
	CC_SAFE_RELEASE(_bgPart1);
	_bgPart1 = Sprite::createWithSpriteFrameName(part1);
	_bgPart1->retain();

}
void Background::setSptitePart2(std::string part2){
	CC_SAFE_RELEASE(_bgPart2);
	_bgPart2 = Sprite::createWithSpriteFrameName(part2);
	_bgPart2->retain();
}

void Background::setParent(Node* parent){
	//prevent the bq to bee added more than once to the scene
	if (!_initialiced){
		parent->addChild(_bgPart1);
		parent->addChild(_bgPart2);
		_initialiced = true;
	}

}



void Background::update(float dt){
	_bgPart1->setPositionY(_bgPart1->getPositionY() - _speed*dt);
	_bgPart2->setPositionY(_bgPart2->getPositionY() - _speed*dt);
	if (_bgPart1->getPositionY() <= -(_screen.height*0.5)){
		_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
		_bgPart2->setPosition(_screen.width*0.5, _screen.height*0.5 + _screen.height - 1);
	}
}

Background::~Background()
{
	_bgPart1->release();
	_bgPart2->release();
}
