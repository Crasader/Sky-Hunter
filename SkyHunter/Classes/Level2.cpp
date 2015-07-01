#include "Level2.h"
#include "MediumEnemy.h"
#include "CustomAudioManager.h"
#include "GameManager.h"
#include "HealthParticle.h"
#include "PlayerUpgradeParticle.h"



USING_NS_CC;
using namespace Levels;
using namespace Actors;


Scene* Level2::createScene()
{
	auto scene = Scene::create();
	auto layer = Level2::create();
	scene->addChild(layer);
	return scene;
}

bool Level2::init()
{
	if (!BaseGameLayer::init())
	{
		return false;
	}


	initializeVariables();
	initActors();
	scheduleActions();
	return true;
}


void Level2::scheduleActions(){
	awakeBasicEnemyScheduler();

	//comienza el bucle del juego
	this->schedule(schedule_selector(Level2::update));



	schduleUpgrades();
}

void Level2::schduleUpgrades(){
	//lanzamos los actualizadores de salud y municion
	DelayTime *delayOne = DelayTime::create(60);
	DelayTime *delayTwo = DelayTime::create(80);
	CallFunc *launhHealth = CallFunc::create(CC_CALLBACK_0(Level2::launchHealth, this));
	CallFunc *launchUpgrade = CallFunc::create(CC_CALLBACK_0(Level2::launchUpgrade, this));
	runAction(RepeatForever::create(Sequence::create(delayOne, launhHealth, NULL)));

	runAction(RepeatForever::create(Sequence::create(delayTwo, launchUpgrade, NULL)));
}

