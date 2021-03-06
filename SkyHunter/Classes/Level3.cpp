#include "Level3.h"
#include "CustomAudioManager.h"
#include "GameManager.h"
#include "HealthParticle.h"
#include "PlayerUpgradeParticle2.h"
#include "PlayerUpgradeParticle.h"
#include "HeightEnemy.h"
#include "MediumEnemy.h"



USING_NS_CC;
using namespace Levels;
using namespace Components;
using namespace Actors;

Scene* Level3::createScene()
{
	auto scene = Scene::create();
	auto layer = Level3::create();
	scene->addChild(layer);
	return scene;
}

bool Level3::init()
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


void Level3::scheduleActions(){
	awakeMediumEnemyScheduler();

	//comienza el bucle del juego
	this->schedule(schedule_selector(Level3::update));
	schduleUpgrades();
}

void Level3::schduleUpgrades(){
	//lanza upgrades de salud y municion
	DelayTime *delayOne = DelayTime::create(60);
	DelayTime *delayTwo = DelayTime::create(30);
	CallFunc *launhHealth = CallFunc::create(CC_CALLBACK_0(Level3::launchHealth, this));
	CallFunc *launchUpgrade = CallFunc::create(CC_CALLBACK_0(Level3::launchUpgrade, this));
	auto upgrade = RepeatForever::create(Sequence::create(delayTwo, launchUpgrade, NULL));
	upgrade->setTag(Upgrade);
	runAction(RepeatForever::create(Sequence::create(delayOne, launhHealth, NULL)));
	runAction(upgrade);
}

