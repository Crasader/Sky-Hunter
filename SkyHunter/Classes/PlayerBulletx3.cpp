#include "PlayerBulletx3.h"



USING_NS_CC;

bool PlayerBulletx3::init(){

	if (!PlayerBullet::init()){
		return false;
	}

	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("white_laser"));
	_damage = 3;
	_speed = 160;
	//invisible by default
	setVisible(false);
	schedule(schedule_selector(PlayerBulletx3::update));
	return true;
}