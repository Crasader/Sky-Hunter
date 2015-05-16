#include "Player.h"
#include "Bullet.h"
#include "BasicEnemy.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

USING_NS_CC;


Player::Player() :_speed(150),
_numBullets(30),
_bulletIndex(0),
_health(MAX_HEALTH),
_initialiced(false)
{
}

Player::~Player()
{
	CC_SAFE_RELEASE(_idleAnimation);
	CC_SAFE_RELEASE(_explosionAnimation);
	CC_SAFE_RELEASE(_shoot);
}


bool Player::init(){
	//superclass first
	if (!Sprite::init())
	{
		return false;
	}


	for (int i = 0; i < _numBullets; i++){
		_bulletPool.pushBack(Bullet::createPlayerBullet());
	}

	_currentAnimation = IDLE;

	_controller = TouchController::create();
	addChild(_controller);

	createIdleAnimation();

	createExplosionAnimation();

	//start the initial animation
	runAction(_idleAnimation);

	Player::_hitEffect = ParticleSystemQuad::create("impact.plist");
	_hitEffect->stopSystem();
	_hitEffect -> setScale(0.1 );
	_hitEffect->setVisible(false);
	
	scheduleShoot();
	return true;

}


void Player::setHealth(int health){
	_health = health;
	if (_health <= 0){
		_health = 0;
	}
	if (_health >= MAX_HEALTH){
		_health = MAX_HEALTH;
	}
}

void Player::setVisible(bool visible){
	Sprite::setVisible(visible);
	if (visible){
		runAction(_shoot);
	}
	else{
		stopActionByTag(SHOOT_TAG);
	}
}

void Player::setTargets(cocos2d::Vector<BasicEnemy*>& targets){
	_targets = targets;
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.at(i)->setPlayerTargets(_targets);
	}
}


void Player::setParent(Node* parent){
	Sprite::setParent(parent);

	//prevent the bullet to been added more than once to the scene
	if (!_initialiced){
		for (int i = 0; i < _numBullets; i++){
			//add bullets to parent, in this case is GameLayer.
			getParent()->addChild(_bulletPool.at(i));
		}
		getParent()->getParent()->addChild(_hitEffect);
		_initialiced = true;
	}

}

void Player::scheduleShoot(){

	// set up the time delay
	DelayTime *delayAction = DelayTime::create(0.5f);

	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Player::shoot, this));
	auto shootSequence = Sequence::create(delayAction, callSelectorAction, NULL);

	_shoot = RepeatForever::create(shootSequence);
	_shoot->setTag(SHOOT_TAG);
	// run the action all the time
	runAction(_shoot);
}

void Player::createIdleAnimation(){
	//create animation pool
	Animation* animation = animation = Animation::create();
	std::string name = "";
	std::ostringstream ostr;
	for (int i = 0; i < 4; i++){
		name.append("player");
		ostr << i;
		name.append(ostr.str());
		ostr.str("");
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
		name = "";
	}
	//set base sprite before run anything
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player0"));
	//create the animation with a deley of 0.25 ms between images
	animation->setDelayPerUnit(0.25f);

	//create the action of animate with the previous animation
	auto animate = Animate::create(animation);

	//set the periodicity of reproduction
	_idleAnimation = RepeatForever::create(animate);

	//put a tag on the animation in order to identify and stop it in the future
	_idleAnimation->setTag(Player::Animations::IDLE);

	//preserve for future uses
	_idleAnimation->retain();
}

void Player::createExplosionAnimation(){
	//create animation pool
	Animation* animation = animation = Animation::create();
	std::string name = "";
	std::ostringstream ostr;
	for (int i = 0; i < 4; i++){
		name.append("player_explosion");
		ostr << i;
		name.append(ostr.str());
		ostr.str("");
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
		name = "";
	}

	//create the animation with a deley of 0.15 ms between images
	animation->setDelayPerUnit(0.15f);

	//create the action of animate with the previous animation,
	//the default perodicity for an animate object is 1
	_explosionAnimation = Animate::create(animation);

	//put a tag on the animation in oreder to identify and stop it in the future
	_explosionAnimation->setTag(Player::Animations::EXPLOSION);
	_explosionAnimation->retain();
}

void Player::setCurrentAnimation(Animations anim){
	if (_currentAnimation == anim) return;
	_currentAnimation = anim;
	if (_currentAnimation == IDLE){
		stopActionByTag(EXPLOSION);
		runAction(_idleAnimation);
	}
	if (_currentAnimation == EXPLOSION){
		stopActionByTag(IDLE);
		SimpleAudioEngine::getInstance()->playEffect("music/explosion.mp3");
		runAction(_explosionAnimation);
	}
}

void Player::update(float dt){
	//si la nave es destruida no podra moverse y dejara de verse tras explotar 
	if (_currentAnimation == EXPLOSION){
		stopActionByTag(SHOOT_TAG);
		if (_explosionAnimation->isDone() && isVisible()){
			setVisible(false);
		}
		return;
	}

	if (_health <= 0){
		setCurrentAnimation(EXPLOSION);
	}

	//mover la nave a donde el controlador indique
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

void Player::shoot(){
	_bulletIndex = _bulletIndex % _numBullets;
	auto bullet = _bulletPool.at(_bulletIndex);
	bullet->setAnchorPoint(Point(0.5, 0));
	if (!bullet->isVisible()){
		bullet->setPosition(getPositionX(), getPositionY() + getBoundingBox().size.height*0.5);
		SimpleAudioEngine::getInstance()->playEffect("music/laser_shoot.wav");
		bullet->setVisible(true);
	}
	_bulletIndex++;
}



