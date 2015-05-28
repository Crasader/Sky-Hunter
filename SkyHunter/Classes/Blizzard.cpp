#include "Blizzard.h"

using namespace cocos2d;

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
		particle->stopSystem();
		particle->setVisible(false);
		_snow.pushBack(particle);
		addChild(particle);
	}
	scheduleBlizzard();
	schedule(schedule_selector(Blizzard::update));
}

void Blizzard::setParent(Node* parent){
	Node::setParent(parent);
	/*if (!_initialized){
		for (int i = 0; i < _maxSnowParticles; i++){
			_initialized = true;
			parent->addChild(_snow.at(i));
		}
	}*/
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
	//snow ratio
	DelayTime *delayAction = DelayTime::create(0.1f);
	// perform the selector call
	CallFunc *callPositioning = CallFunc::create(CC_CALLBACK_0(Blizzard::positioningParticle, this));
	auto awakeEnemySequence = Sequence::create(callPositioning, delayAction, NULL);
	// run the action all the time
	runAction(RepeatForever::create(awakeEnemySequence));
}

void Blizzard::positioningParticle(){
	_snowIndex = _snowIndex % _maxSnowParticles;

	auto particle = _snow.at(_snowIndex);
	
	auto size = particle->getBoundingBox().size;
	//Positioning
	particle->setPositionX(RandomHelper::random_int(static_cast<int>(size.width * 0.5),
		static_cast<int>(_visibleSize.width - size.width * 0.5)));
	particle->setPositionY(_visibleSize.height + size.height * 0.5);
	particle->setVisible(true);
	particle->resetSystem();

	_snowIndex++;
}

