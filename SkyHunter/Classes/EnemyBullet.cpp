#include "EnemyBullet.h"
#include "Player.h"


USING_NS_CC;

bool EnemyBullet::init(){
	if (!Sprite::init()){
		return false;
	}
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("disparo_enemigo"));
	_enemyTarget = nullptr;
	_speed = 160;
	//invisible by default
	setVisible(false);
	schedule(schedule_selector(EnemyBullet::update));
	return true;
}



void EnemyBullet::update(float dt){
	if (!this->isVisible()) return;
	//go down 
	setAnchorPoint(Point(0.5, 1));
	setPosition(getPositionX(), getPositionY() - _speed*dt);
	if (getPositionY() < 0){
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
