#include "BasicEnemy.h"
#include "Player.h"
#include "CustomAudioManager.h"
#include "GameManager.h"

USING_NS_CC;

using namespace Levels;




Actors::BasicEnemy::BasicEnemy() :
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


bool Actors::BasicEnemy::init(){
	if (!Sprite::init())
	{
		return false;
	}

	createBullets();
	createIdleAnimation("enemy",4);
	createExplosionAnimation("enemy_explosion",6);

	//lanza la animacion por defecto
	runAction(_idleAnimation);
	scheduleShoot();
	scheduleUpdate();
	setVisible(false);
	return true;
}

void Actors::BasicEnemy::createBullets(){
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.pushBack(EnemyBullet::create());
	}
}

void Actors::BasicEnemy::reset(){
	setVisible(false);
	setCurrentAnimation(IDLE);
	for (EnemyBullet* bullet : _bulletPool){
		bullet->setVisible(false);
	}
}

void Actors::BasicEnemy::scheduleShoot(){

	// establece el tiempo entre cada disparo
	DelayTime *delayAction = DelayTime::create(_shootFrequencySeconds);

	// llama al metodo que activa la bala
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(BasicEnemy::shoot, this));
	//crea la secuencia
	auto shootSequence = Sequence::create(delayAction,callSelectorAction, NULL);
	//envuelve la secuencia en un RepetForever
	_shoot = RepeatForever::create(shootSequence);
	_shoot->setTag(SHOOT_TAG);
	_shoot->retain();

	// lanza la accion
	runAction(_shoot);
}

void Actors::BasicEnemy::pause(){
	Sprite::pause();
	for (EnemyBullet* node : _bulletPool){
		node->pause();
	}
}

void Actors::BasicEnemy::resume(){
	Sprite::resume();
	for (EnemyBullet* node : _bulletPool){
		node->resume();
	}
}

void Actors::BasicEnemy::setTarget(Player* target) {
	for (int i = 0; i < _numBullets; i++){
		_bulletPool.at(i)->setEnemyTarget(target);
	}
}

void Actors::BasicEnemy::shoot(){
	_bulletIndex = _bulletIndex % _numBullets;
	auto bullet = _bulletPool.at(_bulletIndex);
	bullet->setAnchorPoint(Point(0.5, 1));
	if (!bullet->isVisible()){
		bullet->setPosition(getPositionX(), getPositionY() - getBoundingBox().size.height*0.5);
		bullet->setVisible(true);
	}
	_bulletIndex++;
}

void Actors::BasicEnemy::setCurrentAnimation(Animations anim){
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

void Actors::BasicEnemy::setParent(Node* parent){
	//impide que el objeto se insertado en la escena mas de una vez
	if (!_initialiced){
		for (int i = 0; i < _numBullets; i++){
			// inserta las balas en la escena (o SpriteBatchNode en este caso)
			parent->addChild(_bulletPool.at(i),getLocalZOrder());
		}
		_initialiced = true;
	}
	Sprite::setParent(parent);
}

void Actors::BasicEnemy::createIdleAnimation(std::string spriteName, int numberOfFrames){
	//crea el pool de objetos para la animacion
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
	//establece el sprite por defeto
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy0"));
	//indica que entre cada frame pasaran 0.25s
	animation->setDelayPerUnit(0.25f);

	//creamos la accion de animar el conjunto de frames (la animacion)
	auto animate = Animate::create(animation);

	//envolvemos la animacion para que se repita en buble
	_idleAnimation = RepeatForever::create(animate);

	//ponemos a la accion un identificador para poder pararla en el futuro
	_idleAnimation->setTag(Player::Animations::IDLE);

	//llamamos a retain apra conservar el objeto hasta que BasicEnemy se destruya.
	_idleAnimation->retain();
}

void Actors::BasicEnemy::createExplosionAnimation(std::string spriteName, int numberOfFrames){
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

	animation->setDelayPerUnit(0.1f);

	_explosionAnimation = Animate::create(animation);


	_explosionAnimation->setTag(Player::Animations::EXPLOSION);
	_explosionAnimation->retain();
}

void Actors::BasicEnemy::setVisible(bool visible){
	Sprite::setVisible(visible);
	if (visible){
		setHealth(ENEMY_HEALTH);
		runAction(_shoot);
	}
	else{
		stopActionByTag(SHOOT_TAG);
	}
}


void Actors::BasicEnemy::update(float dt){
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

void Actors::BasicEnemy::behaviour(float dt){
	//muevete para abajo
	setAnchorPoint(Point(0.5, 1));
	setPosition(getPositionX(), getPositionY() - _speed*dt);
	if (getPositionY() < 0){
		setVisible(false);
	}
}





