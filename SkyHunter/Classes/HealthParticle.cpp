#include "HealthParticle.h"
#include "Player.h"

USING_NS_CC;
using namespace Components;
using namespace Actors;

bool HealthParticle::init()
{
	if (!Node::init()){
		return false;
	}
	_target = nullptr;
	_initialized = false;
	_speed = 100;
	_particle = ParticleSystemQuad::create("health_up.plist");

	_particle->setScale(getScale()*0.15f);
	setVisible(false);
	_particle->setPosition(Point(0, 0));
	addChild(_particle);
	scheduleUpdate();
	return true;
}

void HealthParticle::update(float dt)
{
	if (!isVisible()) return;
	//para abajo
	setAnchorPoint(Point(0.5, 1));
	setPosition(getPositionX(), getPositionY() - _speed*dt);
	if (getPositionY() < 0){
		setVisible(false);
	}
	if (_target != nullptr && _target->getBoundingBox().intersectsRect(getBoundingBox())
		&& isVisible() && _target->isVisible() && _target->getCurrentAnimation()!=Player::Animations::EXPLOSION)
	{
		//colision
		_target->setHealth(MAX_HEALTH);
		setVisible(false);
	}
}


void HealthParticle::setVisible(bool visible){
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
