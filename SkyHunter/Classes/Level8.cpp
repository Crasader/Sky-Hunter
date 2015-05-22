#include "Level8.h"
#include "HeightEnemy.h"
#include "AudioEngine.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "HealthParticle.h"
#include "PlayerUpgradeParticle2.h"
#include "Cloud.h"


USING_NS_CC;

Scene* Level8::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = Level8::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level8::init()
{
	if (!BaseGameLayer::init())
	{
		return false;
	}
	_numEnemies = 20;
	_enemyIndex = 0;
	setTag(2);//level2
	_scoreToCompleTheLevel = 2000;
	_bg = new Background("fondo2");
	_bg->setParent(_gameBatchNode,BackgroundPos);
	initActors();
	awakeEnemyScheduler();
	_health = HealthParticle::create();
	_health->setTarget(_player);

	auto upgrade = PlayerUpgradeParticle2::create();
	upgrade->setPosition(_visibleSize.width*0.5, _visibleSize.height);
	upgrade->setVisible(true);
	upgrade->setTarget(_player);
	addChild(upgrade, ForegroundPos);

	auto cloud = Cloud::create();
	cloud->setPosition(_visibleSize.width*0.5, _visibleSize.height *1.5);
	cloud->setVisible(true);
	cloud->setTarget(_player);
	_gameBatchNode->addChild(cloud, ForegroundPos);
	
	addChild(_health,ForegroundPos);

	//start game loop
	this->schedule(schedule_selector(Level8::update));

	//start sound loop
	experimental::AudioEngine::play2d("music/Lensko.mp3", true, GameManager::getInstance()->getBgVolume()*0.01);

	//scheduleUpdate();
	schedule(schedule_selector(Level8::update));
	return true;
}

void Level8::initActors()
{
	for (int i = 0; i < _numEnemies; i++){
		auto enemy = HeightEnemy::create();
		//tell the enemies about the player.
		enemy->setTarget(_player);
		_enemyPool.pushBack(enemy);
		_gameBatchNode->addChild(enemy, ForegroundPos);
	}
	//tell the player about the enemies
	_player->setTargets(_enemyPool);
}




void Level8::update(float dt)
{
	BaseGameLayer::update(dt);
	_player->update(dt);
	//check for collision between enemies & player
	checkCollisions();
}

void Level8::respawnButtonAction()
{
	BaseGameLayer::respawnButtonAction();
	for (int i = 0; i < _numEnemies; i++){
		_enemyPool.at(i)->reset();
	}
}

void Level8::pauseButtonAction()
{
	BaseGameLayer::pauseButtonAction();
	experimental::AudioEngine::pauseAll();
	_player->pause();
	for (Sprite* enemy : _enemyPool){
		enemy->pause();
	}
}

void Level8::playButtonAction()
{
	BaseGameLayer::playButtonAction();
	experimental::AudioEngine::resumeAll();
	_player->resume();
	for (Sprite* enemy : _enemyPool){
		enemy->resume();
	}
}

void Level8::awakeEnemy()
{
	_enemyIndex = _enemyIndex % _numEnemies;
	//select enemy
	auto enemy = _enemyPool.at(_enemyIndex);
	//Positioning
	//the enemy size is 50*50, take care about the anchor point.
	enemy->setPositionX(RandomHelper::random_int(static_cast<int>(0 + 50 * 0.5),
		static_cast<int>(_visibleSize.width - 50 * 0.5)));
	enemy->setPositionY(_visibleSize.height + 50 * 0.5);
	enemy->setCurrentAnimation(BasicEnemy::Animations::IDLE);
	//awake after positioning
	if (!enemy->isVisible()){
		enemy->setVisible(true);
	}
	_enemyIndex++;
}


void Level8::awakeEnemyScheduler()
{
	//enemy ratio
	// set up the time delay
	DelayTime *delayAction = DelayTime::create(1.5f);
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(Level8::awakeEnemy, this));
	auto awakeEnemySequence = Sequence::create(delayAction, callSelectorAction, NULL);
	// run the action all the time
	runAction(RepeatForever::create(awakeEnemySequence));
}


void Level8::checkCollisions()
{
	if(GameManager::getInstance()->getPlayerScore()  == 700 || 
		GameManager::getInstance()->getPlayerScore() == 1400)
	{
		auto width = _health->getBoundingBox().size.width;
		auto height = _health->getBoundingBox().size.height;
		_health->setAnchorPoint(Point(0.5f, 0.5f));
		_health->setPositionX(RandomHelper::random_int(static_cast<int>(0 + width * 0.5),
			static_cast<int>(_visibleSize.width - width * 0.5)));
		_health->setPositionY(_visibleSize.height *1.3);
		_health->setVisible(true);
	}

	for (int i = 0; i < _numEnemies; i++){
		auto enemy = _enemyPool.at(i);
		if (_player->getBoundingBox().intersectsRect(enemy->getBoundingBox())
			&& enemy->isVisible() && _player->isVisible()){
			enemy->setCurrentAnimation(BasicEnemy::Animations::EXPLOSION);
			_player->setHealth(0);
		}
	}
}