void Level3::initActors()
{
	//50 enemigos en total
	//del 0 al 15 seran b�sicos
	_numEnemies = 45;_enemyIndex = 0;
	//15 enemigos medios
	//del 15 al 30 medios
	_numMediumEnemies = 15;	_mediumEnemyIndex = 15;
	//15 enemigos nivel alto
	//del 30 al 45 seran de nivel alto
	_numHeightEnemies = 15; _heightEnemyIndex = _mediumEnemyIndex + _numMediumEnemies;
	
	//a�ade los enemigos b�sicos al array de enemigos
	for (int i = 0; i < _numEnemies - _numMediumEnemies-_numHeightEnemies; i++){
		auto enemy = Actors::BasicEnemy::create();
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//a�ade los enemigos de nivel medio al array
	for (int i = 0; i < _numMediumEnemies; i++){
		auto enemy = Actors::MediumEnemy::create();
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//a�ade los enemigos de nivel alto al array
	for (int i = 0; i < _numHeightEnemies; i++){
		auto enemy = HeightEnemy::create();
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//hacer que el jugador sepa acerca de los enemigos
	_player->setTargets(_enemyPool);
}

void Level3::initializeVariables(){
	CustomAudioManager::getInstance()->playBackgroundSound("music/Spectre.wav", true);
	setTag(3);//level3
	_scoreToCompleTheLevel = 2000;
	_bg = new Background("fondo");
	_bg->setParent(_gameBatchNode, BackgroundPos);
	_mediumAwakeSpeed = 1.5f;
	_heightAwakeSpeed = 2.0f;

	//flag para saber si estan los enemigos de nivel medio en escena
	//y parar el scheduler de enemigos b�sicos
	_heightSchedulerRunning = false;

	_health = HealthParticle::create();
	_health->setTarget(_player);
	addChild(_health, ForegroundPos);

	_upgrade = PlayerUpgradeParticle::create();
	_upgrade->setTarget(_player);
	addChild(_upgrade, ForegroundPos);

	_upgrade2 = PlayerUpgradeParticle2::create();
	_upgrade2->setTarget(_player);
	addChild(_upgrade2, ForegroundPos);
}




void Level3::update(float dt)
{
	BaseGameLayer::update(dt);
	_player->update(dt);
	//mira colisiones entre enemigos y el player
	checkCollisions();
	launchHeightEnemies();
}

void Level3::respawnButtonAction()
{
	BaseGameLayer::respawnButtonAction();
	_health->setVisible(false);
	_upgrade->setVisible(false);
	_upgrade2->setVisible(false);
	_heightSchedulerRunning = false;

	stopAllActions();
	scheduleActions();

	for (int i = 0; i < _numEnemies; i++){
		_enemyPool.at(i)->reset();
	}
}

void Level3::pauseButtonAction()
{
	BaseGameLayer::pauseButtonAction();
	_player->pause();
	_health->pause();
	_upgrade->pause();
	_upgrade2->pause();
	for (Sprite* enemy : _enemyPool){
		enemy->pause();
	}
}

void Level3::playButtonAction()
{
	BaseGameLayer::playButtonAction();
	_player->resume();
	_health->resume();
	_upgrade->resume();
	_upgrade2->resume();
	for (Sprite* enemy : _enemyPool){
		enemy->resume();
	}
}




void Level3::awakeMediumEnemyScheduler()
{

	DelayTime *delayAction = DelayTime::create(_mediumAwakeSpeed);

	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level3::awakeMediumEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	auto action = RepeatForever::create(awakeEnemySequence);
	action->setTag(MediumScheduler);

	runAction(action);
}

void Level3::awakeMediumEnemy()
{
	//despierta un enemigo b�sico que sigue a un enemigo medio.
	_enemyIndex = _enemyIndex % (_numEnemies - _numMediumEnemies-_numHeightEnemies);

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
	auto enemy = _enemyPool.at(_mediumEnemyIndex+_enemyIndex);
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

void Level3::awakeHeightEnemy()
{
	//indice entre 0 y 15, a�adir offset correspondiente al tipo de enemigo,
	//para ellos tenemos 15, 15 y 15 enemigos de cada tipo
	_enemyIndex = _enemyIndex % (_numEnemies - _numMediumEnemies - _numHeightEnemies);

	//medium enemy
	auto mediumEnemy = _enemyPool.at(_enemyIndex + _numMediumEnemies);
	auto mediumEnemySize = mediumEnemy->getBoundingBox().size;
	//Positioning
	mediumEnemy->setPositionX(RandomHelper::random_int(static_cast<int>(mediumEnemySize.width * 0.5),
		static_cast<int>(_visibleSize.width - mediumEnemySize.width * 0.5)));
	mediumEnemy->setPositionY(_visibleSize.height + mediumEnemySize.height * 1.5);
	mediumEnemy->setCurrentAnimation(Actors::BasicEnemy::Animations::IDLE);
	//awake
	if (!mediumEnemy->isVisible()){
		mediumEnemy->setVisible(true);
	}

	//height enemy
	auto heightEnemy = _enemyPool.at(_numHeightEnemies + _numMediumEnemies + _enemyIndex);
	auto heightEnemySize = heightEnemy->getBoundingBox().size;
	//Positioning
	heightEnemy->setPositionX(RandomHelper::random_int(static_cast<int>(heightEnemySize.width * 0.5),
		static_cast<int>(_visibleSize.width - heightEnemySize.width * 0.5)));
	heightEnemy->setPositionY(mediumEnemy->getPositionY() - mediumEnemySize.height);
	heightEnemy->setCurrentAnimation(Actors::BasicEnemy::Animations::IDLE);
	//awake
	if (!heightEnemy->isVisible()){
		heightEnemy->setVisible(true);
	}

	_enemyIndex++;
}

void Level3::awakeHeightEnemyScheduler()
{

	DelayTime *delayAction = DelayTime::create(_heightAwakeSpeed);

	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level3::awakeHeightEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	auto action = RepeatForever::create(awakeEnemySequence);
	action->setTag(HeightScheduler);

	runAction(action);
	
}




void Level3::checkCollisions()
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

void Level3::launchHealth(){

	auto width = _health->getBoundingBox().size.width;
	auto height = _health->getBoundingBox().size.height;
	_health->setAnchorPoint(Point(0.5f, 0.5f));
	_health->setPositionX(RandomHelper::random_int(static_cast<int>(0 + width * 0.5),
		static_cast<int>(_visibleSize.width - width * 0.5)));
	_health->setPositionY(_visibleSize.height *1.3);
	_health->setVisible(true);

}

void Level3::launchUpgrade(){
	auto width = _upgrade->getBoundingBox().size.width;
	auto height = _upgrade->getBoundingBox().size.height;
	_upgrade->setAnchorPoint(Point(0.5f, 0.5f));
	_upgrade->setPositionX(RandomHelper::random_int(static_cast<int>(0 + width * 0.5),
		static_cast<int>(_visibleSize.width - width * 0.5)));
	_upgrade->setPositionY(_visibleSize.height *1.3);
	_upgrade->setVisible(true);
}

void Level3::launchUpgrade2(){
	auto width = _upgrade2->getBoundingBox().size.width;
	auto height = _upgrade2->getBoundingBox().size.height;
	_upgrade2->setAnchorPoint(Point(0.5f, 0.5f));
	_upgrade2->setPositionX(RandomHelper::random_int(static_cast<int>(0 + width * 0.5),
		static_cast<int>(_visibleSize.width - width * 0.5)));
	_upgrade2->setPositionY(_visibleSize.height *1.3);
	_upgrade2->setVisible(true);
}

void Level3::launchHeightEnemies(){
	if (!_heightSchedulerRunning && GameManager::getInstance()->getPlayerScore() >= 700){
		awakeHeightEnemyScheduler();
		stopActionByTag(MediumScheduler);
		stopActionByTag(Upgrade);

		DelayTime *delayAction = DelayTime::create(8.0f);

		CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level3::launchUpgrade2, this));
		auto launchUpgrade2 = Sequence::create(delayAction, callSelectorAction, NULL);

		runAction(launchUpgrade2);

		DelayTime *delayOne = DelayTime::create(68);
		
		runAction(RepeatForever::create(Sequence::create(delayOne, callSelectorAction, NULL)));
		_heightSchedulerRunning = true;
	}
}