#include "PlayerBullet.h"
#include "AudioEngine.h"
#include "GameManager.h"

USING_NS_CC;

bool PlayerBullet::init(){

	if (!Sprite::init()){
		return false;
	}

	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("disparo_nave"));
	_damage = 1;
	_speed = 160;
	//invisible by default
	setVisible(false);
	schedule(schedule_selector(PlayerBullet::update));
	return true;
}

void PlayerBullet::update(float dt){
	if (!this->isVisible()) return;
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
			enemy->setHealth(enemy->getHealth() - _damage);
			GameManager::getInstance()->setPlayerScore(GameManager::getInstance()->getPlayerScore()+
				enemy->getValue());
			setVisible(false);
		}
	}
}

void PlayerBullet::playShootSound(){
	experimental::AudioEngine::play2d("music/laser_shoot.mp3", false, GameManager::getInstance()->getEffectsVolume()*0.01);
}