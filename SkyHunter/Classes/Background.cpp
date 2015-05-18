#include "Background.h"

using namespace cocos2d;

Background::Background() :_speed(150), _initialiced(false){
	_screen = Director::getInstance()->getVisibleSize();
	_bgPart1 = Sprite::createWithSpriteFrameName("fondo");
	_bgPart2 = Sprite::createWithSpriteFrameName("fondo");
	_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
	_bgPart2->setPosition(_screen.width*0.5, _screen.height*0.5 + _screen.height - 1);
}

void Background::setSptitePart1(std::string part1){
	_bgPart1 = Sprite::createWithSpriteFrameName(part1);

}
void Background::setSptitePart2(std::string part2){
	_bgPart2 = Sprite::createWithSpriteFrameName(part2);
}

void Background::setParent(Node* parent,int pos){
	//prevent the bq to bee added more than once to the scene
	if (!_initialiced){
		parent->addChild(_bgPart1, pos);
		parent->addChild(_bgPart2, pos);
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
}
