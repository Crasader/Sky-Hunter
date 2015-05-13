#include "Bullet.h"
#include "Player.h"
#include "BasicEnemy.h"

USING_NS_CC;

bool Bullet::initWithFile(const std::string& filename){

	if (!Sprite::initWithFile(filename)){
		return false;
	}
	_enemyTarget = nullptr;
	_speed = 160;
	//invisible by default
	setVisible(false);
	schedule(schedule_selector(Bullet::update));
	return true;
}


Bullet* Bullet::createPlayerBullet(){
	Bullet *sprite = new (std::nothrow) Bullet();
	if (sprite && sprite->initWithFile("disparo_nave.png"))
	{
		sprite->_type = PLAYER_BULLET;
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Bullet* Bullet::createEnemyBullet(){
	Bullet *sprite = new (std::nothrow) Bullet();
	if (sprite && sprite->initWithFile("disparo_enemigo.png"))
	{
		sprite->_type = ENEMY_BULLET;
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Bullet::update(float dt){
	if (!this->isVisible()) return;

	if (_type == PLAYER_BULLET){
		//go up 
		setAnchorPoint(Point(0.5, 0));
		setPosition(getPositionX(), getPositionY() + _speed*dt);
		if (getPositionY() > Director::getInstance()->getVisibleSize().height){
			setVisible(false);
		}
		for (int i = 0; i < _playerTargets.size(); i++){
			BasicEnemy* enemy = _playerTargets.at(i);
			if (getBoundingBox().intersectsRect(enemy->getBoundingBox()) && enemy->isVisible() 
				&& enemy->getCurrentAnimation() != BasicEnemy::Animations::EXPLOSION){
				//colision
				enemy->setCurrentAnimation(BasicEnemy::Animations::EXPLOSION);
				setVisible(false);
			}
		}
	}
	else if (_type == ENEMY_BULLET){
		//go down 
		setAnchorPoint(Point(0.5, 1));
		setPosition(getPositionX(), getPositionY() - _speed*dt);
		if (getPositionY() < 0){
			setVisible(false);
		}

		if (getBoundingBox().intersectsRect(_enemyTarget->getBoundingBox()) && 
			_enemyTarget->isVisible() && _enemyTarget->getCurrentAnimation() != BasicEnemy::Animations::EXPLOSION){
			//colision
			_enemyTarget->setCurrentAnimation(Player::Animations::EXPLOSION);
			setVisible(false);
		}

	}
}