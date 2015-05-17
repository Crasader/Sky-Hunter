#include "Bullet.h"
#include "Player.h"
#include "BasicEnemy.h"
#include "AudioEngine.h"
#include "GameManager.h"




USING_NS_CC;

bool Bullet::init(){

	if (!Sprite::init()){
		return false;
	}
	if (_type == ENEMY_BULLET){
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("disparo_enemigo"));
	}
	else
	{
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("disparo_nave"));
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
	sprite->_type = PLAYER_BULLET;
	if (sprite && sprite->init())
	{
		
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Bullet* Bullet::createEnemyBullet(){
	Bullet *sprite = new (std::nothrow) Bullet();
	sprite->_type = ENEMY_BULLET;
	if (sprite && sprite->init())
	{
		
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
				GameManager::getInstance()->setPlayerScore(GameManager::getInstance()->getPlayerScore()+10);
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
			_enemyTarget->isVisible() && _enemyTarget->getCurrentAnimation() != Player::Animations::EXPLOSION){
			//colision
			 experimental::AudioEngine::play2d("music/hit.mp3", false, GameManager::getInstance()->getEffectsVolume()*0.01);
			_enemyTarget->setHealth(_enemyTarget->getHealth() - 1);
			_enemyTarget->runHitEffect();
			setVisible(false);
		}

	}
}