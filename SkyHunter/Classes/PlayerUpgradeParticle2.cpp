#include "PlayerUpgradeParticle2.h"


USING_NS_CC;
using namespace Components;
using namespace Actors;

bool PlayerUpgradeParticle2::init()
{
	if (!Node::init()){
		return false;
	}
	_target = nullptr;
	_initialized = false;
	_speed = 100;
	_particle = ParticleSystemQuad::create("shootx3.plist");
	_particle->setLife(0.2f);
	_particle->setScale(getScale()*0.2f);
	setVisible(false);
	_particle->setPosition(Point(0, 0));
	addChild(_particle);
	scheduleUpdate();
	return true;
}


PlayerBullet* PlayerUpgradeParticle2::createBullet(){
	auto bullet = PlayerBulletx3::create();
	return bullet;
}
