#include "Player.h"
#include "BasicEnemy.h"
#include "CustomAudioManager.h"
#include "GameManager.h"


USING_NS_CC;
using namespace Levels;


Actors::Player::Player() :_speed(150),
_numBullets(30),
_bulletIndex(0),
_health(MAX_HEALTH),
_initialiced(false)
{
}




bool Actors::Player::init(){

	if (!Sprite::init())
	{
		return false;
	}


	for (int i = 0; i < _numBullets; i++){
		_bulletPool.pushBack(PlayerBullet::create());
	}

	_currentAnimation = IDLE;

	_controller = TouchController::create();
	addChild(_controller);

	createIdleAnimation();
	createExplosionAnimation();

	//lanza la animación por defecto
	runAction(_idleAnimation);

	_hitEffect = ParticleSystemQuad::create("impact.plist");
	_hitEffect->stopSystem();
	_hitEffect->setScale(getScale()*0.25f);
	_hitEffect->setVisible(false);

	scheduleShoot();
	return true;

}

void Actors::Player::runHitEffect(){
	_hitEffect->setPositionX(getPositionX());
	_hitEffect->setPositionY(getPositionY() + getBoundingBox().size.height*0.5);
	_hitEffect->setVisible(true);
	_hitEffect->resetSystem();
	CustomAudioManager::getInstance()->playEffect("music/hit.wav", false);
}

void Actors::Player::updateBullets(const std::function<PlayerBullet*()>& create)
{
	stopActionByTag(SHOOT_TAG);
	for (int i = 0; i < _numBullets; i++){
		_parent->removeChild(_bulletPool.at(i), true);
		auto bullet = create();
		bullet->setPlayerTargets(_targets);
		_bulletPool.replace(i, bullet);
		_parent->addChild(_bulletPool.at(i), getLocalZOrder());
	}
	runAction(_shoot);
}


void Actors::Player::setHealth(int health){
	_health = health;
	if (_health <= 0){
		_health = 0;
	}
	if (_health >= MAX_HEALTH){
		_health = MAX_HEALTH;
	}
}

void Actors::Player::setVisible(bool visible){
	Sprite::setVisible(visible);
	if (!visible){
		runAction(_shoot);
	}
	else{
		stopActionByTag(SHOOT_TAG);
	}
}

void Actors::Player::pause(){
	Sprite::pause();
	for (Node* node : _bulletPool){
		node->pause();
	}
}

void Actors::Player::resume(){
	Sprite::resume();
	for (Node* node : _bulletPool){
		node->resume();
	}
}


void Actors::Player::setTargets(const  cocos2d::Vector<BasicEnemy*>& targets){
	_targets = targets;
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.at(i)->setPlayerTargets(_targets);
	}
}


void Actors::Player::setParent(Node* parent){
	_parent = parent;
	//impide que las balas se incorporen mas de una vez a la escena
	if (!_initialiced){
		for (int i = 0; i < _numBullets; i++){
			//incorporan las balas al la escena
			parent->addChild(_bulletPool.at(i), getLocalZOrder());
		}
		parent->getParent()->addChild(_hitEffect,getLocalZOrder());
		_initialiced = true;
	}
	Sprite::setParent(parent);
}


void Actors::Player::scheduleShoot(){
	//establecemos que la nave disparara cada medio segundo
	DelayTime *delayAction = DelayTime::create(0.5f);
	// creamos una accion a partir de una funcion
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Player::shoot, this));
	//creamos una secuencia que primero espera y luego dispara
	auto shootSequence = Sequence::create(delayAction, callSelectorAction, NULL);
	// envolvemos la secuencia un una accion RepeatForever
	_shoot = RepeatForever::create(shootSequence);
	_shoot->setTag(SHOOT_TAG);
	// le decimos a cocos que no elimine este objeto hasta que lo indiquemos o 
	//hasta que el objeto player se elimine
	_shoot->retain();
	runAction(_shoot);
}

void Actors::Player::reset(){

	if (!isVisible())
	{
		setVisible(true);
	}
	stopActionByTag(SHOOT_TAG);
	setHealth(MAX_HEALTH);
	setCurrentAnimation(Player::Animations::IDLE);
	for (int i = 0; i < _numBullets; i++){
		_parent->removeChild(_bulletPool.at(i), true);
		auto bullet = PlayerBullet::create();
		bullet->setPlayerTargets(_targets);
		_bulletPool.replace(i, bullet);
		_parent->addChild(_bulletPool.at(i), getLocalZOrder());
	}
	runAction(_shoot);


}

void Actors::Player::createIdleAnimation(){
	//creamos un pool de imagenes para la animacion
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
	//si ninguna animacion esta corriendo el esprite por defecto es definido aqui
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player0"));


	//creamos una animacion con un tiempo de espera entre cada frame de 0.25s
	animation->setDelayPerUnit(0.25f);

	//creamos la accion de animar el objeto animation
	auto animate = Animate::create(animation);

	//creamos una accion que repita para siempre la animacion
	_idleAnimation = RepeatForever::create(animate);

	//le ponemos un tag para poder pararlo en el futuro
	_idleAnimation->setTag(Player::Animations::IDLE);

	// le decimos a cocos que no elimine este objeto hasta que lo indiquemos o 
	//hasta que el objeto player se elimine
	_idleAnimation->retain();
}

void Actors::Player::createExplosionAnimation(){
	//mismo proceso que en createIdleAnimation
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
	animation->setDelayPerUnit(0.15f);
	_explosionAnimation = Animate::create(animation);
	_explosionAnimation->setTag(Player::Animations::EXPLOSION);
	_explosionAnimation->retain();
}

void Actors::Player::setCurrentAnimation(Animations anim){
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

void Actors::Player::update(float dt){
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

void Actors::Player::shoot(){
	_bulletIndex = _bulletIndex % _numBullets;
	auto bullet = _bulletPool.at(_bulletIndex);
	bullet->setAnchorPoint(Point(0.5, 0));
	if (!bullet->isVisible()){
		bullet->setPosition(getPositionX(), getPositionY() + getBoundingBox().size.height*0.5);
		bullet->playShootSound();
		bullet->setVisible(true);
	}
	_bulletIndex++;
}



