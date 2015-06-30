#include "PlayerBullet.h"
#include "CustomAudioManager.h"
#include "GameManager.h"

USING_NS_CC;
using namespace Levels;

bool Actors::PlayerBullet::init(){

	if (!Sprite::init()){
		return false;
	}

	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("disparo_nave"));
	_damage = 1;
	_speed = 160;
	//invisible por defecto
	setVisible(false);
	schedule(schedule_selector(PlayerBullet::update));
	return true;
}

void Actors::PlayerBullet::update(float dt){
	if (!this->isVisible()) return;
	//para arriba
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
			auto heath = enemy->getHealth() - _damage;
			enemy->setHealth(heath);
			if (enemy->getHealth()<=0){
				GameManager::getInstance()->setPlayerScore(GameManager::getInstance()->getPlayerScore() +
					enemy->getValue());
			}
			setVisible(false);
		}
	}
}

void Actors::PlayerBullet::playShootSound(){
	CustomAudioManager::getInstance()->playEffect("music/laser_shoot.wav", false);
}