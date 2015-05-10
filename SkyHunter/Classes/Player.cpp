#include "Player.h"


USING_NS_CC;


Player::Player() :_speed(150)
{
}


bool Player::init(){
	//superclass first
	if (!Sprite::init())
	{
		return false;
	}

	_currentAnimation = IDLE;

	_controller = TouchController::create();
	addChild(_controller);

	createIdleAnimation();

	createExplosionAnimation();

	//start the initial animation
	runAction(_idleAnimation);
}

void Player::createIdleAnimation(){
	//create animation pool
	Vector<SpriteFrame*> animFrames;
	auto acc = 0;
	for (int i = 0; i < 4; i++){
		auto frame = SpriteFrame::create("animacion_nave.png", Rect(acc, 0, 50, 63));
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
	_idleAnimation->setTag(Player::Animations::IDLE);
}

void Player::createExplosionAnimation(){
	//create animation pool
	Vector<SpriteFrame*> animFrames;
	auto acc = 0;
	for (int i = 0; i < 4; i++){
		auto frame = SpriteFrame::create("player_explosion.png", Rect(acc, 0, 50, 63));
		acc += 50;
		animFrames.pushBack(frame);
	}

	//create the animation with a deley of 0.15 s between images
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.15f);

	//create the action of animate with the previous animation,
	//the default perodicity for an animate object is 1
	_explosionAnimation = Animate::create(animation);

	//put a tag on the animation in oreder to identify and stop it in the future
	_explosionAnimation->setTag(Player::Animations::EXPLOSION);
}


Player::~Player()
{

}


void Player::update(float dt){
	float speed = _speed*dt;
	auto controller = _controller->getController();
	if (controller.upRight){
		setPosition(getPositionX() + speed, getPositionY() + speed);
	}
	else if (controller.upLeft){
		setPosition(getPositionX() - speed, getPositionY() + speed);
	}
	else if (controller.downRight){
		setPosition(getPositionX() + speed, getPositionY() - speed);
	}
	else if (controller.downLeft){
		setPosition(getPositionX() - speed, getPositionY() - speed);
	}
	else if (controller.left){
		setPositionX(getPositionX() - speed);
	}
	else if (controller.right){
		setPositionX(getPositionX() + speed);
	}
	else if (controller.down){
		setPositionY(getPositionY() - speed);
	}
	else if (controller.up){
		setPositionY(getPositionY() + speed);
	}
}




