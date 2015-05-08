#include "Player.h"

using namespace cocos2d;


Player::Player() :_speed(150)
{
	resetPlayerController();
	Vector<SpriteFrame*> animFrames;
	auto acc = 0;
	for (int i = 0; i < 4; i++){
		auto frame = SpriteFrame::create("animacion_nave.png", Rect(acc, 0, 50, 63));
		acc += 50;
		animFrames.pushBack(frame);
	}
	setTextureRect(Rect(0, 0, 50, 63));
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.25f);
	auto animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}


Player::~Player()
{
}

Player* Player::createPlayer(){
	Player *sprite = new (std::nothrow) Player();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Player::update(float dt){
	if (controller.upRight){
		setPosition(getPositionX() + _speed*dt, getPositionY() + _speed*dt);

	}else if (controller.upLeft){
		setPosition(getPositionX() - _speed*dt, getPositionY() + _speed*dt);
	}
	else if (controller.downRight){
		setPosition(getPositionX() + _speed*dt, getPositionY() - _speed*dt);
	}
	else if (controller.downLeft){
		setPosition(getPositionX() - _speed*dt, getPositionY() - _speed*dt);
	}
	else if (controller.left){
		setPositionX(getPositionX() - _speed*dt);
	}
	else if (controller.right){
		setPositionX(getPositionX() + _speed*dt);
	}
	else if (controller.down){
		setPositionY(getPositionY() - _speed*dt);
	}
	else if (controller.up){
		setPositionY(getPositionY() + _speed*dt);
	}
}

void Player::updateTouchController(const Point* tapInput){
	resetPlayerController();

	if (tapInput == nullptr) return;
	Point  tap = *tapInput;
	auto playerX = getPositionX() + getBoundingBox().size.width;
	auto playerY = getPositionY() + getBoundingBox().size.height;

	if (tap.x > playerX && tap.y > playerY){
		controller.upRight = true;
	}
	else if (tap.x < getPositionX() && tap.y> playerY){
		controller.upLeft = true;
	}
	else if (tap.x > playerX && tap.y < getPositionY()){
		controller.downRight = true;
	}
	else if (tap.x < getPositionX() && tap.y < getPositionY()){
		controller.downLeft = true;
	}
	else if (tap.x < getPositionX()){
		controller.left = true;
	}
	else if (tap.x > playerX){
		controller.right = true;
	}
	else if (tap.y < getPositionY()){
		controller.down = true;
	}
	else if (tap.y > playerY){
		controller.up = true;
	}
}

void inline Player::resetPlayerController(){
	controller.left = false;
	controller.right = false;
	controller.up = false;
	controller.upLeft = false;
	controller.upRight = false;
	controller.down = false;
	controller.downLeft = false;
	controller.downRight = false;
}
