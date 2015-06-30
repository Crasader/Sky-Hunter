#include "Cloud.h"

USING_NS_CC;
using namespace Components;
using namespace Actors;

bool Cloud::init(){
	if (!Sprite::init())
	{
		return false;
	}
	_speed = 30;
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tormenta"));
	setVisible(false);
	schedule(schedule_selector(Cloud::update));
	return true;
}

void Cloud::update(float dt){
	if(!isVisible())return;
	//baja solo si el jugador esta activo 
	//si no permanecen quietas.
	if (_target->isVisible()){
		setAnchorPoint(Point(0.5, 1));
		setPosition(getPositionX(), getPositionY() - _speed*dt);
		if (getPositionY() < 0){
			setVisible(false);
		}
	}

	if (getBoundingBox().intersectsRect(_target->getBoundingBox()) &&
		_target->isVisible() && _target->getCurrentAnimation() != Actors::Player::Animations::EXPLOSION){
		//colision	
		_target->setHealth(0);
	}

}
