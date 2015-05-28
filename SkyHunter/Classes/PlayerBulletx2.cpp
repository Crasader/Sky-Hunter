#include "PlayerBulletx2.h"


USING_NS_CC;

bool PlayerBulletx2::init(){

	if (!PlayerBullet::init()){
		return false;
	}

	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("red_laser"));
	_damage = 2;
	_speed = 170;
	//invisible by default
	setVisible(false);
	schedule(schedule_selector(PlayerBulletx2::update));
	return true;
}

