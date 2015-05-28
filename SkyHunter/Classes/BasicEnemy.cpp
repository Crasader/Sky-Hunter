#include "BasicEnemy.h"
#include "Player.h"
#include "CustomAudioManager.h"
#include "GameManager.h"

USING_NS_CC;



BasicEnemy::BasicEnemy() :
_speed(100),
_numBullets(10),
_bulletIndex(0),
_initialiced(false)
{
	ENEMY_HEALTH = 1;
	_health = ENEMY_HEALTH;
	_currentAnimation = IDLE;
	_value = 10;
	_shootFrequencySeconds = 1.0f;
}


bool BasicEnemy::init(){
	//superclass first
	if (!Sprite::init())
	{
		return false;
	}

	createBullets();
	createIdleAnimation("enemy",4);
	createExplosionAnimation("enemy_explosion",6);

	//start the initial animation
	runAction(_idleAnimation);
	scheduleShoot();
	scheduleUpdate();
	setVisible(false);
	return true;
}

void BasicEnemy::createBullets(){
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.pushBack(EnemyBullet::create());
	}
}

void BasicEnemy::reset(){
	setVisible(false);
	setCurrentAnimation(IDLE);
	for (EnemyBullet* bullet : _bulletPool){
		bullet->setVisible(false);
	}
}

void BasicEnemy::scheduleShoot(){

	// set up the time delay
	DelayTime *delayAction = DelayTime::create(_shootFrequencySeconds);

	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(BasicEnemy::shoot, this));
	auto shootSequence = Sequence::create(delayAction,callSelectorAction, NULL);
	_shoot = RepeatForever::create(shootSequence);
	_shoot->setTag(SHOOT_TAG);
	_shoot->retain();

	// run the action all the time
	runAction(_shoot);
}

void BasicEnemy::pause(){
	Sprite::pause();
	for (EnemyBullet* node : _bulletPool){
		node->pause();
	}
}

void BasicEnemy::resume(){
	Sprite::resume();
	for (EnemyBullet* node : _bulletPool){
		node->resume();
	}
}

void BasicEnemy::setTarget(Player* target) {
	_target = target;
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.at(i)->setEnemyTarget(_target);
	}
}

void BasicEnemy::shoot(){
	_bulletIndex = _bulletIndex % _numBullets;
	auto bullet = _bulletPool.at(_bulletIndex);
	bullet->setAnchorPoint(Point(0.5, 1));
	if (!bullet->isVisible()){
		bullet->setPosition(getPositionX(), getPositionY() - getBoundingBox().size.height*0.5);
		bullet->setVisible(true);
	}
	_bulletIndex++;
}

void BasicEnemy::setCurrentAnimation(Animations anim){
	if (_currentAnimation == anim) return;
	_currentAnimation = anim;
	if (_currentAnimation == IDLE){
		stopActionByTag(EXPLOSION);
		runAction(_idleAnimation);
	}
	if (_currentAnimation == EXPLOSION){
		stopActionByTag(IDLE);
		CustomAudioManager::getInstance()->playEffect("music/explosion.wav", false);
		runAction(_explosionAnimation);
	}
}

void BasicEnemy::setParent(Node* parent){
	//prevent the bullet to been added more than once to the scene
	if (!_initialiced){
		for (int i = 0; i < _numBullets; i++){
			//add bullets to parent, in this case is GameLayer.
			parent->addChild(_bulletPool.at(i),getLocalZOrder());
		}
		_initialiced = true;
	}
	Sprite::setParent(parent);
}

void BasicEnemy::createIdleAnimation(std::string spriteName, int numberOfFrames){
	//create animation pool
	Animation* animation = animation = Animation::create();
	std::string name = "";
	std::ostringstream ostr;
	for (int i = 0; i < numberOfFrames; i++){
		name.append(spriteName);
		ostr << i;
		name.append(ostr.str());
		ostr.str("");
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
		name = "";
	}
	//set base sprite before run anything
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0"));
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

void BasicEnemy::createExplosionAnimation(std::string spriteName, int numberOfFrames){
	//create animation pool
	Animation* animation = animation = Animation::create();
	std::string name = "";
	std::ostringstream ostr;
	for (int i = 0; i < numberOfFrames; i++){
		name.append(spriteName);
		ostr << i;
		name.append(ostr.str());
		ostr.str("");
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animation->addSpriteFrame(frame);
		name = "";
	}

	//create the animation with a deley of 0.15 ms between images
	animation->setDelayPerUnit(0.1f);

	//create the action of animate with the previous animation,
	//the default perodicity for an animate object is 1
	_explosionAnimation = Animate::create(animation);

	//put a tag on the animation in oreder to identify and stop it in the future
	_explosionAnimation->setTag(Player::Animations::EXPLOSION);
	_explosionAnimation->retain();
}

void BasicEnemy::setVisible(bool visible){
	Sprite::setVisible(visible);
	if (visible){
		setHealth(ENEMY_HEALTH);
		runAction(_shoot);
	}
	else{
		stopActionByTag(SHOOT_TAG);
	}
}


void BasicEnemy::update(float dt){
	if (!isVisible()) return;

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

	behaviour(dt);
}

void BasicEnemy::behaviour(float dt){
	//go down 
	setAnchorPoint(Point(0.5, 1));
	setPosition(getPositionX(), getPositionY() - _speed*dt);
	if (getPositionY() < 0){
		setVisible(false);
	}
}





