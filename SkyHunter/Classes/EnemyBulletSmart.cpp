#include "EnemyBulletSmart.h"
#include "Player.h"


USING_NS_CC;
using namespace Actors;

bool Actors::EnemyBulletSmart::init(){
	if (!Sprite::init()){
		return false;
	}
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("disparo_persecutor"));
	_enemyTarget = nullptr;
	_speed = 130;
	

	setVisible(false);
	schedule(schedule_selector(EnemyBullet::update));
	return true;
}



void Actors::EnemyBulletSmart::update(float dt){
	if (!this->isVisible()) return;
	//para abajo 
	setRotation(getRotation() + 360 / 0.5 * dt);
	if (getPositionY()+getBoundingBox().size.height*0.5 < 0){
		setVisible(false);
	}

	if (getBoundingBox().intersectsRect(_enemyTarget->getBoundingBox()) &&
		_enemyTarget->isVisible() && _enemyTarget->getCurrentAnimation() != Player::Animations::EXPLOSION){
		//colision	
		_enemyTarget->setHealth(_enemyTarget->getHealth() - 1);
		_enemyTarget->runHitEffect();
		setVisible(false);
	}
}



void Actors::EnemyBulletSmart::setVisible(bool visible)
{
	Sprite::setVisible(visible);
	if (visible){
		_targetPosition = _enemyTarget->getPosition();
		if (getPositionY() < _targetPosition.y || !_enemyTarget->isVisible()){
			_targetPosition = getPosition();
		}
		auto moveTo = MoveTo::create(3, Point(_targetPosition.x, 0 - getBoundingBox().size.height));
		moveTo->setTag(0);
		runAction(moveTo);
	}
	else{
		stopActionByTag(0);
	}
}