void Level2::initActors()
{
	//40 enemigos en total
	_numEnemies = 40;
	//del 0 al 20 seran básicos
	_enemyIndex = 0;
	//20 enemigos medios
	_numMediumEnemies = 20;
	//del 20 al 40 medios
	_mediumEnemyIndex = 20;

	//añade los enemigos básicos al array de enemigos
	for (int i = 0; i < _numEnemies - _numMediumEnemies; i++){
		auto enemy = Actors::BasicEnemy::create();
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//añade los enemigos de nivel medio al array
	for (int i = 0; i < _numMediumEnemies; i++){
		auto enemy = MediumEnemy::create();
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//hacer que el jugador sepa acerca de los enemigos
	_player->setTargets(_enemyPool);
}

void Level2::initializeVariables(){
	CustomAudioManager::getInstance()->playBackgroundSound("music/Spectre.wav", true);
	setTag(2);//level2
	_scoreToCompleTheLevel = 1500;
	
	_bg = new Components::Background("fondo");
	_bg->setParent(_gameBatchNode, BackgroundPos);

	_mediumAwakeSpeed = 1.5f;
	_basicAwakeSpeed = 1.0f;

	//flag para saber si estan los enemigos de nivel medio en escena
	//y parar el scheduler de enemigos básicos
	_mediumSchedulerRunning = false;

	_health = Components::HealthParticle::create();
	_health->setTarget(_player);
	addChild(_health, ForegroundPos);

	_upgrade = Components::PlayerUpgradeParticle::create();
	_upgrade->setTarget(_player);
	addChild(_upgrade, ForegroundPos);
}




void Level2::update(float dt)
{
	BaseGameLayer::update(dt);
	_player->update(dt);
	//mirar colisiones entre player y enemigos
	checkCollisions();
	launchMediumEnemies();

}

void Level2::respawnButtonAction()
{
	BaseGameLayer::respawnButtonAction();
	_health->setVisible(false);
	_upgrade->setVisible(false);
	_mediumSchedulerRunning = false;

	stopAllActions();
	scheduleActions();

	for (int i = 0; i < _numEnemies; i++){
		_enemyPool.at(i)->reset();
	}
}

void Level2::pauseButtonAction()
{
	BaseGameLayer::pauseButtonAction();
	_player->pause();
	_health->pause();
	_upgrade->pause();
	for (Sprite* enemy : _enemyPool){
		enemy->pause();
	}
}

void Level2::playButtonAction()
{
	BaseGameLayer::playButtonAction();
	_player->resume();
	_health->resume();
	_upgrade->resume();
	for (Sprite* enemy : _enemyPool){
		enemy->resume();
	}
}




void Level2::awakeBasicEnemyScheduler()
{

	DelayTime *delayAction = DelayTime::create(_basicAwakeSpeed);

	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level2::awakeBasicEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	auto action = RepeatForever::create(awakeEnemySequence);
	action->setTag(BasicScheduler);

	runAction(action);
}

void Level2::awakeMediumEnemyScheduler()
{

	DelayTime *delayAction = DelayTime::create(_mediumAwakeSpeed);

	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level2::awakeMediumEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	auto action = RepeatForever::create(awakeEnemySequence);
	action->setTag(MediumScheduler);

	runAction(action);
}

void Level2::awakeMediumEnemy()
{
	//despierta n enemigo básico que sigue a un enemigo medio.
	_enemyIndex = _enemyIndex % (_numEnemies - _numMediumEnemies);

	//basic enemy
	auto basicEnemy = _enemyPool.at(_enemyIndex);
	auto size = basicEnemy->getBoundingBox().size;
	//Positioning
	basicEnemy->setPositionX(RandomHelper::random_int(static_cast<int>(size.width * 0.5),
		static_cast<int>(_visibleSize.width - size.width * 0.5)));
	basicEnemy->setPositionY(_visibleSize.height + size.height * 1.5);
	basicEnemy->setCurrentAnimation(Actors::BasicEnemy::Animations::IDLE);
	//awake
	if (!basicEnemy->isVisible()){
		basicEnemy->setVisible(true);
	}

	//medium enemy
	auto enemy = _enemyPool.at(_mediumEnemyIndex + _enemyIndex);
	//Positioning
	enemy->setPositionX(basicEnemy->getPositionX());
	enemy->setPositionY(basicEnemy->getPositionY() - size.height);
	enemy->setCurrentAnimation(Actors::BasicEnemy::Animations::IDLE);
	//awake
	if (!enemy->isVisible()){
		enemy->setVisible(true);
	}

	_enemyIndex++;
}

void Level2::awakeBasicEnemy()
{
	_enemyIndex = _enemyIndex % (_numEnemies - _mediumEnemyIndex);
	//select enemy
	auto enemy = _enemyPool.at(_enemyIndex);
	//Positioning
	enemy->setPositionX(RandomHelper::random_int(static_cast<int>(0 + 50 * 0.5),
		static_cast<int>(_visibleSize.width - 50 * 0.5)));
	enemy->setPositionY(_visibleSize.height + 50 * 0.5);
	enemy->setCurrentAnimation(Actors::BasicEnemy::Animations::IDLE);
	//awake
	if (!enemy->isVisible()){
		enemy->setVisible(true);
	}
	_enemyIndex++;
}

void Level2::checkCollisions()
{
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = _enemyPool.at(i);
		if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox())
			&& enemy->isVisible() && _player->isVisible()){
			enemy->setCurrentAnimation(Actors::BasicEnemy::Animations::EXPLOSION);
			_player->setHealth(0);
		}
	}
}

void Level2::launchHealth(){

	auto width = _health->getBoundingBox().size.width;
	auto height = _health->getBoundingBox().size.height;
	_health->setAnchorPoint(Point(0.5f, 0.5f));
	_health->setPositionX(RandomHelper::random_int(static_cast<int>(0 + width * 0.5),
		static_cast<int>(_visibleSize.width - width * 0.5)));
	_health->setPositionY(_visibleSize.height *1.3);
	_health->setVisible(true);

}

void Level2::launchUpgrade(){
	auto width = _upgrade->getBoundingBox().size.width;
	auto height = _upgrade->getBoundingBox().size.height;
	_upgrade->setAnchorPoint(Point(0.5f, 0.5f));
	_upgrade->setPositionX(RandomHelper::random_int(static_cast<int>(0 + width * 0.5),
		static_cast<int>(_visibleSize.width - width * 0.5)));
	_upgrade->setPositionY(_visibleSize.height *1.3);
	_upgrade->setVisible(true);
}

void Level2::launchMediumEnemies(){
	if (!_mediumSchedulerRunning && GameManager::getInstance()->getPlayerScore() >= 100){
		awakeMediumEnemyScheduler();
		stopActionByTag(BasicScheduler);
		//lanza un upgrade cada 4s
		DelayTime *delayAction = DelayTime::create(4.0f);
		CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level2::launchUpgrade, this));
		auto launchUpgrade = Sequence::create(delayAction, callSelectorAction, NULL);
		runAction(launchUpgrade);
		_mediumSchedulerRunning = true;
	}
}
