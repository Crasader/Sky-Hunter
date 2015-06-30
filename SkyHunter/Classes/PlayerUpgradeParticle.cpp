#include "PlayerUpgradeParticle.h"

USING_NS_CC;
using namespace Components;
using namespace Actors;

bool PlayerUpgradeParticle::init()
{
	if (!Node::init()){
		return false;
	}
	_target = nullptr;
	_initialized = false;
	_speed = 100;
	_particle = ParticleSystemQuad::create("shootx2.plist");
	_particle->setLife(0.2f);
	_particle->setScale(getScale()*0.2f);
	setVisible(false);
	_particle->setPosition(Point(0, 0));
	addChild(_particle);
	scheduleUpdate();
	return true;
}

void PlayerUpgradeParticle::update(float dt)
{
	if (!isVisible()) return;
	//para abajo
	setAnchorPoint(Point(0.5, 1));
	setPosition(getPositionX(), getPositionY() - _speed*dt);
	if (getPositionY() < 0){
		setVisible(false);
	}
	if (_target != nullptr && _target->getBoundingBox().intersectsRect(getBoundingBox())
		&& isVisible() && _target->isVisible() && _target->getCurrentAnimation() != Actors::Player::Animations::EXPLOSION)
	{
		//colision
		_target->updateBullets(CC_CALLBACK_0(PlayerUpgradeParticle::createBullet, this));
		setVisible(false);
	}
}


PlayerBullet* PlayerUpgradeParticle::createBullet(){
	auto bullet = PlayerBulletx2::create();
	return bullet;
}

void PlayerUpgradeParticle::setVisible(bool visible){
	Node::setVisible(visible);
	_particle->setVisible(visible);
	if (visible){
		_particle->resetSystem();
	}
	else
	{
		_particle->stopSystem();
	}
}
