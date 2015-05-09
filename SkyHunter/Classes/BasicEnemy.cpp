#include "BasicEnemy.h"


USING_NS_CC;

BasicEnemy::BasicEnemy() :_speed(150)
{
}


bool BasicEnemy::init(){
	//superclass first
	if (!Sprite::init())
	{
		return false;
	}

	_currentAnimation = IDLE;
	createIdleAnimation();

	createExplosionAnimation();

	//start the initial animation
	runAction(_idleAnimation);
}

void BasicEnemy::createIdleAnimation(){
	//create animation pool
	Vector<SpriteFrame*> animFrames;
	auto acc = 0;
	for (int i = 0; i < 4; i++){
		auto frame = SpriteFrame::create("animacion_enemigo.png", Rect(acc, 0, 50, 50));
		acc += 50;
		animFrames.pushBack(frame);
	}
	//set base sprite before run anything
	this->setSpriteFrame(animFrames.at(0));

	//create the animation with a deley of 0.25 ms between images
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.25f);

	//create the action of animate with the previous animation
	auto animate = Animate::create(animation);

	//set the periodicity of reproduction
	_idleAnimation = RepeatForever::create(animate);

	//put a tag on the animation in oreder to identify and stop it in the future
	_idleAnimation->setTag(BasicEnemy::Animations::IDLE);
}

void BasicEnemy::createExplosionAnimation(){
	//create animation pool
	Vector<SpriteFrame*> animFrames;
	auto acc = 0;
	for (int i = 0; i < 4; i++){
		auto frame = SpriteFrame::create("animacion_enemigo_explotar.png", Rect(acc, 0, 50, 50));
		acc += 50;
		animFrames.pushBack(frame);
	}

	//create the animation with a deley of 0.15 ms between images
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.15f);

	//create the action of animate with the previous animation,
	//the default perodicity for an animate object is 1
	_explosionAnimation = Animate::create(animation);;

	//put a tag on the animation in oreder to identify and stop it in the future
	_explosionAnimation->setTag(BasicEnemy::Animations::EXPLOSION);
}


BasicEnemy::~BasicEnemy()
{
}


void BasicEnemy::update(float dt){

}





