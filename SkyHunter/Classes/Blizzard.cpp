#include "Blizzard.h"

using namespace cocos2d;
using namespace Components;

bool Blizzard::init(){
	if (!Node::init())
	{
		return false;
	}
	_initialized = false;
	_speed = 150;
	_visibleSize = Director::getInstance()->getVisibleSize();
	_maxSnowParticles = 40;
	_snowIndex = 0;
	for (int i = 0; i < _maxSnowParticles; i++){
		auto particle = ParticleSystemQuad::create("snow.plist");
		particle->setScale(0.1f*getScale());
		_snow.pushBack(particle);
		particle->stopSystem();
		particle->setVisible(false);
		addChild(particle);
	}
	scheduleBlizzard();
	schedule(schedule_selector(Blizzard::update));
	return true;
}



void Blizzard::update(float dt){
	for (ParticleSystemQuad* particle : _snow)
	{
		if (particle->isVisible()){
			particle->setPositionY(particle->getPositionY() - _speed*dt);
			if (particle->getPositionY() <= -particle->getBoundingBox().size.height){
				particle->stopSystem();
				particle->setVisible(false);
			}
		}
	}
}

void Blizzard::scheduleBlizzard()
{
	//velocidad de los copos de nieve
	DelayTime *delayAction = DelayTime::create(0.1f);
	// coloca los copos de forma aletoria
	CallFunc *callPositioning = CallFunc::create(CC_CALLBACK_0(Blizzard::positioningParticle, this));
	auto awakeEnemySequence = Sequence::create(callPositioning, delayAction, NULL);

	runAction(RepeatForever::create(awakeEnemySequence));
}

void Blizzard::positioningParticle(){
	_snowIndex = _snowIndex % _maxSnowParticles;

	auto particle = _snow.at(_snowIndex);
	
	auto size = particle->getBoundingBox().size;
	//Posicionado de los copos de nieve
	particle->setPositionX(RandomHelper::random_int(static_cast<int>(size.width * 0.5),
		static_cast<int>(_visibleSize.width - size.width * 0.5)));
	particle->setPositionY(_visibleSize.height + size.height * 0.5);
	particle->setVisible(true);
	particle->resetSystem();

	_snowIndex++;
}

